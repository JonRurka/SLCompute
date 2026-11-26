# Thread Safety Limitations

## Current status

SLCompute is **not thread-safe**. The compute engine is designed for single-threaded
use. Calling any two kernel `Execute` / `ExecuteBatch` operations concurrently from
different threads on the same `ComputeContext` will produce undefined behaviour.

## Shared resources that cause races

### 1. `mComputeCmdBuffer` — fatal data race

All `ComputeKernel` instances in the same `ComputeContext` share a single
`VkCommandBuffer` via `context->GetPreferedComputeCmdBuffer()`. Recording
(`vkBeginCommandBuffer` → `vkCmdDispatch` → `vkEndCommandBuffer`) on the same
buffer from two threads simultaneously is undefined behaviour per the Vulkan spec.

### 2. `mComputeQueue` — unsynchronised queue submit

All kernels in the same context share `mComputeQueue`. The Vulkan spec requires
external synchronisation on any `VkQueue` accessed from multiple threads.
Concurrent `vkQueueSubmit` calls without a mutex will race.

## What is safe after BUG-15 fix

Each `ComputeKernel` now owns its own `mFinished_fence` (created and destroyed with
the kernel). Fence wait/reset operations no longer race with each other or with
buffer transfers, which use the separate `ComputeContext::mWaitFence`.

## Why this is not currently an active bug

`Execute` and `ExecuteBatch` are both fully synchronous — they block the calling
thread until the GPU finishes (`vkWaitForFences`) before returning. Concurrent
kernel execution is therefore not possible from a single thread, and the library
does not expose an async dispatch API. The races only manifest if a caller
dispatches kernels from multiple threads simultaneously, which is not a supported
or documented use case.

## What a thread-safe implementation would require

- Each kernel allocated its own `VkCommandBuffer` from the shared pool (pool
  allocation must be serialised with a mutex, per the Vulkan spec).
- A mutex guarding all `vkQueueSubmit` calls on `mComputeQueue`.
- Optionally, a per-kernel or per-thread command pool to avoid pool-level lock
  contention on high-parallelism workloads.
