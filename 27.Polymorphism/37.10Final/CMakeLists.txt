cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster
    main.cpp
    animal.cpp animal.h
    bird.cpp bird.h
    bulldog.cpp bulldog.h
    cat.cpp cat.h
    crow.cpp crow.h
    dog.cpp dog.h
    feline.cpp feline.h
    pigeon.cpp pigeon.h
    wildcat.cpp wildcat.h
)
