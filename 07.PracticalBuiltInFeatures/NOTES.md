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
`std::chrono` for durations/clocks/calendar dates, and pattern matching
with regular expressions.

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

### Raw string literals: when backslashes are getting out of hand

An ordinary string literal treats `\` as the start of an **escape
sequence** - `\n` for a newline, `\t` for a tab, and so on. That means
a literal backslash has to be escaped too, by doubling it, `\\`. A
Windows-style file path is a good example of this getting out of hand
fast:

```cpp
std::string path{"C:\\Users\\Ada\\Documents\\notes.txt"};   // every \ doubled
```

A **raw string literal**, written `R"( ... )"`, turns escaping off
entirely - everything between the parentheses is taken literally,
backslash included:

```cpp
std::string raw_path{R"(C:\Users\Ada\Documents\notes.txt)"};   // no doubling needed
```

```
   ordinary:  "C:\\Users\\Ada\\Documents\\notes.txt"
                   │↑    │↑    │↑
                   each \\ is ONE literal backslash, spelled with two

   raw:       R"(C:\Users\Ada\Documents\notes.txt)"
                 │                                │
                 R"(  starts it, no escaping inside   )"  ends it
```

Both lines above produce the **exact same string** - `R"(...)"` doesn't
change what's stored, only how much escaping you have to type to get
there. It earns its keep anywhere backslashes pile up: file paths,
Windows registry keys, and - as the next lecture will lean on heavily -
regular expression patterns, which use backslashes constantly (`\d`,
`\w`, `\s`, ...).

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
what the timestamp on a log line should read, what today's date is.
**`<chrono>`** is the standard library's time toolkit, and this lecture
covers the three pieces of it you're actually likely to reach for:

```
   DURATIONS    an amount of time            ("90 minutes and 32 seconds")
   CLOCKS       a source of "now"            (steady_clock, system_clock, ...)
   DATES        a genuine calendar day       (year_month_day, since C++20)
```

Everything lives in `<chrono>`, namespace `std::chrono`. Underneath sits
`<ratio>` - the compile-time fraction type chrono uses to describe exactly
how long "one tick" is, for every duration type, with zero runtime cost.
This lecture walks the three pieces in that order, one file per topic -
`main1_ratios.cpp`, `main2_durations.cpp`, and `main3_clocks_and_dates.cpp`
- so each can be built and stepped through on its own.

> `<chrono>`'s calendar support goes further than what's covered here -
> weekday-based dates, time zone conversion (`zoned_time`), and more - see
> the note at the end of this lecture for where to look if you need it.

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
intmax_t quarter_hour_num{std::ratio<1, 4>::num};   // 1
intmax_t quarter_hour_den{std::ratio<1, 4>::den};   // 4
std::println("1/4 = {}/{}", quarter_hour_num, quarter_hour_den);
```

```
   std::ratio<1, 4>
              │  │
              │  └── denominator, a compile-time constant: ::den
              └───── numerator,   a compile-time constant: ::num

   You never write "ratio<1,4> r;" and call member functions on r -
   there IS no object. You only ever read ::num / ::den off the TYPE
   itself, the way you just read quarter_hour_num/quarter_hour_den above.
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

**Naming a ratio with `using`, as soon as you plan to reuse it.** A type
alias changes nothing about how the ratio behaves - it is just a shorter
name for the exact same type. `main1_ratios.cpp` introduces two aliases
right here, before the arithmetic, so the rest of the file can lean on
short names instead of the full `std::ratio<1, 4>` spelling wherever it's
convenient:

```cpp
// (3) Two named ratios, and their sum computed through the aliases.
using quarter_hour = std::ratio<1, 4>;
using third_hour = std::ratio<1, 3>;
using sum_via_aliases = std::ratio_add<quarter_hour, third_hour>::type;
std::println("quarter_hour + third_hour = {}/{}", sum_via_aliases::num, sum_via_aliases::den);
// "quarter_hour + third_hour = 7/12"
```

```
   using quarter_hour = std::ratio<1, 4>;
                │                  │
                │                  └── the actual TYPE - unchanged
                └───────────────────── just a shorter NAME for it

   quarter_hour and std::ratio<1, 4> are the exact same type from here on -
   the alias buys you readability, nothing else.
```

**The four arithmetic operations, spelled out in full.** Because ratios
are types, not objects, you cannot write `ratio<1,4> + ratio<1,3>` - the
library gives you four class templates instead, one per operation, each
computing a *new* `ratio` type through an embedded `::type` alias.
`main1_ratios.cpp` deliberately goes back to the full spelling here
(rather than reusing `quarter_hour`/`third_hour`) so you see both styles
side by side - use whichever reads better at the call site. It runs all
four, back-to-back, against the plain fraction math so you can check
every result by hand:

```cpp
// (4) Addition: a quarter of an hour + a third of an hour.
using sum_type = std::ratio_add<std::ratio<1, 4>, std::ratio<1, 3>>::type;
std::println("1/4 + 1/3 = {}/{}", sum_type::num, sum_type::den);
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
// (5) Subtraction: a half of an hour - a quarter of an hour.
using diff_type = std::ratio_subtract<std::ratio<1, 2>, std::ratio<1, 4>>::type;
std::println("1/2 - 1/4 = {}/{}", diff_type::num, diff_type::den);
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
// (6) Multiplication: a quarter of an hour, times two-thirds.
using product_type = std::ratio_multiply<std::ratio<1, 4>, std::ratio<2, 3>>::type;
std::println("1/4 * 2/3 = {}/{}", product_type::num, product_type::den);
```

```
   1/4 * 2/3  =  (1*2) / (4*3)  =  2/12

   2/12, reduced by gcd(2,12)=2, is 1/6   ──►  ratio_multiply<...>::type
                                                 is the NORMALIZED type ratio<1, 6>
