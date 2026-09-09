# Functions

Up to now every program has lived inside `main`. That does not scale.

A **function** is a named, reusable piece of work. You **call** it by
name, hand it **arguments**, it runs, and it hands back a **result**.

```
   caller                          function
   ──────                          ────────
   int m = maximum(a, b, c);       int maximum(int x, int y, int z) {
        │        └──arguments──┐        └──parameters──┘
        │                      ▼        ...
        │                  x=a, y=b, z=c
        │                      │        return largest;
        └──────result──────────┘◄───────────┘
```

In this chapter, we dive deep into functions and see how you can break your program into **smaller, reusable pieces**. 

---

## 6.2 Program components

A C++ program is assembled from **functions**. Some you write; most come
ready-made in the **C++ Standard Library** - `std::println`, `std::sqrt`,
`std::sort`. You **use** any function the same way: its name, then
arguments in parentheses.

```
   library function you call:   std::sqrt(2.0)
   your function you call:       rectangle_perimeter(3, 4)
                                 └────────┬────────┘ └─┬─┘
                                       name        arguments
```

The reason to write your own: **reuse**. Define the work once, call it
wherever you need it, instead of copy-pasting the body.

```cpp
int rectangle_perimeter(int width, int height) {
    return 2 * (width + height);
}

rectangle_perimeter(3, 4);      // 14
rectangle_perimeter(10, 10);    // 40  - one formula, called again
```

---

## 6.3 Built-in functions

You do not have to write everything. The Standard Library ships
**thousands of ready-made functions** across many headers - and it keeps
growing, every standard adds more. Calling any of them is no different
from calling your own: `#include` the header, then `name(arguments)`.

Here is a small tour. The `(C++NN)` tag marks a more recent addition. Go
through them one at a time on camera - each is just a function call, but
knowing it *exists* saves writing (and debugging) it yourself.

---

### Math — `<cmath>`, `<numbers>`

**`std::sqrt(x)`** — the square root. The number that, multiplied by
itself, gives `x`.

```
   sqrt(9.0)  →  3.0        because 3.0 * 3.0 == 9.0
   sqrt(2.0)  →  1.41421...
```

**`std::pow(b, e)`** — `b` raised to the power `e`: `b` multiplied by
itself `e` times.

```
   pow(2.0, 10.0)  →  1024.0

   2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2
   └────────────── ten 2s ──────────────┘
```

The exponent can be fractional, too: `pow(x, 0.5)` is another way to
write `sqrt(x)`.

**`std::hypot(a, b)`** — the length of the hypotenuse of a right
triangle with legs `a` and `b`. Mathematically `sqrt(a*a + b*b)`, but it
computes it *without* the intermediate `a*a` overflowing or underflowing.

```
        │\
        │ \   hypot(3, 4) = 5
      4 │  \
        │   \        (the classic 3-4-5 triangle)
        │____\
          3
```

**`std::lerp(a, b, t)`** *(C++20)* — **l**inear int**erp**olation. Slide
from `a` to `b` by the fraction `t`, where `t = 0` gives `a`, `t = 1`
gives `b`, and `t = 0.5` gives the point exactly halfway.

```
   lerp(0, 100, t):

   t:   0.0      0.25      0.5       0.75      1.0
        │─────────┼─────────┼─────────┼─────────│
   a=0 ─┘         │         │         │         └─ b=100
              lerp = 25   lerp = 50  lerp = 75

```

Used for smooth movement, fades, blending a value from one setting to
another over time.

**`std::midpoint(a, b)`** *(C++20)* — the value exactly between `a` and
`b`. Conceptually `(a + b) / 2`, but written so that `a + b` cannot
overflow (for huge ints) and with correct rounding.

```
   midpoint(10, 20)  →  15

   10 ──────────●────────── 20
               15
```

**`std::numbers::pi`** *(C++20)* — the constant π as a `double`, to full
precision.

```cpp
double area{std::numbers::pi * radius * radius};   // πr²
```

`<numbers>` also has `e`, `sqrt2`, `phi` (the golden ratio), and more.

---

### Numeric helpers — `<numeric>`

**`std::gcd(a, b)`** *(C++17)* — the **g**reatest **c**ommon
**d**ivisor: the largest whole number that divides both `a` and `b`
evenly.

```
   gcd(24, 36)  →  12

   divisors of 24:  1  2  3  4  6  [8]  12  24
   divisors of 36:  1  2  3  4  6  [9]  12  18  36
                    └─ common: 1 2 3 4 6 12 ─┘   largest = 12
```

**`std::lcm(a, b)`** *(C++17)* — the **l**east **c**ommon **m**ultiple:
the smallest number that both `a` and `b` divide into.

