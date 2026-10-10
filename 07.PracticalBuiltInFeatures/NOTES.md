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
with regular expressions. The chapter closes with four hands-on projects
that take the lid off the build: calling the compiler and linker yourself,
making static and dynamic libraries, and driving CMake from the command line.

---

## 7.2 `std::array` and range-based for loops

In this lecture, we are zooming in on **`std::array`**, the fixed-size container, 
and taking the chance to introduce **range-based `for`** loops. These allow you to iterate over the elements of a collection without needing to manage an index variable explicitly.

**`std::array<T, N>`** is a **fixed-size** sequence of `N` values of type
`T`, stored **inline** - the elements sit directly inside the `array`
object, back to back. `N` is part of the type: `std::array<int, 5>` and `std::array<int, 10>` are different types, the same way `int` and `double` 
are different types.

```cpp
std::array<int, 6> roll_tally{};   // {} zero-initializes every element
```

```
   std::array<int, 6> roll_tally{};

   index:      0     1     2     3     4     5
             ┌─────┬─────┬─────┬─────┬─────┬─────┐
   roll_tally│  0  │  0  │  0  │  0  │  0  │  0  │   one block, 6 ints,
             └─────┴─────┴─────┴─────┴─────┴─────┘ 
                ▲                             ▲
         roll_tally[0]                     roll_tally[5]
          (count of 1s)                     (count of 6s)
                      size() == 6, fixed forever
```

### Filling it in from real data

Assume someone rolled a die ten times and wrote down the results. We want to count how many times each face showed up.

```cpp
// 10 die rolls, each face 1..6
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
**arguments** filled in (`T` and `N`) before it becomes a real 
type (The same concepsts we saw for function templates extended to custom types). 
CTAD is the compiler's ability to **deduce** those arguments on its own,
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

Stating `int number` means "give me a **copy** of each element, one by one, and 
I will use it in the loop body." Stating `int& number` means "give me a **writable alias** to each element, one by one, and I will use it in the loop body."

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
members). `const T&` is the habit that pays off once `T` stops being tiny.

### The C++20 `for (init; element : range)` form

Since C++20, a range-based for can start with an optional **init statement**, 
followed by the usual `element : range` part. There is no
condition: the loop simply ends when the range runs out of elements.

```
   for ( int total{0};   int number : lucky_numbers )
         └────┬──────┘   └──────────┬─────────────┘
         init statement,           the usual range-based
         runs once, before         part: one element per
         the first iteration       iteration
```

Here the init statement declares an accumulator, and `number` is still
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

We explore how all this applies to the case when the parameter is a **collection** 
instead of a single `int` or `double`.

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

- `std::array`'s size is baked into its type
- `std::vector` is the default choice whenever you do not know the count 
   up front, or need to add to it later.

```
   std::array<int, 5>                    std::vector<int>
   ───────────────────                   ────────────────
   size fixed at compile time            size can change at run time
   elements stored inline                elements stored on the heap
   N is part of the type                 no size in the type at all
   cannot grow                           push_back() grows it
```

### Growing from nothing: `push_back`

You can create an empty vector and add elements one at a time with `push_back`:

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

`std::array` can't do this. Its size is fixed at compile time, 
while `push_back` grows a `vector` on demand, at run time.

### `(N)` vs. `{N}` - Don't fall for this!

This can be confusing. Watch out!

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

Parentheses `()` size the vector; braces `{}` list its elements. 

### Comparing, copying, assigning

Vectors can be compared, copied, and assigned.

```cpp
std::vector<int> storefront_stock(5);   // 5 elements, each 0 
std::vector<int> backroom_stock(8);     // 8 elements, each 0 
```

```
   storefront_stock: ┌───┬───┬───┬───┬───┐
                     │ 0 │ 0 │ 0 │ 0 │ 0 │                       5 elements
                     └───┴───┴───┴───┴───┘

   backroom_stock:   ┌───┬───┬───┬───┬───┬───┬───┬───┐
                     │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │           8 elements
                     └───┴───┴───┴───┴───┴───┴───┴───┘
```

### Comparing: `==` and `!=`

Two vectors are equal only if they have the same size **and** the same
value at every position. Here every value is `0`, but the sizes differ
(5 vs. 8), so they are not equal:

```cpp
if (storefront_stock != backroom_stock) {
    std::println("storefront_stock and backroom_stock are not equal");
}
```

### Copying: the copy constructor

To create a **new** vector that starts out as a copy of an existing one,
pass the existing vector when you declare the new one:

```cpp
std::vector overflow_stock{backroom_stock};   // a new vector<int>, copied from backroom_stock
```

The element type (`int`) is deduced from `backroom_stock`. Braces usually
list elements, but when the only thing inside is another vector of the
same type, you get a **copy** of it, not a vector that contains a vector.

```
   backroom_stock: ┌───┬───┬───┬───┬───┬───┬───┬───┐
                   │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │     the original, its own block of memory
                   └───┴───┴───┴───┴───┴───┴───┴───┘

   overflow_stock: ┌───┬───┬───┬───┬───┬───┬───┬───┐
                   │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │     a SEPARATE block, overflow_stock's own copy
                   └───┴───┴───┴───┴───┴───┴───┴───┘

   changing backroom_stock later does NOT touch overflow_stock, and vice versa
```

### Assigning: `=`

Assignment works on a vector that **already exists**. Its old contents
are thrown away and replaced by a copy of the right-hand side, **including the size**:

```cpp
storefront_stock = backroom_stock;   // storefront_stock now holds a copy of backroom_stock
```

```
   BEFORE:  storefront_stock: ┌───┬───┬───┬───┬───┐
                              │ 0 │ 0 │ 0 │ 0 │ 0 │                     5 elements
                              └───┴───┴───┴───┴───┘

   AFTER:   storefront_stock: ┌───┬───┬───┬───┬───┬───┬───┬───┐
                              │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │ 0 │         8 elements, a copy
                              └───┴───┴───┴───┴───┴───┴───┴───┘         of backroom_stock
```

`storefront_stock == backroom_stock` is now `true`. From this point on,
`storefront_stock` has **8** elements.

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
catch (const std::exception& ex) {
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

std::ranges::binary_search(fruits, "kiwi"s);   // true
std::ranges::binary_search(fruits, "guava"s);  // false
```

`"kiwi"` is in `fruits`, so the first call gives `true`. `"guava"` is not,
so the second gives `false`.

So **binary search** does the work faster than a linear scan, 
but it has a **precondition**: the data must be sorted in the order the search expects.

#### What goes wrong if the data is not sorted the right way

Notice the comment in the code above: right before this point, `fruits`
was left sorted by **length**, longest first, by the last lambda
comparator. That is sorted, but not by the rule `binary_search` assumes
(alphabetical, ascending). Here is what would happen if we searched it
as it was, looking for `"fig"`, which really is in there:

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

In this lecture, we are expxloring C++20's **ranges library**
two more declarative building features: **filter** (keep only what matches)
and **transform** (map each value to a new one). 

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

`std::views::filter` and `std::views::transform` wrap a range the same way, and chain 
together with `|`, read left to right like a pipeline. Like `accumulate`'s fourth argument, 
each one is a **higher-order function**: `filter` takes a lambda that decides *keep or drop*,
`transform` takes a lambda that decides *how the old value turns into the new value* - you
supply the small decision, the view supplies the iteration.

