#!/bin/sh
# Answer key for the notes: a static library with GCC on Linux, no CMake.
# Run inside this folder (in the course's GCC container, or any Linux with g++).
# The steps are in the same order as the notes.
# Everything the tools produce goes into out-linux-gcc, so deleting that one
# folder cleans up.
set -e

run() { echo "> $*"; "$@"; }

# For the "break it on purpose" steps: the command must fail.
run_must_fail() {
    echo "> $*"
    if "$@"; then echo "should have failed: $*"; exit 1; fi
    echo "(failed, as expected)"
}

mkdir -p out-linux-gcc

# 1. Build the library: two objects, then one archive.
#    ar: r = insert, c = create quietly, s = write a symbol index.
run g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-gcc/stats.o
run g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-gcc/report.o
run ar rcs out-linux-gcc/libstation.a out-linux-gcc/stats.o out-linux-gcc/report.o
run file out-linux-gcc/libstation.a
run ar t out-linux-gcc/libstation.a
run ar tv out-linux-gcc/libstation.a

# 2. Look inside the archive: the members are the original object files
nm -C out-linux-gcc/libstation.a | grep -E 'to_celsius|\.o:'
run ls -l out-linux-gcc/stats.o out-linux-gcc/report.o out-linux-gcc/libstation.a
# Take one member back out and compare it with the object we put in.
mkdir -p out-linux-gcc/extracted
run ar x --output out-linux-gcc/extracted out-linux-gcc/libstation.a stats.o
cmp out-linux-gcc/stats.o out-linux-gcc/extracted/stats.o && echo "identical"

# 3. Link the program against the library.
#    -L<folder> = also search this folder, -lstation = find libstation.a
run g++ -std=c++23 -Wall -Wextra -c main.cpp -o out-linux-gcc/main.o
run g++ out-linux-gcc/main.o -Lout-linux-gcc -lstation -o out-linux-gcc/weather
run ./out-linux-gcc/weather
run ls -l out-linux-gcc/main.o out-linux-gcc/weather

# 4. Break it on purpose
# 4a. Leave the library out
run_must_fail g++ out-linux-gcc/main.o -o out-linux-gcc/broken
# 4b. Library before the object that needs it
run_must_fail g++ -Lout-linux-gcc -lstation out-linux-gcc/main.o -o out-linux-gcc/broken
# 4c. Forget -L
run_must_fail g++ out-linux-gcc/main.o -lstation -o out-linux-gcc/broken

# 5. The finished program does not need the library any more
run rm out-linux-gcc/libstation.a
run ./out-linux-gcc/weather
