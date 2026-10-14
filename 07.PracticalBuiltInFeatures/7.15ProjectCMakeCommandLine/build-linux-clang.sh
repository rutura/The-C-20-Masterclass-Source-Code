#!/bin/sh
# Answer key for the notes: driving CMake from the command line with Clang on Linux.
# Run inside this folder (in the course's Clang container, or any Linux with clang++).
# The steps are in the same order as the notes.
# Everything CMake and the compiler produce goes into out-linux-clang, so
# deleting that one folder cleans up.
set -e

run() { echo "> $*"; "$@"; }

# For the "break it on purpose" steps: the command must fail.
run_must_fail() {
    echo "> $*"
    if "$@"; then echo "should have failed: $*"; exit 1; fi
    echo "(failed, as expected)"
}

# 1. Configure: read CMakeLists.txt and generate build files into out-linux-clang/static.
#    -S = where the source is, -B = where the build goes, -G = which generator.
#    -DCMAKE_CXX_COMPILER picks the compiler explicitly.
run cmake -S . -B out-linux-clang/static -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
ls out-linux-clang/static
grep -E '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:|CMAKE_AR:)' out-linux-clang/static/CMakeCache.txt

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
run cmake --build out-linux-clang/static --verbose
run ./out-linux-clang/static/rooster

# 3. Build again: nothing changed, then touch one source file.
run cmake --build out-linux-clang/static
run touch stats.cpp
run cmake --build out-linux-clang/static

# 4. Build one target, and a different build type.
run cmake -S . -B out-linux-clang/release -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
run cmake --build out-linux-clang/release --target station --verbose
ls out-linux-clang/release
run cmake --build out-linux-clang/release
run ./out-linux-clang/release/rooster

# 5. Same sources, different answer: ask for a .so instead of a static library.
run cmake -S . -B out-linux-clang/shared -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=ON
run cmake --build out-linux-clang/shared --verbose
ls -l out-linux-clang/shared/libstation.so out-linux-clang/shared/rooster
run ./out-linux-clang/shared/rooster
# CMake baked the build folder into the program, so no LD_LIBRARY_PATH is needed.
readelf -d out-linux-clang/shared/rooster | grep -E 'NEEDED.*station|RUNPATH'
ldd out-linux-clang/shared/rooster | grep station

# 6. Install both builds into folders, to see what "install" means.
run cmake --install out-linux-clang/static --prefix out-linux-clang/install
find out-linux-clang/install -type f
run ./out-linux-clang/install/bin/rooster
run cmake --install out-linux-clang/shared --prefix out-linux-clang/install-shared
find out-linux-clang/install-shared -type f
# The install step removed the build-folder path from the program, so the
# loader cannot find libstation.so any more.
run_must_fail ./out-linux-clang/install-shared/bin/rooster
echo "> LD_LIBRARY_PATH=out-linux-clang/install-shared/lib ./out-linux-clang/install-shared/bin/rooster"
LD_LIBRARY_PATH=out-linux-clang/install-shared/lib ./out-linux-clang/install-shared/bin/rooster
# Better: ask CMake to put a relative rpath into the installed program.
run cmake -S . -B out-linux-clang/shared -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=ON '-DCMAKE_INSTALL_RPATH=$ORIGIN/../lib'
run cmake --build out-linux-clang/shared
run cmake --install out-linux-clang/shared --prefix out-linux-clang/install-shared
readelf -d out-linux-clang/install-shared/bin/rooster | grep -E 'RUNPATH'
run ./out-linux-clang/install-shared/bin/rooster

# 7. Break it on purpose
# 7a. The source folder has no CMakeLists.txt
run_must_fail cmake -S out-linux-clang -B out-linux-clang/oops -G Ninja
# 7b. A target that does not exist
run_must_fail cmake --build out-linux-clang/static --target stationn
# 7c. Build a folder that was never configured
run_must_fail cmake --build out-linux-clang/nothere
# 7d. Another generator in a folder that already has one
run_must_fail cmake -S . -B out-linux-clang/static -G "Unix Makefiles"
