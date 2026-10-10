cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Look for the package named "fmt". CONFIG means "find the fmt-config.cmake file
# that the library installed", REQUIRED means "stop with an error if it is not
# found". vcpkg's toolchain file (passed on the cmake command line, see the
# notes) is what tells CMake where vcpkg put it.
find_package(fmt CONFIG REQUIRED)

# Create executable
add_executable(rooster main.cpp)

# fmt::fmt is an IMPORTED TARGET made by find_package. Linking it brings the
# include folder, the library file and any compile definitions along.
target_link_libraries(rooster PRIVATE fmt::fmt)
