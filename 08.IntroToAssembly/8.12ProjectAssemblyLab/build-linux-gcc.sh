#!/bin/sh
# Answer key for the notes: the assembly lab with GCC, in the Linux container.
# One-time setup in the container:  apt-get update && apt-get install -y nasm
# Run inside this folder.
set -e

run() { echo "> $*"; "$@"; }

# Step 1: the smallest program. No C++ at all. nasm assembles, ld links.
run nasm -f elf64 exit_code.asm -o exit_code.o
run ld exit_code.o -o exit_code
./exit_code || echo "exit code: $?"           # prints 42

# Step 2: say something, using the write system call.
run nasm -f elf64 hello.asm -o hello.o
run ld hello.o -o hello
run ./hello

# Step 3: functions written in assembly, called from C++.
#   -g -F dwarf   keep source-line information, so gdb can show our .asm lines
run nasm -f elf64 -g -F dwarf ops.asm -o ops.o
run g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
run g++ -std=c++23 -Wall -Wextra -c reference.cpp -o reference.o
run g++ main.o reference.o ops.o -o ops_demo
run ./ops_demo

# Step 4: look at the names. ops.o has plain names, the C++ twins are mangled.
nm ops.o | grep -E 'add_i32|sum_array'
nm reference.o | grep -E 'add_i32|sum_array'

# Step 5: what does the compiler write for the same two jobs?
run g++ -std=c++23 -S -O0 -masm=intel reference.cpp -o reference_O0.s
run g++ -std=c++23 -S -O2 -masm=intel reference.cpp -o reference_O2.s
run objdump -d -M intel ops.o

# Step 6: step through our own code in the debugger (batch mode here; type the
# same commands interactively with "gdb ./ops_demo").
gdb -q -batch \
    -ex 'set disassembly-flavor intel' \
    -ex 'break add_i32' -ex 'run' \
    -ex 'info registers rdi rsi' \
    -ex 'x/3i $pc' \
    -ex 'stepi' -ex 'stepi' \
    -ex 'info registers eax' \
    ./ops_demo

# Step 7: the same program, built by CMake (which runs nasm for us).
run cmake -S . -B build-gcc -G Ninja -DCMAKE_CXX_COMPILER=g++
run cmake --build build-gcc
run ./build-gcc/rooster
