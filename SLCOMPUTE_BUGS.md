# SLCompute — Known Bugs

Source version: Debug build (`slcom57891d6caaa5a`, `SLC_*` API).  
All file paths are relative to `/home/jon/.conan2/p/b/slcom57891d6caaa5a/b/`.

---

## BUG-1 — VMA staging buffer not marked mappable (crash in Debug)

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:1113–1129`  
**Severity:** Fatal in Debug builds. Silent in Release (assertion compiled out).

### What happens

The staging buffer is allocated with `VmaAllocationCreateFlags = 0`:

```cpp
Utilities::CreateBuffer(
    *mPhysicalDevice, *mLogicalDevice,
    mSize,
    VK_BUFFER_USAGE_TRANSFER_DST_BIT | mStage_transfer_flag,
    VK_SHARING_MODE_CONCURRENT,
    false,
    (VkBufferCreateFlags)0,
    (VmaAllocationCreateFlags)0,          // ← missing HOST_ACCESS flag
    VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
    mAllQueueFamilies,
    stagingBuffer, stagingBufferMemory, stagingBufferAllocation
);
```

VMA 3.x (this codebase uses **v3.2.1**) requires that any allocation passed to `vmaMapMemory` must be created with one of:

- `VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT` — for CPU→GPU upload (memcpy)
- `VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT` — for arbitrary CPU read/write

Without either flag, `FLAG_MAPPING_ALLOWED` is never set on the `VmaAllocation_T` object at construction. When `vmaMapMemory` is later called (via `FlushToBuffer` in `SetData`, or directly in `GetData`), it hits this assertion in `vk_mem_alloc.h:11058`:

```cpp
void VmaAllocation_T::BlockAllocMap() {
    VMA_ASSERT(IsMappingAllowed() &&
        "Mapping is not allowed on this allocation! "
        "Please use one of the new VMA_ALLOCATION_CREATE_HOST_ACCESS_* flags...");
    ...
}
```

`VMA_ASSERT` expands to `assert()` in Debug and to nothing when `NDEBUG` is defined (Release). This is why Debug crashes and Release does not — the underlying memory is HOST_VISIBLE in both cases, so the actual Vulkan mapping would succeed; VMA's own guard is what aborts.

### Call path

```
Test_Buffer_Engine / SetData
  → ComputeBuffer::SetData(src, 0, size)
    → Utilities::FlushToBuffer(..., stagingBufferAllocation, ...)
        → vmaMapMemory(...)
            → VmaAllocation_T::BlockAllocMap()
                → VMA_ASSERT(IsMappingAllowed())   ← SIGABRT
