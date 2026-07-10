# Chapter 2: Environment Setup

## What this chapter is about

Before we write a single lesson in C++, you need somewhere to write code
and something that turns it into a program you can run. Unlike every
chapter after this one, there's no single running example here - every
lecture folder builds the exact same tiny program (a greeting, plus a
printout of which C++ standard and compiler actually built it). The point
of this chapter isn't that program - it's watching the same code get built
by every tool this course supports, on every mainstream operating system,
so you can pick your path once and stop thinking about it.

## What does getting set up actually require?

| Need | Example | Covered in |
|---|---|---|
| Understand the pieces before touching a specific tool | "what's a compiler vs. a linker vs. an IDE?" | 2.2 Meet the Toolchain |
| An IDE and compiler on Windows | Visual Studio + MSVC, or Qt Creator + a Kit | 2.3 Windows |
| An IDE and compiler on Linux | Qt Creator + your system's GCC | 2.4 Linux |
| An IDE and compiler on Mac | Qt Creator + Apple Clang (Xcode Command Line Tools) | 2.5 Mac |
| Know whether your compiler is modern enough | checking cppreference, compiling a feature probe | 2.6 Checking Compiler Support |
| A fallback when it isn't | a containerized, always-up-to-date GCC/Clang | 2.7 Docker |
| Understand what's actually happening under the IDE | CMake, the compiler, and the linker | 2.8 CMake |

## Lecture by lecture

- **2.2 Meet the Toolchain** - the vocabulary every later lecture assumes:
  compiler, linker, build system, and IDE, and how they relate to each
  other. No tool-specific instructions yet - just the mental model.
- **2.3 Windows: Visual Studio and Qt Creator** - installing Visual Studio
  Community with the Desktop C++ workload (MSVC), and Qt Creator with a
  Kit (MSVC, MinGW, or LLVM/Clang) as the alternative. Different kits
  bring genuinely different compilers with different levels of modern
  C++ support.
- **2.4 Linux: Qt Creator** - the recommended IDE, and the gotcha that Qt
  Creator picks your system's already-installed GCC by default, which
  may be older than this course needs.
- **2.5 Mac: Xcode and Qt Creator** - separating the compiler (Apple
  Clang, installed via the lightweight Xcode Command Line Tools) from
  the IDE (we still recommend Qt Creator over the full Xcode app), plus
  the same "your default compiler might be old" gotcha as Linux.
- **2.6 Checking What Your Compiler Supports** - using
  [cppreference's compiler support table](https://en.cppreference.com/w/cpp/compiler_support),
  the `-std=c++23` / `/std:c++latest` flags, and a small "feature probe"
  program (this lecture's `main.cpp`) that only compiles on a modern
  enough toolchain - so a compiler error tells you exactly what's
  missing, instead of guessing from a version number.
- **2.7 Docker: When Your Compiler Is Too Old** - the escape hatch. This
  course ships two ready-made images, `masterclass-gcc:16` and
  `masterclass-clang:21`, so you can build and run every lecture without
  installing anything locally or risking your existing setup.
- **2.8 CMake: The Ground Beneath the Code** - what CMake actually is (a
  build system *generator*, not a compiler), how `cmake -B build` and
  `cmake --build build` map to the compiler and linker, and where the
  `rooster`/`rooster.exe` executable every lecture produces comes from.

## How C++'s latest features help

This chapter is about tooling rather than language features, but the
starter program every lecture builds already leans on the same modern
conventions used everywhere else in this course:

- **`std::print` / `std::println`** (C++23) for output, from the very
  first `main.cpp` in 2.2.
- **`__cplusplus`**, checked at compile time, to show students concretely
  which standard their toolchain is actually targeting - not just told,
  but printed by their own build.
- **Concepts** (C++20), used in 2.6's feature-probe program specifically
  *because* they're recent enough to fail loudly on an under-supported
  compiler - which is the point of that lecture.

## Building the code

Every lecture folder in this chapter has its own `CMakeLists.txt`,
`build-gcc.sh`, and `build-clang.sh`, same as every other chapter. If your
local Visual Studio, Qt Creator Kit, or system compiler isn't new enough
(see 2.6), use one of the ready-made Docker images in
[`../docker`](../docker) - see that folder's README for exact commands.
