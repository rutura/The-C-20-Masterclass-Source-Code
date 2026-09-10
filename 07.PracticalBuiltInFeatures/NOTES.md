# Practical Built-in Features (Collections and More)

Chapters 3 to 6 covered the language: variables, control flow, functions.
Almost every real program also needs a handful of **standard-library
facilities** that the language itself does not give you - a place to put
a list of things, proper text handling, a clock, a way to say "this
result might be missing."

This chapter is that toolkit. Everything here is **modern C++ first** -
`std::array` and `std::vector` instead of C-style arrays, `std::string`
and `std::string_view` instead of `char*`, `<charconv>` instead of
`atoi`. Raw pointers and the older C-style APIs come in the **next
chapter**; you will not need them for anything below.

```
      language (ch 3-6)              this chapter's additions
   ┌────────────────────┐        ┌───────────────────────────────┐
   │ int, double, bool  │        │ std::array<T,N>  fixed list    │
   │ if / for / while   │        │ std::vector<T>   growable list │
   │ functions, lambdas │   +    │ std::string ops, string_view  │
   │                    │        │ enum class, type aliases      │
   │                    │        │ <chrono>  time & dates        │
   │                    │        │ std::optional  "maybe a value"│
   └────────────────────┘        └───────────────────────────────┘
```

Each lecture is a **self-contained program** demonstrating one facility.
The chapter then closes with a **non-trivial project** - an expense-report
tool - built three ways, exactly as chapter 6's image writer was: once
with no dependency, once with a **vendored** third-party library, once
with the library **fetched by CMake**.

After this chapter: pointers and the C-style APIs, then classes.

---

## 7.2 Fixed-size collections: `std::array`

`std::array<T, N>` is `N` values of type `T`, stored back-to-back, size
fixed at compile time. It is the modern replacement for `int scores[5];`
- identical memory layout, but it knows its own size and has real member
functions.

```
   std::array<int, 5> scores{42, 17, 91, 8, 63};

   index:   0    1    2    3    4
          ┌────┬────┬────┬────┬────┐
          │ 42 │ 17 │ 91 │  8 │ 63 │
          └────┴────┴────┴────┴────┘
            ▲                   ▲
          front()            back()
          scores[0]          scores[4]
```

- **Brace-initialize the elements**: `std::array<int, 5> scores{...}`. An
  empty `{}` zero-fills.
- **CTAD**: `std::array temperatures{19.5, 21.0, 18.75}` - the compiler
  deduces `std::array<double, 3>` from the braces.
- **`.size()`** always tells you the element count - no `sizeof` tricks,
  no passing `N` around by hand.
- **`[i]` vs `.at(i)`**: `[]` is fast and unchecked - an out-of-range
  index is undefined behavior. `.at()` checks and **throws
  `std::out_of_range`** on a bad index.
- **`.front()` / `.back()`** - first and last element without the index
  arithmetic. **`.fill(v)`** sets every element to `v`.
- **Range-based `for`**: `const T&` when reading, `T&` when modifying in
  place. The C++20 init-statement form keeps a running accumulator scoped
  to the loop:

  ```cpp
  for (int total{0}; const int& s : scores) {
      total += s;
  }
  ```

Reach for `std::array` when the count is known and fixed - a board, a
week of readings, a set of RGB channels.

---

## 7.3 Growable sequences: `std::vector`

`std::vector<T>` is the workhorse. Same contiguous layout as
`std::array`, but the size can **change at run time**. When you are not
sure which container to use, the answer is `std::vector`.

```
   push_back grows the vector; capacity is the room it has in hand

   size = 3, capacity = 4
   ┌────┬────┬────┬╌╌╌╌┐
   │ 10 │ 20 │ 30 │    │   push_back(40)
   └────┴────┴────┴╌╌╌╌┘        │
                               ▼
   ┌────┬────┬────┬────┐
   │ 10 │ 20 │ 30 │ 40 │   size = 4, capacity = 4  (next push_back reallocates)
   └────┴────┴────┴────┘
```

- **`{...}`** is a list of elements. **`(count, value)`** is a different
  constructor - `std::vector<int> zeros(5, 0)` is five zeros. Watch the
  `{}` vs `()` distinction here.
- **`push_back(x)`** appends a copy; **`emplace_back(args...)`** builds
  the element in place from constructor arguments - cheaper for types
  like `std::string`.
