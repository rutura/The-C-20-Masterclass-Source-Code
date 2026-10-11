#!/bin/sh
# Answer key for the notes: `import std;` with Clang 21 and libc++ (the course image), without CMake.
# Run inside this folder. Clang needs libc++ for this: libstdc++ has no module sources Clang can use.
set -e

STD_CPPM=/usr/lib/llvm-21/share/libc++/v1/std.cppm      # where the course image keeps libc++'s module source

# Step 1: compile the standard library module ONCE into a precompiled module file.
clang++ -std=c++23 -stdlib=libc++ -Wno-reserved-module-identifier --precompile -o std.pcm "$STD_CPPM"

# Step 2: compile and link your program, telling Clang where the module `std` lives.
clang++ -std=c++23 -stdlib=libc++ -fmodule-file=std=std.pcm main.cpp std.pcm -o rooster

./rooster
