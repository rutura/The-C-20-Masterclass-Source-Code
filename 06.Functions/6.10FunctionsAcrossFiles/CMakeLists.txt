cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Every .cpp that contributes code to the program is listed here. CMake
# compiles each to its own object file, then links them into one
# executable. The .h files are named too so IDEs show them in the
# project tree - they are not compiled.
add_executable(rooster
    main.cpp
    geometry.cpp
    money.cpp
    geometry.h
    money.h
)