- **`.size()`** is the element count; **`.capacity()`** is how many it
  can hold before reallocating. **`.reserve(n)`** sets capacity up front
  when you know roughly how many you will add.
- **`[i]` / `.at(i)`** as with `std::array` - unchecked vs. throwing.
- **`==` / `!=`** compare element by element. Copying a vector copies all
  its elements.
- **`.clear()`** removes every element; the vector stays usable.

---

## 7.4 Sorting, searching, aggregating

Once data is in a container, the library already has the common
operations. You rarely hand-write these loops.

- **`std::ranges::sort(c)`** *(C++20)* - sorts the container in place,
  ascending by default. Pass a lambda to change the order:
  `std::ranges::sort(v, [](int a, int b){ return a > b; })` is descending.
- **`std::ranges::binary_search(c, value)`** - `true`/`false`, but the
  range must already be sorted the way it searches.
- **`std::ranges::min_element(c)` / `max_element(c)`** - return an
  *iterator*; dereference with `*` for the value.
- **`std::accumulate(first, last, init)`** *(from `<numeric>`)* - walks
  the range building one result. `init` also fixes the result type
  (`0` gives `int`, `0.0` gives `double`). An optional fourth argument
  replaces `+` with any binary operation - a named function or a lambda:

  ```cpp
  int product{std::accumulate(v.begin(), v.end(), 1,
                              [](int a, int b){ return a * b; })};
  ```

These work on any contiguous sequence - `std::array` and `std::vector`
alike.

---

## 7.5 Multidimensional data

A grid is "an array of rows", each row itself an array. So a 2D grid is
`std::array<std::array<T, columns>, rows>` - the same shape as
`int grid[3][4];`, spelled with the type you already know.

```
              col 0   col 1   col 2   col 3
            ┌───────┬───────┬───────┬───────┐
   row 0    │   1   │   2   │   3   │   4   │
            ├───────┼───────┼───────┼───────┤
   row 1    │   5   │   6   │   7   │   8   │
            ├───────┼───────┼───────┼───────┤
   row 2    │   9   │  10   │  11   │  12   │
            └───────┴───────┴───────┴───────┘
                    board[1][2] == 7
```

- Nested braces mirror the nested type.
- Index one `[]` per dimension: `board[row][col]`.
- A `using` alias (`using Grid = std::array<...>;`, see 7.11) keeps
  function signatures readable.
- Pass the grid **by `const&`** so all the elements are not copied.
- Range-`for` with `const auto&` walks rows, then cells:

  ```cpp
  for (const auto& row : grid) {       // row is one std::array<int, cols>
      for (const auto& cell : row) {   // cell is one int
          ...
      }
  }
  ```

---

## 7.6 A taste of ranges

This is a *taste*, not the tour - ranges gets its own chapter later. The
one idea to take now: a **view** describes a transformation of a sequence
without building a new container for each step. The work happens as you
iterate.

```
   iota(1,11)  →  filter even  →  transform x*x

   1 2 3 4 5 6 7 8 9 10
        │ filter %2==0
        ▼
     2   4   6   8   10
        │ transform x*x
        ▼
     4  16  36  64  100          (nothing stored until the loop asks)
```

- **`std::views::iota(1, 11)`** generates `1..10` on demand.
- A view adaptor is applied with the **pipe** `|`.
  **`std::views::filter(pred)`** keeps matching elements;
  **`std::views::transform(fn)`** maps each element.
- Adaptors **chain**: `numbers | filter(...) | transform(...)` reads left
  to right, still with no intermediate container.
- A view can take a real container as its source.
- To get a plain number out, feed the view to an algorithm:
  `std::accumulate(v.begin(), v.end(), 0)`.

---

## 7.7 `std::string` in depth

Chapter 5 introduced `std::string` for basic text. Here is the rest of
the everyday toolkit.

```
   std::string path{"/home/ada/reports/2025-summary.txt"};
                     └──────────────────┬──────────┘└──┬─┘
                              path.rfind('/')   path.rfind('.')
                     substr(slash+1)  → "2025-summary.txt"
                     substr(dot+1)    → "txt"
```

- **`.size()` / `.length()`** - same function, two names. **`.capacity()`**
  is storage in hand. **`.empty()`**.
- **`[i]` vs `.at(i)`**; **`.front()` / `.back()`**.
- **`.find(x)`** returns the first index, or **`std::string::npos`** if
  not found. **`.rfind(x)`** searches from the end.