```

```cpp
// (7) Division: a half, divided by a quarter.
using quotient_type = std::ratio_divide<std::ratio<1, 2>, std::ratio<1, 4>>::type;
std::println("(1/2) / (1/4) = {}/{}", quotient_type::num, quotient_type::den);
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
// (8)-(10) Comparing 1/3 against 1/4 - and 1/4 against itself.
std::println("1/3 <  1/4 : {}", (std::ratio_less<std::ratio<1, 3>, std::ratio<1, 4>>::value));
std::println("1/3 >  1/4 : {}", (std::ratio_greater<std::ratio<1, 3>, std::ratio<1, 4>>::value));
std::println("1/4 <= 1/4 : {}", (std::ratio_less_equal<std::ratio<1, 4>, std::ratio<1, 4>>::value));
// false, true, true - exactly what plain fraction math would tell you:
// 1/3 (≈0.333) is bigger than 1/4 (0.25), and 1/4 is certainly <= itself.
```

Because a ratio is a type, you cannot `println("{}", some_ratio)` directly
- you always extract `::num`/`::den` (or, for comparisons, `::value`)
first, exactly as every example above does.

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

A **duration** is an amount of time between two points of time. It's like
saying "5 minutes" or "5000 milliseconds". It's a span of time. C++'s
`std::chrono::duration` type represents a duration as two things:
- a **count**, the number of ticks (e.g. 5)
- a **tick period**, how long each tick is (e.g. 1 second or 1/1000 of a
  second)

So `std::chrono::seconds(5)` is "5 ticks, where each tick is 1 second
long", and `std::chrono::milliseconds(5000)` is "5000 ticks, where each
tick is 1/1000 of a second long". Both represent the same amount of time:
5 seconds.

The library ships one of these types ready-made for every unit you'd
normally reach for:

```cpp
std::chrono::minutes five_minutes{5};
std::chrono::milliseconds five_thousand_ms{5000};
std::chrono::hours two_hours{2};
```

`std::chrono::minutes`, `std::chrono::milliseconds`, and `std::chrono::hours`
are all **duration types** - `nanoseconds`, `microseconds`, `milliseconds`,
`seconds`, `minutes`, `hours`, `days`, `weeks`, `months`, and `years` all
exist, ready to use, no setup required. You can print one directly, add and
subtract them, and compare them:

```cpp
std::chrono::minutes five_minutes{5};
std::println("{}", five_minutes);          // "5min"
std::println("{}", five_minutes.count());  // 5 - the raw number, with the unit stripped off
```

`.count()` is how you get the plain number back out when you need it (for
example, to do your own arithmetic or pass it to an API that just wants an
`int`).

**Durations with different units mix freely.** You don't need to convert
minutes to seconds by hand before adding them - the library does it for
you:

```cpp
using namespace std::chrono_literals;
auto race_duration{90min + 32s};   // 90 minutes and 32 seconds, added directly
std::println("{}", race_duration); // "5432s" - chrono picked a common unit itself
```

```
   90min + 32s
      │      │
      │      └── 32 seconds
      └───────── 90 minutes  =  5400 seconds
                                   │
                              5400 + 32  =  5432 seconds total
```

The `min`, `s`, `h`, `ms`, `us`, `ns` suffixes above are **standard chrono
literals** - they build a duration directly from a numeric literal, no type
name needed. They live in the inline namespace `std::chrono_literals` (also
reachable via `std::literals::chrono_literals`), and are additionally
re-exported directly into `std::chrono` - so `using namespace
std::chrono;` alone is enough to use them.

So far, every duration you've reached for already existed in the library.
That covers the vast majority of real code - but what if you needed a unit
`chrono` doesn't predefine, like "ticks of 60 seconds" or "an amount of
time counted in fractional seconds"? Recall the `std::ratio<Num, Den>` type
from earlier in this lecture - a compile-time fraction. It turns out every
duration type above, `minutes` included, is quietly built the same way
under the hood: a plain number, paired with a `ratio` that says how many
seconds long **one tick** of that number is.

Why use a `std::ratio` instead of just a number like `10` or `1000`? Because that
gives us the ability to represent **fractions** of a second exactly. So we get the 
ability to say "one tick is 1/1000 of a second" (milliseconds) or "one tick is 1/60 of a second" (sixtieths of a second) without losing precision.

One thing worth noting is that if you declare ratio and leave out the denominator,
the denominator defaults to 1. For example, `ratio<60>` is equivalent to `ratio<60, 1>`. 
This is something we are about to use.

```cpp
std::println("{}/{}", std::ratio<60>::num, std::ratio<60>::den);   
// "60/1" - the 1 is really there
std::println("{}", std::ratio_equal<std::ratio<60>, std::ratio<60, 1>>::value);   
// true - identical types
```

With that settled: `minutes` ticks in units of `ratio<60>` (60 seconds per
tick); `milliseconds` ticks in units of `std::milli` (1/1000 of a second
per tick). Once you know that, you can build your own:

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

`std::chrono::minutes` is really nothing more than `duration<some integer
type, ratio<60>>` under a shorter name. Spelling it out yourself lets you
describe a unit the library doesn't name for you:

```cpp
std::chrono::duration<long, std::ratio<60>> d1{123};   // 123 ticks of 60s each = 123 minutes
```

This is a **count** (`123`, the number of ticks - stored as a `long` here)
paired with a **tick period** (`ratio<60>`, how long one tick is - 60
seconds).

We can also represent durations in ticks **faster** than a second, using a
fractional ratio:

```cpp
std::chrono::duration<long, std::ratio<1, 1000>> d1_ms{250};   // 250 ticks of 1/1000s each = 250 milliseconds
```

This is exactly how `std::chrono::milliseconds` is built under the hood -
`ratio<1, 1000>` is the same fraction as the `std::milli` alias from the
`ratio` lecture - you're just spelling it out yourself instead of reaching
for the predefined name.

**Three constructors exist**: default, "from a tick count" (as `d1` and
`d1_ms` above), and "from another duration" - the last one is how
conversions between duration types happen. The default constructor does
**not** zero-initialize when `Rep` is a fundamental type like `long` - the
tick count is left indeterminate, exactly like a bare `long x;`. This is
exactly why this course always brace-initializes: `{}` forces the tick
count to `0`, a bare declaration does not.

```cpp
std::chrono::duration<long, std::ratio<60>> d1_default{};  // brace-init -> 0
std::chrono::duration<long, std::ratio<60>> d1_from_tick_count{123};   // from a tick count
std::chrono::duration<long, std::ratio<60>> d1_copy{d1};   // from another duration
std::println("{} {} {}", d1_default, d1_from_tick_count, d1_copy);   // "0min 123min 123min"
```

**`zero()`, `min()`, and `max()` are static member functions** - they
don't need an existing duration to call them, just the type:

```cpp
std::println("{} {} {}",
    std::chrono::duration<long, std::ratio<60>>::zero(),   // a duration of zero
    std::chrono::duration<long, std::ratio<60>>::min(),    // the smallest value long can represent
    std::chrono::duration<long, std::ratio<60>>::max());   // the largest value long can represent
