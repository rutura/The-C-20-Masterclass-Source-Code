# Practical Built-in Features (Collections and More)

Chapters 3 to 6 covered the **language**: variables, control flow,
functions. But look at the programs we can actually write so far and a
gap shows up fast.

```
   "read 20 numbers and print the 3 biggest"
        │
        ▼
   we have no way to HOLD 20 numbers without naming 20 variables

   "find the expense whose id is 4071"
        │
        ▼
   what does the function return when there IS no such expense?

   "how long did that loop take?"
        │
        ▼
   we have no clock
```

Every real program needs a handful of **standard-library facilities**
the language itself does not give you: a place to put a list of things,
proper text handling, a clock, a way to say "this result might be
missing." This chapter is that toolkit.

Everything here is **modern C++ first**:

```
   the old way (next chapter)          this chapter
   ─────────────────────────          ────────────
   int scores[5];                 →    std::array<int, 5>
   int* data = new int[n];        →    std::vector<int>
   char name[64]; strcpy(...)     →    std::string
   const char*  /  atoi()         →    std::string_view  /  std::from_chars
```

Raw pointers, `new`/`delete`, and the C-style string functions come in
the **next chapter**. You will not need any of them for what follows.

Each lecture below is a **self-contained program** built around one
facility. The chapter then closes with a **non-trivial project** - a
command-line expense-report tool - built three ways, exactly as chapter
6's image writer was: once with no dependency, once with a **vendored**
third-party library, once with the library **fetched by CMake**.

After this chapter: pointers and the C-style APIs, then classes.

---

## 7.2 Fixed-size collections: `std::array`

### The problem

We want to add up seven exam scores. With plain variables:

```cpp
int s0{42}, s1{17}, s2{91}, s3{8}, s4{63}, s5{29}, s6{71};
int sum{s0 + s1 + s2 + s3 + s4 + s5 + s6};
```

Seven names, and no loop can touch them - `s0` through `s6` are seven
unrelated variables as far as the compiler is concerned. Add an eighth
score and you edit three places.

### The fix: one name, many slots

**`std::array<T, N>`** is `N` values of type `T`, laid out back-to-back,
with **one name** for the whole run and an **index** to pick a slot.

```cpp
#include <array>

std::array<int, 5> scores{42, 17, 91, 8, 63};
//         │    │
//         │    └── N: how many elements (fixed, known at compile time)
//         └── T: the element type
```

```
   std::array<int, 5> scores{42, 17, 91, 8, 63};

   index:    0     1     2     3     4
           ┌─────┬─────┬─────┬─────┬─────┐
   scores: │ 42  │ 17  │ 91  │  8  │ 63  │
           └─────┴─────┴─────┴─────┴─────┘
              ▲                       ▲
           scores[0]               scores[4]
           scores.front()          scores.back()
```

It is the direct replacement for `int scores[5];` - **identical memory
layout**, a single block of five ints - but unlike the C array it knows
its own length and carries real member functions.

### Reading and writing a slot: `[]` vs `.at()`

Two ways to reach element `i`:

```cpp
scores[2]        // 91   - fast, NO bounds check
scores.at(2)     // 91   - checks i first, throws std::out_of_range if bad
```

```
                    i = 2  (valid)        i = 99  (out of range)
                    ────────────────      ─────────────────────
   scores[i]    →   the element            undefined behavior:
                                           reads whatever is in memory there,
                                           or crashes - no warning

   scores.at(i) →   the element            throws std::out_of_range
                                           (a clean, catchable error)
```

Use `[]` in a loop you have already bounded with `.size()`. Use `.at()`
when the index comes from outside - user input, a parsed file - and a bad
value should be an error, not a silent corruption.

```cpp
try {
    std::println("{}", scores.at(99));
} catch (const std::out_of_range& ex) {
    std::println("bad index: {}", ex.what());
}
```

### `.size()` - the array carries its own length

```cpp
for (std::size_t i{0}; i < scores.size(); ++i) {
    std::println("scores[{}] = {}", i, scores[i]);
}
```

No `sizeof` trick, no separate `const int N = 5;` to keep in sync, no
passing the length alongside the array into every function. `.size()` is
always right.

### Walking it with range-based `for`

When you do not need the index, iterate the elements directly:

```cpp
int sum{0};
for (const int& s : scores) {   // const int& : read each element, no copy
    sum += s;
}
```

```
   for (const int& s : scores)        for (int& s : scores)
   ──────────────────────────         ─────────────────────
   s is a read-only alias to          s is a writable alias
   each element in turn               s += 10;  changes the element in place

   use when you only READ             use when you MODIFY
```

C++20 lets you fold a loop-local variable into the `for` with an
**init-statement**, so a running total does not leak into the
surrounding scope:

```cpp
for (int total{0}; const int& s : scores) {
    total += s;
    std::println("...running total {}", total);
}
// `total` does not exist here
```

### Initializing

Brace-init, always:

```cpp
std::array<int, 5> a{42, 17, 91, 8, 63};   // all five given
std::array<int, 5> b{1, 2};                // b = {1, 2, 0, 0, 0}  - rest zero-filled
std::array<int, 5> c{};                    // all zero
```

And the compiler can **deduce `T` and `N` from the braces** (class
template argument deduction, CTAD):

```cpp
std::array temps{19.5, 21.0, 18.75};   // deduced: std::array<double, 3>
```

### When to use it

`std::array` when the count is **known and fixed**: a chessboard (64
squares), a week of readings (7), the RGB channels of a pixel (3). When
the count changes at run time, you want the next section.

---

## 7.3 Growable sequences: `std::vector`

### The problem

`std::array`'s size is baked in at compile time. But we usually do not
know the count until the program runs:

