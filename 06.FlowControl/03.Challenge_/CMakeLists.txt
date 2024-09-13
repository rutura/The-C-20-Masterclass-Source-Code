#The root CMakeLists.txt file.
cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(Template  VERSION 1.0.0 LANGUAGES CXX)
#Require C++23
set(CXX_STANDARD_REQUIRED ON) #Make C++23 a hard requirement
set(CMAKE_CXX_STANDARD 23) # Default C++ standard for targets
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(Rocket main.cpp)
target_sources(Rocket
        PUBLIC
        FILE_SET CXX_MODULES FILES
        utilities.ixx
)

target_link_libraries(Rocket PRIVATE fmt::fmt sfml-graphics)