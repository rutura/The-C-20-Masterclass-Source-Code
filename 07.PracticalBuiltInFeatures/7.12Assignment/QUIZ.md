# Chapter 7 Quiz - Practical Built-In Features

20 multiple-choice questions covering **Chapter 7 (Practical Built-In
Features)**: bounds checking and collection parameters, `std::vector`,
sorting, searching and `accumulate`, ranges and views, strings,
`std::format`, `std::string_view`, `<chrono>` and `<regex>`. Each question is
followed immediately by its correct answer and a short explanation.

---

### 1. How do `roll_tally[face]` and `roll_tally.at(face)` differ on a `std::array`?

A. `[]` does not check the index (undefined behavior if it is out of range), `.at()` is bounds-checked and throws `std::out_of_range`
B. `[]` throws on a bad index, `.at()` silently reads garbage
C. They are identical
D. `.at()` only works on `const` arrays

**Answer: A** - `[]` is fast but trusts you. `.at()` checks the index first, which costs a little and turns a silent mistake into a visible exception. The same is true for `std::vector`.

### 2. What is the default choice for a function parameter that holds a collection the function only reads?

A. By value
B. A `const` reference, `const T&`
C. A plain reference, `T&`
D. A pointer

**Answer: B** - no copy is made (a by-value parameter copies all `n` elements on every call, which is `O(n)`), and the compiler guarantees the function cannot modify the caller's data. Reach for a plain `&` only when the function's job is to mutate the caller's data.

### 3. What are the sizes of `std::vector<int> a(5);` and `std::vector<int> b{5};`?

A. Both have 5 elements
B. `a` has 1 element, `b` has 5
C. `a` has 5 elements (all 0), `b` has 1 element (the value 5)
D. Both have 1 element

**Answer: C** - parentheses size the vector, braces list its elements. `{5}` is a list with one element, the value `5`.

### 4. What is a higher-order function?

A. A function with more than three parameters
B. A function declared at the top of the file
C. A function that returns a `double`
D. A function that takes another function as an argument (or returns one)

**Answer: D** - `std::accumulate`, `std::views::filter` and `std::views::transform` all take a small function, often a lambda, that decides what to do with one element. You supply that decision, the library supplies the loop.

### 5. Why does a length-sorting comparator end with an extra `return a < b;` for names of the same length?

A. Without it the code does not compile
B. `std::ranges::sort` does not promise an order for tied elements, so the tie-break makes the final order definite
C. It makes the sort run in `O(1)`
D. It removes the duplicates

**Answer: B** - `kiwi` and `date` are tied on length. A second rule inside the comparator decides between them, so the result is always the same, whatever the compiler.

### 6. What does `std::ranges::binary_search` require of the data?

A. At least one million elements
B. All elements must be distinct
C. The data must already be sorted in the order the search expects (ascending by default)
D. The elements must be `int`

**Answer: C** - discarding half the data at each look only makes sense if the order tells you which half to discard. It then needs only about 20 looks for 1,000,000 elements.

### 7. `fruits` is `{apple, mango, date, kiwi, fig}`, sorted by length and not alphabetically. What can `std::ranges::binary_search(fruits, "fig"s)` do?

A. It is guaranteed to return `true`, `"fig"` is in the vector
B. It does not compile
C. It sorts the vector first
D. It can return `false` even though `"fig"` is there, because the data is not in the order the search assumes

**Answer: D** - the search halves the data faithfully, but the halving rule is wrong for this order. The failure is not reliable, which is what makes it dangerous. Sort in the order the search expects right before you search.

### 8. A nested loop visits every pair of elements of the same collection. If the data doubles from 4 to 8 elements, how does the number of steps change?

A. It quadruples, from 16 to 64
B. It doubles, from 16 to 32
C. It stays the same
D. It grows by one

**Answer: A** - `n x n` steps: 4 x 4 = 16 and 8 x 8 = 64. That is `O(n^2)`: twice the data, four times the work. Compare that with `O(n)`, which doubles, and `O(log n)`, which grows by one step.

### 9. What does `std::accumulate(factors.begin(), factors.end(), 0, multiply)` return for `{1, 2, 3, 4, 5}`, where `multiply(x, y)` returns `x * y`?

A. 120
B. 15
C. 0
D. 1

**Answer: C** - `accumulate` starts from the starting value you give it, and `0 * anything` is `0`. For a product the starting value must be `1`, which gives 1, 2, 6, 24, 120.

### 10. What does it mean that `std::views::filter` and `std::views::transform` are lazy?

A. They run on a background thread
B. They are slower than a hand-written loop
C. They only work on `std::array`
D. They build nothing up front: values are produced on demand when something iterates the view

**Answer: D** - a view is a thin wrapper around a range, not a copy. Nothing is filtered or transformed until a range-based `for`, `accumulate` or similar asks for values.

