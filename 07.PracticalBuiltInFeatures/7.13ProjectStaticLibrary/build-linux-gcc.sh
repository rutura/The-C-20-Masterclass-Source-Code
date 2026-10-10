#!/bin/sh
# Answer key for the notes: a static library with GCC on Linux, no CMake.
# Run inside this folder (in the course's GCC container, or any Linux with g++).
set -e

run() { echo "> $*"; "$@"; }

# 1. The library's source files become object files, as in 7.12.
run g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
run g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o

# 2. ar bundles the objects into an archive. r = insert, c = create quietly,
#    s = write a symbol index so the linker can find things fast.
run ar rcs libstation.a stats.o report.o

# 3. Look inside the archive: t = list the members, tv = with sizes.
run file libstation.a
run ar t libstation.a
run ar tv libstation.a
nm -C libstation.a | grep to_celsius

# 4. The program itself, then link it against the archive.
#    -L. = also search this folder, -lstation = find libstation.a
run g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
run g++ main.o -L. -lstation -o weather

run ./weather
