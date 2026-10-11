cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The pipeline and its three jobs
add_executable(rooster main.cpp log_entry.h task.h scheduler.h)

# The tool that writes a log to analyze. Run it first.
add_executable(rooster_generate generate_log.cpp)
