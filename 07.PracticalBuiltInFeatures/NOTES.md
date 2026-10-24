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

We show how all this applies to the case when the parameter 
is a **collection** instead of a single `int` or `double`.

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

## 7.5 Sorting, searching,  accumulate and algorithms in general

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

That works, but  there is another paradigm we can use to do the same things. 
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
changes is who supplies the small per-element decision: a **higher-order function** is a 
function that takes another function as an argument (or returns one), and `accumulate`, 
`filter`, and `transform` are all higher-order functions - you hand each one a small 
function (often a lambda) saying what to do with one element, and it owns the looping.

```
   WHAT you state                       WHO supplies the loop
   ───────────────                      ─────────────────────
   accumulate(..., combine)             accumulate's internal iteration
   filter(keep_if)                      the view's internal iteration (We'll see this shortly)
   transform(map_to)                    the view's internal iteration (We'll see this shortly)
```

This is C++'s **functional-style** programming: not a different
language, just a different way to think about your code. What to do? 

- reach for a declarative pipeline first. This involves reading the docs and 
  understanding what the library already provides, and how to express your
  intent in terms of it. 
- drop back down to hand-written loop only when a pipeline cannot say what you mean. 

NOTE: Don't overthink this. You will pick up the best practices as you go.

### Sorting with `std::ranges::sort`

```cpp
using namespace std::string_literals;

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

`sort` with no second argument is shorthand. The comparator it
defaults to is `std::ranges::less`. If  you pass it explicitly,
nothing changes:

```cpp
std::ranges::sort(fruits, std::ranges::less{});   // identical order to sort(fruits)
```

If you pass in `std::ranges::greater`, we will now sort **descending** instead of ascending:

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

These produce the same order as the `less{}`/`greater{}` calls above.

#### A lambda can express a rule `less`/`greater` cannot

Lambdas give us the flexibility to sort by any rule we can express in code. 
For example, we can sort by the length of the fruit names instead of alphabetically:

```cpp
std::ranges::sort(fruits,
                   [](const std::string& a, const std::string& b) {
                       if (a.size() != b.size()) {
                           return a.size() < b.size();   // shorter name first
                       }
                       return a < b;                     // same length: alphabetical
                   });

std::ranges::sort(fruits,
                   [](const std::string& a, const std::string& b) {
                       if (a.size() != b.size()) {
                           return a.size() > b.size();   // longer name first
                       }
                       return a < b;                     // same length: alphabetical
                   });
```

```
   fruits = {mango, kiwi, fig, date, apple}   (lengths: 5, 4, 3, 4, 5)

   sort by .size(), ascending:    fig  date  kiwi  apple  mango
                                    3    4     4      5      5

   sort by .size(), descending:   apple  mango  date  kiwi  fig
                                     5      5     4     4     3
```

Why the extra `return a < b;` line? Some elements are **tied**: `kiwi` and
`date` both have length 4, so on length alone neither belongs before the
other. `std::ranges::sort` makes **no promise** about the order it leaves
tied elements in. On a tiny collection like this one it may happen to keep
their original order, but on bigger data it will shuffle them, and the
result can differ from one compiler to the next. A **tie-break** fixes
that: when the lengths are equal, fall back to a second rule (here,
alphabetical), so the comparator gives a definite answer for every pair
and the final order is always the same. Whenever the order of equal
elements matters to you, put that rule inside the comparator.

This is the real payoff of a lambda comparator: alphabetical order is
only one possible rule, and `sort` does not care which rule you give it
- it just needs something that can say, for any two elements, which one
should come first.

### Searching sorted data with `std::ranges::binary_search`

#### The problem: is this value in the collection?

Say we want to know whether `"kiwi"` is somewhere in `fruits`. The
obvious way is to look at the elements one at a time, from the front,
until we find it or run out. That is what a loop does:

```
   index:    0        1       2      3       4
   fruits:   apple    date    fig    kiwi    mango

   look 1:   index 0: apple?   no
   look 2:   index 1: date?    no
   look 3:   index 2: fig?     no
   look 4:   index 3: kiwi?    YES, found it after 4 looks
```

With 5 fruits, that is nothing. With a million fruits, the unlucky case
is a million looks. There is a much smarter way, and you already know it.

#### The dictionary trick

You want to look up the word "kiwi" in a paper dictionary. You do **not**
start at page 1 and read every word. Instead:

1. Open the dictionary roughly in the **middle**. Say you land on "fig".
2. "kiwi" comes **after** "fig" in the alphabet, so everything from the
   front of the book up to this page is useless. **Throw that half away.**
3. Open the remaining half in its middle and repeat.

Every look throws away **half** of what is left. That is all
**binary search** is ("binary" meaning "two halves"). Now let's do the
same on our fruits.

#### Keeping track of what is left: `low`, `high` and `mid`

Every element in `fruits` has an **index**, its position counting from 0.
To remember which part is still in play, we keep two indexes:

- `low`: the index of the **first** element still in play
- `high`: the index of the **last** element still in play

At the start, everything is in play:

```
   index:       0       1       2       3       4
   fruits:      apple   date    fig     kiwi    mango
                ▲                               ▲
                low                             high
```

So `low` is `0` and `high` is `4`. The middle is the index halfway
between them:

```
   mid = (low + high) / 2
```

This is **integer division**, so any fraction is dropped: `7 / 2` is `3`,
not `3.5`. Each look compares the value we want against `fruits[mid]`,
and there are only three outcomes:

| The value we want is...        | What we do                                                    |
|--------------------------------|---------------------------------------------------------------|
| equal to `fruits[mid]`         | Found it. Stop.                                               |
| **after** `fruits[mid]`        | Throw away `mid` and everything left of it: `low = mid + 1`   |
| **before** `fruits[mid]`       | Throw away `mid` and everything right of it: `high = mid - 1` |

If `low` ever ends up bigger than `high`, nothing is left in play, so
the value is not there.

#### Walkthrough 1: searching for `"kiwi"` (it is there)

```
   index:       0       1       2       3       4
   fruits:      apple   date    fig     kiwi    mango
   looking for: "kiwi"

   look 1:      low                             high
                                mid
```

- `low = 0`, `high = 4`, so `mid = (0 + 4) / 2 = 2`.
- `fruits[2]` is `"fig"`. `"kiwi"` comes **after** `"fig"`, so throw away
  indexes 0 to 2: `low = mid + 1 = 3`.

```
   look 2:                              low     high
                                        mid
```

- `low = 3`, `high = 4`, so `mid = (3 + 4) / 2 = 7 / 2 = 3`.
- `fruits[3]` is `"kiwi"`. **Match. Found!** (2 looks, instead of 4.)

#### Walkthrough 2: searching for `"guava"` (it is not there)

```
   index:       0       1       2       3       4
   fruits:      apple   date    fig     kiwi    mango
   looking for: "guava"

   look 1:      low                             high
                                mid
```

- `mid = (0 + 4) / 2 = 2`. `fruits[2]` is `"fig"`. `"guava"` comes
  **after** `"fig"`, so `low = mid + 1 = 3`.

```
   look 2:                              low     high
                                        mid
```

- `mid = (3 + 4) / 2 = 3`. `fruits[3]` is `"kiwi"`. `"guava"` comes
  **before** `"kiwi"`, so `high = mid - 1 = 2`.

```
   look 3:                      high    low
```

- Now `low` (3) is bigger than `high` (2). Nothing is left in play, so
  `"guava"` is **not** in the collection.

(The standard library's own implementation is organized a little
differently inside, but it follows the same halving idea and gives the
same answers. The `low`/`high`/`mid` version is simply the easiest to
follow by hand.)

#### Why bother? The work barely grows

Each look cuts the leftover pile in half, so even a huge collection
shrinks to nothing after a handful of looks. Here is a collection of 64
elements shrinking:

```
   64 left  →  32  →  16  →  8  →  4  →  2  →  1        about 6 looks
```

And here is the worst case for 64 elements, one bar character per look:

```
   one at a time  │████████████████████████████████████████████████████████████████  64 looks
   halving        │██████                                                              about 6 looks
```

The gap only widens as the collection grows:

```
   elements in collection     one at a time (worst case)     halving (worst case)
   ──────────────────────     ──────────────────────────     ────────────────────
                        8                              8                        3
                    1,000                          1,000                       10
                1,000,000                      1,000,000                       20
            1,000,000,000                  1,000,000,000                       30
```
For a billion elements, a linear scan might take a billion looks in the worst case.
But a binary search would take only about 30 looks.

#### The one rule: the data must be sorted

Go back to the dictionary. Throwing away half of the book only makes
sense because you **know** the words are in alphabetical order. If the
words were in random order, "kiwi comes after fig" would tell you
nothing about which half to discard.

So `binary_search` has one requirement: the data must already be sorted,
**in the order the search assumes**. By default that order is ascending
(`std::ranges::less`), the same default `sort` used.

The code below does exactly this. Sort first, then search:

```cpp
std::ranges::sort(fruits);   // back to alphabetical ascending - fruits was
                              // left sorted by LENGTH, descending, from the
                              // last lambda comparator above; binary_search
                              // assumes alphabetical ascending order

// These two are equivalent.
std::ranges::binary_search(fruits, "kiwi"s);   // true
std::ranges::binary_search(fruits, "kiwi"s, std::ranges::less{}, std::identity{});

std::ranges::binary_search(fruits, "guava"s);  // false
```

`"kiwi"` is in `fruits`, so the first call gives `true`. `"guava"` is not,
so the second gives `false`.

So **binary search** does the work faster than a linear scan, 
but it has a **precondition**: the data must be sorted in the order the search expects.

#### What goes wrong if the data is not sorted the right way

Assume we start with data that is **not** sorted in the expected way (alphabetical, ascending). 
Here is what would happen if we searched it as it was, looking for `"fig"`, which really is in there:

```
   index:       0       1       2       3       4
   fruits:      apple   mango   date    kiwi    fig
   looking for: "fig"

   look 1:      low                             high
                                mid
```

- `mid = (0 + 4) / 2 = 2`. `fruits[2]` is `"date"`. `"fig"` comes
  **after** `"date"` alphabetically, so the search throws away indexes
  0 to 2: `low = mid + 1 = 3`. So far so good: `"fig"` is at index 4,
  in the half that stays.

```
   look 2:                              low     high
                                        mid
```

- `mid = (3 + 4) / 2 = 3`. `fruits[3]` is `"kiwi"`. `"fig"` comes
  **before** `"kiwi"` alphabetically, so the search throws away indexes
  3 to 4: `high = mid - 1 = 2`. But `"fig"` is at index 4, in the half
  that was just thrown away.

```
   look 3:                      high    low
```

- Now `low` (3) is bigger than `high` (2). Nothing is left in play, so
  the search answers `false`, even though `"fig"` is right there.

The search followed its rule faithfully. The data just did not follow
the rule the search relies on.

The nasty part is that this failure is **not reliable**. Depending on
where the halving happens to land, a wrong ordering might report "not
found" for a value that is there, might find the wrong thing, or might
even accidentally succeed. Nothing warns you that the assumption was
violated. A bug that only shows up for *some* searches on *some* data is
much harder to catch in testing than an obvious crash. Sorting back to
alphabetical ascending right before the search, as the code above does,
avoids it. 

NOTE: Before do binary search, always sort the data in the order the search expects.

NOTE: Before you use an algorithm, make sure to carefully read the **preconditions** in the documentation. If you violate them, the algorithm may misbehave in ways that are hard to detect.

### How much work is an algorithm? A first look at complexity

You now know two ways to answer "is `"kiwi"` in this collection?":

```
   one at a time (a loop)         halving (binary_search)
   ──────────────────────         ───────────────────────
   works on any data              needs sorted data
   about n looks, worst case      about log n looks, worst case
```

Which one is "better"? That depends on a question programmers ask all
the time: **when the data gets bigger, how much more work does this need?** 
The tools for answering it are called **algorithm complexity**, and the notation 
is called **Big O**. 

#### Count steps, not seconds

We could time each search with a stopwatch, but seconds depend on the computer, 
the compiler and whatever else is running. 
Instead we **count steps** (looks, comparisons, additions) 
and ask how that count **grows** as the amount of data grows. 
We call the amount of data **`n`**: for `fruits`, `n` is 5.

Here are our two searches again. The horizontal axis is `n`, the number
of elements, growing from 1 to 32. The vertical axis is the number of
looks needed in the worst case. Each `*` is the one-at-a-time search at
that `n`, and each `.` is the halving search at that `n`:

```
 steps
  32 |                                                               *  n = 32: linear needs 32 looks
     |                                                             *
     |                                                           *
     |                                                         *
  28 |                                                       *
     |                                                     *
     |                                                   *
     |                                                 *
  24 |                                               *
     |                                             *
     |                                           *
     |                                         *
  20 |                                       *
     |                                     *
     |                                   *
     |                                 *
  16 |                               *
     |                             *
     |                           *
     |                         *
  12 |                       *
     |                     *
     |                   *
     |                 *
   8 |               *
     |             *
     |           *
     |         *                                   . . . . . . . . . .  n = 32: halving needs about 5 looks
   4 |       *               . . . . . . . . . . .
     |     *     . . . . . .
     |   * . . .
     | * .
   0 | .
     +-----------------------------------------------------------------
       1     4       8      12      16      20      24      28      32    n

   *  one at a time (a loop)
   .  halving (binary search)
```

#### How to read the graph

- **Pick a spot on the bottom axis and read straight up.** At `n = 8`,
  the `*` sits at 8 looks and the `.` sits at about 3. At `n = 32`, the
  `*` is at 32 and the `.` is at about 5.
- **The `*` rises in a straight line.** Every extra element adds one more
  look. Double the data and the work doubles too.
- **The `.` flattens out.** It climbs quickly at first, then crawls along
  nearly level. Double the data and the work grows by just **one** look.

Here are those readings from the graph in a table, so you can watch what
happens each time `n` doubles:

```
   n          4     8     16    32
   *  linear  4     8     16    32     (+4, +8, +16: the gap itself keeps growing)
   .  halving 2     3     4     5      (+1, +1, +1:  one extra look every time)
```

The further right you go, the wider the gap between the two. That gap is
exactly what Big O is about to give us a name for.

#### Big O: the name for the shape of that curve

Big O writes down the **shape** of the growth, using `n` for the amount
of data. We say "O of n" or "order n":

| Big O          | Say it as          | What it means                               | If the data **doubles**          |
|----------------|--------------------|---------------------------------------------|----------------------------------|
| `O(1)`         | constant           | same work, no matter how big the data is    | no change                        |
| `O(log n)`     | logarithmic        | halving the pile each step                  | **one** extra step               |
| `O(n)`         | linear             | touch every element once                    | twice the work                   |
| `O(n log n)`   | "n log n"          | a halving trick repeated for every element  | a bit more than twice the work   |
| `O(n^2)`       | quadratic          | for every element, touch every element again | **four** times the work         |

#### The same ideas as code

```cpp
// O(1): one step, whatever the size of quantities
int first{quantities[0]};

// O(n): one step per element
int total{0};
for (const int& item : quantities) {
    total += item;
}

// O(n^2): for EVERY element, walk over EVERY element again
for (const int& a : quantities) {
    for (const int& b : quantities) {
        std::println("pair: {} and {}", a, b);
    }
}
```

For `quantities = {10, 20, 30, 40}`, so `n = 4`, the nested loop prints
every cell of a 4 x 4 grid, which is 4 x 4 = **16** steps:

```
                 b = 10      b = 20      b = 30      b = 40
   a = 10       (10, 10)    (10, 20)    (10, 30)    (10, 40)
   a = 20       (20, 10)    (20, 20)    (20, 30)    (20, 40)
   a = 30       (30, 10)    (30, 20)    (30, 30)    (30, 40)
   a = 40       (40, 10)    (40, 20)    (40, 30)    (40, 40)

   n = 4   →   4 x 4   =  16 steps
   n = 8   →   8 x 8   =  64 steps      (twice the data, FOUR times the work)
```

#### How fast do these grow? Real numbers

Number of steps for each shape (rounded):

| `n`           | `O(1)` | `O(log n)` | `O(n)`      | `O(n log n)`        | `O(n^2)`                |
|---------------|--------|------------|-------------|---------------------|-------------------------|
| 10            | 1      | 3          | 10          | 33                  | 100                     |
| 100           | 1      | 7          | 100         | 664                 | 10,000                  |
| 1,000         | 1      | 10         | 1,000       | 10,000              | 1,000,000               |
| 1,000,000     | 1      | 20         | 1,000,000   | 20,000,000          | 1,000,000,000,000       |

To feel those numbers, pretend each step takes one nanosecond (a billionth
of a second). For `n = 1,000,000`:

```
   O(1)          1 nanosecond
   O(log n)      20 nanoseconds
   O(n)          1 millisecond            (blink of an eye)
   O(n log n)    20 milliseconds          (still instant)
   O(n^2)        1,000 seconds            (about 17 MINUTES)
```

#### Three rules for reading Big O

1. **Ignore the small stuff.** Big O describes the *shape*, so constants
   and small extras are dropped. Looping over the data twice takes `2n`
   steps, and a loop plus 10 extra steps takes `n + 10`. Both are just
   `O(n)`, because at large `n` the leftover pieces do not change the
   shape of the curve.
2. **It usually describes the unlucky case.** Linear search can get
   lucky and find the value at the very first element (1 look), but the
   unlucky case, the value is last or missing, takes `n` looks. We quote
   the unlucky case because it is the promise we can always keep.
3. **It is about growth, not a stopwatch.** With 5 fruits, any method is
   instant. Big O starts to matter when `n` gets large, or when the code
   runs over and over. Do not reach for a clever algorithm to save
   microseconds on a tiny array.

#### Where you have already met these

| What you have used                                              | Big O          |
|-----------------------------------------------------------------|----------------|
| `array[i]`, `vector[i]`, `.at(i)`, `.size()`                    | `O(1)`         |
| `vector.push_back(x)` (on average*)                             | `O(1)`         |
| `std::ranges::binary_search` (sorted data)                      | `O(log n)`     |
| a loop over every element, `std::accumulate`, a linear search   | `O(n)`         |
| copying a vector, passing a collection **by value**             | `O(n)`         |
| `std::ranges::sort`                                             | `O(n log n)`   |
| a loop inside a loop over the same data                         | `O(n^2)`       |

The "copying is `O(n)`" row is the real reason the earlier rule of thumb
says to pass collections by `const&`: a by-value parameter copies all `n`
elements on **every call**, while a reference is `O(1)`.

#### Putting it to work: is sorting first worth it?

`binary_search` needs sorted data, and sorting is not free: `O(n log n)`.
So should you sort and then binary search, or just loop? Take `n = 1,000,000`:

| Plan                                      | 1 search                   | 1,000 searches                        |
|-------------------------------------------|----------------------------|---------------------------------------|
| loop every time, `O(n)` each              | about 1,000,000 steps      | about 1,000,000,000 steps             |
| sort once, then `O(log n)` each           | about 20,000,000 steps     | 20,000,000 + 1,000 x 20 = about 20,020,000 steps |

For a **single** search, just loop: sorting costs more than it saves. For
**many** searches, sort once and the savings are enormous, here about 50
times fewer steps. Roughly speaking, the sort pays for itself after about
`log n` searches (around 20 here). Without Big O, that is a guess. With it,
it is arithmetic.

NOTE: Don't overthink this. You do not need to memorise the table. What
to take away: 

- **loops over the data** grow in a line, 
- **halving grows** barely at all, and 
- **loops inside loops** grow explosively.

### Folding a range into one value with `std::accumulate`

The `std::accumulate` function takes a range of values and reduces it to 
a single value by combining them with a binary operation. The most common use 
is to sum a range of numbers, but it can be used for other binary operations as well.

The syntax: `std::accumulate(first, last, init, combine)`
*What* you want to do: start from `init`, combine every element in the range `[first, last)` using the `combine` function.

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

In this lecture, we explore C++20's **ranges library** through two declarative
building blocks: **filter** (keep only what matches) and **transform** (map each
value to a new one). 

We will use them in two ways: first **nested**, like any
other function calls, then **piped** with `|`. Seeing both is the best way to
understand what the pipe really is. Here is the big idea:

```cpp
   // the procedural way: one running vector per step

   std::vector<int> evens{};
   for (int x : numbers) {
       if (x % 2 == 0) evens.push_back(x);          // filter, by hand
   }
   std::vector<int> squares{};
   for (int x : evens) {
       squares.push_back(x * x);                     // transform, by hand
   }

   // Utility lambdas to help out
   auto is_even{[](int x) { return x % 2 == 0; }};
   auto square{[](int x) { return x * x; }};

   // the nested way: call the library, hand each result to the next call
   std::views::transform(std::views::filter(numbers, is_even), square)

   // the piped way: the same calls, written in the order they happen
   numbers | std::views::filter(is_even) | std::views::transform(square)
```

In English: take `numbers`, keep only the even ones, then square each of
those that survived the filter. Nothing is computed yet: 
the result **just sits in the air** as a view, waiting for something to iterate it.

### A view does not build a container, it wraps one, lazily

```cpp
auto counted{std::views::iota(1, 11)};   // the integers 1..10, generated lazily
```

```
   std::views::iota(1, 11)

   NOT this (eager, builds the whole thing up front):
      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
      │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 10 │    a real std::vector<int>
      └───┴───┴───┴───┴───┴───┴───┴───┴───┴────┘

   THIS (lazy, a tiny object that knows the RULE):
      counted = "start at 1, stop before 11, +1 each step"
                 no elements exist yet, they are generated as you iterate
```

### `filter` and `transform` are ordinary function calls

Each one is a **higher-order function**, like `accumulate`'s fourth argument:
`filter` takes a lambda that decides *keep or drop*, and `transform` takes a
lambda that decides *how the old value turns into the new value*. You supply
the small decision, the view supplies the iteration.

We name the three lambdas once, so the rest of the lecture is about the shape
of the expressions and not about lambda syntax:

```cpp
auto is_even{[](int x) { return x % 2 == 0; }};
auto square{[](int x) { return x * x; }};
auto above_twenty{[](int x) { return x > 20; }};
```

Now call `filter` the plain way: hand it the range and the predicate, and it
hands you back a view.

```cpp
auto evens{std::views::filter(counted, is_even)};
auto squares{std::views::transform(evens, square)};
```

```
   counted ──filter(is_even)──► evens ──transform(square)──► squares

    1  2  3  4  5  6  7  8  9  10
       │     │     │     │     │
       ▼     ▼     ▼     ▼     ▼
       2     4     6     8     10          (filter kept only these)
       │     │     │     │     │
       ▼     ▼     ▼     ▼     ▼
       4    16    36    64    100          (transform squared each one)
```

Neither call builds a container. `evens` wraps `counted`, and `squares`
wraps `evens`: each is a **view**, a description of a range that produces real
values only when something iterates it.

### Nesting the calls

A call that returns a view returns a **range**, and a range is exactly what
the next call wants as its first argument. So the intermediate names are
optional: put the call inside the call.

```cpp
auto nested{
    std::views::transform(std::views::filter(counted, is_even), square)};
```

```
   std::views::transform( std::views::filter( counted, is_even ), square )
                                              └── step 1 ──┘
                          └────────────── step 2 ───────────────┘

   the innermost call happens first, you read from the inside out
```

With two steps this is still fine. Now add a third one: keep only the even
squares that are above 20.

```cpp
auto nested_deeper{
    std::views::filter(
        std::views::transform(
            std::views::filter(counted, is_even),
            square),
        above_twenty)};
```

It works, and it prints `36 64 100`. But look at what happened to the
reading order: the **first** thing that happens is buried in the middle, the
**last** thing that happens is the first thing you read, and every lambda sits
far away from the call that uses it. Every extra step makes it worse.

### Piping the calls

The pipe fixes exactly that. `range | adaptor(arguments)` means the same as
`adaptor(range, arguments)`, so the pipe is the nesting turned inside out,
written in the order things happen.

```cpp
auto piped{
    counted | std::views::filter(is_even)
            | std::views::transform(square)
            | std::views::filter(above_twenty)};
```

Same views, same values (`36 64 100`), but now each lambda sits right next to
the step it belongs to, and the code reads like the English sentence: take
`counted`, keep the evens, square them, keep those above twenty.

The `|` here is an overloaded operator that the ranges library defines. Chapter
12 shows how you can write one yourself.

**The pattern to remember:** nested reads inside out, piped reads left to
right. They build the same view, so use the pipe whenever there is more than
one step.

### Laziness: nothing runs until you actually iterate

```
   auto piped{ counted | filter(...) | transform(...) | filter(...) };
        │
        └─  at THIS line: nothing has been filtered, nothing squared,
            piped is just a recipe wrapping counted

   for (int x : piped) { ... }
        │
        └─  NOW, one element at a time, as the loop asks for the next
            value: pull from counted → test filter → apply transform →
            test the second filter
```

This is called **lazy evaluation**. `piped` is only iterated by something that
asks for values: a range-based for, `std::accumulate`, or a copy into a
`std::vector`. A view is a range like any other, so `accumulate` works on it
directly:

```cpp
std::accumulate(piped.begin(), piped.end(), 0);   // 36 + 64 + 100 = 200
```

The same pipeline works over a real container, not just a generated sequence
like `iota`. Here it runs over a `std::array<int, 10>` called `numbers`:

```cpp
constexpr std::array numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
auto from_array{
    numbers | std::views::filter(is_even)
            | std::views::transform(square)};
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
Let's look as some more!

### Assignment, concatenation, swap

```cpp
std::string title{"cat"};
std::string subtitle;             // empty string
std::string first{"one"};
std::string second{"two"};

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
const std::string filename{"report_final.pdf"};

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
const std::string log{"noon is 12pm; midnight is not"};

log.find("is");                    // first occurrence, from the front
log.rfind("is");                   // last occurrence
log.find_first_not_of("noon is "); // first character NOT in this set
```

```
   log:  n  o  o  n     i  s     1  2  p  m  ;     m  i  d  n  i  g  h  t     i  s     n  o  t
   idx:  0  1  2  3  4  5  6  7  8  9  10 ...                                 23 24            ...

   log.find("is")     →  5     (first "is": "noon [is] 12pm...")
   log.rfind("is")    →  23    (last "is": "...midnight [is] not")
```

`find_first_not_of` works from the front, skipping every character that is
in the set you give it, and stops at the first one that is not:

```
   log.find_first_not_of("noon is ")      the set: n, o, i, s and the space

   idx:           0  1  2  3  4  5  6  7  8
   char:          n  o  o  n  ␣  i   s  ␣  1          (␣ = a space)
   in the set?    ✓  ✓  ✓  ✓  ✓  ✓  ✓  ✗
                                          ▲
                  skipped, skipped, ...   first character NOT in the set
                                          → returns index 8
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
std::string sentence{"The quick brown fox jumps over the lazy dog"};
std::size_t position{sentence.find(' ')};    // 3: the first space

sentence.erase(19);                          // drop everything from index 19 on
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

```cpp
std::string sentence{"The quick brown fox jumps over the lazy dog"};
sentence.replace(position, 1, "_");          // 1 char at position -> "_"
```

Looping a `find` + `replace` together is the everyday pattern for
"replace every occurrence of X":

```cpp
std::string sentence{"The quick brown fox"};
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
std::string greeting{"Hello, !"};

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
std::string item;
int quantity{};
double price{};

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

An ordinary string literal treats `\` as the start of an **escape sequence**:  
`\n` for a newline, `\t` for a tab, and so on. That means a literal backslash 
has to be escaped too, by doubling it, `\\`. A Windows-style file path is a good 
example of this getting out of hand fast:

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
there. Raw string literals show their value anywhere backslashes pile up: file paths,
Windows registry keys, and regular expression patterns (We'll learn about these in a 
few lectures ahead), which use backslashes constantly (`\d`,`\w`, `\s`, ...).

### Raw string literal vs. `std::string` literal: two different questions

These two names sound alike, and students often mix them up. They answer
**different questions** about a piece of text in your code:

- **Raw string literal or ordinary literal?** This is about the **spelling**: how backslashes
  are treated. `"..."` is ordinary (`\` starts an escape sequence).
  `R"(...)"` is raw (`\` is just a character).

- **`std::string` or not?** This is about the **type** you get. A plain
  literal like `"cat"` is **not** a `std::string`. It is a C-style array
  of characters, `const char[4]` (`c`, `a`, `t` and a hidden end marker).
  Add the `s` suffix, `"cat"s`, and the literal itself becomes a
  `std::string`.

Here are all four combinations in one complete program. They all print
the same characters, because the spelling decides how you type the
backslashes, not what ends up stored:

```cpp
#include <print>
#include <string>

int main() {
    using namespace std::string_literals;   // makes the "s" suffix available

    // C-style literals: the type is const char[N], so we keep them in a const char*
    const char* ordinary{"C:\\Users\\Ada\\notes.txt"};
    const char* raw{R"(C:\Users\Ada\notes.txt)"};

    // std::string literals: the "s" suffix makes the literal itself a std::string
    std::string ordinary_s{"C:\\Users\\Ada\\notes.txt"s};
    std::string raw_s{R"(C:\Users\Ada\notes.txt)"s};

    std::println("{}", ordinary);     // C:\Users\Ada\notes.txt
    std::println("{}", raw);          // C:\Users\Ada\notes.txt
    std::println("{}", ordinary_s);   // C:\Users\Ada\notes.txt
    std::println("{}", raw_s);        // C:\Users\Ada\notes.txt

    return 0;
}
```

The earlier examples, `std::string path{"C:\\Users..."}` and
`std::string raw_path{R"(C:\Users...)"}`, did not need the `s`. A
`std::string` can be built from a C-style literal, so we got a
`std::string` either way.

#### When does the `s` suffix actually matter?

When there is no `std::string` on the left to do the converting for you. 
Here are the two everyday cases, `auto` and `+`:

```cpp
#include <string>

int main() {
    using namespace std::string_literals;

    auto plain{"cat"};     // const char*  - NOT a std::string!
    auto proper{"cat"s};   // std::string

    // auto bad{"cat" + "acomb"};   // error: cannot add two C-style literals
    auto joined{"cat"s + "acomb"};  // OK: std::string + literal gives "catacomb"

    return 0;
}
```

```
   "cat"    →  const char[4]   c  a  t  \0       just characters in memory:
                                                  no .size(), no .find(), no +

   "cat"s   →  std::string     "cat"             the full string type:
                                                  .size(), .find(), .append(), +, ...
```

**Rule of thumb**: 
- pick raw or ordinary by how many backslashes you would have to double. 
- Add `s` when you need a real `std::string` right at that spot** (with `auto`, or before a `+`). 

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

In this lecture, we are going to look at the standard library's time toolkit, `<chrono>`.
It allows us to measure time, get the current time, and work with dates. 
We'll explore the three main pieces: 

```
   DURATIONS    an amount of time            ("90 minutes and 32 seconds")
   CLOCKS       a source of "now"            (steady_clock, system_clock, ...)
   DATES        a genuine calendar day       (year_month_day, since C++20)
```

Let's start by the facilities in place to describe fractions. 

### `std::ratio`: an exact fraction, known at compile time

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

We can use `std::ratio_equal` to check that two different spellings of the same
rational number are indeed the same type.

```cpp
// (2) Two different SPELLINGS, but the exact same type after normalization.
std::println("ratio<2,8> == ratio<1,4>: {}",
              std::ratio_equal<std::ratio<2, 8>, std::ratio<1, 4>>::value);
// "ratio<2,8> == ratio<1,4>: true"
```

**Naming a ratio with `using`** A type
alias changes nothing about how the ratio behaves - it is just a shorter
name for the exact same type. 

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

**The four arithmetic operations.** Because ratios
are types, not objects, you cannot write `ratio<1,4> + ratio<1,3>` - the
library gives you four class templates instead, one per operation, each
computing a *new* `ratio` type through an embedded `::type` alias.

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
values. You can read the answer off the result's `::value` member:

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
(`milliseconds` is a duration ticking in `milli`-second units) 

### Durations: an amount of time, with the unit baked into the type

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
exist, ready to use. You can print one directly, add and
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

The `min`, `s`, `h`, `ms`, `us`, `ns` suffixes above are **standard chrono literals**  
they build a duration directly from a numeric literal, no type
name needed. They live in the inline namespace `std::chrono_literals` (also
reachable via `std::literals::chrono_literals`), and are additionally
re-exported directly into `std::chrono` - so `using namespace std::chrono;` 
alone is enough to use them.

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
ability to say "one tick is 1/1000 of a second" (milliseconds) 
or "one tick is 1/60 of a second" (sixtieths of a second) without losing precision.

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

`std::chrono::minutes` is really nothing more than `duration<some integer type, ratio<60>>` under a shorter name. Spelling it out yourself lets you
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

**Three constructors (ways to build a duration)**: 
- default, 
- "from a tick count" 
- "from another duration" - the last one is how conversions between duration types happen. 

The default constructor does **not** zero-initialize when `Rep` is a fundamental type like `long` - the
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

**`floor()`, `ceil()`, and `round()` work on durations exactly as they do on plain numbers**  
rounding `250ms` down/up/nearest to a whole number of seconds:

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

NOTE: `std::chrono::duration<long>` here leans on `Period`'s default of
`std::ratio<1>` - it's shorthand for `std::chrono::duration<long,
std::ratio<1>>`, i.e. "ticks in seconds" - the same default-argument
mechanic as `std::ratio<Num, Den = 1>` from earlier.

**One extra rule applies specifically to the predefined durations**. 
The standard mandates that types like `minutes`  and `seconds` use **integral** Reps
Just like the `long`-based example above, a conversion that *could* produce a 
fractional result is a compile-time error, even when the specific numbers involved divide evenly:

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

You can use `duration_cast` to force the conversion if inclined.

```cpp
using namespace std::chrono_literals;
std::println("{}", std::chrono::duration_cast<std::chrono::seconds>(90min + 32s).count());   // 5432
```

**`hh_mm_ss`** is a small helper type whose only job is to take a single
duration - one number and a unit - and re-slice it into the separate
hours/minutes/seconds fields you'd actually show on a clock or a countdown
timer. 

It takes any duration and splits it back into display-ready fields -
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

### Clocks and Dates

There are two different questions you ask about time in everyday life: 

- "what time is it right now?" and 
- "how long did that just take?".

Those are two different jobs - one wants a wall-clock reading you'd
show a person, the other wants an elapsed amount of time you'd measure with
a stopwatch. C++ gives you a different **clock** for each job.

**Asking "what time is it right now?"** - `std::chrono::system_clock` is
that clock. Its `now()` returns the current `time_point`, and
`std::println`/`std::format` understand a `time_point` directly, using the
same `{:...}` spec grammar we have seen.

```cpp
auto now_utc{std::chrono::system_clock::now()};
std::println("UTC: {:%Y-%m-%d %H:%M:%S}", now_utc);
```

NOTE: `system_clock::now()` is always UTC, never your local time. 
Printing it directly shows the UTC hour:  a person in Nairobi (UTC+3) or New York
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

Locale is a separate concept from time zone - it changes **how a time is written**, 
not which instant or zone is being shown. Setting a locale
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

`<regex>` gives us four things we can do with a pattern:

```
   MATCH     does this WHOLE string fit the pattern?      regex_match
   SEARCH    is the pattern found ANYWHERE inside it?      regex_search
   WALK      find EVERY match, one at a time                sregex_iterator /
                                                              sregex_token_iterator
   REPLACE   rewrite every match in a copy of the string   regex_replace
```

There is no single "regular expression language". Over the decades, several
regex *grammars* (flavors) have grown up, and they differ in small but
annoying ways: which characters are special, whether `\d` exists, whether
`+` and `|` need a backslash, and so on. The C++ Standard Library lets you
pick from these grammars:

- `ECMAScript`: the flavor of JavaScript (with a few C++ tweaks). Also very
  close to what Perl and Python use.
- `basic`: POSIX Basic Regular Expressions, used by classic tools like `sed`.
- `extended`: POSIX Extended Regular Expressions, used by tools like `egrep`.
- `awk`: the grammar of the POSIX `awk` tool.
- `grep`: like `basic`, but a newline also separates alternatives.
- `egrep`: like `extended`, but a newline also separates alternatives.

**The one C++ uses by default is ECMAScript.** If you write
`std::regex{"\\d+"}` and don't ask for anything else, the pattern is
interpreted as a (slightly modified) ECMAScript regex. That's also why
everything in the table below, with `\d`, `\w`, `\s` and friends, works out of
the box. The POSIX grammars have no `\d`, for example, so a pattern that
works in one grammar may behave differently or fail in another.

If you ever need a different grammar, you can pass it as a second argument to
the `std::regex` constructor, using the flags in `std::regex_constants`:

```cpp
std::regex re{"[0-9]+", std::regex_constants::extended};
```

This is just for your information. In this course we'll stick with the
default ECMAScript grammar, which is what you will most likely meet in real
projects, and it's the one most developers already know from other languages.

We will explore all these bit by bit. But before we start, let's look at the basic 
building blocks of a regex pattern. The table below shows some of the most common pieces:

| Pattern piece  | Means                                                                     |
|----------------|---------------------------------------------------------------------------|
| `\d`           | a single digit                                                            |
| `\w`           | a single text character (letter, digit, `_`)                              |
| `\s`           | a single whitespace character (space, tab, newline, ...)                  |
| `[A-Z]`        | one uppercase letter (a range)                                            |
| `[a-z]`        | one lowercase letter (a range)                                            |
| `[...]`        | a **character set** - one character from whatever's inside the brackets   |
| `.`            | the **wildcard** - any single character except a newline                  |
| `^` / `$`      | anchors - "start of string" / "end of string"                             |
| `()`           | a **capture group** - remembers what matched inside it                    |
| `\|`           | **alternation** - "or": matches what's on its left *or* what's on its     |
|                |     right (`cat\|dog`). To match a literal pipe, put a backslash in       |
|                |     front of it (see `regex_replace` below)                               |
| `+`            | one or more of the preceding piece                                        |
| `*`            | zero or more of the preceding piece                                       |
| `{n}`          | exactly `n` occurrences of the preceding piece                            |
| `{n,}`         | `n` or more occurrences                                                   |
| `{n,m}`        | between `n` and `m`, inclusive                                            |

### Metacharacters vs. escape sequences: two different `\`'s

Every backslash piece in the table above (`\d`, `\w`, `\s`) is a
**metacharacter** - the *regex engine's own* shorthand for a whole
category of characters. 

A `\t`, `\n`, or `\r` appearing in a pattern is a different matter.
These represent an ordinary **C++ string escape**, resolved by the compiler
*before* the regex engine ever sees the string. By the time
`std::regex{"\t"}` runs, C++ has already turned `"\t"` into a string
holding one real tab byte - the regex engine just sees a literal
character to match, the exact same way it would see a literal `a`. It
never even knows a backslash was involved.

| Kind                  | Examples         | Interpreted by   | Means                                |
|-----------------------|------------------|------------------|--------------------------------------|
| **Metacharacter**     | `\d`, `\w`, `\s` | the regex engine | a whole *category* of characters     |
| **C++ string escape** | `\t`, `\n`, `\r` | the C++ compiler | one specific *literal* character     |

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

### `regex_match`: does the whole string fit?

`regex_match` requires the **entire** string to satisfy the pattern -
one leftover character the pattern doesn't account for is enough to fail:

```cpp
std::regex city_name{"[A-Z][a-z]+"};
std::regex_match("Nairobi", city_name);   // true  - the WHOLE string fits
std::regex_match("K", city_name);         // false - no lowercase letters follow
```

```
   pattern:  [A-Z]     [a-z]+
             one       one or more
             CAPITAL   lowercase letters
             letter

   "Nairobi" N  a  i  r  o  b  i
             ▲  └────┬────┘
          [A-Z]  [a-z]+ (6 lowercase letters, "one or more" satisfied)
                                                    → MATCH, true

   "K"       K
             ▲
          [A-Z] matches, but nothing is left for [a-z]+ to match
          (it needs AT LEAST one)                 → NO MATCH, false
