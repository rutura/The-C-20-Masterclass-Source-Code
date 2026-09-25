cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Fetch stb at configure time ------------------------------------------
# FetchContent clones a git repo into the build tree. stb is header-only,
# so there is no build step and nothing to link - MakeAvailable just puts
# the sources on disk. GIT_TAG is pinned to an exact commit so the build
# is reproducible; never leave it on a moving branch for a real project.
include(FetchContent)
FetchContent_Declare(stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        2c980bb59875b0d32144a71867fbdebb2f77cd20
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(stb)
# After this, ${stb_SOURCE_DIR} is the checked-out repo folder.
# ------------------------------------------------------------------------

add_executable(rooster
    main.cpp
    image.cpp
    image.h
    stb_impl.cpp          # compiles stb's function bodies, as in 6.17
)

# Point at the fetched sources so #include "stb_image_write.h" resolves.
# SYSTEM: do not warn about code inside stb.
target_include_directories(rooster SYSTEM PRIVATE
    ${stb_SOURCE_DIR}
)
