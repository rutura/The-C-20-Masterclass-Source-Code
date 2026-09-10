cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Version B: the csv2 library is VENDORED - its headers live under
# vendor/csv2/ and are committed alongside our code. csv2 is header-only,
# so there is nothing to build or link; it is compiled from source as
# part of this target, which means no ABI mismatch is possible.
add_executable(rooster
    main.cpp
    csv_loader.cpp
    csv_loader.h
    report.cpp
    report.h
)

# Put vendor/ on the include path so #include <csv2/reader.hpp> resolves.
# SYSTEM marks it third-party: -Wall / -Wextra will not flag csv2's code.
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

# Copy the sample data next to the executable.
add_custom_command(TARGET rooster POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/expenses.csv
            $<TARGET_FILE_DIR:rooster>/expenses.csv
)
