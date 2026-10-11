# Chapter 17 Quiz - Modules

20 multiple-choice questions covering **Chapter 17 (Modules)**: what is wrong with headers, a
first module and `export`, the global module fragment, interface and implementation units,
partitions, `import std;`, wrapping legacy headers, how the build works, and the lessons of
the modularize project. Each question is followed immediately by its correct answer and a short
explanation.

---

### 1. Why does `#include <print>` make every source file slower to compile?

A. `<print>` contains a lot of machine code that must be linked
B. The compiler has to run the program once before compiling it
C. The compiler reads and parses its tens of thousands of lines again in every source file that includes it
D. `<print>` must be downloaded the first time

**Answer: C** - `#include` is copy-paste (6.11). A file with one line, `#include <print>`, grew to about 65,000 lines before the compiler saw the first line of the program, and every other file that includes it pays the same again.

### 2. A header contains `#define WARM 25`. What does it do to the file that includes it?

A. From that line on, every `WARM` in the file is the number 25, even in places where you meant a name of your own
B. Nothing, because macros respect namespaces
C. It only affects the lines of the header itself
D. It defines a constant that can be used only in `main`

**Answer: A** - a macro does not respect scope or names. An `enum class Mode { COLD, WARM, HOT };` after that include became `{ COLD, 25, HOT }` and failed to compile. Modules do not export macros.

### 3. What does `export` do in a module interface file?

A. It writes the declaration to a header file
B. It makes the function run faster
C. It marks the declaration as thread safe
D. It makes the name visible to code that imports the module; names without it stay private to the module

**Answer: D** - in 17.3, `calibration_offset()` was not exported, and a call to it from `main` failed with "not declared", while `calibrated()` (which uses it inside the module) worked.

### 4. A module interface contains `#define STATION_WARM_LIMIT 25.0`. Can the code that imports the module use `STATION_WARM_LIMIT`?

A. Yes, all macros are exported
B. No, macros are never exported; the module can export a constant built from the macro instead
C. Yes, but only in `main`
D. Only if it is also declared with `export`

**Answer: B** - a module is not text that is pasted: macros cannot cross it. In 17.7 the legacy header's macro `LEGACY_VERSION` was handed on as `export constexpr int legacy_version{LEGACY_VERSION};`.

### 5. Why do CMake projects list module interface files in `FILE_SET CXX_MODULES`?

A. So that CMake scans them to learn which module each defines and imports, and compiles them before the files that import them
B. Because module files cannot be compiled otherwise
C. To make them smaller
D. Because Ninja does not know the extension `.cppm`

**Answer: A** - an ordinary source file has no build-order requirements. A module interface must be built first, and CMake works the order out from the scan.

### 6. What is the global module fragment?

A. The part of a module that is exported
B. A place where macros are stored
C. The section between `module;` and `export module name;` where `#include`s of ordinary headers go
D. A second module that every program imports

**Answer: C** - it is textual inclusion, as in any source file, placed before the module declaration so that the header's contents do not become part of the module.

### 7. The interface of module `stations` includes `<string>` and `<vector>`. Its implementation unit `stations.cpp` uses `std::string` but includes neither. What happens?

A. It compiles: the implementation unit sees the interface's includes
B. It does not compile: `std::string` is not visible there, so each module unit must include what it uses
C. It compiles, but slowly
D. It compiles only with Clang

**Answer: B** - GCC said `'string' is not a member of 'std'`, and Clang said `missing '#include <bits/stl_vector.h>'; 'vector' must be declared before it is used`. The names are reachable through the interface but not visible in the other unit.

### 8. Why must the body of a function template be in the module interface?

A. Because modules cannot contain more than one file
B. Because templates are exported by default
C. Because implementation units cannot include headers
D. Because the code that imports the module instantiates the template, so the compiler needs the body, as with a header (6.13)

**Answer: D** - a declaration in the interface with the body in a `.cpp` would leave the importer with nothing to instantiate. Ordinary functions can be split; templates cannot.

### 9. A primary module interface says `export import :model;`. What does it do?

A. Imports a file called `:model`
B. Hides the partition from everybody
C. Makes everything that the partition exports part of the module's own interface, so importers of the module see it
D. Compiles the partition twice

**Answer: C** - the primary interface decides what the module offers by re-exporting the partitions it wants to expose. A partition that is not re-exported, like the internal `detail`, stays inside.

### 10. `module forecast:detail;` has no `export` in front of `module`. Who can see it?

A. Only other files of the module `forecast`, never the code that imports `forecast`
B. Everybody
C. Only `main`
D. Nobody, not even the module

