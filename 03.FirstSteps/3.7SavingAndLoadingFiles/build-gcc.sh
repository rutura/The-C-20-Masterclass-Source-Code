#!/bin/sh
set -e

cmake -B build -G Ninja .
cmake --build build
./build/rooster