```cpp
auto even_squares{
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
   auto even_squares{ counted | filter(...) | transform(...) };
        │
        └─  at THIS line: nothing has been filtered, nothing squared -
            evenSquares is just a recipe wrapping counted

   for (int x : evenSquares) { ... }
        │
        └─  NOW, one element at a time, as the loop asks for the next
            value: pull from counted → test filter → apply transform
```

`even_squares` is only ever iterated by something that asks for values -
a range-based for, `std::accumulate`, or copying it into a `std::vector`. 
The same pipeline works over a real container, not just a generated sequence like `iota`.
Below is a use of this machinery on a `std::vector<int>` called `numbers`:

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
   idx:  0  1  2  3  4  5  6  7  8  9  10 ...                              23 24            ...

   log.find("is")     →  5     (first "is": "noon [is] 12pm...")
   log.rfind("is")    →  23    (last "is": "...midnight [is] not")
```

`find_first_not_of` works from the front, skipping every character that is
in the set you give it, and stops at the first one that is not:

```
   log.find_first_not_of("noon is ")      the set: n, o, i, s and the space

   idx:           0  1  2  3  4  5  6  7  8
   char:          n  o  o  n  ␣  i  s  ␣  1          (␣ = a space)
   in the set?    ✓  ✓  ✓  ✓  ✓  ✓  ✓  ✓  ✗
                                          ▲
                  skipped, skipped, ...   first character NOT in the set
                                          → returns 8
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
You saw it in 7.5, with `"mango"s` inside `std::array`. Here are the two
everyday cases, `auto` and `+`:

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

`std::print`/`std::println` already cover the everyday case. You build a
formatted result and send it straight to the console. **`std::format`**
does the same formatting work, but **returns a `std::string`** instead
of printing. This is useful when text is not going straight to the screen,
and intended to land in log files, part of a larger string, or a label built 
up piece by piece.

```cpp
   std::println("Hello, {}!", name);     // WRITES to stdout, returns nothing

   std::string s{std::format("Hello, {}!", name)};
                                          // BUILDS a std::string, prints nothing
                                          // - you decide what happens to it next
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

   field:  [ *   *   *   *   4   2   *   *   *   * ]
             └─────┬─────┘   └─┬─┘   └─────┬─────┘
               fill pad      value     fill pad
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
std::string_view color_view{color};   // "sees" color's own characters
```

```
   std::string color{"red"};              (owns its own character buffer)

   color: ┌───┬───┬───┐
          │ r │ e │ d │
          └───┴───┴───┘
            ▲
            │
   std::string_view color_view{color};

   color_view:  { pointer , length: 3 }
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
   color_view still points HERE  →  color_view now reads "Red"

   compare with std::string color_copy{color}; (a REAL copy, made earlier):
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

   "Red" itself is never touched - only color_view's own (pointer, length)
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

In this lecture, we explore the `<chrono>` library, which provides a comprehensive set of tools for handling time in C++. Time is a fundamental aspect of programming, appearing in various contexts such as measuring operation durations, logging timestamps, and managing dates.

**`<chrono>`** is the standard library's time toolkit, and this lecture
covers the three pieces of it you're actually likely to reach for:

```
   DURATIONS    an amount of time            ("90 minutes and 32 seconds")
   CLOCKS       a source of "now"            (steady_clock, system_clock, ...)
   DATES        a point on the calendar,     (year_month_day, since C++20)
                not a moment on the clock
```

Everything lives in `<chrono>`, namespace `std::chrono`. Underneath sits
`<ratio>` - the compile-time fraction type chrono uses to describe exactly
how long "one tick" is, for every duration type, with zero runtime cost.

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
// A quarter
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
`ratio` built from ordinary (non-const) variables is a compile error.
One can use constants initialized from literals, but not ordinary variables:

```cpp
intmax_t n{1}, d{4};
using bad = std::ratio<n, d>;         // Error: n, d are not compile-time constants

const intmax_t cn{1}, cd{4};
using ok = std::ratio<cn, cd>;        // Ok: const constants are usable
```

**Ratios are always normalized.** For `ratio<n, d>`, the library divides
out the greatest common divisor `gcd` of `n` and `d`:

```
   num = n / gcd
   den = d / gcd

   ratio<2, 8>   and   ratio<1, 4>   →  the exact same TYPE after normalization
```

We can prove this with `ratio_equal`, one of the compile-time comparison templates:

```cpp
// Two different SPELLINGS, but the exact same type after normalization.
std::println("ratio<2,8> == ratio<1,4>: {}",
              std::ratio_equal<std::ratio<2, 8>, std::ratio<1, 4>>::value);
// "ratio<2,8> == ratio<1,4>: true"
```

**Naming a ratio with `using`, as soon as you plan to reuse it.** A type
alias changes nothing about how the ratio behaves - it is just a shorter
name for the exact same type. We introduce two aliases so we can lean on
short names instead of the full `std::ratio<1, 4>` spelling wherever it's
convenient:

```cpp
// Two named ratios, and their sum computed through the aliases.
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

The examples below deliberately go back to the full spelling here
(rather than reusing `quarter_hour`/`third_hour`) so you see both styles
side by side - use whichever reads better at the call site. 

```cpp
// Addition: a quarter of an hour + a third of an hour.
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
// Subtraction: a half of an hour - a quarter of an hour.
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
// Multiplication: a quarter of an hour, times two-thirds.
using product_type = std::ratio_multiply<std::ratio<1, 4>, std::ratio<2, 3>>::type;
std::println("1/4 * 2/3 = {}/{}", product_type::num, product_type::den);
```

```
   1/4 * 2/3  =  (1*2) / (4*3)  =  2/12

   2/12, reduced by gcd(2,12)=2, is 1/6   ──►  ratio_multiply<...>::type
                                                 is the NORMALIZED type ratio<1, 6>
```

```cpp
// Division: a half, divided by a quarter.
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
values. Read the answer off the result's `::value` member:

```cpp
// Comparing 1/3 against 1/4 - and 1/4 against itself.
std::println("1/3 <  1/4 : {}", (std::ratio_less<std::ratio<1, 3>, std::ratio<1, 4>>::value));
std::println("1/3 >  1/4 : {}", (std::ratio_greater<std::ratio<1, 3>, std::ratio<1, 4>>::value));
std::println("1/4 <= 1/4 : {}", (std::ratio_less_equal<std::ratio<1, 4>, std::ratio<1, 4>>::value));
// false, true, true 
```

Because a ratio is a type, you cannot `println("{}", some_ratio)` directly
- you always extract `::num`/`::den` (or, for comparisons, `::value`)
first, exactly as every example above does.

**SI ratio aliases the library ships for convenience** - `milli`,
`micro`, `nano`, `kilo`, `mega`, and more, all the way from `yocto`
(`10^-24`) to `yotta` (`10^24`):

```cpp
std::println("milli = {}/{}", std::milli::num, std::milli::den);   // "milli = 1/1000"
std::println("kilo  = {}/{}", std::kilo::num, std::kilo::den);     // "kilo  = 1000/1"
```

`chrono` uses exactly these to define its predefined duration types
(`milliseconds` is a duration ticking in `milli`-second units) 

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


```cpp
#include <chrono>
#include <print>

