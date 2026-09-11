# Practical Built-In Features

Every program so far has worked on a handful of loose variables. Real data
comes in **collections** - a list of scores, a column from a spreadsheet, a
whole passenger manifest - and real programs spend most of their time
loading it, cleaning it, and pulling answers out of it.

```
   loose variables                    a collection
   ────────────────                   ────────────
   int score1{68};                    std::vector<int> scores{68, 72, 59, 81};
   int score2{72};                           │
   int score3{59};                           └── one name, any number of
   int score4{81};                               elements, looped over
```

This chapter is a tour of the **standard library's everyday tools** for
that job: fixed and growable containers, sorting and searching, the
functional-style ranges/views pipeline, strings beyond what chapter 5
introduced, non-owning views into text, files revisited with formatted
input, reading real CSV data, and pattern matching with regular
expressions. It closes with a small project that puts all of it to work
on a real dataset - the Titanic passenger manifest - before the course
moves on to pointers and classes.

---

## 7.2 `std::array`

**`std::array<T, N>`** is a **fixed-size** sequence of `N` values of type
`T`, stored inline - no separate heap allocation, unlike a raw pointer to
dynamically allocated memory. `N` is part of the type: `std::array<int, 5>`
and `std::array<int, 10>` are different types.

```cpp
std::array<int, 5> scores{};   // {} zero-initializes every element
```

### Access: `[]` vs `.at()`

`scores[i]` is unchecked - fast, but an out-of-range `i` is undefined
behavior. `scores.at(i)` is the same idea, bounds-checked: an out-of-range
index throws `std::out_of_range` instead of reading garbage.

```
   scores.at(10)   on a 5-element array
        │
        ▼
   throws std::out_of_range   (instead of silently reading past the end)
```

### CTAD: skip the `<T, N>`

```cpp
std::array highScores{32, 27, 64, 18, 95};   // inferred: array<int, 5>
```

Class template argument deduction reads the braced initializer and infers
both the element type and the count - no need to spell out
`<int, 5>` yourself.

### Range-based for

```cpp
for (const int& score : highScores) { /* read-only */ }
for (int& score : highScores)       { score *= 2; }   // modifies in place
```

A `const T&` element avoids a copy per iteration; a non-`const` `T&`
lets the loop body write back into the array. The C++20
`for (init; cond; range)` form lets a loop declare its own accumulator
right where it is used:

```cpp
for (int total{0}; const int& score : highScores) {
    total += score;
    // ...
}
```

---

## 7.3 `std::vector`

**`std::vector<T>`** is the growable counterpart to `std::array`: its
elements live on the heap, and it can grow or shrink at run time. Where
`std::array`'s size is fixed forever, `std::vector` is the default choice
whenever you do not know the count up front, or need to add to it later.

```cpp
std::vector<int> readings(7);    // 7 elements, each value-initialized to 0
std::vector<int> other{7};       // ONE element, valued 7 - braces mean
                                  // "these are the elements", not a count
```

That distinction - `(7)` sizes the vector, `{7}` is a one-element list -
is worth calling out explicitly; it is a common first mistake.

### Comparing, copying, assigning

```cpp
std::vector<int> a(5), b(5);
a == b;                 // element-by-element comparison, like std::array
std::vector c{a};       // copy constructor - c owns its own copy of a's data
a = b;                  // assignment - a's old contents are replaced
```

### Growing: `push_back`

```cpp
std::println("size before: {}", readings.size());
readings.push_back(1000);   // appends one element, resizing as needed
std::println("size after: {}", readings.size());
```

This is the one thing `std::array` fundamentally cannot do - its size is
fixed at compile time.

### `.at()` still bounds-checks

```cpp
try {
    readings.at(15);   // out of range
}
catch (const std::out_of_range& ex) {
    std::println("An exception occurred: {}", ex.what());
}
```

---

## 7.4 Sorting, searching, and `accumulate`

### Sorting with `std::ranges::sort`

```cpp
std::array fruits{"mango"s, "kiwi"s, "fig"s, "date"s, "apple"s};
std::ranges::sort(fruits);   // ascending, in place
```

### Searching sorted data with `std::ranges::binary_search`

`binary_search` repeatedly halves the search range - which only gives a
correct answer when the data is **already sorted**. That is the trade a
sort buys you: `O(log n)` lookups instead of scanning every element.

```cpp
std::ranges::binary_search(fruits, "kiwi"s);   // true
std::ranges::binary_search(fruits, "guava"s);  // false
```

### Folding a range into one value with `std::accumulate`

`std::accumulate(first, last, init)` sums a range by default:

```cpp
std::accumulate(quantities.begin(), quantities.end(), 0);   // sum
```

A fourth argument - a named function or a lambda - replaces `+` with
whatever "combine" should mean:

```cpp
int multiply(int x, int y) { return x * y; }

std::accumulate(factors.begin(), factors.end(), 1, multiply);   // product

std::accumulate(factors.begin(), factors.end(), 1,
                 [](int x, int y) { return x * y; });           // same, inline
```

