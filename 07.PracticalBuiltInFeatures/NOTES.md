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
that job: fixed and growable containers, how to pass a collection to a
function without either copying it needlessly or letting it be
mutated by accident, sorting and searching, the functional-style
ranges/views pipeline, strings beyond what we have seen so far. Things
like the `std::format` spec grammar, non-owning views into text,
`std::chrono` for durations/clocks/calendar dates, files revisited with
formatted input, reading structured data, and pattern matching with regular
expressions. It closes with a small project that puts all of it to work
on a real dataset - the Titanic passenger manifest.

---

## 7.2 `std::array` and range-based for loops

This lecture covers two things together: **`std::array`**, the
fixed-size container, and **range-based `for`**, the loop shape you will
reach for most often to walk one. They are introduced side by side
because a container is only as useful as the loops that read it.

**`std::array<T, N>`** is a **fixed-size** sequence of `N` values of type
`T`, stored **inline** - the elements sit directly inside the `array`
object, back to back, no separate heap allocation (we will come back to
what that means once heap allocation itself is on the table). `N` is
part of the type: `std::array<int, 5>` and `std::array<int, 10>` are
different types, the same way `int` and `double` are different types.

The running example: tallying six-sided **dice rolls**. `roll_tally`
counts how many times each face came up - index `i` holds the count for
face `i + 1`:

```cpp
std::array<int, 6> roll_tally{};   // {} zero-initializes every element
```

```
   std::array<int, 6> roll_tally{};

   index:      0     1     2     3     4     5
             ┌─────┬─────┬─────┬─────┬─────┬─────┐
   roll_tally│  0  │  0  │  0  │  0  │  0  │  0  │   one block, 6 ints,
             └─────┴─────┴─────┴─────┴─────┴─────┘   sitting right here
                ▲                                 ▲
         roll_tally[0]                     roll_tally[5]
          (count of 1s)                     (count of 6s)
                      size() == 6, fixed forever
```

### Filling it in from real data

A fixed sequence of ten rolls stands in for "a die that was already
rolled and someone wrote the results down":

```cpp
constexpr std::array<int, 10> rolls{3, 3, 1, 6, 3, 2, 3, 5, 4, 3};

for (std::size_t i{0}; i < rolls.size(); ++i) {
    ++roll_tally[rolls[i] - 1];
}
```

Each roll's face value (`1`..`6`) becomes the index (`face - 1`) whose
count gets incremented - `rolls[i] - 1`, because indices start at `0` but
die faces start at `1`:

```
   rolls:  3   3   1   6   3   2   3   5   4   3
           │   │   │   │   │   │   │   │   │   │
           ▼   ▼   ▼   ▼   ▼   ▼   ▼   ▼   ▼   ▼
   index:  2   2   0   5   2   1   2   4   3   2      (roll - 1)

   roll_tally after all ten increments:

   index:      0     1     2     3     4     5
             ┌─────┬─────┬─────┬─────┬─────┬─────┐
   roll_tally│  1  │  1  │  5  │  1  │  1  │  1  │
             └─────┴─────┴─────┴─────┴─────┴─────┘
             face1  face2  face3  face4  face5  face6
                            ▲
                     three showed up FIVE times
                     (indices 2, 2, 2, 2, 2 - five of the 3s in rolls)
```

### Access: `[]` vs `.at()`

`roll_tally[face]` is **unchecked** - fast, but an out-of-range `face` is
undefined behavior: the program might crash, or might silently read
whatever garbage happens to sit past the array in memory.
`roll_tally.at(face)` is the same idea, **bounds-checked**: an
out-of-range index throws `std::out_of_range` instead of reading garbage.

```
   roll_tally[face]        face in range        →  reads roll_tally[face], no check
                            face out of range    →  UNDEFINED BEHAVIOR (danger)

   roll_tally.at(face)     face in range        →  reads roll_tally[face]
                            face out of range    →  throws std::out_of_range
```

```cpp
roll_tally.at(6);   // 6-element array, valid indices 0..5 - out of range
```

```
   roll_tally.at(6)   on a 6-element array (valid indices 0..5)
        │
        ▼
   throws std::out_of_range   ("array::at: __n (which is 6) >= _Nm (which is 6)")
```

### CTAD: skip the `<T, N>`

In plain terms: normally you have to tell `std::array` two things up
front - what type it holds and how many elements it has
(`std::array<int, 6>`). CTAD (Class Template Argument Deduction) means
the compiler can often **figure both of those out by itself**, just by
looking at what you put in the braces - so you get to skip typing them.

`std::array` is a **class template** - a blueprint that needs some
**arguments** filled in (`T` and `N`) before it becomes a real type. CTAD
is the compiler's ability to **deduce** those arguments on its own,
instead of requiring you to write them by hand every time.

```cpp
std::array lucky_numbers{7, 13, 21, 3, 42, 9};   // inferred: array<int, 6>
```

```
   std::array lucky_numbers{7, 13, 21, 3, 42, 9};
                             └──────────┬──────────┘
                             6 ints in the braces
                                        │
                                        ▼
                        compiler infers: std::array<int, 6>
```

### Range-based for: value vs. reference

```cpp
for (int number : lucky_numbers)  { /* read-only */ }
for (int& number : lucky_numbers) { number += 100; }   // modifies in place
```

A reference is not free - it exists to do one of two jobs. Neither job
applies to a loop that only *reads* an `int`, so the first loop takes
`number` **by value**, not by reference:

```
   WHY A REFERENCE, NORMALLY                 WHY NOT HERE
   ──────────────────────────                ────────────
   1. avoid copying a LARGE element          int is tiny - a few bytes.
      (a std::string, a struct, ...)         Copying it costs nothing a
                                              reference would save.

   2. WRITE back into the array              This loop only reads number -
      through the loop variable              never assigns to it.
```

```
   int number : lucky_numbers              int& number : lucky_numbers
   ────────────────────────                ───────────────────────────
   number is a COPY of                     number is a WRITABLE alias
   each element in turn                    for each element in turn

   lucky_numbers: 7 13 21 3 42 9           lucky_numbers: 7 13 21 3 42 9
                   │                                        │
                   └─ number holds a                        └─ number += 100 writes
                      copy - changing it                        straight back into
                      does not touch the                        the array
                      array

                                                     →   107 113 121 103 142 109
```

The rule of thumb: **default to reading by value for small types like
`int`, `char`, `double`; reach for a reference only when you need to
write back, or when the element is large enough that copying it costs
something** (a `std::string`, a `std::vector`, a struct with several
members). `const T&` is the habit that pays off once `T` stops being tiny
- it shows up again from chapter 7.7 onward, once the elements are
`std::string`s instead of `int`s.

### The C++20 `for (init; cond; range)` form

A plain range-based for only hands you each **value** - no index. That
is fine here, since summing does not need one, and `number` is still
read-only, so it stays a by-value `int`:

```cpp
for (int total{0}; int number : lucky_numbers) {
    total += number;
    std::println("number: {}, running total: {}", number, total);
}
```

The loop declares its own accumulator (`total`) right where it is used,
instead of on a separate line above the loop:

```
   number:    107    113    121    103    142    109
   total:       0 → 107 → 220 → 341 → 444 → 586 → 695     (running total, traced step by step)
```

---

## 7.3 Collection parameters and const

