# Modules

Since chapter 6 you have shared code between files with `#include`. It works, it is what every C and C++ program you will read was built with, and in this chapter we look at what it costs, and at the replacement C++20 added: **modules**.

```
   headers (what you have used)                 modules (this chapter)
   ─────────────────────────────                ────────────────────────────────────────
   #include "canvas.h"                          import render;
   the compiler PASTES the text, again,         the compiler reads a pre-compiled description
   into every file that includes it             of the module, built once

   everything in the header leaks in:           only what the module EXPORTS is visible:
   macros, helper names, the includes           no macros, no private names
   of the header itself
```

A module is a **named unit of code that is compiled once**. The compiler writes its result to a file (a *built module interface*, BMI), and every file that says `import name;` reads that file instead of pasting text. That one change fixes the three things this chapter starts with: the time, the leaks, and the dependence on the order of includes.

The chapter, in order:

1. **What is wrong with headers** (17.2): measured, and with the real errors.
2. **Your first module** (17.3): `export module`, `export`, `import`, and how CMake builds it.
3. **Modules that use the standard library** (17.4): the global module fragment, and the split into an interface and an implementation unit.
4. **Partitions** (17.5): one module in several files, with parts that stay private.
5. **`import std;`** (17.6): the whole standard library as a module. It gets its own lecture because it is where the speed is.
6. **Migrating** (17.7): wrapping a header you already have, and what the compilers do not support yet.
7. **How the build works** (17.8): the order, and what is rebuilt after an edit.
8. A **project** (17.9): the shape renderer of chapter 11, converted to modules, built three ways, with the times of all three.

## What works where

Everything in this chapter was built and run on MSVC (19.51), GCC 16 and Clang 21 with CMake and Ninja. The toolchains are young, so here is the honest table first:

| | MSVC | GCC 16 | Clang 21 |
|---|---|---|---|
| named modules, `export`, `import` through CMake | works | works | works |
| partitions and implementation units | works | works | works |
| private module fragment (`module :private;`) | works | **not accepted** | works |
| `import std;` through CMake | works (experimental switch) | works (we add the std module source) | works with **libc++** (same way) |
| header units (`import <vector>;`) | partly (see 17.7) | needs a manual step | not tried |

The programs of the chapter print **identical output on the three compilers**.

CMake needs to be **3.28 or newer** for modules, and **3.30** for the `import std;` support we use on MSVC. The course uses 3.30.2 on Windows and 3.31.6 in the Linux images. When CMake prints "support for `import std;` is experimental", that is the experiment; the warning can be silenced with `-Wno-dev`.

---

## 17.2 What is wrong with headers

In this lecture we measure the cost of `#include`, and meet two problems that no amount of `#pragma once` fixes.

### 1. The text is read again, in every file

`#include` is copy-paste (6.11). Look at how much text a single include pastes. The program is one line, `int main() {}`, plus one include; the numbers are the lines left after the preprocessor has done its work (GCC `-E`, MSVC `/P`):

```
   file contains                    GCC       Clang      MSVC
   ────────────────────────────    ───────   ───────   ───────
   nothing                               7         8         2
   #include <vector>                31,022    27,779    37,218
   #include <algorithm>             36,760    32,002    46,324
   #include <ranges>                57,149    53,376    47,374
   #include <print>                 67,222    65,465    64,606
   print, ranges, algorithm,
   vector, string and map           96,539    89,184    91,809
```

A program that includes `<print>` is, to the compiler, a **sixty-five thousand line program** before the first line of yours. And the compiler reads those lines again for **every source file** that includes it: a project with a hundred files parses `<print>` a hundred times. Include guards (`#pragma once`) stop the same header being pasted twice into **one** file. They do nothing about the next file.

### 2. A header is not self-contained

Here is `report.h`:

```cpp
#pragma once

inline std::string label_for(double celsius) {
    return celsius > 20.0 ? "warm" : "cool";
}
```

It uses `std::string` and does not include `<string>`. In `main.cpp` it works:

```cpp
#include <print>                   // this header happens to bring std::string in

#include "report.h"
```

because `<print>` includes `<string>` on all three of our compilers. Swap the two lines, so `report.h` comes first, and it stops compiling:

```
GCC:    error: 'string' in namespace 'std' does not name a type
Clang:  error: use of undeclared identifier 'std'
```

Nothing in `report.h` said what it needs, and another version of the library may include its headers in another order. A header works or not depending on **what was included before it**.

### 3. A header leaks

`settings.h` means well:

```cpp
#define WARM 25
#define COLD 5
```

A macro does not respect scope, namespaces or the file it was written in. From that line on, **every `WARM` in the file is the number 25**. Declare an enumeration that happens to use the same word:

```cpp
enum class Mode { COLD, WARM, HOT };       // the compiler sees { COLD, 25, HOT }
```

```
GCC:    error: expected identifier before numeric constant
Clang:  error: expected identifier
MSVC:   error C2059: syntax error: 'constant'
```

The error lands on a line of yours that looks perfectly fine. The same happens with any helper name or macro a header happens to define: it ends up in your file.

