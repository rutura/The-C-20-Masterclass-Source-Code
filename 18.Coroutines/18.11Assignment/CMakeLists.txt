cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp task.h scheduler.h)

# Solution
add_executable(rooster_solution main_solution.cpp task.h scheduler.h)

# Exercise 8 needs AddressSanitizer (9.12) to see its bug, so it is ON for both
# programs. Turn it off with -DASSIGNMENT_SANITIZE=OFF.
option(ASSIGNMENT_SANITIZE "Build with AddressSanitizer" ON)

if(ASSIGNMENT_SANITIZE)
    if(MSVC)
        # /RTC1 (Debug run-time checks) cannot be combined with /fsanitize=address,
        # and neither can the incremental linker.
        string(REGEX REPLACE "/RTC[1csu]+" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        foreach(target rooster rooster_solution)
            target_compile_options(${target} PRIVATE /fsanitize=address /Zi)
            target_link_options(${target} PRIVATE /INCREMENTAL:NO)
        endforeach()
    else()
        foreach(target rooster rooster_solution)
            target_compile_options(${target} PRIVATE -fsanitize=address -fno-omit-frame-pointer -g)
            target_link_options(${target} PRIVATE -fsanitize=address)
        endforeach()
    endif()
endif()
