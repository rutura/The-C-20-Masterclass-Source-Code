cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp matrix.h)

# This is what makes `ctest` work. A test is just a command: CTest runs it and
# treats exit code 0 as pass and anything else as fail. That is why main
# returns 1 when a check failed.
enable_testing()
add_test(NAME matrix_tests COMMAND rooster)