```cpp
// read expenses from a file until it ends - how many? no idea until we try
std::array<Expense, ???> expenses;   // there is no number to write here
```

### The fix: a sequence that grows

**`std::vector<T>`** is the same idea as `std::array` - a contiguous run
of `T`, indexable, iterable - except its length can **change while the
program runs**.

```cpp
#include <vector>

std::vector<int> primes{2, 3, 5, 7, 11};   // starts with 5 elements
primes.push_back(13);                       // now 6
primes.push_back(17);                       // now 7
```

```
   push_back appends one element to the end

   {2, 3, 5, 7, 11}                    {2, 3, 5, 7, 11, 13}
   ┌──┬──┬──┬──┬──┐   push_back(13)    ┌──┬──┬──┬──┬──┬──┐
   │2 │3 │5 │7 │11│  ───────────────►  │2 │3 │5 │7 │11│13│
   └──┴──┴──┴──┴──┘                    └──┴──┴──┴──┴──┴──┘
```

**This is the container to reach for by default.** Use `std::array` only
when you have a specific reason (fixed size, no heap allocation).
Everything else: `std::vector`.

### `size()` vs `capacity()` - and why growth is still cheap

A vector keeps a block of memory that is usually **bigger than it
currently needs**. `size()` is how many elements are in it;
`capacity()` is how many would fit before it must find a bigger block.

```
   std::vector<int> v;  v.push_back(...) five times

   after 1:  size 1, capacity 1   [10]
   after 2:  size 2, capacity 2   [10][20]
   after 3:  size 3, capacity 4   [10][20][30][ ]        ← grew the block, room to spare
   after 4:  size 4, capacity 4   [10][20][30][40]
   after 5:  size 5, capacity 8   [10][20][30][40][50][ ][ ][ ]   ← grew again
```

Most `push_back`s just drop the value into a spare slot. Only
occasionally does the vector allocate a larger block and move the
elements over. If you know roughly how many you will add, **`reserve`**
grabs the capacity up front and skips the regrowth entirely:

```cpp
std::vector<int> ids;
ids.reserve(1000);          // one allocation now...
for (int i{0}; i < 1000; ++i) {
    ids.push_back(i);       // ...none of these reallocate
}
```

### `push_back` vs `emplace_back`

```cpp
std::vector<std::string> names;

names.push_back("Ada");        // build a temporary std::string, then move it in
names.emplace_back("Ada");     // build the std::string directly in the vector's slot
```

```
   push_back("Ada")                    emplace_back("Ada")
   ───────────────                     ──────────────────
   "Ada" → temp std::string            "Ada" → std::string built
              │                                 straight into the slot
              ▼
   move temp into the vector           (no temporary, no move)
```

For `int` the two are identical. For a type that is costly to build or
move, `emplace_back` skips a step.

### The `{}` vs `()` gotcha

```cpp
std::vector<int> a{5, 0};   // TWO elements: 5 and 0
std::vector<int> b(5, 0);   // FIVE elements, each 0   ← (count, value) constructor
```

Braces are always "here is the list of elements." Parentheses reach a
different constructor. This is the one place the distinction bites.

### The rest of the everyday interface

```cpp
std::vector<int> v{10, 20, 30};

v[1]            // 20     - unchecked, like std::array
v.at(1)         // 20     - checked, throws std::out_of_range
v.at(0) = 99;   // works as an assignment target too
v.size();       // 3
v.empty();      // false
v.clear();      // now size 0, still usable

std::vector<int> x{1, 2, 3};
std::vector<int> y{1, 2, 3};
x == y;         // true  - compares element by element

std::vector<int> copy{x};   // copies all three elements
```

---

## 7.4 Sorting, searching, aggregating

### The problem

You have a `std::vector<int>` and you need it sorted, or you need its
largest element, or its total. You *could* write the loops:

```cpp
// sort by hand
for (std::size_t i{0}; i < v.size(); ++i) {
    for (std::size_t j{i + 1}; j < v.size(); ++j) {
        if (v[j] < v[i]) { std::swap(v[i], v[j]); }
    }
}
```

That is a slow sort, it is easy to get the indices wrong, and you will
write it again next week. The library already has these, correct and
fast.

### `std::ranges::sort` - order a whole container

```cpp
#include <algorithm>

std::vector<int> v{5, 2, 8, 1, 9, 3};

std::ranges::sort(v);           // {1, 2, 3, 5, 8, 9}  - ascending, the default
```

```
   {5, 2, 8, 1, 9, 3}  ──ranges::sort(v)──►  {1, 2, 3, 5, 8, 9}
```

To sort the other way, hand it a **comparison lambda** - "does `a` come
before `b`?":

```cpp
std::ranges::sort(v, [](int a, int b) { return a > b; });
//                    └──────────┬──────────┘
//              "a before b when a is the LARGER"  → descending

// {9, 8, 5, 3, 2, 1}
```

The `ranges::` version takes **the container itself**. The older
`std::sort(v.begin(), v.end())` needs an iterator pair; same result, more
to type.

### `std::ranges::binary_search` - is it in there?

```cpp
std::ranges::sort(v);                          // REQUIRED first
bool has8{std::ranges::binary_search(v, 8)};    // true
bool has6{std::ranges::binary_search(v, 6)};    // false
```

```
   binary_search only works on a SORTED range - it halves the search
   space each step, which only makes sense if the data is in order:

   look for 8 in {1, 2, 3, 5, 8, 9}
                        │
              middle is 3, 8 > 3 → discard the left half
                              {5, 8, 9}
                                 │
                       middle is 8 → found
```

Sort first, then search. Searching an unsorted range gives wrong
answers, not an error.

### `min_element` / `max_element` - returns a *position*, not a value

```cpp
auto it{std::ranges::max_element(v)};   // an ITERATOR to the largest element
int biggest{*it};                       // dereference with * to get the value
```