### What a module changes

```
   header                                        module
   ──────                                        ──────
   parsed again in every file                    compiled ONCE into a file; importers read that
   whatever it includes leaks into you           only what is exported is visible
   macros leak                                   macros never cross
   works depending on include order              imports can come in any order
```

The rest of the chapter shows how, and what it costs to get there.

**Code for this lecture**: `17.2WhyHeadersHurt/` (`main.cpp`, `report.h`, `settings.h`).

---

## 17.3 Your first module

In this lecture we write a module, export a few names, and let CMake build it.

### The module interface file

A **module interface unit** is a source file that defines a module. Here is `station.cppm`:

```cpp
export module station;                 // this file defines the module called "station"

#define STATION_WARM_LIMIT 25.0        // a macro in a module stays in the module

export struct Reading {
    int hour;
    double celsius;
};

export constexpr double warm_limit{STATION_WARM_LIMIT};

export double to_fahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

// Not exported: a detail of the module that importers cannot even name.
double calibration_offset() {
    return 0.5;
}

export double calibrated(double celsius) {
    return celsius + calibration_offset();
}

export bool is_warm(const Reading& reading) {
    return calibrated(reading.celsius) >= STATION_WARM_LIMIT;
}
```

- **`export module station;`** is the module declaration. It must be the first thing in the file (we will put something before it in 17.4, with a special meaning).
- **`export`** in front of a declaration makes it visible to the code that imports the module. Anything without it is **private to the module**. `calibration_offset()` is used by `calibrated()` inside the module, and cannot be called from outside.
- Functions defined in the interface (`to_fahrenheit` and the others) are ordinary functions; a function that is exported and defined in the interface does not need `inline`.