// "0min -9223372036854775808min 9223372036854775807min"
```

**`floor()`, `ceil()`, and `round()` work on durations exactly as they do
on plain numbers** - rounding `250ms` down/up/nearest to a whole number of
seconds:

```cpp
std::println("{} {} {}",
    std::chrono::floor<std::chrono::seconds>(d1_ms),   // 0s
    std::chrono::ceil<std::chrono::seconds>(d1_ms),    // 1s
    std::chrono::round<std::chrono::seconds>(d1_ms));  // 0s - 250ms is closer to 0s than 1s
```

**So does `abs()`:**

```cpp
std::println("{}", std::chrono::abs(std::chrono::seconds{-5}));   // "5s"
```

**Comparing durations with different tick periods just works** - the
library converts internally:

```cpp
std::chrono::minutes d3{10};   // 10 minutes
std::chrono::seconds d4{14};   // 14 seconds
d3 > d4;                        // true - compared as the same underlying time
```

**Converting between duration types** is where the interesting rules
live. Going from a smaller tick to a bigger tick with a **floating-point**
Rep never loses information, so it stays implicit:

```cpp
std::chrono::duration<long> d7{30};                       // 30 seconds (integral)
std::chrono::duration<double, std::ratio<60>> d8{d7};     // 0.5 minutes - implicit, no data lost
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
std::chrono::duration<long> d7{30};
std::chrono::duration<long, std::ratio<60>> bad{d7};   // Error: possible truncation - refused
                                                         // at compile time, not just at runtime
```

`duration_cast<T>()` is the explicit override, the same spirit as
`static_cast` - it forces the conversion using integer truncation:

```cpp
auto forced{std::chrono::duration_cast<
    std::chrono::duration<long, std::ratio<60>>>(std::chrono::duration<long>{30})};
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
std::chrono::duration<long, std::ratio<60>> d9{10};   // 10 minutes
std::chrono::duration<long> d10{d9};                   // 600 seconds - implicit, exact
```

`std::chrono::duration<long>` here leans on `Period`'s default of
`std::ratio<1>` - it's shorthand for `std::chrono::duration<long,
std::ratio<1>>`, i.e. "ticks in seconds" - the same default-argument
mechanic as
`std::ratio<Num, Den = 1>` from earlier.

**One extra rule applies specifically to the predefined durations** you
started this section with. The standard mandates that types like `minutes`
and `seconds` use **integral** Reps - so, just like the `long`-based
example above, a conversion that *could* produce a fractional result is a
compile-time error, even when the specific numbers involved divide evenly:

```cpp
std::chrono::seconds s{60};
std::chrono::minutes m{s};   // Error - refused even though 60s IS exactly 1 minute;
                              // the compiler only looks at the TYPES, not the value
```

Converting minutes to seconds is always exact (multiplying by an integer
never introduces a fraction), so it stays implicit:

```cpp
std::chrono::minutes m{2};
std::chrono::seconds s{m};   // Ok, implicit - 120s
```

And the `duration_cast` you just saw works just as well on the race-time
example from earlier:

```cpp
using namespace std::chrono_literals;
std::println("{}", std::chrono::duration_cast<std::chrono::seconds>(90min + 32s).count());   // 5432
```

**`hh_mm_ss`** is a small helper type whose only job is to take a single
duration - one number and a unit - and re-slice it into the separate
hours/minutes/seconds fields you'd actually show on a clock or a countdown
timer. It takes any duration and splits it back into display-ready fields -
`hours()`, `minutes()`, `seconds()`, `subseconds()`, all non-negative, plus
`is_negative()`:

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

### `main3_clocks_and_dates.cpp` - Clocks: a source of "now"

There are two different questions you ask about time in everyday
life: "what time is it right now?" and "how long did that just take?".
Those are two different jobs - one wants a wall-clock reading you'd
show a person, the other wants an elapsed amount of time you'd measure with
a stopwatch. C++ gives you a different **clock** for each job.

**Asking "what time is it right now?"** - `std::chrono::system_clock` is
that clock. Its `now()` returns the current `time_point`, and
`std::println`/`std::format` understand a `time_point` directly, using the
same `{:...}` spec grammar from 7.8 - `%` codes replace a type letter like
`f` or `d`:

```cpp
auto now_utc{std::chrono::system_clock::now()};
std::println("UTC: {:%Y-%m-%d %H:%M:%S}", now_utc);
```

**A gotcha worth knowing up front: `system_clock::now()` is always UTC,
never your local time.** Printing it directly, no matter how you format
it, still shows the UTC hour - a student in Nairobi (UTC+3) or New York
(UTC-5) will not see their own wall-clock time from this alone. To get
that, convert the UTC `time_point` to a specific **time zone**:
`current_zone()` asks the OS which zone it's configured for, and
`to_local()` converts a UTC `time_point` to that zone's wall-clock time:

```cpp
auto now_local{std::chrono::current_zone()->to_local(now_utc)};
std::println("Local: {:%Y-%m-%d %H:%M:%S}", now_local);
```

```
   system_clock::now()  is ALWAYS UTC, regardless of formatting
              │
              └──► current_zone()->to_local(...)  ──►  the machine's own
                                                        wall-clock time
