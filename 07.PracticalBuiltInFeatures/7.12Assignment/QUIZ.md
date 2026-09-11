# Chapter 7 Quiz — Practical Built-In Features

18 multiple-choice questions covering **Chapter 7 (Practical Built-In
Features)**: `std::array` vs `std::vector`, sorting/searching/`accumulate`,
ranges and views, strings beyond the basics (`find`/`erase`/`replace`/
`insert`, string streams), `std::string_view`, files with formatted `>>`/
`<<`, reading CSV data with a vendored library, `<regex>`, and the Titanic
dataset project. Each question is followed immediately by its correct
answer and a short explanation.

---

### 1. What is the key difference between `std::array<int, 5>` and `std::vector<int>`?

A. `array` lives on the heap, `vector` does not
B. `array`'s size is fixed and part of its type; `vector` can grow and shrink at run time
C. `vector` cannot be looped over with range-based for
D. There is no difference — they are aliases for the same type

**Answer: B** — `std::array<T, N>` stores its `N` elements inline with no heap allocation, and `N` is baked into the type. `std::vector<T>` allocates on the heap and can `push_back` to grow.

### 2. What does `.at(i)` do differently from `[i]` on both `array` and `vector`?

A. Nothing — they are identical
B. `.at(i)` is bounds-checked and throws `std::out_of_range` on a bad index; `[i]` does not check
C. `[i]` is bounds-checked; `.at(i)` is not
D. `.at(i)` only works on `const` containers

**Answer: B** — `.at(i)` checks the index and throws if it is out of range. `[i]` skips the check for speed, so an out-of-range `[i]` is undefined behavior.

### 3. Why must data be sorted before calling `std::ranges::binary_search` on it?

A. It does not need to be — `binary_search` sorts internally
B. `binary_search` works by repeatedly halving the search range, which only gives a correct answer when the data is already in order
C. Sorting is only required for `std::string` elements
D. `binary_search` only accepts `std::array`, never `std::vector`

**Answer: B** — binary search assumes order to decide which half to discard at each step. Run it on unsorted data and it can miss an element that is actually present.

### 4. `std::accumulate(v.begin(), v.end(), 1, multiply)` where `multiply(x, y)` returns `x * y`...

A. Sums the elements of `v`, ignoring `multiply`
B. Folds the elements together using `multiply` instead of `+`, starting from `1` — i.e. their product
C. Is a compile error — `accumulate` only supports addition
D. Multiplies every element by `1` and returns a new vector

**Answer: B** — `accumulate`'s optional fourth argument replaces `+` with whatever binary operation you pass — a named function or a lambda both work.

### 5. What makes `std::views::filter` and `std::views::transform` *lazy*?

A. They run on a background thread
B. They do not build a new container up front — each wraps the underlying range and produces values on demand as it is iterated
C. They only work with `std::array`, never generated ranges
D. "Lazy" just means they are slower than a hand-written loop

**Answer: B** — a view is a thin wrapper, not a copy. Nothing is computed until something actually iterates the view (a range-based for, `accumulate`, converting it to a `std::vector`, etc.).

### 6. Piping views with `|`, as in `numbers | std::views::filter(...) | std::views::transform(...)`, reads as...

A. A bitwise OR of the two operations
B. A pipeline: take `numbers`, keep what the filter accepts, then transform what was kept — left to right
C. Two independent, unrelated operations on `numbers`
D. A syntax error before C++23

**Answer: B** — `|` chains views left to right, the same idea as a shell pipeline. Each stage wraps the one before it.

### 7. `s.find("is")` returns `std::string::npos`. What does that mean?

A. `"is"` was found at index 0
B. `"is"` was not found anywhere in `s`
C. `s` is empty
D. `npos` is a compile error

**Answer: B** — `npos` is the sentinel "no such position" value every `find`-family function returns when the search fails. Always compare against it before using the result as an index.

### 8. In `s.replace(position, 1, "_")`, what do the three arguments mean?

A. Replace the whole string with `"_"`, ignoring `position` and `1`
B. Starting at `position`, replace `1` character with the string `"_"`
C. Insert `"_"` at `position`, `1` time
D. `replace` only takes two arguments — this is invalid

**Answer: B** — `replace(pos, count, newText)` removes `count` characters starting at `pos` and puts `newText` in their place. Looping this with `find` is how you replace every occurrence of something.

### 9. What is the purpose of an `std::ostringstream`?

A. It reads formatted values out of a string
B. It accumulates pieces of different types (strings, numbers, ...) into one string using `<<`, the same operator `std::cout` uses
C. It can only hold a single `int` at a time
D. It writes directly to a file on disk

**Answer: B** — `ostringstream` behaves like `std::cout`, except the destination is an in-memory string, retrieved with `.str()`, instead of the console.