int main() {
    using namespace std::chrono; // This works too.

    auto race_duration{90min + 32s};     // literals work
    minutes warmup{15};                  // no std::chrono:: needed
    std::println("{}", race_duration);   // 5432s
    std::println("{}", warmup);          // 15min

    return 0;
}
```

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
per tick). A second is the baselin ehere. Once you know that, you can build your own:

```cpp
template <class Rep, class Period = std::ratio<1>>       // If you don't specify the ratio, 
                                                         // it defaults to 1, meaning one tick = one second
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
std::chrono::duration<long, std::ratio<1, 1000>> d1_ms{250};
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

There are two different questions you ask about time in everyday life: 

- "what time is it right now?" and 
- "how long did that just take?".

Those are two different jobs - one wants a wall-clock reading you'd
show a person, the other wants an elapsed amount of time you'd measure with
a stopwatch. C++ gives you a different **clock** for each job.

**Asking "what time is it right now?"** - `std::chrono::system_clock` is
that clock. Its `now()` returns the current `time_point`, and
`std::println`/`std::format` understand a `time_point` directly, using the
same `{:...}` spec grammar from earlier - `%` codes replace a type letter like
`f` or `d`:

```cpp
auto now_utc{std::chrono::system_clock::now()};
std::println("UTC: {:%Y-%m-%d %H:%M:%S}", now_utc);
```

**Note:**`system_clock::now()` is always UTC, never your local time. 
Printing it directly, no matter how you format
it, still shows the UTC hour - a student in Nairobi (UTC+3) or New York
(UTC-5) will not see their own wall-clock time from this alone. 

To get that, convert the UTC `time_point` to a specific **time zone**:
`current_zone()` asks the OS which zone it's configured for, and
`to_local()` converts a UTC `time_point` to that zone's wall-clock time:

```cpp
auto now_local{std::chrono::current_zone()->to_local(now_utc)};
std::println("Local: {:%Y-%m-%d %H:%M:%S}", now_local);
```

> **A note on the Docker student environments.** As of Clang 21, libc++
> does not yet implement the IANA time zone database, so `current_zone()`
> will fail to compile there. This works on MSVC and on GCC's libstdc++,
> which is what we build with. You can try compiler explorer with a compiler
> that supports it.

**Locale** is a separate thing compared to time zone: it changes how a time is
written, not which instant or zone is being shown. Setting a locale
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

   TIME ZONE  answers "in which time zone should I show the time for?"
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

The last one is brutal on purpose!  Please note that none of the rules above 
don't name a specific password. They describe a *pattern* the text must aggree with.
That's exactly what a **regular expression** is. A set of rules that the text mush **agree with**. 
To the letter! The C++ Standard Library ships a `<regex>` header that implements most of 
what we need in that regard.

`<regex>` gives you four things to do with a pattern:

```
   MATCH     does this WHOLE string fit the pattern?      regex_match
   SEARCH    is the pattern found ANYWHERE inside it?      regex_search
   WALK      find EVERY match, one at a time                sregex_iterator /
                                                              sregex_token_iterator
   REPLACE   rewrite every match in a copy of the string   regex_replace
```

We will explore all these bit by bit. But before we start, let's look at the basic 
building blocks of a regex pattern. The table below shows some of the most common pieces:

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
| `\|`            | **alternation** - "or": matches what's on its left *or* what's on its right (`cat\|dog`). To match a literal pipe, put a backslash in front of it (see `regex_replace` below) |
| `+`            | one or more of the preceding piece |
| `*`            | zero or more of the preceding piece |
| `{n}`          | exactly `n` occurrences        |
| `{n,}`         | `n` or more occurrences        |
| `{n,m}`        | between `n` and `m`, inclusive |

### Metacharacters vs. escape sequences: two different `\`'s

Every backslash piece in the table above (`\d`, `\w`, `\s`) is a
**metacharacter** - the *regex engine's own* shorthand for a whole
category of characters. `\d` doesn't mean "a digit" the way a letter
means itself; it's special syntax the regex engine interprets. How are
these different from escape sequences like `\t`, `\n`, and `\r`? 

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
             ▲  └────┬─────────┘
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

### `main2_searching.cpp` - `regex_search`: find a match anywhere, and find them all

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
                    ▲                                                ▲
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

This begin/`!=`/`++`/`*` machinery is done for us internally if we use 
a range-based `for` loop. This is the same mechanism that `std::sregex_iterator` 
uses to walk the matches of a regex against a string as we are about to see.

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
> This is why `item` above is a named variable declared *before* the
> loop, not `std::sregex_iterator{shopping_list.cbegin(), shopping_list.cend(),
> std::regex{R"([\w]+)"}}` inline.

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

### `main4_replacing.cpp` - `regex_replace`: build a new string from an old one

The tools so far only *read* text: does it match? (`regex_match`), is the
pattern in there (`regex_search`), where are all the matches (theiterators). 

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
             step 2    step 1  step 2    step 3
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

That is the whole machine. Only **two inputs** can change what it
produces:

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

Up to now you have pressed a Run button, or typed `cmake --build`, and a program appeared. In this project we take the lid off. You will call the **compiler and the linker yourself**, on the command line, and then open the files they produce to see what is really inside.

We do it for a reason. Sooner or later a build fails with a message like `undefined reference to ...` or `unresolved external symbol ...`. Those messages come from the **linker**, not the compiler, and they only make sense once you have seen what the linker is given.

The program is a small **weather station** report, in the same spirit as the chapter assignment. It reads a list of Fahrenheit readings, summarises them, and prints one line in Celsius.

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

The code is in `7.12ProjectManualCompile`. It has two forms: `single.cpp` (one file, nothing else) and three files that work together (`main.cpp`, `stats.cpp`, `report.cpp`, with their headers).

### What happens between source and program

```
   main.cpp ──┐                            ┌── compiler ──► main.o  ──┐
   stats.cpp ─┼── each .cpp on its own ────┼── compiler ──► stats.o ──┼──► linker ──► weather
   report.cpp ┘                            └── compiler ──► report.o ─┘
                                                   (object files)
```

- The **compiler** turns **one `.cpp` file at a time** into an **object file**: machine code for that file, plus a list of names. Each file is compiled in complete ignorance of the others. That is why a header only *declares* `to_celsius` and the compiler is happy to trust it.
- The **linker** takes all the object files, matches every "I need `to_celsius`" with the object that defines it, and writes the final program.

Everything in this project is a variation on those two steps.

### The five environments

You can follow along in whichever of these you have. The commands change a little, the ideas do not.

| Environment | Compiler driver | Linker | Object files |
|---|---|---|---|
| Windows, MSVC | `cl` | `link` | `.obj` |
| Windows, MinGW GCC | `g++` | `ld` (called by `g++`) | `.o` |
| Windows, MinGW Clang | `clang++` | `ld` (called by `clang++`) | `.o` |
| Linux, GCC | `g++` | `ld` (called by `g++`) | `.o` |
| Linux, Clang | `clang++` | `ld` (called by `clang++`) | `.o` |

How to get a shell for each one:

- **MSVC**: open **Developer PowerShell for VS** from the Start menu. That is an ordinary PowerShell with `cl`, `link`, `lib` and `dumpbin` on the PATH. You can also load it by hand from any PowerShell: `& "<your VS folder>\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64 -HostArch amd64`.
- **MinGW**: a normal PowerShell with `C:\mingw64\bin` on the PATH. Check with `g++ --version` and `clang++ --version`.
- **Linux**: the Docker containers from chapter 2. From the repository root, `docker run -it --rm -v "${PWD}:/workspace" cpp-masterclass-gcc` (or `cpp-masterclass-clang`), then `cd 07.PracticalBuiltInFeatures/7.12ProjectManualCompile`.

