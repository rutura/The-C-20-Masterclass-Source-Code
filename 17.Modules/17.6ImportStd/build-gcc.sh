#!/bin/sh
# Answer key for the notes: `import std;` with GCC 16 (the course image), without CMake.
# Run inside this folder.
set -e

# Step 1: compile the standard library module ONCE. GCC ships its source, bits/std.cc,
# among the library headers; -fsearch-include-path finds it there. The result is
# written to gcm.cache/std.gcm.
g++ -std=c++23 -fmodules -fsearch-include-path -c bits/std.cc

# Step 2: compile and link your program. -fmodules finds gcm.cache/std.gcm.
g++ -std=c++23 -fmodules main.cpp -o rooster

./rooster
