cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rooster
    main.cpp
    canvas.cpp
    canvas.h
    color.h
    stb_impl.cpp          # the ONE file that compiles stb's function bodies (6.18)
    vendor/stb_image_write.h
)

# The vendored header from 6.18, found without a path prefix. SYSTEM keeps the
# compiler from warning about code inside stb itself.
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
