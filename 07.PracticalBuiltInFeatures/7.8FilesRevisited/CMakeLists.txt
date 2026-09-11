cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Two programs in this lecture, built as their own executables.
# Run rooster_write first (it creates accounts.txt), then rooster_read.
add_executable(rooster_write write.cpp)
add_executable(rooster_read read.cpp)
