# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

SLCompute is a C++ static library (v0.0.1, MIT) that ports the GNU Scientific Library (GSL) to run on the GPU via compute shaders. It is packaged with Conan 2.x and built with CMake.

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

### 2. GPGSL / SLCompute — GSL API layer (`include/GPGSL_*.h`, `src/GPGSL_*.cpp`)

`ProgramController` (base class) owns the `IComputeController` and manages loading embedded SPIR-V programs at startup. Concrete subclasses expose GSL-style math functions by binding input/output buffers and dispatching to the appropriate shader program.

### 3. Shader library (`shaders/`)

- **`libUSL/`** — Universal Shader Library: cross-platform buffer and type macros (`Buffers.inc`, `Types.inc`, `compat.inc`). A `#define USL_VULKAN 1` / `USL_OPENCL 1` / `USL_DIRECTX_UNITY3D 1` guard selects the correct SSBO/buffer syntax at compile time.
- **`libGSL/`** — GSL math implementations as GLSL `.inc` files. `complex_imp.inc` is the main complex-number implementation.
- **`.comp` files** — Entry points that `#include` from both libs and define `main()` with `local_size_x/y/z`.

### Shader function dispatch pattern

A single SPIR-V binary implements multiple GSL functions. Two fixed-binding SSBOs drive dispatch:
- **Binding 0** (`settings`): `uvec4[0].x` holds the function ID (e.g. `FUNC_ID_COMPLEX_ADD = 1`)
- **Binding 1** (`control`): one `uvec4` per work item, encoding result/operand indices into the data buffers
- **Bindings 2–5**: the actual float/complex data buffers

`Execute(uint x)` in the shader reads `func_id` and switches to the appropriate `*_main(x)` function.

## Key Files

- `include/slcompute.h` — public API entry point (use `SLCOMPUTE_EXPORT` for all exported symbols)
- `include/Compute/ComputeInterface.h` — factory for getting a compute controller
- `include/Compute/ComputeEngine.h` — Vulkan instance/context management (all statics)
- `include/GPGSL_Program.h` — base class for GSL program controllers
- `include/Resources/binary_resources.hpp` — **generated**, do not edit directly
- `Embed_Shaders.py` — regenerates `binary_resources.hpp` from compiled `.spv` files
- `conanfile.py` — Conan recipe; `exports_sources` only includes `CMakeLists.txt`, `src/*`, `include/*` — shaders are embedded before packaging
