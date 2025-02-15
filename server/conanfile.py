from conan import ConanFile
from conan.tools.cmake import (
    CMake,
    CMakeToolchain,
    cmake_layout,
)

class GridWarriors(ConanFile):
    name = "gridwarriors"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"
    options = {
        "shared": [True, False]
    }
    default_options = {
        "shared": False,
    }
    requires = [
        "poco/1.13.3",
        "gtest/1.15.0",
        "log.c/cci.20200620",
    ]

    def generate(self):
        tc = CMakeToolchain(self, generator="Ninja")
        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        tc.generate()

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