Every folder in this project also has one script per environment (`build-msvc.ps1`, `build-mingw-gcc.ps1`, `build-mingw-clang.ps1`, `build-linux-gcc.sh`, `build-linux-clang.sh`) that runs the commands below from top to bottom. Type the commands yourself first, and use the scripts to check your work.

### Part 1: one file, two ways

`single.cpp` is small enough to hold in your head: sum a vector, print the average.

```cpp
const std::vector<double> readings{68.0, 72.5, 59.0, 81.0, 90.5, 55.0, 77.0, 64.5};
const double total{std::accumulate(readings.begin(), readings.end(), 0.0)};
std::println("average: {:.1f} F", total / static_cast<double>(readings.size()));
```

**Way 1: two steps.** Compile to an object file, then link it.

```
   single.cpp ──► compile ──► single.obj / single.o ──► link ──► single_two_step
```

#### MSVC

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c single.cpp
link /nologo single.obj /OUT:single_two_step.exe
```

- `/c` means **compile only, do not link**. That is what produces `single.obj`.
- `/std:c++latest` selects the newest language mode. Do **not** write `/std:c++23`: with this compiler `cl` ignores it, and `<print>` breaks.
- `/EHsc` turns on normal C++ exception handling. `/W4` asks for more warnings.
- `/MD` picks the **shared C runtime**. We will care about this in 7.13. CMake uses it by default, so we use it too.

#### MinGW GCC

```powershell
g++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
g++ single.o -o single_two_step.exe -lstdc++exp
```

#### MinGW Clang

```powershell
clang++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
clang++ single.o -o single_two_step.exe -lstdc++exp
```

#### Linux, GCC

```sh
g++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
g++ single.o -o single_two_step
```

#### Linux, Clang

```sh
clang++ -std=c++23 -Wall -Wextra -c single.cpp -o single.o
clang++ single.o -o single_two_step
```

`-c` is the same idea as `/c`: compile, stop before linking. `-o` names the output file. The second command has no source file at all: the "compiler" is being used as a **front end for the linker**.

> **Gotcha, MinGW only: `-lstdc++exp`.** On the MinGW GCC 14 and Clang 19 we use on Windows, `std::println` needs one extra library. Leave it out and the link fails with:
>
> ```
> undefined reference to `std::__open_terminal(_iobuf*)'
> undefined reference to `std::__write_to_terminal(void*, std::span<char, ...>)'
> ```
>
> `-lstdc++exp` ("the experimental part of the C++ library") has to come **after** the objects that need it. Newer compilers, like the GCC 16 and Clang 21 in our Linux containers, do not need it. Notice how the message is about **missing names**, not about syntax: your code compiled fine. This is a linker error.

**Way 2: one step.** Hand the source file straight to the driver and let it run both steps.

```powershell
# MSVC
cl /nologo /std:c++latest /EHsc /MD /W4 single.cpp /Fe:single_one_step.exe

# MinGW GCC or Clang (Windows)
g++ -std=c++23 -Wall -Wextra single.cpp -o single_one_step.exe -lstdc++exp

# Linux
g++ -std=c++23 -Wall -Wextra single.cpp -o single_one_step
```

Compare the two programs. On our machine both executables had **exactly the same size**. That is the point: `cl`, `g++` and `clang++` are **drivers**. They are not one program that does everything: they run the compiler, then the linker, and pass your options along. The one-step form just skips saving the object file.

> **The size surprise.** On our machine `single.obj` was about 800 KB, bigger than the 310 KB executable built from it (MSVC), and `single.o` was about 700 KB against a 510 KB program (MinGW GCC). Two lines of `std::println` and `std::accumulate` pull in a lot of templates, and the object file keeps a copy of every template instantiation the file used, plus the bookkeeping the linker needs. The linker then keeps only what the program actually uses. Your numbers will differ. The lesson is that an object file is **not a small program**, it is a half-finished one.

### Part 2: three files, three objects, one link

Now the real program. Look at how the work is divided:

```
   stats.h / stats.cpp     summarize(readings) and to_celsius(f)
   report.h / report.cpp   format_report(sensor, summary), which CALLS to_celsius
   main.cpp                builds the readings, calls both, prints
```

`report.cpp` calls `to_celsius`, which lives in `stats.cpp`. When the compiler builds `report.cpp` it only sees the declaration in `stats.h`. It cannot know where the function is, so it leaves a note in the object file that says "**I need `to_celsius`, fill it in later**".

Compile each `.cpp` on its own, then link all three objects together.

#### MSVC

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c stats.cpp
cl /nologo /std:c++latest /EHsc /MD /W4 /c report.cpp
cl /nologo /std:c++latest /EHsc /MD /W4 /c main.cpp
link /nologo main.obj stats.obj report.obj /OUT:weather.exe
.\weather.exe
```

#### MinGW GCC (swap `g++` for `clang++` to use Clang)

```powershell
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
g++ main.o stats.o report.o -o weather.exe -lstdc++exp
.\weather.exe
```

#### Linux (swap `g++` for `clang++` to use Clang)

```sh
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o
g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
g++ main.o stats.o report.o -o weather
./weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

The same line comes out on all five environments.

**Break it on purpose.** The best way to understand the linker is to starve it. Link again, this time **leaving out `stats.obj` (or `stats.o`)**:

```
link /nologo main.obj report.obj /OUT:broken.exe
```

```
main.obj : error LNK2019: unresolved external symbol "struct station::Summary __cdecl
    station::summarize(...)" (?summarize@station@@YA?AUSummary@1@...) referenced in function main
report.obj : error LNK2019: unresolved external symbol "double __cdecl
    station::to_celsius(double)" (?to_celsius@station@@YANN@Z) referenced in function ...
broken.exe : fatal error LNK1120: 2 unresolved externals
```

With GCC or Clang the same mistake reads:

```
main.o:main.cpp:(.text+0x68): undefined reference to `station::summarize(std::vector<double, ...> const&)'
report.o:report.cpp:(.text+0x35): undefined reference to `station::to_celsius(double)'
```

Read those messages with fresh eyes. Every `.cpp` compiled without complaint. The error is that two promises ("someone defines `summarize`", "someone defines `to_celsius`") were never kept. Whenever you see `LNK2019` or `undefined reference`, ask: **did I forget to compile or link the file that defines it?** The odd-looking text in parentheses, `?to_celsius@station@@YANN@Z`, is the next topic.

### Part 3: look inside the object files

An object file is a binary file with a **table of symbols**: names the file *defines* and names it *needs*. There are tools for reading that table, one set per platform.

| I want to... | MSVC | GCC / Clang (Windows and Linux) |
|---|---|---|
| see the file format | `dumpbin /headers stats.obj` | `objdump -f stats.o`, or `file stats.o` and `readelf -h stats.o` on Linux |
| list the symbols | `dumpbin /symbols stats.obj` | `nm stats.o` |
| turn a mangled name back into C++ | `undname <name>` | `nm -C stats.o`, or `c++filt <name>` |

A tiny program still contains **hundreds** of symbols from `std::vector`, `std::format` and friends, so filter for our own namespace, `station`.

#### On MSVC

```powershell
dumpbin /headers stats.obj | Select-String 'File Type|machine'
dumpbin /symbols stats.obj | Select-String station
dumpbin /symbols report.obj | Select-String to_celsius
```

```
File Type: COFF OBJECT
8664 machine (x64)

