cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Timings of an unoptimized build are meaningless, so default to Release when
# no build type was chosen (Visual Studio and other multi-config setups ignore this).
# Note: with MSVC and Ninja, CMake picks Debug by itself on the first configure,
# so pass -DCMAKE_BUILD_TYPE=Release there.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

# The analyzer
add_executable(rooster main.cpp log_entry.h)

# The tool that writes a log to analyze. Run it first.
add_executable(rooster_generate generate_log.cpp)
