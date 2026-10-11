cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Timings of an unoptimized build are meaningless, so default to Release when
# no build type was chosen (Visual Studio and other multi-config setups ignore this).
# Note: with MSVC and Ninja, CMake picks Debug by itself on the first configure,
# so pass -DCMAKE_BUILD_TYPE=Release there.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Create executable
add_executable(rooster main.cpp)

# MSVC's standard library runs the parallel algorithms on its own thread pool.
# GCC and Clang (libstdc++) need Intel's oneTBB. Without it the program still
# compiles and runs, but every policy runs on ONE thread, and "par" can even be
# slower than plain code. Install it (Debian/Ubuntu: apt-get install libtbb-dev).
if(NOT MSVC)
    find_package(TBB QUIET)
    if(TBB_FOUND)
        target_link_libraries(rooster PRIVATE TBB::tbb)
    else()
        message(WARNING "oneTBB not found: std::execution::par will run on one thread. Try: apt-get install libtbb-dev")
    endif()
endif()
