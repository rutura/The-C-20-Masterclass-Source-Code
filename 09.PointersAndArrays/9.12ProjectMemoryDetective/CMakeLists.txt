cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

# Turn the sanitizers on or off from the command line:
#   cmake -S . -B build -G Ninja -DDETECTIVE_SANITIZE=OFF
# They are ON by default here, because catching the planted bugs is the point.
option(DETECTIVE_SANITIZE "Build with AddressSanitizer (and UBSan where available)" ON)

if(DETECTIVE_SANITIZE)
    if(MSVC)
        # MSVC's Debug flags include /RTC1 (run-time checks), which cannot be
        # combined with /fsanitize=address. Remove it, and the incremental
        # linker, which the sanitizer also does not support.
        string(REGEX REPLACE "/RTC[1csu]+" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        target_compile_options(rooster PRIVATE /fsanitize=address /Zi)
        target_link_options(rooster PRIVATE /INCREMENTAL:NO)
    else()
        # -g keeps line numbers for the report. Frame pointers make the
        # stack traces in it complete.
        target_compile_options(rooster PRIVATE
            -fsanitize=address,undefined -fno-omit-frame-pointer -g)
        target_link_options(rooster PRIVATE -fsanitize=address,undefined)
    endif()
endif()
