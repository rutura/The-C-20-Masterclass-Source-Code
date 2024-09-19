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
        constr_and_inh.h constr_and_inh.cpp
        copy_constr_and_inh.h copy_constr_and_inh.cpp
        inh_and_destructors.h inh_and_destructors.cpp
        inh_default_arg_constr.h inh_default_arg_constr.cpp
        inherit_base_constructors.h inherit_base_constructors.cpp
        utilities.h utilities.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)