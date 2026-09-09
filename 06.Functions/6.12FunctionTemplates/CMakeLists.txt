cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# in_range.h is header-only: there is no in_range.cpp, because a template
# body must be visible wherever it is called (see the header's comment).
# It is listed here only so IDEs show it in the project tree.
add_executable(rooster
    main.cpp
    in_range.h
)
