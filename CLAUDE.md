# The C++20/23 Masterclass: Source Code

This repo is the source code companion to a **video course** teaching C++
from first principles up through modern C++20/23. Each numbered top-level
folder (`03.FirstSteps`, `06.Functions`, `08.IntroToAssembly`, ...) is a
chapter. Each subfolder inside a chapter (e.g. `6.14LambdaFunctions`) is one
recorded lecture, project or assignment, with its own `main.cpp` and
`CMakeLists.txt`. Each chapter also has a chapter-level `NOTES.md` that is the
instructor's script and the student's reference.

Because this is a course, changes here are not just "fix the code". They
affect what an instructor says on camera and what a student sees when they
open a folder. Treat lecture folders, their numbering and the notes as
content, not just source files.

## Status and the plan

- **`SESSION-HANDOFF.md` at the repo root is where the current state lives**:
  which chapters are done, what is next, decisions already made, tooling
  gotchas, open items. Read it at the start of a session. **Keep it up to
  date**: update it whenever a chapter is finished, a decision is made, a
  tooling lesson is learned or an open item is resolved. Do this as part of the
  work, not as an afterthought.
- Chapter 06 (`06.Functions`) is the style reference for everything that
  follows. Chapters up to the one named in the handoff are done. The rest are
  being written from scratch.
- **`COURSE-PLAN.md` at the repo root is the source of truth** for chapter
  layout, project placement and build order. Follow it. If something in it
  seems wrong or incomplete, ask the user, do not silently change it.
- Work one chapter at a time. After each chapter, report what passed and what
  could not be verified, then stop for the user's review.

## Shape of every chapter from 06 on

1. Chapter intro at the top of `NOTES.md` (the "N.1" slot, no folder).
2. Lectures `N.2` onward, one folder each: `main.cpp`, `CMakeLists.txt`,
   `.gitignore`. Extra demos in a lecture use `main2.cpp`/`rooster2` style or
   `mainN_topic.cpp` as already used in chapters 06 and 07.
3. Project folder(s) named `N.xProjectName`. All teaching lives in the chapter
   `NOTES.md`; there is no per-folder README. A project may span several
   folders (chapter 06 has three, chapter 07 has four).
4. `N.xAssignment` is always the last number: `main.cpp` with stubbed
   exercises on one running theme, `main_solution.cpp` as a second target
   `rooster_solution`, `QUIZ.md` with 20 multiple-choice questions
   (`### N.` question, options A to D, `**Answer: X** - why`), and an exercise
   table plus closing line in `NOTES.md`. Model: `06.Functions/6.20Assignment`.
5. Folder numbering is sequential with no gaps. When a lecture or project is
   inserted or removed, renumber and fix every cross reference (notes
   headings, comments, CMake comments, quizzes) and grep for dangling numbers.

Do not generate a chapter-root `README.md`. The code and `NOTES.md` are the
reference.

## Writing the notes and lectures

- Voice: second person, on-camera, conversational, short paragraphs, one new
  idea at a time, bold key terms, "the pattern to remember" lines, ASCII
  diagrams in fenced blocks for memory, call flow and state. Look at
  `06.Functions/NOTES.md` before writing a new chapter.
- **No em dashes** in notes or any written docs. Rephrase with a colon, comma
  or hyphen instead.
- One running example per chapter, built up lecture by lecture. Prefer
  problem-solving over exhaustive enumeration. Introduce something because the
  running example needs it. Cut anything that does not earn its place.
- Check whether another chapter already covers a concept before teaching it
  again (for example vector, sorting and views basics are chapter 07, lambdas
  and function templates are chapter 06).
- **Reference books are idea sources only.** `D:\CourseRef` holds Deitel
  (C++20 for Programmers) and Gregoire (Professional C++, 6th ed.) plus their
  code. Use them for topic order, pitfalls and the kind of exercise. Write all
  code, prose, examples and quiz questions from scratch in the course voice.
  No verbatim text or listings, and do not reuse their case studies as is.
  The Deitel PDF is too big for the Read tool: use
  `pdftotext -f N -l M -layout <pdf> -`. Its chapters 17 to 19 have no text,
  only code.

## Coding conventions (enforced, do not deviate without being asked)

