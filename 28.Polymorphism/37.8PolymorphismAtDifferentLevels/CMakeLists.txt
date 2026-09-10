cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster
    main.cpp
    animal.h animal.cpp
    feline.h feline.cpp
    dog.h dog.cpp
    cat.h cat.cpp
    bird.h bird.cpp
    crow.h crow.cpp
    pigeon.h pigeon.cpp
)