```
   lcm(4, 6)  →  12

   multiples of 4:  4  8  [12]  16  20  24 ...
   multiples of 6:  6  [12]  18  24 ...
                        └─ smallest shared = 12
```

---

### Picking and bounding values — `<algorithm>`

**`std::min(a, b)` / `std::max(a, b)`** — the smaller / larger of two
values.

```
   min(7, 3) → 3          max(7, 3) → 7
```

**`std::clamp(v, lo, hi)`** *(C++17)* — force `v` into the range
`[lo, hi]`. Below `lo` it becomes `lo`; above `hi` it becomes `hi`;
in between it is unchanged.

```
   clamp(v, 0, 100):

   v:   -30     0        55       100     150
        ●───────┿━━━━━━━━━━━━━━━━━┿───────●
        │       │                │       │
      → 0      0                100     100      (● snapped to the edge)
```

**`std::ranges::sort(v)`** *(C++20)* — sort a whole container in one
call, ascending by default. 

```
   {5, 2, 8, 1, 9, 3}   ──ranges::sort──►   {1, 2, 3, 5, 8, 9}
```

---

### Text queries — `<string>`

These are member functions you call on a `std::string`.

**`s.starts_with(p)` / `s.ends_with(p)`** *(C++20)* — does the string
begin / end with `p`? Returns a `bool`.

```
   "hello world"
    └───┘     └───┘
  starts_with  ends_with
   ("hello")    ("world")   → both true
```

**`s.contains(sub)`** *(C++23)* — is `sub` found *anywhere* inside `s`?

```
   "hello world".contains("lo wo")

    h e l l o   w o r l d
        └─ l o _ w o ─┘        found → true
```

Before C++23 you wrote `s.find(sub) != std::string::npos` for this;
`contains` says what you mean.

---

### Bit inspection — `<bit>` *(C++20)*

These look at the binary representation of an unsigned integer.

**`std::popcount(x)`** — the **pop**ulation **count**: how many bits are
set to `1`.

```
   popcount(0b1011'0100u)

   1 0 1 1 0 1 0 0
   ▲   ▲ ▲   ▲            four 1s  →  4
```

**`std::bit_width(x)`** — how many bits it takes to represent `x`: the
position of the highest set bit, plus one.

```
   bit_width(0b1011'0100u)

   1 0 1 1 0 1 0 0
   ▲
   highest 1 is in bit 7 (counting from 0)  →  width 8
```

**`std::has_single_bit(x)`** — is exactly one bit set? Equivalently, is
`x` a power of two (1, 2, 4, 8, 16, ...)?

```
   64  = 0b0100'0000   → one bit set   → true
   65  = 0b0100'0001   → two bits set  → false
```

---

The takeaway: **before writing a helper, check whether the library
already has it.** Very often it does - and the library version handles
the edge cases (`hypot` avoids overflow, `midpoint` avoids the
`(a + b)` overflow, `clamp` gets both comparisons right) that a quick
hand-rolled version tends to miss.

---

## 6.4 Declaring and defining functions

A function has two forms:

```
   double average(double a, double b, double c);   ← PROTOTYPE: signature + ';',
                                                     no body. everything a caller needs

   double average(double a, double b, double c) {  ← DEFINITION: prototype + { body }
       return (a + b + c) / 3.0;
   }
```

The compiler reads top to bottom and must have seen a **prototype (or
the full definition) before the first call**. The standard arrangement:

```
   double average(double a, double b, double c);   ← prototype up top

   int main() {
       ... average(x, y, z) ...     ← compiler checks this call against the prototype
   }

   double average(double a, double b, double c) {  ← definition below main
       ...
   }
```

This keeps `main` at the top for the reader, and is the only way when
two functions call each other.

- Parameter **names** in a declaration are optional:
  `double average(double, double, double);` is valid - only the types
  matter.
- The **definition's first line must agree** with the declaration
  (return type and parameter types).

### The signature is name + parameter types

The **return type is not part of the signature**. `double average(...)`
and a hypothetical `int average(...)` with the same parameters would
*clash*, not coexist. What lets two functions share a name is a
*different parameter list* - see overloading (6.14).

### Argument coercion

If an argument's type differs from the parameter's, the compiler
**converts** it - when a safe conversion exists.

```
   double average(double a, double b, double c);

   average(4, 8, 15)   ← 4, 8, 15 are ints; each widened to double
                         (4 → 4.0) before the call, giving 9.0
   average(4.0, 8.0, 15.0)   ← already double
```

