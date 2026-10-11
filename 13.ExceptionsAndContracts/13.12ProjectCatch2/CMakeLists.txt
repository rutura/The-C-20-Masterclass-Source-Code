cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg.json lists "catch2", so the toolchain file (set in CMakePresets.json)
# has already built it by the time this line runs.
find_package(Catch2 3 CONFIG REQUIRED)

# Create executable. Catch2WithMain supplies main(), so the file has only tests.
add_executable(rooster matrix_tests.cpp matrix.h)
target_link_libraries(rooster PRIVATE Catch2::Catch2WithMain)

# Registers every TEST_CASE with CTest, one CTest entry per test case.
enable_testing()
include(Catch)
catch_discover_tests(rooster)
