cmake_minimum_required(VERSION 3.20)

# Project name. ASM_NASM means nasm must be installed in the container.
project(rooster LANGUAGES CXX ASM_NASM)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable: the student's starting point (stubs that fail).
add_executable(rooster main.cpp mystery.cpp exercises.asm)

# The solved version of the assignment, built as its own executable
# alongside the student's starting point. It reuses the same checker
# (main.cpp) with the solved assembly and C++ files.
add_executable(rooster_solution main.cpp mystery_solution.cpp exercises_solution.asm)
