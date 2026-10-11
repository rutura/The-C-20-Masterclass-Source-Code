cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The tour of the generic Matrix
add_executable(rooster main.cpp matrix.h)

# The tests: part of them are static_asserts, so building this target IS the
# compile-time test. Running it executes the run-time tests.
add_executable(rooster_tests tests.cpp matrix.h)

# `ctest` runs the tests (13.10).
enable_testing()
add_test(NAME matrix_template_tests COMMAND rooster_tests)
