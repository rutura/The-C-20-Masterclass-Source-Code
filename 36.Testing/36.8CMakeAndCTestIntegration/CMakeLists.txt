cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)

# Create executable
add_executable(rooster main.cpp boxcontainer.h boxcontainer.cpp)
target_link_libraries(rooster PRIVATE Catch2::Catch2WithMain)

# enable_testing() turns on CTest for this project -- without it, ctest has
# nothing to run, even if the test executable itself works fine.
enable_testing()

# The manual way: register the whole executable as one CTest test. Running
# `ctest` would report a single pass/fail for the entire suite.
# add_test(NAME BoxContainerTests COMMAND rooster)

# The better way: Catch2 ships a CMake module that inspects the built
# executable and registers each individual TEST_CASE as its own CTest test.
# `ctest` then reports pass/fail per TEST_CASE, and `ctest -R "some name"`
# can re-run just one of them -- much more useful once a suite grows.
include(Catch)
catch_discover_tests(rooster)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