```

```cpp
   std::regex invoice_code{R"(\d{5})"};   // exactly 5 digits
   std::regex_match("48213",   invoice_code)   → true   (exactly 5 digits, nothing more)
   std::regex_match("48213-1", invoice_code)   → false  (the "-1" is unaccounted for -
                                                           regex_match needs the WHOLE string)
```

Wrapping part of a pattern in `()` marks a **capture group** - the
matched text behind each group can be pulled back out of a
`std::smatch` afterward, `[1]` for the first group, `[2]` for the
second, and so on. `[0]` is always the entire match:

```
   (\d{4})   /   (\d{1,2})   /   (\d{1,2})
   group 1       group 2         group 3

   "2025   /   3   /   9"
     │         │       │
    m[1]      m[2]     m[3]      m[0] = "2025/3/9" (the whole match)
   "2025"     "3"      "9"
```

`std::stoi` is a built-in function that converts a string into a signed integer. 


```cpp
std::regex ship_date{R"((\d{4})/(\d{1,2})/(\d{1,2}))"};
if (std::smatch m; std::regex_match(input, m, ship_date)) {
    int year{std::stoi(m[1])};
    int month{std::stoi(m[2])};
    int day{std::stoi(m[3])};
}
```

### `regex_search`: find a match anywhere, and find them all

`regex_match` demands the whole string fit. `regex_search` looks for a
match **anywhere** inside it, and captures what it found in a
`std::smatch` the same way `regex_match` does:

```
   regex_match("Debugging is fun", regex{"fun"})    → false
                                                          (the WHOLE string
                                                           is not just "fun")

   regex_search("Debugging is fun", regex{"fun"})   → true
                                                          (found "fun"
                                                           SOMEWHERE inside)
```

A single `regex_search` call only ever finds the **first** match. To find
every match in a string, search, record what was found, then keep
searching what's left - `match.suffix()` is everything **after** the
match just found:

We are looking for ticket IDs. Not just one.

```cpp
std::string ticket{"Grace Hopper, Order: TCK-9001, Follow-up: TCK-9042"};
std::regex ticket_id{R"(TCK-\d{4})"};
std::smatch match;
while (std::regex_search(ticket, match, ticket_id)) {
    std::println("{}", match.str());
    ticket = match.suffix();   // keep searching after this match
}
```

```
   ticket: "Grace Hopper, Order: TCK-9001, Follow-up: TCK-9042"

   search 1:  finds "TCK-9001"
              match.suffix() = ", Follow-up: TCK-9042"   ← everything AFTER the match

   ticket = match.suffix();

   search 2 (on the new, shorter ticket):  finds "TCK-9042"
              match.suffix() = ""

   search 3:  nothing left to find → loop ends
```

### walking every match directly

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

A range-based `for` loop hides the index entirely. You just say "for each name in names":

```cpp
for (const auto& name : names) {
    std::println("{}", name);
}
```

What the range-based `for` loop is hiding is an **iterator**. An object
that knows how to move to the next element and how to read the current one. 

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
> error, on purpose. The reason for that is out of scope for now. So I won't 
> say more about this. Just be aware that you need to name your regex before
> passing it to the iterator. Just we name the regex `item` in the example below. 

```cpp
std::string shopping_list{"eggs milk  bread rice"};
std::regex item{R"([\w]+)"}; // A collection of 1 or more \w, once we meet a non \w the current word is done.
const std::sregex_iterator end;
for (auto it = std::sregex_iterator{shopping_list.cbegin(), shopping_list.cend(), item};
    it != end; ++it) {
    std::println("\"{}\"", (*it)[0].str());
}
```

```
   shopping_list: "eggs milk  bread rice"

   it starts here ──► finds "eggs" ──► ++it ──► finds "milk" ──► ++it ──► ...
                                                                           │
                                        ++it eventually reaches end ◄──────┘
                        (the same "keep going until you hit end()" shape
                         a range-based for loop already hides from you)
```

`std::sregex_token_iterator` does the same walk, but hands back the
matched text directly through `->str()` instead of a full `match_results`
object - simpler when the whole match is all you need. 

```cpp
const std::sregex_token_iterator token_end;
   for (auto it = std::sregex_token_iterator{shopping_list.cbegin(), shopping_list.cend(), item};
      it != token_end; ++it) {
      std::println("  \"{}\"", it->str());
}
```

Without telling it otherwise, a token iterator only ever yields submatch
`0` - the **whole match** - even against a pattern that has capture
groups. The timestamp pattern below has three, but nothing here pulls them
out individually yet:

```cpp
std::regex timestamp{R"(^(\d{1,2}):(\d{1,2}):(\d{1,2})$)"};
std::string logged_at{"14:6:9"};
for (auto it = std::sregex_token_iterator{logged_at.cbegin(), logged_at.cend(), timestamp};
    it != token_end; ++it) {
    std::println("\"{}\"", it->str());   // "14:6:9" - the whole match, groups ignored
}
```

It can also be pointed at **specific capture groups by index**, instead
of the whole match - passing a `vector<int>` of the indices to walk:

```cpp
std::vector hour_and_minute{1, 2}; // Only walk index 1 and 2. 
for (auto it = std::sregex_token_iterator{logged_at.cbegin(), logged_at.cend(), timestamp, hour_and_minute};
    it != token_end; ++it) {
    std::println("\"{}\"", it->str());
}
```

```
   timestamp pattern:  ^(\d{1,2}):(\d{1,2}):(\d{1,2})$
                          group1     group2     group3

   no index given   →  submatch 0 (the WHOLE match)  →  "14:6:9"

   {1, 2}  →  "only walk groups 1 and 2, skip group 3 and the whole match"

   "14:6:9"  →  yields "14", then "6"   (second is never visited)
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
    std::sregex_token_iterator{tags.cbegin(), tags.cend(), delimiter, -1},   // begin: walk tags, yield the GAPS
    std::sregex_token_iterator{}};                                          // end: the usual sentinel
```

```
   tags: "backend,  urgent;needs-review"
   delimiter pattern: \s*[,;]\s*   (a comma or semicolon, with optional
                                     whitespace hugging either side)

   what the delimiter actually matches (the part -1 THROWS AWAY):

   ┌─────────┬╌╌╌╌╌╌╌┬────────┬╌╌╌┬───────────────┐
   │ backend ┊,      ┊ urgent ┊;  ┊ needs-review  │
   └─────────┴╌╌╌╌╌╌╌┴────────┴╌╌╌┴───────────────┘
                ▲                ▲
           delimiter         delimiter
            match              match
        (",  " - comma      (";" - no
         + 2 spaces)       surrounding space)

   -1 flips it: keep the SOLID boxes, drop the dashed ones -
   "give me the gaps BETWEEN matches", not the matches themselves:

   ┌─────────┐        ┌────────┐      ┌───────────────┐
   │ backend │        │ urgent │      │ needs-review  │
   └─────────┘        └────────┘      └───────────────┘
     token 1            token 2           token 3
```

### `regex_replace`: rewrite every match in a copy

The tools so far only *read* text: does it match? (`regex_match`), is the
pattern in there (`regex_search`), where are all the matches (the iterators). 

`regex_replace` is the first one that produces **different text** out of the 
text you already have. As the name implies, it replaces a text **pattern** with some 
other text, and returns the transformed string. You can use it to reformat a record, 
strip markup from text, or reshape a sentence. 

WHAT IT DOES: it takes text in and returns a **new** string.

Here is how a typical call looks:

```
   regex_replace( input_text,  pattern,  replacement )
                       │          │           │
                       │          │           └─ what to write in place of each match
                       │          └─ which parts of the input to rewrite
                       │
                       └─ only read, never modified

                       │
                       ▼
                 returns a NEW std::string
```

#### The general idea

Assuming a call like:

```cpp
   regex_replace( input_text,  pattern,  replacement )
```

Here is the general flow of what happens:

```
   for each match, scanning left to right:
       1. copy the unmatched text between the previous match and this one
       2. write the replacement, with $1, $2, ... filled in after the last match:
       3. copy the remaining tail
```

Every outcome in this section runs the **same procedure**. Learn it once
on a small example, and each outcome below becomes "the same procedure
with one detail changed".

```cpp
std::string input{"cat-7, dog-42, bird"};
std::regex  re{R"((\w+)-(\d+))"};                          // word, dash, number (two capture groups)
std::string result{std::regex_replace(input, re, "DOG")};  // Replace the whole match with the literal text "DOG"
std::string result{std::regex_replace(input, re, "$2:$1")};  // Fiddle with the capture groups: $1 = "cat", $2 = "7"
                                                             // for the first match, etc.
```

**Step 1: find the matches.** The engine scans the input and cuts it into
*matched* pieces and *unmatched* pieces:

```
   input:    c a t - 7 ,   d o g - 4 2 ,   b i r d
             └───┬───┘     └────┬────┘
              match 1        match 2

   match 1:  $1 = "cat"    $2 = "7"
   match 2:  $1 = "dog"    $2 = "42"

   Cut into pieces:

   [ match 1 ][ ", " ][ match 2 ][ ", bird" ]
                  ▲                   ▲
              unmatched           unmatched
              (in between)        (the tail)
```

**Step 2: build the result, left to right.** For every match, two things
happen in order: the unmatched text in front of it is **copied**, then the
**replacement** is written, with `$1`, `$2`, ... filled in from *that*
match's groups. After the last match, the remaining tail is copied.

Here it is on the example, with the replacement `"$2:$1"`:

```
   input:     [cat-7]  ", "  [dog-42]  ", bird"
                 │       │       │         │
                 ▼       ▼       ▼         ▼
             replace   copy    replace   copy
                 │       │       │         │
                 ▼       ▼       ▼         ▼
   result:    [7:cat]  ", "  [42:dog]  ", bird"

   result = "7:cat, 42:dog, bird"
```

```
   input   still "cat-7, dog-42, bird"     <- never modified
   result  "7:cat, 42:dog, bird"            <- the new string that is returned
```

A summary of the two key points to remember about `regex_replace`:

```
   1. the REPLACEMENT STRING     does it contain $1, $2, ... ?

          ","            no $   same literal text written for every match
          "$2:$1"        $n     each match gets its OWN captured pieces
                                  match 1 -> 7:cat
                                  match 2 -> 42:dog

   2. the optional 4th ARGUMENT  (a flag; leaving it out = the default)

          (nothing)           copy steps 1 and 3 run      unmatched text is kept
          format_no_copy      copy steps 1 and 3 SKIPPED  unmatched text is dropped

                 default:         7:cat, 42:dog, bird
                 format_no_copy:  7:cat42:dog
```


#### Example 1: swap a separator (pipes to commas)

You start with a record that uses `|` between fields, and you want the
same record as comma-separated values.

```cpp
std::string data{"apple|3|0.99"};
std::string csv_line{std::regex_replace(data, std::regex{R"(\|)"}, ",")};
```

```
   START                 data      "apple|3|0.99"

   regex_replace(data, \|, ",")    every "|" becomes ","

   END                   csv_line  "apple,3,0.99"      <- the returned string
                         data      "apple|3|0.99"      <- still exactly as it was
```

NOTE: If you don't grab the returned string, nothing happens to the original data:

```
   WRONG - the result is thrown away, data is untouched, nothing happened:

       std::regex_replace(data, std::regex{R"(\|)"}, ",");

   RIGHT - catch the returned string:

       std::string csv_line{std::regex_replace(data, std::regex{R"(\|)"}, ",")};
```

Note the pattern escapes the pipe as `\|`. Recall from the table at the start of this
lecture that `|` is a regex metacharacter (alternation), so matching a *literal* pipe
character requires escaping it.

#### Example 2: rearrange pieces of the match (capture groups in the replacement)

Now the goal is bigger than swapping one character. You start with a
snippet of markup and want to pull the title and summary text out of it
and present them in your own format.

The capture groups `(...)` from earlier lectures don't only *report* what
they matched. The replacement text can *use* them: `$1` is whatever group
1 captured, `$2` is group 2, and so on.

```cpp
std::string article{"<article><title>Launch Day</title><summary>It shipped</summary></article>"};
std::regex markup{"<title>(.*)</title><summary>(.*)</summary>"};
std::string replacement{"TITLE=$1 and SUMMARY=$2"};

std::string default_result{std::regex_replace(article, markup, replacement)};
```

```
   START   article:
           <article><title>Launch Day</title><summary>It shipped</summary></article>
           └───┬───┘└──────────────────────────┬─────────────────────────┘└───┬────┘
            no match            the whole match (pattern markup)           no match
                                              │
                              ┌───────────────┴────────────────┐
                              ▼                                ▼
                        $1 = "Launch Day"              $2 = "It shipped"

   The matched part is replaced by "TITLE=$1 and SUMMARY=$2", with the
   groups filled in:

   END     default_result:
           <article>TITLE=Launch Day and SUMMARY=It shipped</article>
           └───┬───┘└───────────────────┬──────────────────┘└───┬────┘
          copied as-is          the replacement            copied as-is
```

By default everything that did **not** match is carried over into the
result untouched. That is why `<article>` and `</article>` are still
there: the rewrite only touched the part the pattern matched, and the
rest of the string came along for the ride.

#### Example 3: keep only what the replacement produced

Sometimes the surrounding text is exactly what you want to get rid of.
Passing `std::regex_constants::format_no_copy` as a fourth argument
changes the rule for the unmatched parts: **drop** them instead of
copying them.

```cpp
std::string no_copy_result{std::regex_replace(article, markup, replacement,
    std::regex_constants::format_no_copy)};
```

```
   article:         <article><title>Launch Day</title><summary>It shipped</summary></article>

   default:         <article>TITLE=Launch Day and SUMMARY=It shipped</article>
                    └───┬───┘                                       └───┬────┘
                      kept                                            kept

   format_no_copy:           TITLE=Launch Day and SUMMARY=It shipped
                    └───┬───┘                                       └───┬────┘
                     dropped                                        dropped
```

Here is what it all boils down to: 

```
   (no flag)         result = unmatched text  +  replacement(s)
   format_no_copy    result =                    replacement(s)
```

#### Example 4: reflow text, one word per line

In this example, we take a sentence and reformat it so that each word is on its own line.

```cpp
std::string headline{"Regex makes text processing easy"};
std::regex one_word{R"(([\w]+))"};
std::string one_per_line{std::regex_replace(headline, one_word, "$1\n",
    std::regex_constants::format_no_copy)};
```

```
   START   headline:   Regex makes text processing easy
                       └─┬─┘ └─┬─┘ └─┬┘ └───┬────┘ └┬─┘
                         │     │     │      │       │
                       each run of word characters is one match,
                       and the word itself is captured as $1

   Each match is replaced by "$1\n": the word, then a newline.
   The spaces between words match nothing, so format_no_copy drops them.

   END     one_per_line:
                       Regex
                       makes
                       text
                       processing
                       easy
```

Without `format_no_copy` the spaces would be copied through, and every
line after the first would start with a stray space. Dropping the
unmatched text is what makes this come out clean.

---

## 7.12 Project: building by hand

Up to now you have gone through your IDE to build your binaries. In this
project we take the lid off. You will call the 
**compiler and the linker yourself**, on the command line, and then open 
the files they produce to see what is really inside.

We do it for a reason. Sooner or later a build fails with a message like
`undefined reference to ...` or `unresolved external symbol ...`. Those
messages come from the **linker**, not the compiler, and they only make
sense once you have gone down to this level at least once, seen what the
tools do under the hood and looked at what is inside the files they produce.

NOTE: This lecture and the few that follow are unusual in a beginner C++
course. But these ideas widen your view of what the tools do under the
hood, and they give you the insight to switch confidently to another
build tool if **CMake** ever stops meeting your needs.

NOTE: We will meet many tools and commands. You do not have to memorize
them. These notes are yours to come back to. The important thing is to
understand what is happening.

### What happens between source and program

```
   main.cpp ──┐                            ┌── compiler ──► main.o  ──┐
   stats.cpp ─┼── each .cpp on its own ────┼── compiler ──► stats.o ──┼──► linker ──► weather
   report.cpp ┘                            └── compiler ──► report.o ─┘
                                                   (object files)
```

- The **compiler** turns **one `.cpp` file at a time** into 
  an **object file**: machine code for that file, plus a table of names. 
  Each file is compiled in complete ignorance of the others.
- The **linker** takes all the object files, matches every reference to
  a function with the object that defines it, and writes the final
  program.
- What you call on the command line is rarely the compiler or the linker itself. `cl`, `g++`
  and `clang++` are **drivers**: programs that run the compiler, then
  the linker, and pass your options along. That is why one command can
  do both jobs, and why the same command can also do only the first job
  (the `-c` or `/c` flag).

Everything in this project is a variation on those two steps.

### The files you will build

All the source files are in `7.12ProjectManualCompile`.

```
   single.cpp              sums a vector and prints the average (one file, nothing to link against)

   stats.h / stats.cpp     summarize(readings) and to_celsius(f)
   report.h / report.cpp   format_report(sensor, summary), which CALLS to_celsius
   main.cpp                builds the readings, calls both, prints
```

`report.cpp` calls `to_celsius`, which lives in `stats.cpp`. When the
compiler builds `report.cpp` it only sees the declaration in `stats.h`.
It cannot know where the function is, so it leaves a note in the object
file that says "**I need `to_celsius`, fill it in later**". The linker
keeps that promise.

### Pick your environment

The project has **five environments**. I use these environments because they are the 
ones I have available on my system. Do the one you have, and come back for the others 
if you are curious. In each one you will do the same four things:

1. Build `single.cpp` in **two steps** (compile, then link).
2. **Read** what is inside the object files and the finished binary.
3. Build `single.cpp` in **one step**.
4. Build the **multi-file** program, then break it on purpose.

- **Windows, MSVC**
  - Compiler driver: `cl`
  - Linker: `link`
  - Object files: `.obj`
  - Output folder: `out-msvc`
- **Windows, MinGW GCC**
  - Compiler driver: `g++`
  - Linker: `ld` (called by `g++`)
  - Object files: `.o`
  - Output folder: `out-mingw-gcc`
- **Windows, MinGW Clang**
  - Compiler driver: `clang++`
  - Linker: `ld` (called by `clang++`)
  - Object files: `.o`
  - Output folder: `out-mingw-clang`
- **Linux, GCC (Docker)**
  - Compiler driver: `g++`
  - Linker: `ld` (called by `g++`)
  - Object files: `.o`
  - Output folder: `out-linux-gcc`
- **Linux, Clang (Docker)**
  - Compiler driver: `clang++`
  - Linker: `ld` (called by `clang++`)
  - Object files: `.o`
  - Output folder: `out-linux-clang`

Every environment writes **everything it produces** (object files,
programs, even the ones you build to fail) into **its own output folder**.

The starter folder for this project also has one script per environment
(`build-msvc.ps1`, `build-mingw-gcc.ps1`, `build-mingw-clang.ps1`,
`build-linux-gcc.sh`, `build-linux-clang.sh`) that runs the commands of
that environment from top to bottom. 

Type the commands yourself first, and use the scripts to check your work. 
(A script and your own commands fill the same output folder, so delete the 
folder between the two if you want to be sure the script did the work.)

---

### Environment 1: Windows, MSVC

MSVC is Microsoft's C++ compiler, the one Visual Studio uses and the
reference compiler of this course. Our version is `cl` 19.51 (Visual
Studio 2026).

#### Open the shell

Open **Developer PowerShell for VS** from the Start menu. That is an
ordinary PowerShell that already knows where the Microsoft tools are.
(From any other PowerShell you can load it by hand:
`& "<your VS folder>\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64`.)
Then, from the repository root:

```powershell
cd 07.PracticalBuiltInFeatures\7.12ProjectManualCompile
cl
```

`cl` on its own prints a banner. Ours starts with
`Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36260 for x64`.
If you see it, the shell is ready.

#### The tools in this environment

- **`cl`**: the compiler driver. You give it `.cpp` files and options.
  It runs the compiler and, unless you say `/c`, it then runs the linker
  for you.
- **`link`**: the linker. It takes `.obj` files, matches every name a
  file needs with the file that defines it, and writes the `.exe`. We
  call it ourselves in the two-step build.
- **`dumpbin`**: Microsoft's "dump a binary" tool. It reads object
  files, executables and DLLs and prints their headers, their symbol
  tables and the DLLs they depend on. It only reads: it never changes
  the file. We need it because an object file is not text, and this is
  how we look inside.
- **`undname`**: turns a mangled C++ name back into readable C++. We
  need it because the names in an object file look like noise (more on
  that below).

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-msvc
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Single file, two steps

```
   single.cpp ──► compile ──► single.obj ──► link ──► single_two_step.exe
```

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c single.cpp /Fo:out-msvc\
link /nologo out-msvc\single.obj /OUT:out-msvc\single_two_step.exe
.\out-msvc\single_two_step.exe
```

```
average: 70.9 F
```

- `/c` means **compile only, do not link**. That is what produces
  `single.obj`.
- `/std:c++latest` selects the newest language mode. Do **not** write
  `/std:c++23`: `cl` answers
  `Command line warning D9002 : ignoring unknown option '/std:c++23'`,
  compiles in an older mode and then fails with
  `error C2039: 'println': is not a member of 'std'`.
- `/EHsc` turns on normal C++ exception handling. `/W4` asks for more
  warnings. `/nologo` hides the banner.
- `/Fo:out-msvc\` says **which folder** gets the object file. The
  trailing backslash is what tells `cl` it is a folder and not a file
  name.
- `/MD` picks the **shared C runtime**. CMake uses it by default, so we
  use it too. All your objects must agree on this option, otherwise the
  link fails (we talk more about this in a later lecture ).
- The second command has no `.cpp` file at all: `link` only joins
  objects. `/OUT:` names the result, here inside `out-msvc`.

You now have two new files in `out-msvc`: `single.obj` (the object) and
`single_two_step.exe` (the program).

#### 2. Read the object files and the binary

First, make two more small objects to look at: `stats.obj` (which
**defines** `to_celsius`) and `report.obj` (which **uses** it).

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c stats.cpp /Fo:out-msvc\
cl /nologo /std:c++latest /EHsc /MD /W4 /c report.cpp /Fo:out-msvc\
```

**What kind of file is it?**

```powershell
dumpbin /headers out-msvc\stats.obj | Select-String 'File Type|machine'
```

```
File Type: COFF OBJECT
            8664 machine (x64)
```

**COFF** is the object file format on Windows. `8664 machine (x64)` says
the machine code is for 64-bit x86.

**Which names does it define, and which does it need?** A tiny program
still contains **hundreds** of symbols from `std::vector`, `std::format`
and friends, so we filter for our own namespace, `station`:

```powershell
dumpbin /symbols out-msvc\stats.obj | Select-String 'External.*station'
dumpbin /symbols out-msvc\report.obj | Select-String 'UNDEF.*to_celsius'
```

```
049 00000000 SECT4  notype ()    External     | ?to_celsius@station@@YANN@Z (double __cdecl station::to_celsius(double))
04A 00000030 SECT4  notype ()    External     | ?summarize@station@@YA?AUSummary@1@AEBV?$vector@NV?$allocator@N@std@@@std@@@Z (struct station::Summary __cdecl station::summarize(class std::vector<double,class std::allocator<double> > const &))

6FD 00000000 UNDEF  notype ()    External     | ?to_celsius@station@@YANN@Z (double __cdecl station::to_celsius(double))
```

(`dumpbin` wraps long lines at an odd place. We joined them here.) Two
things to see:

- In `stats.obj`, `to_celsius` is **External** and has a section
  (`SECT4`): this object **defines** it.
- In `report.obj`, the same name is **UNDEF**: "undefined here, the
  linker must find it". The linker's whole job is to **match every UNDEF with
  exactly one definition**.

**Name mangling.** You wrote `to_celsius`. The object file says
`?to_celsius@station@@YANN@Z`. That is **name mangling**. C++ allows
several functions with the same name and different parameters
(overloading), but a linker only compares **plain names**.
So the compiler puts the **namespace, the name and the parameter types into the one name** 
it hands to the linker. `undname` reads it back:

```powershell
undname '?to_celsius@station@@YANN@Z'
```

```
Undecoration of :- "?to_celsius@station@@YANN@Z"
is :- "double __cdecl station::to_celsius(double)"
```

(`undname` also prints a copyright banner above that.) Here is the name
taken apart:

| Piece | Meaning |
|---|---|
| `?` | "this is a C++ name" |
| `to_celsius@` | the function name |
| `station@` and then `@` | the enclosing namespace, then the end of the qualification |
| `YA` | a free function (`Y`) using the `__cdecl` calling convention (`A`) |
| `N` | the return type: `double` |
| `N` | the parameter type: `double` |
| `@` then `Z` | end of the parameter list, end of the name |

Do not try to memorise this. The point is that **the parameter types are inside the name**. 
We tried an overload `int to_celsius(int)` and MSVC
named it `?to_celsius@station@@YAHH@Z`: the return type and the
parameter are now `H`, which is `int`. Two different names, so both can
live in one program.

**Now the finished program.** An executable is just another binary with
a table of what it needs.

```powershell
dumpbin /headers out-msvc\single_two_step.exe | Select-String 'File Type|machine|subsystem'
dumpbin /dependents out-msvc\single_two_step.exe
```

```
File Type: EXECUTABLE IMAGE
            8664 machine (x64)
            6.00 subsystem version
               3 subsystem (Windows CUI)
...
  Image has the following dependencies:

    MSVCP140.dll
    KERNEL32.dll
    VCRUNTIME140.dll
    VCRUNTIME140_1.dll
    api-ms-win-crt-runtime-l1-1-0.dll
    ...more api-ms-win-crt-*.dll files...
```

`subsystem (Windows CUI)` means a **console** program. The
**dependencies** are the DLLs Windows loads when the program starts:
`MSVCP140.dll` is the C++ standard library and `VCRUNTIME140*.dll` and
`api-ms-win-crt-*.dll` are the C runtime. That is what `/MD` ("shared
runtime") means. We come back to dependencies in a later lecture.

**The ABI.** Notice that MSVC's objects use COFF, as do MinGW's (next
environments), but **a MSVC object cannot be linked with a MinGW one**.
We tried it: we linked this `stats.obj` with `main.o` and `report.o`
built by MinGW GCC. It fails with
`undefined reference to station::to_celsius(double)` (and
`undefined reference to __security_cookie`, a name MinGW's libraries do
not provide). MinGW asks for the name `_ZN7station10to_celsiusEd`, and
MSVC's object only has `?to_celsius@station@@YANN@Z`. The C++ libraries
behind the two are different too. 

**A C++ library is tied to the compiler and standard library that built it.** 
That agreement about names, layouts and calling conventions is the **ABI** (application
binary interface).

#### 3. Single file, one step

Hand the source file straight to `cl` and let it run both steps:

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 single.cpp /Fo:out-msvc\ /Fe:out-msvc\single_one_step.exe
.\out-msvc\single_one_step.exe
Get-ChildItem out-msvc\single.obj, out-msvc\single_two_step.exe, out-msvc\single_one_step.exe | Format-Table Name, Length -AutoSize
```

``

Look at the sizes again: the object file (about 800 KB) is **bigger**
than the program built from it (about 310 KB). Two lines of
`std::println` and `std::accumulate` pull in a lot of templates, and the
object keeps a copy of every template instan`
average: 70.9 F

Name                Length
----                ------
single.obj          801282
single_two_step.exe 311808
single_one_step.exe 311808
```

`/Fe:` names the executable, and `/Fo:` is the same output-folder option
as before. Both programs have **exactly the same size**. That is the point: `cl` is a driver, it runs the compiler and
then `link` and passes your options along. The one-step form just does
not keep the object file.tiation the file used, plus
the bookkeeping the linker needs. The linker then keeps only what the
program uses. Your numbers will differ. The lesson is that an object
file is **not a small program**, it is a half-finished one.

#### 4. Multiple files

Compile each `.cpp` on its own, then link all three objects together:

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c stats.cpp /Fo:out-msvc\
cl /nologo /std:c++latest /EHsc /MD /W4 /c report.cpp /Fo:out-msvc\
cl /nologo /std:c++latest /EHsc /MD /W4 /c main.cpp /Fo:out-msvc\
link /nologo out-msvc\main.obj out-msvc\stats.obj out-msvc\report.obj /OUT:out-msvc\weather.exe
.\out-msvc\weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

**Break it on purpose.** The best way to understand the linker is to
starve it. Link again, this time **leaving out `stats.obj`**:

```powershell
link /nologo out-msvc\main.obj out-msvc\report.obj /OUT:out-msvc\broken.exe
```

```
main.obj : error LNK2019: unresolved external symbol "struct station::Summary __cdecl station::summarize(class std::vector<double,class std::allocator<double> > const &)" (?summarize@station@@YA?AUSummary@1@AEBV?$vector@NV?$allocator@N@std@@@std@@@Z) referenced in function main
report.obj : error LNK2019: unresolved external symbol "double __cdecl station::to_celsius(double)" (?to_celsius@station@@YANN@Z) referenced in function ... (long text shortened)
out-msvc\broken.exe : fatal error LNK1120: 2 unresolved externals
```

Read that with fresh eyes. Every `.cpp` compiled without complaint. The
error is that two promises ("someone defines `summarize`", "someone
defines `to_celsius`") were never kept. And look: the odd-looking text
in parentheses is the mangled name from the table above, the very one
that was UNDEF in `report.obj`. Whenever you see `LNK2019`, ask: **did I
forget to compile or link the file that defines it?**

When you want to start over, or try another environment, delete the
folder: `Remove-Item -Recurse out-msvc`. Nothing else was touched.

That is MSVC done.

---

### Environment 2: Windows, MinGW GCC

**MinGW-w64** brings the GNU tool chain (GCC, binutils) to Windows. The
programs it makes are ordinary Windows programs. Ours is a UCRT build by
Brecht Sanders: `g++ --version` says
`g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r2) 14.2.0`.


The steps:

1. Build `single.cpp` in **two steps** (compile, then link).
2. **Read** what is inside the object files and the finished binary.
3. Build `single.cpp` in **one step**.
4. Build the **multi-file** program, then break it on purpose.

#### Open the shell

Open a normal PowerShell and put `C:\mingw64\bin` on the PATH **for this
window**, then go to the folder (from the repository root):

```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
cd 07.PracticalBuiltInFeatures\7.12ProjectManualCompile
g++ --version
```

If you see a version banner, you are ready.

#### The tools in this environment

- **`g++`**: the GCC compiler driver. You give it `.cpp` files and
  options. It runs the compiler and, unless you say `-c`, then runs the
  linker for you.
- **`ld`**: the GNU linker. You will not usually type it: `g++` calls
  it. But the linker errors you get come from `ld.exe`, and you will see
  its name in them.
- **`-lstdc++exp`**: not a program but a library option (`-l` means
  "link this library"). On our MinGW GCC 14, `std::println` needs this
  extra library ("the experimental part of the C++ library").
- **`nm`**: lists the **symbol table** of an object file: every name it
  defines or needs. We need it to see what the linker sees.
- **`objdump`**: prints information about object files and executables:
  format, architecture, and (with `-p`) which DLLs a program needs.
- **`c++filt`**: turns a mangled C++ name back into readable C++.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-mingw-gcc
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Single file, two steps

```
   single.cpp ──► compile ──► single.o ──► link ──► single_two_step.exe
```

```powershell
g++ -std=c++23 -Wall -Wextra -c single.cpp -o out-mingw-gcc/single.o
g++ out-mingw-gcc/single.o -o out-mingw-gcc/single_two_step.exe -lstdc++exp
./out-mingw-gcc/single_two_step.exe
```

```
average: 70.9 F
```

- `-c` means **compile only, do not link**. That is what produces
  `single.o`.
- `-std=c++23` selects the language mode. `-Wall -Wextra` ask for more
  warnings.
- `-o` names the output file. We put it inside `out-mingw-gcc`, so your
  source folder stays clean.
- The second command has no `.cpp` file at all: `g++` is being used as a
  **front end for the linker**.

> **Gotcha, MinGW only: `-lstdc++exp`.** Leave it out and the link
> fails:
>
> ```powershell
> g++ out-mingw-gcc/single.o -o out-mingw-gcc/nolib.exe
> ```
>
> ```
> ...ld.exe: out-mingw-gcc/single.o:single.cpp:(.text$...): undefined reference to `std::__open_terminal(_iobuf*)'
> ...ld.exe: out-mingw-gcc/single.o:single.cpp:(.text$...): undefined reference to `std::__write_to_terminal(void*, std::span<char, 18446744073709551615ull>)'
> collect2.exe: error: ld returned 1 exit status
> ```
>
> (Long paths and symbol names shortened with `...`.) Notice that the
> message is about **missing names**, not syntax: your code compiled
> fine. This is a **linker** error, and it comes from `ld.exe`. The
> library has to come **after** the objects that need it. Newer
> compilers, like the GCC 16 in our Linux container, do not need it.

#### 2. Read the object files and the binary

First, make two more small objects to look at: `stats.o` (which
**defines** `to_celsius`) and `report.o` (which **uses** it).

```powershell
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-gcc/stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-gcc/report.o
```

**What kind of file is it?**

```powershell
objdump -f out-mingw-gcc/stats.o
```

```
out-mingw-gcc/stats.o:     file format pe-x86-64
architecture: i386:x86-64, flags 0x00000039:
HAS_RELOC, HAS_DEBUG, HAS_SYMS, HAS_LOCALS
start address 0x0000000000000000
```

`pe-x86-64` is the Windows object format (**COFF**, in the PE family)
for 64-bit x86.

**Which names does it define, and which does it need?** A tiny program
still contains **hundreds** of symbols from `std::vector`, `std::format`
and friends, so we filter for our own namespace, `station`:

```powershell
nm out-mingw-gcc/stats.o | Select-String station
nm -C out-mingw-gcc/stats.o | Select-String station
nm out-mingw-gcc/report.o | Select-String to_celsius
```

```
0000000000000000 T _ZN7station10to_celsiusEd
0000000000000038 T _ZN7station9summarizeERKSt6vectorIdSaIdEE

0000000000000000 T station::to_celsius(double)
0000000000000038 T station::summarize(std::vector<double, std::allocator<double> > const&)

                 U _ZN7station10to_celsiusEd
```

(The blank lines are only here to separate the three commands.) `nm`
marks each symbol with a letter. **`T`** = defined, in the code ("text")
section. **`U`** = undefined here: the linker must find it. In
`stats.o`, `to_celsius` is `T`: this object **defines** it. In
`report.o`, the same name is `U`: that is the note from the start of the
lecture, made visible. The linker's whole job is to **match every `U`
with exactly one `T`**. The `-C` flag ("demangle") prints the C++ name
instead of the code.

**Name mangling.** You wrote `to_celsius`. The object file says
`_ZN7station10to_celsiusEd`. That is **name mangling**. C++ allows
several functions with the same name and different parameters
(overloading, lecture 6.9), but a linker only compares **plain names**.
So the compiler puts the **namespace, the name and the parameter types
into the one name** it hands to the linker. `c++filt` reads it back:

```powershell
c++filt _ZN7station10to_celsiusEd
```

```
station::to_celsius(double)
```

GCC uses the "Itanium" rules. Here is the name taken apart:

| Piece | Meaning |
|---|---|
| `_Z` | "this is a C++ name" |
| `N` ... `E` | a **qualified** name, `namespace::function`, from `N` to `E` |
| `7station` | a name that is 7 letters long: `station` |
| `10to_celsius` | a name that is 10 letters long: `to_celsius` |
| `d` | the parameter type: `d` means `double` |

Do not try to memorise this. The point is that **the parameter types are
inside the name**. We tried an overload `int to_celsius(int)` and GCC
named it `_ZN7station10to_celsiusEi`: the `d` became an `i`, which is
`int`. Two different names, so both can live in one program.

**Now the finished program.** An executable is just another binary with
a table of what it needs.

```powershell
objdump -f out-mingw-gcc/single_two_step.exe
objdump -p out-mingw-gcc/single_two_step.exe | Select-String 'DLL Name'
```

```
out-mingw-gcc/single_two_step.exe:     file format pei-x86-64
architecture: i386:x86-64, flags 0x0000013b:
HAS_RELOC, EXEC_P, HAS_DEBUG, HAS_SYMS, HAS_LOCALS, D_PAGED
start address 0x0000000140001125

	DLL Name: libgcc_s_seh-1.dll
	DLL Name: libstdc++-6.dll
	DLL Name: KERNEL32.dll
	DLL Name: api-ms-win-crt-environment-l1-1-0.dll
	...more api-ms-win-crt-*.dll files...
```

`pei-x86-64` is a finished Windows program (**PE**, with the `i` for
"image"). The **DLL Name** lines are the DLLs Windows loads when the
program starts. Two of them, `libstdc++-6.dll` and `libgcc_s_seh-1.dll`,
live in `C:\mingw64\bin`. That is a real consequence: we ran our
`weather.exe` from a window where `C:\mingw64\bin` was **not** on the
PATH, and Windows refused to start it (exit code `-1073741515`, which
means "a DLL was not found"). We come back to dependencies in 7.14.

**The ABI.** MinGW's objects and MSVC's objects are both COFF, but
**they cannot be mixed**. We tried it: we linked `main.o` and `report.o`
built here with an `stats.obj` built by MSVC. It failed with
`undefined reference to station::to_celsius(double)` and
`undefined reference to __security_cookie`. MinGW asks for
`_ZN7station10to_celsiusEd`, and the MSVC object only has
`?to_celsius@station@@YANN@Z`. The C++ libraries behind the two are
different too. **A C++ library is tied to the compiler and standard
library that built it.** That agreement about names, layouts and calling
conventions is the **ABI** (application binary interface). In 7.14 you
will see why it matters for libraries.

#### 3. Single file, one step

Hand the source file straight to `g++` and let it run both steps:

```powershell
g++ -std=c++23 -Wall -Wextra single.cpp -o out-mingw-gcc/single_one_step.exe -lstdc++exp
./out-mingw-gcc/single_one_step.exe
Get-ChildItem out-mingw-gcc/single.o, out-mingw-gcc/single_two_step.exe, out-mingw-gcc/single_one_step.exe | Format-Table Name, Length -AutoSize
```

```
average: 70.9 F

