cmake_minimum_required(VERSION 3.30)       # `import std;` support arrived in CMake 3.30, as an experiment

# With MSVC, CMake's support for `import std;` is EXPERIMENTAL in 3.30 and 3.31.
# It is switched on by setting this variable to a fixed identifier, BEFORE
# project(). (The identifier changes in later CMake versions; see the CMake
# documentation.) GCC and Clang do not use this switch: see import-std.cmake.
if(CMAKE_HOST_WIN32)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
endif()

# Project name
project(rooster)

# Set C++ standard to C++23 (import std is a C++23 feature)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(import-std.cmake)

# Create executable
add_executable(rooster main.cpp)

# Let this target say `import std;`. (build-gcc.sh and build-clang.sh show the
# same thing done by hand, without CMake.)
target_use_import_std(rooster)
