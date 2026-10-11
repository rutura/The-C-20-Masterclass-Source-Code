cmake_minimum_required(VERSION 3.30)       # modules need 3.28; `import std;` (exercise 6) needs 3.30

# MSVC only: CMake's experimental support for `import std;` (17.6). Before project().
if(CMAKE_HOST_WIN32)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
endif()

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(import-std.cmake)                  # target_use_import_std(), explained in 17.6

# ---- Your program -------------------------------------------------------------------
# Start with main.cpp alone. Every module file you write goes in a FILE_SET like this
# one, and every implementation unit (an ordinary .cpp) goes on the add_executable line:
#
#     add_executable(rooster main.cpp statistics.cpp)
#     target_sources(rooster PRIVATE
#         FILE_SET CXX_MODULES FILES
#             units.cppm
#             limits.cppm
#     )
add_executable(rooster main.cpp)

# ---- The solution -------------------------------------------------------------------
add_executable(rooster_solution
    main_solution.cpp
    solution/statistics.cpp
    solution/weather.cpp
    legacy_alarm.cpp                       # the legacy implementation stays an ordinary source
)
target_sources(rooster_solution PRIVATE
    FILE_SET CXX_MODULES FILES
        solution/units.cppm
        solution/limits.cppm
        solution/statistics.cppm
        solution/clamp.cppm
        solution/weather.cppm
        solution/weather_model.cppm
        solution/weather_detail.cppm
        solution/weather_format.cppm
        solution/alarms.cppm
)
target_include_directories(rooster_solution PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})   # for legacy_alarm.h

# Exercise 6 is a second program that uses `import std;` and nothing else.
add_executable(rooster_solution_std main_std_solution.cpp)
target_sources(rooster_solution_std PRIVATE
    FILE_SET CXX_MODULES FILES
        solution/summary.cppm
)
target_use_import_std(rooster_solution_std)
