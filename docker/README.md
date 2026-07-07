# Student build environments

Two ready-to-use containers so you can build and run any chapter in this
course without installing a compiler locally.

| Image | Compiler | Base |
|---|---|---|
| `docker/gcc` | GCC 16.1.0 | `gcc:16` (Docker Official Image, Debian 13) |
| `docker/clang` | Clang 21.1.8 | `silkeh/clang:21` (Debian 13) |

Both images add: CMake, Ninja, git, a debugger (gdb / lldb), a
formatter+linter (clang-format, clang-tidy, cppcheck), two common test
frameworks (Catch2, GoogleTest), and [vcpkg](https://vcpkg.io) for pulling in
any third-party library a future chapter might need.

## Build the images

```sh
docker build -t masterclass-gcc:16 docker/gcc
docker build -t masterclass-clang:21 docker/clang
```

## Use them on a chapter

Every chapter folder already has its own `CMakeLists.txt`. Mount the chapter
folder as `/workspace` and build inside the container — nothing chapter-side
needs to change:

```sh
# from the repo root
docker run --rm -it -v "$(pwd)/45.StlAlgorithms/45.2AllOf:/workspace" masterclass-gcc:16
# inside the container:
cmake -B build -G Ninja .
cmake --build build
./build/rooster
```

Swap `masterclass-gcc:16` for `masterclass-clang:21` and add
`-DCMAKE_CXX_COMPILER=clang++` to the `cmake` call to build the same chapter
with Clang instead.

## Using vcpkg for a chapter that needs a third-party library

Both images have vcpkg pre-bootstrapped at `/opt/vcpkg`, exported as
`$VCPKG_ROOT`. If a chapter needs a library (e.g. `fmt`), add a
`vcpkg.json` manifest next to that chapter's `CMakeLists.txt`:

```json
{
  "name": "chapter-name",
  "version": "0.1.0",
  "dependencies": ["fmt"]
}
```

Then point CMake at vcpkg's toolchain file when configuring:

```sh
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake .
cmake --build build
```

vcpkg reads the manifest, builds/installs the requested libraries into
`<chapter>/vcpkg_installed/` on first configure (this step downloads and
compiles the library, so it takes longer the first time only), and
`find_package(fmt CONFIG REQUIRED)` /
`target_link_libraries(... fmt::fmt)` in `CMakeLists.txt` resolves against
it normally. Verified working end-to-end on both the GCC and Clang images
with `fmt` as the test package.

## Known limitation: Chapter 49 (Modules)

Chapter 49's `.ixx` files are recognized fine by CMake (`FILE_SET
CXX_MODULES`) and module-to-module imports (e.g. `import math_stuff;`)
compile correctly on both GCC 16 and Clang 21.

However, many files in that chapter also use **header-unit imports** —
`import <iostream>;` instead of `#include <iostream>` — and that specific
form currently fails on both compilers in a CMake+Ninja build:

- **GCC 16 / libstdc++**: `fatal error: returning to the gate for a
  mechanical issue` — libstdc++ doesn't yet ship prebuilt header-unit
  modules for the standard library.
- **Clang 21 / libstdc++**: `header file <iostream> ... cannot be imported
  because it is not known to be a header unit` — same underlying gap; Clang
  here links against libstdc++ (not libc++), which doesn't declare header
  units either.
- `import std;` (the C++23 replacement for header imports) was also tested
  and fails on GCC 16 today: CMake explicitly reports *"Toolchain does not
  support discovering `import std` support"* — no prebuilt `std` module
  ships with this libstdc++ yet.

This is a toolchain/library gap, not a container misconfiguration — the
same source will build cleanly on MSVC, which has shipped a prebuilt
`import std;`-capable STL for longer. If you want chapter 49's header-import
examples to build in these Linux containers too, the fix is on the course
content side (e.g. swap `import <iostream>;` for a plain `#include` inside
the module's global module fragment), not the Dockerfiles.
