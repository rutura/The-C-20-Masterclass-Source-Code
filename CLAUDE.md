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
  taught in isolation:
  - `LiteralsAndConstants` and `ConversionsOverflowAndUnderflow` were
    dissolved into chapters 4 and 5.
  - `VariableLifetimeAndScope` (chapter 8) sits right after Loops, where `if`
    blocks and loop bodies give it real scopes to demonstrate.
  - **Chapter 9, `FunctionBasics`, is a new chapter** inserted right after
    Scope and before Arrays (chapter 10) - on the reasoning that raw arrays,
    pointers, and references are low-level tooling that shouldn't gate a
    student's first exposure to functions. Lectures 9.2-9.19 cover the ~20%
    of function knowledge that doesn't require arrays/pointers/references as
    a prerequisite (declarations, multi-file organization/linkage,
    pass-by-value, default parameters, `std::string_view` parameters,
    overloading basics, `auto` return deduction, `std::optional`, captureless
    lambdas, `static`/`inline`/recursion, `constexpr`/`consteval`).
  - **What used to be five separate "advanced functions" chapters
    (`14.Functions`, `15.GettingThingsOutOfFuntions`, `16.FunctionOverloading`,
    `18.ArgumentsToTheMainFunction`, `19.FunctionCallStackD_ebugging`) no
    longer exist as their own chapters.** Once Arrays (10), Pointers (11),
    and References (12) existed, most of their content turned out to
    *belong* there rather than in a function-specific chapter, so it was
    merged in directly: array-parameter lectures into Arrays, pass-by-pointer
    variants into Pointers, pass-by-reference variants (and bare `auto`
    deduction) into References. What was left over - output parameters,
    returning a reference/pointer and the dangling pitfalls that come with
    it, overload resolution once pointers/references exist, and `argc`/`argv`
    - doesn't reduce to "an Arrays/Pointers/References topic," so it was
    folded into chapter 9 instead (lectures 9.20 onward), keeping all
    function-related material in one place except for lambda captures.
    `FunctionsTheMisfits` was dissolved the same way earlier (static locals,
    inline, recursion, all now in chapter 9).
  - `LambdaFunctions` (chapter 21, right after Polymorphism) is the one
    function-related chapter that stayed separate, since a capture list is
    really a small class in disguise and reads better once Classes exist to
    compare it to.
  - `BitwiseOperators` (chapter 23) sits after Enums, kept deliberately
    short - most of what a course would traditionally spend 7 lectures on
    (masks, shifting, manual color packing) doesn't earn that much space in
    a course aimed at practical know-how, so it's 3 lectures ending on the
    one realistic use case (combining flags via `enum class`).
  - **`Classes` (chapter 14, right after Strings)** is a merge of what used
    to be three separate chapters - `Classes` (first classes, constructors,
    destructors, `this`, structs), `ZoomingInOnClassObjects` (const
    objects/member functions, dangling references, `mutable`, structured
    bindings), and `DivingDeepIntoConstructorsAndInitialization`
    (aggregate/designated initialization, default constructor parameters,
    delegation, `explicit`, copy/move constructors, deleted constructors) -
    moved earlier in the course and combined into one 29-lecture chapter,
    thematically reordered (basics -> const-correctness -> aggregate init ->
    advanced constructor mechanics) rather than left as three chapters
    concatenated back to back. Two near-duplicate lectures
    (`ConstObjectsAsFunctionParameters` and `ConstMemberFunctions`, which
    differed only by whether `dog.h`'s getters were marked `const`) were
    merged into a single lecture showing the const-correctness problem and
    its fix together, rather than kept as two files that were 90% identical.
  - **`Templates` (chapter 25, right after OperatorOverloading)**
    is a merge of what used to be three separate chapters -
    `FunctionTemplates`, `Concepts`, and `ClassTemplates` - concatenated in
    that order (each chapter's own internal lecture order was already a
    sensible progression, so no thematic reshuffling was needed, unlike the
    Classes merge). Placing a "class templates" chapter this early required
    checking every one of its 32 lectures for forward references to
    material taught later - two were found and fixed rather than accepted
    as-is: `ConceptsExample1` used `std::vector` (not introduced until
    `StlContainersAndIterators`) and was rewritten to use `BoxContainer`
    (already established earlier in the same chapter) instead;
    `BuiltInConcepts` defaulted `operator<=>` (not introduced until
    `OperatorOverloading`'s comparison-operator lectures) purely to feed one
    already-commented-out, never-executed `static_assert`, so that one
    member was removed rather than kept as a dependency. Two lectures still
    legitimately need `friend` (`FriendFunctionsForClassTemplates`) and
    `operator<<` overloading (`StreamInsertionOperatorForClassTemplates`) -
    both are satisfied earlier in the course (Friends, OperatorOverloading).
    `Templates` sits right after `OperatorOverloading` rather than further
    back in the course because `OperatorOverloading` itself used to have a
    soft dependency the other direction, back when its comparison-operator
    lectures were still a separate chapter (`LogicalOperatorsAndThreeWayComparison`):
    `Rel_OpsNamespace` used raw `template<class T>` syntax as an
    implementation detail without ever teaching what a template is, which
    used to read better with Templates immediately following. That chapter
    has since been merged into `OperatorOverloading` (see below) and
    `Rel_OpsNamespace`'s `my_utility.h` was de-templatized at the same time -
    it now declares ordinary (non-template) overloads for the one type
    (`Point`) the lecture actually needs, defined in a new `my_utility.cpp` -
    so the forward reference to Templates no longer exists at all, and
    `Templates` was free to move further back in the course. Before moving a
    template/concept-heavy chapter like this, actually read every lecture's
    source for forward-referenced syntax rather than assuming "templates and
    concepts" are self-contained - `std::vector` and `operator<=>` usage
    snuck in as incidental, non-essential parts of two otherwise-unrelated
    example programs, and the chapter that used to sit right before
    Templates turned out to have its own quiet reliance on template syntax.
  - **`OperatorOverloading` (chapter 18) absorbed
    `LogicalOperatorsAndThreeWayComparison`**, which no longer exists as its
    own chapter. The two were always the same broad topic (operator
    overloading, with relational/comparison operators as a specialized
    case), so the merge is a straight concatenation - `OperatorOverloading`'s
    original 19 lectures (arithmetic, subscript, stream, conversion,
    assignment, functor operators; unchanged, still 18.2-18.20) followed by
    `LogicalOperatorsAndThreeWayComparison`'s 14 lectures renumbered
    18.21-18.34 in their existing order (manual relational operators, the
    legacy `std::rel_ops` pattern, `<=>`/`std::partial_ordering`/
    `std::weak_ordering`/`std::strong_ordering`). No thematic reshuffling was
    needed - each source chapter's internal order was already sensible on
    its own, same reasoning as the Templates merge. The one content change
    was de-templatizing `Rel_OpsNamespace`'s `my_utility.h` (see the
    Templates entry above) now that it sits much further from Templates than
    it used to.
  - **Chapters 15-20 (Namespaces, SmartPointers, Friends,
    OperatorOverloading, Inheritance, and Polymorphism) were pulled forward**
    to sit right after Classes(14), on the reasoning that OOP fundamentals
    (smart-pointer-managed objects, operator overloading, inheritance,
    polymorphism) are central, practical knowledge that shouldn't wait until
    two-thirds of the way through the course. This required the same kind
    of dependency audit as the Templates move:
    - `SmartPointers` was already clean (no dependency on Friends,
      OperatorOverloading, Inheritance, Polymorphism, or Templates) - it
      only needs plain classes (Classes, already satisfied) as its demo
      vehicle, so it moved with zero content changes.
    - `Inheritance` and `Polymorphism` turned out to use `friend` +
      `operator<<` overloading as their standard, idiomatic way to print
      every object (10/11 Inheritance lectures) - not incidental, load-bearing
      throughout. Rather than rewrite dozens of lectures' printing style,
      `Friends` and `OperatorOverloading` were pulled forward too, landing
      immediately before Inheritance/Polymorphism so that idiom is already
      taught.
    - `ConstAndStaticMembers` was deliberately **not** pulled forward, since
      only a handful of lectures elsewhere needed it - moving the whole
      chapter would have been overkill. Instead, the specific lectures that
      depended on it were fixed or relocated individually (see below).
    - `Namespaces` had two lectures (`NamespacesAcrossMultipleFiles`,
      `UsingDeclarations`) that used a `Cylinder` class with a private
      `inline static const double PI` member - a `ConstAndStaticMembers`
      forward reference, but purely incidental (the `static` was never the
      point of either lecture, just an implementation detail of the demo
      class). Fixed by changing it to a plain, non-static `const double PI`
      - identical behavior, zero dependency.
    - One Polymorphism lecture, `InheritanceAndPolymorphismWithStaticMembers`,
      could not be fixed the same way - its entire subject *is* static
      members interacting with inheritance/polymorphism, so simplifying it
      away would have gutted the lesson. It was relocated instead, out of
      the (now early) Polymorphism chapter and appended to the end of
      `ConstAndStaticMembers`, which still sits later in the course - the
      one point where both prerequisites (static members and polymorphism)
      are already taught.
  - **`ProgramsWithMultipleFiles` doesn't exist as its own chapter at all
    anymore - it was folded directly into FunctionBasics and Classes as
    extra lectures.** It first got split into two chapters (because 3 of
    its 8 lectures fundamentally need classes to exist - one,
    `ForwardDeclarations`, is entirely about forward-declaring a *class* in
    a header - while the other 5 are pure free-function/variable multi-file
    organization with no class dependency at all), but a single-lecture
    "chapter" for a handful of niche lectures doesn't earn a whole chapter
    slot, so both halves were dissolved a step further:
    - The 5 class-free lectures (compiling/linking model, linkage, flipping
      linkage, inline variables/functions, inline vs. static) were inserted
      into `FunctionBasics` immediately after its existing
      `FunctionsAcrossMultipleFiles` lecture - same topic, deeper dive,
      grouped together as one continuous multi-file block rather than split
      across two places in the chapter.
    - The 3 class-dependent lectures (declarations/definitions with a
      class, one-definition-rule with a class, forward-declaring a class)
      were inserted into `Classes` immediately after its existing
      `ClassAcrossMultipleFiles` lecture, for the same reason.
    - When a chapter turns out to only deserve a handful of lectures once
      split along a prerequisite fault line, don't leave those pieces as
      their own thin chapters - fold each piece into the chapter whose
      existing lecture already covers the same idea at a more basic level,
      inserting right after that lecture (renumbering what follows) rather
      than tacking the new lectures onto the end.
  - **When merging a lecture into a chapter it topically belongs to** (not
    just renumbering it in place), append it after that chapter's existing
    lectures rather than trying to interleave it - preserves the existing
    chapter's internal order and avoids unnecessary renumbering of untouched
    lectures.
  - When dissolving a chapter, delete it outright (including its
    `C++ 20 Template Project` scaffold folder) once every lecture inside has
    been moved elsewhere or confirmed dropped - don't leave an empty
    chapter folder behind, and don't leave a gap in the numbering; renumber
    every following chapter to close it.

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
