# Course plan: chapters 06 to 19

Working document. Edit freely: when you sign off, chapters are built one at a time in this order, with a pause for your review after each. Titles and lecture lists below are drafts.

## Shape of every chapter from 06 on

1. Intro at the top of `NOTES.md` (the "N.1" slot, no folder).
2. Lectures `N.2` onward, one folder each (`main.cpp`, `CMakeLists.txt`, `.gitignore`).
3. Project folder(s), named `N.xProjectName`, taught from the chapter `NOTES.md`.
4. `N.xAssignment` last: `main.cpp` stubs, `main_solution.cpp` (target `rooster_solution`), `QUIZ.md` (20 multiple-choice questions), and an exercise table in `NOTES.md`.

## Rules for building

- Voice and conventions follow chapter 06 and `CLAUDE.md`: second person, on-camera tone, ASCII diagrams, brace init, `std::println`, no `using namespace std`, no `std::endl`, digit separators, comments explain why. No em dashes in notes.
- The Deitel and Gregoire books in `D:\CourseRef` are idea sources only. All code, prose, examples and quiz questions are original. No verbatim text or listings and no reuse of their case studies as is.
- Every build, object file and test binary lives under `D:\Sandbox\` (the antivirus-excluded path), build dirs in `D:\Sandbox\_build\`.
- MSVC is the reference compiler (`/std:c++latest`, never `/std:c++23`). MinGW GCC 14.2 and Clang 19.1 need `-lstdc++exp` for `std::println`. Linux checks run in the `cpp-masterclass-gcc` (GCC 16) and `cpp-masterclass-clang` (Clang 21) images.
- Nothing is committed unless you ask.

## Done in Phase 0

- Chapter 06: removed the duplicate `6.17IntroToAssembly` (chapter 08 covers it, more deeply) and renumbered. Now `6.17ProjectImageWriter`, `6.18ProjectVendoredHeader`, `6.19ProjectFetchContent`, `6.20Assignment`. All four build and run with MSVC.
- Chapter 08: removed the committed `exit_code` ELF from `8.11WritingAssemblyYourself` and ignored it there.
- Chapter 07 (awaiting your review): added `7.12ProjectManualCompile`, `7.13ProjectStaticLibrary`, `7.14ProjectDynamicLibrary`, `7.15ProjectCMakeCommandLine`, renamed the assignment to `7.16Assignment`, and added the five matching sections to `NOTES.md`. Every environment script was run on MSVC, MinGW GCC, MinGW Clang, Linux GCC and Linux Clang. A `.gitattributes` keeps the `.sh` scripts LF.
- Chapter 08 (awaiting your review): renamed `8.11WritingAssemblyYourself` to `8.11SeeingAssemblyLocally` (its NASM half moved into the project), added `8.12ProjectAssemblyLab` (Linux containers, nasm, gdb) and `8.13Assignment` (five assembly functions, one read-the-assembly exercise, a gdb exercise, 20-question quiz), with matching `NOTES.md` sections. Run in both the GCC and Clang containers and on MSVC for 8.11. Not tested on Apple Silicon.
- Chapter 09 (awaiting your review): new `09.PointersAndArrays` with ten lectures (9.2 to 9.11), `9.12ProjectMemoryDetective` (seven planted memory bugs and the sanitizers that catch them) and `9.13Assignment` (eight exercises, solutions, 20-question quiz), plus a 1,480-line `NOTES.md`. Built with MSVC, and the lectures, project and assignment also run on GCC 16 and Clang 21 in the containers, with sanitizers.
- Chapter 10 (awaiting your review): new `10.Classes` with ten lectures (10.2 to 10.11), `10.12ProjectCanvas` (the ch06 image writer as a `Canvas` class, with a custom move that keeps its invariant, and the vendored stb header) and `10.13Assignment` (eight exercises, solutions, 20-question quiz), plus a 1,360-line `NOTES.md`. Built with MSVC, run on GCC 16 and Clang 21 in the containers, and the project and the assignment solution are clean under ASan and UBSan.
- Chapter 11 (awaiting your review): new `11.InheritanceAndPolymorphism` with ten lectures (11.2 to 11.11), `11.12ProjectShapeRenderer` (an abstract `Shape`, concrete shapes, a `Group` composite and `clone()`, drawing onto the chapter 10 `Canvas`) and `11.13Assignment` (eight exercises, solutions, 20-question quiz), plus a 1,346-line `NOTES.md`. Built with MSVC, run on GCC 16 and Clang 21, and the project and the assignment solution are clean under ASan and UBSan.
- Chapter 12 (awaiting your review): new `12.OperatorOverloading` with nine lectures (12.2 to 12.10, including the `Matrix` class in `matrix.h`), the vcpkg project in three folders (`12.11ProjectVcpkgClassicMode` with fmt, `12.12ProjectVcpkgManifestMode` with ftxui and CMake presets, `12.13ProjectFtxuiDashboard` with our own decorators for ftxui's `|`) and `12.14Assignment` (eight exercises, solutions, 20-question quiz), plus a 1,436-line `NOTES.md`. Built with MSVC and run on GCC 16 and Clang 21. The vcpkg projects were built and run on Windows (own vcpkg and the Visual Studio one), and in both containers, using the scripts in each folder.
- Chapter 13 (awaiting your review): new `13.ExceptionsAndContracts` with eight lectures (13.2 to 13.9: error-handling strategies, throw/try/catch and unwinding, standard and custom exceptions, `noexcept` and safety guarantees, rethrow/nested/constructors, `std::expected`, `source_location` and `stacktrace`, assertions and C++26 contracts), Project 6 in three folders testing the chapter 12 `Matrix` (`13.10ProjectTestingByHand`, `13.11ProjectGoogleTest`, `13.12ProjectCatch2`, the last two via vcpkg manifest mode with CTest) and `13.13Assignment` (eight exercises, solutions, 20-question quiz), plus a 1,460-line `NOTES.md`. Built with MSVC, run on GCC 16 and Clang 21 in the containers; the two vcpkg projects were built and tested on MSVC (Visual Studio's vcpkg) and in both containers. Contracts run on GCC 16 only (the CMake target is skipped elsewhere).
- Chapter 14 (awaiting your review): new `14.ContainersAndIterators` with ten lectures (14.2 to 14.11: iterators, inside the vector, iterator invalidation, deque/list/forward_list, set and map, unordered containers and hashing, adaptors, `flat_map` and `mdspan`, writing your own iterator, choosing a container with a timing program), `14.12ProjectLogAnalyzer` (a C++ generator for a 100,000-line web server log, identical on every compiler, and an analyzer that parses with `string_view` and answers its questions with vector, map, array, unordered_map, a top-N heap and a map of sets) and `14.13Assignment` (eight exercises, solutions, 20-question quiz), plus a roughly 1,400-line `NOTES.md`. Built with MSVC, run on GCC 16 and Clang 21 (`flat_map`/`mdspan` on Clang need `-stdlib=libc++`); the project and the assignment solution are clean under ASan and UBSan. The generator is a C++ program instead of the script the plan mentioned, so it needs nothing installed on Windows.
- Chapter 15 (awaiting your review): new `15.AlgorithmsRangesViews` with nine lectures (15.2 to 15.10: algorithms and the ranges form, non-modifying, modifying, erase-remove and `erase_if`, sorting/partitions/binary search, numeric, callables and projections, more views, `ranges::to` and ownership), `15.11ProjectLogPipeline` (the chapter 14 analyzer rewritten as pipelines: identical report on MSVC, GCC and Clang, 24% fewer lines of code, 1.6 to 2.4 times slower, with the numbers in the notes) and `15.12Assignment` (eight exercises, solutions, 20-question quiz), plus a roughly 1,300-line `NOTES.md`. Every lecture program and the assignment solution print byte-identical output on MSVC, GCC 16 and Clang 21; clean under ASan and UBSan on GCC. The Clang image's default library (libstdc++ 14) is the right one for this chapter; Clang with libc++ lacks several C++23 views.
- Chapter 16 (awaiting your review): new `16.TemplatesConceptsMetaprogramming` with ten lectures (16.2 to 16.11: function templates further, generic lambdas, class templates and deduction, value parameters, type traits, using concepts, writing concepts, specialization and `if constexpr`, variadic templates/folds/forwarding, `constexpr`/`consteval`/`constinit`), `16.12ProjectMatrixTemplate` (the chapter 12 Matrix rebuilt as `Matrix<T, Rows, Columns>`: shape in the type, a `Number` concept, compile-time shape errors, `constexpr` arithmetic, a partial `std::formatter` specialization, compile-time tests through concepts plus a run-time harness with `ctest`) and `16.13Assignment` (eight exercises, solutions, 20-question quiz), plus a roughly 1,650-line `NOTES.md`. Written under the new rule "only use what has been taught": the lecture order is driven by dependencies, and the chapter explains the earlier forward references (the 12.4 formatter, the 14.7 hash, the 14.2 and 13.5 assertions, generic lambdas). MSVC, GCC 16 and Clang 21 print byte-identical output for every program, no warnings, clean under ASan and UBSan on GCC.
- Chapter 17 (awaiting your review): new `17.Modules` with seven lectures (17.2 to 17.8: why headers hurt, first module, modules and the standard library, partitions, `import std;`, fragments/header units/migration, how the build works), `17.9ProjectModularize` (the 11.12 shape renderer built as headers, as modules and as modules with `import std;`, with build-time tables for MSVC, GCC and Clang) and `17.10Assignment` (eight exercises, solutions, 20-question quiz), plus a roughly 1,000-line `NOTES.md`. All programs print identical output on MSVC 19.51, GCC 16 and Clang 21 (private module fragment only on MSVC and Clang; `import std;` on MinGW is not possible).
- Chapter 18 (awaiting your review): new `18.Coroutines` with eight lectures (18.2 to 18.9: functions that pause, `std::generator`, the frame/promise/handle, writing your own generator, `co_await` and awaiters, a lazy `Task<T>`, lifetime pitfalls with AddressSanitizer, a round-robin scheduler), `18.10ProjectLazyPipeline` (a pipeline of generators and a `filter` view over a log file that is never held in memory, plus three analysis jobs sharing one thread on the scheduler) and `18.11Assignment` (eight exercises, solutions, 20-question quiz), plus a roughly 1,550-line `NOTES.md`. Identical output on MSVC 19.51, GCC 16 and Clang 21; GCC needs `-foptimize-sibling-calls` (or `-O2`) for deep task chains, and MSVC's AddressSanitizer does not check accesses inside a coroutine body.
- Chapter 19 (awaiting your review): new `19.ParallelAlgorithmsAndConcurrency` with eleven lectures (19.2 to 19.12: parallel algorithms, threads and `jthread`, data races, mutexes and deadlock, atomics, condition variables, `async` and futures, latch/barrier/semaphore, a thread pool, a logger, finding races with ThreadSanitizer), `19.13ProjectParallelMandelbrot` (the chapter 10 `Canvas` rendered serially, with `std::execution::par`, with fixed bands of threads and with the pool, speedups measured on MSVC, GCC, Clang and MinGW; byte-identical PNG) and `19.14Assignment` (eight exercises, solutions, 20-question quiz), plus a roughly 1,620-line `NOTES.md`. Identical output on MSVC 19.51, GCC 16 and Clang 21 (`[varies]` lines aside). GCC and Clang need oneTBB for `par` (not in the images: `apt-get install libtbb-dev`), MSVC and MinGW have no ThreadSanitizer.

## Chapter 07: add the build-tools projects (Projects 1 to 4)

Subject for all four: a small weather-station "stats" program (`stats.h/.cpp`, `report.h/.cpp`, `main.cpp`). Five environments each: Windows MSVC, Windows MinGW GCC, Windows MinGW Clang, Linux GCC (Docker), Linux Clang (Docker). Each folder carries a CMakeLists for comparison and one build script per environment as the answer key.

| Folder | Content |
|---|---|
| `7.12ProjectManualCompile` | source to object to executable by hand; one step vs two steps; inspect objects and binaries (`dumpbin`, `nm`, `objdump`, `readelf`); COFF vs ELF and MSVC vs Itanium name mangling |
| `7.13ProjectStaticLibrary` | build `stats` into `.lib` / `.a`, list archive members, archive vs object, link it |
| `7.14ProjectDynamicLibrary` | `.dll` + import library, `.so`; export macros, `-fPIC`, rpath, PATH; `dumpbin /exports`, `nm -D`, `ldd`; static vs dynamic table |
| `7.15ProjectCMakeCommandLine` | drive CMake from the command line per compiler (interpretation of Project 4: please confirm) and map it back to the manual commands |
| `7.16Assignment` | existing `7.12Assignment`, renamed, plus its notes section |

## Chapter 08: add the assembly project

Keep 8.2 to 8.11 as they are (8.11's NASM part trimmed to point at the project).

| Folder | Content |
|---|---|
| `8.12ProjectAssemblyLab` | Linux Docker, x86-64 NASM and gdb: exit-code and `write` programs, hand-written `add_i32` and `sum_array` called from C++ through `extern "C"`, compare with compiler output, step in gdb. Apple Silicon box: run with `--platform linux/amd64` |
| `8.13Assignment` | assembly stubs and C++ stubs, solutions, 20-question quiz |

## Chapters 09 to 19

| Ch | Title | Lectures (draft) | Project |
|---|---|---|---|
| 09 | Pointers and Arrays | pointers and addresses; const with pointers; pointers vs references; C arrays and decay; pointer arithmetic; `std::span`; `new`/`delete` and why to avoid them; `unique_ptr`; `shared_ptr` and `weak_ptr`; C strings | **Memory Detective**: find planted memory bugs with AddressSanitizer / debug CRT / UBSan (valgrind optional) |
| 10 | Classes | struct to class; constructors and init lists; header/source split; const members; destructors and RAII; copy; move; rule of zero and five; static, this, friend; composition; aggregates | **Canvas**: the ch06 image writer becomes a `Canvas` class |
| 11 | Inheritance and Polymorphism | base/derived; overriding and `virtual`/`override`/`final`; polymorphic containers and slicing; abstract classes; virtual destructors; vtables (look at the assembly); access control and composition vs inheritance; multiple inheritance; RTTI and casts; `variant` + `visit` | **Shape Renderer** onto the ch10 `Canvas` |
| 12 | Operator Overloading | operators are functions; member vs non-member; arithmetic and compound assignment; `<<` and `std::formatter`; `<=>`; `[]` and `()`; copy/move for `Matrix`; conversions and `explicit`; literals; pipe operators | **vcpkg + ftxui** (3 folders: classic mode, manifest mode, ftxui dashboard) |
| 13 | Exceptions and Contracts | error-handling strategies; try/catch/throw; hierarchy and custom exceptions; unwinding and RAII; `noexcept` and guarantees; rethrow and nested; `std::expected`; `source_location` and `stacktrace`; assert, `static_assert`, C++26 contracts | **Testing** (3 folders: hand-rolled, GoogleTest, Catch2) on the ch12 `Matrix` |
| 14 | Containers and Iterators | iterators; invalidation; vector internals; deque/list/forward_list; set/map; unordered containers and hashing; adaptors; `flat_map` and `mdspan`; writing an iterator; choosing a container | **Log Analyzer** |
| 15 | Algorithms, Ranges and Views | iterator pairs vs ranges; non-modifying and modifying; erase-remove and `erase_if`; partitions and binary search; numeric algorithms; callables and projections; constrained algorithms; views; `ranges::to`; dangling | **Log Pipeline**: ch14 analyzer as a ranges pipeline |
| 16 | Templates, Concepts and Metaprogramming | deduction; class templates and CTAD; non-type parameters; concepts; custom concepts; specialization and `if constexpr`; variadics and folds; type traits; `constexpr`/`consteval`/`constinit` | **`Matrix<T,R,C>`** generic version of ch12 |
| 17 | Modules | why headers hurt; first module; implementation units and partitions; `import std;`; fragments and header units; CMake module support | **Modularize** the ch10/11 Canvas + Shapes, compare build times |
| 18 | Coroutines | mental model; `std::generator`; promise type and handle; awaitables; a lazy `task<T>`; lifetime pitfalls; a small scheduler | **Lazy Pipeline**: generator log reader plus a round-robin scheduler |
| 19 | Parallel Algorithms and Concurrency | execution policies; `thread`/`jthread` and stop tokens; races, mutex, deadlock; atomics; condition variables; `async` and futures; latch, barrier, semaphore; thread pool; ThreadSanitizer | **Parallel Mandelbrot** onto `Canvas`: serial vs `par` vs thread pool |

Reuse chains: ch06 image writer, ch10 Canvas, ch11 Shapes, ch17 modules, ch19 parallel render. ch12 Matrix, ch13 tests, ch16 `Matrix<T,R,C>`. ch14 log analyzer, ch15 pipeline, ch18 lazy pipeline.

## Risks to check while building

- C++26 contracts: only GCC 16 in Docker may support them; MSVC and Clang probably not.
- `import std;` needs CMake's experimental switch and cannot work on MinGW GCC 14.2.
- ASan in MSVC needs the VS component; ftxui via vcpkg on MSVC; TBB for `par` in Docker GCC.
- On this machine git cannot verify GitHub's TLS certificate, so FetchContent from GitHub fails here. Verification of FetchContent folders uses a local source override (`FETCHCONTENT_SOURCE_DIR_<NAME>`). Students are not affected unless their machine has the same problem.

## Open questions for you

1. Project 4 (`7.15`): is "drive CMake from the command line" what you meant?
2. Chapter 12 carries the vcpkg + ftxui project and chapter 13 the testing project. OK, or do you prefer other chapters?
3. Should `CLAUDE.md` be refreshed (it still names folders like `05.OperationsOnData` and `4.3IntegerTypes`)?