- **`.substr(pos, count)`** copies out a piece. Combine with `find` to
  split paths, extensions, fields.
- **`+` / `+=`** build text. Prefer `+=` when appending in a loop - no
  temporary.
- **`.insert(pos, text)`**, **`.erase(pos, count)`**,
  **`.replace(pos, count, text)`** edit in place.
- **`.starts_with` / `.ends_with`** *(C++20)*, **`.contains`** *(C++23)* -
  clearer than a `find` comparison.
- **Escape sequences** (`\t`, `\n`, `\"`, `\\`) in a normal literal; a
  **raw string literal** `R"(...)"` takes every character literally -
  ideal for Windows paths, regexes, JSON.

---

## 7.8 String / number conversions

Text in, numbers out, and back again.

```
   convenient (throws)          modern (no throw, no locale, no alloc)
   ─────────────────            ─────────────────────────────────────
   std::stoi("128")            std::from_chars(p, end, value) → {ptr, ec}
   std::stod("2.5e3")          std::to_chars(buf, end, 987654) → {ptr, ec}
   std::to_string(42)
```

- **`std::to_string(n)`** - quick number → text, `"C"` locale, fixed
  default precision.
- **`std::stoi` / `std::stod`** parse the leading number and stop. They
  **throw**: `std::invalid_argument` (no number) or `std::out_of_range`
  (too big).
- **`std::from_chars(first, last, out)`** *(`<charconv>`)* - the modern
  parse. No exceptions, no locale, no allocation. Returns
  `{ptr, ec}`: `ec == std::errc{}` on success, `ptr` is where parsing
  stopped. This is what the chapter project uses to parse CSV fields.
- **`std::to_chars(first, last, value)`** - the reverse, into a
  caller-provided buffer.

---

## 7.9 `std::string_view` parameters

`std::string_view` is a lightweight "look at this text" handle - a
pointer plus a length. It **does not own or copy** the characters. Use it
for **read-only string parameters**: the function then accepts
`std::string`, string literals, and substrings with no copy of any of
them.

```
   void f(std::string_view sv);

   f(some_std_string);   // no copy
   f("a literal");       // no temporary std::string built
   f(sv.substr(0, 4));   // a view into the SAME characters, no alloc
```

- **`const std::string&`** parameters force a temporary `std::string`
  when you pass a literal; `string_view` does not.
- **`.remove_prefix(n)` / `.remove_suffix(n)`**, **`.substr(...)`** all
  produce another view into the same storage - no allocation.
- **The pitfall**: a `string_view` is only valid while the characters it
  points at are alive. **Never return a view of a local string or a
  temporary** - the storage is gone when the function returns.
- Rule of thumb: **`string_view` for parameters, `std::string` when you
  need to own or outlive the text.**

---

## 7.10 Named constants with `enum class`

An `enum class` gives a fixed set of named values their own type. The
names are **scoped** (`Direction::North`) and there is **no silent
conversion to `int`** - you ask with a cast.

```cpp
enum class Direction : std::uint8_t {   // pin storage to one byte
    North, East, South, West,           // 0, 1, 2, 3
};
```

- The optional **`: type`** fixes the underlying integer type -
  `std::uint8_t` here makes `sizeof(Direction) == 1`.
- **`static_cast<int>(d)`** to get the number; **`static_cast<Direction>(n)`**
  to go back (only when `n` is a valid enumerator).
- Enums compare with `==` and `<`, and work as `switch` labels.
- **`using enum Direction;`** *(C++20)* inside a block pulls the
  enumerators into scope, so a `switch` reads `North` instead of
  `Direction::North` on every line.

---

## 7.11 Type aliases

A type alias is a second name for an existing type. It creates **no new
type** - `using Celsius = double;` makes `Celsius` interchangeable with
`double`. The point is **readability**.

- **Modern spelling**: `using Name = Type;` - reads left to right, and
  can be templated. The old `typedef Type Name;` means the same but reads
  backwards.
- Where aliases pay off: a **nested container type** you would otherwise
  retype at every signature.

  ```cpp
  using Sample           = std::vector<std::int64_t>;
  using SamplesByStation  = std::unordered_map<std::string, Sample>;
  ```

---

## 7.12 Working with time

`<chrono>` is the standard time library. Three ideas:

