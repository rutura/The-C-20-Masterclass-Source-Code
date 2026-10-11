cmake_minimum_required(VERSION 3.28)       # CMake understands C++ modules from 3.28 on

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable. stats.cpp is the implementation unit of the module.
add_executable(rooster main.cpp stats.cpp)

# One module, four files: the primary interface and three partitions. Every file
# that starts with `export module` or `module name:partition` goes in the file set.
target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        forecast.cppm
        model.cppm
        stats_interface.cppm
        detail.cppm
)
