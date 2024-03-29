#The root CMakeLists.txt file.
cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(37.20AbstractClassesAsInterfaces  VERSION 1.0.0 LANGUAGES CXX)

#Require C++23
set(CXX_STANDARD_REQUIRED ON) #Make C++23 a hard requirement
set(CMAKE_CXX_STANDARD 23) # Default C++ standard for targets

find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        animal.cpp
        bird.cpp
        cat.cpp
        crow.cpp
        dog.cpp
        feline.cpp
        pigeon.cpp
        stream_insertable.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)