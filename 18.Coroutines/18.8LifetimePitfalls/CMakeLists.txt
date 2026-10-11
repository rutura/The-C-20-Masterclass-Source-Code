cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp task.h)

# The bugs in this lecture are only caught reliably by AddressSanitizer (9.12),
# so it is ON by default. Turn it off with -DPITFALLS_SANITIZE=OFF to see how
# quietly some of these bugs behave without it.
option(PITFALLS_SANITIZE "Build with AddressSanitizer" ON)

if(PITFALLS_SANITIZE)
    if(MSVC)
        # /RTC1 (Debug run-time checks) cannot be combined with /fsanitize=address,
        # and neither can the incremental linker.
        string(REGEX REPLACE "/RTC[1csu]+" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        target_compile_options(rooster PRIVATE /fsanitize=address /Zi)
        target_link_options(rooster PRIVATE /INCREMENTAL:NO)
    else()
        target_compile_options(rooster PRIVATE -fsanitize=address -fno-omit-frame-pointer -g)
        target_link_options(rooster PRIVATE -fsanitize=address)
    endif()
endif()