External | ?to_celsius@station@@YANN@Z (double __cdecl station::to_celsius(double))
External | ?summarize@station@@YA?AUSummary@1@AEBV?$vector@NV?$allocator@N@std@@@std@@@Z (struct station::Summary ...)

UNDEF    | ?to_celsius@station@@YANN@Z (double __cdecl station::to_celsius(double))     <- in report.obj
```

`dumpbin` prints the readable form in brackets next to the mangled one. Two things to see in this output:

- In `stats.obj`, `to_celsius` is **External** and has a section: this object *defines* it.
- In `report.obj`, the same name is **UNDEF**: "undefined here, the linker must find it". That is the note from Part 2, made visible. The linker's whole job is to **match every UNDEF with exactly one definition**.

#### On MinGW (Windows) and Linux

```powershell
nm stats.o | Select-String station          # on Linux: nm stats.o | grep station
nm -C stats.o | Select-String station
nm report.o | Select-String to_celsius
```

```
0000000000000000 T _ZN7station10to_celsiusEd
0000000000000038 T _ZN7station9summarizeERKSt6vectorIdSaIdEE
0000000000000000 T station::to_celsius(double)
0000000000000038 T station::summarize(std::vector<double, std::allocator<double> > const&)
                 U _ZN7station10to_celsiusEd
```

`nm` marks a symbol with a letter. **`T`** = defined, in the code ("text") section. **`U`** = undefined here. It is the same story as `External` and `UNDEF` above. `-C` ("demangle") prints the C++ name instead of the code.

### Name mangling

Now the odd names. You wrote `to_celsius`. The object file says `?to_celsius@station@@YANN@Z` (MSVC) or `_ZN7station10to_celsiusEd` (GCC and Clang). That is **name mangling**.

C++ allows two functions with the same name and different parameters (overloading, lecture 6.9). A linker only compares **plain names**, so the compiler has to put the **namespace, the name and the parameter types into the one name** it gives the linker.

Here is `to_celsius(double)` taken apart, in both styles.

**GCC and Clang** (the "Itanium" rules): `_ZN7station10to_celsiusEd`

| Piece | Meaning |
|---|---|
| `_Z` | "this is a C++ name" |
| `N` ... `E` | a **qualified** name, `namespace::function`, from `N` to `E` |
| `7station` | a name that is 7 letters long: `station` |
| `10to_celsius` | a name that is 10 letters long: `to_celsius` |
| `d` | the parameter type: `d` means `double` |

**MSVC**: `?to_celsius@station@@YANN@Z`

| Piece | Meaning |
|---|---|
| `?` | "this is a C++ name" |
| `to_celsius@` | the function name |
| `station@` and then `@` | the enclosing namespace, then the end of the qualification |
| `YA` | a free function (`Y`) using the `__cdecl` calling convention (`A`) |
| `N` | the return type: `double` |
| `N` | the parameter type: `double` |
| `@` then `Z` | end of the parameter list, end of the name |

Do not try to memorise these. The point is that **the parameter types are inside the name**. Two overloads, `to_celsius(double)` and `to_celsius(int)`, would get two different names and so can coexist in one program.

The two compilers use different rules, and that has a big consequence. Here is the whole picture of our five environments:

| Environment | Object file format | Mangling rules |
|---|---|---|
| Windows, MSVC | COFF (`.obj`) | MSVC: `?to_celsius@station@@YANN@Z` |
| Windows, MinGW GCC / Clang | COFF (`.o`) | Itanium: `_ZN7station10to_celsiusEd` |
| Linux, GCC / Clang | ELF (`.o`) | Itanium: `_ZN7station10to_celsiusEd` |

Check the format yourself: `objdump -f stats.o` on MinGW says `file format pe-x86-64`, and `file stats.o` on Linux says `ELF 64-bit LSB relocatable`.

Notice that **MSVC and MinGW both use COFF** (the Windows object format) but still cannot share objects: their **mangled names differ**, and so does the layout of `std::vector` and `std::string` inside. Compile `stats.cpp` with MSVC, compile the other two files with MinGW GCC and link them all with `g++`: you get the same `undefined reference to station::to_celsius(double)` as if `stats` were missing, because the names MinGW asks for do not exist in the MSVC object. **A C++ library is tied to the compiler and standard library that built it.** That is the **ABI** (application binary interface): the agreement about names, layouts and calling conventions that two pieces of binary code must share. In 7.14 you will see why it matters for libraries.

Now the cousin who is not mangled. In 8.12 we will write a function in assembly and call it from C++. The assembler will not mangle anything, so we will mark that function **`extern "C"`**, which tells the C++ compiler "use the plain name, as C does".

### Look inside the finished program

An executable is just another binary with a table of what it needs.

```powershell
dumpbin /headers weather.exe | Select-String 'machine|subsystem'     # MSVC
dumpbin /dependents weather.exe                                       # which DLLs it loads
```

```
8664 machine (x64)
3 subsystem (Windows CUI)         <- a console program
MSVCP140.dll  VCRUNTIME140.dll  KERNEL32.dll  api-ms-win-crt-*.dll
```

On Linux the same questions are `file weather` and `ldd weather`. We will come back to **dependents** in 7.14.

### Gotchas to take away

- `/std:c++latest`, never `/std:c++23`, with `cl`.
- MinGW needs `-lstdc++exp` for `std::println` and it must come **after** the objects.
- `LNK2019` / `undefined reference` means the **linker** could not find a definition: check you compiled and linked the file that has it.
- Objects from different compilers do not mix, even when both are `.obj` or `.o`.
- Compile every file with the **same standard and the same runtime option** (`/MD` everywhere). Mixing them is how LNK2038 appears, which we meet in 7.13.

---

## 7.13 Project: a static library

In 7.12 you linked three object files by hand. Imagine a program with three hundred. You would not pass three hundred names to the linker every time, and you would not want to hand your teammates a folder of loose `.o` files either. The answer is a **library**: a bundle of compiled code with a name.

There are two kinds. This lecture is the first one, the **static library**. The code is in `7.13ProjectStaticLibrary`. It is the same weather-station program as before, but now `stats.cpp` and `report.cpp` are bundled together and `main.cpp` is built against the bundle.

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

### Build the library

Compile the two library files exactly as in 7.12, then use the **archiver** to bundle them. This is where the toolchains differ most.

#### MSVC

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c stats.cpp
cl /nologo /std:c++latest /EHsc /MD /W4 /c report.cpp

lib /nologo /OUT:station.lib stats.obj report.obj
lib /nologo /LIST station.lib
```

The librarian is `lib`. Its `/LIST` option prints the members of an existing library:

```
stats.obj
report.obj
```

#### MinGW GCC or Clang (Windows)

```powershell
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o

ar rcs libstation.a stats.o report.o
ar t libstation.a
ar tv libstation.a
```

#### Linux, GCC or Clang

```sh
g++ -std=c++23 -Wall -Wextra -c stats.cpp -o stats.o
g++ -std=c++23 -Wall -Wextra -c report.cpp -o report.o

ar rcs libstation.a stats.o report.o
file libstation.a
ar t libstation.a
ar tv libstation.a
```

`ar` is the archiver, and its options come as a bundle of letters: **`r`** puts the files in, **`c`** creates the archive without a warning, **`s`** writes the symbol index that the linker will search. After it, `ar t` lists the members (`t` for table of contents) and `ar tv` adds sizes:

```
stats.o
report.o
rw-r--r-- 0/0  14576 Jan  1 00:00 1970 stats.o
rw-r--r-- 0/0 475632 Jan  1 00:00 1970 report.o
```

On Linux, `file libstation.a` answers `current ar archive`.

**Look inside.** The members are the object files you already know. Ask the symbol tools about the archive and you see the same `T` and `U` as before, now grouped by member:

```powershell
nm -C libstation.a | Select-String to_celsius      # MinGW; on Linux use grep
```

```
0000000000000000 T station::to_celsius(double)      <- defined in the stats.o member
                 U station::to_celsius(double)      <- needed by the report.o member
```

```powershell
dumpbin /symbols station.lib | Select-String to_celsius      # MSVC
```

The library is also **big**, because it holds the whole objects: `station.lib` is about 950 KB here, almost all of it `report`'s template code. Remember that number for 7.14.

### Link the program against the library

Compile `main.cpp` as usual. At the link step, name the library instead of the object files.

#### MSVC

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /c main.cpp
link /nologo main.obj station.lib /OUT:weather.exe
.\weather.exe
```

#### MinGW (Windows)

```powershell
g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
g++ main.o -L. -lstation -o weather.exe -lstdc++exp
.\weather.exe
```

#### Linux

```sh
g++ -std=c++23 -Wall -Wextra -c main.cpp -o main.o
g++ main.o -L. -lstation -o weather
./weather
```

```
sensor-12: low 12.8 C, high 32.5 C, average 21.6 C
```

Two shortcuts on the GCC and Clang side deserve an explanation:

- **`-lstation`** means "find a library called `station`". The tool adds the `lib` in front and the `.a` at the end for you, so it looks for `libstation.a`. **That is why the file is called `libstation.a`.** MSVC does not do this: you give it the real file name, `station.lib`.
- **`-L.`** means "also look in this folder". Without it, `-lstation` searches only the standard system folders and does not find the library sitting next to you.

### Two gotchas

**1. On GCC and Clang, order matters.** The linker reads its inputs **left to right**, and only pulls members out of an archive to satisfy names it **already needs**. Put the library first and nothing needs anything yet, so nothing is pulled out:

```sh
g++ -L. -lstation main.o -o broken
```

```
main.o: in function `main':
main.cpp:(.text+0x46): undefined reference to `station::summarize(std::vector<double, ...> const&)'
```

Same files, same flags, only the order changed, and the link fails. The rule is simple: **libraries go after the objects that use them.** (This is the same rule that applied to `-lstdc++exp` in 7.12.) MSVC's `link` does not care about the order.

**2. Compile everything with the same settings.** `/MD` means "use the shared C runtime". `/MT` means "copy the C runtime into this program". If the library and the program disagree, MSVC refuses to link:

```
stats_mt.obj : error LNK2038: mismatch detected for 'RuntimeLibrary':
    value 'MT_StaticRelease' doesn't match value 'MD_DynamicRelease' in main.obj
```

That is why every command in this project carries `/MD`. The same goes for the language standard, and for debug versus release builds. A static library is only a bundle of compiled code, so it takes on **whatever settings it was compiled with**.

### What a static library is good for

| | |
|---|---|
| Good | The finished program is self-contained: one file to ship, nothing to lose or mismatch at run time. |
| Good | Only the members the program needs are copied in. |
| Not so good | Every program that uses the library gets its **own copy** of the code. |
| Not so good | To fix a bug in the library you must **relink every program** that uses it. |

The second kind of library, in 7.14, trades those points the other way round.

---

## 7.14 Project: a dynamic library

A **dynamic library** (also called a **shared library**) is not copied into the program. It stays a separate file, and the program **finds it and loads it when it starts**. On Windows it is a **DLL**, on Linux a **`.so`** (shared object).

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

The code is in `7.14ProjectDynamicLibrary`. Same program, same functions. One new file appears, `station_api.h`, and a macro, `STATION_API`, in front of the three public functions.

### Why a macro in front of every function

A **Windows DLL exports nothing by default**. You mark each function you want the outside world to see. The marking is different on each side of the boundary:

- When the DLL itself is being compiled, the function is `__declspec(dllexport)`: "I provide this".
- When a program that uses the DLL is compiled, the same function is `__declspec(dllimport)`: "this lives in a DLL".

One header can serve both, with a macro, switched by a flag that only the library build passes:

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

On Linux every function is exported by default, which is not always what you want. Compiling with **`-fvisibility=hidden`** reverses that for your own code, so only the functions marked `STATION_API` are visible. That is the same "opt in" rule Windows has. (The standard library's templates stay visible either way, so the symbol list still has hundreds of `std::` names. We filter for `station`.)

### Build the library

#### MSVC

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /DSTATION_BUILD_DLL /LD stats.cpp report.cpp /Fe:station.dll
```

- `/LD` builds a **DLL** instead of an executable.
- `/DSTATION_BUILD_DLL` defines the macro, so `STATION_API` means `dllexport`.

Three files come out:

```
station.dll   the code (about 310 KB)
station.lib   an IMPORT library (about 3 KB)
station.exp   a by-product you can ignore
```

**`station.lib` here is not the static library from 7.13.** It has the same extension and a very different job. Last time `station.lib` was 950 KB because it held all the code. This one is 3 KB because it holds **only a list of names and the DLL they live in**. It is a signpost, and the linker uses it to learn "`to_celsius` is in `station.dll`".

#### MinGW GCC or Clang (Windows)

```powershell
g++ -std=c++23 -Wall -Wextra -DSTATION_BUILD_DLL -shared stats.cpp report.cpp -o station.dll '-Wl,--out-implib,libstation.dll.a'
```

`-shared` makes a DLL, and `-Wl,--out-implib,...` hands an option to the linker: also write the import library, `libstation.dll.a` (about 3 KB), the counterpart of MSVC's `station.lib`.

> **PowerShell gotcha.** The quotes around `-Wl,--out-implib,libstation.dll.a` matter. PowerShell reads a comma as "a list of values" and the command fails with *Missing argument in parameter list*. In `cmd` or on Linux you do not need the quotes.

#### Linux, GCC or Clang

```sh
g++ -std=c++23 -Wall -Wextra -fPIC -fvisibility=hidden -shared stats.cpp report.cpp -o libstation.so
```

- **`-shared`** makes a `.so`.
- **`-fPIC`** means "position-independent code". The library can be loaded at **any address**, and several programs may load it at different ones, so its code cannot assume where it lives.
- There is **no import library** on Linux. The `.so` itself serves both as the thing the linker reads and the thing the program loads.

### Look inside

```powershell
dumpbin /exports station.dll                       # MSVC
objdump -p station.dll | Select-String station     # MinGW
```

```sh
nm -D --defined-only libstation.so | grep station  # Linux
```

```
   ordinal hint RVA      name
         1    0 00001C40 ?format_report@station@@YA?AV?$basic_string@DU?$char_traits@D@std@@...
         2    1 00001040 ?summarize@station@@YA?AUSummary@1@AEBV?$vector@NV?$allocator@N@std@@@std@@@Z
         3    2 00001010 ?to_celsius@station@@YANN@Z
```

```
000000000001b809 T _ZN7station10to_celsiusEd
000000000001c1b1 T _ZN7station13format_reportB5cxx11ESt17basic_string_viewIcSt11char_traitsIcEERKNS_7SummaryE
000000000001b841 T _ZN7station9summarizeERKSt6vectorIdSaIdEE
```

