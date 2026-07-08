cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Unlike FetchContent, vcpkg doesn't build the dependency as part of this
# project's own build -- vcpkg.json (next to this file) declares fmt as a
# dependency, and passing -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/
# buildsystems/vcpkg.cmake at configure time makes vcpkg install it before
# CMake even gets here. find_package() then locates the already-built
# package, same as it would for a system-installed library.
find_package(fmt CONFIG REQUIRED)

# Create executable
add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE fmt::fmt)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
