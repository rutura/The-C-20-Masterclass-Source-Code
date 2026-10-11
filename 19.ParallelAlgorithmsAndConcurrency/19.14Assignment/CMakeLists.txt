cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp thread_pool.h)

# Solution
add_executable(rooster_solution main_solution.cpp thread_pool.h)

find_package(Threads REQUIRED)
target_link_libraries(rooster PRIVATE Threads::Threads)
target_link_libraries(rooster_solution PRIVATE Threads::Threads)

# std::execution::par (exercise 1) needs oneTBB with GCC and Clang (19.2);
# MSVC has its own. Debian/Ubuntu: apt-get install libtbb-dev
if(NOT MSVC)
    find_package(TBB QUIET)
    if(TBB_FOUND)
        target_link_libraries(rooster PRIVATE TBB::tbb)
        target_link_libraries(rooster_solution PRIVATE TBB::tbb)
    else()
        message(WARNING "oneTBB not found: std::execution::par will run on one thread. Try: apt-get install libtbb-dev")
    endif()
endif()
