cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Version A: no third-party library. Our own files only - the CSV is
# split by hand in report.cpp.
add_executable(rooster
    main.cpp
    report.cpp
    report.h
)

# Copy the sample data next to the executable so it runs with no
# arguments straight after building.
add_custom_command(TARGET rooster POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/expenses.csv
            $<TARGET_FILE_DIR:rooster>/expenses.csv
)