```

> **A note on the Docker student environments.** As of Clang 21, libc++
> does not yet implement the IANA time zone database, so `current_zone()`
> will fail to compile there. This works on MSVC and on GCC's libstdc++,
> which is what we build with.

**Locale is a separate axis from time zone - it changes how a time is
written, not which instant or zone is being shown.** Setting a locale
makes formatted output follow the user's own conventions (date order,
month names, ...), and the `L` specifier formats according to whatever 
locale is currently set:

```cpp
std::locale::global(std::locale{""});    // the user's own OS locale
std::println("{:L%c}", now_local);       // %c = locale's own "preferred" format
```

```
   {:L%c}
     │ │
     │ └── %c: the locale's own preferred date+time layout
     └──── L:  use the currently configured GLOBAL locale to format it

   TIME ZONE  answers "which instant, shown in whose wall clock?"
   LOCALE     answers "written in what style?" - independent questions
```

**Asking "how long did that just take?"** - this is a different clock,
`std::chrono::steady_clock`. You take a reading before the work, another
after, and subtract:

```cpp
auto start{std::chrono::steady_clock::now()};
// ... the work being timed ...
auto end{std::chrono::steady_clock::now()};
auto diff{end - start};   // a DURATION, not a time_point - subtracting two
                           // points in time gives you a span between them
std::println("Total: {}", std::chrono::duration_cast<std::chrono::milliseconds>(diff));
```

```
   timeline:   start ────────────── work happens ────────────── end
                 │                                                │
                 └──────────────────  diff = end - start ─────────┘
                                       (a DURATION, not a time_point -
                                        time_point - time_point = duration)
```

Why a *different* clock instead of just reusing `system_clock` for timing
too? Because `system_clock` can be adjusted at any moment - an NTP sync or
a user changing the time could make your "end" reading jump backward or
forward mid-measurement, corrupting the result. `steady_clock` is
guaranteed to never go backward, which is exactly what you want from a
stopwatch.

There is much more to clocks than this, but the rest is rarely needed, 
and it can quickly get complicated. We will cover more as we keep diving 
deep into more C++ advanced topics.

### Dates: putting the calendar to work

**A brief word on `time_point`, since `end - start` above relied on it.**
Every clock's `now()` returns a **`time_point`** - a point in time, stored
internally as a `duration` counted from that clock's own starting point,
called its **epoch**. You'll rarely construct or name a `time_point` type
yourself; what matters day to day is just the arithmetic it supports:

```
   tp + d = tp        tp - d = tp
   tp - tp = d      (two time_points → a duration - "how far apart?")

   tp + tp             ← NOT supported. There's no meaningful
                          answer to "3pm plus 5pm".
```

**Dates: `year_month_day`.** C++20 added real calendar dates on top of
everything above. `operator/` builds a full date in the natural
year/month/day order, using the `y`/`d` literal suffixes and named month
constants:

```cpp
auto some_date{2020y / std::chrono::June / 22d};   // year / month / day
std::println("{:%Y-%m-%d}", some_date);            // "2020-06-22"
```

**Two shapes for the same date.** `year_month_day` is **field-based** - it
stores year, month, and day as three separate members, which is what you
want for reading and printing. `sys_days` is the other shape: a
`time_point` of `system_clock` that just counts whole days since the
epoch - a **serial** type, which is what you want for arithmetic and
comparisons:

```cpp
std::chrono::sys_days as_time_point{some_date};             // date -> time_point
std::chrono::year_month_day back_to_date{as_time_point};    // time_point -> date
```

```
   year_month_day{ 2020y, June, 22d }        sys_days{ 2020y / June / 22d }
        │                                         │
   FIELD-BASED:                               SERIAL:
   3 separate members                         1 number - "day #N since 1970-01-01"
   (year, month, day)
        │                                         │
   easy to read, easy to print                what a time_point actually is -
                                                fast to add/subtract/compare

   Both name the SAME calendar day - convert between them
   whichever direction the next operation needs.
