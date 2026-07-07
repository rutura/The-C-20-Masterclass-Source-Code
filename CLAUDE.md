# The C++20/23 Masterclass — Source Code

This repo is the source code companion to a **video course** teaching C++
from first principles up through modern C++20/23. Each numbered top-level
folder (`03.FirstSteps`, `04.VariablesAndDatatypes`, `05.OperationsOnData`,
...) is a chapter; each subfolder inside a chapter (e.g. `4.3IntegerTypes`)
is one recorded lecture, with its own `main.cpp` and `CMakeLists.txt`.

Because this is a course, changes here are not just "fix the code" - they
affect what an instructor says on camera and what a student sees when they
open a folder. Treat lecture folders and their ordering as content, not just
source files.

## What "modernizing a chapter" means

Several early chapters were written before C++23 and use dated style
(`std::cout <<`, `std::endl`, `using namespace std`, verbose/dry
enumeration of every type spelling). When asked to modernize a chapter,
follow the approach used for chapter 4 (`04.VariablesAndDatatypes`) and
chapter 3 (`03.FirstSteps`):

1. **One running example per chapter, built up lecture by lecture.**
   Don't write disconnected toy snippets per lecture - pick a single relatable
   scenario (chapter 3: a personal profile; chapter 4: a personal expense
   tracker) and let each lecture add to the same variables/functions the
   previous lecture introduced. This mirrors how the course is actually
   taught on video: continuity matters more than each file being a minimal
   isolated example.
2. **Consolidate lectures where the split no longer earns its keep.**
   If two lectures are really one idea artificially split (e.g. old
   `IntegerTypes` + `IntegerModifiers`, or `Auto` + `Assignments`), merge them
   and renumber the remaining folders so numbering stays sequential (no gaps).
   Always confirm the consolidation plan with the user before renaming
   folders - it's a structural change to recorded content, not just code.
3. **Prefer problem-solving over exhaustive enumeration.** Don't dump every
   `signed short int` / `unsigned long long int` spelling back-to-back with
   no narrative. Introduce a type because the running example needs it
   ("this number can get into the billions, so..."), not because it exists.
4. **Add a chapter-root `README.md`** once a chapter is modernized, following
   the structure used in `03.FirstSteps/README.md` and
   `04.VariablesAndDatatypes/README.md`:
   - a short intro to the running example
   - a "what does this program actually need" table mapping needs to C++
     concepts/types
   - a lecture-by-lecture summary
   - a "how C++'s latest features help" section calling out what's genuinely
     new/better versus how an older course would have taught the same idea
   - (if applicable) a capstone project section
   - a "building the code" pointer to `docker/`
5. **A chapter can end in an optional capstone project folder**
   (e.g. `4.8ExpenseTrackerProject`), a step up in scope from the lectures,
   reusing the same theme and reaching back to reuse concepts from prior
   chapters (e.g. file persistence from chapter 3). Only add one if asked, or
   if it clearly strengthens the chapter - confirm the theme/scope with the
   user first rather than assuming.

## Coding conventions (as of the C++23 modernization)

- **`std::print` / `std::println`** (`<print>`) instead of
  `std::cout <<` / `std::endl`. Reach for `std::cin`/`std::getline` for input
  (C++23 has no formatted-input equivalent yet).
- **No `using namespace std;`** - always qualify with `std::`.
- **Brace initialization (`{}`)** for every variable declaration, e.g.
  `int age{};`, `double amount{93.33};` - never bare declarations that leave
  a variable uninitialized, and never `=`-style init for new variables (that
  style is reserved for demonstrating narrowing conversions on purpose).
- **Digit separators** in large literals: `1'000'000`, not `1000000`.
- **`<cstdint>` fixed-width types** (`std::int32_t`, `std::uint16_t`, ...)
  introduced as the modern alternative once a lecture covers integer sizing,
  not as a replacement for teaching `short`/`int`/`long long` first.
- **Comments explain *why*, not *what*.** No line-by-line narration of
  obvious code. A comment earns its place by explaining a non-obvious
  constraint, a gotcha, or the reasoning behind a choice (e.g. why this stat
  needs `long long` instead of `int`).
