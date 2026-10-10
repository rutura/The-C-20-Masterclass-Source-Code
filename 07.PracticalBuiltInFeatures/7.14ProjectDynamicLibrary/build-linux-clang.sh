#!/bin/sh
# Answer key for the notes: a shared library with Clang on Linux, no CMake.
# Run inside this folder (in the course's Clang container, or any Linux with clang++).
set -e

run() { echo "> $*"; "$@"; }

# 1. Build the library (flags explained in the GCC script).
run clang++ -std=c++23 -Wall -Wextra -fPIC -fvisibility=hidden -shared stats.cpp report.cpp -o libstation.so

# 2. Look inside: the exported (dynamic) symbols.
run file libstation.so
nm -D --defined-only libstation.so | grep station

# 3. Build the program.
run clang++ -std=c++23 -Wall -Wextra main.cpp -L. -lstation -o weather

# 4. Which libraries will the program load at startup, and are they found?
readelf -d weather | grep NEEDED
ldd weather | grep -E 'station|not found'

# 5. Running fails: the loader does not search the current folder.
./weather || echo "exit code without a search path: $?"

# 6. Two ways to tell the loader where to look.
echo "> LD_LIBRARY_PATH=. ./weather"
LD_LIBRARY_PATH=. ./weather

# 6b. Or bake the folder into the program (rpath). $ORIGIN = where the program is.
run clang++ -std=c++23 -Wall -Wextra main.cpp -L. -lstation -Wl,-rpath,'$ORIGIN' -o weather
run ./weather