### 11. What does `log.find("xyz")` return when `"xyz"` is not in the string `log`?

A. `std::string::npos`
B. `-1`
C. `0`
D. An empty string

**Answer: A** - every `find`-family function returns the `npos` sentinel for "not found". Compare against it before using the result as an index. It is also how the "replace every space" loop knows to stop.

### 12. Why does `auto bad{"cat" + "acomb"};` fail to compile, while `"cat"s + "acomb"` works?

A. `auto` cannot deduce strings
B. A plain literal is a `const char[N]` array, and you cannot add two C-style literals, while the `s` suffix makes the left side a real `std::string`
C. The result would be too long
D. The `+` operator does not exist in C++

**Answer: B** - the `s` suffix matters exactly when there is no `std::string` on the left to do the converting for you, for example with `auto` or before a `+`.

### 13. How does `std::format` differ from `std::print`/`std::println`?

A. They are identical, `format` is an older name for `print`
B. `format` can only format numbers
C. `print` returns a `std::string`
D. `format` returns a `std::string` and prints nothing, `print`/`println` write the result straight to the console

**Answer: D** - use `format` when the text is going somewhere other than the screen: a log file, part of a larger string, a label built piece by piece.

### 14. What does `{:>8.2f}` mean in a format spec?

A. Right-aligned in a field 8 characters wide, with exactly 2 digits after the decimal point
B. Left-aligned, 8 digits before the point, 2 after
C. Centered, width 2, precision 8
D. Right-aligned, 8 digits after the decimal point

**Answer: A** - the grammar is `{:fill align width.precision type}`: `>` right-aligns, `8` is the minimum width, `.2` the number of digits after the point, and `f` fixed-point. `std::format("{:>8.2f}", 4.5)` gives `"    4.50"`.

### 15. `std::string color{"red"}; std::string_view color_view{color};` then `color.at(0) = 'R';`. What does `color_view` show?

A. `"red"`, views are snapshots
B. `"Red"`, because a `string_view` is just a pointer and a length into `color`'s own characters
C. Nothing, it is now empty
D. The program crashes

**Answer: B** - the view owns no characters, so it sees every later change. That also means it is only valid while the text it points at is alive.

### 16. Which conversion compiles implicitly?

A. `std::chrono::seconds s{60}; std::chrono::minutes m{s};`
B. `std::chrono::duration<long> d{30}; std::chrono::minutes m{d};`
C. `std::chrono::minutes m{2}; std::chrono::seconds s{m};`
D. None of them

**Answer: C** - minutes to seconds multiplies by an integer, so it never loses information. The other conversions could produce a fraction, so the compiler refuses them based on the types alone, even when the value divides evenly. `std::chrono::duration_cast` is the explicit override, and it truncates.

### 17. Which clock should you use to measure how long a block of code takes, and why?

A. `system_clock`, because it has the best precision
B. Either one, they behave identically
C. `system_clock`, because it is synchronized with the network
D. `steady_clock`, because it never goes backward even if the system clock is adjusted

**Answer: D** - `system_clock` is wall-clock time and can jump when the system time is corrected. `steady_clock` is guaranteed to be monotonic, so `end - start` (a duration) can never come out negative.

### 18. How does `std::regex_search` differ from `std::regex_match`?

A. `regex_search` looks for a match anywhere inside the string, `regex_match` requires the whole string to match
B. They are the same function under two names
C. `regex_search` requires the whole string to match, `regex_match` finds a match anywhere
D. `regex_search` only works on file streams

**Answer: A** - `regex_search("Debugging is fun", std::regex{"fun"})` is `true`, while `regex_match` with the same pattern is `false` because the whole string is not just `"fun"`.

### 19. After a successful `regex_match` into a `std::smatch m` with the pattern `(\d{4})/(\d{1,2})/(\d{1,2})` on `"2025/3/9"`, what are `m[0]` and `m[1]`?

A. `"2025"` and `"3"`
B. `"2025/3/9"` (the entire match) and `"2025"` (what the first `()` group captured)
C. `"2025/3/9"` for both
D. `"3"` and `"9"`

**Answer: B** - `m[0]` is always the entire match, and `m[1]`, `m[2]`, `m[3]` are the capture groups in order. `std::stoi(m[1])` then turns the captured text into a number.

### 20. What does `std::regex_replace("cat-7, dog-42, bird", std::regex{R"((\w+)-(\d+))"}, "$2:$1")` return?

A. `"cat-7, dog-42, bird"`
B. `"7:cat42:dog"`
C. `"7:cat, 42:dog, bird"`
D. `"$2:$1, $2:$1, bird"`

**Answer: C** - `$1` and `$2` are filled from each match's own groups, and the unmatched text (`", "` and `", bird"`) is copied through. The original string is never modified, so you must catch the returned `std::string`. With `std::regex_constants::format_no_copy` the unmatched text would be dropped, giving `"7:cat42:dog"`.
