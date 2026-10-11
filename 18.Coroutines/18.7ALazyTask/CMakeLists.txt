cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp task.h)

# A deep chain of tasks (the notes explain why this needs a flag with GCC)
add_executable(rooster2 main2.cpp task.h)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC turns the "jump to the next coroutine" into a real jump only when it
    # optimizes sibling calls, which -O2 switches on. Without it every hand-back
    # uses stack, and a million of them overflow it.
    target_compile_options(rooster2 PRIVATE -foptimize-sibling-calls)
endif()