- **`CMakeLists.txt` per lecture folder**, always targeting
  `add_executable(rooster main.cpp)` with `CMAKE_CXX_STANDARD 23`. Copy an
  existing sibling lecture's `CMakeLists.txt`/`.gitignore` verbatim when
  scaffolding a new or renumbered folder - don't hand-roll variations.
- Chapters currently top out around chapter 8+ using the older style;
  expect more chapters to need this same treatment over time. Check whether
  a later chapter already covers a concept (e.g. chapter 5 covers operators
  and `std::numeric_limits`) before re-teaching it in an earlier chapter.
- **Ordering has been reshuffled from the original course outline** to get
  to flow control, loops, and functions sooner, and to place lower-priority
  topics only once they can lean on a running example instead of being
  taught in isolation: `LiteralsAndConstants` and
  `ConversionsOverflowAndUnderflow` were dissolved into chapters 4 and 5;
  `VariableLifetimeAndScope` (chapter 8) sits right after Loops, where `if`
  blocks and loop bodies give it real scopes to demonstrate; and
  `BitwiseOperators` (chapter 15) sits after Enums, kept deliberately short -
  most of what a course would traditionally spend 7 lectures on (masks,
  shifting, manual color packing) doesn't earn that much space in a course
  aimed at practical know-how, so it's 3 lectures ending on the one
  realistic use case (combining flags via `enum class`).

## Building and testing

**Always build and run through the Docker images in [`docker/`](docker/),
not a local/system compiler.** Local toolchains on this machine (e.g. mingw64
g++) may have incomplete C++23 stdlib support (`std::print` has been observed
to fail to *link* locally, even though it compiles) - this is a local
environment gap, not a code bug, and Docker is the source of truth for
whether a lecture actually builds and runs correctly.

Images (see `docker/README.md` for full detail):

| Image | Compiler |
|---|---|
| `masterclass-gcc:16` | GCC 16 |
| `masterclass-clang:21` | Clang 21 |

Build once per session if the images aren't already present:

```sh
docker build -t masterclass-gcc:16 docker/gcc
docker build -t masterclass-clang:21 docker/clang
```

Build + run a lecture (GCC):

```sh
docker run --rm -v "D:/full/path/to/chapter/lecture:/workspace" masterclass-gcc:16 sh -c \
  "cd /workspace && cmake -B build -G Ninja . && cmake --build build && ./build/rooster"
```

Clang needs the compiler pinned explicitly:

```sh
docker run --rm -v "D:/full/path/to/chapter/lecture:/workspace" masterclass-clang:21 sh -c \
  "cd /workspace && cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++ . && cmake --build build && ./build/rooster"
```

For interactive programs (anything reading `std::cin`), pipe scripted input
with `printf "...\n" | docker run --rm -i -v ... `, `-i` is required for
stdin to reach the container.

**Always verify against both images** before considering a rewritten lecture
done - a warning/behavior difference between GCC and Clang is worth
surfacing, not silently picking one.

**Clean up after testing:** remove each lecture's `build/` directory (and any
program-generated files, e.g. a demo `expenses.txt`) after verifying, and
double check for stray directories Docker's bind-mount can leave behind on
Windows (watch for oddly-named empty folders after a run) - `git status`
before finishing should show only the intended source changes.

### Windows/Docker path gotcha

From the Bash tool on this machine, `$(pwd)` resolves to a Git-Bash-style
path (`/d/Sandbox/...`) that Docker Desktop's `-v` will silently fail to
mount correctly. Build the Windows drive-letter path explicitly instead
(`WINROOT="D:/Sandbox/..."`) and mount with that.

## Working style expected on this repo

- **Plan before restructuring.** Renumbering/merging lecture folders is a
  structural change to recorded course content - lay out the concrete plan
  (theme, which lectures merge, final numbering) and get explicit sign-off
  before touching folders, even if the general direction was already agreed.
- **Never commit unless explicitly asked.** Leave changes in the working
  tree for review.
- **Reuse existing sibling files** (`CMakeLists.txt`, `.gitignore`) instead of
  hand-writing new ones from scratch, to keep every lecture folder
  byte-for-byte consistent in its boilerplate.
