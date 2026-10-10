cmake_minimum_required(VERSION 3.20)

# Project name. ASM_NASM tells CMake we also have NASM source files, which
# means nasm must be installed (the notes show the one apt-get command).
project(rooster LANGUAGES CXX ASM_NASM)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable. CMake runs "nasm -f elf64" on ops.asm by itself.
add_executable(rooster main.cpp reference.cpp reference.h ops.asm)
