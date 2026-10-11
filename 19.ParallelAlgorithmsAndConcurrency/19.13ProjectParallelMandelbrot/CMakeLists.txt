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

add_executable(rooster
    main.cpp
    canvas.cpp
    canvas.h
    color.h
    thread_pool.h
    stb_impl.cpp          # the ONE file that compiles stb's function bodies (6.18)
    vendor/stb_image_write.h
)

# The vendored header from 6.18, found without a path prefix. SYSTEM keeps the
# compiler from warning about code inside stb itself.
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

find_package(Threads REQUIRED)
target_link_libraries(rooster PRIVATE Threads::Threads)

# std::execution::par needs oneTBB with GCC and Clang (19.2); MSVC has its own.
if(NOT MSVC)
    find_package(TBB QUIET)
    if(TBB_FOUND)
        target_link_libraries(rooster PRIVATE TBB::tbb)
    else()
        message(WARNING "oneTBB not found: the 'par' version will run on one thread. Try: apt-get install libtbb-dev")
    endif()
endif()