```
   {1, 2, 3, 5, 8, 9}
                 ▲
                 │
   max_element(v) ── an iterator pointing AT this element
                 │
      *max_element(v) ── dereference it ──► 9   (the value)
```

Why an iterator and not just the number? Because the position is often
what you want - "which day had the peak", not just "what was the peak".
When you only want the value, write the `*` and move on:

```cpp
std::println("range: {} .. {}",
             *std::ranges::min_element(v),
             *std::ranges::max_element(v));
```

### `std::accumulate` - fold a range down to one value

```cpp
#include <numeric>

int total{std::accumulate(v.begin(), v.end(), 0)};   // sum of all elements
```

```
   std::accumulate(v.begin(), v.end(), 0)

   start with the init value ─┐
                              0
                              + 1   → 1
                              + 2   → 3
                              + 3   → 6
                              + 5   → 11
                              + 8   → 19
                              + 9   → 28   ← the result
```

The third argument is the **starting value** - and it also **fixes the
result type**:

```cpp
std::vector<double> prices{1.5, 2.25, 0.99};

double bad{std::accumulate(prices.begin(), prices.end(), 0)};    // 3   - int accumulator!
double ok {std::accumulate(prices.begin(), prices.end(), 0.0)};  // 4.74
//                                                        ↑
//                          0   → running total is int, every += truncates
//                          0.0 → running total is double, fractions kept
```

An optional **fourth argument** swaps `+` for any two-argument operation
- a named function or a lambda:

```cpp
int product{std::accumulate(v.begin(), v.end(), 1,          // start at 1, not 0
                            [](int acc, int x) { return acc * x; })};
```

```
   1  ×1 →1  ×2 →2  ×3 →6  ×5 →30  ×8 →240  ×9 →2160
```

All of these work on `std::array` and `std::vector` alike - any
contiguous sequence.

---

## 7.5 Multidimensional data

### The problem

A tic-tac-toe board, a spreadsheet, a grid of pixels - the data is
naturally **2D**: rows and columns, addressed as `(row, col)`. A single
`std::array` or `std::vector` is 1D.

### The fix: an array of arrays

A row is `std::array<int, columns>`. A grid is **an array of those**:

```cpp
constexpr std::size_t rows{3};
constexpr std::size_t columns{4};

std::array<std::array<int, columns>, rows> board{{
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9, 10, 11, 12},
}};
```

```
   std::array<std::array<int, 4>, 3>
              └──────┬──────┘   │
              one row (4 ints)  three rows

              col 0   col 1   col 2   col 3
            ┌───────┬───────┬───────┬───────┐
   row 0    │   1   │   2   │   3   │   4   │   ← board[0] is this whole row
            ├───────┼───────┼───────┼───────┤
   row 1    │   5   │   6   │   7   │   8   │
            ├───────┼───────┼───────┼───────┤
   row 2    │   9   │  10   │  11   │  12   │
            └───────┴───────┴───────┴───────┘
                            ▲
                     board[1][2]  ==  7
                          │  └── column index (into the row)
                          └── row index (picks the row)
```

The nested braces in the initializer **mirror the nested type**: an
outer list of three, each an inner list of four.

### Indexing and iterating

One `[]` per dimension. `board[1]` is a row (a `std::array<int, 4>`);
`board[1][2]` is the int in it.

```cpp
board[0][0] = 100;              // one cell

for (int& cell : board[2]) {    // a whole row, by reference
    cell *= 10;
}

for (const auto& row : board) {         // row: const std::array<int, 4>&
    for (const auto& cell : row) {      // cell: const int&
        std::print("{:4}", cell);
    }
    std::println("");
}
```

`const auto&` here saves you writing `std::array<int, 4>` and then `int`
by hand - the compiler fills them in.

### Keep the type readable

`std::array<std::array<int, columns>, rows>` is a mouthful to repeat in
every function signature. A **type alias** (7.11) fixes that:

```cpp
using Grid = std::array<std::array<int, columns>, rows>;

void print_grid(const Grid& g);   // pass by const& - no copy of all 12 ints
```

---

## 7.6 A taste of ranges

This is a **taste**, not the tour - the ranges library gets a full
chapter later. Here is the single idea worth having now.

### The problem it solves

Say you want the sum of the squares of the even numbers from 1 to 10.
The step-by-step way builds a container at each stage:

```cpp
std::vector<int> evens;
for (int n{1}; n <= 10; ++n) {
    if (n % 2 == 0) { evens.push_back(n); }
}
std::vector<int> squares;
for (int n : evens) { squares.push_back(n * n); }
int total{std::accumulate(squares.begin(), squares.end(), 0)};
```

Two throwaway vectors, three loops, for one number.

### The fix: a view is a recipe, not a container

A **view** describes a transformation of a sequence. It stores no
elements - it produces each value on demand as you iterate.

```cpp
#include <ranges>

auto numbers{std::views::iota(1, 11)};       // 1, 2, 3, ... 10  - generated, not stored
```

Views are chained with the pipe `|`:

```cpp
auto result{
    std::views::iota(1, 11)
    | std::views::filter([](int n) { return n % 2 == 0; })   // keep the evens
    | std::views::transform([](int n) { return n * n; })     // square them
};
```

```
   iota(1,11):      1   2   3   4   5   6   7   8   9   10
                        │
   filter %2==0 :       2       4       6       8       10
                        │
   transform x*x:       4      16      36      64      100

   nothing above is stored - each value is computed as the loop below asks for it:

   for (int x : result) { ... }     // sees 4, then 16, then 36, ...
```

To turn a view back into a plain value, feed it to an algorithm:

```cpp
int total{std::accumulate(result.begin(), result.end(), 0)};   // 220
```

A view also works with a real container as its source:

