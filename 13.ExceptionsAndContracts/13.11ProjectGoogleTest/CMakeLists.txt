cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg.json lists "gtest", so the toolchain file (set in CMakePresets.json)
# has already built it by the time this line runs.
find_package(GTest CONFIG REQUIRED)

# Create executable. gtest_main supplies main(), so the file has only tests.
add_executable(rooster matrix_tests.cpp matrix.h)
target_link_libraries(rooster PRIVATE GTest::gtest_main)

# Registers every TEST with CTest, one CTest entry per test, so a failure
# points at a single test instead of the whole program.
enable_testing()
include(GoogleTest)
gtest_discover_tests(rooster)
