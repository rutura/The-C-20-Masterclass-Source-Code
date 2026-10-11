cmake_minimum_required(VERSION 3.28)       # CMake understands C++ modules from 3.28 on

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable. stations.cpp is an ORDINARY source file: a module
# implementation unit is compiled like any other .cpp.
add_executable(rooster main.cpp stations.cpp)

# Only the interface file goes in the CXX_MODULES file set (17.3).
target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        stations.cppm
)