```cpp
std::vector<int> data{3, 1, 4, 1, 5, 9, 2, 6};
auto big{data | std::views::filter([](int n) { return n >= 4; })};   // 4, 5, 9, 6
```

That is the whole idea for now: **compose the transformation, iterate
once, allocate nothing in between.**

---

## 7.7 `std::string` in depth

Chapter 5 introduced `std::string` for holding text. This section is the
rest of the everyday toolkit: measuring it, indexing it, searching it,
and editing it.

### Measuring

```cpp
std::string path{"/home/ada/report.txt"};

path.size();        // 20   - number of characters
path.length();      // 20   - EXACT same function, second name
path.empty();       // false
path.capacity();    // >= 20 - allocated storage, like vector::capacity()
```

### Indexing a character

Same `[]` / `.at()` split as the containers:

```cpp
path[0]          // '/'   - unchecked
path.at(0)       // '/'   - throws std::out_of_range on a bad index
path.front();    // '/'
path.back();     // 't'
```

### Searching: `find` and the `npos` sentinel

`find` returns the **index** of the first match - or the special value
`std::string::npos` when there is no match.

```cpp
std::string path{"/home/ada/report.txt"};

std::size_t slash{path.rfind('/')};      // 9   - rfind searches from the end
std::size_t dot  {path.rfind('.')};      // 16

if (path.find("report") != std::string::npos) {   // the "is it in there" idiom
    std::println("found it");
}
```

```
   /  h  o  m  e  /  a  d  a  /  r  e  p  o  r  t  .  t  x  t
   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
                              ▲                 ▲
                      rfind('/') = 9    rfind('.') = 16

   find("zzz")  →  std::string::npos   (a huge sentinel value meaning "not found")
```

### Slicing out a piece: `substr`

`substr(pos, count)` copies out a run of characters. Combine it with
`find` to pull apart a path:

```cpp
std::string filename {path.substr(slash + 1)};                    // "report.txt"  (to the end)
std::string stem     {filename.substr(0, filename.rfind('.'))};   // "report"
std::string extension{path.substr(dot + 1)};                      // "txt"
```

```
   /home/ada/report.txt
             └────┬────┘└┬┘
          substr(10)   substr(17)
          "report.txt"  "txt"
```

### Building and editing

```cpp
std::string s{"Hello"};
s += ", ";          // append - modifies s in place
s += "world!";      // "Hello, world!"

std::string a{"foo"};
std::string b{a + "bar"};   // + makes a NEW string; prefer += in a loop
```

```
   in a loop:   result += piece;      ← no temporary each time
   avoid:       result = result + piece;   ← builds and throws away a temp every pass
```

Edit in the middle:

```cpp
std::string label{"report.txt"};
label.insert(0, "final-");        // "final-report.txt"
label.erase(0, 6);               // "report.txt"        - remove 6 chars from index 0

std::string sentence{"the quick brown fox"};
sentence.replace(4, 5, "slow");   // "the slow brown fox"  - replace 5 chars at index 4
```

### Prefix / suffix / contains

Clearer than a `find` comparison:

```cpp
path.starts_with("/home");   // true    (C++20)
path.ends_with(".txt");      // true    (C++20)
path.contains("report");     // true    (C++23)
```

```
   "/home/ada/report.txt"
    └───┘            └───┘
  starts_with       ends_with
   ("/home")         (".txt")
```

Before C++23 you wrote `s.find(x) != std::string::npos` for `contains`;
now the name says it.

### Escape sequences and raw string literals

Inside a normal `"..."` literal, backslash starts an **escape**:

```cpp
std::println("tab\there, newline\nhere, a quote \" and a backslash \\");
```

That is a problem for text that is *full* of backslashes - Windows
paths, regexes, JSON. A **raw string literal** `R"(...)"` takes every
character between the delimiters **literally**, no escaping:

```cpp
std::string win{R"(C:\Users\ada\report.txt)"};    // backslashes are just backslashes
std::string json{R"({"name": "Ada", "age": 42})"}; // quotes need no \"
```

```
   "C:\Users\ada"     →  \U and \a get (mis)read as escapes - wrong / won't compile
   R"(C:\Users\ada)"  →  exactly those 13 characters
```

---

## 7.8 String / number conversions

Text comes in from files, arguments, and users as characters. To compute
with it you need a **number**; to print a number nicely you sometimes
need it back as **text**.

```
   "3500"  ──parse──►  3500        (int)
    3500   ──format─►  "3500"      (text)
```

C++ gives you two toolkits for this: a convenient one that throws on bad
input, and a modern one that does not.

### Number → text

```cpp
std::string a{std::to_string(42)};        // "42"
std::string b{std::to_string(3.14159)};   // "3.141590"
```

`std::to_string` is the quick option: always the `"C"` locale (so a
`double` always uses `.`), a fixed default precision.

### Text → number, the convenient way: `std::stoi` / `std::stod`

They parse the **leading** number and stop:

```cpp
int    n{std::stoi("  128 apples")};   // 128   - skips leading spaces, stops at ' '
double d{std::stod("2.5e3")};          // 2500.0
```

But they **throw** on trouble:

```cpp
try {
    int bad{std::stoi("hello")};       // no number at all
} catch (const std::invalid_argument& ex) {
    std::println("not a number: {}", ex.what());
} catch (const std::out_of_range& ex) {
    std::println("number too big for int: {}", ex.what());
}
```

```
   std::stoi(text)
        │
        ├─ leading digits?  ──yes──►  parse them, return the int
        │
        ├─ no digits       ──────────►  throw std::invalid_argument
        │
        └─ digits, but value too big ─►  throw std::out_of_range
```

### Text → number, the modern way: `std::from_chars`

