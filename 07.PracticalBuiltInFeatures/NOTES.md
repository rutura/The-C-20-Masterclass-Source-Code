# Practical Built-In Features

Every program so far has worked on a handful of loose variables. Real data
often comes in **collections** - a list of scores, a column from a spreadsheet, a
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
functional-style ranges/views pipeline, strings beyond what we have seen so far.
Things like the `std::format` spec grammar, non-owning views into text,
`std::chrono` for durations/clocks/calendar dates, files revisited with
formatted input, reading structured data, and pattern matching with regular
expressions. It closes with a small project that puts all of it to work
on a real dataset - the Titanic passenger manifest.

---

## 7.2 `std::array`

**`std::array<T, N>`** is a **fixed-size** sequence of `N` values of type
`T`, stored **inline** - the elements sit directly inside the `array`
object (not heap allocated), back to back, no separate heap allocation 
(we'll understand what this means later on). `N` is part of the
type: `std::array<int, 5>` and `std::array<int, 10>` are different types,
the same way `int` and `double` are different types.

```cpp
std::array<int, 5> scores{};   // {} zero-initializes every element
```

```
   std::array<int, 5> scores{};

   index:    0     1     2     3     4
           ┌─────┬─────┬─────┬─────┬─────┐
   scores: │  0  │  0  │  0  │  0  │  0  │      one block, 5 ints,
           └─────┴─────┴─────┴─────┴─────┘      sitting right here
            ▲                             ▲
        scores[0]                    scores[4]
                      size() == 5, fixed forever
```

### Access: `[]` vs `.at()`

`scores[i]` is **unchecked** - fast, but an out-of-range `i` is undefined
behavior: the program might crash, or might silently read whatever
garbage happens to sit past the array in memory. `scores.at(i)` is the
same idea, **bounds-checked**: an out-of-range index throws
`std::out_of_range` instead of reading garbage.

```
   scores[i]              i in range        →  reads scores[i], no check
                           i out of range    →  UNDEFINED BEHAVIOR (danger)

   scores.at(i)            i in range        →  reads scores[i]
                           i out of range    →  throws std::out_of_range
```

```cpp
scores.at(10);   // 5-element array - out of range
```

```
   scores.at(10)   on a 5-element array (valid indices 0..4)
        │
        ▼
   throws std::out_of_range   ("array::at: __n (which is 10) >= _Nm (which is 5)")
```

### CTAD: skip the `<T, N>`

In plain terms: normally you have to tell `std::array` two things up
front - what type it holds and how many elements it has
(`std::array<int, 5>`). CTAD (Class Template Argument Deduction) 
means the compiler can often **figure both of those out by itself**, 
just by looking at what you put in the braces
- so you get to skip typing them.

`std::array` is a **class template** - a blueprint that needs some
**arguments** filled in (`T` and `N`) before it becomes a real type. CTAD
is the compiler's ability to **deduce** those arguments on its own,
instead of requiring you to write them by hand every time.

```cpp
std::array highScores{32, 27, 64, 18, 95};   // inferred: array<int, 5>
```

**Class template argument deduction (CTAD)** reads the braced initializer
and infers both the element type and the count for you:

```
   std::array highScores{32, 27, 64, 18, 95};
                          └──────────┬──────────┘
                          5 ints in the braces
                                     │
                                     ▼
                     compiler infers: std::array<int, 5>
```

### Range-based for: reference vs. const reference

```cpp
for (const int& score : highScores) { /* read-only */ }
for (int& score : highScores)       { score *= 2; }   // modifies in place
```

```
   const int& score : highScores        int& score : highScores
   ──────────────────────────           ──────────────────────
   score is a READ-ONLY alias           score is a WRITABLE alias
   for each element in turn             for each element in turn

   highScores: 32  27  64  18  95       highScores: 32  27  64  18  95
                │                                     │
                └─ score "looks at"                   └─ score *= 2 writes
                   each one, cannot                      straight back into
                   change it                             the array
                                                    →   64  54 128  36 190
```

The C++20 `for (init; cond; range)` form lets a loop declare its own
accumulator right where it is used, instead of one line above the loop:

```cpp
for (int total{0}; const int& score : highScores) {
    total += score;
}
```

```
   score:    32    27    64    18    95
   total:     0 → 32 → 59 → 123 → 141 → 236     (running total, traced step by step)
```

---

## 7.3 `std::vector`

**`std::vector<T>`** is the growable counterpart to `std::array`: its
elements live on the **heap**, and it can grow or shrink at run time.
Where `std::array`'s size is baked into its type, `std::vector` is the
default choice whenever you do not know the count up front, or need to
add to it later.

```
   std::array<int, 5>                    std::vector<int>
   ───────────────────                   ────────────────
   size fixed at compile time            size can change at run time
   elements stored inline                elements stored on the heap
   N is part of the type                 no size in the type at all
   cannot grow                           push_back() grows it
```

### `(7)` vs. `{7}` - a common first mistake

```cpp
std::vector<int> readings(7);    // 7 elements, each value-initialized to 0
std::vector<int> other{7};       // ONE element, valued 7
```

```
   readings(7)   →  ┌───┬───┬───┬───┬───┬───┬───┐
                    │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │     SEVEN elements
                    └───┴───┴───┴───┴───┴───┴───┘     (7) sizes the vector

   other{7}      →  ┌───┐
                    │ 7 │                              ONE element
                    └───┘                              {7} is the element list
```

Parentheses `()` size the vector; braces `{}` list its elements. The two
look almost identical and mean very different things - worth a second
look every time.

### Comparing, copying, assigning

```cpp
std::vector<int> a(5), b(5);
a == b;                 // element-by-element comparison, like std::array
std::vector c{a};       // copy constructor - c owns its own copy of a's data
a = b;                  // assignment - a's old contents are replaced
```

```
   std::vector c{a};

   a: ┌───┬───┬───┬───┬───┐         c: ┌───┬───┬───┬───┬───┐
      │ 0 │ 0 │ 0 │ 0 │ 0 │            │ 0 │ 0 │ 0 │ 0 │ 0 │
      └───┴───┴───┴───┴───┘            └───┴───┴───┴───┴───┘
        own block of memory              a SEPARATE block - c's own copy
        changing a later does NOT touch c, and vice versa
```

### Growing: `push_back`

```cpp
readings.push_back(1000);   // appends one element, resizing as needed
```

```
   before:  ┌───┬───┬───┬───┬───┬───┬───┐             size() == 7
            │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │
            └───┴───┴───┴───┴───┴───┴───┘

   readings.push_back(1000);

   after:   ┌───┬───┬───┬───┬───┬───┬───┬──────┐      size() == 8
            │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 1000 │
            └───┴───┴───┴───┴───┴───┴───┴──────┘
```

This is the one thing `std::array` fundamentally cannot do - its size is
fixed at compile time, while `push_back` grows a `vector` on demand.

### `.at()` still bounds-checks

```cpp
try {
    readings.at(15);   // out of range - readings only has 8 elements
}
catch (const std::out_of_range& ex) {
    std::println("An exception occurred: {}", ex.what());
}
```

```
   readings.at(15)  on an 8-element vector
        │
        ▼
   throws std::out_of_range  ──►  caught by catch  ──►  ex.what() printed
                                   (program keeps running, does not crash)
```

---

## 7.4 Sorting, searching, and `accumulate`

### Two ways to tell the computer what to do

Every loop written so far in this course has been **procedural**: line
by line, it spells out *how* to get the answer - set up a running
variable, loop, update it, repeat.

```cpp
int total{0};
for (const int& item : quantities) {   // HOW: loop, add, repeat
    total += item;
}
```

That works, but every line is a place a mistake can hide - the wrong
starting value, the wrong operator, a loop bound off by one. This
lecture and the next introduce **declarative** tools - `accumulate`,
`filter`, `transform` - where you instead state *what* you want and let
the library supply the *how*:

```
   PROCEDURAL: you write the HOW              DECLARATIVE: you state the WHAT
   ──────────────────────────────             ────────────────────────────────
   int total{0};                              std::accumulate(quantities.begin(),
   for (const int& item : quantities) {                       quantities.end(), 0)
       total += item;
   }                                          "reduce quantities to one value,
                                               starting from 0" - the library
   loop, running variable, += ...             owns the loop, you just say what
```

Under the hood, each declarative tool still hides a loop somewhere -
this is called **internal iteration**, because the loop runs *inside*
the library function instead of in code you wrote and can see. What
changes is who supplies the small per-element decision: a **higher-order
function** is a function that takes another function as an argument (or
returns one), and `accumulate`, `filter`, and `transform` are all
higher-order functions - you hand each one a small function (often a
lambda) saying what to do with one element, and it owns the looping.

```
   WHAT you state                       WHO supplies the loop
   ───────────────                      ─────────────────────
   accumulate(..., combine)             accumulate's internal iteration
   filter(keep_if)                      the view's internal iteration (7.5)
   transform(map_to)                    the view's internal iteration (7.5)
```

This is C++'s **functional-style** programming: not a different
language, just a different default - reach for a declarative pipeline
first, and drop back down to a hand-written loop only when a pipeline
cannot say what you mean. The rest of this lecture and the next show
what that looks like in practice, starting with sorting and searching.

### Sorting with `std::ranges::sort`

```cpp
std::array fruits{"mango"s, "kiwi"s, "fig"s, "date"s, "apple"s};
std::ranges::sort(fruits);   // ascending, in place
```

```
   before sort:  mango  kiwi  fig  date  apple
                   │      │    │    │      │
                   └──────┴────┴────┴──────┘
                        std::ranges::sort(fruits)
                   ┌──────┬────┬────┬──────┐
                   ▼      ▼    ▼    ▼      ▼
   after sort:   apple  date  fig  kiwi  mango
```

### Searching sorted data with `std::ranges::binary_search`

`binary_search` repeatedly **halves** the search range - which only gives
a correct answer when the data is already sorted.

```
   searching sorted {apple, date, fig, kiwi, mango} for "kiwi"

   step 1:  apple  date  [fig]  kiwi  mango     middle = fig, "kiwi" > "fig" → search right half
   step 2:  ......  kiwi  mango                 middle = kiwi, MATCH → true

   only 2 comparisons instead of checking all 5, one by one
```

```cpp
std::ranges::binary_search(fruits, "kiwi"s);   // true
std::ranges::binary_search(fruits, "guava"s);  // false
```

That halving is the trade a sort buys you: `O(log n)` lookups instead of
scanning every element - but only correct on **already-sorted** data.
Run `binary_search` on unsorted data and it can wrongly report "not
found" even when the value is there.

### Folding a range into one value with `std::accumulate`

`std::accumulate(first, last, init)` is the declarative tool from the
opening of this lecture, applied to "reduce a range to one value": state
*what* you want (start from `init`, combine every element) and let the
library own the loop.

```cpp
std::accumulate(quantities.begin(), quantities.end(), 0);   // sum, starting from 0
```

Traced on `quantities = {10, 20, 30, 40}`:

```
   step         acc + element        acc afterward
   ────         ─────────────        ─────────────
   start        (init)                0
   1            0 + 10                10
   2            10 + 20               30
   3            30 + 30               60
   4            60 + 40               100   ◄── final result
```

`accumulate` hides ("internalizes") the loop and the running total from
you. That hidden loop is called **internal iteration** - you never see
the index or the intermediate value, only the final result.

#### Customizing *how* to combine: higher-order functions

By default `accumulate`'s "combine" step is `+`. A fourth argument - a
**function you pass to another function** - overrides it. A function that
takes another function as an argument (or returns one) is called a
**higher-order function**; `accumulate` is one.

```cpp
int multiply(int x, int y) { return x * y; }

std::accumulate(factors.begin(), factors.end(), 1, multiply);   // product

std::accumulate(factors.begin(), factors.end(), 1,
                 [](int x, int y) { return x * y; });           // same, inline lambda
```

```
   accumulate(begin, end, 1, multiply)   on factors = {1, 2, 3, 4, 5}

   step        combine(acc, element)      acc afterward
   ────        ─────────────────────      ─────────────
   1           multiply(1, 1)     = 1     1
   2           multiply(1, 2)     = 2     2
   3           multiply(2, 3)     = 6     6
   4           multiply(6, 4)     = 24    24
   5           multiply(24, 5)    = 120   120   ◄── final result
```

A **lambda** - the unnamed, inline function from earlier in the course -
is what you reach for when the combining step is only used once, right
here, and does not deserve a separate top-level name like `multiply`
does. Nothing about `accumulate` changes; only *how it combines* does.

Passing behavior around like this is also why these tools favor
**immutability**: `quantities` and `factors` are never modified by any of
this - `accumulate` reads them and hands back a brand new value, so there
is no shared running variable for two different pieces of code to step on
by mistake.

---

## 7.5 Ranges and views

Section 7.4 hid one loop inside `accumulate`. C++20's **ranges library**
(`<ranges>`) goes further and gives you two more declarative building
blocks - **filter** (keep only what matches) and **transform** (map each
value to a new one) - that chain together instead of nesting loops inside
loops.

```
   the procedural way: nested loops, one running vector per step

   std::vector<int> evens{};
   for (int x : numbers) {
       if (x % 2 == 0) evens.push_back(x);          // filter, by hand
   }
   std::vector<int> squares{};
   for (int x : evens) {
       squares.push_back(x * x);                     // transform, by hand
   }

   the declarative way: state what, chain it, let the library iterate

   numbers | std::views::filter(even) | std::views::transform(square)
```

### A view does not build a container - it wraps one, lazily

```cpp
auto counted{std::views::iota(1, 11)};   // the integers 1..10, generated lazily
```

```
   std::views::iota(1, 11)

   NOT this (eager - builds the whole thing up front):
      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
      │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 10 │    a real std::vector<int>
      └───┴───┴───┴───┴───┴───┴───┴───┴───┴────┘

   THIS (lazy - a tiny object that knows the RULE):
      counted = "start at 1, stop before 11, +1 each step"
                 no elements exist yet - they are generated as you iterate
```

### Piping views together

`std::views::filter` and `std::views::transform` wrap a range the same
way, and chain together with `|`, read left to right like a pipeline.
Like `accumulate`'s fourth argument, each one is a **higher-order
function**: `filter` takes a lambda that decides *keep or drop*,
`transform` takes a lambda that decides *old value or new value* - you
supply the small decision, the view supplies the iteration.

```cpp
auto evenSquares{
    counted | std::views::filter([](int x) { return x % 2 == 0; })
            | std::views::transform([](int x) { return x * x; })};
```

```
   counted ──filter(even)──► evens ──transform(square)──► evenSquares

    1  2  3  4  5  6  7  8  9  10
       │     │     │     │     │
       ▼     ▼     ▼     ▼     ▼
       2     4     6     8     10          (filter kept only these)
       │     │     │     │     │
       ▼     ▼     ▼     ▼     ▼
       4    16    36    64    100          (transform squared each one)
```

### Laziness: nothing runs until you actually iterate

```
   auto evenSquares{ counted | filter(...) | transform(...) };
        │
        └─  at THIS line: nothing has been filtered, nothing squared -
            evenSquares is just a recipe wrapping counted

   for (int x : evenSquares) { ... }
        │
        └─  NOW, one element at a time, as the loop asks for the next
            value: pull from counted → test filter → apply transform
```

`evenSquares` is only ever iterated by something that asks for values -
a range-based for, `std::accumulate`, or copying it into a
`std::vector`. The same pipeline works over a real container, not just a
generated sequence like `iota`:

```cpp
numbers | std::views::filter(...) | std::views::transform(...)
```

`filter` and `transform` are exactly the "declarative, higher-order,
internal iteration" pattern this lecture opened with in 7.4 - `accumulate`
folds a range down to one value, `filter`/`transform` reshape a range
into a new one, and all three let you state *what* instead of *how*.

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

```
   before:  first = "one"     second = "two"

   first.swap(second);

   after:   first = "two"     second = "one"
            (the underlying character buffers trade places - no
             character is copied to do it)
```

### `substr`: pull out a piece

```cpp
filename.substr(0, 6);   // "report_final.pdf" -> "report"
```

```
   filename:  r  e  p  o  r  t  _  f  i  n  a  l  .  p  d  f
   index:     0  1  2  3  4  5  6  7  8  9  ...

   substr(0, 6)
          │  └── take 6 characters
          └───── starting at index 0

   result:    r  e  p  o  r  t              "report"
```

### The `find` family: locate things inside a string

```cpp
log.find("is");                    // first occurrence, from the front
log.rfind("is");                   // last occurrence, from the back
log.find_first_not_of("noon is "); // first character NOT in this set
```

```
   log:  n  o  o  n     i  s     1  2  p  m  ;     m  i  d  n  i  g  h  t     i  s     n  o  t
   idx:  0  1  2  3  4  5  6  7  8  9  10 ...                              23 24            ...

   log.find("is")     →  5     (first "is": "noon [is] 12pm...")
   log.rfind("is")    →  23    (last "is": "...midnight [is] not")
```

Every `find`-family function returns **`std::string::npos`** when nothing
matches:

```
   log.find("xyz")
        │
        ▼
   std::string::npos   ("not found" sentinel - always check before using
                         the result as an index, or a bug hides silently)
```

### `erase` / `replace`: edit in place

```cpp
sentence.erase(19);                          // drop everything from index 19 on
sentence.replace(position, 1, "_");          // 1 char at position -> "_"
```

```
   sentence:  The quick brown fox jumps over the lazy dog
   index:     0         1         2         3
              0123456789012345678901234567890...
                                ▲
                               19

   sentence.erase(19);
                │
                ▼
   sentence:  The quick brown fox        (everything from index 19 on: GONE)
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

```
   "The quick brown fox"
       ▲
       find(' ') = 3 ──replace──► "The_quick brown fox"
                                       ▲
                          find(' ', 4) = 9 ──replace──► "The_quick_brown fox"
                                                               ▲
                                                  find(' ', 10) = 15 ──replace──► "The_quick_brown_fox"
                                                                                        ▲
                                                                        find(' ', 16) = npos → loop ends
```

### `insert`: splice text into the middle

```cpp
greeting.insert(7, "World");   // "Hello, !" -> "Hello, World!"
```

```
   greeting:  H  e  l  l  o  ,     !
   index:     0  1  2  3  4  5  6  7
                                ▲
                                7

   greeting.insert(7, "World");
                    │
                    └── everything from index 7 on is pushed right,
                        "World" is spliced in at that gap

   result:    H  e  l  l  o  ,     W  o  r  l  d  !
```

### String streams: build and parse without hand-rolled loops

`std::ostringstream` accumulates pieces of different types into one
string, using the same `<<` `std::cout` uses - just aimed at a string
instead of the console:

```cpp
std::ostringstream receipt;
receipt << "Order #" << 42 << ": " << "coffee" << " - $" << 4.5;
receipt.str();   // the accumulated string
```

```
   std::cout  <<  value   →  value goes to the SCREEN
   receipt    <<  value   →  value goes into receipt's own STRING BUFFER

   receipt << "Order #" << 42 << ": " << "coffee" << " - $" << 4.5;
                  │        │      │         │           │      │
                  └────────┴──────┴─────────┴───────────┴──────┘
                                    │
                                    ▼
   receipt.str()  ==  "Order #42: coffee - $4.5"
```

`std::istringstream` runs the idea backwards - pulling typed values out of
a string the same way `std::cin` pulls them from the keyboard:

```cpp
std::istringstream record{"Ada 3 19.99"};
record >> item >> quantity >> price;
```

```
   record:  "Ada 3 19.99"
             │   │  │
   item  ◄───┘   │  │        item     (std::string)  = "Ada"
   quantity  ◄───┘  │        quantity (int)           = 3
   price  ◄─────────┘        price    (double)        = 19.99

   >> splits on whitespace and converts to each variable's type,
   same as std::cin >> - just reading from a string instead of the keyboard
```

---

## 7.7 String formatting with `std::format`

`std::print`/`std::println` already cover the everyday case - build a
formatted result and send it straight to the console. **`std::format`**
does the same formatting work, but **returns a `std::string`** instead
of printing, for when the text is not going straight to the screen: a
log line, part of a file, a label built up piece by piece.

```
   std::println("Hello, {}!", name);     WRITES to stdout, returns nothing

   std::string s{std::format("Hello, {}!", name)};
                                          BUILDS a std::string, prints nothing
                                          - you decide what happens to it next
```

### The format-spec grammar

Every `{}` can carry a colon-introduced **spec** describing exactly how
to lay out that one argument:

```
   {  :  fill align  width . precision  type  }
      │  │    │        │       │         │
      │  │    │        │       │         └─ how to interpret it: d, f, x, b, ...
      │  │    │        │       └─ digits after '.', or max chars for a string
      │  │    │        └─ minimum field width
      │  │    └─ < left, > right, ^ center
      │  └─ the character used to pad (default: space)
      └─ every spec starts with a colon
```

### Width and alignment

```cpp
std::println("[{:10}]", 42);     // "[        42]"  width 10, default align
std::println("[{:<10}]", 42);    // "[42        ]"  < left
std::println("[{:>10}]", 42);    // "[        42]"  > right (default for numbers)
std::println("[{:^10}]", 42);    // "[    42    ]"  ^ center
std::println("[{:*^10}]", 42);   // "[****42****]"  '*' as fill, centered
```

```
   {:*^10}   on 42

   field:  [ *  *  *  *  4  2  *  *  *  * ]
             └───┬───┘  └┬┘  └────┬──────┘
              fill pad  value   fill pad
                        (centered inside a 10-wide field)
```

### Precision

```cpp
std::println("{:.2f}", 3.14159);   // "3.14" - digits after the decimal
std::println("{:.3}", "abcdefg");  // "abc"  - max characters, for a string
```

### Sign flags and the alternate form

```cpp
std::println("{:+d}  {:+d}", 42, -42);   // "+42  -42" - always show a sign
std::println("{: d}  {: d}", 42, -42);   // " 42  -42" - space reserves +'s column

std::println("{:#x}", 255);   // "0xff"  - hex, alternate form shows the 0x
std::println("{:#o}", 8);     // "010"   - octal, alternate form shows the 0
std::println("{:#b}", 5);     // "0b101" - binary, alternate form shows the 0b
```

```
   {:+d}         {: d}
   ─────         ─────
   42  → "+42"   42  → " 42"     (space reserved where a sign WOULD go)
  -42  → "-42"  -42  → "-42"     (a '-' always prints regardless)
```

### Positional arguments: reuse or reorder

```cpp
std::println("{0} bought {1} for {0}'s {2}.", "Ada", "flowers", "mother");
// "Ada bought flowers for Ada's mother."
```

```
   {0} bought {1} for {0}'s {2}.
    │          │        │    │
    │          │        │    └── args[2] = "mother"
    │          │        └─────── args[0] = "Ada"     (REUSED - same index twice)
    │          └──────────────── args[1] = "flowers"
    └─────────────────────────── args[0] = "Ada"
```

Without positional indices, `{}` always consumes the next argument in
order - positional indices let you reuse one argument twice, or print
them in a different order than they were passed.

### `std::format_to`: write into a buffer instead of allocating fresh

`std::format` allocates a brand-new `std::string` every call.
`std::format_to` writes into somewhere that **already exists**, through
an output iterator - useful for building up one buffer across several
calls without a fresh allocation each time:

```cpp
std::string buffer;
std::format_to(std::back_inserter(buffer), "{}={} ", "width", 400);
std::format_to(std::back_inserter(buffer), "{}={}", "height", 300);
// buffer == "width=400 height=300"
```

```
   buffer:  ""
       │
       format_to(back_inserter(buffer), "{}={} ", "width", 400)
       ▼
   buffer:  "width=400 "
       │
       format_to(back_inserter(buffer), "{}={}", "height", 300)
       ▼
   buffer:  "width=400 height=300"      (appended, not replaced)
```

---

## 7.8 `std::string_view`

A **`std::string_view`** does not own characters - it is a
`(pointer, length)` pair pointing at characters owned by someone else: a
`std::string`, a string literal, or part of either. No allocation, no
copy.

```cpp
std::string color{"red"};
std::string_view colorView{color};   // "sees" color's own characters
```

```
   std::string color{"red"};              (owns its own character buffer)

   color: ┌───┬───┬───┐
          │ r │ e │ d │
          └───┴───┴───┘
            ▲
            │
   std::string_view colorView{color};

   colorView:  { pointer ──────────────┘ , length: 3 }
               (no characters of its own - just POINTS at color's)
```

### A view sees every later change - it has no data of its own to go stale

```cpp
color.at(0) = 'R';
// colorView now reads "Red" too - it has no data of its own to be stale
```

```
   color.at(0) = 'R';

   color: ┌───┬───┬───┐
          │ R │ e │ d │        ← color's own buffer changed
          └───┴───┴───┘
            ▲
            │
   colorView still points HERE  →  colorView now reads "Red"

   compare with std::string colorCopy{color}; (a REAL copy, made earlier):
   colorCopy has its OWN buffer - color.at(0) = 'R' does not touch it
```

### `remove_prefix`/`remove_suffix`: move the window, touch nothing

```cpp
colorView.remove_prefix(1);
colorView.remove_suffix(1);
```

```
   colorView over "Red":     R  e  d
                             ▲        ▲
                          start      end

   remove_prefix(1)  →         e  d
                                ▲     ▲
                             start   end     (window shrinks from the front)

   remove_suffix(1)  →         e
                                ▲  ▲
                             start end       (window shrinks from the back)

   "Red" itself is never touched - only colorView's own (pointer, length)
   moved, in O(1), no characters copied or erased
```

A `string_view` can wrap a plain literal with no `std::string` created at
all, and supports the same `find`/`starts_with`/iteration you would
expect:

```
   std::string_view label{"C++ course"};   // no std::string exists anywhere
                            └──────┬─────┘
                       label points directly at the
                       literal's own storage
```

Prefer it for a function parameter that only **reads** text and does not
need to keep it around - it avoids a copy the caller never asked for:

```
   void describe(const std::string& s)      COPIES only if the caller
                                             passes something that needs
                                             converting to std::string

   void describe(std::string_view s)        NEVER copies - works directly
                                             on a std::string, a literal,
                                             or a slice of either
```

---

## 7.9 `std::chrono`

Time shows up everywhere in real programs - how long an operation took,
what the timestamp on a log line should read, what today's date is.
**`<chrono>`** is the standard library's time toolkit: **durations**
(an amount of time), **clocks** (a source of "now"), and, since C++20,
genuine **calendar dates**.

### Durations: an amount of time, with the unit baked into the type

```cpp
std::chrono::seconds fiveSeconds{5};
std::chrono::milliseconds fiveThousandMs{5000};
```

```
   std::chrono::duration<Rep, Period>
                  │        │
                  │        └── the tick length: what ONE tick means
                  │             (seconds, milliseconds, minutes, ...)
                  └─────────── the number of ticks (a plain integer or double)

   seconds{5}         ==  5 ticks, each tick = 1 second
   milliseconds{5000} ==  5000 ticks, each tick = 1 millisecond
                            │
                            both represent the SAME amount of time,
                            just counted in different-sized units
```

Different duration *types* holding the same amount of time still compare
equal - the library converts for you:

```cpp
fiveSeconds == fiveThousandMs;   // true
```

`duration_cast<T>` converts explicitly between duration types, the same
spirit as `static_cast` - going from a smaller unit to a bigger one can
lose information (leftover milliseconds do not fit in whole seconds), so
it is never implicit:

```cpp
auto raceDuration{90min + 32s};                    // chrono_literals: 90 minutes, 32 seconds
std::chrono::duration_cast<std::chrono::seconds>(raceDuration).count();  // 5432
```

```
   90min + 32s
      │      │
      │      └── 32 seconds
      └───────── 90 minutes  =  5400 seconds
                                   │
                              5400 + 32  =  5432 seconds total
```

### Benchmarking a block of code with `steady_clock`

```cpp
const auto start{std::chrono::steady_clock::now()};
// ... the work being timed ...
const auto end{std::chrono::steady_clock::now()};

const auto elapsed{std::chrono::duration_cast<std::chrono::milliseconds>(end - start)};
```

```
   timeline:   start ────────────── work happens ────────────── end
                 │                                                │
                 └──────────────────  elapsed = end - start ──────┘
                                       (a duration, not a time_point)

   steady_clock NEVER goes backward - it is not tied to the wall clock,
   so a system-clock adjustment (NTP sync, a user changing the time)
   cannot make elapsed come out negative. Use it whenever you are
   MEASURING elapsed time, never system_clock.
```

### Wall-clock time with `system_clock`

```cpp
const auto now{std::chrono::system_clock::now()};   // a time_point
```

```
   steady_clock::now()     answers "how much time has passed?"
                            - use for benchmarking / timeouts

   system_clock::now()     answers "what time is it right now?"
                            - use for timestamps / logging
                            - CAN jump (clock sync, user changes it) -
                              never use it to measure elapsed time
```

`std::format` understands a `time_point` directly, using the same
`{:...}` spec grammar from 7.7 - `%` codes take the place of a type
letter like `f` or `d`:

```cpp
std::println("Right now: {:%Y-%m-%d %H:%M:%S}", now);
// "Right now: 2026-09-11 06:49:25"
```

```
   {:%Y-%m-%d %H:%M:%S}
      │  │  │   │  │  │
      │  │  │   │  │  └── seconds
      │  │  │   │  └───── minutes
      │  │  │   └──────── hours (24-hour)
      │  │  └──────────── day of month
      │  └─────────────── month
      └────────────────── year
```

A raw `time_point` carries sub-second precision (down to nanoseconds on
most systems) - `time_point_cast<seconds>(now)` rounds it down to whole
seconds first, so the printed time stays readable instead of trailing
nine digits of fractional noise.

### C++20 calendar dates: `year_month_day`

A `time_point` is a point on an abstract timeline; **`year_month_day`**
is a genuine **calendar date** - built from chrono's own `year`, `month`,
and `day` building blocks:

```cpp
const std::chrono::year_month_day releaseDate{
    std::chrono::year{2020}, std::chrono::month{9}, std::chrono::day{15}};

std::println("C++20 was published around: {:%B %d, %Y}", releaseDate);
// "C++20 was published around: September 15, 2020"
```

```
   year_month_day{ year{2020}, month{9}, day{15} }
                       │            │        │
                       2020         September 15th

   {:%B %d, %Y}  formats it as  "September 15, 2020"
        │
        %B = full month name (vs. %m for the numeric month, "09")
```

Going from a `time_point` to a calendar date needs one more step -
**`floor<days>`** truncates the `time_point` down to midnight, since a
`time_point` alone carries no notion of "which calendar day" until it is
rounded to that granularity:

```cpp
const std::chrono::year_month_day today{
    std::chrono::floor<std::chrono::days>(now)};
```

```
   now (a time_point, includes hours/minutes/seconds/...)
       │
       floor<days>(now)   ──►  truncates to midnight of that day
       │
       year_month_day{...}  ──►  a genuine calendar date: today
```

Calendar arithmetic in whole days works directly on the floored value -
no hand-rolled "how many days in this month" logic required:

```cpp
const std::chrono::year_month_day nextWeek{
    std::chrono::floor<std::chrono::days>(now) + std::chrono::days{7}};
```

```
   floor<days>(now)  +  days{7}
          │                │
       today's           add 7        →  year_month_day{...}  = one week
       midnight          whole days       from today, correct across a
                                           month or year boundary
```

---

## 7.10 Files revisited

Chapter 5 wrote and read plain lines of text with `std::getline` - one
whole line, one `std::string`. A file can hold several **fields per
line** instead - the same `<<`/`>>` you already know from
`std::cout`/`std::cin`, aimed at a file stream.

```
   chapter 5:  ONE field per line               this lecture: SEVERAL fields per line

   names.txt:                                   accounts.txt:
     Ada                                          100 Jones 24.98
     Alan                                         200 Doe 345.67
     Grace                                        300 White 0.0

   read with:  std::getline(in, name)            read with:  in >> account >> name >> balance
              (one std::string per read)                     (three typed reads per record)
```

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

```
   accounts.txt:   100 Jones 24.98
                    │    │     │
   in >> number ◄───┘    │     │      number  (int)         = 100
   in >> name   ◄─────────┘     │      name    (std::string) = "Jones"
   in >> balance ◄──────────────┘      balance (double)      = 24.98
```

`>>` splits on whitespace and converts to each variable's type as it
reads - three reads per record, instead of `getline`'s one string per
line. The stream itself turns false once there is nothing left to read,
so the `while` loop runs once per complete record - the same shape as
chapter 5's `while (std::getline(in, name))`:

```
   while (in >> number >> name >> balance) {
       ...
   }
        │
        └── the whole expression (in >> number >> name >> balance)
            evaluates to the stream itself, which tests true while
            reads keep succeeding, false once the file runs out
```

---

## 7.11 Reading CSV data

A CSV file's quoting and embedded-comma rules are easy to get subtly
wrong with hand-rolled `stringstream` splitting:

```
   what a naive split-on-comma gets WRONG:

   100,"Smith, Jr.",24.98
        └────┬────┘
        one field, but it CONTAINS a comma inside quotes -
        a naive split(',') would wrongly cut it into two fields
```

**`rapidcsv`** is a small, header-only library that already solved that -
it is **vendored** into this project (the same pattern as
`6.17ProjectVendoredHeader`): the header sits in `vendor/`, committed
alongside our own code, nothing downloaded.

```
   7.11ReadingCSV/
   ├── vendor/
   │   └── rapidcsv.h          ← third-party, committed, nothing downloaded
   ├── accounts.csv
   ├── main.cpp                ← #include "rapidcsv.h"
   └── CMakeLists.txt
```

```cpp
#include "rapidcsv.h"

rapidcsv::Document document{"accounts.csv"};   // loads and parses on construction

std::vector<int> accounts{document.GetColumn<int>("account")};
std::vector<std::string> names{document.GetColumn<std::string>("name")};
std::vector<double> balances{document.GetColumn<double>("balance")};
```

```
   accounts.csv:
   account,name,balance
   100,Jones,24.98
   200,Doe,345.67
   300,White,0.0

   GetColumn<int>("account")     →  std::vector<int>{100, 200, 300}
   GetColumn<std::string>("name")→  std::vector<std::string>{"Jones", "Doe", "White"}
   GetColumn<double>("balance")  →  std::vector<double>{24.98, 345.67, 0.0}

   the header row NAMES each column - GetColumn<T>("name") looks it up
   by that name and converts every cell in it to T
```

Being header-only, `rapidcsv.h` needs no separate implementation file to
compile, unlike `stb_image_write.h` in chapter 6 - just the include path
pointed at `vendor/`:

```cmake
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
```

---

## 7.12 Regex

A **regular expression** describes the *shape* of text, not literal
characters - "a capital letter, then one or more lowercase letters", not
one specific word.

```cpp
std::regex properName{"[A-Z][a-z]+"};
std::regex_match("Wally", properName);   // true  - the WHOLE string fits
std::regex_match("E", properName);       // false - no lowercase letters follow
```

```
   pattern:  [A-Z]     [a-z]+
             one       one or more
             CAPITAL   lowercase letters
             letter

   "Wally"   W  a  l  l  y
             ▲  └──┬──┘
          [A-Z]  [a-z]+ (4 lowercase letters, "one or more" satisfied)
                                                    → MATCH, true

   "E"       E
             ▲
          [A-Z] matches, but nothing is left for [a-z]+ to match
          (it needs AT LEAST one)                 → NO MATCH, false
```

`regex_match` requires the **entire** string to satisfy the pattern.
`regex_search` looks for a match **anywhere** inside it, and can capture
what it found in a `std::smatch`:

```
   regex_match("Programming is fun", regex{"fun"})    → false
                                                          (the WHOLE string
                                                           is not just "fun")

   regex_search("Programming is fun", regex{"fun"})   → true
                                                          (found "fun"
                                                           SOMEWHERE inside)
```

```cpp
std::smatch match;
while (std::regex_search(contact, match, phoneNumber)) {
    std::println("{}", match.str());
    contact = match.suffix();   // keep searching after this match
}
```

```
   contact: "Ada Lovelace, Home: 555-555-1234, Work: 555-555-4321"

   search 1:  finds "555-555-1234"
              match.suffix() = ", Work: 555-555-4321"   ← everything AFTER the match

   contact = match.suffix();

   search 2 (on the new, shorter contact):  finds "555-555-4321"
              match.suffix() = ""

   search 3:  nothing left to find → loop ends
```

`regex_replace` rewrites every match in a **copy** of the string, leaving
the original untouched:

```cpp
std::regex_replace(data, std::regex{"\t"}, ",");   // tabs -> commas
```

```
   data:                "1\t2\t3\t4"        (unchanged after the call)
   regex_replace result: "1,2,3,4"          (a brand new string)
```

Common building blocks:

| Pattern piece | Means                          |
|----------------|--------------------------------|
| `\d`           | a single digit                 |
| `[A-Z]`        | one uppercase letter (a range) |
| `[a-z]`        | one lowercase letter (a range) |
| `{n}`          | exactly `n` occurrences        |
| `{n,}`         | `n` or more occurrences        |
| `{n,m}`        | between `n` and `m`, inclusive |

---

## 7.13 Project: Titanic dataset analysis

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

### Missing data: filtering out `NaN` before it corrupts a statistic

Some `age` values are unparseable (`"?"` in the raw file).
`rapidcsv::ConverterParams{true}` turns those into `NaN` instead of
throwing, and a `std::views::filter` drops them before any statistic is
computed - the same lazy-view idea from 7.5, now filtering out bad data
instead of picking out even numbers.

```cpp
auto knownAges{age | std::views::filter([](double a) { return !std::isnan(a); })};
std::vector<double> cleanAges{knownAges.begin(), knownAges.end()};
```

```
   age column (raw):    29   0.9   NaN    2    30   NaN   25   ...
                          │    │    ✗     │     │    ✗     │
   views::filter(!isnan)  ▼    ▼          ▼     ▼          ▼
   knownAges (lazy view): 29  0.9         2    30          25   ...

   one NaN slipping through would poison std::accumulate's sum with NaN,
   and would throw off std::ranges::sort's ordering - filtering FIRST
   avoids both
```

### Descriptive statistics: sort, then read off the shape

```
   cleanAges, sorted ascending:

   [ 0.17  0.42  1.00  ...  28.00  ...  79.00  80.00 ]
     ▲                        ▲                  ▲
   .front()                middle               .back()
   = minimum                                   = maximum
                    (median = the middle element,
                     or the average of the two middle
                     elements if the count is even)

   average = std::accumulate(cleanAges, 0.0) / cleanAges.size()
```

### Counting with a condition: `std::ranges::count_if`

```cpp
std::ranges::count_if(passengerClass, [](int c) { return c == 1; });
```

```
   passengerClass:  1   3   1   2   3   3   1   2  ...
                    │       │       │       │
                    ▼       ▼       ▼       ▼
                count_if(== 1) counts only these matches

   result: however many elements satisfied the predicate -
           no hand-written loop, no manually incremented counter
```

### Cross-referencing parallel columns by index

`survived`, `sex`, and `passengerClass` are separate `std::vector`s, but
row `i` in each one describes the **same passenger** - so answering "what
fraction of survivors were women" means walking `i` across all three
together.

```
   index i:          0        1        2        3       ...
                      │        │        │        │
   survived[i]:       1        1        0        1
   sex[i]:          female    male    female    male
   passengerClass[i]:  1        1        1        2

   passenger 0: survived=1, sex="female", class=1   ─┐
   passenger 1: survived=1, sex="male",   class=1    ├─ same i, same person,
   passenger 3: survived=1, sex="male",   class=2   ─┘   three parallel vectors
```

The result is a small report: passenger counts by class, an overall
survival rate, and a breakdown of who survived by sex and by class - real
answers pulled out of a real dataset using nothing but the tools from
this chapter.

---

## 7.14 Assignment

Eight exercises building toward the same kind of work as the Titanic
project, on a smaller dataset. `main.cpp` has the eight stubbed exercises,
each with its problem statement and a sample run in a comment;
`main_solution.cpp` solves all eight with the statements repeated above
each solution. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `grow_readings()` | building a `std::vector` one `push_back` at a time |
| 2 | `warmest_and_coolest()` | sorting a local copy, reference out-parameters, leaving the original untouched |
| 3 | `average_of_hot_days()` | a `views::filter` \| `views::transform` pipeline, `std::accumulate` over a view |
| 4 | `clean_label()` | `find`/`erase`, `find`/`replace` in a loop |
| 5 | `extract_reading()` | parsing one line of text with `std::istringstream` |
| 6 | `flagged_accounts()` | `rapidcsv::Document` + `std::regex_match`, on `accounts.csv` |
| 7 | `format_receipt()` | `std::format`'s fill/align/width/precision spec grammar |
| 8 | `days_until()` | `std::chrono::year_month_day`, `sys_days` conversion, calendar-day arithmetic |

The quiz (`QUIZ.md`) is 23 multiple-choice questions across the whole
chapter, including the format-spec grammar, chrono durations/clocks/
calendar dates, the CSV/vendoring pattern, and the Titanic project's
ranges/statistics.

After this chapter the student can hold, sort, search, and summarize real
collections of data - the last stop before the course turns to pointers
and, from there, to classes.
