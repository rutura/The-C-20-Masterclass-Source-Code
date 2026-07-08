# C++23 Features Worth Adding to the Course

Research pass on C++23 topics not currently covered in this course, done to inform
manually walking back through the chapters. Covers what each feature is, why it's
worth teaching, where it might fit, and — critically — whether it's actually usable
today in this repo's pinned toolchain (`masterclass-gcc:16`, `masterclass-clang:21`).

The course already covers real C++20/23 material (spaceship operator, concepts,
ranges, `std::print`/`std::println`, modules, coroutines) — this is not a gap in
that sense. The gaps below are specific, addressable, and mostly self-contained
additions to existing chapters rather than a course overhaul.

## Worth adding — high value, both compilers solid

### `std::expected<T, E>`
Complete in libc++ since Clang 17, in libstdc++ since GCC 16 (this repo's exact
pinned version). The single biggest omission. The `Exceptions` chapter already
ends on "here's when throwing is the wrong tool" energy — `std::expected` is the
modern, practical answer to that. Comes with monadic operations (`and_then`,
`transform`, `or_else`) that are genuinely elegant and read like real production
code. **Suggested fit:** new lecture-cluster at the end of `Exceptions`, or a short
dedicated chapter right after it.

### `std::mdspan`
Non-owning multidimensional array view. Complete in libc++ since Clang 18;
**new/experimental in GCC 16 specifically** (padded layouts, `submdspan`, etc.
landed in this exact release) — right at the edge, so verify it compiles cleanly
in both Docker images before committing a lecture to it. Useful for image/grid/
matrix-style data without hand-rolling row-major indexing math. **Suggested fit:**
pairs naturally with multidimensional `operator[]` (below) if teaching both.

### `std::flat_map` / `std::flat_set`
Complete in libc++ since Clang 20/21; GCC version unconfirmed from available
docs — check in Docker. "Here's a map that's often faster than `std::map` for
read-heavy workloads because it's just a sorted vector under the hood." Reinforces
"know your container's Big-O, don't just reach for the default." **Suggested
fit:** right after `StlContainersAndIterators`/`ZoomingOnSTLContainers`.

### Ranges additions: `zip`, `enumerate`, `chunk_by`, `cartesian_product`
Not in C++20's range library, genuinely useful in everyday code — e.g.
`for (auto [i, item] : std::views::enumerate(container))` kills a whole category
of manual-index-tracking bugs. The `RangesLibraryInCpp20` chapter is currently
scoped to what C++20 shipped. **Suggested fit:** an explicit "what's new in
C++23" coda lecture rather than folding these in invisibly, so students know
which range features need `-std=c++23` vs `c++20`.

### Formatting ranges/tuples directly with `std::print`/`std::println`
C++23 lets `std::println("{}", my_vector);` just work — no loop needed. The
course already teaches `std::print`; this is a small, cheap addition wherever
that's currently taught. Removes a "why do I need a loop just to print a
vector" moment.

### `if consteval`
Small, clean language feature. **Suggested fit:** one extra example in the
existing `constexpr`/`consteval` lecture in `FunctionBasics` (9.19) — not a new
chapter.

### Deducing `this` (explicit object parameter)
Genuinely changes how certain member functions are written — eliminates the
classic const/non-const getter duplication, enables CRTP-free recursive
lambdas. **Suggested fit:** `Classes` chapter's const-correctness section,
ideally with an explicit callback to `ConstMemberFunctions` ("this solves a
problem you already hit earlier in the course").

### Multidimensional `operator[]`
`matrix[1, 2]` instead of `matrix(1, 2)` or `matrix[1][2]`. Small, clean.
**Suggested fit:** `OperatorOverloading` chapter, pairs naturally with `mdspan`.

## Worth flagging, use judgment on

### `std::stacktrace`
"Not started" in libc++ as of the researched status table — **GCC-only
realistically right now.** Great practical debugging content ("get a stack
trace on assert failure without attaching a debugger"), but the cross-compiler
asymmetry means either GCC-only coverage with an explicit caveat, or skip until
Clang catches up.

### `std::generator` (coroutine-based lazy sequences)
The one to flag most clearly: **implemented in libstdc++ since GCC 14, but not
started in libc++ as of the Clang 21 status table.** Directly overlaps the
existing `Coroutines` chapter, which already hand-rolls a generator pattern
(`34.8CustomGenerator`) — `std::generator` is literally "the standard library
version of what you just built by hand," which is excellent pedagogically
(validates the hand-rolled version was worth learning). But it can't be
verified on both compilers today, and this repo's whole build/verify workflow
is "confirm on both images." Either keep it GCC-only with a clear callout, or
hold it until Clang implements it — don't quietly teach it as if it's
universally available.

### `std::move_only_function`
Nice complement to the existing `FunctionLikeEntities` chapter's `std::function`
coverage ("here's the version for move-only captures like `unique_ptr`").
Moderate value, not urgent.

## Skip for this course

`std::spanstream`, heterogeneous container erasure, `std::out_ptr`/`inout_ptr`
(C-API interop, niche for a practical/modern-focused course), extended
`<charconv>` constexpr support, `[[assume]]` (compiler-hint attribute, more of
an optimization footnote than a teaching moment), new preprocessor directives
(`#elifdef`/`#warning`) — all real, all minor, none earn a lecture on their own
in a course this tightly scoped.

## Process note

Before committing lecture time to any "worth adding" item above, smoke-test it
in both Docker images (`masterclass-gcc:16` / `masterclass-clang:21`) the same
way every lecture in this repo is already verified. Several of these (`mdspan`
especially) are fresh enough in GCC 16 that "the paper says complete" and
"actually compiles cleanly in this pinned image" aren't guaranteed to be the
same thing.

## Sources

- [C++23 - cppreference.com](https://en.cppreference.com/cpp/23)
- [C++23 Language Features and Reference Cards - C++ Stories](https://www.cppstories.com/2024/cpp23_lang/)
- [C++23 Library Features and Reference Cards - C++ Stories](https://www.cppstories.com/2024/cpp23_lib/)
- [libc++ C++23 Status — libc++ documentation](https://libcxx.llvm.org/Status/Cxx23.html)
- [GCC 16 Release Series — Changes, New Features, and Fixes](https://gcc.gnu.org/gcc-16/changes.html)
- [std::generator: Standard Library Coroutine Support - C++ Team Blog](https://devblogs.microsoft.com/cppblog/std-generator-standard-library-coroutine-support/)
- [C++23 and std::flat_map — Raspberry Pi Forums](https://forums.raspberrypi.com/viewtopic.php?t=381906)