```
   CLOCK        "what time is it now"     steady_clock::now(), system_clock::now()
   DURATION     a length of time          250ms, 3s, 2h   (with chrono_literals)
   TIME POINT   a specific instant        now() returns one; subtract to get a duration
```

- **`using namespace std::chrono_literals;`** enables `250ms`, `3s`, `2h`.
  Durations have distinct types and convert where lossless.
  **`.count()`** drops the unit.
- **`steady_clock`** never jumps backward - the right clock for
  **measuring elapsed time**:

  ```cpp
  auto start{std::chrono::steady_clock::now()};
  // ... work ...
  auto elapsed{std::chrono::steady_clock::now() - start};
  auto ms{std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)};
  ```

- **`system_clock`** is the wall clock - it maps to civil time. Floor it
  to `days` and view it as a **`std::chrono::year_month_day`**.
- `std::print` / `std::println` **format durations and dates directly**:
  `std::println("{:%Y-%m-%d}", date)`.
- **`std::this_thread::sleep_for(20ms)`** pauses the thread for a
  duration.

---

## 7.13 Maybe a value: `std::optional`

`std::optional<T>` holds **either a `T` or nothing**. It is the honest
return type for "this might not produce a value" - a lookup that can
miss, a parse that can fail - instead of sentinels like `-1`, `""`, or a
bare `bool` out-parameter.

```
   std::optional<std::string> find_phone(...);

   ┌─────────────┐          ┌─────────────┐
   │  "555-0101" │   or     │  (nothing)  │
   └─────────────┘          └─────────────┘
     has_value()==true        has_value()==false
     *opt  → the string       std::nullopt
```

- Return a value to wrap it; return **`std::nullopt`** for "no value".
- **`.has_value()`** or the `bool` conversion tests it. **`*opt`** and
  **`opt->member`** reach the value (undefined if empty).
- **`.value_or(fallback)`** - the value if present, else `fallback`. The
  clean way to collapse "maybe" to a definite result.
- **`.value()`** also gets the value but **throws
  `std::bad_optional_access`** if empty - use only after checking.

---

## 7.14 Command-line arguments

A program can receive arguments from whoever launches it. `main` has a
second form:

```
   int main(int argc, char* argv[])

   argc  - the argument COUNT (always >= 1)
   argv  - the argument VALUES, as C strings
           argv[0]              the program's own name/path
           argv[1] .. argv[argc-1]   what the user typed after it
```

- Wrap the raw pair in **`std::span<char*>{argv, static_cast<std::size_t>(argc)}`**
  to get a proper range - `.size()` and range-`for` then work.
- Convert each argument to **`std::string_view`** for comparison
  (`arg == "add"`), and to a number with `std::from_chars` (7.8).
- Typical shape: `argv[1]` is a command, `argv[2..]` its operands; print
  a usage line and `return 1` when the count is wrong.

---

## 7.15 - 7.17 Project: the expense report

The chapter's facilities come together in one program: **read a CSV of
dated expenses, total them by category, and print a bar chart** - timing
each phase with `steady_clock`.

```
   expenses.csv                                        console
   ───────────                                         ───────
   date,category,amount,note                                 Housing | ####################  1290.00
   2025-01-03,Housing,1200.00,January rent    ──►             Food | #######               236.85
   2025-01-04,Food,42.50,groceries                       Utilities | ###                   104.45
   ...                                                       ...
```

What it exercises: `std::vector<Expense>` (rows), `std::array` (fixed
per-category totals), `std::string` / `std::string_view` (splitting
lines), `<charconv>` (field → number and the date parts),
`enum class Category`, `std::optional` (a line that fails to parse, a
category lookup that misses), `std::ranges::sort` + `std::accumulate`
(the aggregation), `<chrono>` (record dates and phase timing), `argv`
(the input filename).

**The analysis code is the part that does NOT change** between the three
versions. `report.h` / `report.cpp` - the `Expense` type, the category
enum, `make_expense`, `totals_by_category`, `print_bar_chart` - are
byte-for-byte identical in all three folders. **Only how the CSV file
becomes a `std::vector<Expense>` differs.**

```
   7.15  hand-rolled     split each line ourselves with string/string_view
   7.16  vendored csv2   the csv2 library, its headers committed under vendor/
   7.17  FetchContent    the same csv2, cloned by CMake at configure time
```

### 7.15 - hand-rolled, no dependency

`parse_expense_line` in `report.cpp` splits on commas with
`std::string_view::find` and `substr`, then hands the field text to
`make_expense`. CSV this regular (no quoted fields, no embedded commas)
is simple enough to parse by hand.

