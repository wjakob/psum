cmake_minimum_required(VERSION 3.15...3.27)
project(psum)

# Find Python
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)

# Force a release build
set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)

# Detect the installed nanobind package and import it into CMake
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

# Enable instruction set extensions
if (MSVC)
   add_compile_options(/arch:AVX2)
else()
  add_compile_options(-march=native)
endif()

# Build the extension (uses a different source file depending on the processor)
nanobind_add_module(psum NB_SHARED psum.cpp)

# Make function symbols visible in generated binary (easier to show dissassembly in class)
set_target_properties(psum PROPERTIES CXX_VISIBILITY_PRESET default)

