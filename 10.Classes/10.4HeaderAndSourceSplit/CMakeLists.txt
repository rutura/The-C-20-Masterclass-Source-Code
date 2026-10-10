cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable. Every .cpp is compiled on its own and the linker joins
# them (7.12). The header is listed only so that IDEs show it in the project.
add_executable(rooster main.cpp sensor.cpp sensor.h)
