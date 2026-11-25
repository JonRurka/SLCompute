from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class slcomputeRecipe(ConanFile):
    name = "slcompute"
    version = "0.0.1"
    package_type = "library"

    # Optional metadata
    license = "MIT"
    author = "Jonathan Rurka, jon@rurka.net"
    # url = "<Package recipe repository url here, for issues about the package>"
    description = "Full port of GNU Science Library to compute shader languages."
    #topics = ("<Put some tag here>", "<here>", "<and here>")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "shaders/**", "Embed_Shaders.py"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def requirements(self):
        self.requires("vulkan-headers/1.3.239.0")
        if self.settings.os != "Android":
            # Android bundles Vulkan in the NDK; all other platforms need the loader
            self.requires("vulkan-loader/1.3.239.0")
        self.requires("vulkan-memory-allocator/3.0.1")
        self.requires("glfw/3.3.8")
        self.requires("glm/1.0.1")

    def layout(self):
        cmake_layout(self)
    
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["slcompute"]

