# The C++20/23 Masterclass — Source Code

This repo is the source code companion to a **video course** teaching C++
from first principles up through modern C++20/23. Each numbered top-level
folder (`03.FirstSteps`, `04.VariablesAndDatatypes`, `05.OperationsOnData`,
...) is a chapter; each subfolder inside a chapter (e.g. `4.3IntegerTypes`)
is one recorded lecture, with its own `main.cpp` and `CMakeLists.txt`.

Because this is a course, changes here are not just "fix the code" — they
affect what an instructor says on camera and what a student sees when they
open a folder. Treat lecture folders and their ordering as content, not just
source files.

## Current work: trimming chapters down and modernizing them

The course is being edited down. Earlier chapters were written with too much
redundancy — near-duplicate lectures, exhaustive enumeration of every type
spelling, verbose old-style C++ — and are being cut down hard to leave more
course time for exercises and for C++ features students will actually use.
MSVC is both the reference and the target compiler for this branch —
students are expected to build locally with whatever MSVC they have
installed, not a container image. See "Building and testing" below.

**This is a different mode of work from a from-scratch rewrite.** The
workflow is:

1. **The user supplies the target lecture layout for a chapter** — the final
   lecture count, titles, and roughly what each one covers. Don't invent a
   layout yourself and don't propose restructuring beyond what's given.
   Your job is to clean up the existing lecture folders to match that
   layout, not to redesign the chapter's scope.
2. **Consolidate ruthlessly.** Where the target layout collapses several old
   lectures into one (e.g. "integer types + integer modifiers + fractional
   numbers" becoming a single "data types" lecture), merge their content,
   cut the redundant parts, and keep only what actually serves the new
   lecture's narrative. Prefer cutting content over keeping it "just in
   case" — the whole point of this pass is reclaiming time.
3. **Expect the repo to be mid-transition, not clean.** Chapter folders may
   currently contain leftover duplicates from a previous partial edit (e.g.
   both an old-style and new-style folder claiming the same lecture number,
   or two folders covering the same topic under different names). Before
   editing a chapter, list its subfolders and actually diff what's in each
   one rather than assuming the folder names reflect the current intended
   structure. Flag anything ambiguous to the user rather than guessing which
   folder is the "real" one.
4. **One running example per chapter, built up lecture by lecture**, still
   applies — don't reintroduce disconnected toy snippets when consolidating.
   Carry the chapter's existing running example (e.g. chapter 4's personal
   expense tracker) through the trimmed lecture set.
5. **Renumber folders sequentially once a chapter's content is settled** —
   no gaps, no leftover old-numbered folders sitting alongside the new ones.
   Delete folders that no longer exist as a separate lecture once their
   content has been merged elsewhere; don't leave them behind "for
   reference."
6. **Always confirm the plan before renaming/deleting folders.** Even though
   the user is now driving the target layout directly, restructuring
   recorded content is still a structural change — lay out which folders
   map to which final lecture before touching anything, unless the user has
   already given folder-level detail in their instructions.
7. **Update the chapter's `README.md`** (or add one if missing) once a
   chapter's trim is done, following the structure already used in
   `03.FirstSteps/README.md` and `04.VariablesAndDatatypes/README.md`:
   - a short intro to the running example
   - a "what does this program actually need" table mapping needs to C++
     concepts/types
   - a lecture-by-lecture summary
   - a "how C++'s latest features help" section
   - (if applicable) a capstone project section
   - a "building the code" pointer to `docker/`

## Coding conventions (enforced — do not deviate without being asked)

- **Brace initialization (`{}`) for every variable declaration, no
  exceptions** — `int decimal{15};`, `double amount{93.33};`. This applies
  even in lectures that are specifically demonstrating literal syntax (e.g.
  number systems: `int octal{017};`, `int hex{0x0F};`, `int binary{0b00001111};`).
  Bare/uninitialized declarations are never acceptable. `=`-style init is
  reserved only for a deliberate narrowing/overflow demonstration, and only
  when the lecture is explicitly teaching that pitfall.
- **Printing: `std::cout` first, then `std::print`/`std::println` as the
  modern upgrade.** Since most existing C++ code, tutorials, and
  documentation students will encounter still use `std::cout <<`, introduce
  it first in the course (chapter 3) so students recognize it. As soon as
  `<print>` is introduced, contrast the two explicitly in that lecture (old
  way vs. new way) and then **use `std::print`/`std::println` as the default
  for all lectures from that point forward** — don't keep writing new
  examples in `std::cout` after the modern form has been introduced. Never
  use `std::endl` (use `"\n"` inside a `std::print`/`std::println` format
  string, or `std::cout <<`'s own `'\n'` in the pre-`<print>` lectures).
- **No `using namespace std;`** — always qualify with `std::`.
- **Digit separators** in large literals: `1'000'000`, not `1000000`.
- **`<cstdint>` fixed-width types** (`std::int32_t`, `std::uint16_t`, ...)
  are introduced as the modern alternative once a lecture covers integer
  sizing, not as a replacement for teaching `short`/`int`/`long long` first.
- **Comments explain *why*, not *what*.** No line-by-line narration of
  obvious code. A comment earns its place by explaining a non-obvious
  constraint, a gotcha, or the reasoning behind a choice.
- **Prefer problem-solving over exhaustive enumeration.** Don't dump every
  type spelling or modifier combination back-to-back with no narrative.
  Introduce something because the running example needs it, not because it
  exists. This matters even more now than before — the whole point of this
  editing pass is cutting content that doesn't earn its place.
- **`CMakeLists.txt` per lecture folder**, always targeting
  `add_executable(rooster main.cpp)` with `CMAKE_CXX_STANDARD 23`. Copy an
  existing sibling lecture's `CMakeLists.txt`/`.gitignore` verbatim when
  scaffolding a new or renumbered folder — don't hand-roll variations.
- Check whether a later chapter already covers a concept before re-teaching
  it in an earlier chapter (e.g. chapter 5 covers operators and
  `std::numeric_limits` — don't re-explain those in chapter 4).

## Building and testing

The student will either be using the MSVC IDE or Qt Creator with any kit available. MSVC will be used by the instructor as a way to show the latest features because it is ahead, but the student on Qt Creator with an older compiler can attempt to revert to whatever their compiler supports. The instructor will point out possible gotchas so the student isn't left on their own devices.

## Working style expected on this repo

- **The user supplies the target lecture layout; you execute the cleanup
  against it.** Don't redesign chapter scope on your own initiative — if
  the given layout seems to be missing something important, ask, don't
  silently add it back.
- **Plan before restructuring.** Even with the layout given, lay out the
  concrete folder-by-folder mapping (which old lecture(s) become which new
  lecture, final numbering) and get explicit sign-off before touching
  folders.
- **Never commit unless explicitly asked.** Leave changes in the working
  tree for review.
- **Reuse existing sibling files** (`CMakeLists.txt`, `.gitignore`) instead of
  hand-writing new ones from scratch, to keep every lecture folder
  byte-for-byte consistent in its boilerplate.