**Three `station` entries**: the three functions we marked. On Windows that is the whole export table, and it is the **public face** of the DLL: the only names a program can reach. (On Linux the list also contains `std::` names, which is why we filtered with `grep station`.)

Look closely at the middle Linux name, `format_reportB5cxx11`. That `B5cxx11` is a **tag meaning "returns the C++11 flavour of `std::string`"**. GCC changed the layout of `std::string` in 2015, and the tag lets old and new code tell each other apart instead of crashing. This is the ABI from 7.12 showing up in a name.

### Link the program, and run it

The program is linked against the **signpost** (the import library on Windows, the `.so` itself on Linux).

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 main.cpp station.lib /Fe:weather.exe            # MSVC
g++ -std=c++23 -Wall -Wextra main.cpp -L. -lstation -o weather.exe -lstdc++exp          # MinGW
```

```sh
g++ -std=c++23 -Wall -Wextra main.cpp -L. -lstation -o weather                          # Linux
```

Ask the finished program what it needs when it **starts**:

```powershell
dumpbin /dependents weather.exe | Select-String 'station|MSVCP'        # MSVC
objdump -p weather.exe | Select-String 'DLL Name: (station|libstdc)'   # MinGW
```

```sh
readelf -d weather | grep NEEDED       # Linux
ldd weather | grep -E 'station|not found'
```

```
    station.dll
    MSVCP140.dll
```

```
 0x0000000000000001 (NEEDED)             Shared library: [libstation.so]
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 ...
	libstation.so => not found
```

`station.dll` is now on the program's **list of requirements**. It is not inside the program. This is the big difference from 7.13.

### The program cannot find its library

On **Linux** try running `./weather` straight away. It stops, and says exactly why:

```
./weather: error while loading shared libraries: libstation.so: cannot open shared object file: No such file or directory
```

The exit code is 127. The linker found `libstation.so` fine, because we passed `-L.`. But **`-L` is a link-time option**. At run time the system's **loader** searches its own list of folders, and the current folder is not on it. There are two common fixes:

```sh
LD_LIBRARY_PATH=. ./weather                          # tell the loader, for this one run
```

```sh
g++ ... main.cpp -L. -lstation -Wl,-rpath,'$ORIGIN' -o weather    # bake it into the program
```

`LD_LIBRARY_PATH` is a list of extra folders. `-rpath` stores the folder **inside the executable**, and `$ORIGIN` stands for "the folder this program is in". With either of them, the program runs and prints the familiar line. (Quote the `$ORIGIN` so your shell does not eat it.)

On **Windows** the rule is different. The loader looks **in the folder of the `.exe` first**, which is why `weather.exe` just worked when `station.dll` sat next to it. Now try it yourself: **rename `station.dll` to `station.dll.away` and run `.\weather.exe` again.** Windows refuses to start the program and shows an error saying that `station.dll` was not found. (Rename it back afterwards.) Other places Windows searches include the folders on your **PATH**.

### Static or dynamic?

| | Static library (7.13) | Dynamic library (7.14) |
|---|---|---|
| File names | `station.lib` / `libstation.a` | `station.dll` + `station.lib` (import) / `libstation.so` |
| What the program contains | a **copy** of the code | only a **reference** to the library |
| Needed to run the program | no | **yes**, the DLL / `.so` must be found at start |
| Several programs using it | each carries its own copy | **share** one file |
| Fixing a bug in the library | relink every program | replace one file, if the interface is unchanged |
| Settings must match | at link time | at **run time** too |
| Needs export markers | no | yes on Windows (`STATION_API`) |

### The ABI warning

The last row of the table needs a word. Look at what our library passes across the boundary: a `std::vector<double>` goes in, a `std::string` comes out. Both are **layouts defined by the standard library**, and different compilers, different versions, and even Debug and Release builds of the same compiler can lay them out differently. Our program works because **the same toolchain and the same options built both sides**.

This is why you will see two styles in the real world:

- Libraries shipped as **source or static libraries**, built by *you* with *your* compiler, so everything matches.
- Libraries that ship as DLLs / `.so` files for everyone keep their public functions to **simple types** (integers, pointers, plain structs) and mark them **`extern "C"`**, so that the names are not mangled either.

That second style is exactly what makes a library callable from other languages.

---

## 7.15 Project: driving CMake from the command line

You have now typed, by hand, every kind of command a build needs: compile, link, archive, build a DLL. Real projects have hundreds of them, in the right order, with the right flags for the right compiler. **CMake** writes and runs those commands for you.

Until now you have probably used CMake through an IDE. In this project we call it **directly, from the command line**, in all five environments, and we keep checking its work against what we typed in 7.12 to 7.14. The code is in `7.15ProjectCMakeCommandLine`. It is the same weather station, with a `CMakeLists.txt` that builds a library called `station` and a program called `rooster` that uses it.

### Three layers

```
   CMakeLists.txt  ──►  cmake (configure)  ──►  build files  ──►  Ninja  ──►  cl / g++ / clang++
   what you want        picks a compiler,       build.ninja       runs the     the commands
   (targets, files)     checks it works,        (a list of        commands     you typed by hand
                        writes the plan         commands)         in order
