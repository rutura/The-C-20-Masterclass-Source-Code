# Session handoff

Read this first, then `CLAUDE.md` (conventions, build rules) and `COURSE-PLAN.md` (the approved chapter plan). This file records where the work stands and what was learned, so a new session can continue without re-deriving it.

Suggested prompt for the next session:

> Read SESSION-HANDOFF.md, CLAUDE.md and COURSE-PLAN.md, then continue with chapter 13 (Exceptions and a look at contracts, plus the testing project) following the per-chapter workflow in the handoff.

## Status

Branch `udemy-update-cpp-23`. Last commit `8eaf674` (chapters 08 and 09), pushed to `origin`. Chapters 10, 11 and 12, this file and the `CLAUDE.md` update are in the working tree, **not committed**: commit them only if the user asks.

| Chapter | State |
|---|---|
| 01 to 05 | done, untouched |
| 06 Functions | done. `6.17IntroToAssembly` removed (chapter 08 covers it), project and assignment renumbered to 6.17 to 6.20 |
| 07 Practical Built-In Features | done. Added build-tool projects `7.12` to `7.15` (manual compile, static lib, dynamic lib, CMake from the command line) and renamed the assignment to `7.16Assignment` |
| 08 Intro to Assembly | done. `8.11` renamed `8.11SeeingAssemblyLocally`, added `8.12ProjectAssemblyLab` (Linux containers, nasm, gdb) and `8.13Assignment` |
| 09 Pointers and Arrays | done. Lectures `9.2` to `9.11`, `9.12ProjectMemoryDetective`, `9.13Assignment` |
| 10 Classes | done, awaiting review. Lectures `10.2` to `10.11` (class basics, constructors, header/source split, const, destructors and RAII, copying, moving, rules of zero and five, static/this/friend, composition and aggregates), `10.12ProjectCanvas`, `10.13Assignment` |
| 11 Inheritance and Polymorphism | done, awaiting review. Lectures `11.2` to `11.11` (inheritance basics, virtual and override, polymorphic containers and slicing, abstract classes and interfaces, virtual destructors, how virtual works with real assembly, access control and composition, multiple inheritance and the diamond, RTTI and casts, variant and visit), `11.12ProjectShapeRenderer`, `11.13Assignment` |
| 12 Operator Overloading | done, awaiting review. Lectures `12.2` to `12.10` (operators are functions, member or free and compound assignment, output and `std::formatter`, comparison and `<=>`, subscript and call operators, the Matrix in context, conversions and explicit, user-defined literals, pipe operators), `12.11ProjectVcpkgClassicMode` (fmt), `12.12ProjectVcpkgManifestMode` (ftxui, presets), `12.13ProjectFtxuiDashboard` (own decorators for ftxui's `|`), `12.14Assignment` |
| 13 to 19 | not started |

The user reviewed chapters 07 and 08 ("Looks good"), then asked for the commit and push of 08 and 09 and for chapter 10 without further comments, so treat 09 as accepted. The user reviewed chapter 10 ("Looking good") and chapter 11 ("Looking good. Continue"). Chapter 12 has not been reviewed yet.

## What comes next

Chapters 13 to 19 in order, one at a time, pausing for the user's review after each. The lecture lists, projects and source references for each chapter are in the table in `COURSE-PLAN.md` ("Chapters 09 to 19"). Short version of the reuse chains the plan depends on:

- ch06 image writer -> ch10 `Canvas` -> ch11 Shapes -> ch17 modules -> ch19 parallel Mandelbrot
- ch12 `Matrix` -> ch13 tests -> ch16 `Matrix<T,R,C>`
- ch14 log analyzer -> ch15 ranges pipeline -> ch18 lazy pipeline
- ch12 carries Project 5 (vcpkg + ftxui, three folders), ch13 carries Project 6 (testing: hand-rolled, GoogleTest, Catch2)

What chapter 12 left for later chapters (keep these promises):

- `12.7MatrixInContext/matrix.h` is the `Matrix` for chapter 13's testing project (copy the header into the project folder, as with Canvas) and chapter 16's generic `Matrix<T,R,C>`. API: `Matrix(rows, columns, fill = 0.0)`, `Matrix{{...},{...}}`, `Matrix::identity(n)`, `rows()`, `columns()`, C++23 `operator[](row, col)` (const and not), `at(row, col)` (throws `std::out_of_range`), `+= -= *=`, binary `+ - *` (by number in both orders, and matrix by matrix), `transposed()`, defaulted `==`, and a `std::formatter<Matrix>`. It **throws** `std::invalid_argument` on shape mismatch and a ragged initializer, and 12.7 says "exceptions are chapter 13, where the project writes tests that check the error paths of this very class". Chapter 13 must keep that promise (tests with `EXPECT_THROW` style checks).
- vcpkg was introduced in chapter 12: classic mode, manifest mode, the toolchain file, presets, baselines. Chapter 13's testing project (GoogleTest, Catch2) should use manifest mode with `CMakePresets.json` as in `12.12` and the same baseline `30ef65cad98f08e7197c9a1656fbd871bcb72f2d` (the commit both course containers carry; see the vcpkg notes below).
- 12.14's closing line says chapter 13 deals with "what happens when something goes wrong: exceptions, and a first look at contracts, where the Matrix class and its error paths come back".
- Chapter 12 taught: operator overloading (members and hidden friends, compound assignment, prefix and postfix, `operator<<`, `std::formatter`, `<=>`, multi-argument `operator[]`, `operator()` and functors, explicit conversions and `explicit operator bool`, user-defined literals, pipe operators), and the vcpkg basics above.

What chapter 11 left for later chapters (kept for reference):

- 11.11 uses a visitor struct with `operator()` overloads and says "`operator()` is chapter 12", so chapter 12 must cover the call operator. 10.10 said `friend` shows up in chapter 12 for `operator<<`.
- 11.12 `Shape` API for chapter 17 (modules: convert Canvas + Shapes from headers to modules) and chapter 19 (parallel Mandelbrot onto `Canvas`): `Shape` is abstract with `draw(Canvas&) const`, `translate(int,int)`, `clone()`, `name()`, `count()`, a virtual destructor and protected defaulted copy operations. Concrete: `Rectangle`, `Circle`, `Line`, `Triangle`, and `Group` (a Shape holding `vector<unique_ptr<Shape>>`). The folder contains its own copy of the chapter 10 Canvas files.
- 11.10 and 11.11 mention exceptions (`std::bad_cast`, `std::bad_variant_access`) as "chapter 13".
- Chapter 11 taught: inheritance, protected, virtual/override/final, slicing, abstract classes, virtual destructors, vtable and vptr (with assembly), private/protected inheritance, multiple and virtual inheritance, `dynamic_cast`, `typeid`, `std::variant`, `std::visit`, `std::get_if`. Chapter 12 can assume them.

What chapter 10 left for chapter 11 (done, kept for reference):

- 10.11 ends by contrasting "has a" (composition) with "is a" and says inheritance is the subject of chapter 11. 10.13 closes with "classes that inherit from one another, and the Canvas gets shapes that draw themselves".
- The `Canvas` API to build on (`10.12ProjectCanvas`): `struct Color{r,g,b}` (aggregate, designated initializers), `Canvas(int width, int height, Color background = {})`, `width()`, `height()`, `empty()`, `contains(x,y)`, `set_pixel(x,y,Color)` (out of range ignored), `pixel(x,y)`, `fill`, `fill_rect(x,y,w,h,Color)`, `draw_gradient(left,right)`, `draw_border(thickness,Color)`, `write_ppm(path)`, `write_png(path)`. It has a custom move so that a moved-from canvas is an empty 0 x 0 (invariant kept). The vendored `stb_image_write.h` lives in `10.12ProjectCanvas/vendor/` with `stb_impl.cpp`. Chapter 11's Shape Renderer should copy these files into its own project folder (each project folder stays self-contained) rather than depend on another chapter's folder.
- Chapter 10 taught: destructors and RAII, copy, move (`std::move`, `noexcept`, `std::exchange`), rule of zero and five, `static`, `this`, `friend`, aggregates, designated initializers, structured bindings (first introduced in 10.11) and `= default` / `= delete`. Chapter 11 can assume them. `virtual` destructors and slicing are new in 11.
- 8.12 mentions `extern "C"` and mangling (7.12). Chapter 11 plans to look at vtables in assembly (ties to chapter 08).

## Decisions the user made (do not re-ask)

- Remove the duplicate assembly lecture from chapter 06 and renumber (done).
- Chapter 07 gets Projects 1 to 4 as four project folders (done). Project 4 means "drive CMake from the command line".
- Chapter 08's assembly project runs in the Linux Docker containers only (done).
- Chapter placement of Projects 5 and 6: chapters 12 and 13 ("okay").
- Work chapter by chapter, outline first (the outline is `COURSE-PLAN.md`), pause for review after each.
- Reference books in `D:\CourseRef` (Deitel, Gregoire) are idea sources only. Write all code, prose and quiz questions from scratch. No verbatim text or listings, no reuse of their case studies as they are.
- Build everything under `D:\Sandbox\` (the antivirus blocks binaries elsewhere). Build dirs go in `D:\Sandbox\_build\<name>`.
- Never commit or push unless asked. (This session the user did ask for both.)
- No em dashes in notes or docs.

## Per-chapter workflow (definition of done)

1. Skim the mapped Deitel and Gregoire sections for topic order and pitfalls only. Design lectures around one running example. Check earlier chapters for what is already taught.
2. Create `N.x` lecture folders: `main.cpp`, and `CMakeLists.txt` plus `.gitignore` copied verbatim from `06.Functions/6.2ProgramComponents`. Brace init everywhere, `std::println`, no `using namespace std`, comments explain why.
3. Write the chapter `NOTES.md` in the chapter 06 voice: second person, on-camera, ASCII diagrams, a "Code for this lecture" line at the end of each lecture. Put real program output in the notes by running the programs.
4. Project folder(s) `N.xProjectName`, assignment `N.xAssignment` last: starter `main.cpp` with exercise statements and sample outputs in comments, `main_solution.cpp` (second target `rooster_solution`), `QUIZ.md` with 20 questions (A to D, answers spread evenly, `**Answer: X** - why`), and an exercise table in `NOTES.md`.
5. Build and run every folder with MSVC. Also compile and run in the Linux containers with `-Wall -Wextra` (students may use Qt Creator with GCC or Clang). Run the exact commands that appear in the notes.
6. Update `COURSE-PLAN.md` ("Done" list), report what passed and what could not be verified, then stop for review.

Lessons from chapters 07 to 09 worth repeating:

- Test every claim before it goes into the notes. Several first drafts were wrong and got corrected by running: a CMake compiler-change behaviour, whether `-fvisibility=hidden` shrinks exports (barely), what plain builds do with each memory bug, whether MinGW has sanitizers (it does not).
- Scripts that exercise things that can hang (Debug CRT dialogs, missing DLL dialogs) must be run with a timeout (`Start-Process` plus `WaitForExit`), and the dialog experiment is left to the student.
- Chapter 07 `NOTES.md` and the chapter 08 `NOTES.md` use CRLF line endings, chapters 06 and 09 use LF. Match the file you append to. Check for stray control characters after editing notes with Python (a `\b` in a path became a backspace once).
- Chapter 11 specifics worth copying: each lecture program was compared with real compiler output, and the notes quote GCC and Clang `-S -masm=intel` for a virtual call and AddressSanitizer's `new-delete-type-mismatch` for the missing virtual destructor. A scratch experiment confirmed the project's closing suggestion (remove `virtual ~Shape()`) really does produce warnings plus an ASan report.
- Chapter 10 specifics worth copying: lectures use a `Sensor` and a `ReadingLog` as running examples, with a small helper class that prints in its constructor and destructor to make lifetimes visible (`Noisy`, `Part`, `Probe`). The project folder includes a note that its outcome was tested under ASan and UBSan in both containers. A claim in the notes about a defaulted move breaking `Canvas` was checked with a scratch experiment (GCC 16's checked `vector::operator[]` aborts).
- Notes files: `10.Classes/NOTES.md` is LF like chapters 06 and 09. Chapters 07 and 08 are CRLF.
- **Backslashes in Python heredocs are unreliable** in this tool setup. A backslash followed by n, written inside a Python string through a heredoc, ended up as a real line break inside a C++ string literal, and a backslash followed by b in a Windows path became a backspace character. For any edit that includes a backslash, use the Edit tool (or write the whole file with the Write tool) instead, then check the result, for example by scanning the file for control characters.
- The editor reports false errors such as "No member named 'println'" and "No member named 'span'". That is clangd analysing without the build flags. The real compilers are the judge.

## Environment and tooling

- **MSVC** (cl 19.51, VS 2026). `vswhere.exe` is not at its usual path, so load the dev shell directly in the same PowerShell call as the build:
  `& "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64 -SkipAutomaticLocation`
  then `cmake -S <folder> -B D:\Sandbox\_build\<name> -G Ninja` and `cmake --build D:\Sandbox\_build\<name>` (CMake 3.30.2, no VS 2026 generator, so always `-G Ninja`). Single file: `cl /nologo /std:c++latest /EHsc /W4 /MD main.cpp`. Never `/std:c++23`.
- **MinGW** in `C:\mingw64\bin` (GCC 14.2, Clang 19.1, nasm, gdb): `std::println` needs `-lstdc++exp` after the objects. No `<stacktrace>`, no `import std`, no TBB (so `par` runs serially), no sanitizers.
- **Docker** (Docker Desktop must be running, the user has to start it): images `cpp-masterclass-gcc` (GCC 16.2) and `cpp-masterclass-clang` (Clang 21.1.8), both with vcpkg at `/opt/vcpkg`. Containers `cppm-gcc` and `cppm-clang` mount the repo at `/workspace`. Start them with `docker start cppm-gcc cppm-clang`. In this session `nasm` was installed in both, and `valgrind` in `cppm-gcc`. For verification, copy a folder into the container (`docker cp <folder> cppm-gcc:/tmp/x`) and build there, so outputs stay out of the repo. Strip CRLF from `.sh` files after copying (`sed -i 's/\r$//'`), or rely on `.gitattributes` for fresh checkouts.
- **git**: the machine's git cannot verify GitHub's certificate. Use `git -c http.sslBackend=schannel push` (and fetch, clone). This keeps verification on. Do not disable certificate checks. The same problem makes FetchContent from GitHub fail locally: verify those folders with `-DFETCHCONTENT_SOURCE_DIR_<NAME>=<local dir>`.
- **PowerShell 5.1 quirks**: with `$ErrorActionPreference = 'Stop'`, redirected stderr (`2>&1`) from a native command becomes a terminating error, so run sanitizer-style programs through `cmd /c "prog 2>&1"`. A `$pc` or backtick inside a double-quoted docker command gets mangled, so put such commands in a script file and `docker cp` it. `Remove-Item` on odd paths can be blocked by a safety check, so use fresh directories instead of deleting. That safety check also trips on a single command that contains both `rm -rf` (even inside a docker string) and a quoted `C:\Program Files` path: split it into two calls.
- **PowerShell pipelines kill native programs**: `cmake ... | Select-Object -First N` stops the pipeline early and kills the build mid-way (exit code 255). Send long output to a log file (`cmd /c "cmake ... > log 2>&1"`) and read the log. Also, `-e CC=$c[1]` does not expand an array element inside a docker argument: assign it to a variable first and use `-e "CC=$cc"`.
- **vcpkg** (chapter 12). The Visual Studio bundled vcpkg (`VCPKG_ROOT` is set to it in the dev shell) is **manifest-only** and **requires `builtin-baseline`** in `vcpkg.json`. For classic mode on Windows a full clone exists at `D:\Sandbox\vcpkg` (cloned with `git -c http.sslBackend=schannel clone https://github.com/microsoft/vcpkg`, bootstrapped with `bootstrap-vcpkg.bat -disableMetrics`), with `fmt` installed there. vcpkg runs its own git, so on this machine its registry fetch fails with an SSL certificate error: for tests set `GIT_CONFIG_COUNT=1`, `GIT_CONFIG_KEY_0=http.sslBackend`, `GIT_CONFIG_VALUE_0=schannel` in the environment (a one-off, keeps verification on). Both containers carry a **shallow** vcpkg clone with exactly one commit, `30ef65cad98f08e7197c9a1656fbd871bcb72f2d`, so any `builtin-baseline` used in a project must be that commit to work in the containers and everywhere else. Build manifest projects from a copy under `D:\Sandbox\_build` so `build/vcpkg_installed` stays out of the repo. In the containers, classic mode changes `/opt/vcpkg/installed` (`vcpkg remove fmt` restores it, already done). `vcpkg x-update-baseline --add-initial-baseline` works on both vcpkg kinds.
- Helper scripts used this session lived in a temp scratchpad and are not in the repo. They were small: a loop that builds each lecture folder with CMake and Ninja under `D:\Sandbox\_build` and runs `rooster.exe`, a script that copies a project folder to `D:\Sandbox\_build` (Windows) or `/tmp` (containers) and runs each `build-<env>` script, and a loop that compiles every lecture in a container with `-Wall -Wextra` and runs it. Recreate them as needed.

## Open items and things not verified

- Chapter 08 project on Apple Silicon (`--platform linux/amd64`, gdb under emulation) is untested. The notes say so. The gdb `layout asm` tip was not run.
- Chapter 09 project: the Visual Studio "C++ AddressSanitizer" installer component path was not tested (the component is installed here).
- Chapters 07 and 08 quizzes: the chapter 07 quiz has no questions on the four build projects (it covers 7.2 to 7.11).
- Chapter 09 is the longest chapter so far (ten lectures, about 1,480 lines of notes). The user may want 9.7 or 9.4 folded into others.
- The 6.19 FetchContent project could not be built from GitHub on this machine for the TLS reason above.
- Risks listed in `COURSE-PLAN.md` still apply to later chapters: C++26 contracts (only GCC 16 in Docker may support them), `import std;` with CMake 3.30 (experimental), ASan and ftxui via vcpkg on MSVC, TBB for `par` in Docker GCC.
- Chapter 06 `NOTES.md` still contains 27 em dashes. They are the user's own text, so they were left alone.
