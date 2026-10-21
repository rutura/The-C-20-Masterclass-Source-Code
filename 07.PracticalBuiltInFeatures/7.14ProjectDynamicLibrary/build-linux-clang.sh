#!/bin/sh
# Answer key for the notes: a shared library with Clang on Linux, no CMake.
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

# 1. Build the library.
#    -fPIC                position-independent code: it can be loaded anywhere
#    -fvisibility=hidden  export only what STATION_API marks, like Windows
#    -shared              make a .so instead of an executable
run clang++ -std=c++23 -Wall -Wextra -fPIC -fvisibility=hidden -shared stats.cpp report.cpp -o out-linux-clang/libstation.so
run ls -l out-linux-clang/libstation.so
run file out-linux-clang/libstation.so

# 2. Look inside: the exported (dynamic) symbols. Only the three functions
#    marked STATION_API are ours, the rest are standard library templates.
nm -D --defined-only out-linux-clang/libstation.so | grep station
nm -D --defined-only out-linux-clang/libstation.so | wc -l

# 3. Link the program. -L<folder> -lstation finds libstation.so. There is no
#    import library on Linux: the .so is used at link time and at run time.
run clang++ -std=c++23 -Wall -Wextra main.cpp -Lout-linux-clang -lstation -o out-linux-clang/weather
readelf -d out-linux-clang/weather | grep NEEDED
ldd out-linux-clang/weather | grep -E 'station|not found'

# 4. Run it. The loader does not search the folder of the library, so it fails.
run_must_fail ./out-linux-clang/weather
# Two ways to tell the loader where to look.
echo "> LD_LIBRARY_PATH=out-linux-clang ./out-linux-clang/weather"
LD_LIBRARY_PATH=out-linux-clang ./out-linux-clang/weather
# Or bake the folder into the program (rpath). $ORIGIN = where the program is.
run clang++ -std=c++23 -Wall -Wextra main.cpp -Lout-linux-clang -lstation -Wl,-rpath,'$ORIGIN' -o out-linux-clang/weather_rpath
readelf -d out-linux-clang/weather_rpath | grep -E 'RPATH|RUNPATH'
run ./out-linux-clang/weather_rpath

# 5. Break it on purpose
# 5a. The library is missing when the program starts
mv out-linux-clang/libstation.so out-linux-clang/libstation.so.away
run_must_fail ./out-linux-clang/weather_rpath
mv out-linux-clang/libstation.so.away out-linux-clang/libstation.so
# 5b. Leave the library out of the link
run_must_fail clang++ -std=c++23 -Wall -Wextra main.cpp -o out-linux-clang/broken
# 5c. Name the library but not the folder
run_must_fail clang++ -std=c++23 -Wall -Wextra main.cpp -lstation -o out-linux-clang/broken

# 6. Replace the library without relinking the program: build a second version
#    from stats.cpp + report_v2.cpp, copy it over the old .so, run the SAME program.
mkdir -p out-linux-clang/v2
run clang++ -std=c++23 -Wall -Wextra -fPIC -fvisibility=hidden -shared stats.cpp report_v2.cpp -o out-linux-clang/v2/libstation.so
run cp out-linux-clang/v2/libstation.so out-linux-clang/libstation.so
run ./out-linux-clang/weather_rpath
