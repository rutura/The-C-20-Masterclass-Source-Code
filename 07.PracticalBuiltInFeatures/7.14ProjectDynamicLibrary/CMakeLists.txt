cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The same two files as 7.13, this time as a shared (dynamic) library.
# report_v2.cpp is not built here: the notes use it to replace the library
# without relinking the program.
add_library(station SHARED stats.cpp stats.h report.cpp report.h station_api.h)

# Only the library's own sources see "export". Everyone else sees "import".
target_compile_definitions(station PRIVATE STATION_BUILD_DLL)
set_target_properties(station PROPERTIES CXX_VISIBILITY_PRESET hidden)

# Create executable
add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE station)
