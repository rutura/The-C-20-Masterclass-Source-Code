#!/bin/sh
# Answer key for the notes: driving CMake from the command line with GCC on Linux.
# Run inside this folder (in the course's GCC container, or any Linux with g++).
set -e

run() { echo "> $*"; "$@"; }

# 1. Configure: read CMakeLists.txt and generate build files into build-gcc.
#    -S = where the source is, -B = where the build goes, -G = which generator.
#    -DCMAKE_CXX_COMPILER picks the compiler explicitly.
run cmake -S . -B build-gcc -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
run cmake --build build-gcc --verbose

run ./build-gcc/rooster

# 3. Build only one target (just the library).
run cmake --build build-gcc --target station

# 4. Same sources, different answer: ask for a .so instead of a static library.
run cmake -S . -B build-gcc-shared -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DBUILD_SHARED_LIBS=ON
run cmake --build build-gcc-shared
ls build-gcc-shared/*.so
run ./build-gcc-shared/rooster

# 5. Install the static build into a folder, to see what "install" means.
run cmake --install build-gcc --prefix install-gcc
find install-gcc -type f
