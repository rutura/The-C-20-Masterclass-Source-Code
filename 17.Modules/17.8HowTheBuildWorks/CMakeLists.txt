cmake_minimum_required(VERSION 3.28)       # CMake understands C++ modules from 3.28 on

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

# Three modules that import each other in a chain: report -> readings -> units.
# The ORDER of this list does not matter. CMake scans each file to find which
# module it defines and which it imports, and works out the build order itself.
target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        report.cppm
        readings.cppm
        units.cppm
)
