# Chapter 8 Quiz - Intro to Assembly

20 multiple-choice questions covering **Chapter 8 (Intro to Assembly)**: memory and
the CPU, virtual addresses, how a variable, an `if`, a loop, a function call, a
reference, `inline`/`constexpr` and recursion look in assembly, the tools for seeing
it on your own machine, and the assembly lab. Each question is followed immediately
by its correct answer and a short explanation.

---

### 1. A CPU is described as "64-bit". What does that number describe?

A. How many bytes one memory address names
B. The width of an address (and of the main registers), not the size of the byte it points to
C. The size of the RAM the computer must have
D. How many instructions run per second

**Answer: B** - every address names exactly one byte, on 32-bit and 64-bit CPUs alike. The "bits" are how wide the number that holds the address is, so a wider address can name more bytes.

### 2. How big is `1 GiB`?

A. 1,000,000,000 bytes
B. 1,000,000 bytes
C. 1,073,741,824 bytes, which is 2^30
D. 8,589,934,592 bytes

**Answer: C** - a gibibyte is a power of two (2^30). A gigabyte (`GB`) is the power-of-ten unit, exactly 10^9 bytes, about 7.4% smaller.

### 3. Two different running programs both use the address `0x00007F0000001000`. What happens?

A. The second program crashes, because the address is taken
B. They write over each other's data
C. Nothing odd: each program's addresses are virtual and are translated through its own private mapping, so they land on different physical bytes
D. The operating system refuses to start the second program

**Answer: C** - this is virtual memory. It is also why one program cannot corrupt another's memory just by guessing an address.

### 4. What is `_start`?

A. The first line of your `main` function
B. A function you must declare before using `main`
C. A C++ keyword
D. The program's real entry point: a little startup code that sets things up and then calls `main`

**Answer: D** - the operating system jumps to `_start`, not to `main`. The startup code is linked in for you (part of the C runtime), and the stack is already partly in use when `main` begins.

### 5. What does the register `rsp` hold?

A. The address of the current top of the stack
B. The result of the last function call
C. The size of the stack in bytes
D. The address of the next instruction to run

**Answer: A** - `rsp` is the stack pointer. (The address of the next instruction is held by `rip`, and results come back in `rax`.)

### 6. The same C++ function is compiled once for x86-64 and once for ARM64. What do you expect?

A. Identical assembly, since the C++ is the same
B. Different assembly, because assembly belongs to one specific CPU family
C. The ARM64 version will not compile
D. The x86-64 version will be faster by definition

**Answer: B** - assembly is the language of one instruction set, not of C++. The meaning of the program is the same, but the instructions and registers differ.

### 7. In a `-O0` listing you see `mov DWORD PTR [rbp-4], 5`. What C++ is this most likely to be?

A. A function call
B. A local `int` variable being given the value 5
C. An `if` statement
D. A reference being created

**Answer: B** - an `int` is 4 bytes (`DWORD`), living at an address a fixed distance below `rbp`. At `-O0`, a variable is just a named place in memory, and the `mov` stores the value there.

### 8. An `if (x > 0) { ... }` is compiled to `cmp` followed by `jle skip`. Why `jle` ("jump if less or equal"), when the C++ said `>`?

A. The compiler made a mistake
B. The jump goes over the body, so it is taken when the condition is FALSE
C. `jle` is the only jump instruction on x86-64
D. Because `x` is a signed variable

**Answer: B** - the body sits right after the `jle`, so the code falls straight into it when the condition holds. The jump exists only to skip the body when the condition does not hold, which is why it tests the opposite.

### 9. How does a `while` or `for` loop look in assembly?

A. A special `loop` keyword the CPU provides
B. A copy of the body repeated many times
C. A conditional jump out of the loop, plus a jump backwards to the top
D. A call to a library function

**Answer: C** - a loop is a jump backwards. Test the condition, leave with a forward jump when it fails, otherwise run the body and jump back to the test.

### 10. What do `call` and `ret` do?

A. `call` pushes the address to come back to and jumps to the function. `ret` pops that address and jumps to it
B. `call` copies the function into the caller
C. `ret` ends the whole program
D. They are the same instruction written two ways

**Answer: A** - the return address on the stack is what lets a function return to wherever it was called from, which is also why the same function can be called from many places.

### 11. On Linux with GCC or Clang, `int add(int a, int b)` is called with `add(25, 7)`. Where does the callee find the arguments, and where does it put the answer?

