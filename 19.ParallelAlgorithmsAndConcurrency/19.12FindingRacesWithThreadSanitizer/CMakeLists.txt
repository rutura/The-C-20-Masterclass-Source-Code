cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(rooster PRIVATE Threads::Threads)

# ThreadSanitizer is how this lecture finds the bugs. GCC and Clang have it on
# Linux (and Clang on macOS). MSVC has AddressSanitizer but NO ThreadSanitizer,
# and neither has MinGW: on Windows, run this lecture in Docker or WSL (the
# notes show how). Turn it off with -DTHREADS_SANITIZE=OFF.
option(THREADS_SANITIZE "Build with ThreadSanitizer" ON)

if(THREADS_SANITIZE)
    if(MSVC OR WIN32)
        message(STATUS "No ThreadSanitizer for this compiler: building without it")
    else()
        # -g keeps line numbers in the report; frame pointers make the stack traces complete.
        target_compile_options(rooster PRIVATE -fsanitize=thread -fno-omit-frame-pointer -g)
        target_link_options(rooster PRIVATE -fsanitize=thread)
    endif()
endif()