Name                Length
----                ------
single.o            706568
single_two_step.exe 513682
single_one_step.exe 513682
```

Both programs have **exactly the same size**. That is the point: `g++`
is a driver, it runs the compiler and then the linker and passes your
options along. The one-step form just does not keep the object file.

Look at the sizes again: the object file (about 700 KB) is **bigger**
than the program built from it (about 510 KB). Two lines of
`std::println` and `std::accumulate` pull in a lot of templates, and the
object keeps a copy of every template instantiation the file used, plus
the bookkeeping the linker needs. The linker then keeps only what the
program uses. Your numbers will differ. The lesson is that an object
file is **not a small program**, it is a half-finished one.

#### 4. Multiple files

Compile each `.cpp` on its own, then link all three objects together:

```powershell
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-gcc/stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-gcc/report.o
g++ -std=c++23 -Wall -Wextra -c main.cpp -o out-mingw-gcc/main.o
g++ out-mingw-gcc/main.o out-mingw-gcc/stats.o out-mingw-gcc/report.o -o out-mingw-gcc/weather.exe -lstdc++exp
./out-mingw-gcc/weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

**Break it on purpose.** The best way to understand the linker is to
starve it. Link again, this time **leaving out `stats.o`**:

```powershell
g++ out-mingw-gcc/main.o out-mingw-gcc/report.o -o out-mingw-gcc/broken.exe -lstdc++exp
```

```
...ld.exe: out-mingw-gcc/main.o:main.cpp:(.text+0x68): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
...ld.exe: out-mingw-gcc/report.o:report.cpp:(.text+0x35): undefined reference to `station::to_celsius(double)'
...ld.exe: out-mingw-gcc/report.o:report.cpp:(.text+0x50): undefined reference to `station::to_celsius(double)'
...ld.exe: out-mingw-gcc/report.o:report.cpp:(.text+0x6a): undefined reference to `station::to_celsius(double)'
collect2.exe: error: ld returned 1 exit status
```

(The long path in front of each line is shortened to `...`.) Read that
with fresh eyes. Every `.cpp` compiled without complaint. The error is
that two promises ("someone defines `summarize`", "someone defines
`to_celsius`") were never kept. One line per place that asked:
`report.o` asks for `to_celsius` three times. Whenever you see
`undefined reference`, ask: **did I forget to compile or link the file
that defines it?** (And did I put `-lstdc++exp` after the objects?)

When you want to start over, or try another environment, delete the
folder: `Remove-Item -Recurse out-mingw-gcc`. Nothing else was touched.

That is MinGW GCC done.

---

### Environment 3: Windows, MinGW Clang

**MinGW-w64** brings the GNU tool chain to Windows, and its package also
contains the **Clang** compiler. The programs it makes are ordinary
Windows programs. Clang here uses MinGW's libstdc++ (the one of GCC 16.2)
and, for the final link, LLVM's own linker **lld**.
Ours is a UCRT build by Brecht Sanders in `C:\mingw64`:
`clang++ --version` says `clang version 23.1.3` and
`Target: x86_64-w64-windows-gnu`.

The steps:

1. Build `single.cpp` in **two steps** (compile, then link).
2. **Read** what is inside the object files and the finished binary.
3. Build `single.cpp` in **one step**.
4. Build the **multi-file** program, then break it on purpose.

#### Open the shell

Open a normal PowerShell and put `C:\mingw64\bin` on the PATH **for this
window**, then go to the folder (from the repository root):

```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
cd 07.PracticalBuiltInFeatures\7.12ProjectManualCompile
clang++ --version
```

If you see a version banner, you are ready.

#### The tools in this environment

- **`clang++`**: the Clang compiler driver. You give it `.cpp` files and
  options. It runs the compiler and, unless you say `-c`, then runs the
  linker for you.
- **`lld`**: the LLVM linker (`ld.lld`). You will not usually type it:
  `clang++` calls it when you add **`-fuse-ld=lld`** ("use lld as the
  linker"). The linker errors you get come from `ld.lld`, and you will
  see its name in them. The GNU linker `ld` is installed too, and it is
  what `clang++` would pick on its own. We will see why we do not let it.
- **`-lstdc++exp`**: not a program but a library option (`-l` means
  "link this library"). On MinGW, `std::println` needs this extra
  library ("the experimental part of the C++ library").
- **`nm`**: lists the **symbol table** of an object file: every name it
  defines or needs. We need it to see what the linker sees.
- **`objdump`**: prints information about object files and executables:
  format, architecture, and (with `-p`) which DLLs a program needs.
- **`c++filt`**: turns a mangled C++ name back into readable C++.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-mingw-clang
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Single file, two steps

```
   single.cpp ──► compile ──► single.o ──► link ──► single_two_step.exe
```

```powershell
clang++ -std=c++23 -Wall -Wextra -c single.cpp -o out-mingw-clang/single.o
clang++ out-mingw-clang/single.o -o out-mingw-clang/single_two_step.exe -fuse-ld=lld -lstdc++exp
./out-mingw-clang/single_two_step.exe
```

```
average: 70.9 F
```

- `-c` means **compile only, do not link**. That is what produces
  `single.o`.
- `-std=c++23` selects the language mode. `-Wall -Wextra` ask for more
  warnings.
- `-o` names the output file. We put it inside `out-mingw-clang`, so your
  source folder stays clean.
- The second command has no `.cpp` file at all: `clang++` is being used
  as a **front end for the linker**.
- `-fuse-ld=lld` and `-lstdc++exp` are the two MinGW extras, explained in
  the box below. Both belong to the **link** command only.

> **Gotcha, MinGW Clang: two link options.** `std::println` needs
> `-lstdc++exp`, and Clang must link with lld. Each one has its own
> symptom when missing.
>
> **Leave out `-lstdc++exp`** and the link fails:
>
> ```powershell
> clang++ out-mingw-clang/single.o -o out-mingw-clang/nolib.exe -fuse-ld=lld
> ```
>
> ```
> ld.lld: error: undefined symbol: std::__open_terminal(_iobuf*)
> >>> referenced by out-mingw-clang/single.o:(std::vprint_unicode(...))
> ld.lld: error: undefined symbol: std::__write_to_terminal(void*, std::span<char, 18446744073709551615ull>)
> >>> referenced by out-mingw-clang/single.o:(std::vprint_unicode(...))
> clang++: error: linker command failed with exit code 1 (use -v to see invocation)
> ```
>
> (Long lines shortened with `...`.) The message is about **missing
> names**, not syntax: your code compiled fine. This is a **linker**
> error. (With the GNU linker the library has to come **after** the
> objects that need it. lld is more forgiving and accepts any order, but
> put it last anyway, so the same line works with both linkers.)
>
> **Leave out `-fuse-ld=lld`** and `clang++` uses the GNU linker `ld`,
> which prints a wall of text:
>
> ```powershell
> clang++ out-mingw-clang/single.o -o out-mingw-clang/nold.exe -lstdc++exp
> ```
>
> ```
> C:/mingw64/lib/libstdc++exp.a(print.o): duplicate section `.rdata$_ZTSSt9exception[_ZTSSt9exception]' has different size
> C:/mingw64/lib/libstdc++exp.a(print.o): duplicate section `.rdata$_ZTSSt13runtime_error[_ZTSSt13runtime_error]' has different size
> ...about twenty more lines like these...
> ```
>
> These are **warnings**, so the program is still written and it runs.
> But the cause is real: `libstdc++exp.a` was built by **GCC**, your
> object file by **Clang**, and both carry their own copy of some
> library data (the type information of `std::runtime_error` and
> friends) with slightly different sizes. GNU `ld` complains about the
> mismatch. Clang's own linker, **lld**, does not, so with `-fuse-ld=lld`
> the link is clean. (Mind that a script run with
> `$ErrorActionPreference = 'Stop'` in Windows PowerShell treats the
> warning text as a failure and stops.) Newer setups, like the Clang 21
> in our Linux container, need neither option.

#### 2. Read the object files and the binary

First, make two more small objects to look at: `stats.o` (which
**defines** `to_celsius`) and `report.o` (which **uses** it).

```powershell
clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-clang/stats.o
clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-clang/report.o
```

**What kind of file is it?**

```powershell
objdump -f out-mingw-clang/stats.o
```

```
out-mingw-clang/stats.o:     file format pe-x86-64
architecture: i386:x86-64, flags 0x0000003d:
HAS_RELOC, HAS_LINENO, HAS_DEBUG, HAS_SYMS, HAS_LOCALS
start address 0x0000000000000000
```

`pe-x86-64` is the Windows object format (**COFF**, in the PE family)
for 64-bit x86.

**Which names does it define, and which does it need?** A tiny program
still contains **hundreds** of symbols from `std::vector`, `std::format`
and friends, so we filter for our own namespace, `station`:

```powershell
nm out-mingw-clang/stats.o | Select-String station
nm -C out-mingw-clang/stats.o | Select-String station
nm out-mingw-clang/report.o | Select-String to_celsius
```

```
0000000000000000 T _ZN7station10to_celsiusEd
0000000000000040 T _ZN7station9summarizeERKSt6vectorIdSaIdEE

0000000000000000 T station::to_celsius(double)
0000000000000040 T station::summarize(std::vector<double, std::allocator<double> > const&)

                 U _ZN7station10to_celsiusEd
```

(The blank lines are only here to separate the three commands.) `nm`
marks each symbol with a letter. **`T`** = defined, in the code ("text")
section. **`U`** = undefined here: the linker must find it. In
`stats.o`, `to_celsius` is `T`: this object **defines** it. In
`report.o`, the same name is `U`: that is the note from the start of the
lecture, made visible. The linker's whole job is to **match every `U`
with exactly one `T`**. The `-C` flag ("demangle") prints the C++ name
instead of the code.

**Name mangling.** You wrote `to_celsius`. The object file says
`_ZN7station10to_celsiusEd`. That is **name mangling**. C++ allows
several functions with the same name and different parameters
(overloading, lecture 6.9), but a linker only compares **plain names**.
So the compiler puts the **namespace, the name and the parameter types
into the one name** it hands to the linker. `c++filt` reads it back:

```powershell
c++filt _ZN7station10to_celsiusEd
```

```
station::to_celsius(double)
```

Clang uses the same "Itanium" rules as GCC, so the names are identical
to the GCC ones. Here is the name taken apart:

| Piece | Meaning |
|---|---|
| `_Z` | "this is a C++ name" |
| `N` ... `E` | a **qualified** name, `namespace::function`, from `N` to `E` |
| `7station` | a name that is 7 letters long: `station` |
| `10to_celsius` | a name that is 10 letters long: `to_celsius` |
| `d` | the parameter type: `d` means `double` |

Do not try to memorise this. The point is that **the parameter types are
inside the name**. We tried an overload `int to_celsius(int)` and Clang
named it `_ZN7station10to_celsiusEi`: the `d` became an `i`, which is
`int`. Two different names, so both can live in one program.

**Now the finished program.** An executable is just another binary with
a table of what it needs.

```powershell
objdump -f out-mingw-clang/single_two_step.exe
objdump -p out-mingw-clang/single_two_step.exe | Select-String 'DLL Name'
```

```
out-mingw-clang/single_two_step.exe:     file format pei-x86-64
architecture: i386:x86-64, flags 0x0000013f:
HAS_RELOC, EXEC_P, HAS_LINENO, HAS_DEBUG, HAS_SYMS, HAS_LOCALS, D_PAGED
start address 0x000000014000105f

	DLL Name: libgcc_s_seh-1.dll
	DLL Name: libstdc++-6.dll
	DLL Name: KERNEL32.dll
	DLL Name: api-ms-win-crt-environment-l1-1-0.dll
	...more api-ms-win-crt-*.dll files...
```

`pei-x86-64` is a finished Windows program (**PE**, with the `i` for
"image"). The **DLL Name** lines are the DLLs Windows loads when the
program starts. Two of them, `libstdc++-6.dll` and `libgcc_s_seh-1.dll`,
live in `C:\mingw64\bin`. That is a real consequence: we ran our
`weather.exe` from a window where `C:\mingw64\bin` was **not** on the
PATH, and Windows refused to start it (exit code `-1073741515`, which
means "a DLL was not found"). We come back to dependencies in 7.14.

**The ABI.** Objects made by MinGW and objects made by MSVC are both
COFF, but **they cannot be mixed**: their mangled names differ
(`_ZN7station10to_celsiusEd` here, `?to_celsius@station@@YANN@Z` with
MSVC), and so do the C++ libraries behind them. **A C++ library is tied
to the compiler and standard library that built it.** That agreement
about names, layouts and calling conventions is the **ABI** (application
binary interface). In 7.14 you will see why it matters for libraries.

#### 3. Single file, one step

Hand the source file straight to `clang++` and let it run both steps:

```powershell
clang++ -std=c++23 -Wall -Wextra single.cpp -o out-mingw-clang/single_one_step.exe -fuse-ld=lld -lstdc++exp
./out-mingw-clang/single_one_step.exe
Get-ChildItem out-mingw-clang/single.o, out-mingw-clang/single_two_step.exe, out-mingw-clang/single_one_step.exe | Format-Table Name, Length -AutoSize
```

```
average: 70.9 F

Name                Length
----                ------
single.o            506328
single_two_step.exe 305664
single_one_step.exe 305664
```

Both programs have **exactly the same size**. That is the point:
`clang++` is a driver, it runs the compiler and then the linker and
passes your options along. The one-step form just does not keep the
object file.

Look at the sizes again. Here the object file (about 500 KB) is
**bigger** than the program built from it (about 300 KB). That is the
linker at work: the object carries every piece of template code that
`std::println` and `std::accumulate` brought in, and the linker keeps
only what the program really uses. With other tool chains the numbers
go the other way, and yours will differ too. The lesson is that an
object file is **not a small program**, it is a half-finished one: all
that template code is spread over it, together with the bookkeeping the
linker needs.

#### 4. Multiple files

Compile each `.cpp` on its own, then link all three objects together:

```powershell
clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-clang/stats.o
clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-clang/report.o
clang++ -std=c++23 -Wall -Wextra -c main.cpp -o out-mingw-clang/main.o
clang++ out-mingw-clang/main.o out-mingw-clang/stats.o out-mingw-clang/report.o -o out-mingw-clang/weather.exe -fuse-ld=lld -lstdc++exp
./out-mingw-clang/weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

**Break it on purpose.** The best way to understand the linker is to
starve it. Link again, this time **leaving out `stats.o`**:

```powershell
clang++ out-mingw-clang/main.o out-mingw-clang/report.o -o out-mingw-clang/broken.exe -fuse-ld=lld -lstdc++exp
```

```
ld.lld: error: undefined symbol: station::summarize(std::vector<double, std::allocator<double>> const&)
>>> referenced by out-mingw-clang/main.o:(main)
ld.lld: error: undefined symbol: station::to_celsius(double)
>>> referenced by out-mingw-clang/report.o:(station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char>>, station::Summary const&))
>>> referenced by out-mingw-clang/report.o:(station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char>>, station::Summary const&))
>>> referenced by out-mingw-clang/report.o:(station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char>>, station::Summary const&))
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

Read that with fresh eyes. Every `.cpp` compiled without complaint. The
error is that two promises ("someone defines `summarize`", "someone
defines `to_celsius`") were never kept. lld prints the missing name once,
then one `>>> referenced by` line for each place that asked: `report.o`
asks for `to_celsius` three times. Whenever you see `undefined
symbol` or `undefined reference`, ask: **did I forget to compile or
link the file that defines it?**

When you want to start over, or try another environment, delete the
folder: `Remove-Item -Recurse out-mingw-clang`. Nothing else was touched.

That is MinGW Clang done.

---

### Environment 4: Linux, GCC (Docker)

You get a real Linux with GCC from the Docker container of chapter 2.
Our image carries GCC 16.2 and GNU binutils 2.44.

#### Open the shell

From the repository root, in PowerShell:

```powershell
docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-gcc
```

You land in `/workspace`, which is the repository. Now, inside the
container:

```sh
cd 07.PracticalBuiltInFeatures/7.12ProjectManualCompile
g++ --version
```

```
g++ (GCC) 16.2.0
```

(`--rm` throws the container away when you leave. The files you create
stay in your folder on Windows, in `out-linux-gcc`, because of the `-v` mount.
They are ignored by git.)

#### The tools in this environment

- **`g++`**: the GCC compiler driver. You give it `.cpp` files and
  options. It runs the compiler and, unless you say `-c`, then runs the
  linker for you.
- **`ld`**: the GNU linker. You will not usually type it: `g++` calls
  it. The linker errors you get come from `/usr/bin/ld`.
- **`nm`**: lists the **symbol table** of an object file: every name it
  defines or needs. We need it to see what the linker sees.
- **`file`**: guesses what a file is from its first bytes. A quick way
  to learn "is this an object or an executable, for which machine?".
- **`readelf`**: prints the headers of **ELF** files, the format of
  objects and programs on Linux.
- **`ldd`**: lists the **shared libraries** a program needs at start-up.
- **`c++filt`**: turns a mangled C++ name back into readable C++.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```sh
mkdir -p out-linux-gcc
```

(`-p` means "no error if it already exists".)

#### 1. Single file, two steps

```
   single.cpp ──► compile ──► single.o ──► link ──► single_two_step
```

```sh
g++ -std=c++23 -Wall -Wextra -c single.cpp -o out-linux-gcc/single.o
g++ out-linux-gcc/single.o -o out-linux-gcc/single_two_step
./out-linux-gcc/single_two_step
```

```
average: 70.9 F
```

- `-c` means **compile only, do not link**. That is what produces
  `single.o`.
- `-std=c++23` selects the language mode. `-Wall -Wextra` ask for more
  warnings.
- `-o` names the output file, here inside `out-linux-gcc`. On Linux the
  program has no extension.
- The second command has no `.cpp` file at all: `g++` is being used as a
  **front end for the linker**.
- There is no extra library to add here: GCC 16 has `std::println` built
  in. (On the older MinGW GCC 14 you need `-lstdc++exp`.)

#### 2. Read the object files and the binary

First, make two more small objects to look at: `stats.o` (which
**defines** `to_celsius`) and `report.o` (which **uses** it).

```sh
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-gcc/stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-gcc/report.o
```

**What kind of file is it?**

```sh
file out-linux-gcc/stats.o
readelf -h out-linux-gcc/stats.o | grep -E 'Class|Type|Machine'
```

```
out-linux-gcc/stats.o: ELF 64-bit LSB relocatable, x86-64, version 1 (GNU/Linux), not stripped
  Class:                             ELF64
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
```

**ELF** is the object format on Linux. `relocatable` is another word for
"object file": its code still has holes (addresses) for the linker to
fill in.

**Which names does it define, and which does it need?** A tiny program
still contains **hundreds** of symbols from `std::vector`, `std::format`
and friends, so we filter for our own namespace, `station`:

```sh
nm out-linux-gcc/stats.o | grep station
nm -C out-linux-gcc/stats.o | grep station
nm out-linux-gcc/report.o | grep to_celsius
```

```
0000000000000000 T _ZN7station10to_celsiusEd
0000000000000038 T _ZN7station9summarizeERKSt6vectorIdSaIdEE

0000000000000000 T station::to_celsius(double)
0000000000000038 T station::summarize(std::vector<double, std::allocator<double> > const&)

                 U _ZN7station10to_celsiusEd
```

(The blank lines are only here to separate the three commands.) `nm`
marks each symbol with a letter. **`T`** = defined, in the code ("text")
section. **`U`** = undefined here: the linker must find it. In
`stats.o`, `to_celsius` is `T`: this object **defines** it. In
`report.o`, the same name is `U`: that is the note from the start of the
lecture, made visible. The linker's whole job is to **match every `U`
with exactly one `T`**. The `-C` flag ("demangle") prints the C++ name
instead of the code.

**Name mangling.** You wrote `to_celsius`. The object file says
`_ZN7station10to_celsiusEd`. That is **name mangling**. C++ allows
several functions with the same name and different parameters
(overloading, lecture 6.9), but a linker only compares **plain names**.
So the compiler puts the **namespace, the name and the parameter types
into the one name** it hands to the linker. `c++filt` reads it back:

```sh
c++filt _ZN7station10to_celsiusEd
```

```
station::to_celsius(double)
```

GCC uses the "Itanium" rules. Here is the name taken apart:

| Piece | Meaning |
|---|---|
| `_Z` | "this is a C++ name" |
| `N` ... `E` | a **qualified** name, `namespace::function`, from `N` to `E` |
| `7station` | a name that is 7 letters long: `station` |
| `10to_celsius` | a name that is 10 letters long: `to_celsius` |
| `d` | the parameter type: `d` means `double` |

Do not try to memorise this. The point is that **the parameter types are
inside the name**. We tried an overload `int to_celsius(int)` and GCC
named it `_ZN7station10to_celsiusEi`: the `d` became an `i`, which is
`int`. Two different names, so both can live in one program.

**Now the finished program.** An executable is just another binary with
a table of what it needs.

```sh
file out-linux-gcc/single_two_step
readelf -h out-linux-gcc/single_two_step | grep -E 'Type|Machine'
ldd out-linux-gcc/single_two_step
```

```
out-linux-gcc/single_two_step: ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, not stripped
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
	linux-vdso.so.1 (0x00007ffeba50d000)
	libstdc++.so.6 => /usr/local/lib64/libstdc++.so.6 (0x00007ff86911d000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007ff86902d000)
	libgcc_s.so.1 => /usr/local/lib64/libgcc_s.so.1 (0x00007ff868fff000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff868e0b000)
	/lib64/ld-linux-x86-64.so.2 (0x00007ff8693d6000)
```

(The addresses in brackets change on every run.) `EXEC` and `executable`
say this is a finished program, not a relocatable object. `ldd` lists
the **shared libraries** it loads at start-up: `libstdc++.so.6` is the
C++ standard library, `libc.so.6` the C library. The first one comes
from `/usr/local/lib64`, where this image keeps the libraries of its GCC
16. We come back to dependencies in 7.14.

**The ABI.** A C++ library is tied to the compiler and standard library
that built it. That agreement about names, layouts and calling
conventions is the **ABI** (application binary interface). You will see
a sign of it in the break-it-on-purpose output below, in the tag
`[abi:cxx11]`: GCC changed the layout of `std::string` in 2015 and the
tag lets old and new code tell each other apart. In 7.14 you will see
why it matters for libraries.

#### 3. Single file, one step

Hand the source file straight to `g++` and let it run both steps:

```sh
g++ -std=c++23 -Wall -Wextra single.cpp -o out-linux-gcc/single_one_step
./out-linux-gcc/single_one_step
ls -l out-linux-gcc/single.o out-linux-gcc/single_two_step out-linux-gcc/single_one_step
```

```
average: 70.9 F
-rw-r--r-- 1 root root 492960 Oct 14 14:39 out-linux-gcc/single.o
-rwxr-xr-x 1 root root 254640 Oct 14 14:39 out-linux-gcc/single_one_step
-rwxr-xr-x 1 root root 254640 Oct 14 14:39 out-linux-gcc/single_two_step
```

Both programs have **exactly the same size**. That is the point: `g++`
is a driver, it runs the compiler and then the linker and passes your
options along. The one-step form just does not keep the object file.

Look at the sizes again: the object file (about 490 KB) is **bigger**
than the program built from it (about 250 KB). Two lines of
`std::println` and `std::accumulate` pull in a lot of templates, and the
object keeps a copy of every template instantiation the file used, plus
the bookkeeping the linker needs. The linker then keeps only what the
program uses. Your numbers will differ. The lesson is that an object
file is **not a small program**, it is a half-finished one.

#### 4. Multiple files

Compile each `.cpp` on its own, then link all three objects together:

```sh
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-gcc/stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-gcc/report.o
g++ -std=c++23 -Wall -Wextra -c main.cpp -o out-linux-gcc/main.o
g++ out-linux-gcc/main.o out-linux-gcc/stats.o out-linux-gcc/report.o -o out-linux-gcc/weather
./out-linux-gcc/weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

**Break it on purpose.** The best way to understand the linker is to
starve it. Link again, this time **leaving out `stats.o`**:

```sh
g++ out-linux-gcc/main.o out-linux-gcc/report.o -o out-linux-gcc/broken
```

```
/usr/bin/ld: out-linux-gcc/main.o: in function `main':
main.cpp:(.text+0x46): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
/usr/bin/ld: out-linux-gcc/report.o: in function `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)':
report.cpp:(.text+0x37): undefined reference to `station::to_celsius(double)'
/usr/bin/ld: report.cpp:(.text+0x52): undefined reference to `station::to_celsius(double)'
/usr/bin/ld: report.cpp:(.text+0x6c): undefined reference to `station::to_celsius(double)'
collect2: error: ld returned 1 exit status
```

Read that with fresh eyes. Every `.cpp` compiled without complaint. The
error is that two promises ("someone defines `summarize`", "someone
defines `to_celsius`") were never kept. The message even tells you
**which function was asking**. Whenever you see `undefined reference`,
ask: **did I forget to compile or link the file that defines it?**

When you want to start over, or try another environment, delete the
folder: `rm -rf out-linux-gcc` inside the container (or
`Remove-Item -Recurse out-linux-gcc` in PowerShell on Windows). Nothing
else was touched.

That is Linux GCC done.

---

### Environment 5: Linux, Clang (Docker)

You get a real Linux with Clang from the Docker container of chapter 2.
Our image carries Clang 21.1.8 and GNU binutils 2.44, and uses GNU's
libstdc++, the C++ library that comes with Linux.

#### Open the shell

From the repository root, in PowerShell:

```powershell
docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-clang
```

You land in `/workspace`, which is the repository. Now, inside the
container:

```sh
cd 07.PracticalBuiltInFeatures/7.12ProjectManualCompile
clang++ --version | head -1
```

```
Debian clang version 21.1.8 (++20251221033036+2078da43e25a-1~exp1~20251221153213.50)
```

(`--rm` throws the container away when you leave. The files you create
stay in your folder on Windows, in `out-linux-clang`, because of the `-v` mount.
They are ignored by git.)

#### The tools in this environment

- **`clang++`**: the Clang compiler driver. You give it `.cpp` files and
  options. It runs the compiler and, unless you say `-c`, then runs the
  linker for you.
- **`ld`**: the GNU linker. You will not usually type it: `clang++`
  calls it. The linker errors you get come from `/usr/bin/ld`.
- **`nm`**: lists the **symbol table** of an object file: every name it
  defines or needs. We need it to see what the linker sees.
- **`file`**: guesses what a file is from its first bytes. A quick way
  to learn "is this an object or an executable, for which machine?".
- **`readelf`**: prints the headers of **ELF** files, the format of
  objects and programs on Linux.
- **`ldd`**: lists the **shared libraries** a program needs at start-up.
- **`c++filt`**: turns a mangled C++ name back into readable C++.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```sh
mkdir -p out-linux-clang
```

(`-p` means "no error if it already exists".)

#### 1. Single file, two steps

```
   single.cpp ──► compile ──► single.o ──► link ──► single_two_step
```

```sh
clang++ -std=c++23 -Wall -Wextra -c single.cpp -o out-linux-clang/single.o
clang++ out-linux-clang/single.o -o out-linux-clang/single_two_step
./out-linux-clang/single_two_step
```

```
average: 70.9 F
```

- `-c` means **compile only, do not link**. That is what produces
  `single.o`.
- `-std=c++23` selects the language mode. `-Wall -Wextra` ask for more
  warnings.
- `-o` names the output file, here inside `out-linux-clang`. On Linux the
  program has no extension.
- The second command has no `.cpp` file at all: `clang++` is being used
  as a **front end for the linker**.
- There is no extra library to add here: the library in this image has
  `std::println` built in. (On MinGW Clang you need `-lstdc++exp` and
  `-fuse-ld=lld`, see 7.12.)

#### 2. Read the object files and the binary

First, make two more small objects to look at: `stats.o` (which
**defines** `to_celsius`) and `report.o` (which **uses** it).

```sh
clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-clang/stats.o
clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-clang/report.o
```

**What kind of file is it?**

```sh
file out-linux-clang/stats.o
readelf -h out-linux-clang/stats.o | grep -E 'Class|Type|Machine'
```

```
out-linux-clang/stats.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped
  Class:                             ELF64
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
```

**ELF** is the object format on Linux. `relocatable` is another word for
"object file": its code still has holes (addresses) for the linker to
fill in.

**Which names does it define, and which does it need?** A tiny program
still contains **hundreds** of symbols from `std::vector`, `std::format`
and friends, so we filter for our own namespace, `station`:

```sh
nm out-linux-clang/stats.o | grep station
nm -C out-linux-clang/stats.o | grep station
nm out-linux-clang/report.o | grep to_celsius
```

```
0000000000000000 T _ZN7station10to_celsiusEd
0000000000000040 T _ZN7station9summarizeERKSt6vectorIdSaIdEE

0000000000000000 T station::to_celsius(double)
0000000000000040 T station::summarize(std::vector<double, std::allocator<double> > const&)

                 U _ZN7station10to_celsiusEd
```

(The blank lines are only here to separate the three commands.) `nm`
marks each symbol with a letter. **`T`** = defined, in the code ("text")
section. **`U`** = undefined here: the linker must find it. In
`stats.o`, `to_celsius` is `T`: this object **defines** it. In
`report.o`, the same name is `U`: that is the note from the start of the
lecture, made visible. The linker's whole job is to **match every `U`
with exactly one `T`**. The `-C` flag ("demangle") prints the C++ name
instead of the code.

**Name mangling.** You wrote `to_celsius`. The object file says
`_ZN7station10to_celsiusEd`. That is **name mangling**. C++ allows
several functions with the same name and different parameters
(overloading, lecture 6.9), but a linker only compares **plain names**.
So the compiler puts the **namespace, the name and the parameter types
into the one name** it hands to the linker. `c++filt` reads it back:

```sh
c++filt _ZN7station10to_celsiusEd
```

```
station::to_celsius(double)
```

Clang uses the same "Itanium" rules as GCC, so the names are identical
to the GCC ones. Here is the name taken apart:

| Piece | Meaning |
|---|---|
| `_Z` | "this is a C++ name" |
| `N` ... `E` | a **qualified** name, `namespace::function`, from `N` to `E` |
| `7station` | a name that is 7 letters long: `station` |
| `10to_celsius` | a name that is 10 letters long: `to_celsius` |
| `d` | the parameter type: `d` means `double` |

Do not try to memorise this. The point is that **the parameter types are
inside the name**. We tried an overload `int to_celsius(int)` and Clang
named it `_ZN7station10to_celsiusEi`: the `d` became an `i`, which is
`int`. Two different names, so both can live in one program.

**Now the finished program.** An executable is just another binary with
a table of what it needs.

```sh
file out-linux-clang/single_two_step
readelf -h out-linux-clang/single_two_step | grep -E 'Type|Machine'
ldd out-linux-clang/single_two_step
```

```
out-linux-clang/single_two_step: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=ea95edc592d2bd6cf3865035ef5f167eba8a2998, for GNU/Linux 3.2.0, not stripped
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
	linux-vdso.so.1 (0x00007ffd739bd000)
	libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f695a412000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f695a322000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f695a2f5000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f695a101000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f695a6a4000)
```

(The addresses in brackets and the `BuildID` change with every build and
run.) `pie executable` says this is a finished program
("position-independent": it can be loaded at any address). `ldd` lists
the **shared libraries** it loads at start-up: `libstdc++.so.6` is the
C++ standard library, `libc.so.6` the C library. We come back to
dependencies in 7.14.

**The ABI.** A C++ library is tied to the compiler and standard library
that built it. That agreement about names, layouts and calling
conventions is the **ABI** (application binary interface). You will see
a sign of it in the break-it-on-purpose output below, in the tag
`[abi:cxx11]`: the library's `std::string` changed layout in 2015 and
the tag lets old and new code tell each other apart. In 7.14 you will
see why it matters for libraries.

#### 3. Single file, one step

Hand the source file straight to `clang++` and let it run both steps:

```sh
clang++ -std=c++23 -Wall -Wextra single.cpp -o out-linux-clang/single_one_step
./out-linux-clang/single_one_step
ls -l out-linux-clang/single.o out-linux-clang/single_two_step out-linux-clang/single_one_step
```

```
average: 70.9 F
-rw-r--r-- 1 root root 416128 Oct 14 14:39 out-linux-clang/single.o
-rwxr-xr-x 1 root root 221624 Oct 14 14:39 out-linux-clang/single_one_step
-rwxr-xr-x 1 root root 221624 Oct 14 14:39 out-linux-clang/single_two_step
```

Both programs have **exactly the same size**. That is the point:
`clang++` is a driver, it runs the compiler and then the linker and
passes your options along. The one-step form just does not keep the
object file.

Look at the sizes again: the object file (about 420 KB) is **bigger**
than the program built from it (about 220 KB). Two lines of
`std::println` and `std::accumulate` pull in a lot of templates, and the
object keeps a copy of every template instantiation the file used, plus
the bookkeeping the linker needs. The linker then keeps only what the
program uses. Your numbers will differ. The lesson is that an object
file is **not a small program**, it is a half-finished one.

#### 4. Multiple files

Compile each `.cpp` on its own, then link all three objects together:

```sh
clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-clang/stats.o
clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-clang/report.o
clang++ -std=c++23 -Wall -Wextra -c main.cpp -o out-linux-clang/main.o
clang++ out-linux-clang/main.o out-linux-clang/stats.o out-linux-clang/report.o -o out-linux-clang/weather
./out-linux-clang/weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

**Break it on purpose.** The best way to understand the linker is to
starve it. Link again, this time **leaving out `stats.o`**:

```sh
clang++ out-linux-clang/main.o out-linux-clang/report.o -o out-linux-clang/broken
```

```
/usr/bin/ld: out-linux-clang/main.o: in function `main':
main.cpp:(.text+0x91): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
/usr/bin/ld: out-linux-clang/report.o: in function `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)':
report.cpp:(.text+0x3f): undefined reference to `station::to_celsius(double)'
/usr/bin/ld: report.cpp:(.text+0x52): undefined reference to `station::to_celsius(double)'
/usr/bin/ld: report.cpp:(.text+0x65): undefined reference to `station::to_celsius(double)'
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

