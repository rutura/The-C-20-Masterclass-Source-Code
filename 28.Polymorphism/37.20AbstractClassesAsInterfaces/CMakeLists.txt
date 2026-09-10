cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster
    main.cpp
    stream_insertable.cpp stream_insertable.h
    animal.cpp animal.h
    feline.cpp feline.h
    cat.cpp cat.h
    dog.cpp dog.h
    bird.cpp bird.h
    crow.cpp crow.h
    pigeon.cpp pigeon.h
)