---

## 7.5 Ranges and views

A **view** is a lazy wrapper around a range: it does not build a new
container up front, it produces values on demand as something iterates it.

```cpp
auto counted{std::views::iota(1, 11)};   // the integers 1..10, generated lazily
```

`std::views::filter` and `std::views::transform` wrap a range the same
way, and chain together with `|`, read left to right like a pipeline:

```cpp
auto evenSquares{
    counted | std::views::filter([](int x) { return x % 2 == 0; })
            | std::views::transform([](int x) { return x * x; })};
```

```
   counted ──filter(even)──► evens ──transform(square)──► evenSquares

   1 2 3 4 5 6 7 8 9 10 ──► 2 4 6 8 10 ──► 4 16 36 64 100
```

Nothing is computed until `evenSquares` is actually iterated - by a
range-based for, by `std::accumulate`, or by copying it into a
`std::vector`. The same pipeline works over a real container, not just a
generated sequence like `iota`:

```cpp
numbers | std::views::filter(...) | std::views::transform(...)
```

---

## 7.6 Strings deep dive

Chapter 5 covered `length()`/`size()`, `empty()`, `==`/`!=`, `+`, and
`starts_with`/`ends_with`. This lecture goes further.

### Assignment, concatenation, swap

```cpp
subtitle.assign(title);     // same effect as: subtitle = title;
title.append("acomb");      // "cat" -> "catacomb"
first.swap(second);         // exchange contents, no copy of the data
```

### `substr`: pull out a piece

```cpp
filename.substr(0, 6);   // "report_final.pdf" -> "report"
```

### The `find` family: locate things inside a string

```cpp
log.find("is");                    // first occurrence, from the front
log.rfind("is");                   // last occurrence, from the back
log.find_first_not_of("noon is "); // first character NOT in this set
```

Every `find`-family function returns **`std::string::npos`** when nothing
matches - always check for it before using the result as an index.

### `erase` / `replace`: edit in place

```cpp
sentence.erase(19);                          // drop everything from index 19 on
sentence.replace(position, 1, "_");          // 1 char at position -> "_"
```

Looping a `find` + `replace` together is the everyday pattern for
"replace every occurrence of X":

```cpp
std::size_t pos{sentence.find(' ')};
while (pos != std::string::npos) {
    sentence.replace(pos, 1, "_");
    pos = sentence.find(' ', pos + 1);
}
```

### `insert`: splice text into the middle

```cpp
greeting.insert(7, "World");   // "Hello, !" -> "Hello, World!"
```

### String streams: build and parse without hand-rolled loops

`std::ostringstream` accumulates pieces of different types into one
string, using the same `<<` `std::cout` uses:

```cpp
std::ostringstream receipt;
receipt << "Order #" << 42 << ": " << "coffee" << " - $" << 4.5;
receipt.str();   // the accumulated string
```

`std::istringstream` runs the idea backwards - pulling typed values out of
a string the same way `std::cin` pulls them from the keyboard:

```cpp
std::istringstream record{"Ada 3 19.99"};
record >> item >> quantity >> price;
```

---

## 7.7 `std::string_view`

A **`std::string_view`** does not own characters - it is a `(pointer,
length)` pair pointing at characters owned by someone else: a
`std::string`, a string literal, or part of either. No allocation, no
copy.

```cpp
std::string color{"red"};
std::string_view colorView{color};   // "sees" color's own characters
```

Because `colorView` points at `color`'s data, a change to `color` shows up
through the view:

```cpp
color.at(0) = 'R';
// colorView now reads "Red" too - it has no data of its own to be stale
```

`remove_prefix`/`remove_suffix` shrink the view's window in `O(1)` -
nothing is copied or erased, the window just moves:

```cpp
colorView.remove_prefix(1);
colorView.remove_suffix(1);
```

A `string_view` can wrap a plain literal with no `std::string` created at
all, and supports the same `find`/`starts_with`/iteration you would expect.
Prefer it for a function parameter that only **reads** text and does not
need to keep it around - it avoids a copy the caller never asked for.

---

## 7.8 Files revisited

Chapter 5 wrote and read plain lines of text with `std::getline`. A file
can hold several **fields per line** instead - the same `<<`/`>>` you
already know from `std::cout`/`std::cin`, aimed at a file stream.

```cpp
// write.cpp
std::ofstream out{"accounts.txt"};
out << account.number << ' ' << account.name << ' ' << account.balance << '\n';
```

```cpp
// read.cpp
while (in >> number >> name >> balance) {   // one whitespace-delimited,
    // ...                                  // typed field per read
}
```

`>>` splits on whitespace and converts to each variable's type as it
reads - three reads per record, instead of `getline`'s one string per
line. The stream itself turns false once there is nothing left to read,
so the `while` loop runs once per complete record - the same shape as
chapter 5's `while (std::getline(in, name))`.

---

## 7.9 Reading CSV data