Read that with fresh eyes. Every `.cpp` compiled without complaint. The
error is that two promises ("someone defines `summarize`", "someone
defines `to_celsius`") were never kept. The message even tells you
**which function was asking**. Whenever you see `undefined reference`,
ask: **did I forget to compile or link the file that defines it?**

When you want to start over, or try another environment, delete the
folder: `rm -rf out-linux-clang` inside the container (or
`Remove-Item -Recurse out-linux-clang` in PowerShell on Windows). Nothing
else was touched.

That is Linux Clang done.

---

### Gotchas to take away

A summary of what you met. Each point was shown in the environment where
it applies.

- `/std:c++latest`, never `/std:c++23`, with `cl`.
- MinGW GCC and Clang need `-lstdc++exp` for `std::println`, and it must
  come **after** the objects. MinGW Clang also needs `-fuse-ld=lld`:
  with the default GNU linker it prints a wall of "duplicate section"
  warnings. The Linux containers need neither.
- `LNK2019` / `undefined reference` means the **linker** could not find
  a definition: check that you compiled and linked the file that has it.
- Objects from different compilers do not mix, even when both are `.obj`
  or `.o`.
- Compile every file with the **same standard and the same runtime
  option** (`/MD` everywhere with MSVC). Mixing them is how LNK2038
  appears, which we meet in 7.13.
- A MinGW program needs `C:\mingw64\bin` on the PATH to start, because
  of the DLLs it depends on.

One last teaser. In 8.12 we will write a function in assembly and call
it from C++. The assembler does not mangle anything, so we will mark
that function **`extern "C"`**, which tells the C++ compiler "use the
plain name, as C does".

---

## 7.13 Project: a static library

In the last project, you linked three object files by hand. Imagine a program with three hundred. You would not pass three hundred names to the linker every time, and you would not want to hand your teammates a folder of loose `.o` files either. The practical answer we have to this is a **library**: a bundle of compiled code with a name.

There are two kinds of libraries, and this lecture covers the first one, the **static library**. 

We are working on the same weather-station program as we did in the last lecture, but now `stats.cpp` and `report.cpp` are bundled together in a **static library** and `main.cpp` is built and linked against the bundle.

```
   stats.cpp  ──► stats.o  ──┐
                             ├──► archive: libstation.a ──┐
   report.cpp ──► report.o ──┘     (a bundle of objects)  │
                                                          ├──► linker ──► weather
   main.cpp   ──► main.o  ────────────────────────────────┘
```

### An archive is not an object file

This is the idea to hold on to.

- An **object file** is the compiled code of **one** source file, with its symbol table.
- A **static library** is an **archive**: a plain container holding **several object files unchanged**, plus an index of the symbols they define. Nothing is rewritten and nothing is merged.

Think of a zip file, but without compression. A static library cannot run, and it cannot be loaded. It exists for **the linker**. When the linker has an unresolved name such as `to_celsius`, it looks in the archive's index, finds which member defines it, pulls out **only that member**, and copies it into the program.

That last sentence has a consequence: once the program is linked, **the library is no longer needed**. The code was *copied into* `weather`. You can delete `libstation.a`, and the program still runs.

### The files you will build

All the source files are in `7.13ProjectStaticLibrary`. They are the same
weather-station files as in the last project:

```
   stats.h / stats.cpp     summarize(readings) and to_celsius(f)               ─┐ the library
   report.h / report.cpp   format_report(sensor, summary), which CALLS         ─┘
                           to_celsius
   main.cpp                builds the readings, calls both, prints             the program
```

`report.cpp` calls `to_celsius`, which lives in `stats.cpp`. Both of
them go into the library, so the library has to keep that promise
**inside itself**, and `main.cpp` only has to find the library.

### Pick your environment

The project has **five environments**. Every one of them is a complete
walk-through that you can do without reading any other. Do the one you
have, and come back for the others if you are curious. In each one you
will do the same five things:

1. **Build the library**: compile the two library files, then bundle
   their object files into one archive.
2. **Look inside** the archive.
3. **Link the program** against the library.
4. **Break it** on purpose.
5. **Delete the library** and run the program again.

| Environment | Compiler driver | Archiver | Library file | Output folder |
|---|---|---|---|---|
| Windows, MSVC | `cl` | `lib` | `station.lib` | `out-msvc` |
| Windows, MinGW GCC | `g++` | `ar` | `libstation.a` | `out-mingw-gcc` |
| Windows, MinGW Clang | `clang++` | `ar` | `libstation.a` | `out-mingw-clang` |
| Linux, GCC (Docker) | `g++` | `ar` | `libstation.a` | `out-linux-gcc` |
| Linux, Clang (Docker) | `clang++` | `ar` | `libstation.a` | `out-linux-clang` |

Every environment writes **everything it produces** (object files, the
library, programs, even the ones you build to fail) into **its own output
folder**, the one in the last column, inside `7.13ProjectStaticLibrary`.
Your source folder stays clean, and when you are done you delete **one
folder** to start over or to try another environment. Git ignores every
`out-*` folder.

Every folder in this project also has one script per environment
(`build-msvc.ps1`, `build-mingw-gcc.ps1`, `build-mingw-clang.ps1`,
`build-linux-gcc.sh`, `build-linux-clang.sh`) that runs the commands of
that environment from top to bottom. Type the commands yourself first,
and use the scripts to check your work. (A script and your own commands
fill the same output folder, so delete the folder between the two if you
want to be sure the script did the work.)

---

### Environment 1: Windows, MSVC

MSVC is Microsoft's C++ compiler, the one Visual Studio uses and the
reference compiler of this course. Our version is `cl` 19.51 (Visual
Studio 2026).

#### Open the shell

Open **Developer PowerShell for VS** from the Start menu. That is an
ordinary PowerShell that already knows where the Microsoft tools are.
(From any other PowerShell you can load it by hand:
`& "<your VS folder>\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64`.)
Then, from the repository root:

```powershell
cd 07.PracticalBuiltInFeatures\7.13ProjectStaticLibrary
cl
```

`cl` on its own prints a banner. Ours starts with
`Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36260 for x64`.
If you see it, the shell is ready.

#### The tools in this environment

- **`cl`**: the compiler driver. In this project we only use it to
  compile (`/c`): every `.cpp` becomes an `.obj`.
- **`lib`**: the **librarian**, Microsoft's archiver. It bundles `.obj`
  files into one `.lib` file, lists what is inside a `.lib` (`/LIST`)
  and can take a member back out (`/EXTRACT`). It does not link
  anything.
- **`link`**: the linker. It takes `.obj` files and `.lib` files and
  writes the `.exe`.
- **`dumpbin`**: Microsoft's "dump a binary" tool. It reads object
  files, libraries and executables and prints what is inside. It only
  reads: it never changes the file.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-msvc
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Build the library

```
   stats.cpp  ──► compile ──► stats.obj  ──┐
                                           ├──► lib ──► station.lib
   report.cpp ──► compile ──► report.obj ──┘
```

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c stats.cpp /Fo:out-msvc\
cl /nologo /std:c++latest /EHsc /MD /W4 /c report.cpp /Fo:out-msvc\
lib /nologo /OUT:out-msvc\station.lib out-msvc\stats.obj out-msvc\report.obj
lib /nologo /LIST out-msvc\station.lib
```

```
out-msvc\stats.obj
out-msvc\report.obj
```

- The two `cl` commands only **compile**: `/c` means "do not link", and
  `/Fo:out-msvc\` says which **folder** gets the object files (the
  trailing backslash is what tells `cl` it is a folder). `/std:c++latest`
  is the newest language mode (never `/std:c++23` with `cl`), `/EHsc`
  turns on normal exception handling, and `/MD` picks the **shared C
  runtime**, which is also what CMake uses by default.
- `lib /OUT:` names the library and the rest of the line is the list of
  members to put in it. Nothing is linked: `lib` only **bundles**. You
  cannot run `station.lib`.
- `lib /LIST` prints the members of an existing library. MSVC stores
  each member under the name you gave it on the command line, folder
  included, which is why the folder shows up in the list.

#### 2. Look inside the archive

**Which names do the members define, and which do they need?** The
library holds the same two objects you would have linked by hand, so we
ask `dumpbin` about the one name that connects them:

```powershell
dumpbin /symbols out-msvc\station.lib | Select-String 'to_celsius'
```

```
6FD 00000000 UNDEF  notype ()    External     | ?to_celsius@station@@YANN@Z (double __cdecl station::to_celsius(double))
049 00000000 SECT4  notype ()    External     | ?to_celsius@station@@YANN@Z (double __cdecl station::to_celsius(double))
```

(`dumpbin` wraps long lines at an odd place. We joined them here.) The
same name shows up **twice**, once per member that mentions it. The line
marked `SECT4` is the member that **defines** `to_celsius`
(`stats.obj`). The line marked `UNDEF` is the member that **needs** it
(`report.obj`). It is the pair you meet when you read two object files,
now sitting inside one file.

**How big is it?**

```powershell
Get-ChildItem out-msvc\stats.obj, out-msvc\report.obj, out-msvc\station.lib | Format-Table Name, Length -AutoSize
```

```
Name        Length
----        ------
stats.obj    22407
report.obj  745931
station.lib 956916
```

The library is **not smaller** than the objects it holds: nothing is
compressed, and it carries an index of names on top. Almost all of its
size is `report.obj`, which pulls in a lot of template code for
`std::format`. Your numbers will differ.

**Are the members really untouched?** Take one member back out of the
library and compare it with the object we put in:

```powershell
mkdir out-msvc\extracted
lib /nologo /EXTRACT:out-msvc\stats.obj /OUT:out-msvc\extracted\stats.obj out-msvc\station.lib
(Get-FileHash out-msvc\stats.obj).Hash -eq (Get-FileHash out-msvc\extracted\stats.obj).Hash
```

```
True
```

`/EXTRACT:` names the member (under the name `/LIST` showed) and `/OUT:`
says where to write the copy. `Get-FileHash` computes a fingerprint of
a file's contents, so `True` means the two files are **identical, byte
for byte**. Nothing was rewritten and nothing was merged: the library is
a container.

#### 3. Link the program against the library

Compile `main.cpp` as usual. At the link step, name the library instead
of the object files it holds:

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c main.cpp /Fo:out-msvc\
link /nologo out-msvc\main.obj out-msvc\station.lib /OUT:out-msvc\weather.exe
.\out-msvc\weather.exe
Get-ChildItem out-msvc\main.obj, out-msvc\weather.exe | Format-Table Name, Length -AutoSize
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C

Name        Length
----        ------
main.obj    798453
weather.exe 320512
```

You give `link` the **real file name**, `station.lib`: MSVC does not add
a prefix or a suffix for you. `main.obj` needs `summarize` and
`format_report`. The linker finds both in the index of the library,
pulls those members out and copies them into the program. When
`report.obj` arrives, it needs `to_celsius`, and that name is found in
the same library. The names a member needs join the list of names still
to find.

Look at the sizes: the program (about 320 KB) is **smaller** than the
library (about 950 KB). The library is a stock of parts, and the program
takes only what it needs from it.

#### 4. Break it on purpose

**a. Leave the library out.** Link again with only `main.obj`:

```powershell
link /nologo out-msvc\main.obj /OUT:out-msvc\broken.exe
```

```
main.obj : error LNK2019: unresolved external symbol "struct station::Summary __cdecl station::summarize(class std::vector<double,class std::allocator<double> > const &)" (?summarize@station@@YA?AUSummary@1@AEBV?$vector@NV?$allocator@N@std@@@std@@@Z) referenced in function main
main.obj : error LNK2019: unresolved external symbol "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl station::format_report(class std::basic_string_view<char,struct std::char_traits<char> >,struct station::Summary const &)" (?format_report@station@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$basic_string_view@DU?$char_traits@D@std@@@3@AEBUSummary@1@@Z) referenced in function main
out-msvc\broken.exe : fatal error LNK1120: 2 unresolved externals
```

Read it closely. The linker asks for `summarize` and `format_report`,
the two functions `main.cpp` calls. It does **not** ask for
`to_celsius`: only `report.obj` calls that one, and `report.obj` is
inside the library we left out.

**b. Change the order.** Put the library **before** the object that
needs it:

```powershell
link /nologo out-msvc\station.lib out-msvc\main.obj /OUT:out-msvc\order.exe
.\out-msvc\order.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It still works. With MSVC the order of the inputs does not matter. (Keep
that in mind: not every linker is so forgiving.)

**c. Mix C runtimes.** 

##### The idea

Almost every program needs a set of ready-made basics that you never wrote: ask the system for memory, print text, open a file, copy a string, take a square root. That bundle is the C runtime. The C++ standard library (std::vector, std::println) is built on top of it.

Your program has to get that bundle from somewhere. /MD and /MT are the two choices:

```
   /MD  "shared"                     /MT  "copied in"

   weather.exe ─┐                    weather.exe
   other.exe  ──┼──► one copy of     (has its own copy of the
   another.exe ─┘    the runtime      runtime inside it)
                     on the machine
                     (DLL files)

```

- **/MD**: "My program uses the runtime that is already installed on the machine." One copy sits on the computer, in DLL files, and every program shares it. This is what we saw in 7.12 when dumpbin /dependents listed VCRUNTIME140.dll and the api-ms-win-crt-*.dll files. The D stands for DLL.

- **/MT**: "My program carries its own copy." The pieces it needs are copied into the .exe. The program does not need those DLLs, but it is usually bigger. I haven't measured the size difference here.
CMake uses /MD by default, so this course uses it everywhere.

##### Why mixing them is a problem

The runtime does more than hold recipes. It also keeps books, for example a record of which memory has been handed out. If half of your program uses the shared copy and the other half uses its own, you now have two sets of books in one program. Memory handed out by one set can be handed back to the other, which doesn't know about it. That leads to crashes that are very hard to find.

So the linker refuses to build the program at all and tells you at link time. That is the LNK2038 error in the notes. Read it like this:

```
mismatch detected for 'RuntimeLibrary':
   value 'MT_StaticRelease'  doesn't match
   value 'MD_DynamicRelease' in main.obj
```

Try this out:

```powershell
cl /nologo /std:c++latest /EHsc /MT /W4 /c stats.cpp /Fo:out-msvc\stats_mt.obj
lib /nologo /OUT:out-msvc\station_mt.lib out-msvc\stats_mt.obj out-msvc\report.obj
link /nologo out-msvc\main.obj out-msvc\station_mt.lib /OUT:out-msvc\mt.exe
```

```
station_mt.lib(stats_mt.obj) : error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MT_StaticRelease' doesn't match value 'MD_DynamicRelease' in main.obj
LINK : warning LNK4098: defaultlib 'LIBCMT' conflicts with use of other libs; use /NODEFAULTLIB:library
out-msvc\mt.exe : fatal error LNK1319: 1 mismatches detected
```

Every command compiled fine, the **link** refused. A static library is
only a bundle of compiled code, so it takes on **whatever settings it
was compiled with**: the C runtime (`/MD` or `/MT`), the language
standard, debug or release. That is why every command in this project
carries the same flags.

#### 5. The finished program does not need the library

Delete the library and run the program again:

```powershell
Remove-Item out-msvc\station.lib
.\out-msvc\weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It still runs. The code it needed was **copied into** `weather.exe`
at link time. The library was needed to **build** the program, not to
**run** it.

When you want to start over, or try another environment, delete the
folder: `Remove-Item -Recurse out-msvc`. Nothing else was touched.

That is MSVC done.

---

### Environment 2: Windows, MinGW GCC

**MinGW-w64** brings the GNU tool chain (GCC, binutils) to Windows. The
programs it makes are ordinary Windows programs. Ours is a UCRT build by
Brecht Sanders: `g++ --version` says
`g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r2) 14.2.0`.

#### Open the shell

Open a normal PowerShell and put `C:\mingw64\bin` on the PATH **for this
window**, then go to the folder (from the repository root):

```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
cd 07.PracticalBuiltInFeatures\7.13ProjectStaticLibrary
g++ --version
```

If you see a version banner, you are ready.

#### The tools in this environment

- **`g++`**: the GCC compiler driver. In this project we use it to
  compile (`-c`) and to link.
- **`ar`**: the **archiver**. It bundles object files into one `.a`
  file, lists what is inside (`t`) and can take a member back out
  (`x`). It does not link anything.
- **`nm`**: lists the **symbol table** of an object file or of every
  member of an archive: every name it defines or needs.
- **`ld`**: the GNU linker. You will not usually type it: `g++` calls
  it, and the linker errors you get come from `ld.exe`.
- **`-lstdc++exp`**: a library option (`-l` means "link this library").
  On our MinGW GCC 14, `std::println` needs this extra library ("the
  experimental part of the C++ library"). It goes **after** everything
  that needs it.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-mingw-gcc
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Build the library

```
   stats.cpp  ──► compile ──► stats.o  ──┐
                                         ├──► ar ──► libstation.a
   report.cpp ──► compile ──► report.o ──┘
```

```powershell
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-gcc/stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-gcc/report.o
ar rcs out-mingw-gcc/libstation.a out-mingw-gcc/stats.o out-mingw-gcc/report.o
ar t out-mingw-gcc/libstation.a
ar tv out-mingw-gcc/libstation.a
```

```
stats.o
report.o
rw-rw-rw- 0/0  32438 Oct 14 18:03 2026 stats.o
rw-rw-rw- 0/0 645393 Oct 14 18:03 2026 report.o
```

- The two `g++` commands only **compile**: `-c` means "do not link", and
  `-o` names the output file, here inside `out-mingw-gcc`.
- `ar` takes its options as a bundle of letters: **`r`** puts the files
  in, **`c`** creates the archive without a warning, **`s`** writes the
  index of names that the linker will search. Then comes the library,
  then the members. Nothing is linked: `ar` only **bundles**. You
  cannot run `libstation.a`.
- `ar t` lists the members (`t` for "table of contents"). `ar tv` adds
  permissions, size and date (yours will differ). Notice that `ar`
  stores only the **file name** of each member, not the folder.
- The file is called `libstation.a` on purpose. In step 3 you will see
  why: the linker looks for libraries by a name with `lib` in front and
  `.a` at the end.

#### 2. Look inside the archive

**Which names do the members define, and which do they need?** The
library holds the same two objects you would have linked by hand.
`nm` prints a header for each member, and then the names inside it:

```powershell
nm -C out-mingw-gcc/libstation.a | Select-String 'to_celsius|\.o:'
```

```
stats.o:
0000000000000000 T station::to_celsius(double)
report.o:
                 U station::to_celsius(double)
```

`-C` ("demangle") prints C++ names instead of codes. **`T`** = defined,
in the code ("text") section. **`U`** = undefined here: the linker must
find it. The member `stats.o` **defines** `to_celsius`, the member
`report.o` **needs** it. It is the pair you meet when you read two
object files, now sitting inside one file.

**How big is it?**

```powershell
Get-ChildItem out-mingw-gcc/stats.o, out-mingw-gcc/report.o, out-mingw-gcc/libstation.a | Format-Table Name, Length -AutoSize
```

```
Name         Length
----         ------
stats.o       32438
report.o     645393
libstation.a 732566
```

The library is **not smaller** than the objects it holds: nothing is
compressed, and it carries an index of names on top. Almost all of its
size is `report.o`, which pulls in a lot of template code for
`std::format`. Your numbers will differ.

**Are the members really untouched?** Take one member back out of the
archive and compare it with the object we put in:

```powershell
mkdir out-mingw-gcc/extracted
ar x --output out-mingw-gcc/extracted out-mingw-gcc/libstation.a stats.o
(Get-FileHash out-mingw-gcc/stats.o).Hash -eq (Get-FileHash out-mingw-gcc/extracted/stats.o).Hash
```

```
True
```

`ar x` extracts, `--output` says into which folder (without it the file
lands in the current folder), and `stats.o` names the member.
`Get-FileHash` computes a fingerprint of a file's contents, so `True`
means the two files are **identical, byte for byte**. Nothing was
rewritten and nothing was merged: the archive is a container.

#### 3. Link the program against the library

Compile `main.cpp` as usual. At the link step, name the library instead
of the object files it holds:

```powershell
g++ -std=c++23 -Wall -Wextra -c main.cpp -o out-mingw-gcc/main.o
g++ out-mingw-gcc/main.o -Lout-mingw-gcc -lstation -o out-mingw-gcc/weather.exe -lstdc++exp
./out-mingw-gcc/weather.exe
Get-ChildItem out-mingw-gcc/main.o, out-mingw-gcc/weather.exe | Format-Table Name, Length -AutoSize
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C

Name        Length
----        ------
main.o      694645
weather.exe 547014
```

Two options on that link line deserve an explanation:

- **`-lstation`** means "find a library called `station`". The tool adds
  the `lib` in front and the `.a` at the end for you, so it looks for
  `libstation.a`. **That is why the file is called `libstation.a`.**
- **`-Lout-mingw-gcc`** means "also look in this folder". Without it,
  `-lstation` searches only the standard library folders and does not
  find the library in your output folder.

`main.o` needs `summarize` and `format_report`. The linker finds both in
the index of the archive, pulls those members out and copies them into
the program. When `report.o` arrives, it needs `to_celsius`, and that
name is found in the same archive. The names a member needs join the
list of names still to find.

The program (about 550 KB) is **smaller** than the library (about
730 KB). The library is a stock of parts, and the program takes only
what it needs from it.

#### 4. Break it on purpose

**a. Leave the library out.** Link again with only `main.o`:

```powershell
g++ out-mingw-gcc/main.o -o out-mingw-gcc/broken.exe -lstdc++exp
```

```
...ld.exe: out-mingw-gcc/main.o:main.cpp:(.text+0x68): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
...ld.exe: out-mingw-gcc/main.o:main.cpp:(.text+0xab): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
collect2.exe: error: ld returned 1 exit status
```

(The long path in front of each line is shortened to `...`.) Read it
closely. The linker asks for `summarize` and `format_report`, the two
functions `main.cpp` calls. It does **not** ask for `to_celsius`: only
`report.o` calls that one, and `report.o` is inside the library we left
out.

**b. Change the order.** Put the library **before** the object that
needs it:

```powershell
g++ -Lout-mingw-gcc -lstation out-mingw-gcc/main.o -o out-mingw-gcc/broken.exe -lstdc++exp
```

```
...ld.exe: out-mingw-gcc/main.o:main.cpp:(.text+0x68): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
...ld.exe: out-mingw-gcc/main.o:main.cpp:(.text+0xab): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
collect2.exe: error: ld returned 1 exit status
```

Same files, same flags, only the order changed, and the link fails with
the same message as if the library were missing. The linker reads its
inputs **left to right**, and only pulls members out of an archive to
satisfy names it **already needs**. Here it met the library first, when
nothing needed anything yet, so it pulled nothing out. The rule is
simple: **libraries go after the objects that use them.** The same rule
puts `-lstdc++exp` at the very end.

**c. Forget `-L`.** Name the library, but do not say where it is:

```powershell
g++ out-mingw-gcc/main.o -lstation -o out-mingw-gcc/broken.exe -lstdc++exp
```

```
...ld.exe: cannot find -lstation: No such file or directory
collect2.exe: error: ld returned 1 exit status
```

This one is a different kind of message: not a missing **function**, a
missing **file**. The linker searched its standard folders for
`libstation.a`, and our output folder is not one of them.

#### 5. The finished program does not need the library

Delete the library and run the program again:

```powershell
Remove-Item out-mingw-gcc/libstation.a
./out-mingw-gcc/weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It still runs. The code it needed was **copied into** `weather.exe`
at link time. The library was needed to **build** the program, not to
**run** it. (The program still needs `C:\mingw64\bin` on the PATH, for
the DLLs of the C++ runtime. That has nothing to do with our library.)

When you want to start over, or try another environment, delete the
folder: `Remove-Item -Recurse out-mingw-gcc`. Nothing else was touched.

That is MinGW GCC done.

---

### Environment 3: Windows, MinGW Clang

**MinGW-w64** brings the GNU tool chain to Windows, and its package also
contains the **Clang** compiler. The programs it makes are ordinary
Windows programs. Clang here uses MinGW's libstdc++ (the one of GCC 16.2)
and, for the final link of a program, LLVM's own linker **lld**.
Ours is a UCRT build by Brecht Sanders in `C:\mingw64`:
`clang++ --version` says `clang version 23.1.3` and
`Target: x86_64-w64-windows-gnu`.

The steps:

1. Build `single.cpp` in **two steps** (compile, then link).
2. **Read** what is inside the object files and the finished binary.
3. Build `single.cpp` in **one step**.
4. Build the **multi-file** program, then break it on purpose.

#### Open the shell

Open a normal PowerShell and put `C:\mingw64\bin` on the PATH **for this
window**, then go to the folder (from the repository root):

```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
cd 07.PracticalBuiltInFeatures\7.13ProjectStaticLibrary
clang++ --version
```

If you see a version banner, you are ready.

#### The tools in this environment

- **`clang++`**: the Clang compiler driver. In this project we use it to
  compile (`-c`) and to link.
- **`ar`**: the **archiver**. It bundles object files into one `.a`
  file, lists what is inside (`t`) and can take a member back out
  (`x`). It does not link anything. It is the same `ar` as with GCC,
  because the object files have the same format.
- **`nm`**: lists the **symbol table** of an object file or of every
  member of an archive: every name it defines or needs.
- **`lld`**: the LLVM linker. You will not usually type it: `clang++`
  calls it when you add `-fuse-ld=lld`, and the linker errors you get
  come from `ld.lld`. (Why not the GNU linker `ld`? See the gotcha in
  7.12: it prints a wall of duplicate-section warnings with
  `-lstdc++exp`.)
- **`-lstdc++exp`**: a library option (`-l` means "link this library").
  On MinGW, `std::println` needs this extra library ("the experimental
  part of the C++ library"). Put it **after** everything that needs it.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-mingw-clang
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Build the library

```
   stats.cpp  ──► compile ──► stats.o  ──┐
                                         ├──► ar ──► libstation.a
   report.cpp ──► compile ──► report.o ──┘
```

```powershell
clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-mingw-clang/stats.o
clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-mingw-clang/report.o
ar rcs out-mingw-clang/libstation.a out-mingw-clang/stats.o out-mingw-clang/report.o
ar t out-mingw-clang/libstation.a
ar tv out-mingw-clang/libstation.a
```

```
stats.o
report.o
rw-rw-rw- 0/0  17495 Oct 24 09:29 2026 stats.o
rw-rw-rw- 0/0 485934 Oct 24 09:29 2026 report.o
```

- The two `clang++` commands only **compile**: `-c` means "do not
  link", and `-o` names the output file, here inside `out-mingw-clang`.
- `ar` takes its options as a bundle of letters: **`r`** puts the files
  in, **`c`** creates the archive without a warning, **`s`** writes the
  index of names that the linker will search. Then comes the library,
  then the members. Nothing is linked: `ar` only **bundles**. You
  cannot run `libstation.a`.
- `ar t` lists the members (`t` for "table of contents"). `ar tv` adds
  permissions, size and date (yours will differ). Notice that `ar`
  stores only the **file name** of each member, not the folder.
- The file is called `libstation.a` on purpose. In step 3 you will see
  why: the linker looks for libraries by a name with `lib` in front and
  `.a` at the end.

#### 2. Look inside the archive

**Which names do the members define, and which do they need?** The
library holds the same two objects you would have linked by hand.
`nm` prints a header for each member, and then the names inside it:

```powershell
nm -C out-mingw-clang/libstation.a | Select-String 'to_celsius|\.o:'
```

```
stats.o:
0000000000000000 T station::to_celsius(double)
report.o:
                 U station::to_celsius(double)
```

`-C` ("demangle") prints C++ names instead of codes. **`T`** = defined,
in the code ("text") section. **`U`** = undefined here: the linker must
find it. The member `stats.o` **defines** `to_celsius`, the member
`report.o` **needs** it. It is the pair you meet when you read two
object files, now sitting inside one file.

**How big is it?**

```powershell
Get-ChildItem out-mingw-clang/stats.o, out-mingw-clang/report.o, out-mingw-clang/libstation.a | Format-Table Name, Length -AutoSize
```

```
Name         Length
----         ------
stats.o       17495
report.o     485934
libstation.a 557238
```

The library is **not smaller** than the objects it holds: nothing is
compressed, and it carries an index of names on top. Almost all of its
size is `report.o`, which pulls in a lot of template code for
`std::format`. Your numbers will differ.

**Are the members really untouched?** Take one member back out of the
archive and compare it with the object we put in:

```powershell
mkdir out-mingw-clang/extracted
ar x --output out-mingw-clang/extracted out-mingw-clang/libstation.a stats.o
(Get-FileHash out-mingw-clang/stats.o).Hash -eq (Get-FileHash out-mingw-clang/extracted/stats.o).Hash
```

```
True
```

`ar x` extracts, `--output` says into which folder (without it the file
lands in the current folder), and `stats.o` names the member.
`Get-FileHash` computes a fingerprint of a file's contents, so `True`
means the two files are **identical, byte for byte**. Nothing was
rewritten and nothing was merged: the archive is a container.

#### 3. Link the program against the library

Compile `main.cpp` as usual. At the link step, name the library instead
of the object files it holds:

```powershell
clang++ -std=c++23 -Wall -Wextra -c main.cpp -o out-mingw-clang/main.o
clang++ out-mingw-clang/main.o -Lout-mingw-clang -lstation -o out-mingw-clang/weather.exe -fuse-ld=lld -lstdc++exp
./out-mingw-clang/weather.exe
Get-ChildItem out-mingw-clang/main.o, out-mingw-clang/weather.exe | Format-Table Name, Length -AutoSize
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C

Name        Length
----        ------
main.o      506300
weather.exe 324096
```

Two options on that link line deserve an explanation (the other two,
`-fuse-ld=lld` and `-lstdc++exp`, are the MinGW extras of 7.12):

- **`-lstation`** means "find a library called `station`". The tool adds
  the `lib` in front and the `.a` at the end for you, so it looks for
  `libstation.a`. **That is why the file is called `libstation.a`.**
- **`-Lout-mingw-clang`** means "also look in this folder". Without it,
  `-lstation` searches only the standard library folders and does not
  find the library in your output folder.

`main.o` needs `summarize` and `format_report`. The linker finds both in
the index of the archive, pulls those members out and copies them into
the program. When `report.o` arrives, it needs `to_celsius`, and that
name is found in the same archive. The names a member needs join the
list of names still to find.

Sizes depend on the toolchain: here the program (about 320 KB) is
**smaller** than the library (about 560 KB), because the linker kept
only what the program uses. Do not expect a rule from the sizes. What
matters is that the program was built from the parts of the library it
needed.

#### 4. Break it on purpose

**a. Leave the library out.** Link again with only `main.o`:

```powershell
clang++ out-mingw-clang/main.o -o out-mingw-clang/broken.exe -fuse-ld=lld -lstdc++exp
```

```
ld.lld: error: undefined symbol: station::summarize(std::vector<double, std::allocator<double>> const&)
>>> referenced by out-mingw-clang/main.o:(main)
ld.lld: error: undefined symbol: station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char>>, station::Summary const&)
>>> referenced by out-mingw-clang/main.o:(main)
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

Read it closely. The linker asks for `summarize` and `format_report`,
the two functions `main.cpp` calls. It does **not** ask for
`to_celsius`: only `report.o` calls that one, and `report.o` is inside
the library we left out.

**b. Change the order.** Put the library **before** the object that
needs it. With lld this link **works**: lld searches all its inputs
together, whatever the order. The order rule belongs to the **GNU
linker**, so we ask for it by name with `-fuse-ld=ld`. We also leave out
`-lstdc++exp` here (with `ld` it brings back the duplicate-section
warnings of 7.12), which is why two extra lines about `std::println`
appear at the end of the message:

```powershell
clang++ -fuse-ld=ld -Lout-mingw-clang -lstation out-mingw-clang/main.o -o out-mingw-clang/broken.exe
```

```
C:/mingw64/bin/ld: out-mingw-clang/main.o:main.cpp:(.text+0x97): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
C:/mingw64/bin/ld: out-mingw-clang/main.o:main.cpp:(.text+0xd1): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
C:/mingw64/bin/ld: out-mingw-clang/main.o:main.cpp:(.text$...): undefined reference to `std::__open_terminal(_iobuf*)'
C:/mingw64/bin/ld: out-mingw-clang/main.o:main.cpp:(.text$...): undefined reference to `std::__write_to_terminal(void*, std::span<char, 18446744073709551615ull>)'
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

(Long symbol names shortened with `...`.) Ignore the last two
`undefined reference` lines, they are the missing `-lstdc++exp`. The
first two are the point: same files, same flags, only the order changed,
and the link fails with the same message as if the library were missing.
The GNU linker reads its inputs **left to right**, and only pulls
members out of an archive to satisfy names it **already needs**. Here it
met the library first, when nothing needed anything yet, so it pulled
nothing out. The rule is simple: **libraries go after the objects that
use them.** The same rule puts `-lstdc++exp` at the very end. lld is
more forgiving, but a command that is right for both linkers is the
safer habit.

**c. Forget `-L`.** Name the library, but do not say where it is:

```powershell
clang++ out-mingw-clang/main.o -lstation -o out-mingw-clang/broken.exe -fuse-ld=lld -lstdc++exp
```

```
lld: error: unable to find library -lstation
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

This one is a different kind of message: not a missing **function**, a
missing **file**. The linker searched its standard folders for
`libstation.a`, and our output folder is not one of them.

#### 5. The finished program does not need the library

Delete the library and run the program again:

```powershell
Remove-Item out-mingw-clang/libstation.a
./out-mingw-clang/weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It still runs. The code it needed was **copied into** `weather.exe`
at link time. The library was needed to **build** the program, not to
**run** it. (The program still needs `C:\mingw64\bin` on the PATH, for
the DLLs of the C++ runtime. That has nothing to do with our library.)

When you want to start over, or try another environment, delete the
folder: `Remove-Item -Recurse out-mingw-clang`. Nothing else was
touched.

That is MinGW Clang done.

---

### Environment 4: Linux, GCC (Docker)

You get a real Linux with GCC from the Docker container of chapter 2.
Our image carries GCC 16.2 and GNU binutils 2.44.

The steps:

1. Build `single.cpp` in **two steps** (compile, then link).
2. **Read** what is inside the object files and the finished binary.
3. Build `single.cpp` in **one step**.
4. Build the **multi-file** program, then break it on purpose.

#### Open the shell

From the repository root, in PowerShell:

```powershell
docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-gcc
```

You land in `/workspace`, which is the repository. Now, inside the
container:

```sh
cd 07.PracticalBuiltInFeatures/7.13ProjectStaticLibrary
g++ --version
```

```
g++ (GCC) 16.2.0
```

(`--rm` throws the container away when you leave. The files you create
stay in your folder on Windows, in `out-linux-gcc`, because of the `-v`
mount. They are ignored by git.)

#### The tools in this environment

- **`g++`**: the GCC compiler driver. In this project we use it to
  compile (`-c`) and to link.
- **`ar`**: the **archiver**. It bundles object files into one `.a`
  file, lists what is inside (`t`) and can take a member back out
  (`x`). It does not link anything.
- **`nm`**: lists the **symbol table** of an object file or of every
  member of an archive: every name it defines or needs.
- **`file`**: guesses what a file is from its first bytes.
- **`cmp`**: compares two files byte by byte.
- **`ld`**: the GNU linker. You will not usually type it: `g++` calls
  it, and the linker errors you get come from `/usr/bin/ld`.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```sh
mkdir -p out-linux-gcc
```

(`-p` means "no error if it already exists".)

#### 1. Build the library

```
   stats.cpp  ──► compile ──► stats.o  ──┐
                                         ├──► ar ──► libstation.a
   report.cpp ──► compile ──► report.o ──┘
```

```sh
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-gcc/stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-gcc/report.o
ar rcs out-linux-gcc/libstation.a out-linux-gcc/stats.o out-linux-gcc/report.o
file out-linux-gcc/libstation.a
ar t out-linux-gcc/libstation.a
ar tv out-linux-gcc/libstation.a
```

```
out-linux-gcc/libstation.a: current ar archive
stats.o
report.o
rw-r--r-- 0/0  14576 Jan  1 00:00 1970 stats.o
rw-r--r-- 0/0 475632 Jan  1 00:00 1970 report.o
```

- The two `g++` commands only **compile**: `-c` means "do not link", and
  `-o` names the output file, here inside `out-linux-gcc`.
- `ar` takes its options as a bundle of letters: **`r`** puts the files
  in, **`c`** creates the archive without a warning, **`s`** writes the
  index of names that the linker will search. Then comes the library,
  then the members. Nothing is linked: `ar` only **bundles**. You
  cannot run `libstation.a`.
- `file` says `current ar archive`: not an object file, not a program,
  an **archive**.
- `ar t` lists the members (`t` for "table of contents"). `ar tv` adds
  permissions, size and date. The date 1970 and the owner `0/0` are not
  a mistake: this `ar` writes fixed values, so the same input always
  gives the same archive. Notice that `ar` stores only the **file name**
  of each member, not the folder.
- The file is called `libstation.a` on purpose. In step 3 you will see
  why: the linker looks for libraries by a name with `lib` in front and
  `.a` at the end.

#### 2. Look inside the archive

**Which names do the members define, and which do they need?** The
library holds the same two objects you would have linked by hand.
`nm` prints a header for each member, and then the names inside it:

```sh
nm -C out-linux-gcc/libstation.a | grep -E 'to_celsius|\.o:'
```

```
stats.o:
0000000000000000 T station::to_celsius(double)
report.o:
                 U station::to_celsius(double)
```

`-C` ("demangle") prints C++ names instead of codes. **`T`** = defined,
in the code ("text") section. **`U`** = undefined here: the linker must
find it. The member `stats.o` **defines** `to_celsius`, the member
`report.o` **needs** it. It is the pair you meet when you read two
object files, now sitting inside one file.

**How big is it?**

```sh
ls -l out-linux-gcc/stats.o out-linux-gcc/report.o out-linux-gcc/libstation.a
```

```
-rw-r--r-- 1 root root 550756 Oct 14 15:03 out-linux-gcc/libstation.a
-rw-r--r-- 1 root root 475632 Oct 14 15:03 out-linux-gcc/report.o
-rw-r--r-- 1 root root  14576 Oct 14 15:03 out-linux-gcc/stats.o
```

The library is **not smaller** than the objects it holds: nothing is
compressed, and it carries an index of names on top. Almost all of its
size is `report.o`, which pulls in a lot of template code for
`std::format`. Your numbers and dates will differ.

**Are the members really untouched?** Take one member back out of the
archive and compare it with the object we put in:

```sh
mkdir -p out-linux-gcc/extracted
ar x --output out-linux-gcc/extracted out-linux-gcc/libstation.a stats.o
cmp out-linux-gcc/stats.o out-linux-gcc/extracted/stats.o && echo "identical"
```

```
identical
```

`ar x` extracts, `--output` says into which folder (without it the file
lands in the current folder), and `stats.o` names the member. `cmp`
prints nothing when two files are the same, so we add an `echo` to see
the result: the two files are **identical, byte for byte**. Nothing was
rewritten and nothing was merged: the archive is a container.

#### 3. Link the program against the library

Compile `main.cpp` as usual. At the link step, name the library instead
of the object files it holds:

```sh
g++ -std=c++23 -Wall -Wextra -c main.cpp -o out-linux-gcc/main.o
g++ out-linux-gcc/main.o -Lout-linux-gcc -lstation -o out-linux-gcc/weather
./out-linux-gcc/weather
ls -l out-linux-gcc/main.o out-linux-gcc/weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
-rw-r--r-- 1 root root 493568 Oct 14 15:03 out-linux-gcc/main.o
-rwxr-xr-x 1 root root 272160 Oct 14 15:03 out-linux-gcc/weather
```

Two options on that link line deserve an explanation:

- **`-lstation`** means "find a library called `station`". The tool adds
  the `lib` in front and the `.a` at the end for you, so it looks for
  `libstation.a`. **That is why the file is called `libstation.a`.**
- **`-Lout-linux-gcc`** means "also look in this folder". Without it,
  `-lstation` searches only the standard library folders and does not
  find the library in your output folder.

`main.o` needs `summarize` and `format_report`. The linker finds both in
the index of the archive, pulls those members out and copies them into
the program. When `report.o` arrives, it needs `to_celsius`, and that
name is found in the same archive. The names a member needs join the
list of names still to find.

The program (about 270 KB) is **smaller** than the library (about
550 KB). The library is a stock of parts, and the program takes only
what it needs from it.

#### 4. Break it on purpose

**a. Leave the library out.** Link again with only `main.o`:

```sh
g++ out-linux-gcc/main.o -o out-linux-gcc/broken
```

```
/usr/bin/ld: out-linux-gcc/main.o: in function `main':
main.cpp:(.text+0x46): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
/usr/bin/ld: main.cpp:(.text+0x72): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
collect2: error: ld returned 1 exit status
```

Read it closely. The linker asks for `summarize` and `format_report`,
the two functions `main.cpp` calls. It does **not** ask for
`to_celsius`: only `report.o` calls that one, and `report.o` is inside
the library we left out.

**b. Change the order.** Put the library **before** the object that
needs it:

```sh
g++ -Lout-linux-gcc -lstation out-linux-gcc/main.o -o out-linux-gcc/broken
```

```
/usr/bin/ld: out-linux-gcc/main.o: in function `main':
main.cpp:(.text+0x46): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
/usr/bin/ld: main.cpp:(.text+0x72): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
collect2: error: ld returned 1 exit status
```

Same files, same flags, only the order changed, and the link fails with
the same message as if the library were missing. The linker reads its
inputs **left to right**, and only pulls members out of an archive to
satisfy names it **already needs**. Here it met the library first, when
nothing needed anything yet, so it pulled nothing out. The rule is
simple: **libraries go after the objects that use them.**

**c. Forget `-L`.** Name the library, but do not say where it is:

```sh
g++ out-linux-gcc/main.o -lstation -o out-linux-gcc/broken
```

```
/usr/bin/ld: cannot find -lstation: No such file or directory
collect2: error: ld returned 1 exit status
```

This one is a different kind of message: not a missing **function**, a
missing **file**. The linker searched its standard folders for
`libstation.a`, and our output folder is not one of them.

#### 5. The finished program does not need the library

Delete the library and run the program again:

```sh
rm out-linux-gcc/libstation.a
./out-linux-gcc/weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It still runs. The code it needed was **copied into** `weather` at link
time. The library was needed to **build** the program, not to **run**
it.

When you want to start over, or try another environment, delete the
folder: `rm -rf out-linux-gcc` inside the container (or
`Remove-Item -Recurse out-linux-gcc` in PowerShell on Windows). Nothing
else was touched.

That is Linux GCC done.

---

### Environment 5: Linux, Clang (Docker)

You get a real Linux with Clang from the Docker container of chapter 2.
Our image carries Clang 21.1.8 and GNU binutils 2.44, and uses GNU's
libstdc++, the C++ library that comes with Linux.

The steps:

1. Build `single.cpp` in **two steps** (compile, then link).
2. **Read** what is inside the object files and the finished binary.
3. Build `single.cpp` in **one step**.
4. Build the **multi-file** program, then break it on purpose.

#### Open the shell

From the repository root, in PowerShell:

```powershell
docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-clang
```

You land in `/workspace`, which is the repository. Now, inside the
container:

```sh
cd 07.PracticalBuiltInFeatures/7.13ProjectStaticLibrary
clang++ --version | head -1
```

```
Debian clang version 21.1.8 (++20251221033036+2078da43e25a-1~exp1~20251221153213.50)
```

(`--rm` throws the container away when you leave. The files you create
stay in your folder on Windows, in `out-linux-clang`, because of the
`-v` mount. They are ignored by git.)

#### The tools in this environment

- **`clang++`**: the Clang compiler driver. In this project we use it to
  compile (`-c`) and to link.
- **`ar`**: the **archiver**. It bundles object files into one `.a`
  file, lists what is inside (`t`) and can take a member back out
  (`x`). It does not link anything.
- **`nm`**: lists the **symbol table** of an object file or of every
  member of an archive: every name it defines or needs.
- **`file`**: guesses what a file is from its first bytes.
- **`cmp`**: compares two files byte by byte.
- **`ld`**: the GNU linker. You will not usually type it: `clang++`
  calls it, and the linker errors you get come from `/usr/bin/ld`.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```sh
mkdir -p out-linux-clang
```

(`-p` means "no error if it already exists".)

#### 1. Build the library

```
   stats.cpp  ──► compile ──► stats.o  ──┐
                                         ├──► ar ──► libstation.a
   report.cpp ──► compile ──► report.o ──┘
```

```sh
clang++ -std=c++23 -Wall -Wextra -c stats.cpp -o out-linux-clang/stats.o
clang++ -std=c++23 -Wall -Wextra -c report.cpp -o out-linux-clang/report.o
ar rcs out-linux-clang/libstation.a out-linux-clang/stats.o out-linux-clang/report.o
file out-linux-clang/libstation.a
ar t out-linux-clang/libstation.a
ar tv out-linux-clang/libstation.a
```

```
out-linux-clang/libstation.a: current ar archive
stats.o
report.o
rw-r--r-- 0/0  18200 Jan  1 00:00 1970 stats.o
rw-r--r-- 0/0 389104 Jan  1 00:00 1970 report.o
```

- The two `clang++` commands only **compile**: `-c` means "do not
  link", and `-o` names the output file, here inside `out-linux-clang`.
- `ar` takes its options as a bundle of letters: **`r`** puts the files
  in, **`c`** creates the archive without a warning, **`s`** writes the
  index of names that the linker will search. Then comes the library,
  then the members. Nothing is linked: `ar` only **bundles**. You
  cannot run `libstation.a`.
- `file` says `current ar archive`: not an object file, not a program,
  an **archive**.
- `ar t` lists the members (`t` for "table of contents"). `ar tv` adds
  permissions, size and date. The date 1970 and the owner `0/0` are not
  a mistake: this `ar` writes fixed values, so the same input always
  gives the same archive. Notice that `ar` stores only the **file name**
  of each member, not the folder.
- The file is called `libstation.a` on purpose. In step 3 you will see
  why: the linker looks for libraries by a name with `lib` in front and
  `.a` at the end.

#### 2. Look inside the archive

**Which names do the members define, and which do they need?** The
library holds the same two objects you would have linked by hand.
`nm` prints a header for each member, and then the names inside it:

```sh
nm -C out-linux-clang/libstation.a | grep -E 'to_celsius|\.o:'
```

```
stats.o:
0000000000000000 T station::to_celsius(double)
report.o:
                 U station::to_celsius(double)
```

`-C` ("demangle") prints C++ names instead of codes. **`T`** = defined,
in the code ("text") section. **`U`** = undefined here: the linker must
find it. The member `stats.o` **defines** `to_celsius`, the member
`report.o` **needs** it. It is the pair you meet when you read two
object files, now sitting inside one file.

**How big is it?**

```sh
ls -l out-linux-clang/stats.o out-linux-clang/report.o out-linux-clang/libstation.a
```

```
-rw-r--r-- 1 root root 459248 Oct 14 15:03 out-linux-clang/libstation.a
-rw-r--r-- 1 root root 389104 Oct 14 15:03 out-linux-clang/report.o
-rw-r--r-- 1 root root  18200 Oct 14 15:03 out-linux-clang/stats.o
```

The library is **not smaller** than the objects it holds: nothing is
compressed, and it carries an index of names on top. Almost all of its
size is `report.o`, which pulls in a lot of template code for
`std::format`. Your numbers and dates will differ.

**Are the members really untouched?** Take one member back out of the
archive and compare it with the object we put in:

```sh
mkdir -p out-linux-clang/extracted
ar x --output out-linux-clang/extracted out-linux-clang/libstation.a stats.o
cmp out-linux-clang/stats.o out-linux-clang/extracted/stats.o && echo "identical"
```

```
identical
```

`ar x` extracts, `--output` says into which folder (without it the file
lands in the current folder), and `stats.o` names the member. `cmp`
prints nothing when two files are the same, so we add an `echo` to see
the result: the two files are **identical, byte for byte**. Nothing was
rewritten and nothing was merged: the archive is a container.

#### 3. Link the program against the library

Compile `main.cpp` as usual. At the link step, name the library instead
of the object files it holds:

```sh
clang++ -std=c++23 -Wall -Wextra -c main.cpp -o out-linux-clang/main.o
clang++ out-linux-clang/main.o -Lout-linux-clang -lstation -o out-linux-clang/weather
./out-linux-clang/weather
ls -l out-linux-clang/main.o out-linux-clang/weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
-rw-r--r-- 1 root root 410280 Oct 14 15:03 out-linux-clang/main.o
-rwxr-xr-x 1 root root 229744 Oct 14 15:03 out-linux-clang/weather
```

Two options on that link line deserve an explanation:

- **`-lstation`** means "find a library called `station`". The tool adds
  the `lib` in front and the `.a` at the end for you, so it looks for
  `libstation.a`. **That is why the file is called `libstation.a`.**
- **`-Lout-linux-clang`** means "also look in this folder". Without it,
  `-lstation` searches only the standard library folders and does not
  find the library in your output folder.

`main.o` needs `summarize` and `format_report`. The linker finds both in
the index of the archive, pulls those members out and copies them into
the program. When `report.o` arrives, it needs `to_celsius`, and that
name is found in the same archive. The names a member needs join the
list of names still to find.

The program (about 230 KB) is **smaller** than the library (about
460 KB). The library is a stock of parts, and the program takes only
what it needs from it.

#### 4. Break it on purpose

**a. Leave the library out.** Link again with only `main.o`:

```sh
clang++ out-linux-clang/main.o -o out-linux-clang/broken
```

```
/usr/bin/ld: out-linux-clang/main.o: in function `main':
main.cpp:(.text+0x91): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
/usr/bin/ld: main.cpp:(.text+0xe0): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

Read it closely. The linker asks for `summarize` and `format_report`,
the two functions `main.cpp` calls. It does **not** ask for
`to_celsius`: only `report.o` calls that one, and `report.o` is inside
the library we left out.

**b. Change the order.** Put the library **before** the object that
needs it:

```sh
clang++ -Lout-linux-clang -lstation out-linux-clang/main.o -o out-linux-clang/broken
```

```
/usr/bin/ld: out-linux-clang/main.o: in function `main':
main.cpp:(.text+0x91): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
/usr/bin/ld: main.cpp:(.text+0xe0): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

Same files, same flags, only the order changed, and the link fails with
the same message as if the library were missing. The linker reads its
inputs **left to right**, and only pulls members out of an archive to
satisfy names it **already needs**. Here it met the library first, when
nothing needed anything yet, so it pulled nothing out. The rule is
simple: **libraries go after the objects that use them.**

**c. Forget `-L`.** Name the library, but do not say where it is:

```sh
clang++ out-linux-clang/main.o -lstation -o out-linux-clang/broken
```

```
/usr/bin/ld: cannot find -lstation: No such file or directory
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

This one is a different kind of message: not a missing **function**, a
missing **file**. The linker searched its standard folders for
`libstation.a`, and our output folder is not one of them.

#### 5. The finished program does not need the library

Delete the library and run the program again:

```sh
rm out-linux-clang/libstation.a
./out-linux-clang/weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It still runs. The code it needed was **copied into** `weather` at link
time. The library was needed to **build** the program, not to **run**
it.

When you want to start over, or try another environment, delete the
folder: `rm -rf out-linux-clang` inside the container (or
`Remove-Item -Recurse out-linux-clang` in PowerShell on Windows).
Nothing else was touched.

That is Linux Clang done.

---

### What a static library is good for

The good:

- The finished program is self-contained: one file to ship, nothing to
  lose or mismatch at run time.
- Only the members the program needs are copied in.

The not so good:

- Every program that uses the library gets its **own copy** of the code.
- To fix a bug in the library you must **relink every program** that
  uses it.

We checked the second "good" point with a three-line program that only
calls `to_celsius`. The linker took the `stats` member and left the
`report` member out, on MSVC, GCC and Clang alike. It took `stats`
**whole**: `summarize` came along although nobody called it. A member
is copied in completely or not at all, which is one more reason to keep
the files of a library small and focused.

### Gotchas to take away

A summary of what you met. Each point was shown in the environment where
it applies.

- A static library is an **archive** of object files. Nothing is
  rewritten, nothing is merged, and nothing is linked until a program
  asks for a name.
- With `g++` and `clang++`, **libraries go after the objects that use
  them**, and `-lname` needs `-L<folder>` unless the library lives in a
  standard folder. MSVC's `link` takes the real file name and does not
  mind the order.
- Compile the library and the program with the **same settings**: with
  MSVC the C runtime option (`/MD` everywhere), and in every
  environment the language standard and debug or release. Mixing them is
  how `LNK2038` appears.
- Once the program is linked, the **library is no longer needed** to run
  it.

---

## 7.14 Project: a dynamic library

A **dynamic library** (also called a **shared library**) is not copied
into the program. It stays a separate file, and the program **finds it
and loads it when it starts**. On Windows it is a **DLL**, on Linux a
**`.so`** (shared object).

```
   STATIC (7.13)                               DYNAMIC (this lecture)

   weather                                     weather ──────────┐
   ┌───────────────────────┐                   ┌───────────┐     │ loads at startup
   │ main code             │                   │ main code │     ▼
   │ stats code   (copy)   │                   └───────────┘   station.dll   (one file,
   │ report code  (copy)   │                                    libstation.so   shared by
   └───────────────────────┘                                    every program that uses it)
   one file, self-contained                    two files: both are needed
```

With a static library, the library was needed only **while linking**.
With a dynamic library it is needed **every time the program runs**.
That one difference brings in a handful of new ideas, and this project
walks you through each of them.

### What is new

**The loader.** When you start a program, the operating system has a
part called the **loader**. Its job is to read the program, find every
library it needs, load them into memory and only then start `main`. With
a static library there was nothing to find. With a dynamic library the
loader has to **locate the file at run time**, and if it cannot, your
program never starts.

**Exporting and importing.** A static library hands over every function
it has. A DLL is stricter: on Windows it **exports nothing unless you
ask**. You mark each function you want the outside world to see. The
marking is different on each side of the boundary:

- When the DLL itself is being compiled, the function is
  `__declspec(dllexport)`: "I provide this".
- When a program that uses the DLL is compiled, the same function is
  `__declspec(dllimport)`: "this lives in a DLL".

One header can serve both, with a macro that is switched by a flag that
only the library build passes. That is the new file in this folder,
`station_api.h`:

```cpp
#if defined(_WIN32)
    #if defined(STATION_BUILD_DLL)
        #define STATION_API __declspec(dllexport)
    #else
        #define STATION_API __declspec(dllimport)
    #endif
#else
    #define STATION_API __attribute__((visibility("default")))
#endif

STATION_API double to_celsius(double fahrenheit);
```

The `STATION_API` in front of the three public functions (`to_celsius`,
`summarize`, `format_report`) is the only change to the code. On Linux
every function is exported by default, which is not always what you
want. Compiling with **`-fvisibility=hidden`** reverses that for your
own code, so only the functions marked `STATION_API` are visible: the
same "opt in" rule as Windows.

**The import library.** On Windows, the linker cannot learn from a DLL
alone which names it holds. So building a DLL also produces a small
**import library**. It has the same `.lib` (MSVC) or `.dll.a` (MinGW)
look as a static library, and a very different job: it holds **only a
list of names and the DLL they live in**, no code. It is a signpost.
Linux has no import library: the `.so` file serves both as the thing the
linker reads and the thing the program loads.

**Where the loader looks.** The loader does not search your whole disk.
It has a short list of places, and on each system the list is different:

- **Windows**: the folder of the `.exe` first, then the folders on your
  **PATH**.
- **Linux**: the system's standard library folders, any folders in the
  **`LD_LIBRARY_PATH`** variable, and a folder that was **baked into the
  program** when it was linked (the **rpath**).

**Position-independent code.** Several programs may load the same `.so`,
each at a **different address** in memory. So the library's code must
not assume where it lives. The compiler flag **`-fPIC`**
("position-independent code") produces code like that. Windows DLLs
handle this differently, so you will only see the flag on Linux.

You have in fact seen dynamic libraries already. In 7.12,
`dumpbin /dependents` and `ldd` listed DLLs and `.so` files such as
`MSVCP140.dll` and `libstdc++.so.6`: that is the C++ standard library,
loaded by the loader exactly the way our `station` library will be. And
`/MD` meant "use the shared (dynamic) C runtime".

### The files you will build

All the source files are in `7.14ProjectDynamicLibrary`. They are the
same weather-station files as before, plus two new ones:

```
   stats.h / stats.cpp     summarize(readings) and to_celsius(f)               ─┐ the library
   report.h / report.cpp   format_report(sensor, summary), which CALLS         ─┘
                           to_celsius
   station_api.h           the STATION_API macro (new)
   main.cpp                builds the readings, calls both, prints             the program
   report_v2.cpp           a second version of format_report (new, step 6)
```

### Pick your environment

The project has **five environments**. Every one of them is a complete
walk-through that you can do without reading any other. Do the one you
have, and come back for the others if you are curious. In each one you
will do the same six things:

1. **Build the library**: compile the two library files into one DLL or
   `.so`.
2. **Look inside** the library: which names does it export?
3. **Link the program** against the library, and ask the finished
   program what it needs at start-up.
4. **Run it**, and see where the loader looks.
5. **Break it** on purpose.
6. **Replace the library** with a second version, **without relinking**
   the program.

| Environment | Compiler driver | Library file(s) | Output folder |
|---|---|---|---|
| Windows, MSVC | `cl` | `station.dll` + `station.lib` (import library) | `out-msvc` |
| Windows, MinGW GCC | `g++` | `station.dll` + `libstation.dll.a` (import library) | `out-mingw-gcc` |
| Windows, MinGW Clang | `clang++` | `station.dll` + `libstation.dll.a` (import library) | `out-mingw-clang` |
| Linux, GCC (Docker) | `g++` | `libstation.so` | `out-linux-gcc` |
| Linux, Clang (Docker) | `clang++` | `libstation.so` | `out-linux-clang` |

Every environment writes **everything it produces** (libraries,
programs, even the ones you build to fail) into **its own output
folder**, the one in the last column, inside
`7.14ProjectDynamicLibrary`. Your source folder stays clean, and when
you are done you delete **one folder** to start over or to try another
environment. Git ignores every `out-*` folder.

Every folder in this project also has one script per environment
(`build-msvc.ps1`, `build-mingw-gcc.ps1`, `build-mingw-clang.ps1`,
`build-linux-gcc.sh`, `build-linux-clang.sh`) that runs the commands of
that environment from top to bottom. Type the commands yourself first,
and use the scripts to check your work. (A script and your own commands
fill the same output folder, so delete the folder between the two if you
want to be sure the script did the work. The Windows scripts leave out
the step where a DLL goes missing, because Windows may show a dialog box
and wait for a click.)

---

### Environment 1: Windows, MSVC

MSVC is Microsoft's C++ compiler, the one Visual Studio uses and the
reference compiler of this course. Our version is `cl` 19.51 (Visual
Studio 2026).

#### Open the shell

Open **Developer PowerShell for VS** from the Start menu. That is an
ordinary PowerShell that already knows where the Microsoft tools are.
(From any other PowerShell you can load it by hand:
`& "<your VS folder>\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64`.)
Then, from the repository root:

```powershell
cd 07.PracticalBuiltInFeatures\7.14ProjectDynamicLibrary
cl
```

`cl` on its own prints a banner. Ours starts with
`Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36260 for x64`.
If you see it, the shell is ready.

#### The tools in this environment

- **`cl`**: the compiler driver. This time it does everything in one
  command: with `/LD` it compiles the sources and then runs the linker
  to make a **DLL**.
- **`link`**: the linker. `cl` calls it for us here, and it is the one
  that writes the DLL and the import library.
- **`dumpbin`**: Microsoft's "dump a binary" tool. It reads object
  files, libraries, DLLs and executables and prints what is inside. It
  only reads: it never changes the file. We use it to list a DLL's
  **exports** and a program's **dependents**.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-msvc
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Build the library

```
   stats.cpp  ─┐
               ├──► cl /LD ──► station.dll    the code
   report.cpp ─┘               station.lib    the import library: names only
                               station.exp    a by-product you can ignore
```

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /DSTATION_BUILD_DLL /LD stats.cpp report.cpp /Fo:out-msvc\ /Fe:out-msvc\station.dll
Get-ChildItem out-msvc | Format-Table Name, Length -AutoSize
```

```
stats.cpp
report.cpp
Generating Code...
   Creating library out-msvc\station.lib and object out-msvc\station.exp

Name         Length
----         ------
report.obj   746033
station.dll  309248
station.exp    1584
station.lib    3196
stats.obj     22469
```

- `/LD` builds a **DLL** instead of an executable. (The sizes of the
  `.obj` and `.exp` files change a little with the folder you build in,
  so yours will differ slightly.)
- `/DSTATION_BUILD_DLL` defines the macro for this build only, so
  `STATION_API` means `dllexport` while the library is compiled.
- `/Fo:out-msvc\` says which **folder** gets the object files (the
  trailing backslash is what tells `cl` it is a folder).
  `/Fe:out-msvc\station.dll` names the output file, and `cl` puts the
  import library and the `.exp` file next to it.
- `/std:c++latest` is the newest language mode (never `/std:c++23` with
  `cl`), `/EHsc` turns on normal exception handling, and `/MD` picks the
  **shared C runtime**, which is also what CMake uses by default.

**`station.lib` here is not a static library.** It has the same
extension as the static library of 7.13 and a very different job. That
one held all the code. This one is **3,196 bytes**, because it holds
**only a list of names and the DLL they live in**. It is the signpost:
the linker will read it to learn "`to_celsius` lives in `station.dll`".
The code itself is in `station.dll`.

#### 2. Look inside the library

```powershell
dumpbin /exports out-msvc\station.dll
```

```
  Section contains the following exports for station.dll

           1 ordinal base
           3 number of functions
           3 number of names

    ordinal hint RVA      name

          1    0 00001C40 ?format_report@station@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$basic_string_view@DU?$char_traits@D@std@@@3@AEBUSummary@1@@Z
          2    1 00001040 ?summarize@station@@YA?AUSummary@1@AEBV?$vector@NV?$allocator@N@std@@@std@@@Z
          3    2 00001010 ?to_celsius@station@@YANN@Z
```

(`dumpbin` prints more: a banner, the file type and a size summary. We
left those out.) **Three exports**: the three functions we marked with
`STATION_API`. On Windows that is the whole table, and it is the
**public face** of the DLL: the only names a program can reach. The
names are the same mangled names you read in 7.12. (An *ordinal* is just
a number for each export, and the *RVA* is where its code sits inside
the DLL. You can ignore both.)

#### 3. Link the program, and ask what it needs

The program is linked against the **signpost**, the import library, not
against the DLL:

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 main.cpp out-msvc\station.lib /Fo:out-msvc\ /Fe:out-msvc\weather.exe
```

Notice that `main.cpp` is compiled **without** `/DSTATION_BUILD_DLL`, so
there `STATION_API` means `dllimport`: "this function lives in a DLL".
Now ask the finished program what it needs when it **starts**:

```powershell
dumpbin /dependents out-msvc\weather.exe | Select-String 'station|MSVCP'
```

```
    station.dll
    MSVCP140.dll
```

`station.dll` is now on the program's **list of requirements**. It is
not inside the program. This is the big difference from 7.13. The second
line is the C++ standard library, another DLL, which Windows finds the
same way.

#### 4. Run it

```powershell
.\out-msvc\weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It works because `station.dll` sits **in the same folder as
`weather.exe`**, and the Windows loader looks in the **folder of the
program first**. Here is the second place it looks. Copy the program to
another folder, where there is no DLL beside it:

```powershell
New-Item -ItemType Directory out-msvc\elsewhere
Copy-Item out-msvc\weather.exe out-msvc\elsewhere\
.\out-msvc\elsewhere\weather.exe
$LASTEXITCODE
```

```
-1073741515
```

Nothing is printed, and the exit code `-1073741515` is Windows' way of
saying "a DLL was not found". (On your desktop you may also see a dialog
box naming `station.dll`. Click OK.) Now add the folder that **does**
have the DLL to the **PATH** of this window and run it again:

```powershell
$env:Path = "$PWD\out-msvc;$env:Path"
.\out-msvc\elsewhere\weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

The loader found `station.dll` through the PATH.

#### 5. Break it on purpose

**a. Take the library away.** Rename the DLL and run the program from
its own folder:

```powershell
Rename-Item out-msvc\station.dll station.dll.away
.\out-msvc\weather.exe
$LASTEXITCODE
```

```
-1073741515
```

The same exit code as before. The program linked fine, because the
import library was there. It cannot **start**, because the DLL is gone.
This is the first kind of failure that a static library never had: a
build that succeeded and a program that does not run. Rename it back
before you go on:

```powershell
Rename-Item out-msvc\station.dll.away station.dll
```

**b. Leave the library out of the link.** Compile `main.cpp` without the
import library:

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 main.cpp /Fo:out-msvc\ /Fe:out-msvc\broken.exe
```

```
main.obj : error LNK2019: unresolved external symbol "__declspec(dllimport) struct station::Summary __cdecl station::summarize(class std::vector<double,class std::allocator<double> > const &)" (__imp_?summarize@station@@YA?AUSummary@1@AEBV?$vector@NV?$allocator@N@std@@@std@@@Z) referenced in function main
main.obj : error LNK2019: unresolved external symbol "__declspec(dllimport) class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl station::format_report(...)" (__imp_?format_report@station@@YA?AV?$basic_string@...@Z) referenced in function main
out-msvc\broken.exe : fatal error LNK1120: 2 unresolved externals
```

(The long second name is shortened with `...`.) Read it closely. The
linker asks for `summarize` and `format_report`, the two functions
`main.cpp` calls. Two new details: the message says
**`__declspec(dllimport)`**, the macro doing its job, and the mangled
name starts with **`__imp_`**, "import": the program expects to reach
the function **through a DLL**. Only the import library can tell the
linker where that is.

#### 6. Replace the library without relinking the program

The great strength of a dynamic library: you can fix or change the
library and **ship one file**. `report_v2.cpp` has a second version of
`format_report` with the same name, the same parameters and the same
result type, and a different text. Build a library from `stats.cpp` and
`report_v2.cpp` into a separate folder, copy the new DLL over the old
one, and run the **same `weather.exe`**:

```powershell
New-Item -ItemType Directory out-msvc\v2
cl /nologo /std:c++latest /EHsc /MD /W4 /DSTATION_BUILD_DLL /LD stats.cpp report_v2.cpp /Fo:out-msvc\v2\ /Fe:out-msvc\v2\station.dll
Copy-Item out-msvc\v2\station.dll out-msvc\station.dll -Force
.\out-msvc\weather.exe
```

```
[v2] sensor-12: min 12.8 C, max 32.5 C, mean 21.6 C
```

`weather.exe` was not compiled or linked again, and its new output
proves it loaded the new library. With the static library of 7.13 you
would have had to **relink every program** that used it. The condition
is that the **interface stays the same**: same names, same parameter
types. The program only checks the names, and nothing checks that the
code behind them still behaves.

That is MSVC done.

---

### Environment 2: Windows, MinGW GCC

**MinGW-w64** brings the GNU tool chain (GCC, binutils) to Windows. The
programs it makes are ordinary Windows programs. Ours is a UCRT build by
Brecht Sanders: `g++ --version` says
`g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r2) 14.2.0`.

#### Open the shell

Open a normal PowerShell and put `C:\mingw64\bin` on the PATH **for this
window**, then go to the folder (from the repository root):

```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
cd 07.PracticalBuiltInFeatures\7.14ProjectDynamicLibrary
g++ --version
```

If you see a version banner, you are ready.

#### The tools in this environment

- **`g++`**: the GCC compiler driver. With `-shared` it compiles the
  sources and then runs the linker to make a **DLL**.
- **`-Wl,<option>`**: not a program but a way to hand an option **to the
  linker**. We use it to ask for the import library (`--out-implib`).
- **`ld`**: the GNU linker. You will not usually type it: `g++` calls
  it, and the linker errors you get come from `ld.exe`.
- **`objdump`**: prints information about object files, DLLs and
  executables. With `-p` it shows a DLL's **export table** and the
  **DLLs a program needs** (the `DLL Name` lines).
- **`-lstdc++exp`**: a library option (`-l` means "link this library").
  On our MinGW GCC 14, `std::println` needs this extra library ("the
  experimental part of the C++ library"). It goes **after** everything
  that needs it. Only the program needs it: the library does not call
  `println`.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-mingw-gcc
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Build the library

```
   stats.cpp  ─┐
               ├──► g++ -shared ──► station.dll       the code
   report.cpp ─┘                       libstation.dll.a   the import library: names only
