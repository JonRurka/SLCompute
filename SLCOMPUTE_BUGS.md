# SLCompute — Bug Audit

Deep scan performed 2026-11-25. All previously tracked bugs have been fixed.

---

## BUG-1 — `ExecuteBatch`: ONE_TIME_SUBMIT command buffer submitted `num` times [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:837,894`
**Severity:** Fatal

`ExecuteBatch` records `*mComputeCmdBuffer` once with `VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT`, then builds `num` `VkSubmitInfo` structs all pointing to that same buffer and passes them to a single `vkQueueSubmit` call. The Vulkan spec (section 6.4) states a command buffer recorded with `ONE_TIME_SUBMIT_BIT` enters the invalid state after it is submitted once and must not be submitted again. Submitting it `num` times in one `vkQueueSubmit` is a spec violation. GPU drivers may silently corrupt output or trigger a device-lost error.

```cpp
// line 837
beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
// ...
// line 880 — same mComputeCmdBuffer in every submitInfo
submitInfo.pCommandBuffers = mComputeCmdBuffer;
// line 894 — submitted num times
vkQueueSubmit(*mComputeQueue, num, submits.data(), mFinished_fence);
```

### Fix

Remove `VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT` from `beginInfo.flags` (use `0`) so the same recorded buffer can be submitted multiple times. It is already protected by `vkQueueWaitIdle` before begin and `vkWaitForFences` after submit.

---

## BUG-2 — `ExecuteBatch`: semaphore queue popped without bounds check [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:847`
**Severity:** High

`ExecuteBatch` pops `num` semaphores from `mAvailable_Semaphore` (pre-filled with `DEFAULT_AVAILABLE_SEMAPHORE = 100`) with `front()`/`pop()` in a loop. Any call with `num > 100`, or any call after the pool is partially exhausted by prior calls, calls `front()` on an empty `std::queue`, which is undefined behaviour and crashes in practice.

```cpp
for (int i = 0; i < num; i++) {
    semaphores.push_back(mAvailable_Semaphore.front()); // UB if empty
    mAvailable_Semaphore.pop();
}
```

### Fix

```cpp
SL_ASSERT((size_t)num <= mAvailable_Semaphore.size(), "Not enough semaphores in pool.");
```

---

## BUG-3 — `ExecuteBatch`: last semaphore recycled in signaled state [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:905`
**Severity:** High

Semaphores `semaphores[0..num-2]` are used as `pWaitSemaphores` in the next submit's wait chain, so they are consumed (unsignaled) before being returned to the pool. But `semaphores[num-1]`, the signal semaphore from the final submit, is returned directly to `mAvailable_Semaphore` without being waited on — it remains in the signaled state. The next time it is dequeued and used as a `pWaitSemaphores` entry, the wait completes immediately (the signal is already set), so no synchronization occurs on that dispatch — a silent race condition.

```cpp
for (VkSemaphore s : semaphores) {
    mAvailable_Semaphore.push(s); // semaphores[num-1] is still signaled
}
```

### Fix

Before recycling, perform a CPU-side wait or use a fence to drain the final signal, or redesign `ExecuteBatch` to use only fences for CPU synchronization and avoid semaphores entirely (they serve no purpose here since all submits target the same queue and sequential queue submissions are ordered).

---

## BUG-4 — `ComputeProgram::Dispose`: `ComputeKernel` heap objects leaked [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:658`
**Severity:** High

`ComputeProgram::Dispose()` iterates the `kernels` map, calls `krn->Dispose()` on each `ComputeKernel*`, then calls `kernels.clear()`. It never calls `delete krn`. Each `ComputeKernel` is heap-allocated with `new` in `GetKernel()`. All `ComputeKernel` C++ objects leak on dispose.

```cpp
for (auto [key, krn] : kernels) {
    krn->Dispose();
    // delete krn; ← missing
}
kernels.clear();
```

### Fix

```cpp
for (auto [key, krn] : kernels) {
    krn->Dispose();
    delete krn;
}
```

---

## BUG-5 — `ComputeContext::GetKernel`: null pointer dereference if program not found [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:391`
**Severity:** High

`GetKernel(p_name, name)` calls `Programs(p_name)->GetKernel(name)` where `Programs()` returns `nullptr` when the named program does not exist. The `->GetKernel(...)` call on `nullptr` is an immediate crash.

```cpp
ComputeKernel* ComputeContext::GetKernel(std::string p_name, std::string name) {
    return Programs(p_name)->GetKernel(name); // null deref if program not found
}
```

### Fix

```cpp
ComputeProgram* prog = Programs(p_name);
SL_ASSERT(prog != nullptr, "Program not found in GetKernel.");
return prog->GetKernel(name);
```

---

## BUG-6 — `ComputeController_VK::Close`: controller objects leaked [FIXED]

**File:** `src/Compute/Vulkan/ComputeController_VK.cpp:140`
**Severity:** High

`Close()` calls `m_controllers.clear()` on `std::vector<ComputeController_VK*>`. Each entry was allocated with `new` in `New()`. Clearing the vector does not `delete` the objects — all `ComputeController_VK` instances and their entire Vulkan resource trees are permanently leaked on shutdown.