```cpp
#include <charconv>

std::string_view field{"3500"};
int value{0};

auto [ptr, ec]{std::from_chars(field.data(),
                               field.data() + field.size(),
                               value)};
```

No exceptions, no locale, no memory allocation. It reports what happened
through the returned pair:

```
   auto [ptr, ec] = std::from_chars(begin, end, value);
             │  │
             │  └── ec  : an error code
             │            ec == std::errc{}                  → success
             │            ec == std::errc::invalid_argument  → not a number
             │            ec == std::errc::result_out_of_range→ too big
             │
             └── ptr : points one past the last character consumed
                       (so ptr - begin tells you how much it read)
```

```cpp
if (ec == std::errc{}) {
    std::println("parsed {}", value);
} else if (ec == std::errc::invalid_argument) {
    std::println("not a number");
}
```

On failure, `value` is **left untouched** - nothing is thrown, nothing
is corrupted. This is what you want when parsing lots of fields where
some are expected to be junk (the chapter project parses a whole CSV
this way).

### Number → text, the modern way: `std::to_chars`

The mirror image - writes digits into a buffer you provide, no
allocation:

```cpp
std::array<char, 32> buffer{};
auto [end, ec]{std::to_chars(buffer.data(),
                             buffer.data() + buffer.size(),
                             987654)};
if (ec == std::errc{}) {
    std::string_view written{buffer.data(), end};   // "987654"
}
```

```
   convenient (throws, allocates)     modern (no throw, no alloc)
   ─────────────────────────────     ───────────────────────────
   int n = std::stoi(str);           std::from_chars(b, e, n)  → {ptr, ec}
   std::string s = std::to_string(n);std::to_chars(b, e, n)    → {ptr, ec}
```

---

## 7.9 `std::string_view` parameters

### The problem

Here is a function that counts vowels. The obvious parameter type is
`const std::string&`:

```cpp
std::size_t count_vowels(const std::string& text);

count_vowels(name);            // name is a std::string - fine, no copy
count_vowels("hello world");   // a string LITERAL...
```

That last call quietly builds a **whole temporary `std::string`** - it
allocates memory, copies `"hello world"` into it, runs the function,
then destroys it. Just to look at 11 characters we already had.

### The fix: a non-owning view of characters

**`std::string_view`** is a tiny handle: a pointer to some characters,
plus a length. It does not own them and never copies them.

```
   std::string  "hello world"          std::string_view over it
   ┌───────────────────────┐           ┌─────────┬────────┐
   │ h e l l o   w o r l d │  ◄──────  │  ptr ●  │ len 11 │
   │ (owns this buffer)    │           └────┬────┴────────┘
   └───────────────────────┘                └─ points into the string above
                                             (no second copy of the text)
```

Take the parameter by `std::string_view` and **all three call styles
cost nothing**:

```cpp
std::size_t count_vowels(std::string_view text);   // by value - it is just ptr + len

count_vowels(name);                       // views the std::string's buffer
count_vowels("hello world");              // views the literal directly - no temp
count_vowels(std::string_view{name}.substr(0, 4));  // a view of the first 4 chars
```

### Cheap slicing

`substr`, `remove_prefix`, `remove_suffix` on a view all just adjust the
pointer and the length - **no allocation**:

```cpp
std::string_view trim(std::string_view text) {
    while (!text.empty() && text.front() == ' ') { text.remove_prefix(1); }
    while (!text.empty() && text.back()  == ' ') { text.remove_suffix(1); }
    return text;
}
```

```
   "   spaced   "
    ▲          ▲
    remove_prefix moves the start →     ← remove_suffix moves the end
        "spaced"        (same underlying characters, just a narrower window)
```

### The one rule you must not break

A `string_view` is only valid **while the characters it points at are
alive**. If those characters go away, the view is left pointing at
freed memory - a **dangling** view.

```cpp
std::string_view broken() {
    std::string local{"gone soon"};
    return local;            // DANGLING: `local` is destroyed as we return;
}                            // the returned view points at nothing

// safe: `full` outlives the view
std::string full{first + " " + last};
std::string_view ok{full};
```

```
   string_view  →  for PARAMETERS (you are just looking, briefly)
   std::string  →  when you must OWN the text or keep it around
```

---

## 7.10 Named constants with `enum class`

### The problem

A compass heading is one of four values. With an `int`:

```cpp
int heading{1};                 // 1 means... east? was north 0 or 1?

if (heading == 2) { /* south? */ }
heading = 47;                   // nothing stops this nonsense
```

Nothing in the code says what `1` and `2` mean, and any int at all is
accepted.

### The fix: a type with a fixed set of named values

```cpp
#include <cstdint>

enum class Direction : std::uint8_t {
    North,     // 0
    East,      // 1
    South,     // 2
    West,      // 3
};

Direction heading{Direction::East};   // reads for itself, and this is ALL it can hold
```

```
   Direction is its own type. A Direction variable holds exactly one of:

   Direction::North   Direction::East   Direction::South   Direction::West

   Direction d{47};                 // ERROR - 47 is not a Direction
   int n = Direction::East;         // ERROR - no silent conversion to int
```

The `class` keyword is what buys you that safety - the enumerators are
**scoped** (you must write `Direction::East`) and there is **no implicit
conversion to `int`**.

### The `: std::uint8_t` part

The optional `: type` after the name fixes the **underlying integer
type** the enum is stored as:

```cpp
enum class Direction : std::uint8_t { North, East, South, West };
//                     └─────┬─────┘
//                  store each value in ONE byte

sizeof(Direction);   // 1   (without the ": std::uint8_t" it would be 4 - int-sized)
```

### Crossing between the enum and its number - on purpose

You *can* get the integer, or build the enum from an integer, but you
must **ask** with a cast:

```cpp
Direction d{Direction::South};

int n{static_cast<int>(d)};              // 2   - enum → int

int raw{2};
Direction back{static_cast<Direction>(raw)};   // Direction::South   - int → enum
                                               // (only valid if raw is a real enumerator)
```

### `using enum` in a switch (C++20)

A `switch` over an enum repeats the type name on every label:

```cpp
switch (d) {
    case Direction::North: return "north";
    case Direction::East:  return "east";
    case Direction::South: return "south";
    case Direction::West:  return "west";
}
```

`using enum` pulls the enumerators into the block so you drop the
prefix:

```cpp
std::string_view to_text(Direction d) {
    using enum Direction;              // North, East, ... now usable unqualified HERE
    switch (d) {
        case North: return "north";
        case East:  return "east";
        case South: return "south";
        case West:  return "west";
    }
    return "unknown";
}
```

Outside that function the enumerators are still scoped - `using enum` is
local to the block it appears in.

---

## 7.11 Type aliases

### The problem

This type turns up in three function signatures and two variable
declarations:

```cpp
std::unordered_map<std::string, std::vector<std::int64_t>>
```

Retyping it is tedious and a single character wrong is a confusing
error. And a bare `double` named `temperature` in one place and
`price` in another does not say which is which.

### The fix: a second name for an existing type

```cpp
using Celsius = double;                                   // a readable name for a plain double
using Reading = std::int64_t;
using Sample  = std::vector<Reading>;
using SamplesByStation = std::unordered_map<std::string, Sample>;
```

```
   using  Sample  =  std::vector<Reading>;
          ──┬───     ─────────┬──────────
        the new name      the existing type it stands for

   Sample and std::vector<Reading> are now the SAME type -
   fully interchangeable, no conversion, no new type created.
```

```cpp
Celsius body_temp{36.8};
double  delta{0.4};
Celsius fever{body_temp + delta};   // Celsius IS double - mix them freely

SamplesByStation stations{          // vs. spelling the full type here
    {"roof",     {21, 22, 24}},
    {"basement", {17, 18}},
};
```

### `using` vs `typedef`

```cpp
using Celsius = double;      // modern: reads left-to-right, "Celsius = double"
typedef double Celsius;      // old C way: reads backwards, and cannot be templated
```

Prefer `using`. It reads in the natural order and works in more places.

---

## 7.12 Working with time

`<chrono>` is the standard library for time. It rests on three ideas.

```
   CLOCK       "what time is it right now?"
               std::chrono::steady_clock::now()
               std::chrono::system_clock::now()

   DURATION    a LENGTH of time, with a unit
               250ms   3s   2h        (needs the chrono_literals)

   TIME POINT  a specific INSTANT, as read from some clock
               now() returns one;  (end - start) is a DURATION
```

### Durations

Bring in the literal suffixes, then durations read like English:

```cpp
using namespace std::chrono_literals;

std::chrono::milliseconds timeout{250ms};
std::chrono::seconds      window{3s};

auto total{window + timeout};      // 3250ms - it picks a common unit automatically
long ms{timeout.count()};          // 250    - .count() drops the unit, gives the number
```

### Timing a piece of code

Take a reading before, a reading after, subtract:

```cpp
auto start{std::chrono::steady_clock::now()};

// ... work to be measured ...

auto elapsed{std::chrono::steady_clock::now() - start};   // a duration
auto ms{std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)};
std::println("took {}", ms);        // e.g. "took 5ms"
```

```
   steady_clock::now()          steady_clock::now()
          │                             │
   ───────●─────────────────────────────●──────────►  time
          │◄─────────── elapsed ───────►│
          start                        (now)

   duration_cast<milliseconds>(elapsed)   → report it in the unit you want
```

**Why `steady_clock` for this?**

```
   steady_clock   - only ever moves forward, at a steady rate.
                    Nothing (NTP sync, daylight saving, the user changing
                    the clock) can make it jump. USE IT to measure elapsed time.

   system_clock   - the wall clock. Maps to real calendar time, but CAN
                    jump when the OS adjusts it. USE IT for dates, not durations.
```

### Sleeping

```cpp
#include <thread>
std::this_thread::sleep_for(20ms);   // pause this thread for a duration
```

### Calendar dates

`system_clock` is the one tied to civil time. Floor a time point to day
precision, then view it as a year/month/day:

```cpp
auto now{std::chrono::system_clock::now()};
auto today{std::chrono::floor<std::chrono::days>(now)};   // drop the time-of-day
std::chrono::year_month_day date{today};

std::println("today is {}", date);              // 2026-09-10
std::println("formatted: {:%Y-%m-%d}", date);   // 2026-09-10  - explicit format
```

`std::print` / `std::println` know how to format both durations and
dates - the `{:%Y-%m-%d}` is a chrono format spec, like `strftime`.

You can also build a specific date and compare or format it:

```cpp
std::chrono::year_month_day deadline{
    std::chrono::year{2025}, std::chrono::month{12}, std::chrono::day{31}};

std::println("deadline: {:%Y-%m-%d}", deadline);
```

---

## 7.13 Maybe a value: `std::optional`

### The problem

A lookup that can fail. What does it return when it finds nothing?

```cpp
int find_index(const std::vector<int>& v, int target);
//  └── return -1 for "not found"? but -1 could be a valid result elsewhere.

std::string find_phone(const Contact& c);
//  └── return "" ? an empty string is not obviously "no phone".
```

Every one of these is a **sentinel**: a special value that has to mean
"nothing here", stolen from the range of normal values, and easy for a
caller to forget to check.

### The fix: a box that is either full or empty

**`std::optional<T>`** holds **either a `T` or nothing at all** - no
sentinel needed.