```

```powershell
g++ -std=c++23 -Wall -Wextra -DSTATION_BUILD_DLL -shared stats.cpp report.cpp -o out-mingw-gcc\station.dll '-Wl,--out-implib,out-mingw-gcc\libstation.dll.a'
Get-ChildItem out-mingw-gcc | Format-Table Name, Length -AutoSize
```

```
Name             Length
----             ------
libstation.dll.a   3400
station.dll      478558
```

- `-shared` makes a **DLL** instead of an executable.
- `-DSTATION_BUILD_DLL` defines the macro for this build only, so
  `STATION_API` means `dllexport` while the library is compiled.
- `-Wl,--out-implib,...` hands an option to the linker: also write the
  **import library**, `libstation.dll.a`, in the folder we name. It is
  3,400 bytes, because it holds **only a list of names and the DLL they
  live in**. It is the signpost, not the code.
- `-std=c++23` selects the language mode, `-Wall -Wextra` ask for more
  warnings, and `-o` names the DLL.

> **PowerShell gotcha.** The quotes around `-Wl,--out-implib,...`
> matter. PowerShell reads a comma as "a list of values" and the command
> fails with *Missing argument in parameter list*. In `cmd` or on Linux
> you do not need the quotes.

#### 2. Look inside the library

```powershell
objdump -p out-mingw-gcc\station.dll | Select-String 'station'
```

```
out-mingw-gcc\station.dll:     file format pei-x86-64
Name 				0000000000024046 station.dll
	[   0] +base[   1]  0000 _ZN7station10to_celsiusEd
	[   1] +base[   2]  0001 _ZN7station13format_reportB5cxx11ESt17basic_string_viewIcSt11char_traitsIcEERKNS_7SummaryE
	[   2] +base[   3]  0002 _ZN7station9summarizeERKSt6vectorIdSaIdEE
```

(`objdump -p` prints a lot more. We filtered for `station`.) **Three
exports**: the three functions we marked with `STATION_API`. On Windows
that is the whole export table, and it is the **public face** of the
DLL: the only names a program can reach. The names are the
Itanium-mangled names you read in 7.12.

Look closely at the middle one, `format_reportB5cxx11`. That `B5cxx11`
is a **tag meaning "returns the C++11 flavour of `std::string`"**.
libstdc++, the C++ library that GCC and Clang use here, changed the
layout of `std::string` in 2015, and the tag lets old and new code tell
each other apart instead of crashing. This is the ABI showing up in a
name.

#### 3. Link the program, and ask what it needs

The program is linked against the **signpost**, the import library, not
against the DLL:

```powershell
g++ -std=c++23 -Wall -Wextra main.cpp -Lout-mingw-gcc -lstation -o out-mingw-gcc\weather.exe -lstdc++exp
```

`-Lout-mingw-gcc` says "also search this folder", and `-lstation` means
"find a library called `station`": the linker looks for
`libstation.dll.a`. Now ask the finished program what it needs when it
**starts**:

```powershell
objdump -p out-mingw-gcc\weather.exe | Select-String 'DLL Name: (station|libstdc)'
```

```
	DLL Name: libstdc++-6.dll
	DLL Name: station.dll
```

`station.dll` is now on the program's **list of requirements**. It is
not inside the program. This is the big difference from 7.13. The other
line is the C++ standard library, another DLL, which lives in
`C:\mingw64\bin`. That is why a MinGW program only starts from a window
where that folder is on the PATH.

#### 4. Run it

```powershell
.\out-mingw-gcc\weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It works because `station.dll` sits **in the same folder as
`weather.exe`**, and the Windows loader looks in the **folder of the
program first**. Here is the second place it looks. Copy the program to
another folder, where there is no DLL beside it:

```powershell
New-Item -ItemType Directory out-mingw-gcc\elsewhere
Copy-Item out-mingw-gcc\weather.exe out-mingw-gcc\elsewhere\
.\out-mingw-gcc\elsewhere\weather.exe
$LASTEXITCODE
```

```
-1073741515
```

Nothing is printed, and the exit code `-1073741515` is Windows' way of
saying "a DLL was not found". (On your desktop you may also see a dialog
box naming `station.dll`. Click OK.) Now add the folder that **does**
have the DLL to the **PATH** of this window and run it again:

```powershell
$env:Path = "$PWD\out-mingw-gcc;$env:Path"
.\out-mingw-gcc\elsewhere\weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

The loader found `station.dll` through the PATH.

#### 5. Break it on purpose

**a. Take the library away.** Rename the DLL and run the program from
its own folder:

```powershell
Rename-Item out-mingw-gcc\station.dll station.dll.away
.\out-mingw-gcc\weather.exe
$LASTEXITCODE
```

```
-1073741515
```

The same exit code as before. The program linked fine, because the
import library was there. It cannot **start**, because the DLL is gone.
This is the first kind of failure that a static library never had: a
build that succeeded and a program that does not run. Rename it back
before you go on:

```powershell
Rename-Item out-mingw-gcc\station.dll.away station.dll
```

**b. Leave the library out of the link.** Compile `main.cpp` without
naming the library:

```powershell
g++ -std=c++23 -Wall -Wextra main.cpp -o out-mingw-gcc\broken.exe -lstdc++exp
```

```
...ld.exe: ...Temp\ccj4TosJ.o:main.cpp:(.text+0x6a): undefined reference to `__imp__ZN7station9summarizeERKSt6vectorIdSaIdEE'
...ld.exe: ...Temp\ccj4TosJ.o:main.cpp:(.text+0xb1): undefined reference to `__imp__ZN7station13format_reportB5cxx11ESt17basic_string_viewIcSt11char_traitsIcEERKNS_7SummaryE'
collect2.exe: error: ld returned 1 exit status
```

(Paths shortened.) Read it closely. The linker asks for `summarize` and
`format_report`, the two functions `main.cpp` calls. The names start
with **`__imp_`**, "import": the program expects to reach the function
**through a DLL**, and without the import library the linker has no idea
where that is.

**c. Name the library, but not the folder.**

```powershell
g++ -std=c++23 -Wall -Wextra main.cpp -lstation -o out-mingw-gcc\broken.exe -lstdc++exp
```

```
...ld.exe: cannot find -lstation: No such file or directory
collect2.exe: error: ld returned 1 exit status
```

A different kind of message: not a missing **function**, a missing
**file**. The linker searched its standard folders for
`libstation.dll.a`, and our output folder is not one of them.

#### 6. Replace the library without relinking the program

The great strength of a dynamic library: you can fix or change the
library and **ship one file**. `report_v2.cpp` has a second version of
`format_report` with the same name, the same parameters and the same
result type, and a different text. Build a library from `stats.cpp` and
`report_v2.cpp` into a separate folder, copy the new DLL over the old
one, and run the **same `weather.exe`**:

```powershell
New-Item -ItemType Directory out-mingw-gcc\v2
g++ -std=c++23 -Wall -Wextra -DSTATION_BUILD_DLL -shared stats.cpp report_v2.cpp -o out-mingw-gcc\v2\station.dll '-Wl,--out-implib,out-mingw-gcc\v2\libstation.dll.a'
Copy-Item out-mingw-gcc\v2\station.dll out-mingw-gcc\station.dll -Force
.\out-mingw-gcc\weather.exe
```

```
[v2] sensor-12: min 12.8 C, max 32.5 C, mean 21.6 C
```

`weather.exe` was not compiled or linked again, and its new output
proves it loaded the new library. With the static library of 7.13 you
would have had to **relink every program** that used it. The condition
is that the **interface stays the same**: same names, same parameter
types. The program only checks the names, and nothing checks that the
code behind them still behaves.

That is MinGW GCC done.

---

### Environment 3: Windows, MinGW Clang

**MinGW-w64** brings the GNU tool chain to Windows, and its package also
contains the **Clang** compiler. The programs it makes are ordinary
Windows programs. Clang here uses MinGW's libstdc++ (the one of GCC 16.2)
and, for the final link of a program, LLVM's own linker **lld**.
Ours is a UCRT build by Brecht Sanders in `C:\mingw64`:
`clang++ --version` says `clang version 23.1.3` and
`Target: x86_64-w64-windows-gnu`.

#### Open the shell

Open a normal PowerShell and put `C:\mingw64\bin` on the PATH **for this
window**, then go to the folder (from the repository root):

```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
cd 07.PracticalBuiltInFeatures\7.14ProjectDynamicLibrary
clang++ --version
```

If you see a version banner, you are ready.

#### The tools in this environment

- **`clang++`**: the Clang compiler driver. With `-shared` it compiles
  the sources and then runs the linker to make a **DLL**.
- **`-Wl,<option>`**: not a program but a way to hand an option **to the
  linker**. We use it to ask for the import library (`--out-implib`).
- **`ld` and `lld`**: the GNU and the LLVM linker. You will not usually
  type them: `clang++` calls one of them. It uses the GNU `ld` for the
  DLL and, because we add `-fuse-ld=lld`, the LLVM `lld` for the program
  (the reason is the gotcha in 7.12). The linker errors you get come
  from whichever one ran, and you will see its name in them.
- **`objdump`**: prints information about object files, DLLs and
  executables. With `-p` it shows a DLL's **export table** and the
  **DLLs a program needs** (the `DLL Name` lines).
- **`-lstdc++exp`**: a library option (`-l` means "link this library").
  On MinGW, `std::println` needs this extra library ("the experimental
  part of the C++ library"). Put it **after** everything that needs it.
  Only the program needs it: the library does not call `println`.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```powershell
mkdir out-mingw-clang
```

(If it already exists from an earlier run, PowerShell says so. That is
harmless.)

#### 1. Build the library

```
   stats.cpp  ─┐
               ├──► clang++ -shared ──► station.dll       the code
   report.cpp ─┘                       libstation.dll.a   the import library: names only
```

```powershell
clang++ -std=c++23 -Wall -Wextra -DSTATION_BUILD_DLL -shared stats.cpp report.cpp -o out-mingw-clang\station.dll '-Wl,--out-implib,out-mingw-clang\libstation.dll.a'
Get-ChildItem out-mingw-clang | Format-Table Name, Length -AutoSize
```

```
Name             Length
----             ------
libstation.dll.a   3400
station.dll      497812
```

- `-shared` makes a **DLL** instead of an executable.
- `-DSTATION_BUILD_DLL` defines the macro for this build only, so
  `STATION_API` means `dllexport` while the library is compiled.
- `-Wl,--out-implib,...` hands an option to the linker: also write the
  **import library**, `libstation.dll.a`, in the folder we name. It is
  3,400 bytes, because it holds **only a list of names and the DLL they
  live in**. It is the signpost, not the code.
- `-std=c++23` selects the language mode, `-Wall -Wextra` ask for more
  warnings, and `-o` names the DLL.

> **PowerShell gotcha.** The quotes around `-Wl,--out-implib,...`
> matter. PowerShell reads a comma as "a list of values" and the command
> fails with *Missing argument in parameter list*. In `cmd` or on Linux
> you do not need the quotes.

#### 2. Look inside the library

```powershell
objdump -p out-mingw-clang\station.dll | Select-String 'station'
```

```
out-mingw-clang\station.dll:     file format pei-x86-64
Name 				000000000002c046 station.dll
	[   0] +base[   1]  0000 _ZN7station10to_celsiusEd
	[   1] +base[   2]  0001 _ZN7station13format_reportB5cxx11ESt17basic_string_viewIcSt11char_traitsIcEERKNS_7SummaryE
	[   2] +base[   3]  0002 _ZN7station9summarizeERKSt6vectorIdSaIdEE
```

(`objdump -p` prints a lot more. We filtered for `station`.) **Three
exports**: the three functions we marked with `STATION_API`. On Windows
that is the whole export table, and it is the **public face** of the
DLL: the only names a program can reach. The names are the
Itanium-mangled names you read in 7.12.

Look closely at the middle one, `format_reportB5cxx11`. That `B5cxx11`
is a **tag meaning "returns the C++11 flavour of `std::string`"**.
libstdc++, the C++ library that GCC and Clang use here, changed the
layout of `std::string` in 2015, and the tag lets old and new code tell
each other apart instead of crashing. This is the ABI showing up in a
name.

#### 3. Link the program, and ask what it needs

The program is linked against the **signpost**, the import library, not
against the DLL:

```powershell
clang++ -std=c++23 -Wall -Wextra main.cpp -Lout-mingw-clang -lstation -o out-mingw-clang\weather.exe -fuse-ld=lld -lstdc++exp
```

`-Lout-mingw-clang` says "also search this folder", and `-lstation`
means "find a library called `station`": the linker looks for
`libstation.dll.a`. (`-fuse-ld=lld` and `-lstdc++exp` are the MinGW
extras of 7.12.) Now ask the finished program what it needs when it
**starts**:

```powershell
objdump -p out-mingw-clang\weather.exe | Select-String 'DLL Name: (station|libstdc)'
```

```
	DLL Name: libstdc++-6.dll
	DLL Name: station.dll
