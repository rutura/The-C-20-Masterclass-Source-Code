#!/bin/sh
# Answer key for the notes: Linux with Clang, no CMake.
# Run inside this folder (in the course's Clang container, or any Linux with clang++).
# The steps are in the same order as the notes.
# Everything the tools produce goes into out-linux-clang, so deleting that one
# folder cleans up.
set -e

run() { echo "> $*"; "$@"; }

# For the "break it on purpose" step: the command must fail.
run_must_fail() {
    echo "> $*"
    if "$@"; then echo "should have failed: $*"; exit 1; fi
    echo "(failed, as expected)"
}

mkdir -p out-linux-clang

# 1. Single file, two steps
run clang++ -std=c++23 -Wall -Wextra -c single.cpp -o out-linux-clang/single.o
run clang++ out-linux-clang/single.o -o out-linux-clang/single_two_step
run ./out-linux-clang/single_two_step

# 2. Read the object files and the binary
run clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-clang/stats.o
run clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-clang/report.o
run file out-linux-clang/stats.o
readelf -h out-linux-clang/stats.o | grep -E 'Class|Type|Machine'
# A tiny program still has hundreds of std:: symbols, so filter for our namespace.
# U means "undefined here, the linker must find it".
nm out-linux-clang/stats.o | grep station
nm -C out-linux-clang/stats.o | grep station
nm out-linux-clang/report.o | grep to_celsius
run c++filt _ZN7station10to_celsiusEd
run file out-linux-clang/single_two_step
readelf -h out-linux-clang/single_two_step | grep -E 'Type|Machine'
run ldd out-linux-clang/single_two_step

# 3. Single file, one step
run clang++ -std=c++23 -Wall -Wextra single.cpp -o out-linux-clang/single_one_step
run ./out-linux-clang/single_one_step
run ls -l out-linux-clang/single.o out-linux-clang/single_two_step out-linux-clang/single_one_step

# 4. Multiple files: three objects, one link
run clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-clang/stats.o
run clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-clang/report.o
run clang++ -std=c++23 -Wall -Wextra -c main.cpp -o out-linux-clang/main.o
run clang++ out-linux-clang/main.o out-linux-clang/stats.o out-linux-clang/report.o -o out-linux-clang/weather
run ./out-linux-clang/weather

# Break it on purpose: leave stats.o out
run_must_fail clang++ out-linux-clang/main.o out-linux-clang/report.o -o out-linux-clang/broken
