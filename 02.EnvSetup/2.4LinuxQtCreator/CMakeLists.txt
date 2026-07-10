cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

# MSVC leaves __cplusplus hardcoded at 199711L for backwards compatibility
# unless this flag is passed, regardless of the /std: mode actually in use -
# without it, this lecture's __cplusplus check would misreport on MSVC.
if (MSVC)
    target_compile_options(rooster PRIVATE /Zc:__cplusplus)
endif()

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
