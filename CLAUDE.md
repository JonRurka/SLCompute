# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

SLCompute is a C++ static library (v0.0.1, MIT) that ports the GNU Scientific Library (SLC) to run on the GPU via compute shaders. It is packaged with Conan 2.x and built with CMake.

**Git remote:** `https://github.com/JonRurka/SLCompute.git`

## Build System

The project uses **Conan 2** as the package manager with CMake as the build system. There are two build directories:
- `build/` — Conan-managed builds (Debug and Release profiles)
- `cmake-build-debug/` — CLion-managed build (Ninja)

### Build with Conan (preferred)

```bash
# Install dependencies and generate CMake presets
conan install . --output-folder=build/Debug --build=missing -s build_type=Debug
conan install . --output-folder=build/Release --build=missing -s build_type=Release

# Build
cmake --preset conan-debug && cmake --build --preset conan-debug
cmake --preset conan-release && cmake --build --preset conan-release
```

### Test (Conan package validation)

```bash
conan create . --build=missing
```

This builds, packages, then compiles and runs `test_package/src/example.cpp` against the library. There is no separate unit test suite.

## Shader Pipeline

Shaders must be compiled and re-embedded whenever `.comp` or `.inc` files change:

1. **Compile GLSL → SPIR-V** (requires Vulkan SDK `glslc`):
   ```bash
   cd shaders
   glslc complex.comp -o bin/complex.spv
   glslc utilities.comp -o bin/utilities.spv
   ```

2. **Embed SPIR-V into C++ header**:
   ```bash
   python Embed_Shaders.py
   ```
   This reads all `shaders/bin/*.spv` files and generates `include/Resources/binary_resources.hpp`, which declares each binary as a `const std::vector<uint8_t>` inside `SLCompute::Resources::Shader_Binaries`.

The generated header is `#include`d at build time — there is no runtime file loading.

## Architecture

The library has three layers:

### 1. DynamicCompute — Compute API abstraction (`include/Compute/`, `src/Compute/`)

A platform-agnostic compute backend. Public interface classes (`IComputeController`, `IComputeProgram`, `IComputeBuffer`) use the **pImpl pattern**: each wraps a `*_private` pointer to the real implementation, hiding Vulkan types from callers. The only current backend is Vulkan (`*_VK` files). `ComputeInterface` is the factory entry point that selects the backend.

The Vulkan object hierarchy: `ComputeEngine` (singleton, manages `VkInstance`) → `ComputeContext` (per-device, owns queues/command pools) → `ComputeProgram` (wraps a `VkShaderModule`) → `ComputeKernel` (wraps a `VkPipeline` + descriptor sets for one entry point).

### 2. SLC / SLCompute — SLC API layer (`include/SLC_*.h`, `src/SLC_*.cpp`)

`ProgramController` (base class) owns the `IComputeController` and manages loading embedded SPIR-V programs at startup. Concrete subclasses expose SLC-style math functions by binding input/output buffers and dispatching to the appropriate shader program.

### 3. Shader library (`shaders/`)

- **`libUSL/`** — Universal Shader Library: cross-platform buffer and type macros (`Buffers.inc`, `Types.inc`, `compat.inc`). A `#define USL_VULKAN 1` / `USL_OPENCL 1` / `USL_DIRECTX_UNITY3D 1` guard selects the correct SSBO/buffer syntax at compile time.
- **`libSLC/`** — SLC math implementations as GLSL `.inc` files. `complex_imp.inc` is the main complex-number implementation.
- **`.comp` files** — Entry points that `#include` from both libs and define `main()` with `local_size_x/y/z`.

### Shader function dispatch pattern

A single SPIR-V binary implements multiple SLC functions. Fixed-binding SSBOs drive dispatch:
- **Binding 0** (`settings`): `uvec4[0].x` = function ID (e.g. `FUNC_ID_COMPLEX_ADD = 1`), `uvec4[0].y` = element count
- **Binding 1** (`control`): one `uvec4` per parameter slot:
  - `.x` = pool type (1=Dynamic, 2=Static)
  - `.y` = static pool buffer index (0→binding 7, 1→binding 8)
  - `.z` = raw float offset within the pool buffer
  - `.w` = unused
- **Bindings 2–5**: result buffer (binding 2) and dynamic parameter copy buffers (bindings 3–6)
- **Bindings 7–8**: static pool buffers (`POOL_BUFFER_1`, `POOL_BUFFER_2`), bound from C++ via `AddBuffer(name, 7+i, m_static_pools[i]->GetStaticComputeBuffer())`

`Execute(uint x)` in the shader reads `func_id` from settings and switches to the appropriate `*_main(x)` function.

### Shader buffer accessor pitfall

`set_buffer_scalar` / `get_buffer_scalar` in `shaders/libUSL/Buffers.inc` pack scalars into `fvec4[]` as `buf[(N)/4][(N)%4]`. The parentheses around `N` are critical — without them, C/GLSL operator precedence applies `/4` and `%4` only to the last additive term (e.g. `offset + idx*stride + 0/4` evaluates as `offset + idx*stride + 0`), leaving the same raw value for both the array index and the vector component. This writes silently out of bounds on the GPU. Always ensure any index expression passed to these macros is fully parenthesized.

## Key Files

- `include/slcompute.h` — public API entry point (use `SLCOMPUTE_EXPORT` for all exported symbols)
- `include/Compute/ComputeInterface.h` — factory for getting a compute controller
- `include/Compute/ComputeEngine.h` — Vulkan instance/context management (all statics)
- `include/SLC_Program.h` — base class for SLC program controllers
- `include/Resources/binary_resources.hpp` — **generated**, do not edit directly
- `Embed_Shaders.py` — regenerates `binary_resources.hpp` from compiled `.spv` files
- `conanfile.py` — Conan recipe; `exports_sources` only includes `CMakeLists.txt`, `src/*`, `include/*` — shaders are embedded before packaging
- `shaders/libUSL/Buffers.inc` — buffer declaration macros and scalar accessors (`set_buffer_scalar`, `get_buffer_scalar`); Vulkan backend packs floats into `fvec4[]`
- `shaders/libSLC/standard_buffers.inc` — declares all SSBO bindings (settings=0, control=1, result=2, params=3–6, pool=7–8)
- `shaders/libSLC/complex_imp.inc` — complex math implementations; defines `write_res_complex`, `Get_Complex`, and static/dynamic dispatch helpers
