#!/bin/sh
# Answer key for the notes: vcpkg in classic mode, in the Linux containers.
# Run inside this folder. The course's images already contain vcpkg, in
# /opt/vcpkg, with VCPKG_ROOT pointing at it. (To get your own, see
# build-windows.ps1 step 1: git clone, then ./bootstrap-vcpkg.sh.)
set -e

run() { echo "> $*"; "$@"; }

# Which vcpkg are we using?
echo "VCPKG_ROOT=$VCPKG_ROOT"
run vcpkg version

# 1. Install a library. The default triplet here is x64-linux: 64-bit, static
#    libraries.
run vcpkg install fmt

# 2. What is installed, and where?
run vcpkg list
ls "$VCPKG_ROOT/installed"
ls "$VCPKG_ROOT/installed/x64-linux/include" | head -3
ls "$VCPKG_ROOT/installed/x64-linux/lib"

# 3. Tell CMake about vcpkg with its toolchain file, build and run.
run cmake -S . -B build -G Ninja "-DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release
run cmake --build build
run ./build/rooster
