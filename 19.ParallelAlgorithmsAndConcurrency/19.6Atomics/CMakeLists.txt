cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

# Threads need the platform's thread library. On Windows this changes nothing;
# on older Linux systems it adds -pthread (glibc 2.34 and later do not need it).
find_package(Threads REQUIRED)
target_link_libraries(rooster PRIVATE Threads::Threads)
