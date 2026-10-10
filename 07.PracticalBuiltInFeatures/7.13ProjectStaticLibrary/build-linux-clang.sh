#!/bin/sh
# Answer key for the notes: a static library with Clang on Linux, no CMake.
# Run inside this folder (in the course's Clang container, or any Linux with clang++).
set -e

run() { echo "> $*"; "$@"; }

# 1. The library's source files become object files, as in 7.12.
run clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
run clang++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o

# 2. Bundle the objects into an archive.
run ar rcs libstation.a stats.o report.o

# 3. Look inside the archive.
run file libstation.a
run ar t libstation.a
run ar tv libstation.a
nm -C libstation.a | grep to_celsius

# 4. The program itself, then link it against the archive.
run clang++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
run clang++ main.o -L. -lstation -o weather

run ./weather