```

`station.dll` is now on the program's **list of requirements**. It is
not inside the program. This is the big difference from 7.13. The other
line is the C++ standard library, another DLL, which lives in
`C:\mingw64\bin`. That is why a MinGW program only starts from a window
where that folder is on the PATH.

#### 4. Run it

```powershell
.\out-mingw-clang\weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

It works because `station.dll` sits **in the same folder as
`weather.exe`**, and the Windows loader looks in the **folder of the
program first**. Here is the second place it looks. Copy the program to
another folder, where there is no DLL beside it:

```powershell
New-Item -ItemType Directory out-mingw-clang\elsewhere
Copy-Item out-mingw-clang\weather.exe out-mingw-clang\elsewhere\
.\out-mingw-clang\elsewhere\weather.exe
$LASTEXITCODE
```

```
-1073741515
```

Nothing is printed, and the exit code `-1073741515` is Windows' way of
saying "a DLL was not found". (On your desktop you may also see a dialog
box naming `station.dll`. Click OK.) Now add the folder that **does**
have the DLL to the **PATH** of this window and run it again:

```powershell
$env:Path = "$PWD\out-mingw-clang;$env:Path"
.\out-mingw-clang\elsewhere\weather.exe
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

The loader found `station.dll` through the PATH.

#### 5. Break it on purpose

**a. Take the library away.** Rename the DLL and run the program from
its own folder:

```powershell
Rename-Item out-mingw-clang\station.dll station.dll.away
.\out-mingw-clang\weather.exe
$LASTEXITCODE
```

```
-1073741515
```

The same exit code as before. The program linked fine, because the
import library was there. It cannot **start**, because the DLL is gone.
This is the first kind of failure that a static library never had: a
build that succeeded and a program that does not run. Rename it back
before you go on:

```powershell
Rename-Item out-mingw-clang\station.dll.away station.dll
```

**b. Leave the library out of the link.** Compile `main.cpp` without
naming the library:

```powershell
clang++ -std=c++23 -Wall -Wextra main.cpp -o out-mingw-clang\broken.exe -fuse-ld=lld -lstdc++exp
```

```
ld.lld: error: undefined symbol: __declspec(dllimport) station::summarize(std::vector<double, std::allocator<double>> const&)
>>> referenced by C:/Users/<you>/AppData/Local/Temp/main-cda861.o:(main)
ld.lld: error: undefined symbol: __declspec(dllimport) station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char>>, station::Summary const&)
>>> referenced by C:/Users/<you>/AppData/Local/Temp/main-cda861.o:(main)
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

(Paths shortened.) Read it closely. The linker asks for `summarize` and
`format_report`, the two functions `main.cpp` calls. They are marked
**`__declspec(dllimport)`**: the program expects to reach the function
**through a DLL**, and without the import library the linker has no idea
where that is. (The GNU linker says the same with an `__imp_` prefix on
the mangled name, "import".)

**c. Name the library, but not the folder.**

```powershell
clang++ -std=c++23 -Wall -Wextra main.cpp -lstation -o out-mingw-clang\broken.exe -fuse-ld=lld -lstdc++exp
```

```
lld: error: unable to find library -lstation
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

A different kind of message: not a missing **function**, a missing
**file**. The linker searched its standard folders for
`libstation.dll.a`, and our output folder is not one of them.

#### 6. Replace the library without relinking the program

The great strength of a dynamic library: you can fix or change the
library and **ship one file**. `report_v2.cpp` has a second version of
`format_report` with the same name, the same parameters and the same
result type, and a different text. Build a library from `stats.cpp` and
`report_v2.cpp` into a separate folder, copy the new DLL over the old
one, and run the **same `weather.exe`**:

```powershell
New-Item -ItemType Directory out-mingw-clang\v2
clang++ -std=c++23 -Wall -Wextra -DSTATION_BUILD_DLL -shared stats.cpp report_v2.cpp -o out-mingw-clang\v2\station.dll '-Wl,--out-implib,out-mingw-clang\v2\libstation.dll.a'
Copy-Item out-mingw-clang\v2\station.dll out-mingw-clang\station.dll -Force
.\out-mingw-clang\weather.exe
```

```
[v2] sensor-12: min 12.8 C, max 32.5 C, mean 21.6 C
```

`weather.exe` was not compiled or linked again, and its new output
proves it loaded the new library. With the static library of 7.13 you
would have had to **relink every program** that used it. The condition
is that the **interface stays the same**: same names, same parameter
types. The program only checks the names, and nothing checks that the
code behind them still behaves.

That is MinGW Clang done.

---

### Environment 4: Linux, GCC (Docker)

You get a real Linux with GCC from the Docker container of chapter 2.
Our image carries GCC 16.2 and GNU binutils 2.44.

#### Open the shell

From the repository root, in PowerShell:

```powershell
docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-gcc
```

You land in `/workspace`, which is the repository. Now, inside the
container:

```sh
cd 07.PracticalBuiltInFeatures/7.14ProjectDynamicLibrary
g++ --version
```

```
g++ (GCC) 16.2.0
```

(`--version` prints a few more lines. We show only the first.)

(`--rm` throws the container away when you leave. The files you create
stay in your folder on Windows, in `out-linux-gcc`, because of the `-v`
mount. They are ignored by git.)

#### The tools in this environment

- **`g++`**: the GCC compiler driver. With `-shared` it compiles the
  sources and then runs the linker to make a **shared library**, a `.so`
  file.
- **`ld`**: the GNU linker. You will not usually type it: `g++` calls
  it, and the linker errors you get come from `/usr/bin/ld`.
- **`nm -D`**: lists the **symbol table** of a binary. With `-D` it
  lists the **dynamic** symbols: the names a shared library offers to
  the outside.
- **`readelf -d`**: prints the **dynamic section** of an ELF file, which
  includes the list of libraries the program needs (the `NEEDED` lines)
  and any folder baked into it.
- **`ldd`**: asks "which shared libraries will this program load, and
  **where is each one found**?" It is the quickest way to see whether
  the loader will succeed.
- **`file`**: guesses what a file is from its first bytes.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```sh
mkdir -p out-linux-gcc
```

(`-p` means "no error if it already exists".)

#### 1. Build the library

```
   stats.cpp  ─┐
               ├──► g++ -shared ──► libstation.so   the code (and nothing else: no import library)
   report.cpp ─┘
```

```sh
g++ -std=c++23 -Wall -Wextra -fPIC -fvisibility=hidden -shared stats.cpp report.cpp -o out-linux-gcc/libstation.so
ls -l out-linux-gcc/libstation.so
file out-linux-gcc/libstation.so
```

```
-rwxr-xr-x 1 root root 352640 Oct 14 16:12 out-linux-gcc/libstation.so
out-linux-gcc/libstation.so: ELF 64-bit LSB shared object, x86-64, version 1 (GNU/Linux), dynamically linked, not stripped
```

- **`-shared`** makes a `.so` instead of an executable.
- **`-fPIC`** means "position-independent code". The library can be
  loaded at **any address**, and several programs may load it at
  different ones, so its code cannot assume where it lives.
- **`-fvisibility=hidden`** hides everything we did not mark with
  `STATION_API`, so only the three public functions are exported.
- There is **no import library** on Linux. The `.so` itself serves both
  as the thing the linker reads and the thing the program loads.

(The date in the `ls -l` line will be yours, not ours.)

#### 2. Look inside the library

```sh
nm -D --defined-only out-linux-gcc/libstation.so | grep station
nm -D --defined-only out-linux-gcc/libstation.so | wc -l
```

```
000000000001b809 T _ZN7station10to_celsiusEd
000000000001c1b1 T _ZN7station13format_reportB5cxx11ESt17basic_string_viewIcSt11char_traitsIcEERKNS_7SummaryE
000000000001b841 T _ZN7station9summarizeERKSt6vectorIdSaIdEE
708
```

The addresses will differ on your machine. **Three `station` entries**:
the three functions we marked. The names are the Itanium-mangled names
you read in 7.12. The second command counts **all** the exported names
in the library: there are hundreds, because the standard library's
templates stay visible whatever we do. That is why we filter for
`station`.

Look closely at the middle name, `format_reportB5cxx11`. That `B5cxx11`
is a **tag meaning "returns the C++11 flavour of `std::string`"**.
libstdc++, the C++ library that GCC and Clang use here, changed the
layout of `std::string` in 2015, and the tag lets old and new code tell
each other apart instead of crashing. This is the ABI showing up in a
name.

#### 3. Link the program, and ask what it needs

```sh
g++ -std=c++23 -Wall -Wextra main.cpp -Lout-linux-gcc -lstation -o out-linux-gcc/weather
```

`-Lout-linux-gcc` says "also search this folder", and `-lstation` means
"find a library called `station`": the linker looks for `libstation.so`.
Now ask the finished program what it needs when it **starts**:

```sh
readelf -d out-linux-gcc/weather | grep NEEDED
ldd out-linux-gcc/weather | grep -E 'station|not found'
```

```
 0x0000000000000001 (NEEDED)             Shared library: [libstation.so]
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libgcc_s.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
	libstation.so => not found
```

`libstation.so` is now on the program's **list of requirements** (the
`NEEDED` lines). It is not inside the program. This is the big
difference from 7.13. And look at the last line: **`ldd` says
`not found`**. The loader already knows it will not find our library.
Let us see what that means.

#### 4. Run it

```sh
./out-linux-gcc/weather
echo $?
```

```
./out-linux-gcc/weather: error while loading shared libraries: libstation.so: cannot open shared object file: No such file or directory
127
```

The program does not start. The linker found `libstation.so` fine,
because we passed `-L`. But **`-L` is a link-time option**. At run time
the **loader** searches its own list of folders, and our output folder
is not on it. There are two common fixes. The first is to tell the
loader, for this one run:

```sh
LD_LIBRARY_PATH=out-linux-gcc ./out-linux-gcc/weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`LD_LIBRARY_PATH` is a list of extra folders for the loader. The second
fix is to bake the folder **into the program**. Link again, with
`-Wl,-rpath,'$ORIGIN'`, and call the result `weather_rpath`:

```sh
g++ -std=c++23 -Wall -Wextra main.cpp -Lout-linux-gcc -lstation -Wl,-rpath,'$ORIGIN' -o out-linux-gcc/weather_rpath
readelf -d out-linux-gcc/weather_rpath | grep -E 'RPATH|RUNPATH'
./out-linux-gcc/weather_rpath
```

```
 0x000000000000001d (RUNPATH)            Library runpath: [$ORIGIN]
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`-Wl,` hands an option to the linker (as with `-Wl,--out-implib` on
Windows). **`rpath`** stores a folder **inside the executable**, and
**`$ORIGIN`** stands for "the folder this program is in". So the program
looks for its library right next to itself, wherever you run it from.
Quote the `$ORIGIN` so your shell does not eat it. Try it from another
folder:

```sh
cd /
/workspace/07.PracticalBuiltInFeatures/7.14ProjectDynamicLibrary/out-linux-gcc/weather_rpath
cd /workspace/07.PracticalBuiltInFeatures/7.14ProjectDynamicLibrary
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(The linker wrote the entry as `RUNPATH`, the modern spelling of the
older `RPATH`.)

#### 5. Break it on purpose

**a. Take the library away.** Move `libstation.so` out of the way and
run the program that has the rpath:

```sh
mv out-linux-gcc/libstation.so out-linux-gcc/libstation.so.away
./out-linux-gcc/weather_rpath
echo $?
ldd out-linux-gcc/weather_rpath | grep station
```

```
./out-linux-gcc/weather_rpath: error while loading shared libraries: libstation.so: cannot open shared object file: No such file or directory
127
	libstation.so => not found
```

The program linked fine. It cannot **start**, because the library is
gone. This is the first kind of failure that a static library never had:
a build that succeeded and a program that does not run. Put it back
before you go on:

```sh
mv out-linux-gcc/libstation.so.away out-linux-gcc/libstation.so
```

**b. Leave the library out of the link.** Compile `main.cpp` without
naming the library:

```sh
g++ -std=c++23 -Wall -Wextra main.cpp -o out-linux-gcc/broken
```

```
/usr/bin/ld: /tmp/ccdouMl2.o: in function `main':
main.cpp:(.text+0x46): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
/usr/bin/ld: main.cpp:(.text+0x72): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
collect2: error: ld returned 1 exit status
```

(The `/tmp/...` object file name is a temporary file and will differ.)
Read it closely. The linker asks for `summarize` and `format_report`,
the two functions `main.cpp` calls. It does **not** ask for
`to_celsius`: only the library calls that one.

**c. Name the library, but not the folder.**

```sh
g++ -std=c++23 -Wall -Wextra main.cpp -lstation -o out-linux-gcc/broken
```

```
/usr/bin/ld: cannot find -lstation: No such file or directory
collect2: error: ld returned 1 exit status
```

A different kind of message: not a missing **function**, a missing
**file**. The linker searched its standard folders for `libstation.so`,
and our output folder is not one of them.

#### 6. Replace the library without relinking the program

The great strength of a dynamic library: you can fix or change the
library and **ship one file**. `report_v2.cpp` has a second version of
`format_report` with the same name, the same parameters and the same
result type, and a different text. Build a library from `stats.cpp` and
`report_v2.cpp` into a separate folder, copy the new `.so` over the old
one, and run the **same `weather_rpath`**:

```sh
mkdir -p out-linux-gcc/v2
g++ -std=c++23 -Wall -Wextra -fPIC -fvisibility=hidden -shared stats.cpp report_v2.cpp -o out-linux-gcc/v2/libstation.so
cp out-linux-gcc/v2/libstation.so out-linux-gcc/libstation.so
./out-linux-gcc/weather_rpath
```

```
[v2] sensor-12: min 12.8 C, max 32.5 C, mean 21.6 C
```

The program was not compiled or linked again, and its new output proves
it loaded the new library. With the static library of 7.13 you would
have had to **relink every program** that used it. The condition is that
the **interface stays the same**: same names, same parameter types. The
program only checks the names, and nothing checks that the code behind
them still behaves.

That is Linux GCC done.

---

### Environment 5: Linux, Clang (Docker)

You get a real Linux with Clang from the Docker container of chapter 2.
Our image carries Clang 21.1.8 and GNU binutils 2.44.

#### Open the shell

From the repository root, in PowerShell:

```powershell
docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-clang
```

You land in `/workspace`, which is the repository. Now, inside the
container:

```sh
cd 07.PracticalBuiltInFeatures/7.14ProjectDynamicLibrary
clang++ --version
```

```
Debian clang version 21.1.8 (++20251221033036+2078da43e25a-1~exp1~20251221153213.50)
```

(`--version` prints a few more lines. We show only the first.)

(`--rm` throws the container away when you leave. The files you create
stay in your folder on Windows, in `out-linux-clang`, because of the
`-v` mount. They are ignored by git.)

#### The tools in this environment

- **`clang++`**: the Clang compiler driver. With `-shared` it compiles
  the sources and then runs the linker to make a **shared library**, a
  `.so` file.
- **`ld`**: the GNU linker. You will not usually type it: `clang++`
  calls it, and the linker errors you get come from `/usr/bin/ld`.
- **`nm -D`**: lists the **symbol table** of a binary. With `-D` it
  lists the **dynamic** symbols: the names a shared library offers to
  the outside.
- **`readelf -d`**: prints the **dynamic section** of an ELF file, which
  includes the list of libraries the program needs (the `NEEDED` lines)
  and any folder baked into it.
- **`ldd`**: asks "which shared libraries will this program load, and
  **where is each one found**?" It is the quickest way to see whether
  the loader will succeed.
- **`file`**: guesses what a file is from its first bytes.

#### A folder for the output

Make the folder first. Every file the tools produce in this walk-through
goes into it, and nothing lands next to your sources:

```sh
mkdir -p out-linux-clang
```

(`-p` means "no error if it already exists".)

#### 1. Build the library

```
   stats.cpp  ─┐
               ├──► clang++ -shared ──► libstation.so   the code (and nothing else: no import library)
   report.cpp ─┘
```

```sh
clang++ -std=c++23 -Wall -Wextra -fPIC -fvisibility=hidden -shared stats.cpp report.cpp -o out-linux-clang/libstation.so
ls -l out-linux-clang/libstation.so
file out-linux-clang/libstation.so
```

```
-rwxr-xr-x 1 root root 306208 Oct 14 16:13 out-linux-clang/libstation.so
out-linux-clang/libstation.so: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, BuildID[sha1]=2d52bd14fa7171caeb4aa2022dd3b8dab2aa5a4e, not stripped
```

- **`-shared`** makes a `.so` instead of an executable.
- **`-fPIC`** means "position-independent code". The library can be
  loaded at **any address**, and several programs may load it at
  different ones, so its code cannot assume where it lives.
- **`-fvisibility=hidden`** hides everything we did not mark with
  `STATION_API`, so only the three public functions are exported.
- There is **no import library** on Linux. The `.so` itself serves both
  as the thing the linker reads and the thing the program loads.

(The date in the `ls -l` line will be yours, not ours.)

#### 2. Look inside the library

```sh
nm -D --defined-only out-linux-clang/libstation.so | grep station
nm -D --defined-only out-linux-clang/libstation.so | wc -l
```

```
00000000000185b0 T _ZN7station10to_celsiusEd
0000000000018e60 T _ZN7station13format_reportB5cxx11ESt17basic_string_viewIcSt11char_traitsIcEERKNS_7SummaryE
00000000000185f0 T _ZN7station9summarizeERKSt6vectorIdSaIdEE
585
```

The addresses will differ on your machine. **Three `station` entries**:
the three functions we marked. The names are the Itanium-mangled names
you read in 7.12. The second command counts **all** the exported names
in the library: there are hundreds, because the standard library's
templates stay visible whatever we do. That is why we filter for
`station`.

Look closely at the middle name, `format_reportB5cxx11`. That `B5cxx11`
is a **tag meaning "returns the C++11 flavour of `std::string`"**.
libstdc++, the C++ library that GCC and Clang use here, changed the
layout of `std::string` in 2015, and the tag lets old and new code tell
each other apart instead of crashing. This is the ABI showing up in a
name.

#### 3. Link the program, and ask what it needs

```sh
clang++ -std=c++23 -Wall -Wextra main.cpp -Lout-linux-clang -lstation -o out-linux-clang/weather
```

`-Lout-linux-clang` says "also search this folder", and `-lstation`
means "find a library called `station`": the linker looks for
`libstation.so`. Now ask the finished program what it needs when it
**starts**:

```sh
readelf -d out-linux-clang/weather | grep NEEDED
ldd out-linux-clang/weather | grep -E 'station|not found'
```

```
 0x0000000000000001 (NEEDED)             Shared library: [libstation.so]
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libgcc_s.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
	libstation.so => not found
```

`libstation.so` is now on the program's **list of requirements** (the
`NEEDED` lines). It is not inside the program. This is the big
difference from 7.13. And look at the last line: **`ldd` says
`not found`**. The loader already knows it will not find our library.
Let us see what that means.

#### 4. Run it

```sh
./out-linux-clang/weather
echo $?
```

```
./out-linux-clang/weather: error while loading shared libraries: libstation.so: cannot open shared object file: No such file or directory
127
```

The program does not start. The linker found `libstation.so` fine,
because we passed `-L`. But **`-L` is a link-time option**. At run time
the **loader** searches its own list of folders, and our output folder
is not on it. There are two common fixes. The first is to tell the
loader, for this one run:

```sh
LD_LIBRARY_PATH=out-linux-clang ./out-linux-clang/weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`LD_LIBRARY_PATH` is a list of extra folders for the loader. The second
fix is to bake the folder **into the program**. Link again, with
`-Wl,-rpath,'$ORIGIN'`, and call the result `weather_rpath`:

```sh
clang++ -std=c++23 -Wall -Wextra main.cpp -Lout-linux-clang -lstation -Wl,-rpath,'$ORIGIN' -o out-linux-clang/weather_rpath
readelf -d out-linux-clang/weather_rpath | grep -E 'RPATH|RUNPATH'
./out-linux-clang/weather_rpath
```

```
 0x000000000000001d (RUNPATH)            Library runpath: [$ORIGIN]
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`-Wl,` hands an option to the linker (as with `-Wl,--out-implib` on
Windows). **`rpath`** stores a folder **inside the executable**, and
**`$ORIGIN`** stands for "the folder this program is in". So the program
looks for its library right next to itself, wherever you run it from.
Quote the `$ORIGIN` so your shell does not eat it. Try it from another
folder:

```sh
cd /
/workspace/07.PracticalBuiltInFeatures/7.14ProjectDynamicLibrary/out-linux-clang/weather_rpath
cd /workspace/07.PracticalBuiltInFeatures/7.14ProjectDynamicLibrary
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(The linker wrote the entry as `RUNPATH`, the modern spelling of the
older `RPATH`.)

#### 5. Break it on purpose

**a. Take the library away.** Move `libstation.so` out of the way and
run the program that has the rpath:

```sh
mv out-linux-clang/libstation.so out-linux-clang/libstation.so.away
./out-linux-clang/weather_rpath
echo $?
ldd out-linux-clang/weather_rpath | grep station
```

```
./out-linux-clang/weather_rpath: error while loading shared libraries: libstation.so: cannot open shared object file: No such file or directory
127
	libstation.so => not found
```

The program linked fine. It cannot **start**, because the library is
gone. This is the first kind of failure that a static library never had:
a build that succeeded and a program that does not run. Put it back
before you go on:

```sh
mv out-linux-clang/libstation.so.away out-linux-clang/libstation.so
```

**b. Leave the library out of the link.** Compile `main.cpp` without
naming the library:

```sh
clang++ -std=c++23 -Wall -Wextra main.cpp -o out-linux-clang/broken
```

```
/usr/bin/ld: /tmp/main-3955fd.o: in function `main':
main.cpp:(.text+0x91): undefined reference to `station::summarize(std::vector<double, std::allocator<double> > const&)'
main.cpp:(.text+0xe0): undefined reference to `station::format_report[abi:cxx11](std::basic_string_view<char, std::char_traits<char> >, station::Summary const&)'
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

(The `/tmp/...` object file name is a temporary file and will differ.)
Read it closely. The linker asks for `summarize` and `format_report`,
the two functions `main.cpp` calls. It does **not** ask for
`to_celsius`: only the library calls that one.

**c. Name the library, but not the folder.**

```sh
clang++ -std=c++23 -Wall -Wextra main.cpp -lstation -o out-linux-clang/broken
```

```
/usr/bin/ld: cannot find -lstation: No such file or directory
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
```

A different kind of message: not a missing **function**, a missing
**file**. The linker searched its standard folders for `libstation.so`,
and our output folder is not one of them.

#### 6. Replace the library without relinking the program

The great strength of a dynamic library: you can fix or change the
library and **ship one file**. `report_v2.cpp` has a second version of
`format_report` with the same name, the same parameters and the same
result type, and a different text. Build a library from `stats.cpp` and
`report_v2.cpp` into a separate folder, copy the new `.so` over the old
one, and run the **same `weather_rpath`**:

```sh
mkdir -p out-linux-clang/v2
clang++ -std=c++23 -Wall -Wextra -fPIC -fvisibility=hidden -shared stats.cpp report_v2.cpp -o out-linux-clang/v2/libstation.so
cp out-linux-clang/v2/libstation.so out-linux-clang/libstation.so
./out-linux-clang/weather_rpath
```

```
[v2] sensor-12: min 12.8 C, max 32.5 C, mean 21.6 C
```

The program was not compiled or linked again, and its new output proves
it loaded the new library. With the static library of 7.13 you would
have had to **relink every program** that used it. The condition is that
the **interface stays the same**: same names, same parameter types. The
program only checks the names, and nothing checks that the code behind
them still behaves.

That is Linux Clang done.

---

### Static or dynamic?

Same weather station, two ways to package the library. Side by side:

**What the program contains**

- Static (7.13): a **copy** of the library code.
- Dynamic (7.14): only a **reference** to the library.

**Needed to run the program**

- Static: no, the code is already inside.
- Dynamic: **yes**, the DLL or `.so` must be found when the program
  starts.

**Several programs using it**

- Static: each carries its own copy.
- Dynamic: they **share** one file.

**Fixing a bug in the library**

- Static: relink every program that uses it.
- Dynamic: replace one file, **if the interface is unchanged**.

**Settings that must match** (C runtime, language standard, debug or
release)

- Static: at link time.
- Dynamic: at link time **and at run time**.

**Export markers in the code**

- Static: not needed.
- Dynamic: needed on Windows (`STATION_API`).

**What can go wrong**

- Static: a link error.
- Dynamic: a link error, **or a program that builds but does not start**
  because the loader cannot find the library.

### The ABI warning

The "settings that must match" point needs a word. Look at what our
library passes across the boundary: a `std::vector<double>` goes in, a
`std::string` comes out. Both are **layouts defined by the standard
library**, and different compilers, different versions, and even Debug
and Release builds of the same compiler can lay them out differently.
Our program works because **the same tool chain and the same options
built both sides**.

This is why you will see two styles in the real world:

- Libraries shipped as **source or static libraries**, built by *you*
  with *your* compiler, so everything matches.
- Libraries that ship as DLLs or `.so` files for everyone keep their
  public functions to **simple types** (integers, pointers, plain
  structs) and mark them **`extern "C"`**, so that the names are not
  mangled either.

That second style is exactly what makes a library callable from other
languages.

### Gotchas to take away

A summary of what you met. Each point was shown in the environment where
it applies.

- A DLL **exports nothing** unless you mark it. `STATION_API` is
  `dllexport` while you build the library and `dllimport` while you
  build the program that uses it. On Linux `-fvisibility=hidden` gives
  you the same rule.
- On Windows you link against an **import library** (a signpost of
  names), not against the DLL. On Linux the `.so` itself is used at link
  time and at run time.
- A dynamic library is needed **every time the program runs**. If the
  loader cannot find it the program does not start: exit code
  `-1073741515` on Windows, exit code `127` and
  `error while loading shared libraries` on Linux.
- Windows looks in the **folder of the program first**, then the PATH.
  Linux looks in its standard folders, then `LD_LIBRARY_PATH`, and in
  the **rpath** that was baked into the program
  (`-Wl,-rpath,'$ORIGIN'`).
- `-L` is a **link-time** option. It does not tell the loader anything.
- `ldd` (Linux), `readelf -d`, `objdump -p` and `dumpbin /dependents`
  tell you what a program needs **before** you run it.
- You can replace a library without relinking the program, as long as
  the **interface does not change**.
- Mixing settings between the library and the program is how crashes
  appear, not only link errors: build both sides with the **same tool
  chain and the same options**.

---

## 7.15 Project: driving CMake from the command line

You have now typed, by hand, every kind of command a build needs:
compile, link, archive, build a DLL. Real projects have hundreds of
them, in the right order, with the right flags for the right compiler.
**CMake** writes and runs those commands for you.

Until now you have probably used CMake through an IDE. In this project
we call it **directly, from the command line**, in all five
environments, and we keep checking its work against what we typed in
7.12 to 7.14. The code is in `7.15ProjectCMakeCommandLine`. It is the
same weather station, with a `CMakeLists.txt` that builds a library
called `station` and a program called `rooster` that uses it.

### Three layers

```
   CMakeLists.txt  ──►  cmake (configure)  ──►  build files  ──►  Ninja  ──►  cl / g++ / clang++
   what you want        picks a compiler,       build.ninja       runs the     the commands
   (targets, files)     checks it works,        (a list of        commands     you typed by hand
                        writes the plan         commands)         in order
```

- **`cmake`** reads your `CMakeLists.txt`, finds out which compiler you
  have, and writes a plan. It never compiles anything itself.
- A **generator** turns the plan into build files for some build tool.
  We always use **Ninja**, a small, fast build tool, with `-G Ninja`.
- **Ninja** reads the plan and runs the compiler, the archiver and the
  linker, in the right order.

### What is new

**Configure and build are two separate commands.**
`cmake -S . -B <folder>` is the **configure** step: it reads
`CMakeLists.txt` and writes the plan into a folder.
`cmake --build <folder>` is the **build** step: it runs the plan. You
configure once, and then build as many times as you like.

**Out-of-source build.** Everything CMake generates goes into the build
folder you name, never next to your sources. That is why you can delete
the whole folder to start again.

**Cache variables.** An option written `-D<NAME>=<value>` sets a **cache
variable**: a named setting stored in a file called `CMakeCache.txt` in
the build folder. Think of the cache as that folder's memory of what you
asked for.

**Targets.** A **target** is a thing `CMakeLists.txt` defines. Ours has
two: `station` (the library) and `rooster` (the program).

**One build type per folder.** With Ninja, a build folder is configured
for **one** build type, such as `Debug` or `Release`. If you want both,
you make two build folders.

**The export header.** In 7.14 you wrote the `STATION_API` macro by hand
to export the functions of a DLL. CMake can write an equivalent header
for you. You will see it in a minute.

### The file: `CMakeLists.txt`

Here it is, without the comments. Read it once, and you will meet every
line again in the commands below.

```cmake
cmake_minimum_required(VERSION 3.20)
project(rooster)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(station stats.cpp stats.h report.cpp report.h)

include(GenerateExportHeader)
generate_export_header(station)
target_include_directories(station PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(station PROPERTIES CXX_VISIBILITY_PRESET hidden)

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(station PUBLIC STATION_STATIC_DEFINE)
endif()

add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE station)

if(WIN32 AND NOT MSVC)
    target_link_libraries(rooster PRIVATE stdc++exp)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_link_options(rooster PRIVATE -fuse-ld=lld)
    endif()
endif()

install(TARGETS rooster station
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(FILES stats.h report.h ${CMAKE_CURRENT_BINARY_DIR}/station_export.h
    DESTINATION include)
```

- `add_library(station ...)` has **no `STATIC` or `SHARED`** keyword.
  The command line decides, with one variable (step 5).
- `generate_export_header(station)` **writes a header for us**,
  `station_export.h`, into the build folder. It defines `STATION_EXPORT`
  as `dllexport` while the library is compiled, `dllimport` for the
  program that uses it, and visibility on Linux: the macro you wrote
  yourself in 7.14. The `stats.h` and `report.h` of this folder include
  it.
- `CXX_VISIBILITY_PRESET hidden` is the `-fvisibility=hidden` of 7.14.
- A **static** library has nothing to import or export, so the `if`
  tells the header to define `STATION_EXPORT` as nothing. Without that
  line, a static build on Windows would label the functions `dllimport`
  and fail to link.
- `target_link_libraries(rooster PRIVATE station)` says "the program
  uses the library", and gives you the link step for free.
- On MinGW, `stdc++exp` is the `-lstdc++exp` of 7.12, written once for
  everybody. For Clang, `target_link_options(... -fuse-ld=lld)` adds the
  other MinGW extra of 7.12 to the link command of the program. The
  inner `if` asks CMake which compiler it found.
- `install(...)` says what `cmake --install` copies, and where (step 6).

### Pick your environment

The project has **five environments**. Every one of them is a complete
walk-through that you can do without reading any other. Do the one you
have, and come back for the others if you are curious. In each one you
will do the same seven things:

1. **Configure**, and look at what CMake wrote.
2. **Build** and watch the real commands it runs.
3. **Build again**, and see that only what changed is rebuilt.
4. Build **one target**, and a **Release** build.
5. Ask for a **dynamic library** instead of a static one, with one
   option.
6. **Install** the results into a folder.
7. **Break it** on purpose.

| Environment | Compiler CMake uses | Output folder |
|---|---|---|
| Windows, MSVC | `cl` | `out-msvc` |
| Windows, MinGW GCC | `g++` | `out-mingw-gcc` |
| Windows, MinGW Clang | `clang++` | `out-mingw-clang` |
| Linux, GCC (Docker) | `g++` | `out-linux-gcc` |
| Linux, Clang (Docker) | `clang++` | `out-linux-clang` |

Every environment writes **everything it produces** into **its own
output folder**, the one in the last column, inside
`7.15ProjectCMakeCommandLine`. The build folders live inside it:
`out-msvc/static`, `out-msvc/shared`, and so on. Your source folder
stays clean, and when you are done you delete **one folder** to start
over or to try another environment. Git ignores every `out-*` folder.

Every folder in this project also has one script per environment
(`build-msvc.ps1`, `build-mingw-gcc.ps1`, `build-mingw-clang.ps1`,
`build-linux-gcc.sh`, `build-linux-clang.sh`) that runs the commands of
that environment from top to bottom. Type the commands yourself first,
and use the scripts to check your work. (A script and your own commands
fill the same output folder, so delete the folder between the two if you
want to be sure the script did the work.)

---

### Environment 1: Windows, MSVC

MSVC is Microsoft's C++ compiler, the one Visual Studio uses and the
reference compiler of this course. Our version is `cl` 19.51 (Visual
Studio 2026).

#### Open the shell

Open **Developer PowerShell for VS** from the Start menu. That is an
ordinary PowerShell that already knows where the Microsoft tools are,
`cl` included. (From any other PowerShell you can load it by hand:
`& "<your VS folder>\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64`.)
Then, from the repository root:

```powershell
cd 07.PracticalBuiltInFeatures\7.15ProjectCMakeCommandLine
cmake --version
ninja --version
```

```
cmake version 3.30.2
...
1.12.1
```

(`cmake --version` prints a few more lines. Both tools must print a
version before you go on.)

#### The tools in this environment

- **`cmake`**: the program this whole project is about. It configures,
  builds (by calling Ninja), and installs.
- **`ninja`**: the build tool. CMake calls it for you. It decides
  **what** has to be rebuilt and runs the commands.
- **`cl`, `lib`, `link`**: the compiler driver, the librarian and the
  linker of 7.12 and 7.13. In this project you never type them: CMake
  does. You will see them in the verbose output.

#### Where the output goes

You do not have to make a folder: CMake creates `out-msvc/static` (and
`out-msvc` above it) by itself when it configures.

#### 1. Configure

```powershell
cmake -S . -B out-msvc/static -G Ninja
```

```
-- The C compiler identification is MSVC 19.51.36260.0
-- The CXX compiler identification is MSVC 19.51.36260.0
...
-- Configuring done (2.6s)
-- Generating done (0.0s)
-- Build files have been written to: D:/.../7.15ProjectCMakeCommandLine/out-msvc/static
```

(The many `Detecting ...` and `Check for working ...` lines are left
out.)

- **`-S .`**: the **S**ource folder, where `CMakeLists.txt` is.
- **`-B out-msvc/static`**: the **B**uild folder, where everything
  generated goes. CMake creates it.
- **`-G Ninja`**: the generator.

CMake checked a **C** compiler too, because `project(rooster)` does not
list languages, and so turns on C as well as C++. That is all CMake
needs on MSVC: the Developer PowerShell has already put `cl` on the
PATH, and CMake takes the first compiler it finds.

Now look at what configuring wrote:

```powershell
Get-ChildItem out-msvc\static -Name
Select-String -Path out-msvc\static\CMakeCache.txt -Pattern '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:)' | ForEach-Object { $_.Line }
```

```
CMakeFiles
build.ninja
CMakeCache.txt
cmake_install.cmake
station_export.h
CMAKE_BUILD_TYPE:STRING=Debug
CMAKE_CXX_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe
CMAKE_MAKE_PROGRAM:FILEPATH=C:/mingw64/bin/ninja.exe
CMAKE_GENERATOR:INTERNAL=Ninja
```

(Yours will show your own paths.)

- **`build.ninja`**: the plan: the list of commands Ninja will run.
- **`CMakeCache.txt`**: the cache, the folder's memory. It remembers the
  compiler (`cl.exe`), the generator, and the **build type**. On MSVC
  CMake chose `Debug` for us. In step 4 you will see what that means.
- **`station_export.h`**: the export header that
  `generate_export_header` wrote.
- **`cmake_install.cmake`** and **`CMakeFiles`**: CMake's own working
  files. You never edit them.

#### 2. Build, and watch the real commands

```powershell
cmake --build out-msvc/static --verbose
.\out-msvc\static\rooster.exe
```

`cmake --build <folder>` runs Ninja for you. **`--verbose`** makes it
print the **real commands**:

