cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The same two files the notes archive by hand, as a static library.
add_library(station STATIC stats.cpp stats.h report.cpp report.h)

# Create executable
add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE station)
