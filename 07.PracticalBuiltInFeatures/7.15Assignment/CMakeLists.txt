cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# rapidcsv is VENDORED - same setup as 7.12ReadingCSV (needed for Exercise 6).
add_executable(rooster
    main.cpp
    vendor/rapidcsv.h
)

# The solved version of the assignment, built as its own executable
# alongside the student's starting point (main.cpp).
add_executable(rooster_solution
    main_solution.cpp
    vendor/rapidcsv.h
)

target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
target_include_directories(rooster_solution SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
