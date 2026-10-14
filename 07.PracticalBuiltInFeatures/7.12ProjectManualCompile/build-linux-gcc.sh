#!/bin/sh
# Answer key for the notes: Linux with GCC, no CMake.
# Run inside this folder (in the course's GCC container, or any Linux with g++).
# The steps are in the same order as the notes.
# Everything the tools produce goes into out-linux-gcc, so deleting that one
# folder cleans up.
set -e

run() { echo "> $*"; "$@"; }

# For the "break it on purpose" step: the command must fail.
run_must_fail() {
    echo "> $*"
    if "$@"; then echo "should have failed: $*"; exit 1; fi
    echo "(failed, as expected)"
}

mkdir -p out-linux-gcc

# 1. Single file, two steps
run g++ -std=c++23 -Wall -Wextra -c single.cpp -o out-linux-gcc/single.o
run g++ out-linux-gcc/single.o -o out-linux-gcc/single_two_step
run ./out-linux-gcc/single_two_step

# 2. Read the object files and the binary
run g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-gcc/stats.o
run g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-gcc/report.o
run file out-linux-gcc/stats.o
readelf -h out-linux-gcc/stats.o | grep -E 'Class|Type|Machine'
# A tiny program still has hundreds of std:: symbols, so filter for our namespace.
# U means "undefined here, the linker must find it".
nm out-linux-gcc/stats.o | grep station
nm -C out-linux-gcc/stats.o | grep station
nm out-linux-gcc/report.o | grep to_celsius
run c++filt _ZN7station10to_celsiusEd
run file out-linux-gcc/single_two_step
readelf -h out-linux-gcc/single_two_step | grep -E 'Type|Machine'
run ldd out-linux-gcc/single_two_step

# 3. Single file, one step
run g++ -std=c++23 -Wall -Wextra single.cpp -o out-linux-gcc/single_one_step
run ./out-linux-gcc/single_one_step
run ls -l out-linux-gcc/single.o out-linux-gcc/single_two_step out-linux-gcc/single_one_step

# 4. Multiple files: three objects, one link
run g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-gcc/stats.o
run g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-gcc/report.o
run g++ -std=c++23 -Wall -Wextra -c main.cpp -o out-linux-gcc/main.o
run g++ out-linux-gcc/main.o out-linux-gcc/stats.o out-linux-gcc/report.o -o out-linux-gcc/weather
run ./out-linux-gcc/weather

# Break it on purpose: leave stats.o out
run_must_fail g++ out-linux-gcc/main.o out-linux-gcc/report.o -o out-linux-gcc/broken
