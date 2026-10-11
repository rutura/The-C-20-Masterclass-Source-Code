cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)

# C++26 contracts exist only in GCC 16 so far (needs -fcontracts). On any other
# compiler this second program is simply not built.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 16)
    add_executable(rooster_contracts main_contracts.cpp)
    target_compile_features(rooster_contracts PRIVATE cxx_std_26)
    # The flag is needed at link time too: it pulls in the default violation handler.
    target_compile_options(rooster_contracts PRIVATE -fcontracts)
    target_link_options(rooster_contracts PRIVATE -fcontracts)
endif()
