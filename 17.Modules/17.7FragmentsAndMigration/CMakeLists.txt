cmake_minimum_required(VERSION 3.28)       # CMake understands C++ modules from 3.28 on

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The migration: the header and its implementation are unchanged, and a module
# wraps them.
add_executable(rooster main.cpp legacy.cpp)
target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        legacy_module.cppm
)

# A module in one file, with a private module fragment. GCC 16 does not accept
# private module fragments yet (it stops at `module :private;`), so this second
# program is built only with MSVC and Clang.
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_executable(rooster_private main_private.cpp)
    target_sources(rooster_private PRIVATE
        FILE_SET CXX_MODULES FILES
            single.cppm
    )
endif()
