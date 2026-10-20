cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster1_ratios main1_ratios.cpp)
add_executable(rooster2_durations main2_durations.cpp)
add_executable(rooster3_clocks_and_dates main3_clocks_and_dates.cpp)