```
[1/5] cl.exe /nologo /TP -DSTATION_STATIC_DEFINE -I... /DWIN32 /D_WINDOWS /EHsc /Zi /Ob0 /Od /RTC1 -std:c++latest -MDd /showIncludes /FoCMakeFiles\station.dir\stats.cpp.obj /FdCMakeFiles\station.dir\station.pdb /FS -c ...\stats.cpp
[2/5] cl.exe ... -c ...\report.cpp
[3/5] cl.exe ... -c ...\main.cpp
[4/5] lib.exe /nologo /machine:x64 /out:station.lib CMakeFiles\station.dir\stats.cpp.obj CMakeFiles\station.dir\report.cpp.obj
[5/5] ... link.exe /nologo CMakeFiles\rooster.dir\main.cpp.obj /out:rooster.exe ... /debug /INCREMENTAL /subsystem:console station.lib kernel32.lib user32.lib ...
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(Paths are shortened, the first few lines of `--verbose` and the start
of the long link line are left out.) Read them. This is the payoff of
the previous three lectures. Compare with what you typed:

- **Steps 1 to 3** are the compile commands of 7.12: one
  `cl ... -c file.cpp` per source file. You recognise `/EHsc` and
  `-std:c++latest`. CMake added `/nologo`, `/TP` ("treat this file as
  C++") and `/showIncludes` (Ninja uses it to track which headers a file
  includes).
- **`-MDd`** is the `/MD` you typed by hand, in its **Debug** flavour:
  the debug version of the shared C runtime. The other flags,
  `/Zi /Ob0 /Od /RTC1`, ask for debug information, no inlining, no
  optimisation and run-time checks. That is what the `Debug` build type
  means.
- **`-DSTATION_STATIC_DEFINE`** comes from the
  `if(NOT BUILD_SHARED_LIBS)` in `CMakeLists.txt`.
- **Step 4** is the `lib` command of 7.13, making `station.lib`.
- **Step 5** is the link of 7.12 and 7.13: `rooster.exe` from
  `main.cpp.obj` and `station.lib`, plus the Windows libraries
  (`kernel32.lib` and friends) that every Windows program links. CMake
  runs it through a small helper, `cmake -E vs_link_exe`, which also
  deals with manifests. The real linker, `link.exe`, is in the line.

**CMake is not magic. It is a command generator.** Whenever a CMake
build misbehaves, `--verbose` shows you the exact command that went
wrong, and you can run it yourself.

#### 3. Build again: only what changed

Run the same build without changing anything:

```powershell
cmake --build out-msvc/static
```

```
ninja: no work to do.
```

Now change one source file. Setting its "last modified" time to now is
what saving the file in your editor does:

```powershell
(Get-Item stats.cpp).LastWriteTime = Get-Date
cmake --build out-msvc/static
```

```
[1/3] Building CXX object CMakeFiles\station.dir\stats.cpp.obj
[2/3] Linking CXX static library station.lib
[3/3] Linking CXX executable rooster.exe
```

Only `stats.cpp` was recompiled. `report.cpp` and `main.cpp` were left
alone, and then the library and the program were rebuilt, because they
depend on `stats.cpp.obj`. This is why you use a build tool: with three
files it hardly matters, with three thousand it is the difference
between seconds and an hour.

#### 4. One target, and a Release build

Make a **second** build folder, this time for the `Release` build type,
and build only the **library** target:

```powershell
cmake -S . -B out-msvc/release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build out-msvc/release --target station --verbose
Get-ChildItem out-msvc\release -Name
```

```
[1/3] cl.exe /nologo /TP -DSTATION_STATIC_DEFINE -I... /DWIN32 /D_WINDOWS /EHsc /O2 /Ob2 /DNDEBUG -std:c++latest -MD /showIncludes /FoCMakeFiles\station.dir\stats.cpp.obj /FdCMakeFiles\station.dir\station.pdb /FS -c ...\stats.cpp
[2/3] cl.exe ... -c ...\report.cpp
[3/3] ... lib.exe /nologo /machine:x64 /out:station.lib CMakeFiles\station.dir\stats.cpp.obj CMakeFiles\station.dir\report.cpp.obj && cd .
CMakeFiles
.ninja_deps
.ninja_log
build.ninja
CMakeCache.txt
cmake_install.cmake
station.lib
station_export.h
```

- **`-DCMAKE_BUILD_TYPE=Release`** sets a cache variable. Look at the
  flags it changed: `/Zi /Ob0 /Od /RTC1` became **`/O2 /Ob2 /DNDEBUG`**
  (optimise, inline, and switch off `assert`), and `-MDd` became
  **`-MD`**, the very `/MD` you typed in 7.12 to 7.14.
- **`--target station`** builds the library and **nothing else**. There
  is a `station.lib` in the folder and no `rooster.exe`. A target is how
  you ask "does just this part compile?" Without `--target`, CMake
  builds everything.

Now build the rest and run it:

```powershell
cmake --build out-msvc/release
.\out-msvc\release\rooster.exe
```

```
[1/2] Building CXX object CMakeFiles\rooster.dir\main.cpp.obj
[2/2] Linking CXX executable rooster.exe
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

Ninja built only what was missing.

#### 5. A dynamic library, with one option

`CMakeLists.txt` says `add_library(station ...)` with **no `STATIC` or
`SHARED`**. The **command line** decides, with one variable:

```powershell
cmake -S . -B out-msvc/shared -G Ninja -DBUILD_SHARED_LIBS=ON
cmake --build out-msvc/shared --verbose
```

```
[1/5] cl.exe /nologo /TP -Dstation_EXPORTS -I... /DWIN32 /D_WINDOWS /EHsc /Zi /Ob0 /Od /RTC1 -std:c++latest -MDd /showIncludes /FoCMakeFiles\station.dir\stats.cpp.obj /FdCMakeFiles\station.dir\ /FS -c ...\stats.cpp
[2/5] cl.exe ... -c ...\report.cpp
[3/5] cl.exe ... -c ...\main.cpp
[4/5] ... link.exe /nologo CMakeFiles\station.dir\stats.cpp.obj CMakeFiles\station.dir\report.cpp.obj ...
[5/5] ... link.exe /nologo CMakeFiles\rooster.dir\main.cpp.obj /out:rooster.exe ... station.lib ...
```

(Shortened again.) Two things to notice. The library files are compiled
with **`-Dstation_EXPORTS`**: that is the macro that
`generate_export_header` looks for, and it is the `/DSTATION_BUILD_DLL`
you typed in 7.14. CMake defines it for you. And step 4 is now a
**link** that makes a DLL, not a `lib` that makes an archive. Look at
the result:

```powershell
Get-ChildItem out-msvc\shared\*.dll, out-msvc\shared\*.lib | Format-Table Name, Length -AutoSize
.\out-msvc\shared\rooster.exe
```

```
Name         Length
----         ------
station.dll 1213952
station.lib    3196

sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`station.dll` is the code and `station.lib` is the small **import
library**, the signpost of 7.14. The DLL is large because this is a
`Debug` build. The program runs because `station.dll` sits in the **same
folder** as `rooster.exe`, where the Windows loader looks first. One
option, and 7.13 turned into 7.14, with no source changes.

#### 6. Install

```powershell
cmake --install out-msvc/static --prefix out-msvc/install
Get-ChildItem out-msvc\install -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
.\out-msvc\install\bin\rooster.exe
```

```
-- Install configuration: "Debug"
-- Installing: .../out-msvc/install/bin/rooster.exe
-- Installing: .../out-msvc/install/lib/station.lib
-- Installing: .../out-msvc/install/include/stats.h
-- Installing: .../out-msvc/install/include/report.h
-- Installing: .../out-msvc/install/include/station_export.h
out-msvc\install\bin\rooster.exe
out-msvc\install\include\report.h
out-msvc\install\include\station_export.h
out-msvc\install\include\stats.h
out-msvc\install\lib\station.lib
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`--install` copies the **finished products** to a clean folder, as the
`install(...)` lines in `CMakeLists.txt` say. `--prefix` names the
folder. That is the **layout you hand to someone else**: the program in
`bin`, the library in `lib`, the headers in `include`. (The
`Install configuration: "Debug"` line is the build type again.)

Installing the **dynamic** build puts the DLL next to the program:

```powershell
cmake --install out-msvc/shared --prefix out-msvc/install-shared
Get-ChildItem out-msvc\install-shared -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
.\out-msvc\install-shared\bin\rooster.exe
```

```
out-msvc\install-shared\bin\rooster.exe
out-msvc\install-shared\bin\station.dll
out-msvc\install-shared\include\report.h
out-msvc\install-shared\include\station_export.h
out-msvc\install-shared\include\stats.h
out-msvc\install-shared\lib\station.lib
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(The `-- Installing:` lines are left out.) The `RUNTIME DESTINATION bin`
line in `CMakeLists.txt` covers programs **and DLLs**, so `station.dll`
lands in `bin`, next to `rooster.exe`, where Windows finds it. The
import library goes to `lib`.

#### 7. Break it on purpose

**a. A folder without `CMakeLists.txt`.** Point `-S` at the wrong
folder:

```powershell
cmake -S out-msvc -B out-msvc/oops -G Ninja
```

```
CMake Error: The source directory ".../out-msvc" does not appear to contain CMakeLists.txt.
Specify --help for usage, or press the help button on the CMake GUI.
```

`-S` must name the folder that **contains** `CMakeLists.txt`.

**b. A target that does not exist.** A typo in `--target`:

```powershell
cmake --build out-msvc/static --target stationn
```

```
ninja: error: unknown target 'stationn', did you mean 'station'?
```

That message comes from Ninja, which knows the list of targets from
`build.ninja`.

**c. Build a folder that was never configured.**

```powershell
cmake --build out-msvc/nothere
```

```
Error: .../out-msvc/nothere is not a directory
```

You have to **configure** (`-S ... -B ...`) before you can **build**.

**d. Another generator in a folder that already has one.** The cache
remembers the generator:

```powershell
cmake -S . -B out-msvc/static -G "NMake Makefiles"
```

```
CMake Error: Error: generator : NMake Makefiles
Does not match the generator used previously: Ninja
Either remove the CMakeCache.txt file and CMakeFiles directory or choose a different binary directory.
```

One build folder, one generator. CMake offers two ways out: delete the
folder or pick another. That is why every variant in this project,
`static`, `release`, `shared`, has **its own folder**.

That is MSVC done.

---

### Environment 2: Windows, MinGW GCC

**MinGW-w64** brings the GNU tool chain (GCC, binutils) to Windows. The
programs it makes are ordinary Windows programs. Ours is a UCRT build by
Brecht Sanders: `g++ --version` says
`g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r2) 14.2.0`.

#### Open the shell

Open a **normal PowerShell**, not the Visual Studio Developer one, whose
`cl` would be picked up first. Put `C:\mingw64\bin` first on the PATH
**for this window**, then go to the folder (from the repository root):

```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
cd 07.PracticalBuiltInFeatures\7.15ProjectCMakeCommandLine
cmake --version
ninja --version
g++ --version
```

```
cmake version 3.30.4
...
1.12.1
g++.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r2) 14.2.0
...
```

(Each `--version` prints a few more lines. Our MinGW package brings its
own `cmake` and `ninja`: `Get-Command cmake` tells you which `cmake`
runs for you. Both are fine.)

#### The tools in this environment

- **`cmake`**: the program this whole project is about. It configures,
  builds (by calling Ninja), and installs.
- **`ninja`**: the build tool. CMake calls it for you. It decides
  **what** has to be rebuilt and runs the commands.
- **`gcc` and `g++`**: the C and C++ compiler. CMake has to be **told**
  which compiler to use, with
  `-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++`. Without the options
  it would use whatever it finds first.
- **`ar.exe` and `ranlib.exe`**: the archiver of 7.13 and the tool that
  writes the archive's index. You never type them here: CMake does.

#### Where the output goes

You do not have to make a folder: CMake creates `out-mingw-gcc/static`
(and `out-mingw-gcc` above it) by itself when it configures.

#### 1. Configure

```powershell
cmake -S . -B out-mingw-gcc/static -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
```

```
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
...
-- Configuring done (1.2s)
-- Generating done (0.0s)
-- Build files have been written to: D:/.../7.15ProjectCMakeCommandLine/out-mingw-gcc/static
```

(The many `Detecting ...` and `Check for working ...` lines are left
out.)

- **`-S .`**: the **S**ource folder, where `CMakeLists.txt` is.
- **`-B out-mingw-gcc/static`**: the **B**uild folder, where everything
  generated goes. CMake creates it.
- **`-G Ninja`**: the generator.
- **`-D...`**: a **cache variable**. These two say which compilers to
  use. CMake checks a **C** compiler too, because `project(rooster)`
  does not list languages, and so turns on C as well as C++.

Now look at what configuring wrote:

```powershell
Get-ChildItem out-mingw-gcc\static -Name
Select-String -Path out-mingw-gcc\static\CMakeCache.txt -Pattern '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:|CMAKE_AR:)' | ForEach-Object { $_.Line }
```

```
CMakeFiles
build.ninja
CMakeCache.txt
cmake_install.cmake
station_export.h
CMAKE_AR:FILEPATH=C:/mingw64/bin/ar.exe
CMAKE_BUILD_TYPE:STRING=
CMAKE_CXX_COMPILER:STRING=C:/mingw64/bin/g++.exe
CMAKE_MAKE_PROGRAM:FILEPATH=C:/mingw64/bin/ninja.exe
CMAKE_GENERATOR:INTERNAL=Ninja
```

- **`build.ninja`**: the plan: the list of commands Ninja will run.
- **`CMakeCache.txt`**: the cache, the folder's memory. It remembers the
  compiler, the archiver, the generator, and the **build type**. The
  build type is **empty** here: no optimisation flags and no debug
  flags. Step 4 comes back to this.
- **`station_export.h`**: the export header that
  `generate_export_header` wrote.
- **`cmake_install.cmake`** and **`CMakeFiles`**: CMake's own working
  files. You never edit them.

> **The compiler belongs to the build folder.** CMake stores the
> compiler in the cache. That has a consequence you will see in step 7:
> change the compiler of an existing folder and CMake throws the cache
> away. Keep **one build folder per compiler**.

#### 2. Build, and watch the real commands

```powershell
cmake --build out-mingw-gcc/static --verbose
.\out-mingw-gcc\static\rooster.exe
```

`cmake --build <folder>` runs Ninja for you. **`--verbose`** makes it
print the **real commands**:

```
[1/5] g++.exe -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.obj -MF CMakeFiles\station.dir\stats.cpp.obj.d -o CMakeFiles/station.dir/stats.cpp.obj -c ...stats.cpp
[2/5] g++.exe -DSTATION_STATIC_DEFINE ... -c ...report.cpp
[3/5] g++.exe -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -MD ... -c ...main.cpp
[4/5] ... cmake.exe -E rm -f libstation.a && ... ar.exe qc libstation.a CMakeFiles/station.dir/stats.cpp.obj CMakeFiles/station.dir/report.cpp.obj && ... ranlib.exe libstation.a && cd .
[5/5] ... g++.exe CMakeFiles/rooster.dir/main.cpp.obj -o rooster.exe -Wl,--out-implib,librooster.dll.a ... libstation.a -lstdc++exp -lkernel32 -luser32 -lgdi32 ...
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(Paths are shortened, the first few lines of `--verbose` and the end of
the long link line are left out.) Read them. This is the payoff of the
previous three lectures. Compare with what you typed:

- **Steps 1 to 3** are the compile commands of 7.12: one
  `g++ ... -c file.cpp -o file.obj` per source file. CMake added
  `-MD -MT -MF`, which write a list of the headers each file includes,
  so Ninja knows what to rebuild. It also passes **`-std=gnu++23`**, not
  the `-std=c++23` you typed: `gnu++23` is C++23 plus GNU extensions,
  because CMake's `CXX_EXTENSIONS` defaults to on.
- **`-fvisibility=hidden`** is on the two **library** files only: it
  comes from `CXX_VISIBILITY_PRESET hidden`, the flag of 7.14.
  `main.cpp` does not have it. `-DSTATION_STATIC_DEFINE` is on all
  three, because the library marks it `PUBLIC`.
- **Step 4** is the archive of 7.13. CMake first removes any old
  `libstation.a`, then runs **`ar qc`** and **`ranlib`**. You typed
  `ar rcs`: the `s` writes the archive's index, and `ranlib` is the same
  "write the index" step as a separate command.
- **Step 5** is the link of 7.12 and 7.13: `rooster.exe` from
  `main.cpp.obj` and `libstation.a`, then **`-lstdc++exp`** (the
  `target_link_libraries(... stdc++exp)` line of `CMakeLists.txt`, in
  the right place: **after** the objects that need it), then the Windows
  libraries every Windows program links.

**CMake is not magic. It is a command generator.** Whenever a CMake
build misbehaves, `--verbose` shows you the exact command that went
wrong, and you can run it yourself.

#### 3. Build again: only what changed

Run the same build without changing anything:

```powershell
cmake --build out-mingw-gcc/static
```

```
ninja: no work to do.
```

Now change one source file. Setting its "last modified" time to now is
what saving the file in your editor does:

```powershell
(Get-Item stats.cpp).LastWriteTime = Get-Date
cmake --build out-mingw-gcc/static
```

```
[1/3] Building CXX object CMakeFiles/station.dir/stats.cpp.obj
[2/3] Linking CXX static library libstation.a
[3/3] Linking CXX executable rooster.exe
```

Only `stats.cpp` was recompiled. `report.cpp` and `main.cpp` were left
alone, and then the library and the program were rebuilt, because they
depend on `stats.cpp.obj`. This is why you use a build tool: with three
files it hardly matters, with three thousand it is the difference
between seconds and an hour.

#### 4. One target, and a Release build

Make a **second** build folder, this time for the `Release` build type,
and build only the **library** target:

```powershell
cmake -S . -B out-mingw-gcc/release -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release
cmake --build out-mingw-gcc/release --target station --verbose
Get-ChildItem out-mingw-gcc\release -Name
```

```
[1/3] g++.exe -DSTATION_STATIC_DEFINE -I... -O3 -DNDEBUG -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.obj -MF CMakeFiles\station.dir\stats.cpp.obj.d -o CMakeFiles/station.dir/stats.cpp.obj -c ...stats.cpp
[2/3] g++.exe ... -c ...report.cpp
[3/3] ... ar.exe qc libstation.a CMakeFiles/station.dir/stats.cpp.obj CMakeFiles/station.dir/report.cpp.obj && ... ranlib.exe libstation.a && cd .
CMakeFiles
.ninja_deps
.ninja_log
build.ninja
CMakeCache.txt
cmake_install.cmake
libstation.a
station_export.h
```

- **`-DCMAKE_BUILD_TYPE=Release`** sets a cache variable. Look at the
  flags it added: **`-O3 -DNDEBUG`** (optimise hard, and switch off
  `assert`). The folder from step 1 had neither.
- **`--target station`** builds the library and **nothing else**. There
  is a `libstation.a` in the folder and no `rooster.exe`. A target is
  how you ask "does just this part compile?" Without `--target`, CMake
  builds everything.

Now build the rest and run it:

```powershell
cmake --build out-mingw-gcc/release
.\out-mingw-gcc\release\rooster.exe
```

```
[1/2] Building CXX object CMakeFiles/rooster.dir/main.cpp.obj
[2/2] Linking CXX executable rooster.exe
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

Ninja built only what was missing.

#### 5. A dynamic library, with one option

`CMakeLists.txt` says `add_library(station ...)` with **no `STATIC` or
`SHARED`**. The **command line** decides, with one variable:

```powershell
cmake -S . -B out-mingw-gcc/shared -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DBUILD_SHARED_LIBS=ON
cmake --build out-mingw-gcc/shared --verbose
```

```
[1/5] g++.exe -Dstation_EXPORTS -I... -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.obj -MF CMakeFiles\station.dir\stats.cpp.obj.d -o CMakeFiles/station.dir/stats.cpp.obj -c ...stats.cpp
[2/5] g++.exe -Dstation_EXPORTS ... -c ...report.cpp
[3/5] g++.exe -I... -std=gnu++23 -MD ... -c ...main.cpp
[4/5] ... g++.exe -shared -o libstation.dll -Wl,--out-implib,libstation.dll.a ... CMakeFiles/station.dir/stats.cpp.obj CMakeFiles/station.dir/report.cpp.obj ...
[5/5] ... g++.exe CMakeFiles/rooster.dir/main.cpp.obj -o rooster.exe ... libstation.dll.a -lstdc++exp ...
```

(Shortened again.) Three things to notice. The library files are
compiled with **`-Dstation_EXPORTS`**: that is the macro that
`generate_export_header` looks for, and it is the `-DSTATION_BUILD_DLL`
you typed in 7.14. CMake defines it for you. Step 4 is now a
**`-shared`** link that makes a DLL and its import library
(`-Wl,--out-implib,...`, the option from 7.14), not an archive. And the
program is linked against **`libstation.dll.a`**, the import library,
with `-lstdc++exp` after it. Look at the result:

```powershell
Get-ChildItem out-mingw-gcc\shared\*.dll, out-mingw-gcc\shared\*.a | Format-Table Name, Length -AutoSize
.\out-mingw-gcc\shared\rooster.exe
```

```
Name              Length
----              ------
libstation.dll   477964
libstation.dll.a   3446

sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`libstation.dll` is the code and `libstation.dll.a` is the small
**import library**, the signpost of 7.14. CMake adds the `lib` prefix to
the name. The program runs because the DLL sits in the **same folder**
as `rooster.exe`, where the Windows loader looks first. One option, and
7.13 turned into 7.14, with no source changes.

#### 6. Install

```powershell
cmake --install out-mingw-gcc/static --prefix out-mingw-gcc/install
Get-ChildItem out-mingw-gcc\install -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
.\out-mingw-gcc\install\bin\rooster.exe
```

```
-- Install configuration: ""
-- Installing: .../out-mingw-gcc/install/bin/rooster.exe
-- Installing: .../out-mingw-gcc/install/lib/libstation.a
-- Installing: .../out-mingw-gcc/install/include/stats.h
-- Installing: .../out-mingw-gcc/install/include/report.h
-- Installing: .../out-mingw-gcc/install/include/station_export.h
out-mingw-gcc\install\bin\rooster.exe
out-mingw-gcc\install\include\report.h
out-mingw-gcc\install\include\station_export.h
out-mingw-gcc\install\include\stats.h
out-mingw-gcc\install\lib\libstation.a
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`--install` copies the **finished products** to a clean folder, as the
`install(...)` lines in `CMakeLists.txt` say. `--prefix` names the
folder. That is the **layout you hand to someone else**: the program in
`bin`, the library in `lib`, the headers in `include`.
(`Install configuration: ""` is the empty build type from step 1.)

Installing the **dynamic** build puts the DLL next to the program:

```powershell
cmake --install out-mingw-gcc/shared --prefix out-mingw-gcc/install-shared
Get-ChildItem out-mingw-gcc\install-shared -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
.\out-mingw-gcc\install-shared\bin\rooster.exe
```

```
out-mingw-gcc\install-shared\bin\libstation.dll
out-mingw-gcc\install-shared\bin\rooster.exe
out-mingw-gcc\install-shared\include\report.h
out-mingw-gcc\install-shared\include\station_export.h
out-mingw-gcc\install-shared\include\stats.h
out-mingw-gcc\install-shared\lib\libstation.dll.a
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(The `-- Installing:` lines are left out.) The `RUNTIME DESTINATION bin`
line in `CMakeLists.txt` covers programs **and DLLs**, so
`libstation.dll` lands in `bin`, next to `rooster.exe`, where Windows
finds it. The import library goes to `lib`.

#### 7. Break it on purpose

**a. A folder without `CMakeLists.txt`.** Point `-S` at the wrong
folder:

```powershell
cmake -S out-mingw-gcc -B out-mingw-gcc/oops -G Ninja
```

```
CMake Error: The source directory ".../out-mingw-gcc" does not appear to contain CMakeLists.txt.
Specify --help for usage, or press the help button on the CMake GUI.
```

`-S` must name the folder that **contains** `CMakeLists.txt`.

**b. A target that does not exist.** A typo in `--target`:

```powershell
cmake --build out-mingw-gcc/static --target stationn
```

```
ninja: error: unknown target 'stationn', did you mean 'station'?
```

That message comes from Ninja, which knows the list of targets from
`build.ninja`.

**c. Build a folder that was never configured.**

```powershell
cmake --build out-mingw-gcc/nothere
```

```
Error: .../out-mingw-gcc/nothere is not a directory
```

You have to **configure** (`-S ... -B ...`) before you can **build**.

**d. Change the compiler of a folder that is already configured.** First
configure a throw-away folder with GCC, then run the command again with
the C++ compiler changed to Clang:

```powershell
cmake -S . -B out-mingw-gcc/swap -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake -S . -B out-mingw-gcc/swap -G Ninja -DCMAKE_CXX_COMPILER=clang++
```

```
-- Configuring done (0.1s)
You have changed variables that require your cache to be deleted.
Configure will be re-run and you may have to reset some variables.
The following variables have changed:
CMAKE_CXX_COMPILER= clang++

-- The C compiler identification is GNU 16.2.0
-- The CXX compiler identification is Clang 23.1.3
...
```

This is a **warning, not an error**, and that is what makes it
dangerous. CMake **throws the cache away** and starts again. Everything
you had set is gone: only the option you just gave survived, so the **C
compiler fell back to the default**. We asked for GCC and ended up with
a folder that is not what we configured. (In Windows PowerShell the
warning may appear wrapped in red error text. CMake writes it to stderr.
It is still only a warning.) **Keep one build folder per compiler**,
which is why each command in this project has its own.

That is MinGW GCC done.

---

### Environment 3: Windows, MinGW Clang

**MinGW-w64** brings the GNU tool chain to Windows, and its package also
contains the **Clang** compiler. The programs it makes are ordinary
Windows programs. Clang here uses MinGW's libstdc++ (the one of GCC 16.2)
and, for the final link of a program, LLVM's own linker **lld**.
Ours is a UCRT build by Brecht Sanders in `C:\mingw64`:
`clang++ --version` says `clang version 23.1.3` and
`Target: x86_64-w64-windows-gnu`.

#### Open the shell

Open a **normal PowerShell**, not the Visual Studio Developer one, whose
`cl` would be picked up first. Put `C:\mingw64\bin` first on the PATH
**for this window**, then go to the folder (from the repository root):

```powershell
$env:Path = "C:\mingw64\bin;$env:Path"
cd 07.PracticalBuiltInFeatures\7.15ProjectCMakeCommandLine
cmake --version
ninja --version
clang++ --version
```

```
cmake version 4.4.4
...
1.13.2
(built by Brecht Sanders, r3) clang version 23.1.3
...
```

(Each `--version` prints a few more lines. Our MinGW package brings its
own `cmake` and `ninja`: `Get-Command cmake` tells you which `cmake`
runs for you. Both are fine.)

#### The tools in this environment

- **`cmake`**: the program this whole project is about. It configures,
  builds (by calling Ninja), and installs.
- **`ninja`**: the build tool. CMake calls it for you. It decides
  **what** has to be rebuilt and runs the commands.
- **`clang` and `clang++`**: the C and C++ compiler. CMake has to be
  **told** which compiler to use, with
  `-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++`. Without the
  options it would use whatever it finds first.
- **`llvm-ar.exe` and `llvm-ranlib.exe`**: the archiver of 7.13 and the
  tool that writes the archive's index. You never type them here: CMake
  does.

#### Where the output goes

You do not have to make a folder: CMake creates `out-mingw-clang/static`
(and `out-mingw-clang` above it) by itself when it configures.

#### 1. Configure

```powershell
cmake -S . -B out-mingw-clang/static -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```

```
-- The C compiler identification is Clang 23.1.3
-- The CXX compiler identification is Clang 23.1.3
...
-- Configuring done (1.3s)
-- Generating done (0.0s)
-- Build files have been written to: D:/.../7.15ProjectCMakeCommandLine/out-mingw-clang/static
```

(The many `Detecting ...` and `Check for working ...` lines are left
out.)

- **`-S .`**: the **S**ource folder, where `CMakeLists.txt` is.
- **`-B out-mingw-clang/static`**: the **B**uild folder, where
  everything generated goes. CMake creates it.
- **`-G Ninja`**: the generator.
- **`-D...`**: a **cache variable**. These two say which compilers to
  use. CMake checks a **C** compiler too, because `project(rooster)`
  does not list languages, and so turns on C as well as C++.

Now look at what configuring wrote:

```powershell
Get-ChildItem out-mingw-clang\static -Name
Select-String -Path out-mingw-clang\static\CMakeCache.txt -Pattern '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:|CMAKE_AR:)' | ForEach-Object { $_.Line }
```

```
CMakeFiles
build.ninja
CMakeCache.txt
cmake_install.cmake
station_export.h
CMAKE_AR:FILEPATH=C:/mingw64/bin/llvm-ar.exe
CMAKE_BUILD_TYPE:STRING=
CMAKE_CXX_COMPILER:STRING=C:/mingw64/bin/clang++.exe
CMAKE_MAKE_PROGRAM:FILEPATH=C:/mingw64/bin/ninja.exe
CMAKE_GENERATOR:INTERNAL=Ninja
```

- **`build.ninja`**: the plan: the list of commands Ninja will run.
- **`CMakeCache.txt`**: the cache, the folder's memory. It remembers the
  compiler, the archiver, the generator, and the **build type**. The
  build type is **empty** here: no optimisation flags and no debug
  flags. Step 4 comes back to this.
- **`station_export.h`**: the export header that
  `generate_export_header` wrote.
- **`cmake_install.cmake`** and **`CMakeFiles`**: CMake's own working
  files. You never edit them.

> **The compiler belongs to the build folder.** CMake stores the
> compiler in the cache. That has a consequence you will see in step 7:
> change the compiler of an existing folder and CMake throws the cache
> away. Keep **one build folder per compiler**.

#### 2. Build, and watch the real commands

```powershell
cmake --build out-mingw-clang/static --verbose
.\out-mingw-clang\static\rooster.exe
```

`cmake --build <folder>` runs Ninja for you. **`--verbose`** makes it
print the **real commands**:

```
[1/5] clang++.exe -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.obj -MF CMakeFiles\station.dir\stats.cpp.obj.d -o CMakeFiles/station.dir/stats.cpp.obj -c ...stats.cpp
[2/5] clang++.exe -DSTATION_STATIC_DEFINE ... -c ...report.cpp
[3/5] clang++.exe -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -MD ... -c ...main.cpp
[4/5] ... cmake.exe -E rm -f libstation.a && ... llvm-ar.exe qc libstation.a CMakeFiles/station.dir/stats.cpp.obj CMakeFiles/station.dir/report.cpp.obj && ... llvm-ranlib.exe libstation.a && cd .
[5/5] ... clang++.exe -fuse-ld=lld CMakeFiles/rooster.dir/main.cpp.obj -o rooster.exe -Wl,--out-implib,librooster.dll.a ... libstation.a -lstdc++exp -lkernel32 -luser32 -lgdi32 ...
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(Paths are shortened, the first few lines of `--verbose` and the end of
the long link line are left out.) Read them. This is the payoff of the
previous three lectures. Compare with what you typed:

- **Steps 1 to 3** are the compile commands of 7.12: one
  `clang++ ... -c file.cpp -o file.obj` per source file. CMake added
  `-MD -MT -MF`, which write a list of the headers each file includes,
  so Ninja knows what to rebuild. It also passes **`-std=gnu++23`**, not
  the `-std=c++23` you typed: `gnu++23` is C++23 plus GNU extensions,
  because CMake's `CXX_EXTENSIONS` defaults to on.
- **`-fvisibility=hidden`** is on the two **library** files only: it
  comes from `CXX_VISIBILITY_PRESET hidden`, the flag of 7.14.
  `main.cpp` does not have it. `-DSTATION_STATIC_DEFINE` is on all
  three, because the library marks it `PUBLIC`.
- **Step 4** is the archive of 7.13. CMake first removes any old
  `libstation.a`, then runs **`llvm-ar qc`** and **`llvm-ranlib`**, the
  LLVM versions of `ar` and `ranlib` that go with Clang. You typed
  `ar rcs`: the `s` writes the archive's index, and `ranlib` is the same
  "write the index" step as a separate command.
- **Step 5** is the link of 7.12 and 7.13: `rooster.exe` from
  `main.cpp.obj` and `libstation.a`, with **`-fuse-ld=lld`** first (the
  `target_link_options` line of `CMakeLists.txt`), then **`-lstdc++exp`**
  (the `target_link_libraries(... stdc++exp)` line, in the right place:
  **after** the objects that need it), then the Windows libraries every
  Windows program links.

**CMake is not magic. It is a command generator.** Whenever a CMake
build misbehaves, `--verbose` shows you the exact command that went
wrong, and you can run it yourself.

#### 3. Build again: only what changed

Run the same build without changing anything:

```powershell
cmake --build out-mingw-clang/static
```

```
ninja: no work to do.
```

Now change one source file. Setting its "last modified" time to now is
what saving the file in your editor does:

```powershell
(Get-Item stats.cpp).LastWriteTime = Get-Date
cmake --build out-mingw-clang/static
```

```
[1/3] Building CXX object CMakeFiles/station.dir/stats.cpp.obj
[2/3] Linking CXX static library libstation.a
[3/3] Linking CXX executable rooster.exe
```

Only `stats.cpp` was recompiled. `report.cpp` and `main.cpp` were left
alone, and then the library and the program were rebuilt, because they
depend on `stats.cpp.obj`. This is why you use a build tool: with three
files it hardly matters, with three thousand it is the difference
between seconds and an hour.

#### 4. One target, and a Release build

Make a **second** build folder, this time for the `Release` build type,
and build only the **library** target:

```powershell
cmake -S . -B out-mingw-clang/release -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
cmake --build out-mingw-clang/release --target station --verbose
Get-ChildItem out-mingw-clang\release -Name
```

```
[1/3] clang++.exe -DSTATION_STATIC_DEFINE -I... -O3 -DNDEBUG -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.obj -MF CMakeFiles\station.dir\stats.cpp.obj.d -o CMakeFiles/station.dir/stats.cpp.obj -c ...stats.cpp
[2/3] clang++.exe ... -c ...report.cpp
[3/3] ... llvm-ar.exe qc libstation.a CMakeFiles/station.dir/stats.cpp.obj CMakeFiles/station.dir/report.cpp.obj && ... llvm-ranlib.exe libstation.a && cd .
CMakeFiles
.ninja_deps
.ninja_log
build.ninja
CMakeCache.txt
cmake_install.cmake
libstation.a
station_export.h
```

- **`-DCMAKE_BUILD_TYPE=Release`** sets a cache variable. Look at the
  flags it added: **`-O3 -DNDEBUG`** (optimise hard, and switch off
  `assert`). The folder from step 1 had neither.
- **`--target station`** builds the library and **nothing else**. There
  is a `libstation.a` in the folder and no `rooster.exe`. A target is
  how you ask "does just this part compile?" Without `--target`, CMake
  builds everything.

Now build the rest and run it:

```powershell
cmake --build out-mingw-clang/release
.\out-mingw-clang\release\rooster.exe
```

```
[1/2] Building CXX object CMakeFiles/rooster.dir/main.cpp.obj
[2/2] Linking CXX executable rooster.exe
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

Ninja built only what was missing.

#### 5. A dynamic library, with one option

`CMakeLists.txt` says `add_library(station ...)` with **no `STATIC` or
`SHARED`**. The **command line** decides, with one variable:

```powershell
cmake -S . -B out-mingw-clang/shared -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=ON
cmake --build out-mingw-clang/shared --verbose
```

```
[1/5] clang++.exe -Dstation_EXPORTS -I... -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.obj -MF CMakeFiles\station.dir\stats.cpp.obj.d -o CMakeFiles/station.dir/stats.cpp.obj -c ...stats.cpp
[2/5] clang++.exe -Dstation_EXPORTS ... -c ...report.cpp
[3/5] clang++.exe -I... -std=gnu++23 -MD ... -c ...main.cpp
[4/5] ... clang++.exe -shared -o libstation.dll -Wl,--out-implib,libstation.dll.a ... CMakeFiles/station.dir/stats.cpp.obj CMakeFiles/station.dir/report.cpp.obj ...
[5/5] ... clang++.exe -fuse-ld=lld CMakeFiles/rooster.dir/main.cpp.obj -o rooster.exe ... libstation.dll.a -lstdc++exp ...
```

(Shortened again.) Three things to notice. The library files are
compiled with **`-Dstation_EXPORTS`**: that is the macro that
`generate_export_header` looks for, and it is the `-DSTATION_BUILD_DLL`
you typed in 7.14. CMake defines it for you. Step 4 is now a
**`-shared`** link that makes a DLL and its import library
(`-Wl,--out-implib,...`, the option from 7.14), not an archive. And the
program is linked against **`libstation.dll.a`**, the import library,
with `-lstdc++exp` after it. Look at the result:

```powershell
Get-ChildItem out-mingw-clang\shared\*.dll, out-mingw-clang\shared\*.a | Format-Table Name, Length -AutoSize
.\out-mingw-clang\shared\rooster.exe
```

```
Name              Length
----              ------
libstation.dll   497812
libstation.dll.a   3446

sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`libstation.dll` is the code and `libstation.dll.a` is the small
**import library**, the signpost of 7.14. CMake adds the `lib` prefix to
the name. The program runs because the DLL sits in the **same folder**
as `rooster.exe`, where the Windows loader looks first. One option, and
7.13 turned into 7.14, with no source changes.

#### 6. Install

```powershell
cmake --install out-mingw-clang/static --prefix out-mingw-clang/install
Get-ChildItem out-mingw-clang\install -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
.\out-mingw-clang\install\bin\rooster.exe
```

```
-- Install configuration: ""
-- Installing: .../out-mingw-clang/install/bin/rooster.exe
-- Installing: .../out-mingw-clang/install/lib/libstation.a
-- Installing: .../out-mingw-clang/install/include/stats.h
-- Installing: .../out-mingw-clang/install/include/report.h
-- Installing: .../out-mingw-clang/install/include/station_export.h
out-mingw-clang\install\bin\rooster.exe
out-mingw-clang\install\include\report.h
out-mingw-clang\install\include\station_export.h
out-mingw-clang\install\include\stats.h
out-mingw-clang\install\lib\libstation.a
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

`--install` copies the **finished products** to a clean folder, as the
`install(...)` lines in `CMakeLists.txt` say. `--prefix` names the
folder. That is the **layout you hand to someone else**: the program in
`bin`, the library in `lib`, the headers in `include`.
(`Install configuration: ""` is the empty build type from step 1.)

Installing the **dynamic** build puts the DLL next to the program:

```powershell
cmake --install out-mingw-clang/shared --prefix out-mingw-clang/install-shared
Get-ChildItem out-mingw-clang\install-shared -Recurse -File | ForEach-Object { $_.FullName.Substring((Get-Location).Path.Length + 1) }
.\out-mingw-clang\install-shared\bin\rooster.exe
```

```
out-mingw-clang\install-shared\bin\libstation.dll
out-mingw-clang\install-shared\bin\rooster.exe
out-mingw-clang\install-shared\include\report.h
out-mingw-clang\install-shared\include\station_export.h
out-mingw-clang\install-shared\include\stats.h
out-mingw-clang\install-shared\lib\libstation.dll.a
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(The `-- Installing:` lines are left out.) The `RUNTIME DESTINATION bin`
line in `CMakeLists.txt` covers programs **and DLLs**, so
`libstation.dll` lands in `bin`, next to `rooster.exe`, where Windows
finds it. The import library goes to `lib`.

#### 7. Break it on purpose

**a. A folder without `CMakeLists.txt`.** Point `-S` at the wrong
folder:

```powershell
cmake -S out-mingw-clang -B out-mingw-clang/oops -G Ninja
```

```
CMake Error: The source directory ".../out-mingw-clang" does not appear to contain CMakeLists.txt.
Specify --help for usage, or press the help button on the CMake GUI.
```

`-S` must name the folder that **contains** `CMakeLists.txt`.

**b. A target that does not exist.** A typo in `--target`:

```powershell
cmake --build out-mingw-clang/static --target stationn
```

```
ninja: error: unknown target 'stationn', did you mean 'station'?
```

That message comes from Ninja, which knows the list of targets from
`build.ninja`.

**c. Build a folder that was never configured.**

```powershell
cmake --build out-mingw-clang/nothere
```

```
Error: .../out-mingw-clang/nothere is not a directory
```

You have to **configure** (`-S ... -B ...`) before you can **build**.

**d. Change the compiler of a folder that is already configured.** First
configure a throw-away folder with Clang, then run the command again
with the C++ compiler changed to GCC:

```powershell
cmake -S . -B out-mingw-clang/swap -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake -S . -B out-mingw-clang/swap -G Ninja -DCMAKE_CXX_COMPILER=g++
```

```
-- Configuring done (0.1s)
You have changed variables that require your cache to be deleted.
Configure will be re-run and you may have to reset some variables.
The following variables have changed:
CMAKE_CXX_COMPILER= g++

