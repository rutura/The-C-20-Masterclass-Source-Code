cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# rapidcsv is VENDORED (see 6.17ProjectVendoredHeader for the pattern) -
# the header sits in vendor/, committed alongside our code. Nothing is
# downloaded, and being header-only, there is no separate implementation
# file to compile like stb needed.
add_executable(rooster
    main.cpp
    vendor/rapidcsv.h
)

# Put vendor/ on the header search path so #include "rapidcsv.h" resolves
# without a path prefix. SYSTEM marks it as third-party: the compiler will
# not nag us about warnings originating inside rapidcsv's own code.
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