A. Both arguments on the stack, the answer on the stack
B. `ecx` and `edx`, the answer in `ebx`
C. `edi` and `esi`, the answer in `eax`
D. `eax` and `ebx`, the answer in `ecx`

**Answer: C** - the System V convention hands out `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9` for the first six integer arguments and uses `rax` for the result. (MSVC on Windows has its own convention, starting with `rcx` and `rdx`.)

### 12. What is the assembly-level difference between `void f(int n)` and `void f(int& n)`?

A. None, a reference is only a naming convention
B. The reference version copies `n` twice
C. The reference version must run at `-O0`
D. The reference version receives the ADDRESS of the caller's `int` and follows it each time `n` is used

**Answer: D** - a reference is a hidden pointer. That is how a write through it reaches the caller's variable, where the by-value parameter changes only the function's own copy.

### 13. With `-O2`, a call `cube(3)` to an `inline` function `cube` compiles to `mov eax, 27`. What does that tell you?

A. The compiler pasted the body in and even computed the answer, so there is no call left to see
B. The program is wrong, because `3` appears nowhere
C. `inline` made the function slower
D. The compiler did the math at run time, very fast

**Answer: A** - once the call is gone there is nothing to call. `inline` is a request the optimiser can honour, and with a constant argument, it can fold the arithmetic away as well.

### 14. What does `constexpr` change about a call such as `square_ce(9)` that has literal arguments?

A. The function is always slower at run time
B. The result can be computed while compiling, so only the finished number appears in the program
C. The function can no longer be called from `main`
D. The function is placed on the stack

**Answer: B** - when the arguments are known at compile time, a `constexpr` function can be evaluated by the compiler, and the program contains just the answer.

### 15. What is the sign that a function is recursive, when you look at its assembly?

A. It contains a `jmp`
B. It uses the `rbp` register
C. It never contains `ret`
D. It contains a `call` to its own name

**Answer: D** - each such call pushes a fresh return address and a fresh frame onto the stack, which is also why runaway recursion eventually runs out of stack.

### 16. Which command writes the assembly for `main.cpp` to a text file, with Intel syntax, using GCC?

A. `g++ -c main.cpp`
B. `g++ -S -masm=intel main.cpp -o main.s`
C. `g++ -asm main.cpp`
D. `objdump main.cpp`

**Answer: B** - `-S` stops after producing assembly, and `-masm=intel` asks for the `mov destination, source` order used throughout the chapter. (`/FAs` is the MSVC equivalent.)

### 17. In the lab, `add_i32` is written in `ops.asm` and called from C++. Why are its declarations wrapped in `extern "C"`?

A. It makes the function faster
B. It lets the assembler read the C++ file
C. It tells the C++ compiler not to mangle the names, so the linker looks for plain `add_i32`, which is what the object file made from `ops.asm` contains
D. It is required by the C++ standard for every function

**Answer: C** - without it, the compiler would ask the linker for a mangled name (something like `_Z7add_i32ii`), and the link fails with `undefined reference to 'add_i32(int, int)'`.

### 18. In `sum_array(const int* data, std::size_t count)`, which registers hold the two arguments when the assembly function starts (Linux x86-64)?

A. `data` in `rdi`, `count` in `rsi`
B. `data` in `rax`, `count` in `rbx`
C. `data` in `rsi`, `count` in `rdi`
D. Both are on the stack

**Answer: A** - arguments are handed out in order: the first in `rdi`, the second in `rsi`. A pointer and a `size_t` are 64 bits wide, so the full registers are used.

### 19. Your assembly function wants to use `rbx` for its own purposes. What must it do?

A. Nothing, every register is free to use
B. Clear it before each use
C. Push it at the start and pop it before `ret`, because `rbx` belongs to the caller
D. Use only `eax`, always

**Answer: C** - `rbx`, `rbp` and `r12` to `r15` must come back unchanged. `rax`, `rcx`, `rdx`, `rsi` and `rdi` are scratch registers, free to overwrite.

### 20. Which tool turns hand-written assembly (`ops.asm`) into an object file you can link with C++?

A. `nasm -f elf64 ops.asm -o ops.o`
B. `g++ -S ops.asm`
C. `cmake --build`, with no other tools
D. `objdump -d ops.asm`

**Answer: A** - an assembler (`nasm`) translates assembly text into an object file. The linker then joins it with the C++ objects, exactly as in 7.12. (`objdump -d` goes the other way: it reads an object file and shows the assembly.)
