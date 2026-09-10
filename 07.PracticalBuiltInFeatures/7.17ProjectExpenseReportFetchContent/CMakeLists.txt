cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Version C: identical C++ to version B, but csv2 is NOT committed here.
# CMake clones it at configure time. GIT_TAG is pinned to an exact commit
# so the build stays reproducible - never leave it on a branch name.
include(FetchContent)
FetchContent_Declare(csv2
    GIT_REPOSITORY https://github.com/p-ranav/csv2.git
    GIT_TAG        4f3c41db6457465e94b92b91fc560b911c16a16a
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(csv2)
# csv2 defines an INTERFACE target `csv2` that carries its include path.

add_executable(rooster
    main.cpp
    csv_loader.cpp
    csv_loader.h
    report.cpp
    report.h
)

# Link the interface target - header-only, so this only adds the include
# search path. As with vendoring, csv2's headers compile in our build:
# no prebuilt binary, no ABI concerns.
target_link_libraries(rooster PRIVATE csv2)

# Copy the sample data next to the executable.
add_custom_command(TARGET rooster POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/expenses.csv
            $<TARGET_FILE_DIR:rooster>/expenses.csv
)
