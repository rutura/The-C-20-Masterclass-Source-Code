#The root CMakeLists.txt file.
cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(Project_template  VERSION 1.0.0 LANGUAGES CXX)

#Require C++23
set(CXX_STANDARD_REQUIRED ON) #Make C++23 a hard requirement
set(CMAKE_CXX_STANDARD 23) # Default C++ standard for targets

find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp
        override_keyword.h override_keyword.cpp
        override_overload_and_hide.h override_overload_and_hide.cpp
        polymorphism_diff_levels.h polymorphism_diff_levels.cpp
        polymorphism_with_static_members.h polymorphism_with_static_members.cpp
        utilities.h utilities.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)