# CS328 Lecture 5: Processor Architecture & Efficiency

## Benchmark problem

The ``benchmark.ipynb`` file in this repository compares 6 different ways of
computing the sum of positive elements in an array. Before you can execute the
cells in this notebook, you must install:

1. **CMake**

   - On Linux, install it with the package manager of your distribution (apt,
     yum, ..). On Ubuntu/Debian, run \"sudo apt install cmake\".

   - On macOS, install it through Homebrew (https://brew.sh)

   - On Windows, install it via the official installer (http://cmake.org)

2. **A C++ compiler** (XCode on macOS, GCC/Clang on Linux, Visual Studio on Windows)

3. **nanobind**: To install it, run \"python -m pip install nanobind\" on the command line

Following this, run ``cmake`` or ``cmake-gui`` to generate a build file that you can compile with
your C++ compiler.

General information on compiling C++ projects via CMake on various platforms is
available [here](https://preshing.com/20170511/how-to-build-a-cmake-based-project/).
