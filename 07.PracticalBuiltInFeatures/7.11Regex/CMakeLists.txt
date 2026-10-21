cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster1_matching main1_matching.cpp)
add_executable(rooster2_searching main2_searching.cpp)
add_executable(rooster3_walking_matches main3_walking_matches.cpp)
add_executable(rooster4_replacing main4_replacing.cpp)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