Widening conversions (`int` → `double`, `char` → `int`) are safe and
silent. Narrowing ones (`double` → `int`) lose information and should be
made explicit with a cast.

### Order of argument evaluation is unspecified

The compiler may evaluate a call's arguments in **any order**. If one
argument's side effect is observed by another, the result is not
portable:

```cpp
average(n++, n, n);   // which reading of n goes where? UNSPECIFIED - avoid
```

Do side-effecting work in its own statement first.

---

## 6.5 Standard library headers

The library groups related functions and types into **headers**;
`#include` the one you need. Early in this course:

| Header | Provides |
|--------|----------|
| `<iostream>` | `std::cin`, `std::cout` |
| `<print>` | `std::print`, `std::println` (C++23) |
| `<string>` | `std::string` |
| `<string_view>` | `std::string_view` |
| `<vector>` | `std::vector` |
| `<cmath>` | `sqrt`, `pow`, `abs`, `ceil`, `floor`, `fmod`, … |
| `<numbers>` | `numbers::pi` and friends (C++20) |
| `<random>` | engines, distributions, `random_device` |
| `<algorithm>` | `sort`, `find`, `count`, `min`, `max`, … |

All these names live in namespace `std`, so you qualify them:
`std::sqrt`, `std::vector`, `std::sort`.

---

## 6.6 Random numbers

Random values come from **two pieces**:

```
   ENGINE         produces raw random bits
        │
        ▼
   DISTRIBUTION   shapes those bits into the range/shape you asked for
        │
        ▼
   one value      distribution(engine)
```

```cpp
std::default_random_engine engine{};              // the source
std::uniform_int_distribution<int> die{1, 6};     // shape: ints 1..6, equal odds

for (int i{0}; i < 10; ++i) {
    std::print("{} ", die(engine));               // call the distribution with the engine
}
```

- A **default-constructed engine replays the same sequence every run** -
  useful while testing. Change that by seeding it (6.7).
- A different range is just a different distribution:
  `uniform_int_distribution<int>{0, 100}`.

---

## 6.7 Nondeterministic seeding

To get a different sequence each run, **seed** the engine.

```
   engine{}          → same sequence every run
   engine{seed}      → reproducible: same seed value ⇒ same sequence
   engine{rd()}      → fresh sequence every run (rd is a std::random_device)
```

```cpp
// reproducible - the user picks the seed
std::default_random_engine seeded{seed};

// fresh each run - random_device is a nondeterministic source
std::random_device rd{};
std::default_random_engine fresh{rd()};   // rd() produces the seed
```

Use a **fixed seed while developing** (so a bug reproduces), and
`random_device` for the shipped program.

---

## 6.8 Game of chance and scoped `enum`

The craps example pulls three ideas together.

### A helper function

`roll_dice()` does one job - roll two dice, show them, return the sum -
and `main` calls it wherever a roll is needed:

```cpp
int roll_dice() {
    static std::random_device rd{};
    static std::default_random_engine engine{rd()};
    static std::uniform_int_distribution<int> die{1, 6};
    const int d1{die(engine)};
    const int d2{die(engine)};
    std::println("  rolled {} + {} = {}", d1, d2, d1 + d2);
    return d1 + d2;
}
```

(The `static` locals mean the engine is set up **once**, not on every
call - see 6.9.)

### A scoped `enum`

```cpp
enum class Status { keep_rolling, won, lost };
```

- The names live **inside** `Status`: you write `Status::won`, never a
  bare `won`. No name clashes with anything else.
- A scoped enum **does not implicitly convert to `int`**, so you cannot
  accidentally compare it to a number or a different enum.

### `switch` with an initializer

```cpp
switch (const int first{roll_dice()}; first) {
    case 7: case 11:  status = Status::won;  break;
    case 2: case 3: case 12:  status = Status::lost;  break;
    default:  point = first;  break;   // remember the point, keep rolling
}
```

`first` is rolled once, is in scope for the whole `switch`, and is gone
after it.

---

## 6.9 Scope rules

**Scope** = where a name is visible. **Lifetime** = how long the object
exists.

| Kind | Scope | Lifetime |
|------|-------|----------|
| local variable | its enclosing `{ }` | until that block ends |
| block variable | the inner `{ }` | until that inner block ends |
| global variable | its declaration → end of file | whole program |
| `static` local | its function | whole program (created once) |

### Hiding

An inner name **hides** an outer one of the same name:

```cpp
int x{1};                 // global

int main() {
    int x{5};             // hides the global inside main
    {
        int x{7};         // hides both, inside this block
        std::println("{}", x);   // 7
    }
    std::println("{}", x);       // 5  (block's x is gone)
}
```

### `static` local

