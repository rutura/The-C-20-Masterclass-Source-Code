#!/bin/sh
# Answer key for the notes: driving CMake from the command line with Clang on Linux.
# Run inside this folder (in the course's Clang container, or any Linux with clang++).
set -e

run() { echo "> $*"; "$@"; }

# 1. Configure. Only the compiler options differ from the GCC script.
run cmake -S . -B build-clang -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
run cmake --build build-clang --verbose

run ./build-clang/rooster

# 3. Build only one target (just the library).
run cmake --build build-clang --target station

# 4. Same sources, different answer: ask for a .so instead of a static library.
run cmake -S . -B build-clang-shared -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=ON
run cmake --build build-clang-shared
ls build-clang-shared/*.so
run ./build-clang-shared/rooster

# 5. Install the static build into a folder, to see what "install" means.
run cmake --install build-clang --prefix install-clang
find install-clang -type f