- **Brace initialization (`{}`) for every variable declaration, no
  exceptions**: `int decimal{15};`, `double amount{93.33};`. This applies even
  when demonstrating literal syntax (`int octal{017};`). Bare or uninitialized
  declarations are never acceptable. `=`-style init is reserved for a
  deliberate narrowing or overflow demonstration in a lecture that teaches
  that pitfall.
- **Printing: `std::print`/`std::println` is the default** from the lecture
  that introduces `<print>` onward (chapter 03 introduces `std::cout` first so
  students recognise it). Never use `std::endl`. Use `"\n"` inside a format
  string.
- **No `using namespace std;`**. Always qualify with `std::`.
- **Digit separators** in large literals: `1'000'000`.
- **`<cstdint>` fixed-width types** (`std::int32_t`, ...) as the modern
  alternative once sizing is covered, not a replacement for teaching
  `short`/`int`/`long long` first.
- **Comments explain why, not what.** No narration of obvious code.
- **`CMakeLists.txt` per lecture folder**, `add_executable(rooster main.cpp)`
  with `CMAKE_CXX_STANDARD 23` (more sources on the same line for multi-file
  lectures). Copy a sibling lecture's `CMakeLists.txt` and `.gitignore`
  verbatim (for example from `06.Functions/6.2ProgramComponents`) when
  scaffolding a folder. A folder may append lines to `.gitignore` for its own
  outputs (images, extensionless binaries) but should not otherwise vary.

## Building and testing

- **Everything is built under `D:\Sandbox\`.** The antivirus excludes
  `D:\Sandbox\*` and blocks binaries elsewhere. Use out-of-tree build dirs in
  `D:\Sandbox\_build\<name>` (outside the repo so lecture folders stay clean)
  and put scratch experiments in `D:\Sandbox\_build\scratch\`. Never build or
  run binaries from Temp or the Claude scratchpad.
- **MSVC is the reference compiler** (cl 19.51, VS 2026 Community). Load the
  dev shell in the same PowerShell call as the build:

  ```
  & "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64 -SkipAutomaticLocation
  cmake -S <lecture-folder> -B D:\Sandbox\_build\<name> -G Ninja
  cmake --build D:\Sandbox\_build\<name>
  ```

  CMake is 3.30.2 with no VS 2026 generator, so pass `-G Ninja`. For a single
  file use `cl.exe /nologo /std:c++latest /EHsc /W4 main.cpp`. Do not use
  `/std:c++23`: `cl` ignores it and `<print>` breaks. `vswhere.exe` is not at
  its usual path, so the install path above is used directly.
- **MinGW in `C:\mingw64\bin`** (GCC 14.2, Clang 19.1, binutils, nasm, gdb)
  links `std::println` only with `-lstdc++exp`. It has no `<stacktrace>`, no
  `import std`, and no TBB (so `std::execution::par` runs serially). Use it for
  command-line toolchain lectures and ABI checks, and say so when a lecture is
  not verified with it.
- **Linux checks** run in Docker with the images `cpp-masterclass-gcc`
  (GCC 16) and `cpp-masterclass-clang` (Clang 21), both with vcpkg at
  `/opt/vcpkg`. Existing stopped containers `cppm-gcc` and `cppm-clang` mount
  the repo at `/workspace` (`docker start` then `docker exec`). nasm, valgrind
  and libtbb-dev are not in the images, so lectures that need them tell the
  student to `apt-get install` them.
- On this machine `git` cannot verify GitHub's TLS certificate, so
  FetchContent from GitHub fails locally. Verify those folders with
  `-DFETCHCONTENT_SOURCE_DIR_<NAME>=<local dir>` and do not disable
  certificate checks.
- Students use the MSVC IDE or Qt Creator with any kit. MSVC shows the latest
  features because it is ahead. Students on older compilers can revert to what
  their compiler supports, and the instructor points out the gotchas, so
  notes should call out compiler differences instead of hiding them.

## Working style expected on this repo

- **Never commit unless explicitly asked.** Leave changes in the working tree
  for review.
- Build and run every new or renamed folder with MSVC before reporting it
  done. For tool-chain projects, run the exact commands that appear in the
  notes on every environment the notes cover.
- Plan before restructuring existing recorded content: lay out the old to new
  folder mapping and get explicit sign-off before renaming or deleting.
  Chapters in `COURSE-PLAN.md` are already approved.
- Reuse sibling boilerplate instead of hand-writing new files.
- Report faithfully: say what failed or could not be verified.
