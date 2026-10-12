#!/bin/sh
# Answer key for the notes: Linux with GCC, no CMake.
# Run inside this folder (in the course's GCC container, or any Linux with g++).
# The steps are in the same order as the notes.
set -e

run() { echo "> $*"; "$@"; }

# For the "break it on purpose" step: the command must fail.
run_must_fail() {
    echo "> $*"
    if "$@"; then echo "should have failed: $*"; exit 1; fi
    echo "(failed, as expected)"
}

# 1. Single file, two steps
run g++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
run g++ single.o -o single_two_step
run ./single_two_step

# 2. Read the object files and the binary
run g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
run g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
run file stats.o
readelf -h stats.o | grep -E 'Class|Type|Machine'
# A tiny program still has hundreds of std:: symbols, so filter for our namespace.
# U means "undefined here, the linker must find it".
nm stats.o | grep station
nm -C stats.o | grep station
nm report.o | grep to_celsius
run c++filt _ZN7station10to_celsiusEd
run file single_two_step
readelf -h single_two_step | grep -E 'Type|Machine'
run ldd single_two_step

# 3. Single file, one step
run g++ -std=c++23 -Wall -Wextra single.cpp -o single_one_step
run ./single_one_step
run ls -l single.o single_two_step single_one_step

# 4. Multiple files: three objects, one link
run g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
run g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
run g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
run g++ main.o stats.o report.o -o weather
run ./weather

# Break it on purpose: leave stats.o out
run_must_fail g++ main.o report.o -o broken
