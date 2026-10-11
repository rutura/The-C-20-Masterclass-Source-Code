cmake_minimum_required(VERSION 3.30)       # `import std;` support arrived in CMake 3.30, as an experiment

# With MSVC, CMake's support for `import std;` is experimental (17.6) and must be
# switched on BEFORE project(). GCC and Clang do not use this switch.
if(CMAKE_HOST_WIN32)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
endif()

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(import-std.cmake)                  # target_use_import_std(), explained in 17.6

# The vendored header-only library (6.18). The ONE file that compiles its
# function bodies goes in a small static library that every version links.
add_library(stb STATIC vendor/stb_impl.cpp)
target_include_directories(stb SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

# ---- Version 1: headers. The program of 11.12, unchanged. -----------------------
add_executable(rooster_headers
    headers/main.cpp
    headers/canvas.cpp
    headers/shapes.cpp
    headers/color.h
    headers/canvas.h
    headers/shape.h
    headers/shapes.h
)
target_include_directories(rooster_headers PRIVATE headers)
target_link_libraries(rooster_headers PRIVATE stb)

# ---- Version 2: modules. The same code, split into one module `render`. -----------
# The standard library is still brought in with #include.
add_executable(rooster
    modules/main.cpp
    modules/canvas.cpp          # implementation units are ordinary sources
    modules/shapes.cpp
)
target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        modules/render.cppm     # the primary interface
        modules/color.cppm      # its partitions
        modules/canvas.cppm
        modules/shape.cppm
        modules/shapes.cppm
)
target_link_libraries(rooster PRIVATE stb)

# ---- Version 3: modules, and `import std;` instead of the #includes. ---------------
add_executable(rooster_std
    modules_std/main.cpp
    modules_std/canvas.cpp
    modules_std/shapes.cpp
)
target_sources(rooster_std PRIVATE
    FILE_SET CXX_MODULES FILES
        modules_std/render.cppm
        modules_std/color.cppm
        modules_std/canvas.cppm
        modules_std/shape.cppm
        modules_std/shapes.cppm
)
target_use_import_std(rooster_std)
target_link_libraries(rooster_std PRIVATE stb)
