cmake_minimum_required(VERSION 3.15)
project(slcompute CXX)

option(VULKAN_PLATFROM "Include Vulkan platform for compute." ON)
add_compile_definitions(VULKAN_COMPUTE_PLATFROM)

include_directories(include)
include_directories(include/Compute)
include_directories(include/Compute/Vulkan)
#include_directories(include/Compute/Vulkan/nvpro_core/nvp)
#include_directories(include/Compute/Vulkan/nvpro_core)

set(slc_headers
        # science library
        include/GPGSL_Structures.h
        include/GPGSL_func_ids.h
        include/GPGSL_Program.h
        include/GPGSL_ComputePool.h
        include/GPGSL_ComputePool_private.h
        include/complex.h

        # Resources
        include/Resources/binary_resources.hpp

        # math
        include/glm_inc.h

        # misc
        include/bimap.h
        include/Logger.h
)
LIST(APPEND slc_headers
        # Compute interface
        include/Compute/ForwardDeclarations.h
        include/Compute/InterfaceIncludes_private.h
        include/Compute/PlatformStructures_private.h
        include/Compute/ComputeInterface_private.h
        include/Compute/IComputeController_private.h
        include/Compute/IComputeProgram_private.h
        include/Compute/IComputeBuffer_private.h
        include/Compute/std_includes.h
        include/Compute/dynamic_compute.h
        include/Compute/InterfaceIncludes.h
        include/Compute/PlatformStructures.h
        include/Compute/IComputeBuffer.h
        include/Compute/IComputeProgram.h
        include/Compute/IComputeController.h
        include/Compute/ComputeInterface.h
)
LIST(APPEND slc_headers
        # Compute engine
        #include/Compute/Vulkan/nvpro_core/nvgl/extensions_gl.hpp
        include/Compute/Vulkan/vk_mem_alloc.h
        include/Compute/Vulkan/vulkan_utils.h
        include/Compute/Vulkan/ComputeEngine_VK.h
        include/Compute/Vulkan/ComputeController_VK.h
        include/Compute/Vulkan/ComputeProgram_VK.h
        include/Compute/Vulkan/ComputeBuffer_VK.h
)



set(slc_sources
        # science library
        src/GPGSL_Program.cpp
        src/GPGSL_ComputePool.cpp
        src/GPGSL_ComputePool_private.cpp
        src/complex.cpp
        src/slcompute.cpp
        src/Logger.cpp
)
LIST(APPEND slc_sources
        # Compute interface
        src/Compute/PlatformStructures.cpp
        src/Compute/IComputeBuffer.cpp
        src/Compute/IComputeProgram.cpp
        src/Compute/IComputeController.cpp
        src/Compute/ComputeInterface_private.cpp
        src/Compute/ComputeInterface.cpp
)
LIST(APPEND slc_sources
        # Compute engine
        #include/nvpro_core/nvgl/extensions_gl.cpp
        src/Compute/Vulkan/vulkan_utils.cpp
        src/Compute/Vulkan/ComputeEngine_VK.cpp
        src/Compute/Vulkan/ComputeController_VK.cpp
        src/Compute/Vulkan/ComputeProgram_VK.cpp
        src/Compute/Vulkan/ComputeBuffer_VK.cpp
)











LIST(APPEND slc_headers_old
        # Compute library
        include/Compute/ForwardDeclarations.h
        include/Compute/vulkan_utils.h
        include/Compute/ComputeEngine.h
        include/Compute/ComputeController_VK.h
        include/Compute/ComputeProgram_VK.h
        include/Compute/ComputeBuffer_VK.h
        include/Compute/InterfaceIncludes_private.h
        include/Compute/PlatformStructures_private.h
        include/Compute/ComputeInterface_private.h
        include/Compute/IComputeController_private.h
        include/Compute/IComputeProgram_private.h
        include/Compute/IComputeBuffer_private.h
        include/Compute/std_includes.h
        include/Compute/dynamic_compute.h
        include/Compute/InterfaceIncludes.h
        include/Compute/PlatformStructures.h
        include/Compute/IComputeBuffer.h
        include/Compute/IComputeProgram.h
        include/Compute/IComputeController.h
        include/Compute/ComputeInterface.h
)
set(slc_sources_old
        src/slcompute.cpp

        # Compute library
        src/Compute/vulkan_utils.cpp
        src/Compute/ComputeEngine.cpp
        src/Compute/ComputeController_VK.cpp
        src/Compute/ComputeProgram_VK.cpp
        src/Compute/ComputeBuffer_VK.cpp
        src/Compute/PlatformStructures.cpp
        src/Compute/IComputeBuffer.cpp
        src/Compute/IComputeProgram.cpp
        src/Compute/IComputeController.cpp
        src/Compute/ComputeInterface.cpp

        # science library
        src/GPGSL_Program.cpp
        src/GPGSL_ComputePool.cpp
        src/GPGSL_ComputePool_private.cpp
        src/complex.cpp
        include/bimap.h
)


