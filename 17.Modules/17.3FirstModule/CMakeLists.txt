cmake_minimum_required(VERSION 3.28)       # CMake understands C++ modules from 3.28 on

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

# A module interface file is not an ordinary source file: CMake must scan it to
# learn which module it defines, and compile it BEFORE the files that import it.
# Listing it in a FILE_SET of type CXX_MODULES tells CMake that.
target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        station.cppm
)