```

### Fix

Add `VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT` to the staging buffer's `vma_flags`. Because the staging buffer is also read back during `GetData`, `VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT` is the more correct choice:

```cpp
VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT,  // was: (VmaAllocationCreateFlags)0
VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
```

---

## BUG-2 — Hard-coded device index 1

**File:** `src/SLC_Program.cpp:306`  
**Severity:** Fatal crash on single-GPU systems. Wrong device on systems with more than two GPUs.

### What happens

After enumerating physical devices, the second device in the list is selected unconditionally:

```cpp
std::vector<Vulkan_Device_Info> devices = ComputeInterface::GetSupportedDevices_Vulkan();
// ...
Vulkan_Device_Info device = devices[1];   // ← hard-coded index
```

If the system has only one GPU, `devices[1]` is an out-of-bounds access on a `std::vector`, resulting in undefined behaviour (typically a crash or returning garbage data). If a future system has three or more GPUs, the index may also select the wrong device.

The `GetSupportedDevices_Vulkan` function creates a temporary `VkInstance` solely to enumerate devices, so the returned list order depends on the Vulkan driver's enumeration order, which is not guaranteed to be stable across driver updates.

The runtime log before the crash confirms two devices are present and shows which is at index 1:

```
DEBUG::ProgramController: Get Compute Devices: 2
DEBUG::ProgramController:     Found: Intel(R) Graphics (ARL)       ← index 0
DEBUG::ProgramController:     Found: NVIDIA GeForce RTX 5080 Laptop GPU  ← index 1
DEBUG::ProgramController: Selected compute device: NVIDIA GeForce RTX 5080 Laptop GPU
```

This only works by coincidence on this machine.

### Fix

Replace the hard-coded index with a selection policy. The most direct option is to prefer a discrete GPU over an integrated GPU:

```cpp
Vulkan_Device_Info device = devices[0]; // default fallback
for (const auto& d : devices) {
    if (d.DeviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        device = d;
        break;
    }
}
```

Alternatively, expose a `ProgramSettings::device_index` or `device_name` field so the caller can select the device explicitly.

---

## BUG-3 — Infinite loop in `findMemoryType` [FIXED]

**File:** `src/Compute/Vulkan/vulkan_utils.cpp:717`  
**Severity:** Infinite loop / process hang if no suitable memory type is found before all types are exhausted.

### What happens

The loop condition uses the constant `memProperties.memoryTypeCount` instead of comparing `i` against it:

```cpp
uint32_t Utilities::findMemoryType(VkPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; memProperties.memoryTypeCount; i++) {   // ← bug: should be i < memProperties.memoryTypeCount
        if (typeFilter & (1 << i) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type!");
}
```

`memProperties.memoryTypeCount` is a non-zero constant (typically 11–16 on NVIDIA hardware). Using it directly as the loop condition means it always evaluates to `true`, so the loop never terminates through the condition — it only exits via the `return i` inside. The `throw` at the end is unreachable.

In practice, a compatible memory type is always found before `i` goes out of bounds, so this does not currently crash. However, if `typeFilter` and `properties` are ever used to request an impossible combination (no matching memory type exists), the loop increments `i` past `memoryTypeCount`, reads out-of-bounds memory from `memProperties.memoryTypes[]`, and loops indefinitely.

Note: `findMemoryType` is not used in the main buffer allocation path (which uses VMA). It is called by `CreateImage` (`vulkan_utils.cpp:700`), so it only triggers for image allocations.

### Fix

```cpp
for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
```

---

## BUG-4 — External buffer path leaves `mBuffer` uninitialized [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:1058–1131`  
**Severity:** Use of uninitialized `VkBuffer` handle. Any subsequent `CopyBuffer`, `SetData`, or `GetData` call on an external buffer will pass garbage to Vulkan.

### What happens

`ComputeBuffer`'s constructor branches on the `external` parameter. The non-external path (the normal case) allocates `mBuffer` with VMA. The external path is entirely commented-out dead code:

```cpp
if (external) {
    // All of this is commented out:
    // m_gl_vk_buffer.bufVk = alloc->createBuffer(...)
    // mBuffer = m_gl_vk_buffer.bufVk.buffer
    // initExternalCopy()
}
else {
    Utilities::CreateBuffer(..., mBuffer, mBufferMemory, mBufferAllocation);
}

// Staging buffer is always created unconditionally below — even for external.
Utilities::CreateBuffer(..., stagingBuffer, stagingBufferMemory, stagingBufferAllocation);
```

When `external = true`, the `if` block executes but does nothing (all code inside is in `/* */` comments), so `mBuffer` retains its default-initialized value — a null or garbage `VkBuffer` handle. The staging buffer is created normally. Any call that uses `mBuffer` (such as `CopyBuffer` from staging to device) passes this invalid handle to Vulkan, which is undefined behaviour and will typically produce a validation error or a GPU fault.

The `initExternalCopy()` method itself is guarded by `#ifdef EXTERNAL_BUFFERS` which is never defined, making external buffer support entirely non-functional.

### Current exposure

`ComputeContext::CreateBuffer` passes `external = false` in all calls from the current GPGSL/SLC layer, so this path is not currently reachable through normal use. It becomes a live bug the moment any caller passes `external = true`.

### Fix

Either remove the `external` parameter and all associated dead code until the feature is ready to be implemented, or add an assertion that aborts early:

```cpp
if (external) {
    SL_ASSERT(false, "External buffer support is not implemented.");
}
```

---

## BUG-5 — Semaphore leak in `ExecuteBatch` [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:838–841`  
**Severity:** Resource leak leading to undefined behaviour (empty-queue `front()`) after 100 `ExecuteBatch` calls.

### What happens

`ExecuteBatch` builds a semaphore chain for sequential dispatch. For each invocation it pops `num` semaphores from `mAvailable_Semaphore` (pre-filled with 100 `VkSemaphore` objects at kernel build time):

```cpp
std::vector<VkSemaphore> semaphores;
for (int i = 0; i < num; i++) {
    semaphores.push_back(mAvailable_Semaphore.front());
    mAvailable_Semaphore.pop();                           // ← never returned
}
```

The popped semaphores are submitted to the queue and waited on, but they are never pushed back into `mAvailable_Semaphore` after the batch completes. Each `ExecuteBatch` call with `num = N` permanently drains N semaphores from the pool.

After 100 total semaphores have been consumed (e.g., 100 calls with `num = 1`, or one call with `num = 100`), `mAvailable_Semaphore` is empty. The next call to `mAvailable_Semaphore.front()` on an empty `std::queue` is undefined behaviour — typically a crash or memory corruption.

Additionally, the function contains a dead second `return 0` statement at line 904 (after the first `return 0` at line 902), which is unreachable but harmless.

### Fix

Return semaphores to the queue after the fence wait confirms the batch has completed:

```cpp
vkWaitForFences(*mDevice, 1, &mFinished_fence, VK_TRUE, UINT64_MAX);
vkResetFences(*mDevice, 1, &mFinished_fence);

for (VkSemaphore s : semaphores) {
    mAvailable_Semaphore.push(s);
}
```

---

## BUG-7 — `INCLUDE_COMPLEX_ACCESSORS` defined as `true`/`TRUE` silently disables complex accessors [FIXED]

**Files:** `shaders/libSLC/standard_buffers.inc`, `shaders/libSLC/complex_imp.inc`

`INCLUDE_COMPLEX_ACCESSORS` was defined as `true` (standard_buffers.inc) and `TRUE` (complex_imp.inc). The GLSL preprocessor treats unrecognized identifiers in `#if` expressions as `0`, so `#if INCLUDE_COMPLEX_ACCESSORS` always evaluated false and the entire complex accessor block — `write_res_complex`, `Get_Complex`, and all helpers — was silently excluded from every compiled shader. Fixed by changing both definitions to `1`.

---

## BUG-8 — Shader recompile not reliably triggered on `.inc` file changes [FIXED]

**File:** `CMakeLists.txt`

Both `.spv` outputs were listed as outputs of a single `add_custom_command`. Ninja can consider such a rule satisfied when any one output is up to date, potentially skipping recompilation when only an `.inc` dependency changed. Additionally, `file(GLOB_RECURSE)` for the dependency list is evaluated at configure time, so newly added `.inc` files are not tracked until CMake reconfigures.

Fixed by splitting into one `add_custom_command` per shader and passing `-MD -MF <depfile>` to `glslc` with a `DEPFILE` clause, letting the compiler report its own transitive includes directly to Ninja.

---

## BUG-9 — PARAM_3 and PARAM_4 buffer bindings are wrong, PARAM_4 collides with pool buffer [FIXED]

**File:** `shaders/libSLC/standard_buffers.inc` lines 54, 61

```glsl
#define PARAM_3_BUFFER_BIND (PARAM_BIND_START + 3)  // = binding 6, should be 5
#define PARAM_4_BUFFER_BIND (PARAM_BIND_START + 4)  // = binding 7, should be 6
```

The offsets skip binding 5 and place PARAM_4 at binding 7. Binding 7 is `POOL_BUFF_BIND_START` — the first static pool buffer — causing a collision. Any dispatch using parameter slots 3 or 4 will read/write the wrong buffer; parameter 4 silently aliases the static pool.

**Fix:** Change to `(PARAM_BIND_START + 2)` and `(PARAM_BIND_START + 3)`.

---

## BUG-6 — `ComputeBuffer_VK` heap allocation leaked in `Destroy_Buffer` [FIXED]

**File:** `src/Compute/IComputeBuffer.cpp:63–67`, `src/SLC_ComputePool_private.cpp:168–180`  
**Severity:** Memory leak. One `ComputeBuffer_VK` object (and its `ComputeBuffer` member) leaks per destroyed buffer. GPU memory is freed correctly; only the C++ heap allocation leaks.

### What happens

`IComputeBuffer` is a pimpl wrapper. It holds a raw `IComputeBuffer_private* p_inst` which points to the concrete `ComputeBuffer_VK` heap allocation. `Dispose()` calls through to the private implementation and then nulls the pointer, but does not free it:

```cpp
// IComputeBuffer.cpp:63
void IComputeBuffer::Dispose()
{
    p_inst->Dispose();    // frees VkBuffer/VmaAllocation correctly
    p_inst = nullptr;     // ← p_inst itself (the ComputeBuffer_VK*) is never deleted
}
```

`IComputeBuffer` has no custom destructor that would `delete p_inst`. When `Destroy_Buffer` then calls `delete comp_buffer`, it destroys the `IComputeBuffer` wrapper, but the `ComputeBuffer_VK` object that `p_inst` was pointing to remains on the heap with no owner.

```cpp
// SLC_ComputePool_private.cpp:168
void ComputePool_private::Destroy_Buffer(BufferInstance buffer) {
    m_pool_buffers[buffer].comp_buffer->Dispose();  // p_inst->Dispose(), then p_inst = nullptr
    if (m_type == PoolType::Dynamic) {
        delete m_pool_buffers[buffer].comp_buffer;  // deletes IComputeBuffer wrapper only
    }                                               // ComputeBuffer_VK* already nulled, leaked
    delete m_pool_buffers[buffer].info_buffer;
    m_pool_buffers.erase(buffer);
}
```

The same pattern occurs in `ComputePool_private::Dispose()` (lines 361–376), which loops over all pool buffers on shutdown.

### Fix

`IComputeBuffer::Dispose()` should delete the private implementation after calling through to it:

```cpp
void IComputeBuffer::Dispose()
{
    p_inst->Dispose();
    delete p_inst;
    p_inst = nullptr;
}
```

Alternatively, replace the raw pointer with `std::unique_ptr<IComputeBuffer_private>`, which deletes automatically when `IComputeBuffer` is destroyed.

---

## BUG-10 — `findQueueFamilies` first loop never increments `i` [FIXED]

**File:** `src/Compute/Vulkan/vulkan_utils.cpp:367`
**Severity:** Fatal

The first search loop over `queueFamilies` declares `int i = 0` but never increments `i` inside the body. The index is always 0, so `computeFamily` and `transferFamily` are always set to 0 regardless of which family actually matched. On hardware where the dedicated compute or transfer family is not at index 0 the wrong queue family is silently selected, breaking dispatch or transfers entirely.

The second loop in the same function correctly uses `i++`.

### Fix

Replace the hand-rolled loop with an indexed range loop that increments `i`:

```cpp
for (int i = 0; i < (int)queueFamilies.size(); i++) { ... }
```

---

## BUG-11 — VMA allocator is a file-scope global, never destroyed [FIXED]

**File:** `src/Compute/Vulkan/vulkan_utils.cpp:16,34`
**Severity:** High

`vma_allocator` is a single file-scope `VmaAllocator` global. `Create_VMA_Allocator` is called from every `ComputeContext::createLogicalDevice`, so creating a second context overwrites the allocator handle, leaking the first context's allocator and making any surviving buffer from the first context point at a stale allocator. `vmaDestroyAllocator` is never called anywhere, so the allocator leaks on shutdown. Multi-context use is fundamentally broken by this design.

### Fix

Move the allocator into `ComputeContext` as a member. Call `vmaDestroyAllocator` in `ComputeContext::Dispose()` before `vkDestroyDevice`.

---

## BUG-12 — `ComputeContext::Dispose` missing `vkDeviceWaitIdle`, fence never destroyed [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:561`
**Severity:** High

`Dispose()` destroys command pools and disposes programs/buffers without first calling `vkDeviceWaitIdle`, risking destruction of resources still in use by the GPU. The `mWaitFence` created in `createLogicalDevice` is never destroyed with `vkDestroyFence`, leaking the Vulkan object.

### Fix

Add `vkDeviceWaitIdle(mDevice)` at the start of `Dispose()`. Add `vkDestroyFence(mDevice, mWaitFence, nullptr)` before the device is destroyed.

---

## BUG-13 — Buffers created with `VK_SHARING_MODE_CONCURRENT` over uninstantiated queue families [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:1096,1115`
**Severity:** High

All buffers are created with `VK_SHARING_MODE_CONCURRENT` and `mAllQueueFamilies`, which includes every capable family the physical device advertises — not just the families the device was actually created with. Specifying families that have no instantiated queues can trip validation and disables device-local tiling optimizations. When compute and transfer resolve to the same family, `CONCURRENT` is unnecessary overhead.

### Fix

Use `VK_SHARING_MODE_EXCLUSIVE` when compute and transfer map to the same family. When they differ, pass only the two actually-created families.

---

## BUG-14 — Single shared `mComputeCmdBuffer` re-recorded without synchronization; `SIMULTANEOUS_USE` incorrect [FIXED]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:768,829`
**Severity:** High

`mComputeCmdBuffer` is a single command buffer shared by every kernel. `Execute` and `ExecuteBatch` call `vkBeginCommandBuffer` on it with `VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT`. If any prior submission is still in flight when `vkBeginCommandBuffer` is called the behaviour is undefined. `SIMULTANEOUS_USE` is also semantically wrong since the code immediately waits idle — it incurs a performance penalty while providing no benefit.

### Fix

Drop `SIMULTANEOUS_USE_BIT`. Ensure the shared fence is waited before re-recording, or allocate per-submission command buffers.

---

## BUG-15 — Single `mWaitFence` shared across compute dispatches and all buffer transfers [OPEN]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:745` and `vulkan_utils.cpp:829`
**Severity:** High

The same `VkFence` (`mWaitFence`) is used by `ComputeKernel::Execute`, `ComputeKernel::ExecuteBatch`, and every `endSingleTimeCommands` call (which covers `SetData`, `GetData`, and `CopyTo`). `vkResetFences` on a fence that is still associated with an outstanding submission is undefined behaviour. Any interleaving of a transfer and a dispatch, or two concurrent buffer operations, can corrupt the wait state.

### Fix

Use separate fences for compute dispatches and buffer transfers, or serialize all submissions through a single queue with a per-submission fence allocated from a pool.

---

## BUG-16 — Dispatch group count divided by workgroup size twice [FIXED]

**File:** `src/SLC_Program.cpp:264` and `src/Compute/Vulkan/ComputeEngine_VK.cpp:786`
**Severity:** High

`ProgramController::Execute` divides the element count by `WORKGROUP_SIZE_X` (64) before passing it to the kernel. `ComputeKernel::Execute` then divides again by `mWorkGroupSize.x` (default 16). The effective dispatch is `ceil(N / 64 / 16)` groups, covering only `ceil(N/1024)` elements. Any pool larger than 1 element will have most elements silently unprocessed.

### Fix

Divide by the workgroup size exactly once, at the point of dispatch, using the value that matches the shader's actual `local_size_x`.

---

## BUG-17 — Workgroup size in engine (16) does not match shader `local_size_x` (64) [OPEN]

**File:** `include/Compute/Vulkan/ComputeEngine_VK.h:14` vs `shaders/complex.comp:8`
**Severity:** High

`DEFAULT_WORK_GROUP_SIZE` is 16 but `complex.comp` and `utilities.comp` declare `local_size_x = 64`. Nothing sets the kernel's `mWorkGroupSize` to 64 for these programs. Combined with BUG-16, the actual dispatch geometry is wrong by a factor of 64.

### Fix

Set the kernel workgroup size to `(64, 1, 1)` to match the shaders, or query it from the SPIR-V via `SPV_KHR_workgroup_memory_explicit_layout` / reflection.

---

## BUG-18 — Transfer command buffer re-begun with `ONE_TIME_SUBMIT` without ensuring prior use completed [OPEN]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:1213` and `vulkan_utils.cpp:802`
**Severity:** Medium

`GetData` calls `beginSingleTimeCommands` on the shared `mTransferCmdBuffer` with `VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT`. This is a long-lived reusable buffer, not a throwaway. If a prior transfer using the same buffer has not completed before the next `vkBeginCommandBuffer`, the implicit reset races with the pending submission. Correctness currently relies on the shared `mWaitFence` (BUG-15) happening to serialize all transfers.

### Fix

Allocate a transient command buffer per transfer, freeing it after the fence wait, or explicitly verify completion before re-recording.

---

## BUG-19 — No host-read memory barrier before CPU readback in `GetData` [OPEN]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:1219`
**Severity:** Medium

After copying from the device buffer to the staging buffer, there is no barrier with `dstAccessMask = VK_ACCESS_HOST_READ_BIT` before `vmaMapMemory` + `memcpy`. Correctness currently depends on `HOST_COHERENT` memory being selected. If VMA selects non-coherent memory, stale cached data can be read without a `vkInvalidateMappedMemoryRanges` call.

### Fix

Add an explicit `vmaInvalidateAllocation` call before reading, or add a `VK_PIPELINE_STAGE_HOST_BIT` / `VK_ACCESS_HOST_READ_BIT` barrier after the copy.

---

## BUG-20 — `createShaderModule` returns uninitialized handle on failure; `Set_Binary` always reports success [OPEN]

**File:** `src/Compute/Vulkan/vulkan_utils.cpp:835` and `ComputeEngine_VK.cpp:610`
**Severity:** Medium

`createShaderModule` declares a local `VkShaderModule module` and only assigns it on success. On failure it logs and falls through, returning the uninitialized handle. `Set_Binary` and `Set_Binary_File` both return `0` unconditionally and set `mInitialized = true`, so a failed shader load is indistinguishable from success and the garbage module handle flows into pipeline creation.

### Fix

Return `VK_NULL_HANDLE` on failure from `createShaderModule`. Propagate a non-zero error code from `Set_Binary*` and prevent pipeline creation when `mInitialized` is false.

---

## BUG-21 — `VkResult` return values widely ignored [OPEN]

**File:** `vulkan_utils.cpp:34,792,808,822,829` and `ComputeEngine_VK.cpp:315`
**Severity:** Medium

`vmaCreateAllocator`, `vkAllocateCommandBuffers`, `vkBeginCommandBuffer`, `vkEndCommandBuffer`, and `vkQueueSubmit` return values are unchecked in several places. `createLogicalDevice`'s return is captured but device creation failure still proceeds to `getQueueInstances` and `createCommandPools`, which will dereference an invalid device handle.

### Fix

Check all `VkResult` returns. Abort context construction if `createLogicalDevice` fails.

---

## BUG-22 — Half-constructed `ComputeContext` returned and used after device-not-found [OPEN]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:298`
**Severity:** High

When no suitable device is found the constructor prints a message and returns early, leaving `mPhysicalDevice` and all Vulkan handles default-initialized. The object has already been registered in `mContexts` and is returned to the caller. Any subsequent use dereferences null/garbage handles, and the eventual `Dispose()` calls `vkDestroyCommandPool`/`vkDestroyDevice` on them.

### Fix

Signal failure to the caller (return `nullptr` or throw). Do not register or return a half-initialized context.

---

## BUG-23 — Pool stored under wrong key in `m_pools`; dynamic pools never erased [OPEN]

**File:** `src/SLC_Program.cpp:47`
**Severity:** High

`pool_num` is incremented twice per pool creation: once to generate the pool's own id and once when storing it in the map. The pool is stored under key `N+1` but `DisposePool` looks it up by `pool->PoolID()` which is `N`. The erase always misses, so dynamic pools are never removed from `m_pools` — the map grows indefinitely and holds stale `shared_ptr` references.

```cpp
unsigned int pool_id = pool_num++;          // pool id = N
...
m_pools[pool_num++] = inst;                 // stored under N+1
```

### Fix

```cpp
unsigned int pool_id = pool_num++;
m_pools[pool_id] = inst;                    // single increment, consistent key
```

---

## BUG-24 — Tangled buffer ownership between pool and context causes double-dispose [OPEN]

**File:** `src/SLC_ComputePool_private.cpp:360` and `src/Compute/Vulkan/ComputeEngine_VK.cpp:576`
**Severity:** High

`ComputeContext::mBuffers` owns (but never `delete`s) every `ComputeBuffer*`. `ComputePool_private` also holds `IComputeBuffer` wrappers over the same underlying `ComputeBuffer` objects. On shutdown, `ComputePool_private::Dispose` and `ComputeContext::Dispose` both call `Dispose()` on the same underlying buffers. `ComputeBuffer::Dispose` guards against double VK destroy via `mDestroyed`, but the `ComputeBuffer*` objects in `mBuffers` are never `delete`d, leaking every C++ buffer object.

### Fix

Establish single ownership. `ComputeContext` should own and `delete` its `ComputeBuffer*` entries. Use `std::unique_ptr` or at minimum `delete buffer` before `mBuffers.clear()`.

---

## BUG-25 — `mBuffers` elements are never `delete`d on context dispose [OPEN]

**File:** `src/Compute/Vulkan/ComputeEngine_VK.cpp:400,576`
**Severity:** Medium

`CreateBuffer` pushes `new ComputeBuffer(...)` into `mBuffers`. `Dispose` calls `buffer->Dispose()` on each then calls `mBuffers.clear()`. The raw `ComputeBuffer` heap allocation is never `delete`d — the C++ object leaks even though the Vulkan resources inside it are freed correctly.

### Fix

`delete buffer;` before `mBuffers.clear()`, or store `std::unique_ptr<ComputeBuffer>`.

---

## BUG-26 — Programs disposed twice; inner `ComputeProgram*` objects never deleted [OPEN]

**File:** `src/Compute/Vulkan/ComputeController_VK.cpp:109` and `ComputeEngine_VK.cpp:572`
**Severity:** Medium

`ComputeController_VK::Dispose` deletes every `ComputeProgram_VK*`, which calls through to the inner `ComputeProgram::Dispose`. Then it calls `m_context->Dispose()`, which iterates `programs` and calls `prog->Dispose()` on the same objects again. `ComputeProgram::Dispose` is `mDestroyed`-guarded so double-dispose is safe, but the `ComputeProgram*` objects in `ComputeContext::programs` are never `delete`d — only `programs.clear()` is called.

### Fix

Context should `delete` its `ComputeProgram*` entries before clearing. Use `std::unique_ptr`.

---

## BUG-27 — No bounds check on static pool count against available binding slots [OPEN]

**File:** `src/SLC_Program.cpp:54`
**Severity:** Medium

`m_static_bind_idx` grows unbounded as static pools are created, but only `NUM_POOL_BIND_BUFFERS` (2) binding slots exist in the shader. Creating more than 2 static pools silently drops the extras — they are initialized but never bound, and the shader's `write_res_float_static`/`Get_Float_static` switch only handles pool ids 0 and 1.

### Fix

```cpp
SL_ASSERT(m_static_bind_idx < NUM_POOL_BIND_BUFFERS, "Exceeded maximum static pool count.");
```

---

## BUG-28 — `PoolType` enum values undocumentedly coupled to shader `POOL_TYPE_*` defines [OPEN]

**File:** `src/SLC_ComputePool_private.cpp:288` and `shaders/libSLC/standard_buffers.inc:103`
**Severity:** Low

`Get_Control_Vec` constructs `glm::uvec4(m_type, 0, 0, 0)` relying on `PoolType::Dynamic == 1` and `PoolType::Static == 2` matching the shader defines `POOL_TYPE_DYNAMIC 1` / `POOL_TYPE_STATIC 2`. If the enum is ever reordered or the shader defines change independently, the pool type selector silently falls to the shader's `default` case and writes 255 into every result element.

### Fix

Add a `static_assert` or compile-time check that the enum values match the shader constants, and add a comment documenting the coupling.

---

## BUG-31 — Three-layer raw pointer ownership with no clear owner [OPEN]

**File:** `src/Compute/Vulkan/ComputeController_VK.cpp:81`
**Severity:** Low

`ComputeController_VK` holds a raw `ComputeContext*`, which in turn holds raw `ComputeProgram*` and `ComputeBuffer*` objects. There is no documented ownership contract — it is unclear which destructor is responsible for which objects, making future refactoring error-prone and making it difficult to audit for leaks without reading all three files. This is the root cause behind BUG-25 and BUG-26.

### Fix

Establish and document ownership chains. Prefer `std::unique_ptr` at ownership boundaries.

---

## BUG-29 — `write_complex` macro uses unparenthesized `idx` [OPEN]

**File:** `shaders/libSLC/standard_buffers.inc:225`
**Severity:** Medium

```glsl
write(buf, idx * COMPLEX_TYPE_STRIDE + 0, GSL_REAL(v));
```

`idx` is unparenthesized. The sibling macros `write_complex_offset` (line 234) and `read_complex` (line 277) correctly use `(idx)`. Any caller passing a compound expression (e.g. `base + offset`) expands to `base + offset * 2` rather than `(base + offset) * 2`, silently writing to the wrong buffer slot — the same class of bug as BUG-9.

### Fix

```glsl
write(buf, (idx) * COMPLEX_TYPE_STRIDE + 0, GSL_REAL(v));
write(buf, (idx) * COMPLEX_TYPE_STRIDE + 1, GSL_IMAG(v));
```

---

## BUG-30 — `VECTOR_ANGLE` defined as object-like macro (space before `(`) [OPEN]

**File:** `shaders/libUSL/compat.inc:25`
**Severity:** Low

```glsl
#define VECTOR_ANGLE (out_val, from, to) float num = ...
```

The space between `VECTOR_ANGLE` and `(` makes this an object-like macro that expands to the token sequence `(out_val, from, to) float num = ...`. Any call site using `VECTOR_ANGLE(a, b, c)` will not behave as a function call. Currently unused, but broken.

### Fix

Remove the space: `#define VECTOR_ANGLE(out_val, from, to) ...`

---

## BUG-32 — `57.29578f` float suffix in `compat.inc` breaks non-GLSL backends [OPEN]

**File:** `shaders/libUSL/compat.inc:33,43`
**Severity:** Low

The `f` suffix on floating-point literals (e.g. `57.29578f`) is GLSL-specific syntax. The `libUSL` layer advertises support for OpenCL and DirectX/Unity3D via its `USL_OPENCL` / `USL_DIRECTX_UNITY3D` guards, but OpenCL C does not accept `f`-suffixed literals in this context (it uses `(float)57.29578`). These literals will cause compile errors if the OpenCL or DirectX/Unity3D backends are ever revived.

### Fix

Remove the `f` suffix or use an explicit cast: `(float)57.29578`.
