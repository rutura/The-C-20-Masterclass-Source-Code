# The C++23/26 Masterclass — Restructuring Plan

Status: proposal, for review before rerecording begins.
Scope: this document restructures "The Modern C++20 Masterclass" into a C++23-based course (with a C++26 preview chapter), targeting a 2026 relaunch.

**Revision history:**
- v1 cut chapters based on folder/lecture *names* looking similar — lazy, and wrong in several places (verified `unique_ptr`/`shared_ptr` lectures, most of Inheritance/Polymorphism, most of Operator Overloading are legitimate scaffolding, not duplication). v2 fixed this with a real source-code audit (§1a) — every cut is now backed by a line-count/code comparison.
- v3 fixed a second, bigger problem: v2 still didn't get a student to a tangible program until **chapter 16** — merely 2 chapters earlier than the original course's chapter 18. This revision reorganized aggressively around a **Fast Path**: the actual minimum floor of C++ mechanics needed to write a real, runnable program, identified by reading source across chapters 3, 4, 10, 11, 15, 16, 43 to find the smallest true prerequisite chain (§1b). Everything not on that floor is explicitly deferred as a "depth pass," taught later on the exact same topic once the student has already shipped something.
- v4 (this revision) merges the templates story. It was previously split across three touchpoints — `24.FunctionTemplates`, `25.Concepts`, and `40.ClassTemplates` — taught 15 chapters apart. A source audit (§1d) found that ch.24+ch.25 are self-contained on free functions/primitives and merge cleanly into one "Templates I" chapter with zero rewrites, but ch.40's class-template content is architecturally a direct sequel to the OOP arc (ch.26-39) — it reuses the exact `BoxContainer`/`Point` classes, operators, and `friend` idioms built there as its teaching vehicle, and cannot be pulled forward without gutting and rewriting that entire running example. The result is a two-part "Templates" chapter: Part 1 (functions + concepts) taught early, Part 2 (class templates + concepts-on-classes) taught immediately after the OOP arc concludes — a single named topic, honestly split where the actual prerequisite chain splits it.

## 0. Goals this document addresses

1. **Get students productive as soon as physically possible.** Not "earlier than before" — genuinely as early as the language allows. See §1b for the evidence-based floor and §1c for the resulting Fast Path.
2. **Modernize to C++23, preview C++26.** Adopt `std::print`/`println`, `std::expected`, deducing `this`, `std::generator`, flat containers, new ranges views, `mdspan`, woven into the chapters that already teach their conceptual ancestors. Add a closing chapter hacking on C++26 features that genuinely compile today (GCC trunk/16.1: static reflection, contracts).
3. **Replace toy exercises with real projects.** Clone the one genuinely good running example in the course (the Box Container capstone, ch.39) into a spine of 4 running projects, the first of which now starts on **day one**, not chapter 16.
4. **Teach AI-assisted C++ development.** Two touchpoints: tool onboarding once students have real code worth assisting on, and a review/safety discipline once they know enough about memory and ownership to recognize a bad AI suggestion.
5. **Reduce total runtime while preserving/increasing value — based on verified duplication, not guesswork.** See §1a for the audit and §6 for the resulting, evidence-backed cut list.

**Numbering convention:** per user decision, historical chapter numbers are preserved so the old→new mapping stays traceable during migration. Existing chapters keep their number; net-new chapters are inserted as sub-numbered slots (e.g. `21.5` sits between old ch.21 and ch.24) rather than triggering a renumber of the whole course. Because this revision resequences the *playlist order* far more aggressively than v2, §2 (the playlist-order table) is now the load-bearing section — folder numbers no longer track teaching order at all in the first third of the course.

---

## 1a. Source-level duplication audit (evidence base for the cut list in §6)

Every lecture folder in the chapters below was actually opened and read — not inferred from folder names. Findings, with line counts and code evidence:

### Confirmed near-total duplicates (strong merge candidates)

- **`16.Functions` pass-by-X lectures (`16.5`–`16.11`, 6 lectures).** All six use the *identical* `say_age(int age)` function and identical `main()` (`int age{23}; say_age(age);`), varying only the parameter declaration and whether a `++age` line is commented out:
  - `16.5PassByValue`: `void say_age(int age)`, mutation allowed
  - `16.6PassByConstValue`: `const int age`, mutation commented out
  - `16.7PassByPointer`: `int* age`, `++(*age)`
  - `16.8PassByPointerToConst`: `const int* age`, mutation commented out
  - `16.9PassByConstPointerToConst`: `const int* const age`, mutation commented out
  - `16.10PassByReference`: `int& age`, mutation allowed
  - `16.11PassByConstReference`: `const int& age`, mutation commented out

  15-21 lines each, only the signature keyword and one commented-out line differ. **Merge all 6 into 1 lecture** with a single side-by-side comparison file/table.

- **`35.2AllLogicalOperators` / `35.3Rel_OpsNamespace`.** Near-identical `main.cpp` (21 vs 23 lines): both construct the same two `Point` objects and print the same six comparisons. Only difference: `35.3` swaps hand-written operators for the deprecated `std::rel_ops` namespace. **Merge into 1 lecture.**

- **`43.2StdVector` fully subsumed by `44.5Vector`.** `43.2` (~91 lines) covers construction/`push_back`/`pop_back`/`.at()`/`.front()`/`.back()`/`.data()`. `44.5` (~292 lines) re-teaches the *same* container with the *same* style of example, reaching everything in 43.2 in its opening third, then goes deeper (capacity, `insert`/`emplace`/`erase`/`resize`/`swap`). **Cut 43.2 entirely** — but see §1b: its *opening ~20 lines* (bare `std::vector` construction + `push_back` + range-for print, no template helper) is exactly the minimal-usage subset needed for the Fast Path, so that fragment moves to the very front of the course as new content inside the Fast Path arc, while the full 43.2 lecture-as-currently-recorded is cut as redundant with 44.5. Same subsumption pattern found for `43.3StdArray` vs `44.6Array` — cut `43.3` too.