```cpp
#include <optional>

std::optional<std::string> find_phone(const std::vector<Contact>& book,
                                      std::string_view name) {
    for (const Contact& c : book) {
        if (c.name == name) {
            return c.phone;      // found - wrap the value
        }
    }
    return std::nullopt;         // not found - the empty state
}
```

```
   std::optional<std::string>

   ┌──────────────────┐            ┌──────────────────┐
   │  ● "555-0101"    │    or      │  (empty)         │
   └──────────────────┘            └──────────────────┘
     has_value() == true            has_value() == false
     *opt   → "555-0101"            *opt   → undefined behavior
     opt->size() → 8                std::nullopt
```

### Getting the value out

```cpp
auto phone{find_phone(book, "Ada")};

if (phone.has_value()) {          // or just:  if (phone)
    std::println("{}", *phone);   // * gets the value  (only when non-empty!)
}

std::optional<Contact> c{Contact{"Ada", "555-0101"}};
std::println("{}", c->name);      // -> reaches a member of the contained value
```

The clean one-liner - value if present, fallback if not:

```cpp
std::string p{find_phone(book, "Bjarne").value_or("unknown")};
//                                       └────────┬────────┘
//                             collapses "maybe a string" to a definite string
```

And `.value()`, which is like `*` but **throws** instead of being UB
when empty:

```cpp
std::optional<int> empty{};
try {
    int n{empty.value()};        // throws std::bad_optional_access
} catch (const std::bad_optional_access& ex) {
    std::println("was empty: {}", ex.what());
}
```

```
   *opt            → fast, but UNDEFINED if empty  (check first)
   opt.value()     → throws std::bad_optional_access if empty
   opt.value_or(x) → never fails: the value, or x
```

---

## 7.14 Command-line arguments

### Where they come from

When something launches your program, it can pass it a list of words:

```
   > rooster add 3 4
     ───┬── ─┬─ ┬ ┬
        │    │  │ └── argv[3]  "4"
        │    │  └──── argv[2]  "3"
        │    └─────── argv[1]  "add"
        └──────────── argv[0]  "rooster"  (the program's own name/path)

   argc (the count) = 4
```

`main` has a second form that receives them:

```cpp
int main(int argc, char* argv[]) {
    // argc : how many words (always >= 1 - argv[0] is always there)
    // argv : the words, as C strings (char*)
}
```

### Making them usable

The raw `(count, pointer)` pair is awkward. Wrap it in a **`std::span`**
and it becomes a normal range - `.size()`, indexing, range-`for` all
work:

```cpp
#include <span>

std::span<char*> args{argv, static_cast<std::size_t>(argc)};

for (std::size_t i{0}; i < args.size(); ++i) {
    std::println("argv[{}] = \"{}\"", i, args[i]);
}
```

Then treat each argument as a `std::string_view` to compare it, and
`std::from_chars` (7.8) to turn one into a number:

```cpp
std::string_view op{args[1]};        // "add"

int a{};
std::from_chars(args[2], args[2] + std::string_view{args[2]}.size(), a);

if (op == "add") { /* ... */ }
```

### The usual shape

```
   argv[1]        → a command word   ("add", "list", "--help")
   argv[2..]      → its operands

   if argc is not what you expect:
       print a "usage: rooster <cmd> <args>" line
       return 1            (non-zero = "something went wrong")
```

```cpp
if (argc < 4) {
    std::println("usage: {} <add|sub|mul> <a> <b>", args[0]);
    return 1;
}
```

---

## 7.15 - 7.17 Project: the expense report

Everything in this chapter comes together in one program: it **reads a
CSV file of dated expenses, totals them by category, and prints a bar
chart** - timing each phase with `steady_clock`.

```
   expenses.csv                              rooster (console)
   ────────────                              ─────────────────
   date,category,amount,note                       Housing | ####################   1290.00  (70.2%)
   2025-01-03,Housing,1200.00,rent                    Food | #######                 236.85  (12.9%)
   2025-01-04,Food,42.50,groceries      ──►      Utilities | ###                     104.45  ( 5.7%)
   2025-01-05,Transport,18.75,bus                Transport | ###                      81.50  ( 4.4%)
   ...                                               Other | ##                       80.00  ( 4.4%)
                                             Entertainment | #                        44.99  ( 2.4%)
                                                     TOTAL |                        1837.79

                                             timing:
                                               read file : 17us
                                               parse     : 267us
                                               aggregate : 0us
```

### What it exercises

```
   std::vector<Expense>      the parsed rows
   std::array<double, 6>     a running total per category (indexed by the enum)
   std::string / string_view splitting each line into fields
   <charconv> from_chars     "42.50" → 42.50 ,  and the "2025-01-03" date parts
   enum class Category       Food, Transport, Housing, ...
   std::optional<Expense>    a line that fails to parse → std::nullopt
   std::ranges::sort         order the category totals, biggest first
   std::accumulate           the grand total for the percentages
   <chrono> steady_clock     time each phase
   argv                      the input filename (defaults to expenses.csv)
```

### What stays fixed, and what changes

```
   ┌─────────────────────────────────────────────────────────────┐
   │  report.h / report.cpp    ← IDENTICAL in all three folders   │
   │                                                             │
   │    struct Expense                    enum class Category     │
   │    make_expense(fields...)  →  builds & validates an Expense │
   │    totals_by_category(...)  →  the aggregation               │
   │    print_bar_chart(...)     →  the output                    │
   └─────────────────────────────────────────────────────────────┘
                              ▲
        the ONLY thing that differs between 7.15 / 7.16 / 7.17:
        how the CSV file becomes a std::vector<Expense>

   7.15  hand-rolled      split each line ourselves, string_view + find + substr
   7.16  vendored csv2    the csv2 library, headers committed under vendor/
   7.17  FetchContent     the same csv2, cloned by CMake at configure time
```