### 10. What does a `std::string_view` actually store?

A. A full copy of the characters it displays
B. A pointer to characters owned by someone else, plus a length — no ownership, no copy
C. A `std::vector<char>`
D. Nothing — it is purely a compile-time construct with no run-time representation

**Answer: B** — a `string_view` is a non-owning (pointer, length) pair. It is cheap to pass around, but it is only valid as long as the data it points at (a `std::string`, a literal) is still alive.

### 11. If `std::string original{"red"}; std::string_view view{original};` and then `original.at(0) = 'R';`, what does `view` show afterward?

A. Still `"red"` — views take a snapshot at construction
B. `"Red"` — the view sees the change, because it points at `original`'s own characters
C. A crash — modifying `original` invalidates `view` immediately
D. `view` becomes empty

**Answer: B** — a `string_view` has no data of its own; it is watching `original`'s characters directly, so any change to `original` is visible through the view.

### 12. Reading a file with `input >> account >> name >> balance` (formatted extraction) instead of `std::getline(input, line)` differs how?

A. There is no difference between the two
B. `>>` reads one whitespace-delimited, typed field at a time (so three reads pull three separate fields off the stream); `getline` reads one whole line as a single string
C. `getline` can only be used with `std::cin`, never a file
D. `>>` cannot read numbers, only strings

**Answer: B** — `>>` splits on whitespace and converts to the target variable's type as it reads, which is exactly what lets one line yield an `int`, a `std::string`, and a `double` in one statement.

### 13. Why is `rapidcsv.h` *vendored* into the project folder instead of hand-writing a CSV parser with `std::stringstream`?

A. The standard library cannot open files at all
B. A real CSV parser needs to handle quoting, embedded commas, and header rows correctly — a small hand-rolled splitter gets those wrong on real-world data; vendoring reuses a library that already solved it
C. Vendoring is required by the C++ standard for any third-party header
D. `stringstream` cannot read numbers, only text

**Answer: B** — 7.6's `istringstream` splitting is fine for one clean line; a CSV file's quoting/escaping rules are enough extra complexity that reaching for a small, focused library (the same vendoring pattern from 6.17) is the practical choice.

### 14. `rapidcsv::Document doc{"accounts.csv"}; auto balances{doc.GetColumn<double>("balance")};` gives you...

A. A single `double` — the sum of the column
B. A `std::vector<double>`, one entry per row, converted from the CSV's text to `double`
C. A `std::string` containing the raw column text
D. Nothing — `GetColumn` requires a numeric header, not a name

**Answer: B** — `GetColumn<T>("name")` reads an entire named column and converts each cell to `T`, returning them as a `std::vector<T>` in row order.

### 15. `std::regex_match("Wally", std::regex{"[A-Z][a-z]+"})` returns `true` because...

A. `regex_match` only checks the first character
B. The whole string fits the pattern: one capital letter, followed by one or more lowercase letters, with nothing left over
C. `regex_match` ignores case entirely by default
D. The pattern matches any word of any length

**Answer: B** — `regex_match` requires the *entire* string to satisfy the pattern, start to end. `"Wally99"` would fail the same pattern because of the trailing digits.

### 16. How does `std::regex_search` differ from `std::regex_match`?

A. They are exactly the same function under two names
B. `regex_search` looks for a match *anywhere* inside the string; `regex_match` requires the *whole* string to match
C. `regex_search` only works on file streams
D. `regex_match` is deprecated in C++20

**Answer: B** — `regex_search("Programming is fun", std::regex{"fun"})` finds `"fun"` even though it is only part of the string; `regex_match` with the same pattern would fail because `"Programming is fun"` as a whole does not equal `"fun"`.

### 17. In the Titanic project, why filter the `age` column with `std::views::filter([](double a){ return !std::isnan(a); })` before computing statistics?

A. To remove passengers who did not survive
B. Some age values are missing in the dataset (parsed as NaN); including them would corrupt an average or a sorted median
C. `isnan` sorts the ages in the process
D. Views cannot hold `double` values otherwise

**Answer: B** — the dataset uses `"?"` for unknown ages, which `ConverterParams{true}` turns into `NaN` instead of throwing. Filtering those out before averaging or sorting keeps the statistics meaningful.

### 18. `std::ranges::count_if(survived, [](int s){ return s != 0; })` in the Titanic project computes...

A. The total number of passengers, survivors or not
B. How many entries in `survived` are non-zero — i.e. how many passengers survived
C. The sum of the `survived` column
D. Whether at least one passenger survived (a `bool`)

**Answer: B** — `count_if` counts how many elements satisfy the predicate. Here that predicate is "is this passenger's `survived` value non-zero", so the result is the survivor count.
