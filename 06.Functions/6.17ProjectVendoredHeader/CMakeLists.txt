cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rooster
    main.cpp
    image.cpp
    image.h
    stb_impl.cpp          # the ONE file that compiles stb's function bodies
    vendor/stb_image_write.h
)

# Put vendor/ on the header search path so #include "stb_image_write.h"
# resolves without a path prefix. The header is compiled here from source
# - there is no library binary to link, so no ABI concerns.
#
# SYSTEM marks it as third-party: the compiler will not nag us about
# warnings originating inside stb's own code.
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
