# BUG-14 Fence Synchronization — Lessons Learned

## What was fixed

Replaced `VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT` with
`VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT` in both `Execute` and `ExecuteBatch`.
No other synchronization changes were needed.

## The deadlock attempt

An earlier version of this fix tried to add a `vkWaitForFences` + `vkResetFences`
guard at the **top** of `Execute` and `ExecuteBatch` before `vkBeginCommandBuffer`,
with the fence created using `VK_FENCE_CREATE_SIGNALED_BIT` to make the first call
safe. This deadlocked immediately on the first `Execute` call.

### Why it deadlocked

`mFinished_fence` is not owned by the kernel — it is a copy of the handle from
`mWaitFence` on the `ComputeContext` (set at `ComputeEngine_VK.cpp:751`):

```cpp
mFinished_fence = *mProgram->GetContext()->GetWaitFence();
```

The same fence (`mWaitFence`) is also used by `Utilities::endSingleTimeCommands`,
which is called by every `SetData` / `GetData` / `CopyBuffer` transfer operation.
`endSingleTimeCommands` ends with:

```cpp
vkWaitForFences(device, 1, &p_fence, VK_TRUE, UINT64_MAX);
vkResetFences(device, 1, &p_fence);   // ← leaves fence UNSIGNALED
```

By the time `Execute` is called for the first time, the program controller has
already performed many buffer uploads (settings, control, pool data). Each one
calls `endSingleTimeCommands`, and the last one leaves `mWaitFence` in an
**unsignaled** state. A `vkWaitForFences` on an unsignaled fence with no pending
submission blocks forever.

`VK_FENCE_CREATE_SIGNALED_BIT` on the fence creation only sets the initial state
at device-creation time. By the time the first `Execute` runs, the fence has been
reset multiple times by transfers and is no longer signaled.

### Why the original end-of-function pattern is correct

`Execute` and `ExecuteBatch` both end with:

```cpp
vkWaitForFences(...)   // block until this dispatch is done
vkResetFences(...)     // reset for the next submission
```

This guarantees that when either function **returns**, the command buffer is no
longer in-flight and the fence is in the unsignaled state ready for the next
`vkQueueSubmit`. Sequential calls are therefore always safe to re-record without
any top-of-function guard.

## The root cause this exposes (BUG-15) — now fixed

The real underlying problem was that `mFinished_fence` / `mWaitFence` was a **single
shared fence** used by both compute dispatches and all buffer transfer operations.
BUG-15 was fixed by uncommenting the kernel-owned `vkCreateFence` block so each
`ComputeKernel` creates and destroys its own private `mFinished_fence`, leaving
`mWaitFence` on `ComputeContext` solely for transfers.
