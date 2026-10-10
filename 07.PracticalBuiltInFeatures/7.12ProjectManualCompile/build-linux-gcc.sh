#!/bin/sh
# Answer key for the notes: Linux with GCC, no CMake.
# Run inside this folder (in the course's GCC container, or any Linux with g++).
set -e

run() { echo "> $*"; "$@"; }

# Part 1: single file, two steps
run g++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
run g++ single.o -o single_two_step

# Part 1 again: single file, one step
run g++ -std=c++23 -Wall -Wextra single.cpp -o single_one_step

# Part 2: three source files, three objects, one link
run g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
run g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
run g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
run g++ main.o stats.o report.o -o weather

run ./weather

# Part 3: look inside. ELF object, Itanium name mangling.
run file stats.o weather
run readelf -h stats.o
# A tiny program still drags in hundreds of std:: template symbols, so
# filter for our own namespace. U means "undefined here, the linker must find it".
nm stats.o | grep station
nm -C stats.o | grep station
nm report.o | grep to_celsius
