#!/bin/sh
set -e

cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++ .
cmake --build build
./build/rooster