-- The C compiler identification is GNU 16.2.0
-- The CXX compiler identification is GNU 16.2.0
...
```

This is a **warning, not an error**, and that is what makes it
dangerous. CMake **throws the cache away** and starts again. Everything
you had set is gone: only the option you just gave survived, so the **C
compiler fell back to the default**. We asked for Clang and ended up
with a folder that is not what we configured. (In Windows PowerShell the
warning may appear wrapped in red error text. CMake writes it to stderr.
It is still only a warning.) **Keep one build folder per compiler**,
which is why each command in this project has its own.

That is MinGW Clang done.

---

### Environment 4: Linux, GCC (Docker)

You get a real Linux with GCC from the Docker container of chapter 2.
Our image carries GCC 16.2, CMake 3.31.6 and Ninja 1.12.1.

#### Open the shell

From the repository root, in PowerShell:

```powershell
docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-gcc
```

You land in `/workspace`, which is the repository. Now, inside the
container:

```sh
cd 07.PracticalBuiltInFeatures/7.15ProjectCMakeCommandLine
cmake --version
ninja --version
g++ --version
```

```
cmake version 3.31.6
...
1.12.1
g++ (GCC) 16.2.0
...
```

(Each `--version` prints a few more lines. `--rm` throws the container
away when you leave. The files you create stay in your folder on
Windows, in `out-linux-gcc`, because of the `-v` mount. They are ignored
by git.)

#### The tools in this environment

- **`cmake`**: the program this whole project is about. It configures,
  builds (by calling Ninja), and installs.
- **`ninja`**: the build tool. CMake calls it for you. It decides
  **what** has to be rebuilt and runs the commands.
- **`gcc` and `g++`**: the C and C++ compiler. CMake has to be **told**
  which compiler to use, with
  `-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++`. Without the options
  it would use whatever it finds first.
- **`ar` and `ranlib`**: the archiver of 7.13 and the tool that writes
  the archive's index. You never type them here: CMake does.
- **`readelf` and `ldd`**: the tools of 7.14 for asking a program which
  libraries it needs and where the loader finds them.

#### Where the output goes

You do not have to make a folder: CMake creates `out-linux-gcc/static`
(and `out-linux-gcc` above it) by itself when it configures.

#### 1. Configure

```sh
cmake -S . -B out-linux-gcc/static -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
```

```
-- The C compiler identification is GNU 16.2.0
-- The CXX compiler identification is GNU 16.2.0
...
-- Configuring done (1.4s)
-- Generating done (0.0s)
-- Build files have been written to: /workspace/07.PracticalBuiltInFeatures/7.15ProjectCMakeCommandLine/out-linux-gcc/static
```

(The many `Detecting ...` and `Check for working ...` lines are left
out.)

- **`-S .`**: the **S**ource folder, where `CMakeLists.txt` is.
- **`-B out-linux-gcc/static`**: the **B**uild folder, where everything
  generated goes. CMake creates it.
- **`-G Ninja`**: the generator.
- **`-D...`**: a **cache variable**. These two say which compilers to
  use. CMake checks a **C** compiler too, because `project(rooster)`
  does not list languages, and so turns on C as well as C++.

Now look at what configuring wrote:

```sh
ls out-linux-gcc/static
grep -E '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:|CMAKE_AR:)' out-linux-gcc/static/CMakeCache.txt
```

```
CMakeCache.txt
CMakeFiles
build.ninja
cmake_install.cmake
station_export.h
CMAKE_AR:FILEPATH=/usr/bin/ar
CMAKE_BUILD_TYPE:STRING=
CMAKE_CXX_COMPILER:STRING=/usr/local/bin/g++
CMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/ninja
CMAKE_GENERATOR:INTERNAL=Ninja
```

- **`build.ninja`**: the plan: the list of commands Ninja will run.
- **`CMakeCache.txt`**: the cache, the folder's memory. It remembers the
  compiler, the archiver, the generator, and the **build type**. The
  build type is **empty** here: no optimisation flags and no debug
  flags. Step 4 comes back to this.
- **`station_export.h`**: the export header that
  `generate_export_header` wrote.
- **`cmake_install.cmake`** and **`CMakeFiles`**: CMake's own working
  files. You never edit them.

> **The compiler belongs to the build folder.** CMake stores the
> compiler in the cache. That has a consequence you will see in step 7:
> change the compiler of an existing folder and CMake throws the cache
> away. Keep **one build folder per compiler**.

#### 2. Build, and watch the real commands

```sh
cmake --build out-linux-gcc/static --verbose
./out-linux-gcc/static/rooster
```

`cmake --build <folder>` runs Ninja for you. **`--verbose`** makes it
print the **real commands**:

```
[1/5] /usr/local/bin/g++ -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.o -MF CMakeFiles/station.dir/stats.cpp.o.d -o CMakeFiles/station.dir/stats.cpp.o -c .../stats.cpp
[2/5] /usr/local/bin/g++ -DSTATION_STATIC_DEFINE ... -c .../report.cpp
[3/5] /usr/local/bin/g++ -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -MD ... -c .../main.cpp
[4/5] : && /usr/bin/cmake -E rm -f libstation.a && /usr/bin/ar qc libstation.a CMakeFiles/station.dir/stats.cpp.o CMakeFiles/station.dir/report.cpp.o && /usr/bin/ranlib libstation.a && :
[5/5] : && /usr/local/bin/g++ -Wl,--dependency-file=CMakeFiles/rooster.dir/link.d CMakeFiles/rooster.dir/main.cpp.o -o rooster libstation.a && :
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(Paths are shortened, and the first few lines of `--verbose` are left
out.) Read them. This is the payoff of the previous three lectures.
Compare with what you typed:

- **Steps 1 to 3** are the compile commands of 7.12: one
  `g++ ... -c file.cpp -o file.o` per source file. CMake added
  `-MD -MT -MF`, which write a list of the headers each file includes,
  so Ninja knows what to rebuild. It also passes **`-std=gnu++23`**, not
  the `-std=c++23` you typed: `gnu++23` is C++23 plus GNU extensions,
  because CMake's `CXX_EXTENSIONS` defaults to on. The compiler has its
  full path, `/usr/local/bin/g++`, because that is what is in the cache.
- **`-fvisibility=hidden`** is on the two **library** files only: it
  comes from `CXX_VISIBILITY_PRESET hidden`, the flag of 7.14.
  `main.cpp` does not have it. `-DSTATION_STATIC_DEFINE` is on all
  three, because the library marks it `PUBLIC`.
- **Step 4** is the archive of 7.13. The `: &&` at the start is a
  do-nothing command that Ninja needs, and CMake first removes any old
  `libstation.a`. Then comes **`ar qc`** and **`ranlib`**. You typed
  `ar rcs`: the `s` writes the archive's index, and `ranlib` is the same
  "write the index" step as a separate command.
- **Step 5** is the link of 7.12 and 7.13: `main.cpp.o` and
  `libstation.a` into `rooster`. The `-Wl,--dependency-file=...` option
  makes the linker list the files it read, for Ninja.

**CMake is not magic. It is a command generator.** Whenever a CMake
build misbehaves, `--verbose` shows you the exact command that went
wrong, and you can run it yourself.

#### 3. Build again: only what changed

Run the same build without changing anything:

```sh
cmake --build out-linux-gcc/static
```

```
ninja: no work to do.
```

Now change one source file. `touch` sets its "last modified" time to
now, which is what saving the file in your editor does:

```sh
touch stats.cpp
cmake --build out-linux-gcc/static
```

```
[1/3] Building CXX object CMakeFiles/station.dir/stats.cpp.o
[2/3] Linking CXX static library libstation.a
[3/3] Linking CXX executable rooster
```

Only `stats.cpp` was recompiled. `report.cpp` and `main.cpp` were left
alone, and then the library and the program were rebuilt, because they
depend on `stats.cpp.o`. This is why you use a build tool: with three
files it hardly matters, with three thousand it is the difference
between seconds and an hour.

#### 4. One target, and a Release build

Make a **second** build folder, this time for the `Release` build type,
and build only the **library** target:

```sh
cmake -S . -B out-linux-gcc/release -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release
cmake --build out-linux-gcc/release --target station --verbose
ls out-linux-gcc/release
```

```
[1/3] /usr/local/bin/g++ -DSTATION_STATIC_DEFINE -I... -O3 -DNDEBUG -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.o -MF CMakeFiles/station.dir/stats.cpp.o.d -o CMakeFiles/station.dir/stats.cpp.o -c .../stats.cpp
[2/3] /usr/local/bin/g++ ... -c .../report.cpp
[3/3] : && /usr/bin/cmake -E rm -f libstation.a && /usr/bin/ar qc libstation.a CMakeFiles/station.dir/stats.cpp.o CMakeFiles/station.dir/report.cpp.o && /usr/bin/ranlib libstation.a && :
CMakeCache.txt
CMakeFiles
build.ninja
cmake_install.cmake
libstation.a
station_export.h
```

- **`-DCMAKE_BUILD_TYPE=Release`** sets a cache variable. Look at the
  flags it added: **`-O3 -DNDEBUG`** (optimise hard, and switch off
  `assert`). The folder from step 1 had neither.
- **`--target station`** builds the library and **nothing else**. There
  is a `libstation.a` in the folder and no `rooster`. A target is how
  you ask "does just this part compile?" Without `--target`, CMake
  builds everything.

Now build the rest and run it:

```sh
cmake --build out-linux-gcc/release
./out-linux-gcc/release/rooster
```

```
[1/2] Building CXX object CMakeFiles/rooster.dir/main.cpp.o
[2/2] Linking CXX executable rooster
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

Ninja built only what was missing.

#### 5. A dynamic library, with one option

`CMakeLists.txt` says `add_library(station ...)` with **no `STATIC` or
`SHARED`**. The **command line** decides, with one variable:

```sh
cmake -S . -B out-linux-gcc/shared -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DBUILD_SHARED_LIBS=ON
cmake --build out-linux-gcc/shared --verbose
```

```
[1/5] /usr/local/bin/g++ -Dstation_EXPORTS -I... -std=gnu++23 -fPIC -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.o -MF CMakeFiles/station.dir/stats.cpp.o.d -o CMakeFiles/station.dir/stats.cpp.o -c .../stats.cpp
[2/5] /usr/local/bin/g++ -Dstation_EXPORTS ... -c .../report.cpp
[3/5] /usr/local/bin/g++ -I... -std=gnu++23 -MD ... -c .../main.cpp
[4/5] : && /usr/local/bin/g++ -fPIC -Wl,--dependency-file=CMakeFiles/station.dir/link.d -shared -Wl,-soname,libstation.so -o libstation.so CMakeFiles/station.dir/stats.cpp.o CMakeFiles/station.dir/report.cpp.o && :
[5/5] : && /usr/local/bin/g++ -Wl,--dependency-file=CMakeFiles/rooster.dir/link.d CMakeFiles/rooster.dir/main.cpp.o -o rooster -Wl,-rpath,.../out-linux-gcc/shared: libstation.so && :
```

(Shortened again, and the order of steps 1 to 3 can differ from run to
run.) Look at what CMake typed for you, and compare with 7.14:

- The library files are compiled with **`-Dstation_EXPORTS`**, the macro
  that `generate_export_header` looks for. It is the
  `-DSTATION_BUILD_DLL` you typed in 7.14.
- They are also compiled with **`-fPIC`**, and with
  **`-fvisibility=hidden`**, the two flags of 7.14. CMake added `-fPIC`
  by itself, because a shared library needs it.
- Step 4 is a **`-shared`** link that makes `libstation.so`, with
  `-Wl,-soname,libstation.so` giving it its run-time name.
- Step 5 links the program against `libstation.so`, and look at
  **`-Wl,-rpath,.../out-linux-gcc/shared:`**. CMake **baked the build
  folder into the program**, the same idea as the `-Wl,-rpath,'$ORIGIN'`
  you typed in 7.14, but with an absolute path.

```sh
ls -l out-linux-gcc/shared/libstation.so out-linux-gcc/shared/rooster
./out-linux-gcc/shared/rooster
readelf -d out-linux-gcc/shared/rooster | grep -E 'NEEDED.*station|RUNPATH'
ldd out-linux-gcc/shared/rooster | grep station
```

```
-rwxr-xr-x 1 root root 352640 Oct 14 16:37 out-linux-gcc/shared/libstation.so
-rwxr-xr-x 1 root root 324888 Oct 14 16:37 out-linux-gcc/shared/rooster
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
 0x0000000000000001 (NEEDED)             Shared library: [libstation.so]
 0x000000000000001d (RUNPATH)            Library runpath: [/workspace/07.PracticalBuiltInFeatures/7.15ProjectCMakeCommandLine/out-linux-gcc/shared:]
	libstation.so => /workspace/07.PracticalBuiltInFeatures/7.15ProjectCMakeCommandLine/out-linux-gcc/shared/libstation.so (0x00007f775da6d000)
```

The program starts **without** `LD_LIBRARY_PATH`, and `ldd` finds the
library, thanks to the `RUNPATH` that CMake wrote into it. (The address
in brackets differs on every run, and the date in the `ls` lines will be
yours.) One option, and 7.13 turned into 7.14, with no source changes.

#### 6. Install

```sh
cmake --install out-linux-gcc/static --prefix out-linux-gcc/install
find out-linux-gcc/install -type f
./out-linux-gcc/install/bin/rooster
```

```
-- Install configuration: ""
-- Installing: .../out-linux-gcc/install/bin/rooster
-- Installing: .../out-linux-gcc/install/lib/libstation.a
-- Installing: .../out-linux-gcc/install/include/stats.h
-- Installing: .../out-linux-gcc/install/include/report.h
-- Installing: .../out-linux-gcc/install/include/station_export.h
out-linux-gcc/install/bin/rooster
out-linux-gcc/install/lib/libstation.a
out-linux-gcc/install/include/stats.h
out-linux-gcc/install/include/report.h
out-linux-gcc/install/include/station_export.h
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(The order of the `find` lines can differ.) `--install` copies the
**finished products** to a clean folder, as the `install(...)` lines in
`CMakeLists.txt` say. `--prefix` names the folder. That is the **layout
you hand to someone else**: the program in `bin`, the library in `lib`,
the headers in `include`. (`Install configuration: ""` is the empty
build type from step 1.)

Now install the **dynamic** build, and run the installed program:

```sh
cmake --install out-linux-gcc/shared --prefix out-linux-gcc/install-shared
./out-linux-gcc/install-shared/bin/rooster
echo $?
```

```
-- Install configuration: ""
-- Installing: .../out-linux-gcc/install-shared/bin/rooster
-- Set non-toolchain portion of runtime path of ".../out-linux-gcc/install-shared/bin/rooster" to ""
-- Installing: .../out-linux-gcc/install-shared/lib/libstation.so
-- Installing: .../out-linux-gcc/install-shared/include/stats.h
-- Installing: .../out-linux-gcc/install-shared/include/report.h
-- Installing: .../out-linux-gcc/install-shared/include/station_export.h
./out-linux-gcc/install-shared/bin/rooster: error while loading shared libraries: libstation.so: cannot open shared object file: No such file or directory
127
```

It **fails**, with the error you know from 7.14. Look at the line
`Set non-toolchain portion of runtime path ... to ""`: when it installs
a program, CMake **removes the build-folder path** from its `RUNPATH`,
because the build folder is not meant to be there when you hand the
program to someone. Now the loader has no idea where `libstation.so` is.
You know two fixes from 7.14. The first is to tell the loader for one
run:

```sh
LD_LIBRARY_PATH=out-linux-gcc/install-shared/lib ./out-linux-gcc/install-shared/bin/rooster
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

The second is to ask CMake to write a **relative** path, for the
installed program, with one more cache variable. `$ORIGIN` is "the
folder the program is in", so `$ORIGIN/../lib` is the `lib` folder next
to `bin`. Configure the dynamic folder again with it, and install again:

```sh
cmake -S . -B out-linux-gcc/shared -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DBUILD_SHARED_LIBS=ON '-DCMAKE_INSTALL_RPATH=$ORIGIN/../lib'
cmake --build out-linux-gcc/shared
cmake --install out-linux-gcc/shared --prefix out-linux-gcc/install-shared
readelf -d out-linux-gcc/install-shared/bin/rooster | grep RUNPATH
./out-linux-gcc/install-shared/bin/rooster
```

```
 0x000000000000001d (RUNPATH)            Library runpath: [$ORIGIN/../lib]
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(Quote the `$ORIGIN` so your shell does not eat it. The `-- Installing:`
lines are left out.) The installed program now finds its library
wherever you put the `install-shared` folder. On Windows none of this
was needed: the DLL goes in `bin`, next to the program.

#### 7. Break it on purpose

**a. A folder without `CMakeLists.txt`.** Point `-S` at the wrong
folder:

```sh
cmake -S out-linux-gcc -B out-linux-gcc/oops -G Ninja
```

```
CMake Error: The source directory ".../out-linux-gcc" does not appear to contain CMakeLists.txt.
Specify --help for usage, or press the help button on the CMake GUI.
```

`-S` must name the folder that **contains** `CMakeLists.txt`.

**b. A target that does not exist.** A typo in `--target`:

```sh
cmake --build out-linux-gcc/static --target stationn
```

```
ninja: error: unknown target 'stationn', did you mean 'station'?
```

That message comes from Ninja, which knows the list of targets from
`build.ninja`.

**c. Build a folder that was never configured.**

```sh
cmake --build out-linux-gcc/nothere
```

```
Error: .../out-linux-gcc/nothere is not a directory
```

You have to **configure** (`-S ... -B ...`) before you can **build**.

**d. Change the compiler of a folder that is already configured.** First
configure a throw-away folder with GCC 16, then run the command again
with the C++ compiler changed to the GCC 14 that the image also carries
(`/usr/bin/g++-14`):

```sh
cmake -S . -B out-linux-gcc/swap -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake -S . -B out-linux-gcc/swap -G Ninja -DCMAKE_CXX_COMPILER=/usr/bin/g++-14
```

```
-- Configuring done (0.0s)
You have changed variables that require your cache to be deleted.
Configure will be re-run and you may have to reset some variables.
The following variables have changed:
CMAKE_CXX_COMPILER= /usr/bin/g++-14

-- The C compiler identification is GNU 16.2.0
-- The CXX compiler identification is GNU 14.2.0
...
```

This is a **warning, not an error**, and that is what makes it
dangerous. CMake **throws the cache away** and starts again. Everything
you had set is gone, and only the option you just gave survived. Look at
the last two lines: the C compiler is GCC **16.2.0** and the C++
compiler is GCC **14.2.0**. You now have a folder that is **neither of
the two you asked for**. **Keep one build folder per compiler**, which
is why each command in this project has its own.

That is Linux GCC done.

---

### Environment 5: Linux, Clang (Docker)

You get a real Linux with Clang from the Docker container of chapter 2.
Our image carries Clang 21.1.8, CMake 3.31.6 and Ninja 1.12.1.

#### Open the shell

From the repository root, in PowerShell:

```powershell
docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-clang
```

You land in `/workspace`, which is the repository. Now, inside the
container:

```sh
cd 07.PracticalBuiltInFeatures/7.15ProjectCMakeCommandLine
cmake --version
ninja --version
clang++ --version
```

```
cmake version 3.31.6
...
1.12.1
Debian clang version 21.1.8 (++20251221033036+2078da43e25a-1~exp1~20251221153213.50)
...
```

(Each `--version` prints a few more lines. `--rm` throws the container
away when you leave. The files you create stay in your folder on
Windows, in `out-linux-clang`, because of the `-v` mount. They are
ignored by git.)

#### The tools in this environment

- **`cmake`**: the program this whole project is about. It configures,
  builds (by calling Ninja), and installs.
- **`ninja`**: the build tool. CMake calls it for you. It decides
  **what** has to be rebuilt and runs the commands.
- **`clang` and `clang++`**: the C and C++ compiler. CMake has to be
  **told** which compiler to use, with
  `-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++`. Without the
  options it would use whatever it finds first.
- **`llvm-ar` and `llvm-ranlib`**: the archiver of 7.13 and the tool
  that writes the archive's index. You never type them here: CMake does.
- **`readelf` and `ldd`**: the tools of 7.14 for asking a program which
  libraries it needs and where the loader finds them.

#### Where the output goes

You do not have to make a folder: CMake creates `out-linux-clang/static`
(and `out-linux-clang` above it) by itself when it configures.

#### 1. Configure

```sh
cmake -S . -B out-linux-clang/static -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```

```
-- The C compiler identification is Clang 21.1.8
-- The CXX compiler identification is Clang 21.1.8
...
-- Configuring done (1.4s)
-- Generating done (0.0s)
-- Build files have been written to: /workspace/07.PracticalBuiltInFeatures/7.15ProjectCMakeCommandLine/out-linux-clang/static
```

(The many `Detecting ...` and `Check for working ...` lines are left
out.)

- **`-S .`**: the **S**ource folder, where `CMakeLists.txt` is.
- **`-B out-linux-clang/static`**: the **B**uild folder, where
  everything generated goes. CMake creates it.
- **`-G Ninja`**: the generator.
- **`-D...`**: a **cache variable**. These two say which compilers to
  use. CMake checks a **C** compiler too, because `project(rooster)`
  does not list languages, and so turns on C as well as C++.

Now look at what configuring wrote:

```sh
ls out-linux-clang/static
grep -E '^(CMAKE_CXX_COMPILER:|CMAKE_BUILD_TYPE:|CMAKE_GENERATOR:|CMAKE_MAKE_PROGRAM:|CMAKE_AR:)' out-linux-clang/static/CMakeCache.txt
```

```
CMakeCache.txt
CMakeFiles
build.ninja
cmake_install.cmake
station_export.h
CMAKE_AR:FILEPATH=/usr/bin/llvm-ar
CMAKE_BUILD_TYPE:STRING=
CMAKE_CXX_COMPILER:STRING=/usr/bin/clang++
CMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/ninja
CMAKE_GENERATOR:INTERNAL=Ninja
```

- **`build.ninja`**: the plan: the list of commands Ninja will run.
- **`CMakeCache.txt`**: the cache, the folder's memory. It remembers the
  compiler, the archiver, the generator, and the **build type**. The
  build type is **empty** here: no optimisation flags and no debug
  flags. Step 4 comes back to this.
- **`station_export.h`**: the export header that
  `generate_export_header` wrote.
- **`cmake_install.cmake`** and **`CMakeFiles`**: CMake's own working
  files. You never edit them.

> **The compiler belongs to the build folder.** CMake stores the
> compiler in the cache. That has a consequence you will see in step 7:
> change the compiler of an existing folder and CMake throws the cache
> away. Keep **one build folder per compiler**.

#### 2. Build, and watch the real commands

```sh
cmake --build out-linux-clang/static --verbose
./out-linux-clang/static/rooster
```

`cmake --build <folder>` runs Ninja for you. **`--verbose`** makes it
print the **real commands**:

```
[1/5] /usr/bin/clang++ -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.o -MF CMakeFiles/station.dir/stats.cpp.o.d -o CMakeFiles/station.dir/stats.cpp.o -c .../stats.cpp
[2/5] /usr/bin/clang++ -DSTATION_STATIC_DEFINE ... -c .../report.cpp
[3/5] /usr/bin/clang++ -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -MD ... -c .../main.cpp
[4/5] : && /usr/bin/cmake -E rm -f libstation.a && /usr/bin/llvm-ar qc libstation.a CMakeFiles/station.dir/stats.cpp.o CMakeFiles/station.dir/report.cpp.o && /usr/bin/llvm-ranlib libstation.a && :
[5/5] : && /usr/bin/clang++ -Xlinker --dependency-file=CMakeFiles/rooster.dir/link.d CMakeFiles/rooster.dir/main.cpp.o -o rooster libstation.a && :
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(Paths are shortened, and the first few lines of `--verbose` are left
out.) Read them. This is the payoff of the previous three lectures.
Compare with what you typed:

- **Steps 1 to 3** are the compile commands of 7.12: one
  `clang++ ... -c file.cpp -o file.o` per source file. CMake added
  `-MD -MT -MF`, which write a list of the headers each file includes,
  so Ninja knows what to rebuild. It also passes **`-std=gnu++23`**, not
  the `-std=c++23` you typed: `gnu++23` is C++23 plus GNU extensions,
  because CMake's `CXX_EXTENSIONS` defaults to on. The compiler has its
  full path, `/usr/bin/clang++`, because that is what is in the cache.
- **`-fvisibility=hidden`** is on the two **library** files only: it
  comes from `CXX_VISIBILITY_PRESET hidden`, the flag of 7.14.
  `main.cpp` does not have it. `-DSTATION_STATIC_DEFINE` is on all
  three, because the library marks it `PUBLIC`.
- **Step 4** is the archive of 7.13. The `: &&` at the start is a
  do-nothing command that Ninja needs, and CMake first removes any old
  `libstation.a`. Then comes **`llvm-ar qc`** and **`llvm-ranlib`**, the
  LLVM versions of `ar` and `ranlib` that go with Clang. You typed
  `ar rcs`: the `s` writes the archive's index, and `ranlib` is the same
  "write the index" step as a separate command.
- **Step 5** is the link of 7.12 and 7.13: `main.cpp.o` and
  `libstation.a` into `rooster`. The `-Xlinker --dependency-file=...`
  option makes the linker list the files it read, for Ninja.

**CMake is not magic. It is a command generator.** Whenever a CMake
build misbehaves, `--verbose` shows you the exact command that went
wrong, and you can run it yourself.

#### 3. Build again: only what changed

Run the same build without changing anything:

```sh
cmake --build out-linux-clang/static
```

```
ninja: no work to do.
```

Now change one source file. `touch` sets its "last modified" time to
now, which is what saving the file in your editor does:

```sh
touch stats.cpp
cmake --build out-linux-clang/static
```

```
[1/3] Building CXX object CMakeFiles/station.dir/stats.cpp.o
[2/3] Linking CXX static library libstation.a
[3/3] Linking CXX executable rooster
```

Only `stats.cpp` was recompiled. `report.cpp` and `main.cpp` were left
alone, and then the library and the program were rebuilt, because they
depend on `stats.cpp.o`. This is why you use a build tool: with three
files it hardly matters, with three thousand it is the difference
between seconds and an hour.

#### 4. One target, and a Release build

Make a **second** build folder, this time for the `Release` build type,
and build only the **library** target:

```sh
cmake -S . -B out-linux-clang/release -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
cmake --build out-linux-clang/release --target station --verbose
ls out-linux-clang/release
```

```
[1/3] /usr/bin/clang++ -DSTATION_STATIC_DEFINE -I... -O3 -DNDEBUG -std=gnu++23 -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.o -MF CMakeFiles/station.dir/stats.cpp.o.d -o CMakeFiles/station.dir/stats.cpp.o -c .../stats.cpp
[2/3] /usr/bin/clang++ ... -c .../report.cpp
[3/3] : && /usr/bin/cmake -E rm -f libstation.a && /usr/bin/llvm-ar qc libstation.a CMakeFiles/station.dir/stats.cpp.o CMakeFiles/station.dir/report.cpp.o && /usr/bin/llvm-ranlib libstation.a && :
CMakeCache.txt
CMakeFiles
build.ninja
cmake_install.cmake
libstation.a
station_export.h
```

- **`-DCMAKE_BUILD_TYPE=Release`** sets a cache variable. Look at the
  flags it added: **`-O3 -DNDEBUG`** (optimise hard, and switch off
  `assert`). The folder from step 1 had neither.
- **`--target station`** builds the library and **nothing else**. There
  is a `libstation.a` in the folder and no `rooster`. A target is how
  you ask "does just this part compile?" Without `--target`, CMake
  builds everything.

Now build the rest and run it:

```sh
cmake --build out-linux-clang/release
./out-linux-clang/release/rooster
```

```
[1/2] Building CXX object CMakeFiles/rooster.dir/main.cpp.o
[2/2] Linking CXX executable rooster
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

Ninja built only what was missing.

#### 5. A dynamic library, with one option

`CMakeLists.txt` says `add_library(station ...)` with **no `STATIC` or
`SHARED`**. The **command line** decides, with one variable:

```sh
cmake -S . -B out-linux-clang/shared -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=ON
cmake --build out-linux-clang/shared --verbose
```

```
[1/5] /usr/bin/clang++ -Dstation_EXPORTS -I... -std=gnu++23 -fPIC -fvisibility=hidden -MD -MT CMakeFiles/station.dir/stats.cpp.o -MF CMakeFiles/station.dir/stats.cpp.o.d -o CMakeFiles/station.dir/stats.cpp.o -c .../stats.cpp
[2/5] /usr/bin/clang++ -Dstation_EXPORTS ... -c .../report.cpp
[3/5] /usr/bin/clang++ -I... -std=gnu++23 -MD ... -c .../main.cpp
[4/5] : && /usr/bin/clang++ -fPIC -Xlinker --dependency-file=CMakeFiles/station.dir/link.d -shared -Wl,-soname,libstation.so -o libstation.so CMakeFiles/station.dir/stats.cpp.o CMakeFiles/station.dir/report.cpp.o && :
[5/5] : && /usr/bin/clang++ -Xlinker --dependency-file=CMakeFiles/rooster.dir/link.d CMakeFiles/rooster.dir/main.cpp.o -o rooster -Wl,-rpath,.../out-linux-clang/shared: libstation.so && :
```

(Shortened again, and the order of steps 1 to 3 can differ from run to
run.) Look at what CMake typed for you, and compare with 7.14:

- The library files are compiled with **`-Dstation_EXPORTS`**, the macro
  that `generate_export_header` looks for. It is the
  `-DSTATION_BUILD_DLL` you typed in 7.14.
- They are also compiled with **`-fPIC`**, and with
  **`-fvisibility=hidden`**, the two flags of 7.14. CMake added `-fPIC`
  by itself, because a shared library needs it.
- Step 4 is a **`-shared`** link that makes `libstation.so`, with
  `-Wl,-soname,libstation.so` giving it its run-time name.
- Step 5 links the program against `libstation.so`, and look at
  **`-Wl,-rpath,.../out-linux-clang/shared:`**. CMake **baked the build
  folder into the program**, the same idea as the `-Wl,-rpath,'$ORIGIN'`
  you typed in 7.14, but with an absolute path.

```sh
ls -l out-linux-clang/shared/libstation.so out-linux-clang/shared/rooster
./out-linux-clang/shared/rooster
readelf -d out-linux-clang/shared/rooster | grep -E 'NEEDED.*station|RUNPATH'
ldd out-linux-clang/shared/rooster | grep station
```

```
-rwxr-xr-x 1 root root 305992 Oct 14 16:38 out-linux-clang/shared/libstation.so
-rwxr-xr-x 1 root root 277672 Oct 14 16:38 out-linux-clang/shared/rooster
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
 0x0000000000000001 (NEEDED)             Shared library: [libstation.so]
 0x000000000000001d (RUNPATH)            Library runpath: [/workspace/07.PracticalBuiltInFeatures/7.15ProjectCMakeCommandLine/out-linux-clang/shared:]
	libstation.so => /workspace/07.PracticalBuiltInFeatures/7.15ProjectCMakeCommandLine/out-linux-clang/shared/libstation.so (0x00007f775da6d000)
```

The program starts **without** `LD_LIBRARY_PATH`, and `ldd` finds the
library, thanks to the `RUNPATH` that CMake wrote into it. (The address
in brackets differs on every run, and the date in the `ls` lines will be
yours.) One option, and 7.13 turned into 7.14, with no source changes.

#### 6. Install

```sh
cmake --install out-linux-clang/static --prefix out-linux-clang/install
find out-linux-clang/install -type f
./out-linux-clang/install/bin/rooster
```

```
-- Install configuration: ""
-- Installing: .../out-linux-clang/install/bin/rooster
-- Installing: .../out-linux-clang/install/lib/libstation.a
-- Installing: .../out-linux-clang/install/include/stats.h
-- Installing: .../out-linux-clang/install/include/report.h
-- Installing: .../out-linux-clang/install/include/station_export.h
out-linux-clang/install/bin/rooster
out-linux-clang/install/lib/libstation.a
out-linux-clang/install/include/stats.h
out-linux-clang/install/include/report.h
out-linux-clang/install/include/station_export.h
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(The order of the `find` lines can differ.) `--install` copies the
**finished products** to a clean folder, as the `install(...)` lines in
`CMakeLists.txt` say. `--prefix` names the folder. That is the **layout
you hand to someone else**: the program in `bin`, the library in `lib`,
the headers in `include`. (`Install configuration: ""` is the empty
build type from step 1.)

Now install the **dynamic** build, and run the installed program:

```sh
cmake --install out-linux-clang/shared --prefix out-linux-clang/install-shared
./out-linux-clang/install-shared/bin/rooster
echo $?
```

```
-- Install configuration: ""
-- Installing: .../out-linux-clang/install-shared/bin/rooster
-- Set non-toolchain portion of runtime path of ".../out-linux-clang/install-shared/bin/rooster" to ""
-- Installing: .../out-linux-clang/install-shared/lib/libstation.so
-- Installing: .../out-linux-clang/install-shared/include/stats.h
-- Installing: .../out-linux-clang/install-shared/include/report.h
-- Installing: .../out-linux-clang/install-shared/include/station_export.h
./out-linux-clang/install-shared/bin/rooster: error while loading shared libraries: libstation.so: cannot open shared object file: No such file or directory
127
```

It **fails**, with the error you know from 7.14. Look at the line
`Set non-toolchain portion of runtime path ... to ""`: when it installs
a program, CMake **removes the build-folder path** from its `RUNPATH`,
because the build folder is not meant to be there when you hand the
program to someone. Now the loader has no idea where `libstation.so` is.
You know two fixes from 7.14. The first is to tell the loader for one
run:

```sh
LD_LIBRARY_PATH=out-linux-clang/install-shared/lib ./out-linux-clang/install-shared/bin/rooster
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

The second is to ask CMake to write a **relative** path, for the
installed program, with one more cache variable. `$ORIGIN` is "the
folder the program is in", so `$ORIGIN/../lib` is the `lib` folder next
to `bin`. Configure the dynamic folder again with it, and install again:

```sh
cmake -S . -B out-linux-clang/shared -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=ON '-DCMAKE_INSTALL_RPATH=$ORIGIN/../lib'
cmake --build out-linux-clang/shared
cmake --install out-linux-clang/shared --prefix out-linux-clang/install-shared
readelf -d out-linux-clang/install-shared/bin/rooster | grep RUNPATH
./out-linux-clang/install-shared/bin/rooster
```

```
 0x000000000000001d (RUNPATH)            Library runpath: [$ORIGIN/../lib]
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

(Quote the `$ORIGIN` so your shell does not eat it. The `-- Installing:`
lines are left out.) The installed program now finds its library
wherever you put the `install-shared` folder. On Windows none of this
was needed: the DLL goes in `bin`, next to the program.

#### 7. Break it on purpose

**a. A folder without `CMakeLists.txt`.** Point `-S` at the wrong
folder:

```sh
cmake -S out-linux-clang -B out-linux-clang/oops -G Ninja
```

```
CMake Error: The source directory ".../out-linux-clang" does not appear to contain CMakeLists.txt.
Specify --help for usage, or press the help button on the CMake GUI.
```

`-S` must name the folder that **contains** `CMakeLists.txt`.

**b. A target that does not exist.** A typo in `--target`:

```sh
cmake --build out-linux-clang/static --target stationn
```

```
ninja: error: unknown target 'stationn', did you mean 'station'?
```

That message comes from Ninja, which knows the list of targets from
`build.ninja`.

**c. Build a folder that was never configured.**

```sh
cmake --build out-linux-clang/nothere
```

```
Error: .../out-linux-clang/nothere is not a directory
```

You have to **configure** (`-S ... -B ...`) before you can **build**.

**d. Another generator in a folder that already has one.** The cache
remembers the generator:

```sh
cmake -S . -B out-linux-clang/static -G "Unix Makefiles"
```

```
CMake Error: Error: generator : Unix Makefiles
Does not match the generator used previously: Ninja
Either remove the CMakeCache.txt file and CMakeFiles directory or choose a different binary directory.
```

One build folder, one generator. CMake offers two ways out: delete the
folder or pick another. That is why every variant in this project,
`static`, `release`, `shared`, has **its own folder**. (Changing the
compiler of an existing folder is a related trap: CMake warns, throws
the cache away, and starts again. The Clang image has no other compiler
to show it with, but the MinGW and GCC walk-throughs do.)

That is Linux Clang done.

---

### Options you will use all the time

- **`-S <dir>`** and **`-B <dir>`**: the source folder and the build
  folder.
- **`-G Ninja`**: which generator to use.
- **`-D<NAME>=<value>`**: set a cache variable.
- **`-DCMAKE_CXX_COMPILER=<c++>`**: pick the compiler, once per build
  folder.
- **`-DCMAKE_BUILD_TYPE=Release`**: an optimised build (Ninja builds one
  type per folder).
- **`-DBUILD_SHARED_LIBS=ON`**: `add_library` without a keyword makes a
  `.dll` or `.so`.
- **`cmake --build <dir>`**: build everything that changed.
- **`--target <name>`**: build one target only.
- **`--verbose`**: print the real compiler commands.
- **`cmake --install <dir> --prefix <dir>`**: copy the finished products
  out.

> **Gotcha: the build type.** With Ninja, each build folder is **one**
> build type, chosen at configure time. On MSVC, if you do not pass
> `-DCMAKE_BUILD_TYPE`, you get `Debug` (`/Od /RTC1 -MDd`, and the
> install output says `Install configuration: "Debug"`). On MinGW and
> Linux you get **no** build type at all: no optimisation and no debug
> information. Pass `-DCMAKE_BUILD_TYPE=Release` and the optimisation
> flags appear in the verbose output (`/O2 /DNDEBUG` or `-O3 -DNDEBUG`).

### What to take away from the four projects

```
   source ──► compiler ──► object ──► archiver ──► static library ─┐
                              │                                      ├──► linker ──► program
                              └──► linker ──► dynamic library ──────┘     (+ the DLL / .so at run time)

   CMake writes all of these commands. You read them with --verbose.
```

When something fails to build, you now know which stage it came from:
**compiler** errors come with a line of your code, **linker** errors
(`undefined reference`, `LNK2019`) are about missing or mismatched
names, and **run-time** loading errors
(`cannot open shared object file`, a missing DLL) are about where the
loader looks.


