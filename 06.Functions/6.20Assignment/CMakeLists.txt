cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Fetch stb at configure time (needed for Exercise 8's write_png) -----
# Same setup as 6.18ProjectFetchContent: stb is header-only, so there is
# no build step, just sources dropped into the build tree. GIT_TAG is
# pinned to an exact commit for a reproducible build.
include(FetchContent)
FetchContent_Declare(stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        2c980bb59875b0d32144a71867fbdebb2f77cd20
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(stb)
# After this, ${stb_SOURCE_DIR} is the checked-out repo folder.
# ------------------------------------------------------------------------

# Create executable
add_executable(rooster
    main.cpp
    image.cpp
    image.h
    stb_impl.cpp
)

# The solved version of the assignment, built as its own executable
# alongside the student's starting point (main.cpp).
add_executable(rooster_solution
    main_solution.cpp
    image.cpp
    image.h
    stb_impl.cpp
)

# Point at the fetched sources so #include "stb_image_write.h" resolves.
# SYSTEM: do not warn about code inside stb.
target_include_directories(rooster SYSTEM PRIVATE ${stb_SOURCE_DIR})
target_include_directories(rooster_solution SYSTEM PRIVATE ${stb_SOURCE_DIR})