```cpp
void ComputeController_VK::Close() {
    m_controllers.clear(); // pointers discarded, no delete
    DisposePlatform();
}
```

### Fix

```cpp
for (auto* ctrl : m_controllers)
    delete ctrl;
m_controllers.clear();
```

---

## BUG-7 — Zero-size `VkBuffer` for unpopulated static pool [FIXED]

**File:** `src/SLC_ComputePool_private.cpp` (static pool `initialize_buffers` path)
**Severity:** High

If a static pool is created but no buffers are registered into it before `Start()`, the pool's internal float scalar count is 0. The resulting `CreateBuffer(..., 0, sizeof(float))` calls `vkCreateBuffer` with `size = 0`. The Vulkan spec (`VkBufferCreateInfo`) requires `size > 0`. Passing zero is undefined behaviour; many drivers return an error that is not checked, leaving the buffer handle uninitialized.

### Fix

Guard the buffer creation: if the scalar count is zero, skip the allocation and bind the existing dummy static buffer for that slot.

---

## BUG-8 — `createShaderModule`: strict-aliasing UB on `char*` → `uint32_t*` cast [FIXED]

**File:** `src/Compute/Vulkan/vulkan_utils.cpp:854`
**Severity:** Medium

`VkShaderModuleCreateInfo::pCode` is set by casting `std::vector<char>::data()` (a `char*`) directly to `const uint32_t*`. Under the C++ standard, accessing memory through a pointer of an incompatible type is strict-aliasing undefined behaviour. It works in practice due to alignment guarantees from `std::allocator`, but is technically UB and may break with aggressive LTO.

```cpp
createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
```

### Fix

Change the SPIR-V storage type to `std::vector<uint32_t>` throughout (file read, `Set_Binary`, `binary_resources.hpp`), eliminating the cast.

---

## BUG-9 — `FORCE_VALIDATION_LAYERS` hardcoded `true` in all builds [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:29`
**Severity:** Medium

`#define FORCE_VALIDATION_LAYERS true` unconditionally enables Vulkan validation layers for every build including Release and the packaged library. This adds significant per-call CPU overhead, writes to stderr, and requires the LunarG SDK to be installed on end-user machines. If the layers are absent, `vkCreateInstance` fails with `VK_ERROR_LAYER_NOT_PRESENT`.

```cpp
#define FORCE_VALIDATION_LAYERS true
```

### Fix

```cpp
#ifdef NDEBUG
#define FORCE_VALIDATION_LAYERS false
#else
#define FORCE_VALIDATION_LAYERS true
#endif
```

---

## BUG-10 — Win32: `vkGetDeviceProcAddr` called on null `mDevice` before `vkCreateDevice` [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp` (Win32 block, ~line 415)
**Severity:** Low

Inside a `#ifdef WIN32` block, `vkGetDeviceProcAddr(mDevice, ...)` is called to fetch an extension function pointer before `vkCreateDevice` runs. At that point `mDevice` is a default-initialized null `VkDevice`. Passing a null handle to `vkGetDeviceProcAddr` is undefined behaviour per the Vulkan spec. In practice the result is overwritten after the real `vkCreateDevice`, so no crash occurs, but it triggers a validation layer error.

### Fix

Move the `vkGetDeviceProcAddr` call to after `vkCreateDevice` succeeds.

---

## BUG-11 — `SL_Strided_Buffer_struct::id` never default-initialized [FIXED]

**File:** `include/SLC_Structures.h:79`
**Severity:** Medium

`SL_Strided_Buffer_struct` has a `uint32_t id` field with no default member initializer. It is only assigned when a buffer is registered through a pool. Any call to `ID()` on a buffer not registered through the pool returns an indeterminate value. The shader dispatch uses this id as the float offset into the static pool — an indeterminate value silently corrupts GPU computation.

### Fix

```cpp
uint32_t id = 0;
```

---

## Summary

| ID | Severity | Description |
|----|----------|-------------|
| BUG-1 | Fatal | `ExecuteBatch` submits ONE_TIME_SUBMIT buffer `num` times |
| BUG-2 | High | `ExecuteBatch` semaphore queue popped without bounds check |
| BUG-3 | High | `ExecuteBatch` last semaphore recycled while still signaled |
| BUG-4 | High | `ComputeProgram::Dispose` leaks `ComputeKernel` heap objects |
| BUG-5 | High | `ComputeContext::GetKernel` null deref if program not found |
| BUG-6 | High | `ComputeController_VK::Close` leaks all controller objects |
| BUG-7 | High | ~~Zero-size `VkBuffer` for unpopulated static pool~~ FIXED |
| BUG-8 | Medium | ~~`createShaderModule` strict-aliasing UB on char*→uint32_t*~~ FIXED |
| BUG-9 | Medium | ~~`FORCE_VALIDATION_LAYERS` hardcoded true in all builds~~ FIXED |
| BUG-10 | Low | ~~Win32: `vkGetDeviceProcAddr` on null device before `vkCreateDevice`~~ FIXED |
| BUG-11 | Medium | ~~`SL_Strided_Buffer_struct::id` uninitialized — indeterminate GPU offset~~ FIXED |
