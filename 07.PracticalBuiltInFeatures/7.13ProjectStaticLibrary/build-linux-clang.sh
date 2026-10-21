#!/bin/sh
# Answer key for the notes: a static library with Clang on Linux, no CMake.
# Run inside this folder (in the course's Clang container, or any Linux with clang++).
# The steps are in the same order as the notes.
# Everything the tools produce goes into out-linux-clang, so deleting that one
# folder cleans up.
set -e

run() { echo "> $*"; "$@"; }

# For the "break it on purpose" steps: the command must fail.
run_must_fail() {
    echo "> $*"
    if "$@"; then echo "should have failed: $*"; exit 1; fi
    echo "(failed, as expected)"
}

mkdir -p out-linux-clang

# 1. Build the library: two objects, then one archive.
#    ar: r = insert, c = create quietly, s = write a symbol index.
run clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-clang/stats.o
run clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-clang/report.o
run ar rcs out-linux-clang/libstation.a out-linux-clang/stats.o out-linux-clang/report.o
run file out-linux-clang/libstation.a
run ar t out-linux-clang/libstation.a
run ar tv out-linux-clang/libstation.a

# 2. Look inside the archive: the members are the original object files
nm -C out-linux-clang/libstation.a | grep -E 'to_celsius|\.o:'
run ls -l out-linux-clang/stats.o out-linux-clang/report.o out-linux-clang/libstation.a
# Take one member back out and compare it with the object we put in.
mkdir -p out-linux-clang/extracted
run ar x --output out-linux-clang/extracted out-linux-clang/libstation.a stats.o
cmp out-linux-clang/stats.o out-linux-clang/extracted/stats.o && echo "identical"

# 3. Link the program against the library.
#    -L<folder> = also search this folder, -lstation = find libstation.a
run clang++ -std=c++23 -Wall -Wextra -c main.cpp -o out-linux-clang/main.o
run clang++ out-linux-clang/main.o -Lout-linux-clang -lstation -o out-linux-clang/weather
run ./out-linux-clang/weather
run ls -l out-linux-clang/main.o out-linux-clang/weather

# 4. Break it on purpose
# 4a. Leave the library out
run_must_fail clang++ out-linux-clang/main.o -o out-linux-clang/broken
# 4b. Library before the object that needs it
run_must_fail clang++ -Lout-linux-clang -lstation out-linux-clang/main.o -o out-linux-clang/broken
# 4c. Forget -L
run_must_fail clang++ out-linux-clang/main.o -lstation -o out-linux-clang/broken

# 5. The finished program does not need the library any more
run rm out-linux-clang/libstation.a
run ./out-linux-clang/weather
