#!/bin/sh
# Answer key for the notes: build times of the three versions, on Linux. Run
# inside this folder:   sh compare-builds.sh [compiler]       (g++ or clang++)
# Every number is the MEDIAN of 3 runs, in milliseconds, of an unoptimized build
# (CMake's default when no build type is given). The clean build of the third
# version includes building the standard library module, once.
CXX=${1:-g++}
BUILD=build-compare

cmake -S . -B $BUILD -G Ninja -DCMAKE_CXX_COMPILER=$CXX > /dev/null || exit 1
cmake --build $BUILD --target stb > /dev/null          # the shared library is not part of the comparison

ms()  { s=$(date +%s%N); "$@" > /dev/null 2>&1; e=$(date +%s%N); echo $(( (e - s) / 1000000 )); }
median() { sort -n | sed -n 2p; }
build() { cmake --build $BUILD --target "$1"; }

clean_build() {   # target
    for i in 1 2 3; do ninja -C $BUILD -t clean "$1" > /dev/null; ms build "$1"; done | median
}
touch_and_build() {   # target file
    build "$1" > /dev/null 2>&1
    for i in 1 2 3; do touch "$2"; ms build "$1"; done | median
}
row() { printf '%-36s %8s ms %8s ms %8s ms\n' "$1" "$2" "$3" "$4"; }

printf '%-36s %11s %11s %11s\n' "" "headers" "modules" "import std"
row "clean build" "$(clean_build rooster_headers)" "$(clean_build rooster)" "$(clean_build rooster_std)"
row "touch color (the lowest file)" "$(touch_and_build rooster_headers headers/color.h)" "$(touch_and_build rooster modules/color.cppm)" "$(touch_and_build rooster_std modules_std/color.cppm)"
row "touch shapes (the top interface)" "$(touch_and_build rooster_headers headers/shapes.h)" "$(touch_and_build rooster modules/shapes.cppm)" "$(touch_and_build rooster_std modules_std/shapes.cppm)"
row "touch canvas.cpp (an implementation)" "$(touch_and_build rooster_headers headers/canvas.cpp)" "$(touch_and_build rooster modules/canvas.cpp)" "$(touch_and_build rooster_std modules_std/canvas.cpp)"
row "touch main.cpp" "$(touch_and_build rooster_headers headers/main.cpp)" "$(touch_and_build rooster modules/main.cpp)" "$(touch_and_build rooster_std modules_std/main.cpp)"