This is the same structure as chapter 6's image writer (PPM by hand →
vendored `stb` → fetched `stb`). The lesson is about **dependencies**,
not about CSV.

### 7.15 - hand-rolled, no dependency

`parse_expense_line` in `report.cpp` walks the commas itself:

```cpp
std::array<std::string_view, 4> fields{};
std::size_t start{0};
// find each ',', slice the piece before it with substr, move past it
```

then hands the four field views to `make_expense`. Our CSV is regular -
no quoted fields, no embedded commas - so this is a dozen lines.

```cmake
add_executable(rooster main.cpp report.cpp report.h)
```

### 7.16 - a vendored library (`csv2`)

Real-world CSV has quoting, whitespace trimming, and header-row rules
you would rather not re-implement. **`csv2`** (by Vince Mi, MIT licensed,
header-only) handles the tokenising. Here we **vendor** it - the headers
are committed into our own repo:

```
   7.16ProjectExpenseReportVendored/
   ├── vendor/
   │   ├── csv2/  reader.hpp  mio.hpp  parameters.hpp  writer.hpp
   │   ├── LICENSE
   │   └── LICENSE.mio
   ├── csv_loader.h / csv_loader.cpp   ← the ONLY new code vs. 7.15
   ├── report.h / report.cpp           ← byte-for-byte identical to 7.15
   ├── main.cpp
   └── expenses.csv
```

`csv_loader.cpp` reads the file with the library and finishes by calling
the **same `make_expense`** the hand-rolled version ends on:

```cpp
csv2::Reader<...> reader;
reader.mmap(path);
for (const auto row : reader) {
    for (const auto cell : row) {
        cell.read_value(field);        // csv2 does the unquoting/trimming
    }
    make_expense(fields[0], fields[1], fields[2], fields[3]);   // our code again
}
```

```cmake
add_executable(rooster main.cpp csv_loader.cpp csv_loader.h report.cpp report.h)

target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor)     # so #include <csv2/reader.hpp> resolves
```

```
   SYSTEM   → treat vendor/ as third-party: -Wall / -Wextra stay quiet about csv2's code
   no link  → csv2 is header-only. It compiles INSIDE our build, with our compiler
              and flags. There is no prebuilt .lib/.dll, so an ABI mismatch is
              impossible - the class of linker error that comes from mixing
              toolchains simply cannot happen here.
```

### 7.17 - fetched by CMake

The C++ is **identical to 7.16** - `csv_loader.*`, `report.*`, `main.cpp`
all unchanged. csv2 is no longer in our repo; CMake clones it when you
configure:

```cmake
include(FetchContent)
FetchContent_Declare(csv2
    GIT_REPOSITORY https://github.com/p-ranav/csv2.git
    GIT_TAG        4f3c41db6457465e94b92b91fc560b911c16a16a   # an exact commit, not a branch
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(csv2)
target_link_libraries(rooster PRIVATE csv2)   # csv2 is an INTERFACE target: this just
                                              # adds its include path
```

```
   cmake -S . -B build
        │
        ▼
   FetchContent_MakeAvailable(csv2)
        │   git clone --depth 1 https://github.com/p-ranav/csv2.git
        │   git checkout 4f3c41d...
        ▼
   build/_deps/csv2-src/        ← headers now on disk
        │
        ▼
   the `csv2` target carries build/_deps/csv2-src/include on its include path
        │
        ▼
   normal build: csv_loader.cpp #includes <csv2/reader.hpp> and compiles it
```

- **`GIT_TAG` is a commit hash, not a branch name.** A branch would mean
  "whatever it points at on the day you build" - the build stops being
  reproducible. Pin it.
- csv2 is header-only, so there is no build step - `MakeAvailable` just
  puts the files on disk. It is still compiled *in our build*, so the
  no-ABI-mismatch guarantee from 7.16 still holds.
- The clone happens **once**, into `build/_deps/`. The first configure
  needs network and `git`; 7.16 builds offline forever.

### The three side by side

```
                     7.15 hand-rolled   7.16 vendored        7.17 FetchContent
   ────────────────  ────────────────   ──────────────────   ──────────────────
   CSV parsing       our own code       csv2 library         csv2 library
   library in repo   —                  yes, under vendor/   no, cloned to build/
   how it arrives    —                  git add (committed)  CMake, at configure
   offline build     yes                yes                  first build needs net
   reproducible      yes                yes (files frozen)   yes (commit pinned)
   compiled here?    —                  yes → no ABI risk    yes → no ABI risk
   report.h/.cpp     ───────────  identical in all three  ───────────
```

---

## 7.18 Assignment

One small program - a terminal **temperature-log tool** over a fixed
list of `"YYYY-MM-DD,LABEL,VALUE"` records - built in seven steps.
`main.cpp` has the seven stubbed exercises, each with its problem
statement and a sample run in a comment; `main_solution.cpp` solves all
seven with the statements repeated above each solution. Built as two
executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | station list | `std::array<std::string_view, N>`, range-`for` with an init-statement |
| 2 | `parse_value()` | `using` type alias, `std::optional`, `std::from_chars` (no exceptions) |
| 3 | `parse_record()` | `std::string_view` `find` / `substr` splitting, a `struct`, `std::optional` |
| 4 | summary stats | `std::ranges::min_element` / `max_element`, `std::accumulate` |
| 5 | `Station` enum | `enum class : std::uint8_t`, `using enum` in a `switch` |
| 6 | sort by value | `std::ranges::sort` with a comparison lambda |
| 7 | record dates | `std::chrono::year_month_day`, `std::from_chars` on the parts, `{:%Y-%m-%d}` and weekday formatting |

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole
chapter.

After this chapter the student can hold and process collections of data,
handle text properly, work with time, and model "maybe a value" - and is
ready for pointers, then classes.
