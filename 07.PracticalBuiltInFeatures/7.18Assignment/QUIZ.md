# Chapter 7 Quiz — Practical Built-in Features

20 multiple-choice questions covering **Chapter 7** as it now stands:
`std::array` and `std::vector`, the sort / search / accumulate
algorithms, a taste of ranges, `std::string` operations and
`std::string_view`, `<charconv>` conversions, `enum class` and
`using enum`, type aliases, `<chrono>`, `std::optional`, command-line
arguments, and the expense-report project (the vendored vs. FetchContent
split). Each question is followed immediately by its correct answer and a
short explanation.

---

### 1. What is the difference between `std::array<int, 5>` and `int arr[5]`?

A. `std::array` stores its elements on the heap; the C array is on the stack
B. None in memory layout — but `std::array` knows its own `.size()` and has member functions
C. `std::array` can grow at run time; the C array cannot
D. `std::array` elements are always zero-initialized; C array elements never are

**Answer: B** — `std::array<T, N>` has the identical contiguous layout of a C array. What it adds is a real interface: `.size()`, `.at()`, `.front()`, `.back()`, `.fill()`, iterators.

### 2. `std::array values{1.1, 2.2, 3.3};` — what type is `values`?

A. `std::array<double, 3>`, deduced from the braces (CTAD)
B. `std::array<double>` — the size is left unspecified
C. a compile error — `std::array` always needs explicit `<T, N>`
D. `std::vector<double>` of size 3

**Answer: A** — class template argument deduction reads the initializer and deduces both the element type (`double`) and the count (`3`).

### 3. `scores[10]` vs `scores.at(10)` on a 5-element container — what happens?

A. Both throw `std::out_of_range`
B. Both are undefined behavior
C. `scores[10]` is undefined behavior; `scores.at(10)` throws `std::out_of_range`
D. `scores[10]` throws; `scores.at(10)` returns a default-constructed element

**Answer: C** — `operator[]` does no bounds checking, so an out-of-range index is UB. `.at()` checks and throws `std::out_of_range`.

### 4. `std::vector<int> v(5, 0);` creates...

A. a vector holding the two elements `5` and `0`
B. a vector of five elements, each `0`
C. a vector of five elements, each `5`
D. an empty vector with capacity `5`

**Answer: B** — the `(count, value)` constructor. Note that `std::vector<int> v{5, 0};` with braces is different: that is the two-element list `{5, 0}`.

### 5. What is the difference between `.size()` and `.capacity()` on a `std::vector`?

A. `.size()` is the element count; `.capacity()` is how many it can hold before reallocating
B. They always return the same number
C. `.size()` is in bytes; `.capacity()` is in elements
D. `.capacity()` is the number of elements; `.size()` is the byte total

**Answer: A** — `.size()` counts the elements actually present. `.capacity()` is the allocated room; when `push_back` would exceed it, the vector reallocates to a larger block.

### 6. `push_back(x)` versus `emplace_back(args...)` — the difference is...

A. `emplace_back` appends to the front instead of the back
B. `emplace_back` constructs the element in place from its constructor arguments, avoiding a temporary
C. `push_back` is C++11; `emplace_back` was removed in C++20
D. there is none — they are aliases

**Answer: B** — `push_back` takes an already-built object and copies/moves it in. `emplace_back` forwards constructor arguments and builds the element directly in the vector's storage — cheaper for types like `std::string`.

### 7. `std::ranges::binary_search(v, 6)` returns `false` even though `6` is in `v`. The most likely cause?

A. `binary_search` only works on `std::array`, not `std::vector`
B. `v` is not sorted in the order `binary_search` assumes (ascending)
C. `binary_search` returns an iterator, not a bool
D. `6` must be passed as `6.0`

**Answer: B** — `binary_search` requires the range to be sorted the same way it searches. If you last sorted `v` descending, sort it ascending again before searching.

### 8. `std::accumulate(v.begin(), v.end(), 0)` vs `std::accumulate(v.begin(), v.end(), 0.0)` on a `std::vector<double>` — why does the `0` version lose the fractions?

A. `accumulate` truncates its result to whole numbers by default
B. the `init` argument fixes the accumulator type: `0` makes it `int`, so each add truncates
C. `accumulate` cannot take a `double` vector
D. it does not — both give the same answer

**Answer: B** — the third argument is both the starting value and the type of the running total. `0` gives an `int` accumulator; every `+= element` narrows to `int`. Pass `0.0` for a `double` total.

### 9. `std::ranges::min_element(v)` returns...

A. the smallest value in `v`
B. an iterator to the smallest element — dereference with `*` for the value
C. the index of the smallest element
D. a `std::optional<int>` that is empty if `v` is empty

**Answer: B** — the `*_element` algorithms return an iterator. `*std::ranges::min_element(v)` is the value; the iterator itself is useful when you want the position.

### 10. In `numbers | std::views::filter(pred) | std::views::transform(fn)`, when does the filtering and transforming actually run?

