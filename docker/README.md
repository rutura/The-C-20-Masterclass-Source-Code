# Student build environments

Two ready-to-use containers so you can build and run any chapter in this
course without installing a compiler locally. Pick one — each section below
is self-contained. Nearly every command is identical on Windows and
Linux/macOS; the one line that differs (the `docker run` mount path) is
shown for both.

| Image | Compiler | Base |
|---|---|---|
| `docker/gcc` | GCC 16.1.0 | `gcc:16` (Docker Official Image, Debian 13) |
| `docker/clang` | Clang 21.1.8 | `silkeh/clang:21` (Debian 13) |

Both images include the same tool set: CMake, Ninja, git, a debugger
(gdb / lldb), a formatter+linter (clang-format, clang-tidy, cppcheck), two
test frameworks (Catch2, GoogleTest), and [vcpkg](https://vcpkg.io) for
pulling in third-party libraries a future chapter might need.

---

# GCC

## Build the image

Run from the repo root (same command on every OS):

```sh
docker build -t masterclass-gcc:16 docker/gcc
```

## Build and run a chapter

Every chapter folder already has its own `CMakeLists.txt`. Mount the
chapter folder as `/workspace` and build inside the container — nothing
chapter-side needs to change. Example uses `45.StlAlgorithms/45.2AllOf`;
substitute any chapter path. Run from the repo root — the only thing that
changes across hosts is how you write the mount path:

```powershell
# Windows (PowerShell)
docker run --rm -it -v "${PWD}\45.StlAlgorithms\45.2AllOf:/workspace" masterclass-gcc:16
```

```sh
# Linux / macOS
docker run --rm -it -v "$(pwd)/45.StlAlgorithms/45.2AllOf:/workspace" masterclass-gcc:16
```

Then, inside the container (identical from here on, regardless of host —
the container is always Linux):

```sh
cmake -B build -G Ninja .
cmake --build build
./build/rooster
```

(Replace `rooster` with whatever `add_executable(...)` name that chapter's
`CMakeLists.txt` uses.)

## Using vcpkg with GCC

vcpkg is pre-bootstrapped at `/opt/vcpkg` inside the image, exported as
`$VCPKG_ROOT`. Add a `vcpkg.json` manifest next to the chapter's
`CMakeLists.txt`:

```json
{
  "name": "chapter-name",
  "version": "0.1.0",
  "dependencies": ["fmt"]
}
```

Then, inside the container, configure with the vcpkg toolchain file:

```sh
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake .
cmake --build build
```

vcpkg reads the manifest and builds/installs the requested libraries on
first configure (slower the first time only), and
`find_package(fmt CONFIG REQUIRED)` /
`target_link_libraries(... fmt::fmt)` in `CMakeLists.txt` resolves against
it normally. Verified working end-to-end with `fmt` as the test package.

---

# Clang

## Build the image

Run from the repo root (same command on every OS):

```sh
docker build -t masterclass-clang:21 docker/clang
```

## Build and run a chapter

Same idea as GCC: mount the chapter folder as `/workspace`. The only
difference from GCC is you must tell CMake to use `clang++` explicitly. Run
from the repo root — the only thing that changes across hosts is how you
write the mount path:

```powershell
# Windows (PowerShell)
docker run --rm -it -v "${PWD}\45.StlAlgorithms\45.2AllOf:/workspace" masterclass-clang:21
```

```sh
# Linux / macOS
docker run --rm -it -v "$(pwd)/45.StlAlgorithms/45.2AllOf:/workspace" masterclass-clang:21
```

Then, inside the container (identical from here on, regardless of host —
the container is always Linux):

```sh
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++ .
cmake --build build
./build/rooster
```

(Replace `rooster` with whatever `add_executable(...)` name that chapter's
`CMakeLists.txt` uses.)

## Using vcpkg with Clang

Same as GCC — vcpkg is pre-bootstrapped at `/opt/vcpkg` (`$VCPKG_ROOT`) in
this image too. Add the same `vcpkg.json` manifest shown above, then
configure with both the compiler and toolchain flags:

```sh
cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake .
cmake --build build
```

Verified working end-to-end with `fmt` as the test package.

---

## Known limitation: Chapter 49 (Modules)

Chapter 49's `.ixx` files are recognized fine by CMake (`FILE_SET
CXX_MODULES`) and module-to-module imports (e.g. `import math_stuff;`)
compile correctly on both images above.

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
