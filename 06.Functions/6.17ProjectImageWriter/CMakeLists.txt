cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# No external dependency at all - just our own two source files.
add_executable(rooster
    main.cpp
    image.cpp
    image.h
)
