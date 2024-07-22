#The root CMakeLists.txt file.
cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(Project_template  VERSION 1.0.0 LANGUAGES CXX)

#Require C++23
set(CXX_STANDARD_REQUIRED ON) #Make C++23 a hard requirement
set(CMAKE_CXX_STANDARD 23) # Default C++ standard for targets
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET CXX_MODULES FILES
        utilities.ixx 
        catching_std_exceptions.ixx
        throwing_std_exceptions.ixx 
        deriving_from_std_exceptions.ixx 
)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)