An ordinary local is **recreated every call**. A `static` local is
created **once**, on the first call, and keeps its value between calls:

```cpp
void use_local()        { int x{25};        ++x; }   // 25→26 every call
void use_static_local() { static int x{50}; ++x; }   // 50→51, 51→52, 52→53 …
```

```
   ordinary:   call1 [25→26]   call2 [25→26]   call3 [25→26]
   static:     call1 [50→51]   call2 [51→52]   call3 [52→53]
                             (value carried across calls)
```

---

## 6.10 Inline functions

`inline` on a function definition **permits that definition to appear in
more than one translation unit** (typically because it sits in a header
included by several `.cpp` files) without a "multiple definition" linker
error. All copies must be identical; the linker folds them into one.

It is **not** a command to paste the body at the call site - the
optimizer already decides that on its own, `inline` or not.

```cpp
inline double cube(double side) {
    return side * side * side;
}
```

A function defined **before** its first use needs no separate prototype:
its first line serves as one.

```
   constexpr  → "may be evaluated at compile time"      (a later topic)
   inline     → "this definition may appear in many files; treat as one"
```

---

## 6.11 Reference parameters

The two ways an argument reaches a function.

### Pass by value

The parameter is a **copy** of the argument. Changing it does not touch
the caller.

```
   main:              square_by_value:
   ┌─────────┐  copy   ┌──────────────┐
   │  x  2   │────────►│ number  2    │
   └─────────┘         └──────┬───────┘
        ▲                     │ number *= number  → 4  (the COPY)
        │                     ▼
   x still 2               returned value is 4
```

```cpp
int square_by_value(int number) {
    number *= number;
    return number;          // new value visible ONLY via the return
}
```

### Pass by reference

The parameter, written `T&`, is an **alias** for the caller's variable.
Changing it changes the original.

```
   main:              square_by_reference:
   ┌─────────┐         ┌──────────────────┐
   │  z  4   │◄───────►│ ref  (alias of z)│
   └─────────┘         └────────┬─────────┘
        ▲                       │ ref *= ref
        └───────────────────────┘  → z is now 16
```

```cpp
void square_by_reference(int& ref) {
    ref *= ref;             // the caller's variable is modified in place
}
```

Use **by value** for small inputs you only read; use **a reference**
when the function must change the caller's variable (or hand back more
than one result by writing through several reference parameters).

---

## 6.12 Default arguments

A parameter can carry a **default**, used when the caller omits that
argument.

```cpp
int box_volume(int length = 1, int width = 1, int height = 1);
```

```
   box_volume()          → 1 * 1 * 1  = 1
   box_volume(10)        → 10 * 1 * 1 = 10
   box_volume(10, 5)     → 10 * 5 * 1 = 50
   box_volume(10, 5, 2)  → 10 * 5 * 2 = 100
```

Rules:

- Defaults live in the **prototype**, written once (not repeated in the
  definition).
- Only **trailing** parameters may have defaults, so arguments fill
  **left to right**. `box_volume(10, , 2)` is invalid.
- Put the parameters most often left default **last**.

---

## 6.13 Unary scope resolution operator

When a local variable **hides** a global of the same name, the local
wins inside its scope. `::name` reaches past the local to the **global**.

```cpp
int value{7};              // global int

int main() {
    double value{10.5};    // local - hides the global in main

    std::println("{}", value);     // 10.5   (the local)
    std::println("{}", ::value);   // 7      (the global, via ::)
}
```

```
   value      → nearest declaration: the local
   ::value    → skip locals: the global
```

---

## 6.14 Function overloading

Several functions may **share a name** if their **parameter lists
differ** (in count or type). The compiler picks the best match per call.

```cpp
int    square(int x)    { return x * x; }
double square(double x) { return x * x; }
```

```
   square(7)     → argument is int    → int version
   square(7.5)   → argument is double → double version
   square(7.0f)  → float promotes to double → double version
```

- The **return type alone cannot distinguish overloads**:
  `int f(int);` and `double f(int);` together is an error.
- If no overload matches exactly, the compiler tries conversions to find
  the best; an ambiguous tie is a compile error.
- Internally the compiler gives each overload a distinct mangled name
  from its parameter types, so the versions never collide at link time.

---

## 6.15 Function templates

A **function template** is a pattern with the type left blank. `T` is a
placeholder the compiler fills in from the call's arguments, generating a
concrete function on demand. One template stands in for a whole **family
of overloads** you would otherwise hand-write.

```cpp
template <typename T>
T maximum(T a, T b, T c) {
    T largest{a};
    if (b > largest) { largest = b; }
    if (c > largest) { largest = c; }
    return largest;
}
```

