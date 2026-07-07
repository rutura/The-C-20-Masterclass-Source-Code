cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp boxcontainer.h)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
