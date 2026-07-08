cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# CATCH_INSTALL_DOCS/CATCH_BUILD_TESTING off: we only want the Catch2
# library itself, not its own internal test suite and docs built alongside
# our project every time.
set(CATCH_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

# Create executable
add_executable(rooster main.cpp bank_account.h)
target_link_libraries(rooster PRIVATE Catch2::Catch2WithMain)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
