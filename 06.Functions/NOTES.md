# Functions

Up to now every program has lived inside `main`. That does not scale:
the same lines get copied around, `main` grows into a wall, and one
change has to be made in five places.

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

This chapter follows the reference (Deitel ch05): program components and
the math library, defining functions and prototypes, argument coercion,
the standard-library headers, random numbers, scope rules, `inline`,
reference parameters, default arguments, the `::` operator, overloading,
templates, recursion, `[[nodiscard]]`, and a look at lambdas.

| Lecture | Outline § | Reference figure |
|---|---|---|
| 6.2 Program components | 5.2 | prose |
| 6.3 Math library functions | 5.3 | prose |
| 6.4 Defining functions and prototypes | 5.4 | fig05_01 |
| 6.5 Argument evaluation and coercion | 5.5, 5.6 | fig05_01 |
| 6.6 Standard library headers | 5.7 | table |
| 6.7 Random numbers | 5.8 | fig05_02–04 |
| 6.8 Nondeterministic seeding | 5.10 | fig05_05 |
| 6.9 Game of chance + scoped `enum` | 5.9 | fig05_05 |
| 6.10 Scope rules | 5.11 | fig05_06 |
| 6.11 Inline functions | 5.12 | fig05_07 |
| 6.12 Reference parameters | 5.13 | fig05_08 |
| 6.13 Default arguments | 5.14 | fig05_09 |
| 6.14 Unary scope resolution | 5.15 | fig05_10 |
| 6.15 Function overloading | 5.16 | fig05_11, fig05_12 |
| 6.16 Function templates | 5.17 | fig05_14, maximum.h |
| 6.17 Recursion | 5.18, 5.19 | fig05_15, fig05_16 |
| 6.18 Recursion vs iteration | 5.20 | fig05_17 |
| 6.19 `[[nodiscard]]` | 5.21 | prose |
| 6.20 Lambda functions | — | (practical add-on) |

---

## 6.2 Program components

A C++ program is assembled from **functions**. Some you write; most come
ready-made in the **C++ Standard Library** - `std::println`, `std::sqrt`,
`std::sort`. You **use** any function the same way: its name, then
arguments in parentheses.

```
   library function you call:   std::sqrt(2.0)
   your function you call:       average_of_three(2, 4, 9)
                                 └──────┬───────┘ └───┬───┘
                                     name          arguments
```

The reason to write your own: **reuse**. Define the work once, call it
wherever you need it, instead of copy-pasting the body.

```cpp
double average_of_three(double a, double b, double c) {
    return (a + b + c) / 3.0;
}
```

---

## 6.3 Math library functions

`<cmath>` is a large set of ready-made math functions. Calling them is no
different from calling your own.

| Call | Returns | Example |
|------|---------|---------|
| `std::sqrt(x)` | square root | `sqrt(9.0)` → `3.0` |
| `std::pow(b, e)` | b to the power e | `pow(2.0, 10.0)` → `1024.0` |
| `std::ceil(x)` | round up | `ceil(2.3)` → `3.0` |
| `std::floor(x)` | round down | `floor(2.8)` → `2.0` |
| `std::fmod(a, b)` | floating remainder | `fmod(10.0, 3.0)` → `1.0` |
| `std::abs(x)` | absolute value | `abs(-4.5)` → `4.5` |

C++20 adds named constants in `<numbers>`:

```cpp
double area{std::numbers::pi * radius * radius};
```

---

## 6.4 Defining functions and prototypes

A function has two forms:

```
   int maximum(int x, int y, int z);      ← PROTOTYPE: signature + ';', no body
                                            everything a caller needs

   int maximum(int x, int y, int z) {     ← DEFINITION: prototype + { body }
       int largest{x};
       if (y > largest) { largest = y; }
       if (z > largest) { largest = z; }
       return largest;
   }
```

The compiler reads top to bottom and must have seen a **prototype (or
the full definition) before the first call**. The standard arrangement:

```
   int maximum(int x, int y, int z);   ← prototype up top

   int main() {
       ... maximum(a, b, c) ...        ← compiler checks this against the prototype
   }

   int maximum(int x, int y, int z) {  ← definition below main
       ...
   }
```

This keeps `main` at the top for the reader, and is the only way when
two functions call each other.

- Parameter **names** in a prototype are optional:
  `int maximum(int, int, int);` is valid.
- The **definition's first line must agree** with the prototype (return
  type and parameter types).

---

## 6.5 Argument evaluation and coercion

### Argument coercion

If an argument's type differs from the parameter's, the compiler
**converts** it - when a safe conversion exists.

```
   double square(double value);

   square(4)     ← 4 is int; coerced to 4.0, then squared → 16.0
   square(2.5)   ← already double → 6.25
```

Widening conversions (`int` → `double`, `char` → `int`) are safe and
silent. Narrowing ones (`double` → `int`) lose information and should be
made explicit with a cast.

### The signature is name + parameter types

The **return type is not part of the signature**. `int f(int)` and
`double f(int)` have the *same* signature and cannot both exist - see
overloading (6.15).

### Order of argument evaluation is unspecified

The compiler may evaluate a call's arguments in **any order**. If one
argument's side effect is observed by another, the result is not
portable:

```cpp
std::println("{} {}", n++, n);   // which reads n first? UNSPECIFIED - avoid
```

Do side-effecting work in its own statement:

```cpp
int a{n++};
std::println("a = {}, n = {}", a, n);
```

---

## 6.6 Standard library headers

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

## 6.7 Random numbers

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
  useful while testing. Change that by seeding it (6.8).
- A different range is just a different distribution:
  `uniform_int_distribution<int>{0, 100}`.

---

## 6.8 Nondeterministic seeding

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

## 6.9 Game of chance and scoped `enum`

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
call - see 6.10.)

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

## 6.10 Scope rules

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

## 6.11 Inline functions

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

## 6.12 Reference parameters

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

## 6.13 Default arguments

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

## 6.14 Unary scope resolution operator

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

## 6.15 Function overloading

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

## 6.16 Function templates

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

## 6.17 Recursion

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

## 6.18 Recursion vs iteration

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

## 6.19 The `[[nodiscard]]` attribute

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

## 6.20 Lambda functions

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

## 6.21 Assignment

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