**Answer: A** - it is an internal partition. In 17.5 `stats.cpp` imported it to use `square()`, while a call to `square()` from `main` failed.

### 11. What happens with `import forecast:model;` written in `main.cpp`?

A. It imports only the part called `model`
B. It does not compile: a partition can be imported only inside its own module
C. It compiles but is ignored
D. It imports `model` from the standard library

**Answer: B** - the three compilers report a syntax error ("expected ';' before ':'"). Importers always import the whole module: `import forecast;`.

### 12. What does `import std;` give you?

A. The whole C and C++ standard library, including macros such as `INT_MAX` and `assert`
B. Only the C++ headers that end in `.h`
C. Only `<print>`
D. All the names in `std::`, but no macros and no global C names such as `printf`; `import std.compat;` adds those

**Answer: D** - macros never cross a module boundary, so use `std::numeric_limits` and `static_assert`, or include the header. Unqualified `size_t` was rejected by GCC and Clang after `import std;`, so write `std::size_t`.

### 13. Which statement about `import std;` through CMake in this course is true?

A. It works with all three compilers: MSVC through CMake's experimental switch, and GCC and Clang by adding the library's module source (`std.cc` or `std.cppm`) to the project as one more module, Clang with libc++
B. It works only with MSVC
C. It works only on Linux
D. It needs a different language standard on each compiler

**Answer: A** - that is what `import-std.cmake` does. On MSVC the switch is `CMAKE_EXPERIMENTAL_CXX_IMPORT_STD`, set before `project()`. The first build of the std module takes a few seconds, once.

### 14. A legacy header `legacy.h` declares `celsius_to_kelvin`. The module `legacy` includes it in its global module fragment and says `export using ::celsius_to_kelvin;`. What does that achieve?

A. It copies the function into the module
B. It deletes the header
C. It makes the existing name part of the module's interface, without changing the header or its implementation
D. It renames the function

**Answer: C** - this is the first step of a migration: the header and its `.cpp` stay as they are, and importers can already use `import legacy;`.

### 15. A single-file module ends with `module :private;` followed by the function bodies. In our tests, which compilers accepted it?

A. All three
B. Only GCC
C. Only MSVC
D. MSVC and Clang; GCC 16 rejected it

**Answer: D** - GCC stopped at `module :private;` with "module already declared". The `CMakeLists.txt` of 17.7 builds that program only when the compiler is not GCC.

### 16. You change the body of one function in a module implementation unit (`stats.cpp`). What does the build recompile?

A. Everything
B. Only that file, and then it links again
C. The module interface and every importer
D. Nothing

**Answer: B** - in 17.8's experiment, editing a function body in a `.cpp` file rebuilt only that file. The interface did not change, so the importers are not rebuilt.

### 17. A chain of modules: `report` imports `readings`, which imports `units`, and `main` imports `report`. You change a function body inside `units.cppm` (an interface). What is rebuilt?

A. Only `units`
B. Only `main`
C. `units`, `readings`, `report` and `main`: everything above it in the chain
D. Nothing, because the change is inside a function

**Answer: C** - the body is part of the interface file, and nothing in the build compares contents: even `touch units.cppm` without a change rebuilt all four. The order of the first build is the other way round: `units`, `readings`, `report`, `main`.

### 18. How does CMake know in which order to build the module files?

A. It scans each file to find the module it defines and the modules it imports, and Ninja builds in the order that results
B. By the order of the files in the list
C. Alphabetically
D. You must write the order yourself

**Answer: A** - the order of the `FILE_SET` list does not matter. CMake generates the dependency information (a "dyndep" file) from the scan, and the build log showed `units` first although it was last in the list.

### 19. In the modularize project, Canvas and Shapes became modules but the standard headers were still `#include`d in the global module fragments. What happened to the clean build time?

A. It halved
B. It stayed the same
C. It became random
D. It got slower, two to three times in our tests, on all three compilers

**Answer: D** - every module unit parsed the standard headers again, and the partitions form a chain (`color`, `canvas`, `shape`, `shapes`, `render`) that must be built one after the other, while the header version compiled three `.cpp` files in parallel.

### 20. Why were the rebuilds of the `import std;` version usually faster than those of the header version?

A. Its executable is smaller
B. The standard library is compiled once into a module file, so rebuilding a file no longer parses tens of thousands of lines of standard headers
C. It does not use Ninja
D. It does not link

**Answer: B** - the price was in the first build: the clean build included compiling the standard library module (about 3 to 4 seconds with MSVC, once). After that, touching a `.cpp` file rebuilt faster on every compiler (348 against 763 ms with GCC, for example).