- **`45.StlAlgorithms`'s 7 one-algorithm-per-lecture lectures, versus `46.2RangeAlgorithms` alone.** `46.2` (one lecture) re-demonstrates `sort`/`all_of`/`for_each`/`find_if`/`copy` using ranges-without-iterators syntax — the same algorithms that took 4 separate ch.45 lectures to cover individually. **Consolidate ch.45's 7 lectures into 2-3.**

- **`33.4UniquePointersAndArrays` / `33.7SharedPointersWithArrays`.** Both ~30 lines, both build a `Dog[]` array via smart pointer, differing mainly in construction syntax. **Merge into one lecture.**

- **`07.ConversionsOverflowAndUnderflow`** (3 lectures, ~75 lines total). Confirmed thin. Ch.05 has zero existing conversion/cast content (verified via grep), so fold into ch.05 as 1-2 lectures without losing any concept.

- **`22.FunctionsTheMisfits`** (74 lines/3 lectures) and **`23.FunctionCallStackD_ebugging`** (56 lines/2 lectures) — both short, self-contained, no interdependency. **Fold into ch.19** as one combined lecture pair.

- **`11.14FixCalculator`** (~30 lines) — its teaching point (switch-based dispatch) reappears, expanded, inside `18.3`/`18.4`. **Cut** — and further superseded by the Fast Path's own Day-1 project (§1c), which is a stronger vehicle for the same "put loops+conditionals to work" goal.

### Investigated and found to be legitimate scaffolding — NOT cut

- **`25.Concepts` vs `40.ClassTemplates` lectures 40.12-40.16.** Ch.25 teaches concept *syntax* on a trivial free function — thin and over-split internally, but ch.40's lectures apply concepts to a real class template (`BoxContainer<T>`), a context ch.25 never covers. **Keep both chapters; compress only ch.25's own internal 5 lectures to 2-3.**
- **`33.SmartPointers` unique_ptr/shared_ptr pairs (6 of 8 lectures).** `shared_ptr`'s reference-counting content (`use_count()`, multiple owners, `reset()` propagation) is genuinely new material versus `unique_ptr`, not a search-and-replace. **Only merge the array lectures (33.4/33.7); keep the other 6 distinct.**
- **`34.OperatorOverloading` vs `35.LogicalOperatorsAndThreeWayComparison`.** Ch.34 has **zero** equality/`<=>` content and scaffolds one new operator per lecture onto a single `Point` class — legitimate progression. **Keep as separate chapters.**
- **`36.Inheritance` vs `37.Polymorphism`.** Ch.36 uses entirely distinct examples (`Person`/`Player`, `Person`/`Engineer`/`CivilEngineer`) with zero overlap with ch.37's Shape/Animal families. **Keep as separate chapters**; one small internal cut inside ch.37 (`37.5`+`37.6` merge — `37.6`'s raw-pointer loop is a literal subset of code already present, commented out, in `37.5`).

### Folder-numbering clarification (cosmetic, not a content finding)

Chapter 47 folders are internally prefixed `40.x` (10 folders), chapter 48 (Coroutines) folders are internally prefixed `47.x` (5 folders), chapter 49 (Modules) folders are internally prefixed `48.x` (15 folders) — leftover from an earlier chapter-reordering commit. Cosmetic; fix during those chapters' re-record passes.

### Confirmed NOT redundant (spot checks)

- `12.7Practice_FortuneTellerV1` / `12.10Practice_FortuneTellerV2` — legitimate "naive way, then improved" pair. Replaced by the project spine regardless (§3), not because they were redundant with each other.
- `18.3CalculatorV1` / `18.4CalculatorV2` — teach different things (interactive I/O loop vs. `argc`/`argv` parsing), not duplicates.
- `43.4`-`43.9` (iterator mechanics) — ch.44 only uses iterators incidentally; this is ch.43's genuine, non-overlapping unique value once 43.2/43.3 are cut.

---

## 1d. Templates consolidation audit — why it's one topic in two parts, not one continuous chapter

A full source read of `24.FunctionTemplates` (15 lectures), `25.Concepts` (5 lectures), and `40.ClassTemplates` (12 lectures, including its concepts-specific lectures `40.12`-`40.16`) to determine whether all three can become a single unified "Templates" chapter.

**Ch.24 (Function Templates) — all 15 lectures (`24.2`-`24.16`) use only free functions on fundamental types (int, double, char, `std::string`, raw pointers/arrays), never a user-defined class:** basic type deduction, explicit template args, template params by reference, specialization, overloading vs. templates, multi-param templates, `auto`/`decltype(auto)` return deduction, default template args, non-type template parameters, abbreviated function templates, named template params for generic lambdas, type traits + `static_assert`, `if constexpr`.

**Ch.25 (Concepts) — all 5 lectures (`25.2`-`25.6`) constrain function templates exclusively, using only `int`/`char`/`double`/`long long`, zero classes anywhere.** It could sit immediately after ch.24 with no OOP prerequisite at all.

**Verdict on ch.24+25: fully unifiable, today, with no rewrites.** No dependency in either direction beyond the obvious (concepts build on templates); merge into one continuous chapter, "**Templates I: Function Templates & Concepts**."

**Ch.40 (Class Templates) — the picture is different.** Its running example (`BoxContainer<T>`) is not an independent topic — it's a direct, deliberate continuation of the `Practice-BoxContainerType` capstone (old ch.39) and everything that seeded it:

- Ch.39's `IntContainer`/`DoubleContainer`/`CharContainer` classes (built via inheritance + `virtual stream_insert`, i.e. ch.36/37 material) exist specifically to demonstrate the code-duplication pain that class templates solve. Ch.40's `40.2YourFirstClassTemplate` collapses those duplicate classes into one `template <typename T> class BoxContainer` — the explicit payoff of the setup ch.39 built.
- Every `BoxContainer<T>` version across ch.40 reuses: custom copy constructor/destructor (ch.26/28), `operator+=`/`operator=`/free `operator+`/`operator<<` (ch.34, mirroring 34.6/34.7 almost exactly), `friend` (ch.29, explicit in `40.10FriendFunctionsForClassTemplates` and `40.11`/`40.12`+), and `std::weak_ordering operator<=>(...) = default` (ch.35's spaceship operator, used directly in `40.14BuiltInConcepts`).
- The 7 real non-concepts lectures (`40.2`, `40.4`, `40.5`, `40.7`, `40.8`, `40.10`, `40.11` — no `40.1`/`40.3`/`40.6`/`40.9`) each build a class template with constructors/destructors/copy-semantics/operator-overloads structurally identical to the non-template classes taught in ch.26-35. None of this content exists independent of that lineage.

**Verdict on ch.40: cannot be pulled forward without rewriting its entire teaching vehicle from scratch.** There is no version of "class templates" content in this repo that doesn't lean on Classes, Friends, Static/Const Members, Operator Overloading, and the Spaceship operator having already been taught — and separating it from the ch.39 capstone it directly answers would break the "here's the pain point, here's the fix" narrative that makes ch.40 land in the first place.

**Resolution: one named topic, two parts, separated by the OOP arc that ch.40's example depends on —**
- **Templates I: Functions & Concepts** = current ch.24 + ch.25 (20 lectures, merges cleanly, taught where ch.24 sits today — right after ch.23/19, before Classes).
- *(the entire Classes/OOP arc — ch.26 through ch.38.5 — happens in between, unchanged; ch.39/38.5's capstone is not filler, it's the narrative setup for Part 2's payoff and must not be separated from it)*
- **Templates II: Class Templates & Constraining Them** = current ch.40 (12 lectures: `40.2`-`40.16`), taught immediately after the Box Container Capstone (ch.38.5), exactly where ch.40 sits today.

This is presented to students as **one topic explicitly split into two parts** ("Templates, Part 1" early, "Templates, Part 2" once you know classes) rather than as two unrelated chapters that happen to both mention `template<>` — the throughline is named and cross-referenced in both directions so it doesn't read as an accident of the syllabus.

---

## 1b. The real floor: what does a student actually need before writing something tangible?

This is the key evidence for the reorganization. Read in full: chapters 03, 04, 10, 11, 15, 16, 18, 39, and the vector-related lectures in 43/44. Per-chapter findings:

| Chapter | True floor (lecture-level) | What it unlocks | Everything else in the chapter |
|---|---|---|---|
| 03 FirstSteps | **3.2** (first program), **3.5** (statements — a full function with params/return is demoed here informally, plus braced-init variables), **3.6** (`std::cin`, `std::getline`, `std::cerr`) | Compile, print, and **read input** — `std::cin`/`getline` land here, lecture 6 of chapter 1 | 3.3 (comments), 3.4 (errors/warnings) are conceptual asides, not gating |
| 04 VariablesAndDatatypes | **4.3** (declare `int`, braced-init), **4.6** (`bool` + `if`), **4.8** (`auto`, trimmed to 2 examples), **4.9** (re-assignment) | Store and mutate simple data | 4.2 (number systems), 4.4 (int modifiers), 4.5 (floats depth), 4.7 (char/ASCII) are depth/polish, deferrable |
| 10 FlowControl | **10.2** (if/else), **10.3** (else-if) | Make a decision, branch a menu | 10.4 (switch) onward (short-circuit, ternary, `if constexpr`, init-statements, scope corner cases) are variants/depth |
| 11 Loops | **11.2** (indexed for), **11.5** (range-based for — demoed over a raw array/brace-list, contrasted directly against the indexed version in the same file) | Repeat an action, iterate a collection **without needing pointers or manual indexing** | 11.3/11.4 (multi-declaration, comma operator), 11.6-11.15 (while, do-while, nested, infinite, break/continue, FixCalculator) are depth/variants |
| 15 Strings | **15.6** (declare/print `std::string`), first third of **15.7** (`+` concatenation) | Store and print real text, not just `char` | 15.8+ (indexed char access, `.at()`), 15.2-15.4 (C-strings), 15.9-15.19 (the full method tour, `string_view`) are depth, deferrable |
| 43 Vector | Opening ~20 lines of **43.2** (brace-init construction, `push_back`, indexing) — **printed via a plain range-based for-loop, not the lecture's own template-based print helper**, to avoid pulling in templates early | Store a growable list of things (tasks, notes, scores) | The rest of 43.2 (`.at()`/`.front()`/`.back()`/`.data()`) plus all of 43.3-43.9 and 44 are depth, deferrable |
| 16 Functions | **16.2** (a single lecture already demonstrates void+param, value-returning, no-param void, no-param-returning-value, and pass-by-value-copy — informally, no theory needed), **16.3** (declaration vs. definition, only needed once a program has 2+ functions) | Package repeated logic into a named, callable, optionally value-returning unit | 16.5-16.24 (the six pass-by-X variants, array params, default params, multi-file compilation, implicit conversions, string_view params, constexpr/consteval) are all depth, deferrable — confirmed none of it is needed to write or call a simple function |

**Bottom line, stated plainly:** a student can write, compile, and run a genuinely tangible small program — one that reads input, stores a growable list of it, makes decisions, loops over it, and organizes the logic into functions — using only about **14-15 lectures total**, none of which require pointers, classes, templates, operator overloading, or multi-file builds. That floor spans what are *currently* chapters 3, 4, 10, 11, 15, 16, and a fragment of 43 — i.e., it's achievable well before the old chapter 16, let alone chapter 18.

Two chapters that looked like natural "first project" homes are explicitly **not** part of this floor, and here's why, so the "why not just use X" question has a documented answer:

- **`18.ArgumentsToTheMainFunction`'s calculators (18.3/18.4)** actually require a *harder* prerequisite chain than the Fast Path: `argc`/`char** argv` (raw pointer/array of C-strings), `argv[i]` indexing, `atof`, C-string comparison — i.e., pointers and C-strings, which the Fast Path deliberately avoids needing up front. Ch.18 stays where conceptually appropriate (after functions, alongside enums) but is not the Day-1 vehicle.
- **`39.Practice-BoxContainerType`** requires classes with constructors/destructors, operator overloading, and multi-file builds — an OOP capstone, correctly positioned deep in the course, not a Day-1 candidate.

---

## 1c. The Fast Path — restructured opening arc

This replaces the old "chapters 3 through 16 in numeric order, project shows up at the end" shape with a **spiral**: hit the floor lectures first across chapters 3/4/10/11/15/16/43, ship a real program by the end of week one, then circle back and go deep on each of those same chapters afterward — using the depth lectures identified in §1b as their own later pass, not cut, just resequenced.

**New Chapter 00 — "Ship Something on Day One" *(NEW, sits before the renumbered fast-path pass through 03/04/10/11/15/16/43)*:**

A single short chapter (4-5 lectures) that sequences the exact floor lectures from §1b back-to-back, in this order, each retaught in miniature (5-10 min, not the full original lecture) purely to the extent needed to keep building:

1. Compile/print/read input (3.2, 3.5, 3.6 compressed) — "hello world" straight into `std::print`/`std::println` (C++23) and `std::cin`/`getline`.
2. Store data: `int`, `bool`, `auto`, `std::string` (4.3/4.6/4.8/4.9 + 15.6 + start of 15.7 compressed) — enough to hold a task's text and a done/not-done flag.
3. Decide and repeat: `if`/`else if` (10.2/10.3) + indexed and range-based `for` (11.2/11.5) — enough to loop over a menu and a list.
4. Hold a growable list: `std::vector<std::string>` construction/`push_back`/range-for print (opening fragment of 43.2, retaught minimally, printed with a plain range-for loop — no templates yet).
5. Package it into functions: a `add_task`, `list_tasks`, `remove_task` split (16.2/16.3 compressed) — informally, no pass-by-X theory yet.

**Project 1 (Task Tracker CLI) is introduced at the end of this chapter — Day One, not chapter 16.** By the end of ch.00, the student has a working, if unpolished, command-line task list: add a task, list tasks, mark done, loop until they quit. This is the single biggest change from v2: the project moves from ch.16 to ch.00, roughly **16 chapters earlier**.

**Then the course loops back** and takes each topic touched in ch.00 to its full depth, in this order, explicitly framed each time as "you already used this informally in your first project — now let's understand it properly":

- Ch.03 (full) — the conceptual asides (errors/warnings) plus anything not already hit.
- Ch.04 (full) — number systems, int modifiers, float depth, char/ASCII — all the "why does this matter" material.
- Ch.05 Operators, Ch.06 Literals/Constants, Ch.08 Bitwise (deferred further, alongside Pointers), Ch.09 Scope.
- Ch.10 (full) — switch, ternary, short-circuit, `if constexpr`, init-statements.
- Ch.11 (full) — while/do-while, nested loops, break/continue.
- Ch.12 Arrays, with `std::array` added — **Project 1 gets fixed-size lookup tables here** (e.g. priority-level names).
- Ch.15 (full) — the complete `std::string` method tour, C-strings, `string_view` — **Project 1's text handling deepens here** (trimming, searching task text).
- Ch.16 (full) — now the six pass-by-X variants (merged to 1 lecture per §1a), default params, array params, implicit conversions, `string_view` params, constexpr/consteval — **Project 1's functions get properly typed parameter-passing** here instead of the ad hoc versions from ch.00.
- Ch.17 Enums, Ch.18 argv (both kept, not cut — argv becomes "Project 1 now takes CLI flags").
- Ch.19 Functions II — `std::optional`/`std::expected` — **Project 1's error handling upgrades from ad hoc to proper.**
- Ch.43/44 (full container tour, once 43.2/43.3 are cut per §1a) — **Project 1's storage upgrades from `std::vector` to `std::flat_map`.**

This "spiral" shape (floor first, depth pass after, explicitly reconnected to the same running project) is the structural fix — it is not simply moving the project earlier, it's rebuilding the whole opening third of the course around motivating *why* the depth matters, since the student has already felt the absence of that depth in their own Day-1 code (e.g. they'll have hit an unhandled bad-input case in ch.00 that `std::expected` in ch.19 then properly fixes).

---

## 2. Full playlist order (what students actually see, in order)

Folder numbers no longer track teaching order in the first third of the course — this table is now the authoritative sequence. Folder numbers remain the source-code/traceability reference (§9).

**Arc 1 — Ship something (new ch.00, ~5 lectures):** 00 (Fast Path: compressed 3.2/3.5/3.6 → 4.3/4.6/4.8/4.9 → 15.6/15.7-start → 10.2/10.3 → 11.2/11.5 → 43.2-fragment → 16.2/16.3) → **Project 1 v0 shipped.**

**Arc 2 — Depth pass on the fast-path topics:** 03(full) → 04(full) → 05 → 06 → 09 → 10(full) → 11(full) → 12(+`std::array`, Project 1 gains lookup tables) → 15(full, Project 1's string handling deepens) → 16(full, pass-by-X merged, Project 1's functions properly typed) → 17 → 18(argv, Project 1 gains CLI flags) → 19(`std::expected`, Project 1's error handling upgrades) → 20/21 → 21.5(AI-I).

**Arc 3 — Templates I, then OOP and generics, then Templates II:** 24/25 (**Templates I: Functions & Concepts**, merged, 25 compressed) → 26(Project 2 GenericBox intro) → 27/28(+deducing `this`) → 29/30 → 31/32 → 34 → 35(35.2/35.3 merged) → 36(Project 3 MiniGrep intro) → 37(37.5/37.6 merged) → 38(vs. `std::expected` reframe) → 38.5(Box Container Capstone) → 40 (**Templates II: Class Templates & Constraining Them**, Project 4 MiniJSON intro).

**Arc 4 — Systems layer ("how it really works," deliberately last, not first):** 13(Pointers) → 14(References) → 33(SmartPointers, only 33.4/33.7 merged) → 08(Bitwise) → 41(MoveSemantics) → 42.

**Arc 5 — STL depth, tooling, and close:** 43/44(full container tour, 43.2/43.3 cut, flat_map/flat_set added, Project 1 storage upgrade) → 45(consolidated)/46(+C++23 views/mdspan) → 47/48(+`std::generator`) → 49(Modules) → 49.5(AI-II) → 49.6(Final Capstone) → 50(C++26 Hacking Preview).

**Why pointers move to Arc 4, deliberately last among "core mechanics":** the Fast Path proves a student can build, extend, and even error-handle a real program using only `std::string`/`std::vector`/references-via-functions, with zero raw pointers. Pointers/manual memory become "how the safe abstractions you've been using for 20+ chapters actually work under the hood" — a stronger motivating frame than "here's a pointer, trust me it'll matter later," and it matches the pedagogy precedent from Stroustrup's own PPP textbook (cited in the original research pass behind this document).

---

## 3. The annotated curriculum (chapter-by-chapter detail)

Legend for **Tier**: **A** = keep as-is, **B** = minor edit, **C** = re-record, **D** = net-new.

| Ch. | Title | New scope | Lectures (was → now) | Tier |
|---|---|---|---|---|
| **00** | **Ship Something on Day One** *(NEW)* | Compressed floor lectures from §1b, sequenced to produce a working CLI task tracker by the end of the chapter. Not a replacement for chapters 3/4/10/11/15/16 — those are still taught in full in Arc 2, this is a fast, shallow first pass purely to get something running. | 0 → 5 | D |
| 03 | FirstSteps | Full depth pass in Arc 2 (student already saw 3.2/3.5/3.6 in ch.00); add `std::print`/`std::println` from the very first exposure in ch.00 itself. | 5 → 5 | B |
| 04 | VariablesAndDatatypes | Full depth pass in Arc 2. Unchanged content otherwise, C++23 standard bump. | 8 → 8 | A |
| 05 | OperationsOnData | Absorbs old ch.07 (Conversions/Overflow/Underflow, ~75 lines) as 1-2 added lectures. | 10+3 → 11-12 | B |
| 06 | LiteralsAndConstants | Unchanged. | 4 → 4 | A |
| ~~07~~ | ~~ConversionsOverflowAndUnderflow~~ | Cut as standalone chapter — folded into ch.05. | 3 → 0 | — |
| 08 | BitwiseOperators | Moved to Arc 4 ("under the hood"), alongside Pointers/Memory. Content unchanged. | 7 → 7 | A |
| 09 | VariableLifetimeAndScope | Unchanged. | 1 → 1 | A |
| 10 | FlowControl | Full depth pass in Arc 2 (student already saw 10.2/10.3 in ch.00). | 11 → 11 | A |
| 11 | Loops | Full depth pass in Arc 2 (student already saw 11.2/11.5 in ch.00). Drops `11.14FixCalculator` — subsumed by Project 1. | 14 → 13 | B |
| 12 | Arrays | Add `std::array`. Project 1 gains fixed-size lookup tables here. Drops both Fortune Teller lectures (replaced by Project 1 continuity, not because they were bad content). | 9 → 7 | B |
| 13 | Pointers | Moved to Arc 4, deliberately late — "how the safe abstractions work under the hood," after students have shipped real programs without needing pointers at all. Content unchanged. | 17 → 17 | A |
| 14 | References | Taught alongside ch.13 in Arc 4. Unchanged. | 4 → 4 | A |
| 15 | CharacterManipulationAndStrings | Student already saw 15.6/start-of-15.7 in ch.00; full depth pass (C-strings, `.at()`, full method tour, `string_view`) here in Arc 2. Project 1's string handling deepens (trimming, searching). | 17 → 17 | B |
| 16 | Functions | Student already saw 16.2/16.3 informally in ch.00; full depth pass here — pass-by-X (16.5-16.11) merged to 1 comparison lecture (confirmed byte-for-byte duplicates, §1a), plus default params/array params/implicit conversions/`string_view` params/constexpr-consteval. Project 1's functions get properly typed parameter passing. | 22 → 16-17 | C |
| 17 | EnumsAndTypeAliases | Unchanged. | 4 → 4 | A |
| 18 | ArgumentsToTheMainFunction | Kept as-is — both calculators confirmed non-redundant with each other. Project 1 gains CLI flags here. | 3 → 3 | A |
| 19 | GettingThingsOutOfFuntions | Add `std::expected<T,E>` + monadic ops alongside `std::optional`. Absorbs ch.22/23 (confirmed short/foldable). Project 1's error handling upgrades from ad hoc (ch.00) to proper here. | 12+3+2 → 15-16 | C |
| 20 | FunctionOverloading | Merge with ch.21 (Lambdas) — boundary merge only, no internal duplication found. | 7+3 → 9-10 | B |
| 21 | LambdaFunctions | Merged into ch.20. | (see ch.20) | B |
| **21.5** | **AI-Assisted C++ Development I: Tools of the Trade** *(NEW)* | Copilot/Claude Code setup, prompting for boilerplate + STL-idiom suggestions, MCP-based repo context. Placed once students have two real projects' worth of code (ch.00's tracker plus everything since) to meaningfully evaluate AI suggestions against. | 0 → 4 | D |
| ~~22~~ | ~~FunctionsTheMisfits~~ | Folded into ch.19. | 3 → 0 | — |
| ~~23~~ | ~~FunctionCallStackD_ebugging~~ | Folded into ch.19. | 2 → 0 | — |
| 24 | **Templates I, Part A: Function Templates** | Merged with ch.25 into one continuous chapter, "Templates I: Functions & Concepts" (confirmed fully unifiable with zero rewrites, §1d — both are free-function/primitive-only, no OOP dependency). Content itself unchanged. | 15 → 15 | A |
| 25 | **Templates I, Part B: Concepts** | Taught immediately after ch.24 as the second half of the same chapter, not a separate one. NOT merged with ch.40 (confirmed distinct content requiring the OOP arc first, §1d). Internal compression only: 5 lectures re-teaching concept syntax on the same trivial `add()` function collapse to 2-3. | 5 → 2-3 | C |
| 26 | Classes | **Project 2 (GenericBox) introduced here** as a first hand-built, non-generic value type. | 11 → 11 | B |
| 27 | ZoomingInOnClassObjects | Merge with ch.28. Add **deducing `this`**. | 7+12 → 17-18 | C |
| 28 | DivingDeepIntoConstructorsAndInitialization | Merged into ch.27. | (see ch.27) | C |
| 29 | Friends | Merge with ch.30 — boundary merge only. | 2+9 → 11 | B |
| 30 | ConstAndStaticMembers | Merged into ch.29. | (see ch.29) | B |
| 31 | Namespaces | Merge with ch.32 — boundary merge only. | 8+8 → 14-16 | B |
| 32 | ProgramsWithMultipleFiles | Merged into ch.31. | (see ch.31) | B |
| 33 | SmartPointers | Moved to Arc 4. Only `33.4`/`33.7` merged (confirmed genuine duplicate); other 6 lectures kept distinct (confirmed genuinely different content, §1a). | 8 → 7 | B |
| 34 | OperatorOverloading | Kept as its own chapter — confirmed no overlap with ch.35. | 19 → 19 | A |
| 35 | LogicalOperatorsAndThreeWayComparison | Kept as its own chapter. Internal cut: `35.2`/`35.3` merge (confirmed near-identical). | 14 → 13 | B |
| 36 | Inheritance | Kept as its own chapter — confirmed no overlap with ch.37. **Project 3 (MiniGrep) introduced here.** | 11 → 11 | B |
| 37 | Polymorphism | Kept as its own chapter. Internal cut: `37.5`/`37.6` merge (confirmed subset relationship). | 19 → 18 | B |
| 38 | Exceptions | Re-framed with explicit comparative teaching against `std::expected` from ch.19. | 16 → 14 | C |
| **38.5** | **Project Capstone: The Box Container Type** *(was ch.39)* | Built from Project 2's foundation — "now make it generic." Core material unchanged. | 5 → 6 | A |
| 40 | **Templates II: Class Templates & Constraining Them** | The direct sequel to Templates I, taught here — immediately after the Box Container Capstone (ch.38.5) it answers — rather than pulled forward next to ch.24/25, because its entire running example (`BoxContainer<T>`) reuses classes/friends/operators/spaceship from the OOP arc as its teaching vehicle (confirmed, §1d). Concepts lectures (40.12-40.16) stay here (confirmed distinct from ch.25's function-level teaching, not moved). **Project 4 (MiniJSON) introduced here.** | 12 → 12 | A |
| 41 | MoveSemantics | Moved to Arc 4. Unchanged. | 8 → 8 | A |
| 42 | FunctionLikeEntities | Moved to Arc 4. No confirmed internal duplication — unchanged pending closer audit. | 14 → 14 | A |
| 43 | StlContainersAndIterators | `43.2`/`43.3` cut (confirmed fully subsumed by `44.5`/`44.6`); their minimal-usage opening fragment already moved to ch.00. Remaining iterator-mechanics lectures (43.4-43.9) kept — confirmed unique value. Project 1's storage upgrades to `std::flat_map` here. | 7 → 5 | C |
| 44 | ZoomingOnSTLContainers | Add `std::flat_map`/`std::flat_set`. Remaining 11 of 13 lectures confirmed non-overlapping with ch.43. | 13 → 14-15 | B |
| 45 | StlAlgorithms | Confirmed cut: 7 lectures consolidate to 2-3 (proven over-split, §1a). | 7 → 2-3 | C |
| 46 | RangesLibraryInCpp20 | Add C++23 views (`zip`/`chunk`/`slide`/`enumerate`) + `mdspan`. Existing 46.3-46.7 confirmed non-overlapping with ch.45. | 6 → 8-9 | C |
| 47 | BuildingIteratorsForCustomContainers | Not deep-audited for internal duplication — unchanged pending closer read. | 10 → 10 | A |
| 48 | Coroutines | Add `std::generator` (removes confirmed "need 3rd-party library" caveat). Fix internal `47.x`-prefix folder-naming leftover. | 5 → 5-6 | C |
| 49 | Modules | Unchanged content, keeps per-compiler manual build docs. GenericBox (Project 2) modularized here. Fix internal `48.x`-prefix folder-naming leftover. | 15 → 10-11 | A |
| **49.5** | **AI-Assisted C++ Development II: Review, Safety & Sanitizers** *(NEW)* | Reviewing AI-generated C++ like a junior's PR. Mandatory ASan/UBSan pass. Live demo catching an AI-introduced memory bug. Placed after Pointers/Smart Pointers/Move Semantics (Arc 4) so students can recognize a memory-safety bug when they see one. | 0 → 4 | D |
| **49.6** | **Final Capstone Build** *(NEW)* | Students combine two project-spine projects (recommended: Task Tracker + MiniJSON) into one finished, tested application, using AI assistance plus the ch.49.5 review checklist. | 0 → 6 | D |
| **50** | **C++26 Hacking Preview** *(NEW)* | Static reflection (P2996), Contracts, placeholder `_`, conceptual senders/receivers demo via stdexec. Placed last — never a prerequisite for anything else. | 0 → 8 | D |

**Total: roughly 355-370 lectures**, down from ~460 lecture-equivalent folders today (~20-23% reduction, evidence-backed per §1a). This revision adds ~5 lectures (ch.00) versus v2's count, but the reduction is otherwise unchanged — the win in this revision is entirely about **when** students reach a working program, not lecture count.

---

## 4. The project spine

Four projects. Each is a CLI program, uses `std::print`/`println` from day one, and gets an explicit "extend this" prompt at every revisit point. **Project 1 now starts in ch.00, not ch.16 — a ~16-chapter pull-forward from v2, and the single biggest change in this revision.**

### Project 1 — Task Tracker CLI

A command-line task list: add/list/remove/mark-done tasks, held in memory.

- **v0 shipped in ch.00 (Day One):** ad hoc functions, `std::vector<std::string>`, `if`/`for`, no error handling, no CLI flags, no proper typed parameter passing — deliberately rough, since the goal is momentum, not correctness.
- **Extended, in playlist order:**
  | Chapter | Extension |
  |---|---|
  | 12 (Arrays/std::array) | Fixed-size priority-level lookup table. |
  | 15 (Strings, full depth) | Trimming/searching task text properly. |
  | 16 (Functions, full depth) | Ad hoc parameter passing replaced with properly typed pass-by-reference/const-reference. |
  | 18 (argv) | Runs via CLI flags (`--add`, `--list`). |
  | 19 (Functions II) | Ad hoc error handling replaced with `std::expected<Task, TaskError>`. |
  | 34 (Operator Overloading) | `operator<=>` added to sort tasks by priority/due-date. |
  | 44 (STL Containers) | Internal storage swapped to `std::flat_map<int, Task>` keyed by task ID. |
  | 46 (Ranges) | Filter/sort via `views::filter`, `views::zip` against a tags vector. |

### Project 2 — GenericBox

A generic value-holder type — the existing Box Container pattern (ch.39), cloned earlier and grown incrementally.

- **Introduced:** ch.26 (Classes) as a non-generic first version.
- **Extended:** ch.27/28 (constructors, deducing `this`) → ch.29/30 (const/static/friends) → ch.34 (operators) → ch.38.5 (capstone — "now make it generic") → ch.40 (templatized) → ch.33 (`unique_ptr<T[]>` storage) → ch.41 (move semantics) → ch.47/48 (iterator + generator view) → ch.49 (modularized).

### Project 3 — MiniGrep

A text-search / line-filter CLI utility.

- **Introduced:** ch.36 (Inheritance) — `Matcher` base, `LiteralMatcher`/`RegexMatcher`/`WildcardMatcher` derived.
- **Extended:** ch.37 (virtual dispatch, polymorphic storage) → ch.38 (exceptions vs. `std::expected` comparison) → ch.13 (raw-pointer buffer demo, then fixed) → ch.42 (`std::function` predicates vs. virtual dispatch) → ch.44/46 (ranges pipelines).

### Project 4 — MiniJSON

A tiny structured-data reader/writer.

- **Introduced:** ch.40 (Class Templates) — templated `Value` variant-like type.
- **Extended:** ch.44 (`std::flat_map` object storage) → ch.46 (`std::mdspan` for matrix-shaped values) → ch.47/48 (`std::generator` streaming parser) → ch.49.6 (final capstone, paired with Project 1).

---

## 5. AI-assisted development — two touchpoints

**Ch.21.5 — Tools of the Trade.** Placed after Overloading/Lambdas, once students have real, nontrivial code (both the Day-1 tracker and everything since) to evaluate AI suggestions against. Covers Copilot/Claude Code setup, prompting patterns, MCP-based repo context. Kept short (4 lectures).

**Ch.49.5 — Review, Safety & Sanitizers.** Placed after Arc 4 (Pointers/Smart Pointers/Move Semantics) and Modules, right before the Final Capstone — only works once students can recognize a memory-safety bug. Covers reviewing AI-generated C++ like a junior's PR, mandatory ASan/UBSan pass, live bug-catching demo, CVE/vulnerability-rate stats as motivation.

---

## 6. C++26 Hacking Preview (ch.50) — placement and scope

Placed last, explicitly a preview, never a prerequisite for anything else.

Scope (~8 lectures): (1) trunk GCC setup + feature-test macros, (2)-(3) static reflection (`^^`, `std::meta::info`, applied to `GenericBox`/`MiniJSON::Value`), (4)-(5) Contracts (`[[pre:]]`/`[[post:]]`, `contract_assert`, contrasted against `std::expected`/exceptions), (6) placeholder `_`, (7) `std::execution`/stdexec conceptual demo, (8) mention-only wrap-up (`std::linalg`, pattern matching — not reliably runnable yet, no graded exercises).

---

## 7. What we cut, and why (each backed by the §1a audit)

- **`16.Functions` pass-by-X (6 lectures → 1).** Verified byte-for-byte structural duplicates.
- **`35.2`/`35.3` (2 → 1).** Near-identical `main.cpp`; only a deprecated-namespace framing differs.
- **`43.2StdVector`/`43.3StdArray` (2 → 0 as standalone lectures).** Confirmed subsumed line-by-line by `44.5`/`44.6`; minimal-usage fragment repurposed into ch.00 instead of lost.
- **`45.StlAlgorithms` (7 → 2-3).** Proven over-split — `46.2` alone already re-covers 4 of the 7 algorithms.
- **`33.4`/`33.7` (2 → 1).** The one genuinely parallel smart-pointer pair.
- **`25.Concepts` internal compression (5 → 2-3).** All five re-teach syntax on the same trivial function.
- **`37.5`/`37.6` (2 → 1).** `37.6` is a literal subset of `37.5`'s already-present code.
- **Ch.07 (3 lectures) folded into ch.05.** Confirmed thin, ~75 lines total.
- **Ch.22+ch.23 (5 lectures) folded into ch.19.** Confirmed short, self-contained.
- **`11.14FixCalculator` dropped.** Subsumed by ch.18's calculators, and now further superseded by Project 1's Day-1 milestone.
- **Both Fortune Teller lectures and both original-position calculators' standalone-toy role dropped** — not because they were bad or redundant with each other (confirmed they weren't), but because Project 1 replaces them as the continuous motivating thread; the calculators themselves stay in ch.18 as real teaching content for argv.

- **Ch.24 + ch.25 merged into one chapter, "Templates I: Functions & Concepts" (20 lectures, 5 compressed to 2-3 within it).** Confirmed fully unifiable — both are free-function/primitive-only content with no OOP dependency (§1d). This is a genuine chapter-count reduction (2 chapters → 1), not just a relabeling.

**Explicitly reversed from v1, confirmed correct in v2/v3, unchanged in this revision:** ch.33 is not condensed wholesale; ch.34/35 are not merged; ch.36/37 are not merged as chapters. See §1a for the evidence. **Ch.25 is still not merged with ch.40** (that finding stands, §1d) — but ch.24 and ch.25 are now merged with *each other*, which v1-v3 hadn't considered since they were evaluating ch.25 only against ch.40.

**Not cut, confirmed correctly sized:** Modules (ch.49), Box Container capstone (ch.38.5), ch.13/14, ch.18 (both calculators), ch.42, ch.47.

---

## 8. Migration / re-recording effort tiers

**Tier A — Keep as-is:** ch.04, ch.06, ch.08, ch.09, ch.10, ch.13, ch.14, ch.18, ch.24 (content unchanged, now Part A of Templates I), ch.34, ch.38.5, ch.40 (content unchanged, now "Templates II"), ch.41, ch.42, ch.47, ch.49.

**Tier B — Minor edit:** ch.03, ch.05, ch.11, ch.12, ch.15, ch.20/21, ch.26, ch.29/30, ch.31/32, ch.33, ch.35, ch.36, ch.37, ch.44.

**Tier C — Re-record:** ch.16 (pass-by-X consolidation + full depth pass), ch.19 (`std::expected` + absorbs 22/23), ch.25 (internal compression), ch.27/28 (merge + deducing `this`), ch.38 (comparative reframe), ch.43 (cuts 43.2/43.3), ch.45 (consolidation), ch.46 (C++23 views/mdspan), ch.48 (`std::generator`).

**Tier D — Net-new:** **ch.00 (Fast Path/Day-1 project — new top priority, since every other reordering downstream depends on this existing first)**, ch.21.5 (AI-I), ch.49.5 (AI-II), ch.49.6 (Final Capstone), ch.50 (C++26 Hacking Preview), plus project-spine milestone segments woven through Tier B/C chapters.

**Recording-order recommendation:** build ch.00 first, before anything else in this plan — it's the highest-leverage new content (fixes the core "productive fast" goal on its own) and is a short, self-contained chapter that can be scripted and test-recorded quickly to validate the whole Fast Path concept before committing to resequencing the rest of the course around it.

---

## 9. Tooling notes

- Every lecture folder already has its own `CMakeLists.txt` pinned to `CXX_STANDARD 20` (461 files). Bump to `CXX_STANDARD 23` across all retained folders as a mechanical first pass.
- New ch.00 needs its own folder + CMakeLists following the established convention — likely 5 sub-folders (one per compressed floor topic) plus a final "Project1_v0" folder holding the shipped Day-1 tracker.
- Modules (ch.49) keeps its per-compiler manual-build documentation.
- Fix the internal `40.x`/`47.x`/`48.x` lecture-numbering leftovers inside chapters 47/48/49 during their re-record passes.

---

## 10. Old → new chapter mapping (quick reference)

| Old ch. | New location | Status |
|---|---|---|
| — | **00 — NEW, Fast Path / Day-1 project** | Net-new |
| 03 | 03 (floor lectures 3.2/3.5/3.6 pulled into ch.00; full chapter still taught in Arc 2) | Minor edit |
| 04 | 04 (floor lectures 4.3/4.6/4.8/4.9 pulled into ch.00; full chapter still taught in Arc 2) | Keep as-is |
| 05 | 05 (absorbs 07) | Minor edit |
| 06 | 06 | Keep as-is |
| 07 | folded into 05 | Cut (content preserved, merged) |
| 08 | 08 (Arc 4, deferred) | Keep as-is |
| 09 | 09 | Keep as-is |
| 10 | 10 (floor lectures 10.2/10.3 pulled into ch.00; full chapter still taught in Arc 2) | Keep as-is |
| 11 | 11 (floor lectures 11.2/11.5 pulled into ch.00; full chapter still taught in Arc 2; drops FixCalculator) | Minor edit |
| 12 | 12 (adds std::array, drops Fortune Tellers, Project 1 extension) | Minor edit |
| 13 | 13 (Arc 4, deliberately late) | Keep as-is |
| 14 | 14 (Arc 4) | Keep as-is |
| 15 | 15 (floor lectures 15.6/15.7-start pulled into ch.00; full chapter still taught in Arc 2) | Minor edit |
| 16 | 16 (floor lectures 16.2/16.3 pulled into ch.00; pass-by-X consolidated; full depth pass in Arc 2) | Re-record |
| 17 | 17 | Keep as-is |
| 18 | 18 (unchanged, both calculators kept; Project 1 CLI-flag extension) | Keep as-is |
| 19 | 19 (adds `std::expected`, absorbs 22 & 23) | Re-record |
| 20 | 20 (merged w/ 21, boundary only) | Minor edit |
| 21 | merged into 20 | Minor edit |
| — | 21.5 — NEW, AI-Assisted Dev I | Net-new |
| 22 | folded into 19 | Cut (content preserved, merged) |
| 23 | folded into 19 | Cut (content preserved, merged) |
| 24 | 24 (merged with 25 into "Templates I", content unchanged) | Keep as-is |
| 25 | merged into 24 as "Templates I" Part B (internal compression only; still NOT merged with 40) | Re-record |
| 26 | 26 (Project 2 intro) | Minor edit |
| 27 | merged w/ 28 | Re-record |
| 28 | merged into 27 | Re-record |
| 29 | merged w/ 30 (boundary only) | Minor edit |
| 30 | merged into 29 | Minor edit |
| 31 | merged w/ 32 (boundary only) | Minor edit |
| 32 | merged into 31 | Minor edit |
| 33 | 33 (Arc 4; only 33.4/33.7 merged) | Minor edit |
| 34 | 34 (kept separate from 35) | Keep as-is |
| 35 | 35 (kept separate from 34; internal 35.2/35.3 merge) | Minor edit |
| 36 | 36 (kept separate from 37; Project 3 intro) | Minor edit |
| 37 | 37 (kept separate from 36; internal 37.5/37.6 merge) | Minor edit |
| 38 | 38 (comparative reframe) | Re-record |
| 38.5 | Box Container Capstone (was 39) | Keep as-is |
| 40 | 40 ("Templates II," direct sequel to 24/25, unchanged content, concepts lectures stay; Project 4 intro) | Keep as-is |
| 41 | 41 (Arc 4) | Keep as-is |
| 42 | 42 (Arc 4, no confirmed cut) | Keep as-is |
| 43 | 43 (cuts 43.2/43.3, keeps 43.4-43.9) | Re-record |
| 44 | 44 (adds flat_map/flat_set) | Minor edit |
| 45 | 45 (consolidated 7→2-3) | Re-record |
| 46 | 46 (adds C++23 views/mdspan) | Re-record |
| 47 | 47 (no confirmed cut) | Keep as-is |
| 48 | 48 (adds `std::generator`) | Re-record |
| 49 | 49 | Keep as-is |
| — | 49.5 — NEW, AI-Assisted Dev II | Net-new |
| — | 49.6 — NEW, Final Capstone Build | Net-new |
| — | 50 — NEW, C++26 Hacking Preview | Net-new |

Every one of the 47 content-bearing old chapters (03-49, excluding always-empty numbering gaps 01-02) appears exactly once above. Chapters 03/04/10/11/15/16 each appear twice in spirit (a compressed fragment in ch.00, the full chapter later in Arc 2) but are listed once in this table since no folder is duplicated — only specific lecture numbers within them are retaught in miniature at the front.
