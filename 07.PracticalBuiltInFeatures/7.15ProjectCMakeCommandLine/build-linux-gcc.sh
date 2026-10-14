#!/bin/sh
# Answer key for the notes: driving CMake from the command line with GCC on Linux.
# Run inside this folder (in the course's GCC container, or any Linux with g++).
# The steps are in the same order as the notes.
# Everything CMake and the compiler produce goes into out-linux-gcc, so
# deleting that one folder cleans up.
set -e

run() { echo "> $*"; "$@"; }

# For the "break it on purpose" steps: the command must fail.
run_must_fail() {
    echo "> $*"
    if "$@"; then echo "should have failed: $*"; exit 1; fi
    echo "(failed, as expected)"
}

# 1. Configure: read CMakeLists.txt and generate build files into out-linux-gcc/static.
#    -S = where the source is, -B = where the build goes, -G = which generator.
#    -DCMAKE_CXX_COMPILER picks the compiler explicitly.
run cmake -S . -B out-linux-gcc/static -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
ls out-linux-gcc/static
grep -E '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:|CMAKE_AR:)' out-linux-gcc/static/CMakeCache.txt

# 2. Build, and show the real commands CMake runs. Compare them with 7.12 to 7.14.
run cmake --build out-linux-gcc/static --verbose
run ./out-linux-gcc/static/rooster

# 3. Build again: nothing changed, then touch one source file.
run cmake --build out-linux-gcc/static
run touch stats.cpp
run cmake --build out-linux-gcc/static

# 4. Build one target, and a different build type.
run cmake -S . -B out-linux-gcc/release -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release
run cmake --build out-linux-gcc/release --target station --verbose
ls out-linux-gcc/release
run cmake --build out-linux-gcc/release
run ./out-linux-gcc/release/rooster

# 5. Same sources, different answer: ask for a .so instead of a static library.
run cmake -S . -B out-linux-gcc/shared -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DBUILD_SHARED_LIBS=ON
run cmake --build out-linux-gcc/shared --verbose
ls -l out-linux-gcc/shared/libstation.so out-linux-gcc/shared/rooster
run ./out-linux-gcc/shared/rooster
# CMake baked the build folder into the program, so no LD_LIBRARY_PATH is needed.
readelf -d out-linux-gcc/shared/rooster | grep -E 'NEEDED.*station|RUNPATH'
ldd out-linux-gcc/shared/rooster | grep station

# 6. Install both builds into folders, to see what "install" means.
run cmake --install out-linux-gcc/static --prefix out-linux-gcc/install
find out-linux-gcc/install -type f
run ./out-linux-gcc/install/bin/rooster
run cmake --install out-linux-gcc/shared --prefix out-linux-gcc/install-shared
find out-linux-gcc/install-shared -type f
# The install step removed the build-folder path from the program, so the
# loader cannot find libstation.so any more.
run_must_fail ./out-linux-gcc/install-shared/bin/rooster
echo "> LD_LIBRARY_PATH=out-linux-gcc/install-shared/lib ./out-linux-gcc/install-shared/bin/rooster"
LD_LIBRARY_PATH=out-linux-gcc/install-shared/lib ./out-linux-gcc/install-shared/bin/rooster
# Better: ask CMake to put a relative rpath into the installed program.
run cmake -S . -B out-linux-gcc/shared -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DBUILD_SHARED_LIBS=ON '-DCMAKE_INSTALL_RPATH=$ORIGIN/../lib'
run cmake --build out-linux-gcc/shared
run cmake --install out-linux-gcc/shared --prefix out-linux-gcc/install-shared
readelf -d out-linux-gcc/install-shared/bin/rooster | grep -E 'RUNPATH'
run ./out-linux-gcc/install-shared/bin/rooster

# 7. Break it on purpose
# 7a. The source folder has no CMakeLists.txt
run_must_fail cmake -S out-linux-gcc -B out-linux-gcc/oops -G Ninja
# 7b. A target that does not exist
run_must_fail cmake --build out-linux-gcc/static --target stationn
# 7c. Build a folder that was never configured
run_must_fail cmake --build out-linux-gcc/nothere
# 7d. Change the compiler of a folder that is already configured. This is not
#     an error: CMake warns, throws its cache away and starts again. The C and C++
#     compilers can end up different, which is why one folder keeps one compiler.
#     (The GCC image also carries Debian's GCC 14 as /usr/bin/g++-14.)
run cmake -S . -B out-linux-gcc/swap -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
run cmake -S . -B out-linux-gcc/swap -G Ninja -DCMAKE_CXX_COMPILER=/usr/bin/g++-14
