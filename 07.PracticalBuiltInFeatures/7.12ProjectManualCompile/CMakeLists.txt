cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The multi-file program: the same three .cpp files the notes compile by hand.
add_executable(rooster main.cpp stats.cpp stats.h report.cpp report.h)

# The single-file program from the first half of the project.
add_executable(rooster_single single.cpp)