A CSV file's quoting and embedded-comma rules are easy to get subtly
wrong with hand-rolled `stringstream` splitting. **`rapidcsv`** is a
small, header-only library that already solved that - it is **vendored**
into this project (the same pattern as `6.17ProjectVendoredHeader`): the
header sits in `vendor/`, committed alongside our own code, nothing
downloaded.

```cpp
#include "rapidcsv.h"

rapidcsv::Document document{"accounts.csv"};   // loads and parses on construction

std::vector<int> accounts{document.GetColumn<int>("account")};
std::vector<std::string> names{document.GetColumn<std::string>("name")};
std::vector<double> balances{document.GetColumn<double>("balance")};
```

`GetColumn<T>("name")` reads an entire named column - addressed by the
CSV's header row - into a `std::vector<T>`, converting each cell from text
to `T` along the way. Being header-only, `rapidcsv.h` needs no separate
implementation file to compile, unlike `stb_image_write.h` in chapter 6 -
just the include path pointed at `vendor/`:

```cmake
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
```

---

## 7.10 Regex

A **regular expression** describes the *shape* of text, not literal
characters - "a capital letter, then one or more lowercase letters",
not one specific word.

```cpp
std::regex properName{"[A-Z][a-z]+"};
std::regex_match("Wally", properName);   // true  - the WHOLE string fits
std::regex_match("E", properName);       // false - no lowercase letters follow
```

`regex_match` requires the **entire** string to satisfy the pattern.
`regex_search` looks for a match **anywhere** inside it, and can capture
what it found in a `std::smatch`:

```cpp
std::smatch match;
while (std::regex_search(contact, match, phoneNumber)) {
    std::println("{}", match.str());
    contact = match.suffix();   // keep searching after this match
}
```

`regex_replace` rewrites every match in a **copy** of the string, leaving
the original untouched:

```cpp
std::regex_replace(data, std::regex{"\t"}, ",");   // tabs -> commas
```

Common building blocks: `\d` (a digit), `{n}` (exactly n), `{n,}` (n or
more), `{n,m}` (n to m inclusive), `[A-Z]`/`[a-z]` (character ranges).

---

## 7.11 Project: Titanic dataset analysis

Everything in this chapter comes together on one real dataset: the
Titanic passenger manifest, loaded with the same vendored `rapidcsv`
from 7.9.

```
   titanic.csv ──rapidcsv──► GetColumn<T> per field ──► std::vector<T>
                                                              │
                             sort · filter · accumulate · count_if
                                                              │
                                                    survival statistics
```

- **Missing data**: some `age` values are unparseable (`"?"` in the raw
  file). `rapidcsv::ConverterParams{true}` turns those into `NaN` instead
  of throwing, and a `std::views::filter` drops them before any statistic
  is computed - the same lazy-view idea from 7.5, now filtering out bad
  data instead of picking out even numbers.

  ```cpp
  auto knownAges{age | std::views::filter([](double a) { return !std::isnan(a); })};
  std::vector<double> cleanAges{knownAges.begin(), knownAges.end()};
  ```

- **Descriptive statistics**: `std::ranges::sort` the cleaned ages, then
  `std::accumulate` for the average, `.front()`/`.back()` for min/max, and
  the sorted vector's middle element(s) for the median.

- **Counting with a condition**: `std::ranges::count_if` counts how many
  elements satisfy a predicate - "how many passengers were in 1st class",
  "how many survived" - in one call, no hand-written loop and counter.

  ```cpp
  std::ranges::count_if(passengerClass, [](int c) { return c == 1; });
  ```

- **Cross-referencing columns by index**: `survived`, `sex`, and
  `passengerClass` are parallel vectors - the same row `i` in each one
  describes the same passenger - so answering "what fraction of survivors
  were women" means walking `i` across all three together.

The result is a small report: passenger counts by class, an overall
survival rate, and a breakdown of who survived by sex and by class -
real answers pulled out of a real dataset using nothing but the tools
from this chapter.

---

## 7.12 Assignment

Six exercises building toward the same kind of work as the Titanic
project, on a smaller dataset. `main.cpp` has the six stubbed exercises,
each with its problem statement and a sample run in a comment;
`main_solution.cpp` solves all six with the statements repeated above
each solution. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `grow_readings()` | building a `std::vector` one `push_back` at a time |
| 2 | `warmest_and_coolest()` | sorting a local copy, reference out-parameters, leaving the original untouched |
| 3 | `average_of_hot_days()` | a `views::filter` \| `views::transform` pipeline, `std::accumulate` over a view |
| 4 | `clean_label()` | `find`/`erase`, `find`/`replace` in a loop |
| 5 | `extract_reading()` | parsing one line of text with `std::istringstream` |
| 6 | `flagged_accounts()` | `rapidcsv::Document` + `std::regex_match`, on `accounts.csv` |

The quiz (`QUIZ.md`) is 18 multiple-choice questions across the whole
chapter, including the CSV/vendoring pattern and the Titanic project's
ranges/statistics.

After this chapter the student can hold, sort, search, and summarize real
collections of data - the last stop before the course turns to pointers
and, from there, to classes.
