cmake_minimum_required(VERSION 3.28)
project(48.6MultipleImplementationFiles CXX)

# Turning off extensions avoids and issue with the clang 16 compiler
# clang 17 and greater can avoid this setting
set(CMAKE_CXX_EXTENSIONS OFF)
# Set the version of C++ for the project
set(CMAKE_CXX_STANDARD 20)
# Create a library
add_library(math)
# Add the module file to the library
target_sources(math
  PUBLIC
    FILE_SET CXX_MODULES FILES
      math.ixx   
)
# Create an executable
add_executable(rooster main.cpp math_impl.cpp print_impl.cpp)
# Link to the library math
target_link_libraries(rooster math)