```
   maximum(3, 9, 5)          T deduced = int      → generates maximum<int>
   maximum(2.5, 1.1, 3.8)    T deduced = double   → generates maximum<double>
   maximum('q', 'a', 'm')    T deduced = char     → generates maximum<char>
```

- The compiler **deduces `T`** from the arguments. All three must agree:
  `maximum(3, 9.0, 5)` (int, double, int) fails to deduce one `T`.
- State it explicitly to force a type: `maximum<double>(3, 9, 5)`.
- The body must be valid for whatever `T` is - `maximum` needs `>` to
  work on `T`, which it does for the numeric types and `std::string`.

---

## 6.16 Recursion

A **recursive** function calls itself. Every one needs:

- a **base case** that returns without recursing (ends the chain), and
- a **recursive step** that calls itself with an argument closer to the
  base case.

```cpp
long factorial(int number) {
    if (number <= 1) { return 1; }              // base case
    return number * factorial(number - 1);      // recursive step
}
```

```
   factorial(4)
   = 4 * factorial(3)
       = 3 * factorial(2)
           = 2 * factorial(1)
               = 1                 ← base case; unwinding begins
           = 2 * 1  = 2
       = 3 * 2  = 6
   = 4 * 6  = 24
```

`fibonacci` has **two** base cases:

```cpp
long fibonacci(long n) {
    if (n == 0 || n == 1) { return n; }
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

Miss the base case, or fail to move toward it, and the calls never stop:
a **stack overflow** - the recursive cousin of an infinite loop.

---

## 6.17 Recursion vs iteration

The same `factorial`, both ways:

```cpp
long factorial_recursive(int n) {
    if (n <= 1) { return 1; }
    return n * factorial_recursive(n - 1);
}

long factorial_iterative(int n) {
    long result{1};
    for (int i{2}; i <= n; ++i) { result *= i; }
    return result;
}
```

| | Recursion | Iteration |
|--|-----------|-----------|
| stack use | one frame per call - deep input can overflow | constant |
| speed | function-call overhead per step | usually faster |
| clarity | natural for recursive structures (trees, divide-and-conquer) | natural for counting/accumulating |

Rule of thumb: **iterate by default; recurse when it makes the problem
clearer.**

---

## 6.18 The `[[nodiscard]]` attribute

Mark a function `[[nodiscard]]` when **ignoring its return value is
almost certainly a bug** - the point of the call is the value it hands
back. The compiler then warns if a caller drops it.

```cpp
[[nodiscard]] int add(int a, int b) { return a + b; }

int s{add(3, 4)};   // fine
add(3, 4);          // warning: result of a [[nodiscard]] call is unused
```

Good on: pure computations, functions that report success/failure, and
functions that return a resource the caller must handle.

---

## 6.19 Lambda functions

A **lambda** is a small function written **inline**, where it is used -
usually to hand to another function. Shape:

```
   [ capture ] ( parameters ) { body }
   └───┬────┘
   which surrounding variables the lambda may use
```

```cpp
auto add = [](int a, int b) { return a + b; };
add(3, 4);   // 7
```

### Captures

```cpp
int offset{10};
auto shift = [=](int n) { return n + offset; };   // copies offset (snapshot: 10)
offset = 999;                                      // shift still uses 10

int total{0};
auto accumulate = [&](int n) { total += n; };      // links to the real total
accumulate(3); accumulate(4);                       // total is now 7
```

```
   [=]   capture everything used, BY VALUE   (a snapshot)
   [&]   capture everything used, BY REFERENCE (live link)
   [x]   just x, by value       [&x]  just x, by reference
   []    capture nothing
```

### Passing a lambda where a callable is expected

```cpp
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });   // descending
```

Standard-library algorithms take a callable to decide ordering,
filtering, and so on; a lambda at the call site is the usual way to
supply it.

---

## 6.20 Assignment

`main.cpp` has six stubbed exercises, each with its problem statement and
a sample run in a comment; `main_solution.cpp` solves all six with the
statements repeated above each solution. Built as two executables
(`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `hypotenuse` | prototype below `main`, `<cmath>` `std::sqrt` |
| 2 | roll histogram | `random_device` seed, `uniform_int_distribution`, counting |
| 3 | `announce` call counter | `static` local |
| 4 | `to_minutes_seconds` | reference parameters (two outputs) |
| 5 | `line` + `max3<T>` | default arguments + a function template |
| 6 | `power` + a lambda | recursion, `[[nodiscard]]`, a `[]` lambda |

After this chapter the student can factor code into functions, pass and
return data, and is ready for classes.