```


**Getting "today"** is the same conversion, starting from `now()`.
`floor<days>` truncates any finer `time_point` down to midnight, which is
what turns a clock reading into a whole calendar day:

```cpp
auto today{std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
std::chrono::year_month_day today_as_date{today};
std::println("Today is {:%Y-%m-%d}", today_as_date);
```

**Date arithmetic.** The common case - adding or subtracting a number of
days - just works directly on the serial `sys_days` form:

```cpp
auto one_week_later{as_time_point + std::chrono::days{7}};
std::println("{:%Y-%m-%d}", std::chrono::year_month_day{one_week_later});
```

A full date **with** a time of day builds up the same way, one duration at
a time - starting from a `sys_days` and adding hours/minutes/seconds
directly onto it:

```cpp
auto meeting_time{std::chrono::sys_days{2020y / std::chrono::June / 22d} + 9h + 35min};
std::println("{:%Y-%m-%d %H:%M}", meeting_time);   // "2020-06-22 09:35"
```

> **Going further.** `<chrono>`'s calendar support goes considerably
> deeper than this - weekday-based dates ("the 3rd Monday of June"), the
> last day/weekday of a month, localized month/weekday names, and time
> zone conversion (`zoned_time`, converting UTC to a specific region's
> wall-clock time) are all there if a project needs them. They're left out
> here because they come up rarely in day-to-day code; please reach for the
> Standard Library reference on `<chrono>` calendar types if you need one
> of them.

---

## 7.11 Regex

*Regular expressions* are a way to describe patterns in text. You
can use them, for example, to check whether a password entered by a
user lives up to a set of security rules like:
- at least 8 characters long
- contains at least one uppercase letter
- contains at least one lowercase letter
- contains at least one number
- contains at least 23 special characters like `!@#$%^&*()_+-=[]{}|;':",./<>?`

The last one is brutal on purpose! But notice the shape of every rule
above: none of them name a specific password - they all describe a
*pattern* the text must fit. That's exactly what a **regular expression**
describes - the *shape* of text, not literal characters. 

`<regex>` gives you four things to do with a pattern:

```
   MATCH     does this WHOLE string fit the pattern?      regex_match
   SEARCH    is the pattern found ANYWHERE inside it?      regex_search
   WALK      find EVERY match, one at a time                sregex_iterator /
                                                              sregex_token_iterator
   REPLACE   rewrite every match in a copy of the string   regex_replace
```

We will explore all these bit by bit. But before we start, let's look at the basic building blocks of a regex pattern. The table below shows some of the most common pieces:

| Pattern piece | Means                          |
|----------------|--------------------------------|
| `\d`           | a single digit                 |
| `\w`           | a single "word" character (letter, digit, `_`) |
| `\s`           | a single whitespace character (space, tab, newline, ...) |
| `[A-Z]`        | one uppercase letter (a range) |
| `[a-z]`        | one lowercase letter (a range) |
| `[...]`        | a **character set** - one character from whatever's inside the brackets |
| `.`            | the **wildcard** - any single character except a newline |
| `^` / `$`      | anchors - "start of string" / "end of string" |
| `()`           | a **capture group** - remembers what matched inside it |
| `+`            | one or more of the preceding piece |
| `*`            | zero or more of the preceding piece |
| `{n}`          | exactly `n` occurrences        |
| `{n,}`         | `n` or more occurrences        |
| `{n,m}`        | between `n` and `m`, inclusive |

### Metacharacters vs. escape sequences: two different `\`'s

Every backslash piece in the table above (`\d`, `\w`, `\s`) is a
**metacharacter** - the *regex engine's own* shorthand for a whole
category of characters. `\d` doesn't mean "a digit" the way a letter
means itself; it's special syntax the regex engine interprets.

A `\t`, `\n`, or `\r` appearing in a pattern is a completely different
thing: an ordinary **C++ string escape**, resolved by the compiler
*before* the regex engine ever sees the string. By the time
`std::regex{"\t"}` runs, C++ has already turned `"\t"` into a string
holding one real tab byte - the regex engine just sees a literal
character to match, the exact same way it would see a literal `a`. It
never even knows a backslash was involved.

| Kind | Examples | Interpreted by | Means |
|------|----------|-----------------|-------|
| **Metacharacter** | `\d`, `\w`, `\s` | the regex engine | a whole *category* of characters |
| **C++ string escape** | `\t`, `\n`, `\r` | the C++ compiler | one specific *literal* character |

```cpp
std::regex{R"(\d)"}   // metacharacter - the regex engine sees "\d" and
                       // treats it as "any digit"

std::regex{"\t"}      // C++ escape - the regex engine never sees a
                       // backslash at all, just one literal tab byte
                       // (same \t you've used in std::println strings)
```

```
   std::regex{R"(\d)"}
                 │
                 ▼
        regex engine receives:  \  d     (two characters, backslash intact -
                                            raw string literal passed it through)
                 │
                 ▼
        regex engine's OWN rule: "\d" means "match any digit"

   std::regex{"\t"}
             │
             ▼
   C++ COMPILER resolves the escape FIRST, before regex ever runs:
             │
             ▼
        regex engine receives:  [tab]   (one real tab character, no backslash)
             │
             ▼
        regex engine's rule: "match this exact character" - nothing special
```

This is exactly why raw string literals matter for the metacharacter
row and not the escape-sequence row: `R"(\d)"` protects the backslash so
the *regex engine* gets to interpret it, while `"\t"` deliberately lets
*C++* consume the backslash first.

Let's put these to test with a few examples, all using `std::regex_match`.
This function checks whether the *entire* string fits the pattern, returning `true` or `false`.

Recall from a previous lecture that `R"( ... )"` around the pattern is 
a **raw string literal** - backslashes inside it are just backslashes, 
not escape sequences, so `\d` can be written exactly as it reads instead of
`"\\d"`. Regex patterns lean on backslashes constantly, so raw string
literals are used for most patterns in this lecture from here on.

```cpp
std::regex_match("7", std::regex{R"(\d)"});          // true  - \d is a single digit
std::regex_match("77", std::regex{R"(\d)"});         // false - \d matches only ONE digit

std::regex_match("_", std::regex{R"(\w)"});          // true  - \w matches letters, digits, AND _
std::regex_match("!", std::regex{R"(\w)"});          // false - punctuation is not a "word" character

std::regex_match("Q", std::regex{"[A-Z]"});          // true  - one letter in the range A-Z
std::regex_match("q", std::regex{"[A-Z]"});          // false - lowercase is outside the range

std::regex_match("q", std::regex{"[a-z]"});          // true  - one letter in the range a-z
std::regex_match("Q", std::regex{"[a-z]"});          // false - uppercase is outside the range

std::regex_match(" ", std::regex{R"(\s)"});          // true  - \s is a single whitespace character
std::regex_match("x", std::regex{R"(\s)"});          // false - "x" is not whitespace

std::regex_match("c", std::regex{"[abc]"});          // true  - [...] matches ONE of the characters inside it
std::regex_match("z", std::regex{"[abc]"});          // false - "z" isn't in the set {a, b, c}
std::regex_match("5", std::regex{R"([\w])"});        // true  - a set can wrap a shorthand too - one \w character
std::regex_match("55", std::regex{R"([\w])"});       // false - still just ONE character, same as \w alone

std::regex_search("cat sat", std::regex{"^cat"});   // true  - "cat" is anchored to the START
std::regex_search("the cat", std::regex{"^cat"});   // false - "cat" isn't at the start here
std::regex_search("the cat", std::regex{"cat$"});   // true  - "cat" is anchored to the END
std::regex_search("cat sat", std::regex{"cat$"});   // false - "cat" isn't at the end here

std::smatch m;
std::regex_search("id-42", m, std::regex{R"(id-(\d+))"});
m[1].str();                                          // "42" - () captured just the digits

std::regex_match("aaa", std::regex{"a+"});           // true  - "+" allows one OR more a's
std::regex_match("", std::regex{"a+"});              // false - "+" needs AT LEAST one

std::regex_match("aaa", std::regex{"a*"});           // true  - "*" allows one OR more a's too
std::regex_match("", std::regex{"a*"});              // true  - but "*" is also happy with ZERO
std::regex_match("b", std::regex{"a*"});             // false - "b" still isn't an "a"

std::regex_match("\t", std::regex{"\t"});            // true  - a C++ escape, matched as ONE literal tab
std::regex_match(" ", std::regex{"\t"});             // false - a space isn't a tab, no matter how alike they look

std::regex_match("a", std::regex{"."});              // true  - "." matches ANY one character
std::regex_match("\n", std::regex{"."});             // false - except a newline, which "." refuses
std::regex_match("", std::regex{"."});               // false - "." still needs exactly ONE character
std::regex_match("hello world!", std::regex{".*"});  // true  - "." + "*" together: "any text at all"

std::regex_match("aaa", std::regex{"a{3}"});         // true  - {3} means EXACTLY three a's
std::regex_match("aa", std::regex{"a{3}"});          // false - only two a's, not exactly three

std::regex_match("aaaaa", std::regex{"a{3,}"});      // true  - {3,} means three OR MORE
std::regex_match("aa", std::regex{"a{3,}"});         // false - fewer than three

std::regex_match("aaaa", std::regex{"a{2,4}"});      // true  - {2,4} means between two and four
std::regex_match("aaaaa", std::regex{"a{2,4}"});     // false - five is one too many
```

### `main1_matching.cpp` - `regex_match`: does the whole string fit?

`regex_match` requires the **entire** string to satisfy the pattern -
one leftover character the pattern doesn't account for is enough to fail:

```cpp
std::regex proper_name{"[A-Z][a-z]+"};
std::regex_match("Wally", proper_name);   // true  - the WHOLE string fits
std::regex_match("E", proper_name);       // false - no lowercase letters follow
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

```
   std::regex zip_code{R"(\d{5})"};   // exactly 5 digits
   std::regex_match("02215",   zip_code)     → true   (exactly 5 digits, nothing more)
   std::regex_match("02215-1", zip_code)     → false  (the "-1" is unaccounted for -
                                                         regex_match needs the WHOLE string)
```

Wrapping part of a pattern in `()` marks a **capture group** - the
matched text behind each group can be pulled back out of a
`std::smatch` afterward, `[1]` for the first group, `[2]` for the
second, and so on. `[0]` is always the entire match:

```
   (\d{4})   /   (\d{1,2})   /   (\d{1,2})
   group 1       group 2         group 3

   "2024   /   6   /   22"
     │         │        │
    m[1]      m[2]     m[3]      m[0] = "2024/6/22" (the whole match)
   "2024"     "6"      "22"
```

`std::stoi` is a built-in function that converts a string into a signed integer. 


```cpp
std::regex date{R"((\d{4})/(\d{1,2})/(\d{1,2}))"};
if (std::smatch m; std::regex_match(input, m, date)) {
    int year{std::stoi(m[1])};
    int month{std::stoi(m[2])};
    int day{std::stoi(m[3])};
}
```

### `main2_searching.cpp` - `regex_search`: find a match anywhere, and find them all

`regex_match` demands the whole string fit. `regex_search` looks for a
match **anywhere** inside it, and captures what it found in a
`std::smatch` the same way `regex_match` does:

```
   regex_match("Programming is fun", regex{"fun"})    → false
                                                          (the WHOLE string
                                                           is not just "fun")

   regex_search("Programming is fun", regex{"fun"})   → true
                                                          (found "fun"
                                                           SOMEWHERE inside)
```

A single `regex_search` call only ever finds the **first** match. To find
every match in a string, search, record what was found, then keep
searching what's left - `match.suffix()` is everything **after** the
match just found:

We are looking for phone numbers. Not just one.

```cpp
std::string contact{"Ada Lovelace, Home: 555-555-1234, Work: 555-555-4321"};
std::regex phone_number{R"(\d{3}-\d{3}-\d{4})"};
std::smatch match;
while (std::regex_search(contact, match, phone_number)) {
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

### `main3_walking_matches.cpp` - walking every match directly

Before getting to regex, let's explore the iteration tools we've already
covered using the `for` loop. Take a plain `std::vector<std::string>`
of names. The most basic way to visit every element is an index-based
`for` loop:

```cpp
std::vector<std::string> names{"Ada", "Grace", "Katherine"};
for (std::size_t i{0}; i < names.size(); ++i) {
    std::println("{}", names[i]);
}
```

A range-based `for` loop used constantly since `std::array` in a few past
lectures hides the index entirely - you just say "for each name in names":

```cpp
for (const auto& name : names) {
    std::println("{}", name);
}
```

What the range-based `for` loop is hiding is an **iterator** - an object
that knows how to move to the next element and how to read the current
one. 

```
   index:      0           1            2
             ┌───────────┬────────────┬─────────────┬╌╌╌╌╌╌╌╌╌╌╌╌┐
   names     │   "Ada"   │  "Grace"   │ "Katherine" ┊    (none)  ┊
             └───────────┴────────────┴─────────────┴╌╌╌╌╌╌╌╌╌╌╌╌┘
                    ▲                                       ▲
              names.begin()                            names.end()
              (points AT the                      (one past the last real
               first element)                       element - a sentinel,
                                                    never read, only compared
                                                              against)
```

`names.begin()` gives you an iterator pointing at the first
element; `names.end()` gives you a special "one past the last element"
iterator that never gets dereferenced (doesn't point to a valid element), 
only compared against. Writing the loop out with iterators directly, 
by hand, looks like this:

```cpp
for (auto it = names.begin(); it != names.end(); ++it) {
    std::println("{}", *it);   // *it reads the element the iterator points at
}
```


```
   it = names.begin()  ──►  *it = "Ada"  ──►  ++it  ──►  *it = "Grace"  ──► ...
                                                                              │
                                        ++it eventually reaches names.end()  ◄┘
                                        (it != names.end() becomes false, loop ends)
```

This begin/`!=`/`++`/`*` pattern is exactly what a range-based `for`
loop has been doing for you invisibly the whole time - and it's exactly
what `std::sregex_iterator` reuses, except instead of walking the
elements of a `vector`, it walks the **matches** of a regex against a
range of text.

`std::sregex_iterator` only really has two constructors worth knowing:

```
   sregex_iterator{}                              the "end" sentinel -
                                                    same role as names.end() above,
                                                    never dereferenced, only compared against

   sregex_iterator{begin, end, regex}              the "start walking here" iterator -
                                                    begin/end mark the range of text to
                                                    search, regex is the pattern to walk matches of
```

A default-constructed `sregex_iterator{}` (no arguments) plays the same
role `names.end()` played above: "one past the last match."

> **Watch out!** The `begin, end, regex` constructor
> only accepts the regex by **reference** - passing a temporary
> `std::regex{...}` directly (instead of a named variable) is a compile
> error, on purpose. The iterator stores a pointer to the regex you gave
> it rather than copying it, and a temporary would be destroyed before
> the iterator finished using it - a dangling pointer waiting to happen.
> This is why `word` above is a named variable declared *before* the
> loop, not `std::sregex_iterator{sentence.cbegin(), sentence.cend(),
> std::regex{R"([\w]+)"}}` inline.

```cpp
std::string sentence{"This is  a test string."};
std::regex word{R"([\w]+)"}; // A collection of 1 or more \w, once we meet a non \w the current word is done.
const std::sregex_iterator end;
for (auto it = std::sregex_iterator{sentence.cbegin(), sentence.cend(), word};
    it != end; ++it) {
    std::println("\"{}\"", (*it)[0].str());
}
```

```
   sentence: "This is  a test string."

   it starts here ──► finds "This" ──► ++it ──► finds "is" ──► ++it ──► ...
                                                                          │
                                        ++it eventually reaches end ◄────┘
                        (the same "keep going until you hit end()" shape
                         a range-based for loop already hides from you)
```

`std::sregex_token_iterator` does the same walk, but hands back the
matched text directly through `->str()` instead of a full `match_results`
object - simpler when the whole match is all you need. 

```cpp
const std::sregex_token_iterator token_end;
   for (auto it = std::sregex_token_iterator{sentence.cbegin(), sentence.cend(), word};
      it != token_end; ++it) {
      std::println("  \"{}\"", it->str());
}
```

Without telling it otherwise, a token iterator only ever yields submatch
`0` - the **whole match** - even against a pattern that has capture
groups. The date pattern below has three, but nothing here pulls them
out individually yet:

```cpp
std::regex date{R"(^(\d{4})/(\d{1,2})/(\d{1,2})$)"};
std::string when{"2024/6/22"};
for (auto it = std::sregex_token_iterator{when.cbegin(), when.cend(), date};
    it != token_end; ++it) {
    std::println("\"{}\"", it->str());   // "2024/6/22" - the whole match, groups ignored
}
```

It can also be pointed at **specific capture groups by index**, instead
of the whole match - passing a `vector<int>` of the indices to walk:

```cpp
std::vector month_and_day{2, 3}; // Only walk index 2 and 3. 
for (auto it = std::sregex_token_iterator{when.cbegin(), when.cend(), date, month_and_day};
    it != token_end; ++it) {
    std::println("\"{}\"", it->str());
}
```

```
   date pattern:  ^(\d{4})/(\d{1,2})/(\d{1,2})$
                    group1   group2    group3

   no index given   →  submatch 0 (the WHOLE match)  →  "2024/6/22"

   {2, 3}  →  "only walk groups 2 and 3, skip group 1 and the whole match"

   "2024/6/22"  →  yields "6", then "22"   (year is never visited)
```

Passing `-1` instead of a capture-group index flips the meaning to
"everything that does **NOT** match" - splitting the string on the
pattern, like a delimiter-based tokenizer.

Every Standard Library container - `std::vector` included - has a
constructor that takes a **begin iterator and an end iterator** and
copies everything in that range into the new container. This isn't
regex-specific; it's the same constructor you'd use to build one
`vector` from a slice of another. Since `sregex_token_iterator` is
itself a begin/end pair (a "start walking here" iterator and the
`sregex_token_iterator{}` sentinel), it plugs directly into that
constructor - no explicit loop needed to collect the tokens:

```cpp
std::vector<std::string> tokens{
    std::sregex_token_iterator{csv.cbegin(), csv.cend(), delimiter, -1},   // begin: walk csv, yield the GAPS
    std::sregex_token_iterator{}};                                        // end: the usual sentinel
```

```
   csv: "This is,  a;test string."
   delimiter pattern: \s*[,;]\s*   (a comma or semicolon, with optional
                                     whitespace hugging either side)

   what the delimiter actually matches (the part -1 THROWS AWAY):

   ┌─────────┬╌╌╌╌╌╌╌┬─────┬╌╌╌╌╌┬───────────────┐
   │ This is ┊,      ┊  a  ┊;    ┊ test string.  │
   └─────────┴╌╌╌╌╌╌╌┴─────┴╌╌╌╌╌┴───────────────┘
                ▲             ▲
           delimiter      delimiter
            match           match
        (",  " - comma    (";" - no
         + 2 spaces)     surrounding space)

   -1 flips it: keep the SOLID boxes, drop the dashed ones -
   "give me the gaps BETWEEN matches", not the matches themselves:

   ┌─────────┐        ┌─────┐       ┌───────────────┐
   │ This is │        │  a  │       │ test string.  │
   └─────────┘        └─────┘       └───────────────┘
     token 1          token 2           token 3
```

### `main4_replacing.cpp` - `regex_replace`: rewrite every match in a copy

Every tool so far has answered a yes/no or "where/what" question: does
this fit the pattern (`regex_match`), is the pattern in there somewhere
(`regex_search`), what are all the places it shows up (the iterators).
`regex_replace` is the first tool that actually **edits text** - "find
this shape, and swap it out for something else," the same everyday task
as a find-and-replace in a text editor, except the "find" part is a
whole pattern instead of one exact word.

```
   find-and-replace in a text editor:      find EXACT text  →  swap in new text

   regex_replace:                          find a SHAPE     →  swap in new text
                                            (any tab, any date, any word, ...)
```

Three things end up mattering once you actually use it, and the rest of
this section walks them in order:

- Does it touch the **original** string?
- Can the replacement text **reuse** pieces of what it just matched?
- What happens to the parts that **didn't** match?

`regex_replace` rewrites every match in a **copy** of the string, leaving
the original untouched - question one, answered:

```cpp
std::string data{"1\t2\t3\t4"};
std::string csv_line{std::regex_replace(data, std::regex{"\t"}, ",")};   // tabs -> commas
```

```
   data:                "1\t2\t3\t4"        (unchanged after the call)
   regex_replace RETURNS a brand new string - it has to be caught, or it's lost:
   csv_line:            "1,2,3,4"           (caught in its own variable, above)
```

Question two: can the replacement reuse pieces of what it just matched?
Yes - the replacement text can reference capture groups with `$1`, `$2`,
and so on. Question three, for now: the *default* mode still copies
through everything that did **not** match, alongside the replaced text:

```cpp
std::regex tags{"<h1>(.*)</h1><p>(.*)</p>"};
std::regex_replace(html, tags, "H1=$1 and P=$2");
```

```
   html: "<body><h1>Header</h1><p>Some text</p></body>"
                └─────┬─────┘  └─────┬──────┘
                      $1=Header      $2=Some text

   default replace: "<body>H1=Header and P=Some text</body>"
                      └─┬─┘                            └──┬──┘
                   copied through untouched      copied through untouched
```

Revisiting question three: `regex_constants::format_no_copy` flips that
default - it drops everything that did **not** match instead of copying
it through, so only the replaced text survives:

```cpp
std::regex_replace(html, tags, replacement, std::regex_constants::format_no_copy);
```

```
   default:         "<body>H1=Header and P=Some text</body>"
   format_no_copy:          "H1=Header and P=Some text"
                      ▲                                  ▲
                 "<body>" and "</body>" are GONE - format_no_copy
                 only keeps what the replacement text produced
```

Combining a capture group with `format_no_copy` turns replace into a
reflow tool: every word becomes "the word, followed by a newline," and
the untouched whitespace between words is dropped instead of being
copied through:

```cpp
std::regex one_word{R"(([\w]+))"};
std::regex_replace(paragraph, one_word, "$1\n", std::regex_constants::format_no_copy);
```

```
   paragraph: "This is a test string."

   default    would keep the original spacing between replaced words
   format_no_copy keeps ONLY "$1\n" for each word - the spaces that
                  matched nothing are thrown away, so the words land
                  one per line:

                  This
                  is
                  a
                  test
                  string
```

---

## 7.12 Assignment

Seven exercises drawing on the whole chapter, on a small dataset.
`main.cpp` has the seven stubbed exercises, each with its problem
statement and a sample run in a comment; `main_solution.cpp` solves all
seven with the statements repeated above each solution. Built as two
executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `grow_readings()` | building a `std::vector` one `push_back` at a time |
| 2 | `warmest_and_coolest()` | sorting a local copy, reference out-parameters, leaving the original untouched |
| 3 | `average_of_hot_days()` | a `views::filter` \| `views::transform` pipeline, `std::accumulate` over a view |
| 4 | `clean_label()` | `find`/`erase`, `find`/`replace` in a loop |
| 5 | `extract_reading()` | parsing one line of text with `std::istringstream` |
| 6 | `format_receipt()` | `std::format`'s fill/align/width/precision spec grammar |
| 7 | `days_until()` | `std::chrono::year_month_day`, `sys_days` conversion, calendar-day arithmetic |

The quiz (`QUIZ.md`) is 18 multiple-choice questions across the whole
chapter, including the format-spec grammar and chrono durations/clocks/
calendar dates.

After this chapter the student can hold, sort, search, and summarize real
collections of data - the last stop before the course turns to pointers
and, from there, to classes.
