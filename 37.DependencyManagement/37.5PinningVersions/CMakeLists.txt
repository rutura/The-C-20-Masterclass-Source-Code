cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# BAD: floating on a branch name. Every fresh build (yours, a teammate's, a
# CI runner's) can silently pull a different commit as the branch moves --
# the exact bug that "works on my machine" comes from.
# FetchContent_Declare(
# 	fmt
# 	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
# 	GIT_TAG        master
# )

# GOOD: pin to a released tag. Everyone who builds this project gets the
# exact same fmt 12.2.0, forever, until someone deliberately bumps the tag.
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG        12.2.0
)

# ALSO GOOD, and even more precise: pin to a specific commit hash (this one
# is the exact commit tag 12.2.0 points to). Useful when a project hasn't
# cut a tagged release yet, or you need a fix that landed after the last
# tag -- a hash can never be force-pushed to point somewhere else the way a
# branch or (rarely) a tag technically can.
# FetchContent_Declare(
# 	fmt
# 	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
# 	GIT_TAG        1be298e1bd68957e4cd352e1f676f00e07dcfb57
# )

FetchContent_MakeAvailable(fmt)

# Create executable
add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE fmt::fmt)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
