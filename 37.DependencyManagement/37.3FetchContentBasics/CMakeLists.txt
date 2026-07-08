cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# FetchContent_Declare records where to get a dependency from and which
# version -- it doesn't download anything yet.
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG        12.2.0
)

# FetchContent_MakeAvailable actually downloads (if not already cached) and
# configures fmt as part of this build -- no manual "go download a zip and
# extract it somewhere" step, no system package manager involved.
FetchContent_MakeAvailable(fmt)

# Create executable
add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE fmt::fmt)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
