cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster
    main.cpp
    image.cpp
    image.h
    stb_impl.cpp
)

# Point at the fetched sources so #include "stb_image_write.h" resolves.
# SYSTEM: do not warn about code inside stb.
target_include_directories(rooster SYSTEM PRIVATE ${stb_SOURCE_DIR})