```cmake
add_executable(rooster main.cpp report.cpp report.h)
```

### 7.16 - a vendored library (`csv2`)

Real CSV has quoting, trimming, and header rules you would rather not
re-implement. **`csv2`** (by Vince Mi, MIT licensed, header-only) does
the tokenising. Here it is **vendored** - the `csv2/` headers are
committed under `vendor/`, compiled from source as part of this target.

```
   7.16ProjectExpenseReportVendored/
   ├── vendor/
   │   ├── csv2/  (reader.hpp, mio.hpp, parameters.hpp, writer.hpp)
   │   ├── LICENSE
   │   └── LICENSE.mio
   ├── csv_loader.h / csv_loader.cpp   ← the ONLY new code vs. 7.15
   ├── report.h / report.cpp           ← unchanged from 7.15
   ├── main.cpp
   └── expenses.csv
```

`csv_loader.cpp` opens the file with `reader.mmap(path)`, walks
`for (const auto row : reader) for (const auto cell : row)`, reads each
cell into a `std::string`, and calls the same `make_expense` the
hand-rolled version ends on.

```cmake
add_executable(rooster main.cpp csv_loader.cpp csv_loader.h report.cpp report.h)
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
```

- **`SYSTEM`** marks `vendor/` third-party, so `-Wall -Wextra` do not
  flag csv2's own code.
- **No linking.** The headers compile with our compiler, our flags -
  there is no prebuilt binary, so an ABI mismatch is impossible.

### 7.17 - fetched by CMake

The C++ is **identical to 7.16**. csv2 is no longer committed here;
CMake clones it at configure time with **`FetchContent`**.

```cmake
include(FetchContent)
FetchContent_Declare(csv2
    GIT_REPOSITORY https://github.com/p-ranav/csv2.git
    GIT_TAG        4f3c41db6457465e94b92b91fc560b911c16a16a   # an exact commit
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(csv2)
target_link_libraries(rooster PRIVATE csv2)   # INTERFACE target: adds the include path
```

- **`GIT_TAG` is pinned to a commit hash, not a branch** - otherwise the
  build stops being reproducible.
- csv2 is header-only, so `MakeAvailable` has no build step - it puts the
  files on disk and exposes the `csv2` include target. Still compiled
  from source in our build: same no-ABI-mismatch guarantee as 7.16.
- The download happens once, into `build/_deps/`. The first configure
  needs network access and `git`; 7.16 builds offline forever. Real
  projects usually take that trade to avoid carrying dependency copies in
  their own repo.

### The three side by side

```
                      7.15 hand-rolled   7.16 vendored      7.17 FetchContent
   ─────────────────  ────────────────   ───────────────    ─────────────────
   CSV parsing        our own code       csv2 library       csv2 library
   library code       none               in vendor/,        not in our repo;
                                         committed          cloned to build/
   offline build      yes                yes                first build needs net
   reproducible       yes                yes (files frozen)  yes (commit pinned)
   compiled here?     -                  yes → no ABI risk   yes → no ABI risk
   report.h/.cpp      identical in all three
```

---

## 7.18 Assignment

One small program - a terminal temperature-log tool over a fixed list of
`"YYYY-MM-DD,LABEL,VALUE"` records - built in seven steps. `main.cpp` has
the seven stubbed exercises, each with its problem statement and a sample
run in a comment; `main_solution.cpp` solves all seven with the
statements repeated above each solution. Built as two executables
(`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | station list | `std::array<std::string_view, N>`, range-`for` with an init-statement |
| 2 | `parse_value()` | `using` type alias, `std::optional`, `std::from_chars` (no exceptions) |
| 3 | `parse_record()` | `std::string_view` `find`/`substr` splitting, a `struct`, `std::optional` |
| 4 | summary stats | `std::ranges::min_element`/`max_element`, `std::accumulate` |
| 5 | `Station` enum | `enum class : std::uint8_t`, `using enum` in a `switch` |
| 6 | sort by value | `std::ranges::sort` with a comparison lambda |
| 7 | record dates | `std::chrono::year_month_day`, `std::from_chars` on the parts, `{:%Y-%m-%d}` / weekday formatting |

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole
chapter.

After this chapter the student can hold and process collections of data,
handle text properly, work with time, and model "maybe a value" - and is
ready for pointers, then classes.
