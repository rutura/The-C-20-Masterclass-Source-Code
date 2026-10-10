#!/bin/sh
# Answer key for the notes: Linux with Clang, no CMake.
# Run inside this folder (in the course's Clang container, or any Linux with clang++).
set -e

run() { echo "> $*"; "$@"; }

# Part 1: single file, two steps
run clang++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
run clang++ single.o -o single_two_step

# Part 1 again: single file, one step
run clang++ -std=c++23 -Wall -Wextra single.cpp -o single_one_step

# Part 2: three source files, three objects, one link
run clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
run clang++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
run clang++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
run clang++ main.o stats.o report.o -o weather

run ./weather

# Part 3: look inside
run file stats.o weather
run readelf -h stats.o
# A tiny program still drags in hundreds of std:: template symbols, so
# filter for our own namespace. U means "undefined here, the linker must find it".
nm stats.o | grep station
nm -C stats.o | grep station
nm report.o | grep to_celsius
