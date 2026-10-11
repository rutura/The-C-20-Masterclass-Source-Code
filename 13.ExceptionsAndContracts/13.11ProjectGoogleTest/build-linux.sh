#!/bin/sh
# Answer key for the notes: build and test with vcpkg manifest mode, in the
# Linux containers. Run inside this folder. VCPKG_ROOT is set in the images.
set -e

run() { echo "> $*"; "$@"; }

echo "VCPKG_ROOT=$VCPKG_ROOT"

# The first configure reads vcpkg.json and builds gtest.
run cmake --preset default
run cmake --build --preset default

# Two ways to run the tests: the executable itself, or CTest.
run ./build/rooster
run ctest --preset default