A. Immediately, building a new container at each `|`
B. Lazily, as the resulting view is iterated
C. Never — views are compile-time only
D. Once, when the pipeline is assigned to a variable

**Answer: B** — a view describes the transformation without materializing it. The work happens element-by-element as a loop (or an algorithm) pulls values through the pipeline. No intermediate container is built.

### 11. `path.find("missing")` when the substring is not present returns...

A. `-1`
B. `0`
C. `std::string::npos`
D. it throws `std::out_of_range`

**Answer: C** — `find` returns `std::string::npos`, a sentinel "not found" value. The idiom is `if (path.find(x) != std::string::npos)`.

### 12. Which is the right way to write a Windows path literal `C:\Users\ada` in a `std::string`?

A. `std::string p{"C:\Users\ada"};`
B. `std::string p{R"(C:\Users\ada)"};`
C. `std::string p{"C:\\Users\\ada"};` or `std::string p{R"(C:\Users\ada)"};`
D. Windows paths cannot be stored in a `std::string`

**Answer: C** — either escape every backslash (`\\`), or use a raw string literal `R"(...)"` which takes every character literally. The plain `"C:\Users\ada"` in option A is wrong: `\U` and `\a` are (mis)interpreted as escapes.

### 13. Why prefer `std::string_view` over `const std::string&` for a read-only text parameter?

A. `string_view` can modify the caller's string; `const std::string&` cannot
B. Passing a string literal to `const std::string&` builds a temporary `std::string`; `string_view` does not
C. `string_view` is always faster to iterate
D. `const std::string&` was removed in C++20

**Answer: B** — `string_view` is a pointer + length. It binds to a `std::string`, a literal, or a substring with no allocation and no copy. `const std::string&` forces a temporary `std::string` to be constructed from a literal.

### 14. What is wrong with returning `std::string_view` that points into a local `std::string`?

A. Nothing — the view keeps the string alive
B. The local string is destroyed when the function returns, leaving the view dangling
C. `string_view` cannot be a return type
D. It copies the whole string, defeating the purpose

**Answer: B** — a `string_view` does not own its characters. When the local `std::string` goes out of scope, the storage the view points at is gone. Return `std::string` when the text must outlive the function.

### 15. `std::from_chars` versus `std::stoi` — the key advantage of `from_chars` is...

A. it accepts locale-specific thousands separators
B. no exceptions, no locale, no allocation — it reports failure through an error code
C. it can parse hexadecimal, which `stoi` cannot
D. it returns a `std::string`

**Answer: B** — `from_chars(first, last, out)` returns `{ptr, ec}`. On success `ec == std::errc{}`; on bad input it sets `ec` and leaves `out` untouched — no throw. Ideal for parsing many fields (as the chapter project does).

### 16. `enum class Direction : std::uint8_t { North, East, South, West };` — what does `: std::uint8_t` do?

A. Restricts the enum to exactly four values
B. Fixes the underlying integer type, making `sizeof(Direction) == 1`
C. Makes the enumerators start at `1` instead of `0`
D. Allows implicit conversion to `int`

**Answer: B** — the `: type` clause pins the storage. Without it the underlying type is `int` (4 bytes); with `std::uint8_t` each `Direction` value is one byte.

### 17. What does `using enum Direction;` inside a `switch` block let you write?

A. `case North:` instead of `case Direction::North:`
B. implicit conversion of `Direction` to `int`
C. a `default:` label that is no longer required
D. `switch` on a `Direction` without any `case` labels

**Answer: A** — `using enum` (C++20) brings the enumerators into the current scope for that block, so the `case` labels drop the `Direction::` qualifier. Outside the block they are still scoped.

### 18. `using Sample = std::vector<std::int64_t>;` — `Sample` is...

A. a new, distinct type incompatible with `std::vector<std::int64_t>`
B. exactly `std::vector<std::int64_t>` under a shorter name — fully interchangeable
C. a subclass of `std::vector`
D. only valid inside a template

**Answer: B** — a type alias introduces no new type. `Sample` and `std::vector<std::int64_t>` are the same type; the alias just makes long nested types readable in signatures.

### 19. Which clock should you use to measure how long a block of code takes?

A. `std::chrono::system_clock` — it has the highest resolution
B. `std::chrono::steady_clock` — it never jumps backward
C. either; they are the same clock
D. `std::chrono::utc_clock`

**Answer: B** — `steady_clock` is monotonic: it is unaffected by the wall clock being adjusted (NTP, DST, the user changing the time). `system_clock` is the wall clock — right for calendar dates, wrong for elapsed-time measurement.

### 20. A function returns `std::optional<int>`. Which expression gives you the value, or `-1` if there is none?

A. `opt.value()` — it returns `-1` when empty
B. `opt.value_or(-1)`
C. `*opt` — it is `-1` when empty
D. `opt.has_value() ? *opt : opt.value()`

**Answer: B** — `value_or(fallback)` returns the contained value if present, otherwise `fallback`. `opt.value()` (option A) *throws* `std::bad_optional_access` when empty; `*opt` (option C) is undefined behavior when empty.