# Prevent stale system-path cache entries from winning over Conan-managed packages
foreach(_pkg VulkanHeaders VulkanLoader VulkanMemoryAllocator glm glfw3)
    unset(${_pkg}_DIR CACHE)
endforeach()

find_package(glm REQUIRED CONFIG)
find_package(VulkanHeaders REQUIRED CONFIG)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
find_package(VulkanLoader REQUIRED CONFIG)
find_package(glfw3 REQUIRED CONFIG)

find_program(GLSLC_EXECUTABLE
    NAMES glslc
    HINTS "$ENV{VULKAN_SDK}/bin" "$ENV{VULKAN_SDK}/Bin"
    REQUIRED
)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders")
set(BINARY_RESOURCES_HPP "${CMAKE_SOURCE_DIR}/include/Resources/binary_resources.hpp")

file(MAKE_DIRECTORY "${SHADER_DIR}/bin")
file(GLOB_RECURSE SHADER_INCLUDES "${SHADER_DIR}/*.inc")

add_custom_command(
    OUTPUT
        "${SHADER_DIR}/bin/complex.spv"
        "${SHADER_DIR}/bin/utilities.spv"
    COMMAND ${GLSLC_EXECUTABLE} "${SHADER_DIR}/complex.comp"   -o "${SHADER_DIR}/bin/complex.spv"
    COMMAND ${GLSLC_EXECUTABLE} "${SHADER_DIR}/utilities.comp" -o "${SHADER_DIR}/bin/utilities.spv"
    DEPENDS
        "${SHADER_DIR}/complex.comp"
        "${SHADER_DIR}/utilities.comp"
        ${SHADER_INCLUDES}
    COMMENT "Compiling GLSL shaders to SPIR-V"
    VERBATIM
)

add_custom_command(
    OUTPUT "${BINARY_RESOURCES_HPP}"
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_SOURCE_DIR}/Embed_Shaders.py"
    DEPENDS
        "${SHADER_DIR}/bin/complex.spv"
        "${SHADER_DIR}/bin/utilities.spv"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Embedding SPIR-V binaries into binary_resources.hpp"
    VERBATIM
)

add_library(slcompute ${slc_headers} ${slc_sources})
include_directories(slcompute "include")
target_include_directories(slcompute PUBLIC include)

target_link_libraries(slcompute
    Vulkan::Loader
    glfw
    glm::glm
    vulkan-headers::vulkan-headers
    GPUOpen::VulkanMemoryAllocator
)

install(TARGETS slcompute)

install(FILES
    include/slcompute.h
    include/GPGSL_Structures.h
    include/GPGSL_func_ids.h
    include/GPGSL_Program.h
    include/GPGSL_ComputePool.h
    include/GPGSL_ComputePool_private.h
    include/glm_inc.h
    include/bimap.h
    include/complex.h
    DESTINATION include
)

install(FILES
    include/Compute/std_includes.h
    include/Compute/ForwardDeclarations.h
    include/Compute/dynamic_compute.h
    include/Compute/InterfaceIncludes.h
    include/Compute/PlatformStructures.h
    include/Compute/PlatformStructures_private.h
    include/Compute/IComputeBuffer.h
    include/Compute/IComputeProgram.h
    include/Compute/IComputeController.h
    include/Compute/ComputeInterface.h
    DESTINATION include/Compute
)
