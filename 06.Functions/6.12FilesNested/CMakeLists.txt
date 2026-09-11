cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The .cpp files now sit in subfolders; give their paths relative to this
# CMakeLists.txt.
add_executable(rooster
    main.cpp
    geometry/geometry.cpp
    finance/money.cpp
    geometry/geometry.h
    finance/money.h
)

# Without this, #include "geometry.h" in main.cpp fails - the compiler
# only looks next to main.cpp and in the system paths. These lines add
# the two subfolders to the header search path, so the bare file names
# resolve. PRIVATE = applies to this target only.
target_include_directories(rooster PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/geometry
    ${CMAKE_CURRENT_SOURCE_DIR}/finance
)
