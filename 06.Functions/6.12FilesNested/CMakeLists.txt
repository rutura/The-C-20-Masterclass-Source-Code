cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp
				finance/money.cpp 
				geometry/geometry.cpp)
# Without this, #include "geometry.h" in main.cpp fails - the compiler
# only looks next to main.cpp and in the system paths. These lines add
# the two subfolders to the header search path, so the bare file names
# resolve. PRIVATE = applies to this target only.
target_include_directories(rooster PRIVATE 
				${CMAKE_CURRENT_SOURCE_DIR}/geometry
				${CMAKE_CURRENT_SOURCE_DIR}/finance 
)