In this lecture, we explore what happens when a function takes a
**collection** as a parameter, and how `const` changes the story. 
As usual, a parameter can be passed: 
- by value (the function gets its own copy),
- by reference (the function gets an alias to the caller's own data)
- by const reference (the function gets an alias, but cannot write through it).

We how all this applies to the case when the parameter is a **collection** instead of a single `int` or `double`.

### By value: the whole array gets copied

```cpp
void report_by_value(std::array<int, 5> readings) {
    readings[0] = -1;   // only touches this function's own copy
    // ...
}
```

We have already seen that `const` on a by-value `int` parameter only protects a
copy the function already owns - the caller was never at risk either
way. The same is true here, but the **cost** is no longer negligible:
copying an `int` is one machine word; copying a `std::array<int, 5>` is
five.

```
   caller                                report_by_value(sensor_readings)
   ──────                                ─────────────────────────────────
   sensor_readings: ┌────┬────┬────┬────┬────┐   copy    readings: ┌────┬────┬────┬────┬────┐
                    │ 68 │ 71 │ 69 │ 72 │ 70 │  ───────►           │ 68 │ 71 │ 69 │ 72 │ 70 │
                    └────┴────┴────┴────┴────┘                     └────┴────┴────┴────┴────┘
                                                                      │
                                              readings[0] = -1  ◄─────┘   only this SEPARATE
                                                                            block changes

   sensor_readings afterward: ┌────┬────┬────┬────┬────┐    UNCHANGED - the edit landed
                              │ 68 │ 71 │ 69 │ 72 │ 70 │    on a copy that is thrown
                              └────┴────┴────┴────┴────┘    away when the function returns
```

### By reference: an alias, and writes land on the caller's array

```cpp
void reset_readings(std::array<int, 5>& readings) {
    for (int& reading : readings) {
        reading = 0;
    }
}
```

No copy - `readings` is another name for the caller's own array. This is
the right tool when a function's entire job is to mutate the caller's
data in place:

```
   caller                                reset_readings(sensor_readings)
   ──────                                ────────────────────────────────
   sensor_readings: ┌────┬────┬────┬────┬────┐  alias   readings
                    │ 68 │ 71 │ 69 │ 72 │ 70 │ ◄───────► (same object,
                    └────┴────┴────┴────┴────┘            no copy)
                       ▲
                       │ for (int& reading : readings) { reading = 0; }
                       │ writes THROUGH the alias, straight back onto
                       │ the caller's own array
                       ▼
   sensor_readings afterward: ┌────┬────┬────┬────┬────┐   CHANGED - reset_readings'
                              │  0 │  0 │  0 │  0 │  0 │   whole purpose was to do
                              └────┴────┴────┴────┴────┘   exactly this
```

### By const reference: an alias, but a read-only one

```cpp
void report_by_const_ref(const std::array<int, 5>& readings) {
    // readings[0] = 99;   // would not compile
    std::print("readings: ");
    for (int reading : readings) {
        std::print("{} ", reading);
    }
}
```

No copy, and the compiler enforces that this function **cannot** write
through `readings`. 

```
   readings[0] = 99;   inside report_by_const_ref
        │
        ▼
   COMPILE ERROR: cannot assign to return value because function
                  'operator[]' returns a const value
```

### Side by side

```
                  by value                by reference             by const reference
                  ─────────                ────────────             ───────────────────
   copy made?     YES - all N elements     NO - an alias            NO - an alias
   caller sees    NEVER - edits land       ALWAYS - edits land      cannot write at all -
   mutations?     on a throwaway copy      on the caller's array    compiler-enforced
   choose when    the function needs       the function's job is   the function only
                  its own independent      to mutate the caller's  needs to READ - the
                  copy to experiment on    data in place            common case
```

Rule of thumb: default to **`const&`** for a collection a function only
reads; reach for a plain **`&`** when the function's purpose is to
mutate the caller's own data; reach for **by value** only when the
function needs an independent copy to work with (Very rare). 

---

## 7.4 `std::vector`

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

### Growing from nothing: `push_back`

The running example: a **warehouse** that starts with no stock and
receives deliveries one at a time.

```cpp
std::vector<int> warehouse_stock;   // starts empty, size() == 0

warehouse_stock.push_back(40);
warehouse_stock.push_back(15);
warehouse_stock.push_back(60);
```

```
   warehouse_stock{};                                   size() == 0
   (nothing allocated yet)

   push_back(40)  →  ┌────┐                              size() == 1
                     │ 40 │
                     └────┘

   push_back(15)  →  ┌────┬────┐                         size() == 2
                     │ 40 │ 15 │
                     └────┴────┘

   push_back(60)  →  ┌────┬────┬────┐                    size() == 3
                     │ 40 │ 15 │ 60 │
                     └────┴────┴────┘
```

This is the one thing `std::array` fundamentally cannot do - its size is
fixed at compile time, while `push_back` grows a `vector` on demand.

### `(N)` vs. `{N}` - a common first mistake

A vector can also be built at a fixed starting size instead of growing
one element at a time - `storefront_stock(5)` and `backroom_stock(8)`
each start pre-filled with zeros:

```cpp
std::vector<int> storefront_stock(5);   // 5 elements, each value-initialized to 0
std::vector<int> other{5};              // ONE element, valued 5
```

```
   storefront_stock(5)  →  ┌───┬───┬───┬───┬───┐
                           │ 0 │ 0 │ 0 │ 0 │ 0 │     FIVE elements
                           └───┴───┴───┴───┴───┘     (5) sizes the vector

   other{5}              →  ┌───┐
                            │ 5 │                     ONE element
                            └───┘                     {5} is the element list
```

Parentheses `()` size the vector; braces `{}` list its elements. The two
look almost identical and mean very different things - worth a second
look every time.

### Comparing, copying, assigning

```cpp
storefront_stock != backroom_stock;              // element-by-element comparison
std::vector overflow_stock{backroom_stock};      // copy constructor - overflow_stock
                                                  // owns its own copy of the data
storefront_stock = backroom_stock;               // assignment - storefront_stock's
                                                  // old contents are replaced
```

```
   std::vector overflow_stock{backroom_stock};

   backroom_stock: ┌───┬───┬───┬───┬───┬───┬───┬───┐   overflow_stock: ┌───┬───┬───┬───┬───┬───┬───┬───┐
                   │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │                   │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │
                   └───┴───┴───┴───┴───┴───┴───┴───┘                   └───┴───┴───┴───┴───┴───┴───┴───┘
                     own block of memory                                 a SEPARATE block - overflow_stock's own copy
                     changing backroom_stock later does NOT touch overflow_stock, and vice versa
```

### `.at()` as an lvalue: bounds-checked writes, and reading it out of bounds

`.at(i)` is not just for reading - assigning through it writes to that
element, still with the bounds check:

```cpp
storefront_stock.at(3) = 250;   // bounds-checked write
```

Read past the end, though, and it throws instead of silently returning
garbage:

```cpp
try {
    storefront_stock.at(20);   // out of range - storefront_stock only has 8 elements
}
catch (const std::out_of_range& ex) {
    std::println("An exception occurred: {}", ex.what());
}
```

```
   storefront_stock.at(20)  on an 8-element vector
        │
        ▼
   throws std::out_of_range  ──►  caught by catch  ──►  ex.what() printed
                                   (program keeps running, does not crash)
```

---

## 7.5 Sorting, searching, and `accumulate`

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

That works, but  there is another paradicm we can use to do the same things. 
It is called **Functional Programming**. Sometimes also refered to 
as **Declarative Programming**. This lecture and the next introduce tools that subscribe to that 
paradigm - `accumulate`,`filter`, `transform` - where you instead state *what* you 
want and let the library supply the *how*:

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
   filter(keep_if)                      the view's internal iteration (7.6)
   transform(map_to)                    the view's internal iteration (7.6)
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

#### "Ascending" is a default comparator, not magic

`sort` with no second argument is shorthand, the same way `accumulate`
with no fourth argument was (earlier in this lecture). The comparator it
defaults to is `std::ranges::less` - pass it explicitly and nothing
changes:

```cpp
std::ranges::sort(fruits, std::ranges::less{});   // identical order to sort(fruits)
```

Swap in `std::ranges::greater` instead, and the exact same algorithm
sorts **descending** - `sort`'s job never changes, only the rule it uses
to compare two elements does:

```cpp
std::ranges::sort(fruits, std::ranges::greater{});
```

```
   std::ranges::sort(fruits)                    std::ranges::sort(fruits, std::ranges::greater{})
        │                                              │
        ▼                                              ▼
   apple date fig kiwi mango                    mango kiwi fig date apple
   (ascending - std::ranges::less                (descending - largest first,
    is the implicit default)                      same sort, different comparator)
```

#### A lambda comparator can reproduce `less`/`greater` by hand

`sort`'s comparator is any two-argument, `bool`-returning callable - the
same shape `accumulate`'s combine function had, just interpreted
differently: `true` means "the first argument belongs before the
second." A lambda can reproduce the built-in comparators exactly:

```cpp
std::ranges::sort(fruits, [](const std::string& a, 
         const std::string& b) { return a < b; });   // == std::ranges::less{}
std::ranges::sort(fruits, [](const std::string& a, 
         const std::string& b) { return a > b; });   // == std::ranges::greater{}
```

Both produce byte-for-byte the same order as the `less{}`/`greater{}`
calls above - proof that `less`/`greater` are not a separate mechanism
from a lambda comparator, just a ready-made one for the everyday case.

#### A lambda can express a rule `less`/`greater` cannot

`std::ranges::less`/`greater` only ever compare two elements *as
themselves*. A lambda comparator can compare anything derived from
them - here, each string's `.size()` instead of the strings
alphabetically:

```cpp
std::ranges::sort(fruits,
                   [](const std::string& a, const std::string& b) {
                       return a.size() < b.size();   // shorter name first
                   });

std::ranges::sort(fruits,
                   [](const std::string& a, const std::string& b) {
                       return a.size() > b.size();   // longer name first
                   });
```

```
   fruits = {mango, kiwi, fig, date, apple}   (lengths: 5, 4, 3, 4, 5)

   sort by .size(), ascending:    fig  kiwi  date  mango  apple
                                    3    4     4      5      5
                                              (kiwi/date and mango/apple
                                               keep their original relative
                                               order - ties are not reordered)

   sort by .size(), descending:   mango  apple  kiwi  date  fig
                                     5      5     4     4     3
```

This is the real payoff of a lambda comparator: alphabetical order is
only one possible rule, and `sort` does not care which rule you give it
- it just needs something that can say, for any two elements, which one
belongs first.

### Searching sorted data with `std::ranges::binary_search`

`binary_search` repeatedly **halves** the search range - which only gives
a correct answer when the data is already sorted **in the order the
search assumes** - ascending, by default.

```
   searching sorted {apple, date, fig, kiwi, mango} for "kiwi"

   step 1:  apple  date  [fig]  kiwi  mango     middle = fig, "kiwi" > "fig" → search right half
   step 2:  ......  kiwi  mango                 middle = kiwi, MATCH → true

   only 2 comparisons instead of checking all 5, one by one
```

```cpp
std::ranges::sort(fruits);   // back to alphabetical ascending - fruits was
                              // left sorted by LENGTH, descending, from the
                              // last lambda comparator above; binary_search
                              // assumes alphabetical ascending order

std::ranges::binary_search(fruits, "kiwi"s);   // true
std::ranges::binary_search(fruits, "guava"s);  // false
```

That halving is the trade a sort buys you: `O(log n)` lookups instead of
scanning every element - but only correct when the data's actual order
matches what `binary_search` assumes. The dangerous part is that this
failure is **not reliable**: search `fruits` while it is still sorted by
length instead of alphabetically, and the result depends entirely on
where the halving happens to land - it might report "not found" for a
value that is there, might find the wrong thing, or might even
accidentally succeed, all without any warning that the assumption was
violated. That is worse than an obvious crash - a bug that only shows up
for *some* searches on *some* data is much harder to catch in testing.
Sorting back to alphabetical ascending immediately before the search, as
the code above does, is what avoids it - a reminder that
`binary_search`'s "sorted" always means "sorted by the same rule
`binary_search` itself is using," not sorted any old way.

### Folding a range into one value with `std::accumulate`

`std::accumulate(first, last, init)` is the declarative tool from the
opening of this lecture, applied to "reduce a range to one value": state
*what* you want (start from `init`, combine every element) and let the
library own the loop.

```cpp
std::accumulate(quantities.begin(), quantities.end(), 0);   // sum, starting from 0
```

Unlike `std::ranges::sort` and `std::ranges::binary_search` above,
`accumulate` has **no `std::ranges::` counterpart** to call directly on
`quantities` - `<numeric>` was never given the same range-based
overloads `<algorithm>` was, so `begin()`/`end()` still have to be passed
explicitly, the pre-ranges way.

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

#### "No fourth argument" is shorthand

A lambda spelling out `x + y` and calling `accumulate` with no fourth
argument at all produce the identical result:

```cpp
std::accumulate(quantities.begin(), quantities.end(), 0);                       // 100
std::accumulate(quantities.begin(), quantities.end(), 0,
                 [](int x, int y) { return x + y; });                            // 100, same
```

```
   accumulate(begin, end, 0)                accumulate(begin, end, 0, [](x, y){ return x + y; })
        │                                              │
        └──────────────────────┬──────────────────────┘
                                ▼
                   IDENTICAL - "no fourth argument" is shorthand for
                   "combine with +". Seeing the default written out as
                   a lambda makes plain there was never anything hidden -
                   just a default value for a parameter, like default
                   arguments (6.5) on an ordinary function.
```

#### A built-in function object instead of a lambda: `std::plus`

`<functional>`'s `std::plus<T>` is a small callable object whose whole
job is `x + y` - the standard library's own version of the lambda above,
ready-made:

```cpp
std::accumulate(quantities.begin(), quantities.end(), 0, std::plus<int>());   // 100, same again
```

```
   named function      multiply(x, y) { return x * y; }        - write it yourself, reusable
   lambda               [](int x, int y) { return x + y; }      - write it yourself, inline, once
   function object       std::plus<int>()                       - already written FOR you
```

All three are just different ways to hand `accumulate` something
callable with two arguments - the choice is about where the logic
already lives (a name you already wrote, an inline one-off, or a
standard type nobody has to write at all), not about which one
`accumulate` prefers.

Passing behavior around like this is also why these tools favor
**immutability**: `quantities` and `factors` are never modified by any of
this - `accumulate` reads them and hands back a brand new value, so there
is no shared running variable for two different pieces of code to step on
by mistake.

---

## 7.6 Ranges and views

In this lecture, we are expxloring C++20's **ranges library**
two more declarative building features: **filter** (keep only what matches)
 and **transform** (map each value to a new one) - that chain together instead
of nesting loops inside loops.

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

In English: take `numbers`, keep only the even ones, then square each of
those that survived the filter. Nothing is computed yet - the result just
sits in the air as a view, waiting for something to iterate it.

### A view does not build a container - it wraps one, lazily

```cpp
auto counted{std::views::iota(1, 11)};   // the integers 1..10, generated lazily
```

```
   std::views::iota(1, 11)

   NOT this (eager - builds the whole thing up front):
      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐State w
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

NOTE: The result of the pipeline above is a **view**, or a description of a range,
that comes up with real values only when something iterates it. 
Hence the name **lazy evaluation**.

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
internal iteration" pattern we have seen before: `accumulate`
folds a range down to one value, `filter`/`transform` reshape a range
into a new one, and all three let you state *what* instead of *how*.

---

## 7.7 Strings deep dive

In this lecture, we explore more on `std::string` and its built-in features.
In previous chapters and lectures, we had a chance to look at things like
`length()`/`size()`, `empty()`, `==`/`!=`, `+`, and `starts_with`/`ends_with`. 
We'll now look at some of the other built-in features that `std::string` provides.

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
log.rfind("is");                   // last occurrence
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

Everything so far has streamed to the console (`std::cout`) or to a file
(`std::ifstream`/`std::ofstream`). C++ offers a third destination: a
string held **in memory**, via `std::istringstream` and
`std::ostringstream`. They support the same `<<`/`>>` operators and
formatting machinery as any other stream - just aimed at a string instead
of a screen or a file.

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

## 7.8 String formatting with `std::format`

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

### Precision:

Digits after decimal point for floating-point, or max characters for a string:

```cpp
std::println("{:.2f}", 3.14159);   // "3.14" - digits after the decimal
std::println("{:.3}", "abcdefg");  // "abc"  - max characters, for a string
```

### When you chop off digits after the decimal point

Squeezing a `double` down to fewer decimal digits **rounds** to the
nearest representable value - it does not just chop the extra digits off.
C++ uses **round half to even** (also called **banker's rounding**) .
Here are the rules simplified:

1. **Not a tie?** Round to the nearer value, same as school rounding.
   ```cpp
   std::println("{:.2f}", 3.14159);   // "3.14" - third decimal is 1, rounds down
   std::println("{:.2f}", 3.146);     // "3.15" - third decimal is 6, rounds up
   ```
2. **Is it a tie** (the cut-off part is exactly half)? Check if that
   half is exactly representable in binary (rule below).
   - **Exact** -> it's a real tie -> round to whichever neighbor is
     **even**.
     ```cpp
     std::println("{:.0f}", 2.5);     // "2"    - exact tie -> round to even -> 2
     std::println("{:.0f}", 3.5);     // "4"    - exact tie -> round to even -> 4, not 3
     std::println("{:.2f}", 0.125);   // "0.12" - exact tie -> round to even -> 0.12
     ```
   - **Not exact** -> it only looks like a tie in decimal; the value
     stored in memory is actually a hair above or below `.5` -> round
     to whichever side it actually leans.
     ```cpp
     std::println("{:.2f}", 0.135);   // "0.14" - NOT an exact tie -> leans up -> 0.14
     ```

**How to check "exactly representable in binary":** take the
fractional part and keep multiplying by 2, dropping the whole-number
part each time. If you hit exactly `0`, it is exact. If it repeats
forever instead, it is not.

```
   0.125 x 2 = 0.25   -> .25
   0.25  x 2 = 0.5    -> .5
   0.5   x 2 = 1.0    -> 0 left over          EXACT (took 3 steps)

   0.135 x 2 = 0.27   -> .27
   0.27  x 2 = 0.54   -> .54
   0.54  x 2 = 1.08   -> .08
   0.08  x 2 = 0.16   -> .16
   ...never reaches exactly 0                  NOT EXACT (repeats forever)
```

NOTE: If this is confusing, just set up some code and let your computer tell you!

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

A plain `{}` always grabs the next argument in line. Putting a number
inside the braces - `{0}`, `{1}`, `{2}` - picks an argument by its
position instead, so you can print the same argument more than once, or
print the arguments in a different order than you passed them. This is 
also handy if you decide to translate your program into another language
for example.

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

### Put it all together

You can put it all together. Once thing to note is that the positional
argument or index comes before the `:` in the spec.

```
    std::println("{0:>8.2f} | {1:>8.2f}", 4.5, 128.375);
```

```
   {0:>8.2f}  |  {1:>8.2f}
    │          │
    │          └── args[1] = 128.375 → " 128.38" (rounded, right-aligned in width 8)
    └────────────── args[0] = 4.5 → "   4.50" (rounded, right-aligned in width 8)
```

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

## 7.9 `std::string_view`

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

## 7.10 Date and Time Utilities

Time shows up everywhere in real programs - how long an operation took,
what the timestamp on a log line should read, what today's date is,
what "9am in Brussels" means to someone in New York. **`<chrono>`** is
the standard library's time toolkit, and it is built from five pieces:

```
   DURATIONS    an amount of time            ("90 minutes and 32 seconds")
   CLOCKS       a source of "now"            (steady_clock, system_clock, ...)
   TIME POINTS  a specific instant           (a duration since a clock's epoch)
   DATES        a genuine calendar day       (year_month_day, since C++20)
   TIME ZONES   wall-clock time for a place  (zoned_time, since C++20)
```

Everything lives in `<chrono>`, namespace `std::chrono`. Underneath all
five sits `<ratio>` - the compile-time fraction type chrono uses to
describe exactly how long "one tick" is, for every duration type, with
zero runtime cost. This lecture walks the five pieces in that order, one
file per topic - `main1_ratios.cpp` through `main8_time_zones.cpp` - so
each can be built and stepped through on its own.

### `main1_ratios.cpp` - `std::ratio`: an exact fraction, known at compile time

`std::ratio` lets you represent any finite rational number exactly, and
use it at compile time. It lives in `<ratio>`, namespace `std`. This is
not a value you compute with at runtime - `ratio` is a **class template**,
and a specific instantiation of it, like `ratio<1, 4>` (one quarter),
names one specific rational number as a **type**. The numerator and
denominator are compile-time constants of type `std::intmax_t` (a signed
integer with the widest range your compiler supports), reached through
the type's own `::num` and `::den`:

```cpp
// (1) A quarter, spelled out in full - no alias, just the type itself.
intmax_t quarterHourNum{std::ratio<1, 4>::num};   // 1
intmax_t quarterHourDen{std::ratio<1, 4>::den};   // 4
std::println("1/4 = {}/{}", quarterHourNum, quarterHourDen);
```

```
   std::ratio<1, 4>
              │  │
              │  └── denominator, a compile-time constant: ::den
              └───── numerator,   a compile-time constant: ::num

   You never write "ratio<1,4> r;" and call member functions on r -
   there IS no object. You only ever read ::num / ::den off the TYPE
   itself, the way you just read quarterHourNum/quarterHourDen above.
```

Because the numerator and denominator must be known at compile time, a
`ratio` built from ordinary (non-const) variables is a compile error -
`const` fixes it, since a `const intmax_t` initialized from a literal is
itself a compile-time constant:

```cpp
intmax_t n{1}, d{4};
using bad = std::ratio<n, d>;         // Error: n, d are not compile-time constants

const intmax_t cn{1}, cd{4};
using ok = std::ratio<cn, cd>;        // Ok: const constants are usable
```

**Ratios are always normalized.** For `ratio<n, d>`, the library divides
out the greatest common divisor `gcd` of `n` and `d`:

```
   num = sign(n) * sign(d) * abs(n) / gcd
   den = abs(d) / gcd

   ratio<2, 8>   and   ratio<1, 4>   →  the exact same TYPE after normalization
```

`main1_ratios.cpp` proves it with `ratio_equal`, one of the compile-time
comparison templates covered below:

```cpp
// (2) Two different SPELLINGS, but the exact same type after normalization.
std::println("ratio<2,8> == ratio<1,4>: {}",
              std::ratio_equal<std::ratio<2, 8>, std::ratio<1, 4>>::value);
// "ratio<2,8> == ratio<1,4>: true"
```

**The four arithmetic operations.** Because ratios are types, not
objects, you cannot write `ratio<1,4> + ratio<1,3>` - the library gives
you four class templates instead, one per operation, each computing a
*new* `ratio` type through an embedded `::type` alias. `main1_ratios.cpp`
runs all four, back-to-back, against the plain fraction math so you can
check every result by hand:

```cpp
// (3) Addition: a quarter of an hour + a third of an hour.
using sumType = std::ratio_add<std::ratio<1, 4>, std::ratio<1, 3>>::type;
std::println("1/4 + 1/3 = {}/{}", sumType::num, sumType::den);
```

```
   1/4 + 1/3
      │    │
      │    └── common denominator 12: 1/3 = 4/12
      └─────── common denominator 12: 1/4 = 3/12

   3/12 + 4/12 = 7/12   ──►  ratio_add<ratio<1,4>, ratio<1,3>>::type
                              is the type ratio<7, 12> - already normalized,
                              since gcd(7, 12) == 1
```

```cpp
// (4) Subtraction: a half of an hour - a quarter of an hour.
using differenceType = std::ratio_subtract<std::ratio<1, 2>, std::ratio<1, 4>>::type;
std::println("1/2 - 1/4 = {}/{}", differenceType::num, differenceType::den);
```

```
   1/2 - 1/4
      │    │
      │    └── 1/4 stays as-is
      └─────── common denominator 4: 1/2 = 2/4

   2/4 - 1/4 = 1/4   ──►  ratio_subtract<ratio<1,2>, ratio<1,4>>::type
                           is the type ratio<1, 4>
```

```cpp
// (5) Multiplication: a quarter of an hour, times two-thirds.
using productType = std::ratio_multiply<std::ratio<1, 4>, std::ratio<2, 3>>::type;
std::println("1/4 * 2/3 = {}/{}", productType::num, productType::den);
```

```
   1/4 * 2/3  =  (1*2) / (4*3)  =  2/12

   2/12, reduced by gcd(2,12)=2, is 1/6   ──►  ratio_multiply<...>::type
                                                 is the NORMALIZED type ratio<1, 6>
```

```cpp
// (6) Division: a half, divided by a quarter.
using quotientType = std::ratio_divide<std::ratio<1, 2>, std::ratio<1, 4>>::type;
std::println("(1/2) / (1/4) = {}/{}", quotientType::num, quotientType::den);
```

```
   (1/2) / (1/4)  =  1/2 * 4/1  =  4/2

   4/2, reduced by gcd(4,2)=2, is 2/1 (i.e. 2)   ──►  ratio_divide<...>::type
                                                        is the type ratio<2, 1>
```

**Comparisons work the same way** - `ratio_equal`, `ratio_not_equal`,
`ratio_less`, `ratio_less_equal`, `ratio_greater`, and
`ratio_greater_equal` are all evaluated at compile time, on types, not
values. Each produces a `std::bool_constant` - itself a
`std::integral_constant<bool, ...>`, a struct template pairing a type
with a compile-time constant value (`integral_constant<int, 15>` stores
an `int` valued 15; `bool_constant<true>` is `integral_constant<bool,
true>`). Read the answer off the result's `::value` member:

```cpp
// (7)-(9) Comparing 1/3 against 1/4 - and 1/4 against itself.
std::println("1/3 <  1/4 : {}", (std::ratio_less<std::ratio<1, 3>, std::ratio<1, 4>>::value));
std::println("1/3 >  1/4 : {}", (std::ratio_greater<std::ratio<1, 3>, std::ratio<1, 4>>::value));
std::println("1/4 <= 1/4 : {}", (std::ratio_less_equal<std::ratio<1, 4>, std::ratio<1, 4>>::value));
// false, true, true - exactly what plain fraction math would tell you:
// 1/3 (≈0.333) is bigger than 1/4 (0.25), and 1/4 is certainly <= itself.
```

Because a ratio is a type, you cannot `println("{}", someRatio)` directly
- you always extract `::num`/`::den` (or, for comparisons, `::value`)
first, exactly as every example above does.

**Naming a ratio with `using`, once the full spelling gets tedious.** A
type alias changes nothing about how the ratio behaves - it is just a
shorter name for the exact same type, and it is what you will actually
reach for once a ratio gets used more than once:

```cpp
// (10) Same computation as (3), now with names instead of the full spelling.
using quarterHour = std::ratio<1, 4>;
using thirdHour = std::ratio<1, 3>;
using sumViaAliases = std::ratio_add<quarterHour, thirdHour>::type;
std::println("quarterHour + thirdHour = {}/{}", sumViaAliases::num, sumViaAliases::den);
// "quarterHour + thirdHour = 7/12" - identical result to (3), just easier to read
```

**SI ratio aliases the library ships for convenience** - `milli`,
`micro`, `nano`, `kilo`, `mega`, and more, all the way from `yocto`
(`10^-24`) to `yotta` (`10^24`):

```cpp
// (11)-(12)
std::println("milli = {}/{}", std::milli::num, std::milli::den);   // "milli = 1/1000"
std::println("kilo  = {}/{}", std::kilo::num, std::kilo::den);     // "kilo  = 1000/1"
```

`chrono` uses exactly these to define its predefined duration types
(`milliseconds` is a duration ticking in `milli`-second units) - which is
the whole reason `ratio` exists as a lecture prerequisite: every duration
type is tagged with a ratio describing its tick length.

### `main2_durations.cpp` - Durations: an amount of time, with the unit baked into the type

A **duration** is an interval between two points in time - a number of
**ticks**, plus a **tick period** (how long one tick lasts, as a
compile-time `ratio` in seconds):

```cpp
template <class Rep, class Period = std::ratio<1>>
class duration { /* ... */ };
```

```
   std::chrono::duration<Rep, Period>
                          │     │
                          │     └── tick period, a compile-time ratio<N,D>
                          │          in seconds - defaults to ratio<1>,
                          │          i.e. one tick = one second
                          └──────── the type holding the tick COUNT
                                     (an arithmetic type: long, double, ...)
```

```cpp
std::chrono::duration<long, std::ratio<60>> d1{123};   // 123 ticks of 60s each = 123 minutes
```

Three constructors exist: default, "from a tick count", and "from another
duration" - the last one is how conversions between duration types happen.
Durations support the full set of arithmetic operators
(`+ - * / % ++ -- += -= *= /= %=`) plus `==`/`<=>`, and these member
functions:

```
   MEMBER FUNCTION           DESCRIPTION
   ─────────────────────────────────────────────────────────────────────
   Rep count() const         the raw tick count, as the Rep type
   static duration zero()    a duration of zero
   static duration min()     the smallest value Rep can represent
   static duration max()     the largest value Rep can represent
```

`floor()`, `ceil()`, `round()`, and `abs()` work on durations exactly as
they do on plain numbers.

**Comparing durations with different tick periods just works** - the
library converts internally:

```cpp
duration<long, ratio<60>> d3{10};   // 10 minutes
duration<long, ratio<1>>  d4{14};   // 14 seconds
d3 > d4;                             // true - compared as the same underlying time
```

**Converting between duration types** is where the interesting rules
live. Going from a smaller tick to a bigger tick with a **floating-point**
Rep never loses information, so it stays implicit:

```cpp
duration<long> d7{30};                  // 30 seconds (integral)
duration<double, ratio<60>> d8{d7};     // 0.5 minutes - implicit, no data lost
```

```
   30 seconds  ──implicit──►  0.5 minutes
                                  │
                         double Rep can hold a fraction,
                         so nothing is lost - the compiler allows it
```

But converting seconds to minutes with an **integral** Rep could produce
a non-integral result - so the compiler refuses it outright, even when a
particular value happens to divide evenly:

```cpp
duration<long> d7{30};
duration<long, ratio<60>> bad{d7};   // Error: possible truncation - refused
                                      // at compile time, not just at runtime
```

`duration_cast<T>()` is the explicit override, the same spirit as
`static_cast` - it forces the conversion using integer truncation:

```cpp
auto forced{duration_cast<duration<long, ratio<60>>>(duration<long>{30})};
// forced == 0 minutes - 30 seconds truncates down, same as int division
```

```
   duration_cast<T>(source)
        │
        "I know this can lose information - do it anyway,
         and truncate toward zero if it doesn't divide evenly"

   30 seconds  ──duration_cast<minutes>──►  0 minutes   (30 / 60 = 0, truncated)
```

Converting the **other** direction - minutes to seconds - never loses
information when both Reps are integral, so it stays implicit either way:

```cpp
duration<long, ratio<60>> d9{10};   // 10 minutes
duration<long> d10{d9};              // 600 seconds - implicit, exact
```

**Predefined durations** save you from spelling out `duration<Rep,
Period>` by hand - `nanoseconds`, `microseconds`, `milliseconds`,
`seconds`, `minutes`, `hours`, `days`, `weeks`, `months`, `years`, all in
`std::chrono`, built from the SI ratios above:

```cpp
minutes d9{10};   // same type, same meaning, as duration<long, ratio<60>>{10}
```

The standard mandates that these predefined durations use **integral**
Reps - so, just like the `long`-based example above, a conversion that
*could* produce a fractional result is a compile-time error, even when
the specific numbers involved divide evenly:

```cpp
seconds s{60};
minutes m{s};   // Error - refused even though 60s IS exactly 1 minute;
                // the compiler only looks at the TYPES, not the value
```

Converting minutes to seconds is always exact (multiplying by an integer
never introduces a fraction), so it stays implicit:

```cpp
minutes m{2};
seconds s{m};   // Ok, implicit - 120s
```

**Standard chrono literals** - `h`, `min`, `s`, `ms`, `us`, `ns` - build
durations directly from numeric literals, and combine naturally:

```cpp
auto raceDuration{90min + 32s};   // 90 minutes and 32 seconds, added directly
duration_cast<seconds>(raceDuration).count();   // 5432
```

```
   90min + 32s
      │      │
      │      └── 32 seconds
      └───────── 90 minutes  =  5400 seconds
                                   │
                              5400 + 32  =  5432 seconds total
```

These literals live in the inline namespace `std::chrono_literals` (also
reachable via `std::literals::chrono_literals`), and are additionally
re-exported directly into `std::chrono` - so `using namespace
std::chrono;` alone is enough to use them.

**`hh_mm_ss`** takes any duration and splits it back into display-ready
fields - `hours()`, `minutes()`, `seconds()`, `subseconds()`, all
non-negative, plus `is_negative()`:

```cpp
const hh_mm_ss split{hours{1} + minutes{23} + seconds{45}};
std::println("{}h {}m {}s", split.hours().count(),
              split.minutes().count(), split.seconds().count());
// "1h 23m 45s"
```

```
   hh_mm_ss{ 1h + 23min + 45s }
                    │
          the SAME 5025 seconds, just re-sliced into fields

   duration   ──►  one number + a unit            (5025s)
   hh_mm_ss   ──►  several numbers, one per field  (1h 23m 45s)
```

### `main3_now.cpp` and `main4_timing.cpp` - Clocks: a source of "now"

A **clock** pairs a `time_point` type with a `duration` type and an
**epoch** - the moment that clock starts counting from. The standard
defines several:

```
   CLOCK                   DESCRIPTION                               EPOCH
   ──────────────────────────────────────────────────────────────────────────────
   system_clock            UTC wall-clock time, system-wide           1970-01-01
   steady_clock            time_point NEVER decreases - system_clock  unspecified
                           can be adjusted at any time; this one
                           need not relate to wall-clock time at all
   high_resolution_clock   shortest possible tick period - may just   unspecified
                           be an ALIAS for steady_clock or
                           system_clock, depending on your compiler
   utc_clock               UTC, and the ONLY one of these that        1970-01-01
                           tracks leap seconds
   tai_clock               International Atomic Time, weighted        1958-01-01
                           average of several atomic clocks
   gps_clock               GPS satellite time                         1980-01-06
   file_clock              std::filesystem file timestamps            unspecified*

   * typically 1970-01-01 on Unix, 1601-01-01 on Windows
```

A **leap second** is a second occasionally inserted into (or removed
from) UTC to correct drift against true solar time. `utc_clock` is the
only one of these that tracks them; the others don't, and `file_clock`'s
behavior here is unspecified.

> **high_resolution_clock is best avoided.** Its implementation is not
> consistent between compilers - it might be `steady_clock` on one, and
> `system_clock` on another - so whether it can go backward isn't
> portable. Prefer `system_clock` for wall-clock time and `steady_clock`
> for measuring durations, always.

Every clock has a static `now()` returning the current `time_point`, and
a static `is_steady` reporting whether it can go backward:

```cpp
std::println("steady_clock::is_steady = {}", steady_clock::is_steady);  // true
std::println("system_clock::is_steady = {}", system_clock::is_steady);  // false
```

**`main3_now.cpp`: printing the current time.** `std::format`/`println`
understand a `time_point` directly, using the same `{:...}` spec grammar
from 7.8 - `%` codes replace a type letter like `f` or `d`. The `L`
specifier formats according to the current global `locale`:

```cpp
std::locale::global(std::locale{""});    // the user's own OS locale
std::println("UTC: {:L}", system_clock::now());
std::println("UTC: {:L%c}", system_clock::now());   // %c = locale's own "preferred" format
```

```
   {:L%c}
     │ │
     │ └── %c: the locale's own preferred date+time layout
     └──── L:  use the currently configured GLOBAL locale to format it
```

**`main4_timing.cpp`: measuring elapsed time.** `steady_clock` is the
right tool because it is immune to the system clock being adjusted mid-
measurement (NTP sync, a user changing the time):

```cpp
auto start{steady_clock::now()};
// ... the work being timed ...
auto end{steady_clock::now()};
auto diff{end - start};                                       // a duration
println("Total: {}", duration_cast<milliseconds>(diff));
```

```
   timeline:   start ────────────── work happens ────────────── end
                 │                                                │
                 └──────────────────  diff = end - start ─────────┘
                                       (a DURATION, not a time_point -
                                        time_point - time_point = duration)
```

`system_clock` additionally offers `to_time_t()`/`from_time_t()` to
interoperate with the C-style `time_t` representation from `<ctime>`.

A subtlety worth knowing: most OS timers only update every 10-15ms. Any
event shorter than one timer tick appears to take **zero** time, and any
event between one and two ticks appears to take exactly **one** tick -
called **gating error**. A loop that actually takes 44ms on a system with
a 15ms timer update can appear to take only 30ms. The fix is simple: make
the measured work large enough to span many timer ticks (`main4_timing.cpp`
runs 10 million iterations of real arithmetic for exactly this reason).

### `main5_time_point.cpp` - Time Point: a specific instant

A **`time_point`** represents a point in time, stored as a `duration`
relative to its clock's **epoch**. Every `time_point` is tied to a
specific clock - the epoch belongs to the clock, not to `time_point`
itself. (The classic Unix epoch is 1970-01-01, ticking in seconds; the
Windows epoch is 1601-01-01, ticking in 100-nanosecond units - different
platforms, different epochs and units, all hidden behind the same
interface.)

```cpp
time_point<steady_clock> tp1;             // == steady_clock::time_point tp1;
```

`time_since_epoch()` returns the duration between the clock's epoch and
this `time_point`:

```
   tp1                        epoch of steady_clock's own timeline
    │                              │
    │◄──────── time_since_epoch() ─┤
    │                              │
   "10 minutes after this clock started counting"
```

Only the arithmetic that makes sense is supported - you can add or
subtract a duration from a `time_point`, and subtracting two `time_point`s
gives you a duration, but **adding two `time_point`s is not supported**
(there is no meaningful answer to "3pm plus 5pm"):

```
   tp + d = tp        tp - d = tp
   d + tp = tp        tp - tp = d      (two time_points → a duration)
   tp += d            tp -= d

   tp + tp             ← NOT supported. Adding two points in time
                          is not a meaningful operation.
```

`time_point` has three constructors mirroring `duration`'s: default
(initializes to the epoch), from a duration (epoch + that duration), and
from another `time_point` of the same clock (for converting between
precisions). Comparison (`==`, `<=>`) and `min()`/`max()` work as you'd
expect.

### `main6_time_point_conversions.cpp` - converting between precisions

Just like durations, `time_point` conversions are implicit when nothing
can be lost, and explicit otherwise:

```cpp
time_point<steady_clock, seconds> tpSeconds{42s};
time_point<steady_clock, milliseconds> tpMs{tpSeconds};   // implicit - 42000ms, exact
```

```
   seconds  ──implicit──►  milliseconds
      │                          │
   coarser tick             finer tick - going from coarse to fine
                             never loses anything, so it's allowed silently
```

Going the other way needs `time_point_cast<T>()` - the `time_point`
counterpart to `duration_cast`:

```cpp
time_point<steady_clock, milliseconds> tpMs{42'424ms};
auto tpSeconds{time_point_cast<seconds>(tpMs)};   // 42000ms worth - the 424ms are GONE
```

```
   42424ms  ──time_point_cast<seconds>──►  42000ms (i.e. 42s)
                     │
           explicit - you're telling the compiler
           "yes, I know the 424ms remainder gets truncated"
```

`floor()`, `ceil()`, and `round()` work on `time_points` exactly as they
do on durations and on plain numeric values - each rounds to a target
duration granularity instead of just truncating:

```cpp
time_point<steady_clock, milliseconds> tp{2'500ms};
floor<seconds>(tp);   // 2s   - rounds down
ceil<seconds>(tp);    // 3s   - rounds up
round<seconds>(tp);   // 2s   - rounds to nearest (ties to even, like std::round's cousins)
```

### `main7_dates.cpp` - Date: genuine calendar support

C++20 added real calendar dates on top of everything above. Only the
Gregorian calendar ships with the standard, but the design lets other
calendars (Coptic, Julian, ...) interoperate with the rest of `<chrono>`.

**The building-block types**, all in `std::chrono`:

```
   CLASS                     DESCRIPTION
   ──────────────────────────────────────────────────────────────────────────
   year                      a year, range [-32767, 32767]; is_leap() tells you
                             whether it's a leap year; min()/max() bound it
   month                     a month, range [1, 12]; named constants January..December
   day                       a day, range [1, 31]
   weekday                   a day of the week, [0, 6], 0 = Sunday; named
                             constants Sunday..Saturday
   weekday_indexed           the 1st-5th occurrence of a weekday in a month -
                             e.g. Monday[2] = "the second Monday"
   weekday_last              the LAST occurrence of a weekday in a month
   month_day                 a month + day, year unspecified
   month_day_last            the last day of a month, year unspecified
   month_weekday             the nth weekday of a month, year unspecified
   month_weekday_last        the last weekday of a month, year unspecified
   year_month                a year + month
   year_month_day            a full year + month + day
   year_month_day_last       the last day of a specific year and month
   year_month_weekday        the nth weekday of a specific year and month
   year_month_weekday_last   the last weekday of a specific year and month
```

Every one of these has an `ok()` member reporting whether it holds a
valid value. Two literal suffixes help build them: `y` for years, `d` for
days (both in `std::chrono_literals`), and named month/weekday constants
cover the rest:

```cpp
year y1{2020};        auto y2{2020y};    // equivalent
month m1{6};          auto m2{June};     // equivalent
day d1{22};           auto d2{22d};      // equivalent
```

**`operator/` builds full dates**, in any of three natural orders - and
combines with `weekday_indexed`/`last` to build the more exotic forms:

```cpp
year_month_day fulldate1{2020y, June, 22d};
auto fulldate2{2020y / June / 22d};        // Y / M / D
auto fulldate3{22d / June / 2020y};        // D / M / Y

auto thirdMonday{Monday[3] / June / 2020}; // the 3rd Monday of June 2020

auto june22{June / 22d};                   // month_day: "June 22, some year"
auto june22_2020{2020y / june22};          // attach a year → year_month_day

auto lastDayOfAJune{June / last};                    // month_day_last
auto lastDayOfJune2020{2020y / lastDayOfAJune};       // year_month_day_last
auto lastMondayOfJune2020{2020y / June / Monday[last]}; // year_month_weekday_last
```

```
   Monday[3] / June / 2020
       │         │      │
       │         │      └── year 2020
       │         └───────── the month of June
       └─────────────────── weekday_indexed: the 3rd Monday that falls in it

   operator/ reads left-to-right, narrowing what's unspecified at each
   step - "some weekday" → "that weekday in June" → "...of 2020"
```

**Serial vs. field-based: two shapes for the same date.** `year_month_day`
is **field-based** - it stores year, month, and day as three separate
members. `sys_days` is the other shape: a `time_point` of `system_clock`
that just counts whole days since the epoch - a **serial** type:

```cpp
template <typename Duration>
using sys_time = std::chrono::time_point<std::chrono::system_clock, Duration>;
using sys_seconds = sys_time<seconds>;
using sys_days    = sys_time<days>;
```

```
   year_month_day{ 2020y, June, 22d }        sys_days{ 2020y / June / 22d }
        │                                         │
   FIELD-BASED:                               SERIAL:
   3 separate members                         1 number - "day #N since 1970-01-01"
   (year, month, day)
        │                                         │
   easy to read, easy to print                fast to do arithmetic on
   (this is what you WANT to print)           (this is what you WANT to compute with)

   Both name the SAME calendar day - convert between them
   whichever direction the next operation needs.
```

`floor<days>` truncates any `time_point` down to midnight, turning it
into something convertible to `year_month_day` - a `time_point` alone
carries no notion of "which calendar day" until you round it to that
granularity:

```cpp
auto today{floor<days>(system_clock::now())};             // a sys_days
system_clock::time_point t1{sys_days{2020y / June / 22d}}; // year_month_day → time_point
year_month_day yearmonthday{floor<days>(t1)};              // time_point → year_month_day
```

A full date **with** a time-of-day builds up the same way, one duration
at a time:

```cpp
auto t2{sys_days{2020y / June / 22d} + 9h + 35min + 10s};   // 2020-06-22 09:35:10 UTC
```

**Printing dates.** `operator<<` works on streams as usual; `println`/
`format` understand chrono types directly, and the `L` specifier
localizes the output:

```cpp
std::cout << yearmonthday << '\n';
std::println("{:L}", yearmonthday);
```

Watch out: printing a `year_month_weekday_last` prints its **symbolic**
form, not a resolved date - convert through `sys_days` first if you want
the actual calendar date:

```cpp
println("{:L}", lastMondayOfJune2020);                        // "2020/Jun/Mon[last]"
year_month_day resolved{sys_days{lastMondayOfJune2020}};
println("{:L}", resolved);                                    // "2020-06-29"
```

```
   year_month_weekday_last   ──sys_days{...}──►   year_month_day
   "2020/Jun/Mon[last]"       (resolve it)          "2020-06-29"
      (a RULE)                                      (an actual DATE)
```

With the `L` specifier, month and weekday names are localized; `%A`
prints the full weekday name instead of an abbreviation:

```cpp
std::locale::global(std::locale{"nl-NL"});
std::println("Monday in Dutch is {:L%A}", Monday);   // "Monday in Dutch is maandag"
```

**Arithmetic with dates - and a genuine trap.** Adding whole days to a
serial type is always exact:

```cpp
auto t3{t2 + days{5}};   // add exactly 5 days - unambiguous, no surprises
```

But `sys_days` (and any `time_point`) is a **serial** type - underneath,
just a count of days/seconds since an epoch. Adding `years{1}` to it does
**not** mean "same month and day, next year." The standard defines a
chrono year as the *average* Gregorian year - 86,400 × ((365×400)+97)/400
= 31,556,952 seconds (365.2425 days) - so that repeated additions stay
leap-year-correct on average. That average is not a whole number of
days, so a time-of-day component can visibly **drift**:

```cpp
auto t5{sys_days{2020y/June/22d} + 9h + 35min + 10s};   // 2020-06-22 09:35:10
auto t6{t5 + years{1}};                                  // 2021-06-22 15:24:22  <- drifted!
```

```
   t5   2020-06-22 09:35:10
    │
    │  + years{1}  adds 31,556,952 seconds (the AVERAGE year),
    │              not "the same date, next year"
    ▼
   t6   2021-06-22 15:24:22     ← date advanced correctly, but the
                                   TIME OF DAY drifted by nearly 6 hours
```

To add **exactly** one calendar year, convert to the field-based
`year_month_day` first - where "add a year" means exactly that, because
the type has real year/month/day fields - then rebuild the serial
`time_point` from the pieces:

```cpp
sys_days t5_days{time_point_cast<days>(t5)};   // split off the whole-days part
seconds t5_seconds{t5 - t5_days};               // ...and the remaining time-of-day
year_month_day t5_ymd{t5_days};                 // convert to field-based
year_month_day t7_ymd{t5_ymd + years{1}};       // add a YEAR, exactly, field-based
auto t7{sys_days{t7_ymd} + t5_seconds};         // rebuild, time-of-day intact
// t7 = 2021-06-22 09:35:10  <- time of day preserved this time
```

```
   t5  ──split──►  t5_days (whole days)  +  t5_seconds (09:35:10)
                          │
                  year_month_day{t5_days}
                          │
                    + years{1}     ← exact calendar arithmetic, because
                          │            this type has real y/m/d fields
                    sys_days{...}
                          │
                    + t5_seconds   ← re-attach the original time-of-day
                          │
                          ▼
                 2021-06-22 09:35:10
```

**Rule of thumb:** day-granularity arithmetic (`+ days{n}`) on a serial
type is always exact. For year or month arithmetic where the exact
calendar date matters, go through `year_month_day` instead of adding
straight to a serial `time_point`.

### `main8_time_zones.cpp` - Time Zone: wall-clock time, anywhere

The standard library ships a copy of the IANA time zone database
(www.iana.org/time-zones). `get_tzdb()` returns a reference to the single
existing `tzdb` instance; its public `zones` member is a `vector` of every
known `time_zone`:

```cpp
const auto& database{get_tzdb()};
for (const auto& zone : database.zones) {
    println("{}", zone.name());
}
```

Each `time_zone` has a `name()`, and two conversion functions:
`to_local()` (a `sys_time` → the wall-clock `local_time` for that zone)
and `to_sys()` (the reverse). Because of daylight saving time, a
`local_time → sys_time` conversion can be **ambiguous** (the hour repeats
during "fall back") or **nonexistent** (the hour is skipped during
"spring forward") - such cases throw `ambiguous_local_time` or
`nonexistent_local_time`, respectively.

`locate_zone()` looks a zone up by IANA name and throws `runtime_error`
if it isn't found; `current_zone()` returns whatever zone the machine
itself is configured for:

```cpp
auto* brussels{locate_zone("Europe/Brussels")};
auto* gmt{locate_zone("GMT")};
auto* current{current_zone()};
```

**Converting a UTC instant to different zones' wall-clock time:**

```cpp
auto nowUTC{system_clock::now()};                    // always UTC
auto nowInBrussels{brussels->to_local(nowUTC)};       // Brussels' wall-clock time
auto nowInCurrentZone{current->to_local(nowUTC)};     // this machine's wall-clock time
```

```
   system_clock::now()   is ALWAYS UTC - a single, unambiguous instant
              │
              ├──► brussels->to_local(...)   ──►  "11:35" (UTC+2 in June, DST)
              │
              └──► current->to_local(...)    ──►  whatever this machine reads

   One instant in time. Many correct wall-clock spellings of it.
```

**`zoned_time`** goes one step further: it *pairs* a `time_point` with a
`time_zone`, so formatting it prints the correct wall-clock time for that
zone directly, with no manual `to_local()` call needed. Converting
between zones is then just constructing a new `zoned_time` from an
existing one - the underlying UTC instant never changes, only how it's
displayed:

```cpp
zoned_time<seconds> brusselsTime{brussels, local_days{2020y/June/22d} + 9h};
zoned_time<seconds> newYorkTime{"America/New_York", brusselsTime};

println("Brussels: {:L}", brusselsTime.get_local_time());   // 2020-06-22 09:00:00
println("New York: {:L}", newYorkTime.get_local_time());    // 2020-06-22 03:00:00
```

```
   brusselsTime  ──same UTC instant──►  newYorkTime
   09:00 Brussels (UTC+2)               03:00 New York (UTC-4)
        │                                    │
        └──────── both name the SAME MOMENT, just displayed
                  in each zone's own local wall-clock convention
```

> **A note on the Docker student environments.** As of Clang 21, libc++
> does not yet implement the time zone database - `get_tzdb`,
> `locate_zone`, `current_zone`, and `zoned_time` will fail to compile
> there. `main8_time_zones.cpp` builds and runs correctly on MSVC and on
> GCC's libstdc++ (the compiler this course targets); if you are on the
> Clang container, read through this file rather than building it.
> `main1_ratios.cpp` through `main7_dates.cpp` build cleanly everywhere.

---

## 7.11 Files revisited

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

## 7.12 Reading CSV data

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
   7.12ReadingCSV/
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

## 7.13 Regex

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

## 7.14 Project: Titanic dataset analysis

Everything in this chapter comes together on one real dataset: the
Titanic passenger manifest, loaded with the same vendored `rapidcsv`
from 7.12.

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
computed - the same lazy-view idea from 7.6, now filtering out bad data
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

## 7.15 Assignment

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