```

`cmake` itself never compiles anything. It reads your `CMakeLists.txt`, finds out which compiler you have, and writes a plan. A **generator** turns the plan into build files for some build tool. We always use **Ninja**, a small fast build tool, with `-G Ninja`. The tool then runs the compiler.

### The commands, step by step

#### 1. Configure

```powershell
cmake -S . -B build-msvc -G Ninja
```

- **`-S .`** the **S**ource folder: where `CMakeLists.txt` is.
- **`-B build-msvc`** the **B**uild folder: where everything generated goes. It is created for you. Nothing is written next to your source files, which is called an **out-of-source build**, and it is why you can delete the whole folder to start again.
- **`-G Ninja`** the generator.

That is all CMake needs on MSVC, because the Developer PowerShell has already put `cl` on the PATH, and CMake finds it. On the other compilers you tell CMake which one to use, and you do it with **`-D` options**. A `-D` sets a **cache variable**, a named setting stored in the build folder.

```powershell
# MinGW GCC (normal PowerShell, NOT the VS Developer one)
cmake -S . -B build-mingw-gcc -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# MinGW Clang
cmake -S . -B build-mingw-clang -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```

```sh
# Linux, GCC
cmake -S . -B build-gcc -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# Linux, Clang
cmake -S . -B build-clang -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```

> **Gotcha: the compiler belongs to the build folder.** CMake stores the compiler in the build folder's cache. If you re-run `cmake` on an existing `-B` folder with a different `-DCMAKE_CXX_COMPILER`, it warns `You have changed variables that require your cache to be deleted`, throws the cache away and starts again, so whatever you had configured there is lost. Keep **one build folder per compiler**, which is why each command above has its own. And if you open the **Developer** PowerShell and then ask for MinGW, `cl` is first on the PATH, so be explicit with the `-D` options, or use a normal PowerShell.

#### 2. Build, and watch what CMake runs

```powershell
cmake --build build-msvc --verbose
.\build-msvc\rooster.exe
```

`cmake --build <folder>` runs the build tool for you. **`--verbose`** makes it print the **real commands** it runs. Read them. This is the payoff of the previous three lectures. On Linux with GCC, the five steps for our program were:

```
[1/5] g++ -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -fvisibility=hidden -c stats.cpp  -o stats.cpp.o
[2/5] g++ -DSTATION_STATIC_DEFINE -I... -std=gnu++23 -fvisibility=hidden -c report.cpp -o report.cpp.o
[3/5] g++ -DSTATION_STATIC_DEFINE -I... -std=gnu++23                     -c main.cpp   -o main.cpp.o
[4/5] ar qc libstation.a stats.cpp.o report.cpp.o   &&   ranlib libstation.a
[5/5] g++ main.cpp.o -o rooster libstation.a
```

(Trimmed for the page, and the paths are shortened.) Compare with what you typed:

| CMake ran | You typed in |
|---|---|
| steps 1 to 3: `g++ ... -c file.cpp -o file.o` | 7.12: one `-c` per source file |
| step 4: `ar qc libstation.a ...` then `ranlib` | 7.13: `ar rcs libstation.a ...` (`ranlib` is the "write the index" step that `s` did for us) |
| step 5: `g++ main.o ... libstation.a -o rooster` | 7.12 and 7.13: the link step |

On MSVC, it is the same story with different spellings. Configured with `-DCMAKE_BUILD_TYPE=Release`, the command for step 1 was `cl.exe /nologo /TP -DSTATION_STATIC_DEFINE ... /EHsc /O2 /Ob2 /DNDEBUG -std:c++latest -MD ... -c stats.cpp`, and for step 4 `lib.exe /nologo /machine:x64 /out:station.lib stats.cpp.obj report.cpp.obj`. Notice the flags: `/EHsc`, `-std:c++latest` and `-MD` are the ones you typed by hand. CMake put them there because `CMAKE_CXX_STANDARD 23` and its defaults ask for them.

**CMake is not magic. It is a command generator.** Whenever a CMake build misbehaves, `--verbose` shows you the exact command that went wrong, and you can run it yourself.

#### 3. Build one target

```powershell
cmake --build build-msvc --target station
```

A **target** is a thing `CMakeLists.txt` defines: here `station` (the library) and `rooster` (the program). `--target station` builds the library and nothing else, and it is how you ask "does just this part compile?" Without `--target`, CMake builds everything.

#### 4. Same sources, different library kind

`CMakeLists.txt` says `add_library(station ...)` with **no `STATIC` or `SHARED`**. The **command line** decides, with one variable:

```powershell
cmake -S . -B build-msvc-shared -G Ninja -DBUILD_SHARED_LIBS=ON
cmake --build build-msvc-shared
```

On MSVC, `build-msvc-shared` now contains `station.dll` and `station.lib` (the import library from 7.14), and `rooster.exe` finds the DLL because they are in the same folder. On MinGW you get `libstation.dll` and `libstation.dll.a`; on Linux `libstation.so`. One flag, and 7.13 turned into 7.14, with no source changes.

How can that work when 7.14 needed `STATION_API` on every function? That is what these lines of `CMakeLists.txt` are for:

```cmake
include(GenerateExportHeader)
generate_export_header(station)

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(station PUBLIC STATION_STATIC_DEFINE)
endif()
```

`generate_export_header(station)` **writes the header for us**. It creates `station_export.h` in the build folder, which defines `STATION_EXPORT` as `dllexport` while the library is compiled, `dllimport` for the program using it, and visibility on Linux, which is the macro we wrote ourselves in 7.14. For a **static** library there is nothing to import or export, so the `if` tells the header to define `STATION_EXPORT` as nothing. Without that line, a static build on Windows would label the functions `dllimport` and fail to link.

The other lines are worth reading too. `target_link_libraries(rooster PRIVATE station)` says "the program uses the library", and gives you the link step for free. And on MinGW, `if(WIN32 AND NOT MSVC) target_link_libraries(rooster PRIVATE stdc++exp)` is the `-lstdc++exp` from 7.12, written once for everybody.

#### 5. Install

```powershell
cmake --install build-msvc --prefix install-msvc
```

`--install` copies the **finished products** to a clean folder, controlled by the `install(...)` lines in `CMakeLists.txt`. `--prefix` names the folder.

```
install-msvc/bin/rooster.exe
install-msvc/lib/station.lib
install-msvc/include/stats.h
install-msvc/include/report.h
install-msvc/include/station_export.h
```

That is the **layout you hand to someone else**: the program in `bin`, the library in `lib`, the headers in `include`. They can use `station` without ever seeing a `.cpp` file.

### Options you will use all the time

| Command or option | What it does |
|---|---|
| `-S <dir>` / `-B <dir>` | source folder / build folder |
| `-G Ninja` | which generator to use |
| `-D<NAME>=<value>` | set a cache variable |
| `-DCMAKE_CXX_COMPILER=<c++>` | pick the compiler, once per build folder |
| `-DCMAKE_BUILD_TYPE=Release` | optimised build (Ninja builds one type per folder) |
| `-DBUILD_SHARED_LIBS=ON` | `add_library` without a keyword makes `.dll` / `.so` |
| `cmake --build <dir>` | build everything |
| `--target <name>` | build one target only |
| `--verbose` | print the real compiler commands |
| `cmake --install <dir> --prefix <dir>` | copy the finished products out |

> **Gotcha: the build type.** With Ninja, each build folder is **one** build type, chosen at configure time. If you do not pass `-DCMAKE_BUILD_TYPE`, MSVC builds with its Debug settings (the install output says `Install configuration: "Debug"`). Pass `-DCMAKE_BUILD_TYPE=Release` and `/O2 /DNDEBUG` appear in the verbose output.

### What to take away from the four projects

```
   source ──► compiler ──► object ──► archiver ──► static library ─┐
                              │                                      ├──► linker ──► program
                              └──► linker ──► dynamic library ──────┘     (+ the DLL / .so at run time)

   CMake writes all of these commands. You read them with --verbose.
```

When something fails to build, you now know which stage it came from: **compiler** errors come with a line of your code, **linker** errors (`undefined reference`, `LNK2019`) are about missing or mismatched names, and **run-time** loading errors (`cannot open shared object file`, a missing DLL) are about where the loader looks.

---

## 7.16 Assignment

Five small jobs for one imaginary weather station: sorting and searching, functional style, formatting a table, dates and durations, and regex. `main.cpp` has the five stubbed exercises, each with its problem statement and, where useful, a sample of the output in a comment; `main_solution.cpp` solves all five. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | Sorting and searching: the sensor registry | `std::ranges::sort` on a copy, `std::ranges::binary_search`, a lambda comparator with a tie-break, a `top_n` helper that never touches its `const` input |
| 2 | Functional style: views and accumulate | `std::views::filter` and `std::views::transform` in a pipeline, `std::accumulate` over a range |
| 3 | Strings and formatting: a station table | `std::format` width, alignment and precision, `std::istringstream` parsing, `std::string_view` |
| 4 | Dates and durations | `std::chrono` calendar dates, `std::chrono::days`, `duration_cast`, `hh_mm_ss` |
| 5 | Regex | `std::regex_match`, `std::sregex_iterator`, `std::regex_replace` with `format_no_copy` |

The quiz (`QUIZ.md`) is 20 multiple-choice questions across lectures 7.2 to 7.11. The four projects (7.12 to 7.15) are about the toolchain, and the best check for them is to run the commands yourself in each environment you have.

After this chapter the student can hold, sort, search and reshape collections of data, format and parse text, work with dates and durations, and build a program from the command line by hand and with CMake. The next chapter looks at what the machine actually does with all of this.
