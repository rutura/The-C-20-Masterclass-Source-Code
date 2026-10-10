#!/bin/sh
# Answer key for the notes: vcpkg in manifest mode, in the Linux containers.
# Run inside this folder. VCPKG_ROOT is already set in the course's images.
set -e

run() { echo "> $*"; "$@"; }

echo "VCPKG_ROOT=$VCPKG_ROOT"

# vcpkg.json lists what this project needs. The first configure reads it,
# builds ftxui and puts it in build/vcpkg_installed.
run cmake --preset default

# CMakePresets.json already holds the generator, the toolchain file and the
# build type.
run cmake --build --preset default
run ./build/rooster

# Where did the libraries go? Inside the project's own build folder.
ls build/vcpkg_installed
ls build/vcpkg_installed/x64-linux/lib
