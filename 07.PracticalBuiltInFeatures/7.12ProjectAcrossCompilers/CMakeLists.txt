cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This lecture is about what a LIBRARY actually is on disk, so unlike every
# other lecture's single add_executable(rooster main.cpp), this one builds
# average.cpp as its own static library target first, then links rooster
# against it - the same two-step pipeline NOTES.md walks through by hand
# with the compiler and the archiver directly.
add_library(average STATIC average.cpp average.h)

add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE average)
