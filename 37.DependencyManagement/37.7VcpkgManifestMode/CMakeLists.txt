cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# builtin-baseline in vcpkg.json pins which commit of vcpkg's own package
# registry we resolve "fmt" and "nlohmann-json" against -- without it, the
# exact version vcpkg installs depends on whatever revision of the registry
# happens to be checked out on the machine building this, which is the same
# "works on my machine" risk 37.5PinningVersions warned about, just one
# level removed (pinning the registry, not just the library).
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Create executable
add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE fmt::fmt nlohmann_json::nlohmann_json)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
