cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)

# This lecture has three self-contained demos, one per binary:
#   main2.cpp - seeding the engine (fixed seed vs. random_device)
#   main3.cpp - a helper function, a scoped enum, switch with initializer
add_executable(rooster2 main2.cpp)
add_executable(rooster3 main3.cpp)