The file extension is not fixed by the language. We use `.cppm`, which works with the three compilers through CMake (MSVC's own default is `.ixx`).

### Using it

```cpp
#include <print>

import station;                    // instead of #include "station.h"

int main() {
    Reading noon{12, 24.7};
    Reading morning{6, 11.0};

    std::println("noon is {} F, calibrated {} C", to_fahrenheit(noon.celsius), calibrated(noon.celsius));
    std::println("warm limit is {}", warm_limit);
    std::println("noon is warm: {}   morning is warm: {}", is_warm(noon), is_warm(morning));
    return 0;
}
```

```
noon is 76.46 F, calibrated 25.2 C
warm limit is 25
noon is warm: true   morning is warm: false
```

`import station;` takes the place of `#include`, and it comes **after** the `#include`s of the file (put includes first, imports after).

### What stays private

Two lines in `main.cpp` are commented out. Try them:

```cpp
std::println("{}", calibration_offset());      // not exported
std::println("{}", STATION_WARM_LIMIT);        // a macro
```

```
GCC:    error: 'calibration_offset' was not declared in this scope
Clang:  error: use of undeclared identifier 'calibration_offset'
MSVC:   error C3861: 'calibration_offset': identifier not found

GCC:    error: 'STATION_WARM_LIMIT' was not declared in this scope
Clang:  error: use of undeclared identifier 'STATION_WARM_LIMIT'
MSVC:   error C2065: 'STATION_WARM_LIMIT': undeclared identifier
```

Both messages say "this name does not exist here", because for the importer it really does not. The module can hand the **value** of a macro on, as `warm_limit` does with a constant, but the macro itself never crosses the boundary.

### Telling CMake

```cmake
cmake_minimum_required(VERSION 3.28)       # CMake understands C++ modules from 3.28 on

add_executable(rooster main.cpp)

target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        station.cppm
)
```

An interface file is not an ordinary source: CMake must **scan** it to learn which module it defines, and compile it **before** the files that import it. Listing it in a `FILE_SET` of type `CXX_MODULES` tells CMake that. Build it as always (`cmake -S . -B build -G Ninja`, `cmake --build build`). Behind the scenes the compiler writes a BMI for each module (a `.gcm` file with GCC, `.pcm` with Clang, `.ifc` with MSVC) and the importers read it.

### The pattern to remember

> **`export module name;` starts a module, `export` chooses what importers see, `import name;` replaces `#include`. Macros and unexported names stay inside.**

**Code for this lecture**: `17.3FirstModule/` (`station.cppm`, `main.cpp`, `CMakeLists.txt`).

---

## 17.4 Modules and the standard library

In this lecture the module uses `std::string` and `std::vector`. That needs two new pieces: the **global module fragment**, and the split of a module into an **interface** and an **implementation**.

### The global module fragment

A module that needs a standard header cannot simply write `#include` below `export module`: the declarations of the header would become part of the module. Instead, `#include`s go in the **global module fragment**: the part of the file between `module;` and the module declaration.

```cpp
module;                                // start of the global module fragment

#include <string>
#include <vector>

export module stations;                // the module begins here
```

Inside it, `#include` works exactly as in any source file: it is textual inclusion, nothing more. It is the bridge to the world of headers, and we will use it again to wrap old code in 17.7.

### Interface and implementation

The **interface** says what the module offers. The **implementation unit** is an ordinary-looking `.cpp` file that starts with `module stations;` (no `export`) and defines the functions. It sees everything of the interface, exported or not, and nobody imports it.

`stations.cppm`, the interface:

```cpp
module;

#include <string>
#include <vector>

export module stations;

export struct Station {
    std::string name;
    std::vector<double> readings;
};

// DECLARATIONS only. The bodies are in stations.cpp.
export double mean_of(const Station& station);
export double largest_of(const Station& station);

// A template must be defined in the interface.
export template <typename T>
T clamped(T value, T low, T high) {
    return value < low ? low : (value > high ? high : value);
}

// `export { ... }` exports everything inside the braces.
export {
    Station make_station(std::string name, std::vector<double> readings);
    bool is_empty(const Station& station);
}
```

`stations.cpp`, the implementation unit:

```cpp
module;

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

module stations;

static bool has_readings(const Station& station) {         // private to this file
    return !station.readings.empty();
}

double mean_of(const Station& station) {
    if (!has_readings(station)) {
        return 0.0;
    }
    double total{std::accumulate(station.readings.begin(), station.readings.end(), 0.0)};
    return total / static_cast<double>(station.readings.size());
}
...
```

Why split at all? Exactly as with a header and a `.cpp` (6.11): the importers depend on the **interface**, not on the bodies. Change a body in `stations.cpp` and only that file is recompiled (17.8 shows it).

Why must the template stay in the interface? For the reason of 6.13: whoever instantiates `clamped<int>` needs its body.

The CMake file has the interface in the file set and the implementation unit on the `add_executable` line, since it is an ordinary source:

```cmake
add_executable(rooster main.cpp stations.cpp)
target_sources(rooster PRIVATE FILE_SET CXX_MODULES FILES stations.cppm)
```

```
north: mean 21.33, largest 24
north is empty: false   silent is empty: true
clamped(35, 0, 30)       = 30
clamped(-4.5, 0.0, 30.0) = 0
after push_back: 4 readings
```

### Every unit includes what it uses

Look again at the includes of `stations.cpp`: it has `<string>` and `<vector>` even though the interface already includes them. Our first version did not, and the build failed:

```
GCC:    error: 'string' is not a member of 'std'
Clang:  error: missing '#include <bits/stl_vector.h>'; 'vector' must be declared before it is used
```

The implementation unit sees the *declarations* of the interface, including `Station` with its `std::string` and `std::vector` members, but the **names** `std::string` and `std::vector` are not visible in a file that did not include them. **Each module unit includes the headers it uses itself**, as every source file always had to.

A related fact, in the other direction: a type that comes through a module can be *used* without being *named*. In `main.cpp`:

```cpp
north.readings.push_back(30.0);        // works, although main.cpp never included <vector>
```

but writing `std::vector<double> mine;` in that file fails on GCC (`'vector' is not a member of 'std'`) and Clang (`missing '#include <bits/stl_vector.h>'`). The standard calls the first situation *reachable* and the second *visible*. (MSVC is more lenient and accepted the second line too; do not rely on that.) The simple rule: include or import what you **name**.

### The pattern to remember

> **Standard headers go in the global module fragment (`module;` ... `export module`). The interface declares, the implementation unit defines, templates stay in the interface, and every unit includes what it uses.**

**Code for this lecture**: `17.4ModulesAndTheStandardLibrary/` (`stations.cppm`, `stations.cpp`, `main.cpp`).

---

## 17.5 Partitions

In this lecture one module is split over several files, with some parts visible to importers and some not.

A module can grow large. A **partition** is a named piece of a module: `forecast:model` is the piece `model` of the module `forecast`. Our module `forecast` has these files:

```
   forecast            the PRIMARY interface        (forecast.cppm)
     ├── :model        interface partition          (model.cppm)             Reading, Series
     ├── :stats        interface partition          (stats_interface.cppm)   mean_of, spread_of
     └── :detail       INTERNAL partition           (detail.cppm)            square()
   stats.cpp           implementation unit          (module forecast;)
```

### The primary interface decides

Exactly one file defines the module without a colon. It lists which partitions the module re-exports:

```cpp
export module forecast;

export import :model;              // everything :model exports becomes part of forecast
export import :stats;
// :detail is NOT listed: it is for the module's own files only.
```

`export import` means "import it, and pass it on to my importers". Without `export`, the primary would use the partition and the importers would not see it.

### Interface partitions

```cpp
module;
#include <vector>
export module forecast:model;      // "export module", then module:partition

export struct Reading { int hour; double celsius; };
export struct Series { std::vector<Reading> readings; };
```

A partition that uses another one says `import :model;` (just the colon and the name).

### An internal partition

```cpp
module forecast:detail;            // no `export`

double square(double x) { return x * x; }
```

A partition without `export` in front of `module` is **internal**. The other files of the module can import it, and no importer of `forecast` ever can. It is where helpers live that you want to share between your own files without offering them to the world. `stats.cpp` uses it:

```cpp
module forecast;                   // implementation unit of the whole module
import :detail;                    // available here, not to importers
```

### Using it

```cpp
#include <print>

import forecast;                   // the whole module: model and stats, not detail

int main() {
    Series north{{{6, 11.5}, {12, 18.5}, {18, 15.0}, {24, 12.0}}};
    std::println("north: mean {:.2f}, spread {:.2f}", mean_of(north), spread_of(north));
    return 0;
}
```

```
north: mean 14.25, spread 2.80
```

Two things must **not** work, and here are the real messages. First, importing a partition from outside:

```cpp
import forecast:model;                // in main.cpp
```
```
GCC:    error: expected ';' before ':' token
Clang:  error: expected ';' after module name
MSVC:   error C2143: syntax error: missing ';' before ':'
```

An importer always imports the whole module. Partitions are an organization tool for the module's author, not an interface. Second, using the internal one:

```cpp
std::println("{}", square(3.0));      // square() lives in an internal partition
```
```
GCC:    error: 'square' was not declared in this scope
MSVC:   error C3861: 'square': identifier not found
```

### A rule for the next lectures

An interface partition should not import an internal partition: its interface would then depend on something its importers cannot see. Clang warns about it (`-Wimport-implementation-partition-unit-in-interface-unit`). **Only implementation units import internal partitions.** That is why `square` is used in `stats.cpp` and not in `stats_interface.cppm`.

The interface of `:stats` is in `stats_interface.cppm`, so that it is not mistaken for the implementation unit `stats.cpp`. The file names are free: only the `module` line says what a file is.

### The pattern to remember

> **A partition is a piece of a module. The primary interface re-exports (`export import :part;`) what the world should see. A partition without `export` is internal and is imported only by the module's implementation units.**

**Code for this lecture**: `17.5Partitions/`.

---

## 17.6 `import std;`

In this lecture we replace every `#include` of the standard library by one line, and see what it takes to build.

C++23 defines a module named `std` that exports everything in the `std::` namespace. No headers:

```cpp
import std;                        // the whole standard library, in one line

int main() {
    std::vector<double> temperatures{18.5, 24.0, 21.5, 12.0};
    std::ranges::sort(temperatures);

    std::map<std::string, double> latest{{"north", 18.5}, {"south", 24.0}};
    std::optional<double> missing;

    std::println("sorted: {} .. {}", temperatures.front(), temperatures.back());
    std::println("south is {}", latest.at("south"));
    std::println("missing has a value: {}", missing.has_value());
    std::println("largest int: {}", std::numeric_limits<int>::max());
    std::println("a string of {} letters", std::string{"north"}.size());
    return 0;
}
```

```
sorted: 12 .. 24
south is 24
missing has a value: false
largest int: 2147483647
a string of 5 letters
```

There is **no** `#include` in this file: `vector`, `map`, `optional`, `ranges::sort`, `println`, `numeric_limits` and `string` all came with the one import. In new code this is what you will want to write. The rest of the lecture is the price of being early.

### What `import std;` does not give you

Macros do not cross a module boundary (17.3), and the standard library has some:

```cpp
std::println("{}", INT_MAX);              // a macro of <climits>
assert(temperatures.size() > 0);          // a macro of <cassert>
```

Neither is available after `import std;` on any of the three compilers. Use `std::numeric_limits<int>::max()` and `static_assert`, or `#include` the header.

The C library is the same: the `std::` names are there, the global ones are not. `printf` is not available on all three. If you need the old global names, `import std.compat;` exports them as well. And an unqualified `size_t` is rejected by GCC and Clang after `import std;` (MSVC accepts it): write `std::size_t`.

### Building it: one more module

`import std;` is a module like yours: someone has to compile it once. The standard library ships its source, and the compilers differ in who does the work. **With CMake**:

| | what to do |
|---|---|
| MSVC | CMake 3.30 does it for you, behind an experimental switch |
| GCC 16 | add GCC's module source `std.cc` to the target as one more module |
| Clang 21 | add libc++'s `std.cppm` as one more module, and use libc++ (`-stdlib=libc++`) |

The switch for MSVC is a fixed identifier set before `project()`. It is a placeholder that changes with CMake versions, so check the documentation of yours:

```cmake
cmake_minimum_required(VERSION 3.30)

if(CMAKE_HOST_WIN32)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
endif()

project(rooster)
set(CMAKE_CXX_STANDARD 23)

include(import-std.cmake)

add_executable(rooster main.cpp)
target_use_import_std(rooster)
```

`target_use_import_std` is a small function of ours, in `import-std.cmake`; open it and read it. On MSVC it sets one property (`CXX_MODULE_STD ON`). On GCC it asks the compiler where the module source is (`g++ -print-file-name=libstdc++.modules.json`), on Clang it looks in libc++'s directory, and then it adds the file with `target_sources(... FILE_SET CXX_MODULES ...)`. CMake prints a warning that `import std` is experimental; `-Wno-dev` silences it.

The first build compiles the standard library module, which takes a few seconds (3 to 4 on MSVC). **That is done once**: later builds reuse it, until you clean.

### Building it by hand

Without CMake, GCC needs two commands:

```
g++ -std=c++23 -fmodules -fsearch-include-path -c bits/std.cc       # builds gcm.cache/std.gcm, once
g++ -std=c++23 -fmodules main.cpp -o rooster
```

and Clang two as well, with a precompiled module file in between:

```
clang++ -std=c++23 -stdlib=libc++ -Wno-reserved-module-identifier --precompile -o std.pcm /usr/lib/llvm-21/share/libc++/v1/std.cppm
clang++ -std=c++23 -stdlib=libc++ -fmodule-file=std=std.pcm main.cpp std.pcm -o rooster
```

`build-gcc.sh` and `build-clang.sh` have them (the path to `std.cppm` is where the course image keeps it). Clang needs libc++ because libstdc++ does not provide a module source Clang can read.

On MinGW (GCC 14.2 and Clang 19.1 in `C:\mingw64`), `import std;` is not available: use MSVC on Windows or the Linux images.

### The pattern to remember

> **`import std;` replaces every standard `#include`, gives you names but never macros, and has to be built once per project. In new code it is the default.**

**Code for this lecture**: `17.6ImportStd/` (`main.cpp`, `CMakeLists.txt`, `import-std.cmake`, `build-gcc.sh`, `build-clang.sh`).

---

## 17.7 Fragments, header units and migration

In this lecture we bring existing headers into the world of modules, and finish the list of pieces of a module file.

### Wrapping a header you have

Rewriting a whole code base at once is not realistic. The first step of a **migration** is a module that wraps what exists, so the importers can already say `import`. We have an old header:

```cpp
// legacy.h
#pragma once
#define LEGACY_VERSION 3

struct Calibration { double offset; double scale; };
double celsius_to_kelvin(double celsius);
double apply(const Calibration& calibration, double raw);
```

and its `legacy.cpp`. They are **not changed**. A module file includes the header in its global module fragment and exports the names it wants:

```cpp
module;

#include "legacy.h"                  // global module fragment: the header, as it is

export module legacy;

export using ::Calibration;
export using ::celsius_to_kelvin;
export using ::apply;

export constexpr int legacy_version{LEGACY_VERSION};
```

`export using ::name;` takes a name that already exists (`::name` is "the one in the global scope") and makes it part of the interface. The header and the module both exist: old code keeps `#include`ing the header, new code writes `import legacy;`.

The macro is the usual exception: `LEGACY_VERSION` stays behind, and the module hands over its **value** as a constant. In CMake `legacy.cpp` is an ordinary source on the `add_executable` line, and `legacy_module.cppm` goes in the file set. The program:

```
21.0 raw is 21.5 calibrated
0 C is 273.15 K
the header's version, as a constant: 3
```

Over time the code moves from the header and the `.cpp` into the module, and the wrapper disappears.

### The private module fragment

A module can be written in **one file**, with the interface at the top and the implementation hidden at the bottom:

```cpp
export module single;

export int twice(int x);

module :private;                   // everything below is invisible to importers

int twice(int x) {
    return x * 2;
}
```

Everything after `module :private;` is the private module fragment. It is the `.cpp` file inside the same file, and the idea is that changing it does not force importers to rebuild. It prints

```
twice(21) = 42
```

but only on **MSVC and Clang**. GCC 16 stops at that line:

```
GCC:    error: module already declared
```

So the `CMakeLists.txt` of this lecture builds the private-fragment program only when the compiler is not GCC. If GCC is a target, use an implementation unit (17.4) instead: it works on all three and is the usual structure anyway.

### Header units

The last piece of the standard is the **header unit**: `import <vector>;` or `import "legacy.h";` turns an existing header into something compiled once and imported, without wrapping it in a module of your own. It would be the cheapest migration step, and it is the least supported:

- on MSVC, `import <print>;` compiled but failed to link in our tests
- on GCC, the header first had to be compiled by hand into a module file, and our first attempt failed
- CMake does not support header units

So there is no lecture folder for it. If you meet one, remember that macros **do** cross a header unit, which is the exception to the rule of this chapter and the reason it is less clean than a module. For standard headers use `import std;`, for your own headers use the wrapper above.

### The pieces of a module file, in order

```
   module;                          optional: global module fragment, #include goes here
   #include <...>

   export module name;              the module declaration of an interface unit
   module name;                     ... or of an implementation unit (no export)
   export module name:part;         ... or of an interface partition
   module name:part;                ... or of an internal partition

   import other;                    imports
   import :part;

   export ...                       the declarations
   module :private;                 optional: private fragment (not on GCC 16)
```

### The pattern to remember

> **Migrate in steps: wrap the old header (`#include` in the global fragment, `export using`), hand macros over as constants, and later move the code in. Skip header units for now, and avoid the private fragment if GCC is a target.**

**Code for this lecture**: `17.7FragmentsAndMigration/`.

---

## 17.8 How the build works

In this lecture we watch what the build system does, because modules change the **order** of a build, and that is the part that surprises people.

### The order comes from the sources

With headers, every `.cpp` could be compiled in any order, in parallel: the headers were just text. A module has to be compiled **before** the files that import it, since the importers read its built interface. Three modules in a chain:

```cpp
export module units;                         // units.cppm: imports nothing
export constexpr double to_fahrenheit(double celsius) {...}

export module readings;                      // readings.cppm
import units;
export struct Reading {...};                 // uses to_fahrenheit

export module report;                        // report.cppm
import readings;
export int hour_of_warmest(const Reading*, int);
```

and `main.cpp` imports `readings` and `report`. The CMake file lists them **backwards**:

```cmake
target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        report.cppm
        readings.cppm
        units.cppm
)
```

and the build is still right. The log (MSVC, shortened):

```
[1/10] Scanning ...\report.cppm for CXX dependencies
[2/10] Scanning ...\readings.cppm for CXX dependencies
[3/10] Scanning ...\units.cppm for CXX dependencies
[4/10] Scanning ...\main.cpp for CXX dependencies
[5/10] Generating CXX dyndep file CMakeFiles\rooster.dir\CXX.dd
[6/10] Building CXX object CMakeFiles\rooster.dir\units.cppm.obj
[7/10] Building CXX object CMakeFiles\rooster.dir\readings.cppm.obj
[8/10] Building CXX object CMakeFiles\rooster.dir\report.cppm.obj
[9/10] Building CXX object CMakeFiles\rooster.dir\main.cpp.obj
[10/10] Linking CXX executable rooster.exe
```

First CMake **scans** every file (a cheap pass that only reads the `module` and `import` lines) and writes the result into a *dyndep* file, `CXX.dd`. Ninja reads it and gets the order: `units`, `readings`, `report`, `main`, whatever the order of the list. The program prints:

```
warmest hour: 12
at that hour: 75.2 F
```

Two consequences:

```
   units ──► readings ──► report ──► main            a CHAIN cannot use more than one core
```

1. A chain of modules builds **one after the other**. Independent modules build in parallel, a chain does not. The shape of your imports is now a performance decision.
2. **Circular imports are an error.** If `units` imported `report`, there would be no order.

### What is rebuilt after an edit

We changed files and watched what Ninja rebuilt. The results were **identical on MSVC, GCC and Clang**:

| what you edit | what is rebuilt |
|---|---|
| `main.cpp` | `main.cpp` only |
| the body of a function in `report.cppm` (the top of the chain) | `report` and `main` |
| the body of a function in `units.cppm` (the bottom) | `units`, `readings`, `report` and `main`: everything above it |
| the body of a function in an implementation unit (`stations.cpp`) | that one file, plus the link |
| `touch units.cppm`, no change at all | the same four as if you had changed it |

Two things to take from the table. The build compares **timestamps, not content**, so even `touch` rebuilds everything that depends on the file. And a function body in an interface file is part of the interface: change it and every importer is rebuilt, exactly as with a header. **Modules do not make incremental builds smarter than headers.** What they change is the cost of parsing, and the project measures it.

### The files you will see

The compiler writes one built module interface (BMI) per module into the build directory:

| compiler | file |
|---|---|
| GCC | `units.gcm` (in `CMakeFiles/rooster.dir`) |
| Clang | `units.pcm` |
| MSVC | `units.ifc` |

They are not portable and not meant to be edited or shipped: a BMI is valid for one compiler, one version and one set of options. That is why libraries ship module **sources**.

### The pattern to remember

> **Modules are compiled in dependency order, found by scanning. Chains build one at a time, cycles are errors, and an edit to an interface rebuilds everything above it.**

**Code for this lecture**: `17.8HowTheBuildWorks/`.

---

## 17.9 Project: Modularize the shape renderer

The project of this chapter takes the program you finished in 11.12 (a `Canvas` class, a hierarchy of `Shape`s, and a `main` that draws a scene of two weather stations into a PNG) and converts it from headers to modules. Then we build it **three ways** and measure.

```
   headers/          the program of 11.12, unchanged          #include "canvas.h"  ...
   modules/          one module `render`, standard headers still #included
   modules_std/      the same module, with `import std;`
   vendor/           the stb header (6.18), and the one .cpp that compiles it
```

### The conversion

The four headers become four **partitions** of a single module, and the two `.cpp` files become **implementation units**:

```
   color.h       ──►  render:color      color.cppm
   canvas.h      ──►  render:canvas     canvas.cppm        canvas.cpp   (module render;)
   shape.h       ──►  render:shape      shape.cppm
   shapes.h      ──►  render:shapes     shapes.cppm        shapes.cpp   (module render;)

                      render            render.cppm        re-exports the four
```

`render.cppm` is four lines:

```cpp
export module render;

export import :color;
export import :canvas;
export import :shape;
export import :shapes;
```

and `main.cpp` has `import render;` where it had two `#include "..."` lines. Look at what changed inside the partitions, and what did not:

- `class Canvas` is exactly what it was, with `export` in front. Declarations in the interface, bodies in `canvas.cpp`.
- Each partition has a global module fragment with the standard headers it needs (`<vector>`, `<cstdint>`, `<string_view>`, ...) and `import :color;` for the partitions it uses. That replaces the `#include "color.h"` at the top of `canvas.h`.
- `canvas.cpp` says `module render;` instead of `#include "canvas.h"`. It sees everything the interface declares, and has its own `#include`s for the standard headers (17.4).
- The stb library stays a header, in `vendor/`. A third-party header is not ours to convert, and `stb_impl.cpp` is an ordinary source file linked by all three versions.

The `CMakeLists.txt` has one target per version:

```cmake
add_executable(rooster_headers headers/main.cpp headers/canvas.cpp headers/shapes.cpp ...)

add_executable(rooster modules/main.cpp modules/canvas.cpp modules/shapes.cpp)
target_sources(rooster PRIVATE
    FILE_SET CXX_MODULES FILES
        modules/render.cppm
        modules/color.cppm
        modules/canvas.cppm
        modules/shape.cppm
        modules/shapes.cppm
)

add_executable(rooster_std modules_std/main.cpp modules_std/canvas.cpp modules_std/shapes.cpp)
target_sources(rooster_std PRIVATE FILE_SET CXX_MODULES FILES ...)
target_use_import_std(rooster_std)
```

Build and run any of them (the executable of the first is `rooster_headers`):

```
cmake -S . -B build -G Ninja
cmake --build build
./build/rooster
```

```
Group 'scene' (12 shapes)
  Rectangle 400x80
  Circle r=32
  Group 'station' (5 shapes)
  Group 'station' (5 shapes)

wrote scene.png (400 x 300)
```

The output of the three versions is the same. So is the PNG: **byte for byte identical** across the three versions on GCC, Clang and MSVC (we compared the files), and the program is clean under AddressSanitizer and UndefinedBehaviorSanitizer on GCC. Modules changed how the code is organized and built, not what it does.

### The third version

`modules_std/` is `modules/` with the standard `#include`s deleted and `import std;` in their place: in every partition, every implementation unit and `main.cpp`. For example `modules_std/canvas.cppm` begins `export module render:canvas;` and `import std;`, with no global module fragment at all, since there is nothing left to put in it. It is a good exercise to diff the two folders and see how much text disappears.

### The measurements

Now the part you came for. We timed the three versions on all three compilers. The table lists **milliseconds**, the median of three runs, for an unoptimized build (the CMake default) with Ninja. "Touch" means we updated the file's timestamp and rebuilt. The `import std` column of the **clean** build includes building the standard library module, once.

GCC 16:

| | headers | modules | import std |
|---|---|---|---|
| clean build | 1,331 | 3,033 | 4,634 |
| touch `color` (the lowest file) | 1,322 | 2,923 | 1,640 |
| touch `shapes` (the top interface) | 1,297 | 2,218 | 1,280 |
| touch `canvas.cpp` (an implementation unit) | 763 | 801 | 348 |
| touch `main.cpp` | 1,211 | 1,193 | 783 |

Clang 21 (the `import std` column uses libc++, the others libstdc++):

| | headers | modules | import std |
|---|---|---|---|
| clean build | 1,019 | 3,038 | 2,438 |
| touch `color` | 972 | 2,990 | 733 |
| touch `shapes` | 916 | 1,982 | 578 |
| touch `canvas.cpp` | 699 | 619 | 156 |
| touch `main.cpp` | 853 | 809 | 414 |

MSVC 19.51:

| | headers | modules | import std |
|---|---|---|---|
| clean build | 1,433 | 3,185 | 4,726 |
| touch `color` | 1,660 | 3,632 | 1,004 |
| touch `shapes` | 1,394 | 2,047 | 872 |
| touch `canvas.cpp` | 1,035 | 1,031 | 799 |
| touch `main.cpp` | 1,281 | 1,290 | 686 |

The numbers are specific to this machine and this small program, but the **shape** is the same on all three compilers, and it is not what the advertisement says:

1. **Modules with `#include`d standard headers are slower, two to three times, for a clean build.** Every module unit parses `<vector>`, `<string>` and the rest again, as before, and now the partitions form a chain (`color`, `canvas`, `shape`, `shapes`, `render`) that cannot be built in parallel, while the header version compiles its three `.cpp` files side by side.
2. **`import std;` is the one that pays**, but not in the first build: a clean build starts by compiling the whole standard library module (about 3 to 4 seconds on MSVC, and a similar few seconds on GCC and Clang). After that, almost every rebuild is the fastest of the three (the exception is GCC with the lowest file touched: 1,640 ms against 1,322 for headers): touching `canvas.cpp` took 348 ms against 763 with GCC, and 156 against 699 with Clang, because no file parses tens of thousands of lines of standard headers any more.
3. **Where the module sits in a chain matters.** Touching `color`, at the bottom, rebuilt the most; touching `canvas.cpp`, an implementation unit, rebuilt one file. This is the table of 17.8 seen in time.
4. For a program as small as this one, none of it matters in absolute terms. The difference grows with the number of files that include the same big headers, which is why the example is a lesson and not a verdict. A real project with hundreds of files is where parsing cost dominates.

(The numbers come from `compare-builds.ps1` on Windows and `compare-builds.sh` on Linux, which are in the project folder. Run them on your machine and see for yourself.)

### What we learned

- **Convert one header to one partition**, and let the primary interface re-export them. The conversion is mechanical, and it is a good use of an afternoon.
- **Keep implementation units.** They are the cheapest thing to change, and they stayed the fast path in every table.
- **Do not expect modules to speed up a build by themselves.** The gain comes from `import std;` and from many importers sharing one compiled interface. Modules that merely wrap `#include`s can cost time.
- **Check your toolchain first.** The same project needs a gate for MSVC, a source file for GCC, and libc++ for Clang (17.6). It is solvable, and it is why the chapter spent a lecture on it.

### Things to try

1. Add the `Ellipse` class suggested at the end of 11.12 as a new partition `render:ellipse`, re-exported by `render.cppm`. How many files change?
2. Move a helper that only `canvas.cpp` uses into an **internal partition** (17.5).
3. Break the build on purpose: make `render:canvas` import `render:shapes`, which imports `render:canvas`. What does CMake say?
4. Run `compare-builds` with `-O2` (`-DCMAKE_BUILD_TYPE=Release`). Which column wins now?

**Code for this lecture**: `17.9ProjectModularize/` (`headers/`, `modules/`, `modules_std/`, `vendor/`, `CMakeLists.txt`, `import-std.cmake`, `compare-builds.sh`, `compare-builds.ps1`).

---

## 17.10 Assignment

Eight small jobs for the weather station, on the theme of the chapter. This assignment is a little different from the previous ones: most exercises ask you to **write new files** (module files), add them to `CMakeLists.txt`, and then use them from `main()`. The starter `main.cpp` has the exercise statements with the sample output, the `CMakeLists.txt` has the pattern, and `solution/` has the answers.

| # | Exercise | Skill |
|---|---|---|
| 1 | Module `units`: `to_fahrenheit` and `to_kelvin`, with the Kelvin offset in a non-exported function | `export module`, what stays private (17.3) |
| 2 | Module `limits`: `Range`, a `constexpr` `comfortable` and `within()`, with the numbers defined as macros inside the module | `export`, macros stay inside (17.3) |
| 3 | Module `statistics`: interface and implementation unit for `mean_of` and `largest_of` | global module fragment, interface versus implementation (17.4) |
| 4 | Module `clamp`: the template `clamped`. Where must the body be, and why? | templates in interfaces (17.4) |
| 5 | Module `weather` with partitions `:model`, `:detail` (internal) and `:format`, plus an implementation unit | partitions, `export import`, internal partitions (17.5) |
| 6 | A separate program with `import std;` and a module `summary` that uses it | `import std;` in CMake (17.6) |
| 7 | Module `alarms` wrapping a legacy header, with the macro handed over as a constant | `export using`, global module fragment (17.7) |
| 8 | Predict which files are rebuilt after four kinds of edits, then check | the build (17.8) |

How to work:

1. Write the module file(s) in the assignment folder. Add each interface to the `FILE_SET` of `CMakeLists.txt`, and each implementation unit to the `add_executable` line.
2. Add the `import` below the `#include`s of `main.cpp`, and the code under the exercise heading.
3. Build and run. If the compiler complains that a name does not exist, check three things first: is it exported, is the module imported, and did the unit include what it uses.
4. Exercise 6 is a **separate program**: a file that says `import std;` should not also include standard headers. Look at the end of `CMakeLists.txt` for the target pattern.

`main_solution.cpp` builds as the target `rooster_solution` (and `main_std_solution.cpp` as `rooster_solution_std`), with the modules in `solution/`. The solution's output:

```
--- Exercise 1: a first module ---
21.5 C = 70.7 F = 294.65 K

--- Exercise 2: a struct and a constant ---
comfortable range: 18 to 26
22 is comfortable: true   30 is comfortable: false

--- Exercise 3: interface and implementation ---
mean 19.00, largest 24

--- Exercise 4: a template in a module ---
clamped(35, 0, 30) = 30   clamped(-4.5, 0.0, 30.0) = 0

--- Exercise 5: partitions ---
6h: 11.5 C, cold
12h: 26 C, warm
18h: 19 C, mild

--- Exercise 7: wrapping a legacy header ---
warning: battery low (levels go up to 3)
```

Exercises 6 and 8 print nothing here: 6 is the second program, `rooster_solution_std`, and 8 is written. The second program prints:

```
--- Exercise 6: import std ---
lowest 12, highest 24, mean 19.00
```

The quiz has 20 questions on the whole chapter: the cost of headers, `export`, the global module fragment, interface and implementation units, partitions, `import std;`, wrapping legacy headers, the order of a build, and the lessons of the project. See `QUIZ.md` in the assignment folder.

That is modules: the replacement for the preprocessor's copy-and-paste that C++20 gave us, and `import std;` that C++23 added on top. They are the way new projects will be written, and you now know how they are built, where they still fall short, and how to measure them. In the next chapter we turn to **coroutines**: functions that can stop in the middle and continue later.

**Code for this lecture**: `17.10Assignment/` (`main.cpp`, `main_solution.cpp`, `main_std_solution.cpp`, `solution/`, `legacy_alarm.h`, `legacy_alarm.cpp`, `QUIZ.md`).
