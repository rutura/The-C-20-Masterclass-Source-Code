#The root CMakeLists.txt file.
cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(Project_template  VERSION 1.0.0 LANGUAGES CXX)

#Require C++23
set(CXX_STANDARD_REQUIRED ON) #Make C++23 a hard requirement
set(CMAKE_CXX_STANDARD 23) # Default C++ standard for targets

find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        explicit_instantiation_declaration.cpp
        utilities.h utilities.cpp
        implicit_instantiations.h
        explicit_instantiation_definition.h
        explicit_instantiation_declaration.h
        full_specialization.h
        partial_specialization.h
        type_trait_example.h
        single_method_in_class.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)