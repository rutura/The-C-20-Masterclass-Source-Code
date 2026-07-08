cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Threading needs the platform's thread library linked in explicitly.
find_package(Threads REQUIRED)

# Create executable
add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE Threads::Threads)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
