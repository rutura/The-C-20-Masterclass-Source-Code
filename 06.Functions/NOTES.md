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
        │                           }
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

rectangle_perimeter(3, 4)e_peri;      // 14
rectanglmeter(10, 10);    // 40  - one formula, called again
```

### The call stack

When a function is called, the program does not just "jump" to it. It
sets aside a block of memory - a **stack frame** - to hold that call's
arguments, local variables, and the address to return to. Frames stack
up as calls nest, and pop off as calls return.

```
   main() calls area(), which calls square()

   ┌──────────────────────────┐  ← top of stack (most recent call)
   │ square()                 │
   │   n = 4                  │
   │   return address → area  │
   ├──────────────────────────┤
   │ area()                   │
   │   side = 4               │
   │   return address → main  │
   ├──────────────────────────┤
   │ main()                   │
   │   ...                    │
   └──────────────────────────┘  ← bottom (first call)

   square() returns → its frame pops → area() resumes
   area()   returns → its frame pops → main() resumes
```

The stack grows and shrinks automatically; this is why a local variable
vanishes when its function returns (its frame is gone) and why very deep
recursion can **overflow the stack** - it runs out of room for frames.

### Call overhead and `inline`

Building a frame, jumping in, and tearing it down on return is cheap, but
it is **not free**. For a tiny function - a one-liner called inside a
tight loop - that setup can cost more than the work itself.

Marking the function **`inline`** gives the compiler permission to skip
the call: paste the function's body straight into the call site.

```cpp
inline int sum(int a, int b) {
    return a + b;
}

int total{sum(3, 4)};   // compiler may compile this as: int total{3 + 4};
```

Two things to keep straight:

- `inline` is a **suggestion, not a command**. The compiler may still
  decide to call it normally if it deems that better.

---

## 6.3 Built-in functions

You do not have to write everything. The Standard Library ships
**thousands of ready-made functions** across many headers - and it keeps
growing, every standard adds more. Calling any of them is no different
from calling your own defined functions.

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
        │   \        
        │____\
          3
```

**`std::lerp(a, b, t)`** *(C++20)* — **l**inear int**erp**olation. Slide
from `a` to `b` by the fraction `t`, where `t` is treated as a
percentage of the distance from `a` to `b`: `t = 0` gives `a`, `t = 1`
gives `b`, and `t = 0.5` gives the point exactly halfway.

```
   lerp(a, b, t) = a + t * (b - a)
```

```
   lerp(0, 100, t):

   t:   0.0      0.25      0.5       0.75      1.0
        │─────────┼─────────┼─────────┼─────────│
   a=0 ─┘         │         │         │         └─ b=100
              lerp = 25   lerp = 50  lerp = 75

```

```cpp
std::lerp(0.0, 100.0, 0.25);   // 25.0  -> a quarter of the way from 0 to 100
std::lerp(0.0, 100.0, 0.5);    // 50.0  -> halfway between 0 and 100
std::lerp(0.0, 100.0, 1.0);    // 100.0 -> exactly b, guaranteed, no rounding error
std::lerp(0.0, 100.0, 0.0);    // 0.0   -> exactly a, guaranteed, no rounding error
```

The return type is always floating-point (`double`, unless `float` or
`long double` is used throughout) — even if `a` and `b` are integers,
since the result is inherently fractional.

Used for smooth movement, fades, blending a value from one setting to
another over time.

**Extrapolation.** `t` isn't required to stay between 0 and 1. The same
formula keeps working outside that range, it just walks *past* `a` or
`b` instead of stopping between them:

```
 t:    -0.5        0.0                    1.0        1.5
        │───────────│──────────────────────│───────────│
       -50           0                    100          150
    (before a)      a=0                   b=100    (past b)

        ◄── extrapolating ──►  interpolating  ◄── extrapolating ──►
```

```cpp
std::lerp(0.0, 100.0, -0.5);  // -50.0  -> t < 0, lands before a
std::lerp(0.0, 100.0,  1.5);  // 150.0  -> t > 1, lands past b
```
The rules:

- `t < 0` → result lands before `a`
- `0 <= t <= 1` → result lands between `a` and `b` (this is "interpolation" proper)
- `t > 1` → result lands past `b`

If overshoot isn't wanted, clamp `t` to `[0, 1]` before calling
`lerp`:

```cpp
double t_clamped{std::clamp(t, 0.0, 1.0)};
double value{std::lerp(a, b, t_clamped)};   // never overshoots a or b
```

**Color gradients** are a good way to see all of this at once, since
blending from one color to another is just `lerp` applied to each of
its red, green, and blue channels separately:

```cpp
// red   goes from 255 (red) to 0   (blue)
// green stays    0                (unused here)
// blue  goes from 0   (red) to 255 (blue)

double t{0.5};   // 0.0 = pure red, 1.0 = pure blue

double red  {std::lerp(255.0, 0.0, t)};
double green{std::lerp(0.0,   0.0, t)};
double blue {std::lerp(0.0,   255.0, t)};

// t = 0.0  ->  red=255, green=0, blue=0     -> red
// t = 0.5  ->  red=127.5, green=0, blue=127.5 -> purple
// t = 1.0  ->  red=0,  green=0, blue=255    -> blue
```

```
 t:      0.0        0.25        0.5        0.75        1.0
         │───────────┼───────────┼───────────┼───────────│
 color:  RED                   PURPLE                   BLUE
         (255,0,0)            (128,0,128)            (0,0,255)
```

**`std::midpoint(a, b)`** *(C++20)* — the value exactly between `a` and
`b`. Conceptually `(a + b) / 2`, but written so that `a + b` cannot
overflow (for huge ints) and with correct rounding.

```
   midpoint(10, 20)  →  15

   10 ──────────●────────── 20
               15
```

**`std::numbers::pi`** *(C++20)* — the constant π as a `double`, to full
precision. Before this existed, people either typed `3.14159...` by
hand (easy to mistype, never precise enough) or wrote their own
`constexpr double PI = ...`. Now the library just hands you the exact
value.

```cpp
double radius{5.0};
double area{std::numbers::pi * radius * radius};   // πr² ≈ 78.5398
```

`<numbers>` also has `e`, `sqrt2`, `phi` (the golden ratio), and more —
worth a peek if you ever find yourself hand-typing a math constant.

---

### Numeric helpers — `<numeric>`

**`std::gcd(a, b)`** *(C++17)* — the **g**reatest **c**ommon
**d**ivisor: the largest whole number that divides both `a` and `b`
evenly, with no remainder.

```
   gcd(24, 36)  →  12

   divisors of 24:  1  2  3  4  6  8  12  24
   divisors of 36:  1  2  3  4  6  9  12  18  36
                    └─ common: 1 2 3 4 6 12 ─┘   largest = 12
```

```cpp
std::gcd(24, 36);   // 12
std::gcd(7, 13);     // 1   -> nothing in common but 1 ("coprime")
```

**Practical nugget:** the classic use is reducing a fraction to its
simplest form — divide both numerator and denominator by their `gcd`:

```cpp
int numerator{24}, denominator{36};
int divisor{std::gcd(numerator, denominator)};   // 12

numerator   /= divisor;   // 2
denominator /= divisor;   // 3
// 24/36 simplified is 2/3
```

**`std::lcm(a, b)`** *(C++17)* — the **l**east **c**ommon **m**ultiple:
the smallest number that both `a` and `b` divide into evenly.

```
   lcm(4, 6)  →  12

   multiples of 4:  4  8  12  16  20  24 ...
   multiples of 6:  6  12  18  24 ...
                        └─ smallest shared = 12
```

```cpp
std::lcm(4, 6);   // 12
std::lcm(3, 5);   // 15  -> no overlap until 3*5
```

**Practical nugget:** `lcm` is what you'd reach for to line up two
repeating cycles — e.g. "event A happens every 4 seconds, event B every
6 seconds, when do they next coincide?" → every `lcm(4, 6) = 12`
seconds.

---

### Picking and bounding values — `<algorithm>`

**`std::min(a, b)` / `std::max(a, b)`** — the smaller / larger of two
values.

```
   min(7, 3) → 3          max(7, 3) → 7
```

```cpp
std::min(7, 3);   // 3
std::max(7, 3);   // 7
```

**`std::clamp(v, lo, hi)`** *(C++17)* — force `v` into the range
`[lo, hi]`. Below `lo` it becomes `lo`; above `hi` it becomes `hi`;
in between it is left unchanged.

```
   clamp(v, 0, 100):

   v:   -30     0        55       100     150
        ●───────┿━━━━━━━━━━━━━━━━━┿───────●
        │       │                │       │
      → 0      0                100     100      (● snapped to the edge)
```

```cpp
std::clamp(-30, 0, 100);   // 0    -> below lo, snapped up
std::clamp( 55, 0, 100);   // 55   -> already in range, unchanged
std::clamp(150, 0, 100);   // 100  -> above hi, snapped down
```

**Practical nugget:** this is exactly the same idea as clamping `t`
before a `std::lerp` call (see above) — anywhere you have a value that
must not escape a valid range (a volume percentage, a health bar, a
pixel coordinate on screen) `clamp` is one call instead of a manual
`if`/`else if`.

```cpp
// without clamp
int volume{raw_volume};
if (volume < 0)   volume = 0;
if (volume > 100) volume = 100;

// with clamp
int volume{std::clamp(raw_volume, 0, 100)};
```

**`std::ranges::sort(v)`** *(C++20)* — sort a whole container in one
call, ascending by default.

```
   {5, 2, 8, 1, 9, 3}   ──ranges::sort──►   {1, 2, 3, 5, 8, 9}
```

```cpp
std::vector<int> v{5, 2, 8, 1, 9, 3};
std::ranges::sort(v);
// v is now {1, 2, 3, 5, 8, 9}
```

Note there's no return value to capture here — `v` is sorted **in
place**, meaning the original container itself is rearranged.

---

### Text queries — `<string>`

These are member functions you call *on* a `std::string`, with dot
syntax: `s.starts_with(...)` rather than `starts_with(s, ...)`.

**`s.starts_with(p)` / `s.ends_with(p)`** *(C++20)* — does the string
begin / end with `p`? Returns a `bool`.

```
   "hello world"
    └───┘     └───┘
  starts_with  ends_with
   ("hello")    ("world")   → both true
```

```cpp
std::string s{"hello world"};

s.starts_with("hello");   // true
s.starts_with("world");   // false
s.ends_with("world");     // true
```

**Practical nugget:** a common real use is checking file extensions or
URL prefixes:

```cpp
if (filename.ends_with(".cpp"))  { /* it's a C++ source file */ }
if (url.starts_with("https://")) { /* it's a secure link */ }
```

**`s.contains(sub)`** *(C++23)* — is `sub` found *anywhere* inside `s`?
Returns a `bool`.

```
   "hello world".contains("lo wo")

     h e l l o  w o r l d
        └─ l o_ w o ─┘        found → true
```

```cpp
s.contains("lo wo");   // true
s.contains("bye");     // false
```

Before C++23 you had to write
`s.find(sub) != std::string::npos` for this — checking that `find`
didn't return the special "not found" marker. `contains` says exactly
what you mean, directly.

---

### Bit inspection — `<bit>` *(C++20)*

These look at the binary (0s and 1s) representation of an unsigned
integer — the kind of low-level check you'd reach for in graphics,
networking, or performance-sensitive code.

**`std::popcount(x)`** — the **pop**ulation **count**: how many bits are
set to `1`.

```
   popcount(0b1011'0100u)

   1 0 1 1 0 1 0 0
   ▲   ▲ ▲   ▲            four 1s  →  4
```

```cpp
std::popcount(0b1011'0100u);   // 4
std::popcount(0b0000'0000u);   // 0
std::popcount(0b1111'1111u);   // 8
```

**`std::bit_width(x)`** — how many bits it takes to represent `x`: the
position of the highest set bit, plus one.

```
   bit_width(0b1011'0100u)

   1 0 1 1 0 1 0 0
   ▲
   highest 1 is in bit 7 (counting from 0)  →  width 8
```

```cpp
std::bit_width(0b1011'0100u);   // 8
std::bit_width(0b0000'0001u);   // 1
std::bit_width(0b0000'0000u);   // 0  -> no bits set at all
```

**`std::has_single_bit(x)`** — is exactly one bit set? Equivalently, is
`x` a power of two (1, 2, 4, 8, 16, ...)?

```
   64  = 0b0100'0000   → one bit set   → true
   65  = 0b0100'0001   → two bits set  → false
```

```cpp
std::has_single_bit(64u);   // true   -> 64 is a power of two
std::has_single_bit(65u);   // false
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

   double average(double a, double b, double c) {  ← DEFINITION: prototype +  body 
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

### NOTE: *declaration* and *signature*

**Declaration (prototype)** — a statement that names a function and
gives its return type and parameter types, ending in `;`, with **no body**. 
It is a *promise*: "a function shaped like this exists somewhere;
here is how to call it." The **definition** is the same first line plus
the `{ }` body that actually does the work.

```cpp
double average(double a, double b, double c);   // declaration (prototype)

double average(double a, double b, double c) {  // definition
    return (a + b + c) / 3.0;
}
```

A program can have the **declaration many times** (once per file that
calls it) but **exactly one definition**. The two must match.

**Signature** — the part of a function the compiler uses to tell one
function from another: its **name** plus its **parameter types, in
order**. That is *all*. The signature deliberately leaves out:

```
   double  average  ( double, double, double )
   ──┬───  ───┬───    ──────────┬────────────
   return    name       parameter types
   type
   (NOT in    └──────────┬──────────┘
    the sig)         THE SIGNATURE
```

- **return type** — not in the signature
- **parameter names** — not in the signature (`double average(double x,double y, double z)` 
   and `double average(double, double, double)` have the identical signature)

#### Why "return type is not in the signature" matters

If the return type counted, these two would be different functions:

```cpp
int    parse(std::string_view text);   // returns an int
double parse(std::string_view text);   // returns a double
```

They are **not** different - they have the same signature
(`parse(std::string_view)`), so this is a **redefinition error**, not an
overload. The compiler has no way to pick between them at a call site:
`parse("42")` on its own does not say which return type you wanted.

#### What *does* let two functions share a name

A **different parameter list** - a different signature:

```cpp
int area(int side);              // signature: area(int)
int area(int width, int height); // signature: area(int, int)   ← different, OK

area(5);        // matches area(int)
area(4, 6);     // matches area(int, int)
```

That is **overloading**, covered later in the chapter. The rule of thumb: change the
*parameters* to make an overload; changing only the *return type* is not
allowed.

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
silent - no data is lost, which is why `average(4, 8, 15)` above just
works. **Narrowing** ones go the other way (`double` → `int`) and *do*
lose information, so the compiler makes you ask for them on purpose with
**`static_cast<T>(value)`**.

Say we also have a function that takes a whole number of people:

```cpp
double average(double a, double b, double c);
void   report(int headcount);          // wants an int

double mean{average(4, 8, 15)};        // 9.0

// report(mean);                       // warning / error: 9.0 → int is narrowing
report(static_cast<int>(mean));        // OK - you asked: 9.0 becomes 9
```

`static_cast<int>(mean)` means "I know this drops the fraction, do it
anyway." The fraction is **truncated toward zero, not rounded**:
`static_cast<int>(9.7)` is `9`, and `static_cast<int>(-9.7)` is `-9`.

The other everyday use is the reverse - forcing a `double` context so
integer division does not bite: 

```cpp
int total{4 + 8 + 15};                        // 27
double bad{total / 3};                        // 9    - int / int, fraction lost
double good{static_cast<double>(total) / 3};  // 9.0  - one operand is double now
```

The pattern to remember: **when a conversion might lose data, name it
with `static_cast<TargetType>(...)`** so both the compiler and the next
reader can see it was deliberate.

### Order of argument evaluation is unspecified

The compiler may evaluate a call's arguments in **any order**. If one
argument's side effect is observed by another, the result is not
portable:

```cpp
average(n++, n, n);   // which reading of n goes where? UNSPECIFIED - avoid
```

Do side-effecting work in its own statement first.

---

## 6.5 Default arguments

You can call the function without specifying some or all arguments
and the compiler will use the defaults that are burned in the function
declaration.

```cpp
std::string greet(std::string_view name,
                  std::string_view greeting = "Hello",
                  char punctuation = '!');
```

```
   greet("Sara")                 → "Hello, Sara!"
   greet("Sara", "Welcome")      → "Welcome, Sara!"
   greet("Sara", "Goodbye", '.') → "Goodbye, Sara."
```

### The rules

**1. Defaults go in the declaration, and only there.** Put them on the
prototype; the definition repeats the parameters *without* the `= ...`.

```cpp
std::string greet(std::string_view name,
                  std::string_view greeting = "Hello",   // default: here
                  char punctuation = '!');

// definition - no defaults repeated, or the compiler errors
std::string greet(std::string_view name,
                  std::string_view greeting,
                  char punctuation) {
    return std::string{greeting} + ", " + std::string{name} + punctuation;
}
```

(If a function has no separate prototype - it is defined before its first
use - then the defaults go on that definition, since it is also the
declaration.)

**2. Only trailing parameters may have a default.** Once one parameter
has a default, every parameter after it must have one too.

```cpp
void f(int a, int b = 2, int c = 3);   // OK  - defaults are trailing
void g(int a = 1, int b, int c = 3);   // ERROR - b has no default but c does
```

**3. Arguments fill left to right - you cannot skip one.** There is no
syntax for "use the default for the middle argument but pass the last."

```cpp
greet("Sara");             // name="Sara", greeting="Hello", punctuation='!'
greet("Sara", "Hi");       // name="Sara", greeting="Hi",    punctuation='!'
greet("Sara", "Hi", '?');  // all three supplied
// greet("Sara", , '?');   // ERROR - no way to skip 'greeting'
```

**4. Order the parameters so the ones most often left to default comelast.** That is what makes the short calls read well - `greet("Sara")` isthe common case, so `name` comes first and the rarely-changed
`punctuation` comes last.

---

## 6.6 Random numbers

### What we are building

In this lecture, we are exploring the **random numbers** facilities in
C++. As an excuse to explore them, we will build a simple **fortune teller** program.

```
   ┌─────────────────────────────────────────────┐
   │             THE FORTUNE TELLER              │
   │                                             │
   │   Your lucky numbers are:  73 12 45 ...     │
   │   The cards say:  "An old friend has        │
   │                    news you will want       │
   │                    to hear."                │
   └─────────────────────────────────────────────┘
             ▲                    ▲
             │                    │
       numbers in a        one entry picked
       range (1..99)       from a fixed list
```

- We need to pick random numbers in a range (1..99) for the lucky
  numbers.
- We need to pick a random index into a fixed list of fortunes, to choose
  one.

### The two pieces: engine and distribution

Modern C++ (`<random>`) provides two **entities** that work together to
produce random numbers:

- An **engine** implements a random-number generation algorithm. It
  produces a stream of numbers that **seem** random.
- A **distribution** takes the raw numbers from the engine and reshapes
  them into the range and spread you want.

REMEMBER THIS: to get a random number, you call the **distribution** and
give it the **engine** as an argument.

There is a variety of engines and distributions to choose from. For
example, `std::default_random_engine` is a good general-purpose engine,
and `std::uniform_int_distribution<int>{1, 99}` gives integers in the
range 1..99.

```
   ENGINE                         DISTRIBUTION
   ──────                         ────────────
   generates raw (non ranged)    ►    reshapes each raw number into the
   random numbers                     range and spread you asked for,
                                      fairly

   std::default_random_engine     std::uniform_int_distribution<int>{1, 99}
        │                              │
        └──────────────┬───────────────┘
                       ▼
              distribution(engine)   → one value in 1..99
```

You keep **one engine** and point as many distributions at it as you
need - one for the lucky number, another for the fortune index.

### I need a random number between 1 and 99

**You call the distribution with the engine as an argument**. Call it
again and again on the same engine and you get a sequence:

```cpp
std::default_random_engine engine{};                     // Declare the engine
std::uniform_int_distribution<int> lucky_number{1, 99};  // Declare the distribution

// A sequence of 10 lucky numbers, each in the range 1..99.
std::print("Your lucky numbers are: ");
for (int i{0}; i < 10; ++i) {
   std::print("{} ", lucky_number(engine));   // call the distribution with the engine
}
std::println("");
```

This will print something like:

```
Your lucky numbers are: 73 12 45 67 89 34 56 78 90 23
```

Picking a fortune is the same idea with a different distribution - one
that yields an **index** into a fixed list:

```cpp
constexpr std::array fortunes{
    "A pleasant surprise is waiting for you.",
    "Now is the time to try something new.",
    // ...
};
std::uniform_int_distribution<std::size_t> pick{0, fortunes.size() - 1};

std::println("The cards say: {}", fortunes[pick(engine)]);
```

PROBLEM: every time you run the program, you get the **same sequence of
numbers**.

### Different random numbers each run (`main2.cpp`)

What we want is a fresh fortune each run. We hand the engine a **seed**
value: the starting point for the sequence.

```
   engine{}          → same fortune every run        (fixed, hidden seed)
   engine{seed}      → same seed value ⇒ same fortune (fixed, YOU chose it)
   engine{rd()}      → fresh fortune every run        (seed pulled from the OS)
```

```cpp
// reproducible - a fixed seed: the same value always draws the same fortune
unsigned int seed{100};
std::default_random_engine seeded_engine{seed};
std::println("For {}, the cards say: {}", seed, fortunes[pick(seeded_engine)]);

// fresh each run - random_device is a nondeterministic source
std::random_device rd{};
std::default_random_engine fresh_engine{rd()};   // rd() produces the seed
std::println("And a fresh draw for today: {}", fortunes[pick(fresh_engine)]);
```

### A fortune-teller game

Now a fuller program. The teller greets you, then keeps asking whether to
draw. You type `y` for another fortune, anything else to leave:

```
   Welcome my child.
   Shall the cards speak? (y/n) y
     The cards say: Now is the time to try something new.
   Shall the cards speak? (y/n) y
     The cards say: The obstacle in your path is smaller than it looks.
   Shall the cards speak? (y/n) n
   Bye!
```

**A helper function.** `next_fortune()` does one job - roll an index into
the list, return the matching line as a `std::string_view`:

```cpp
std::string_view next_fortune() {
    static constexpr std::array lines{
        "A pleasant surprise is waiting for you.",
        // ...
    };
    static std::random_device rd{};
    static std::default_random_engine engine{rd()};
    static std::uniform_int_distribution<std::size_t> pick{0, lines.size() - 1};

    return lines[pick(engine)];
}
```

The engine and distribution are `static`: they survive between function
calls, so they are set up once rather than rebuilt (and restarted from
the same seed) on every call. Lecture 6.7 covers this in full.

**Enumerations** give a name to a small set of values - things like
colors, states, or modes.

Our session is either **running** or **finished**. We could track that
with a `bool`, or with numbers:

```cpp
int state{0};   // 0 means open, 1 means closed... or was it the other way round?

// later
if (state == 1) { /* ...what does 1 mean again? */ }
```

Nothing here says what `0` and `1` *mean*. A reader has to remember the
convention, and nothing stops `state = 7;`. An **enumeration** replaces the
bare numbers with names:

```cpp
enum class Session { open, closed };   // two named values, nothing else is valid

Session state{Session::open};

if (state == Session::closed) { /* clear at a glance */ }
```

`Session` is now a distinct **type**. A variable of that type can only
hold `Session::open` or `Session::closed` - the compiler rejects anything
else.

**Scoped vs unscoped.** The older form, **without** `class`, has two
problems:

```cpp
enum Color  { red, green, blue };      // unscoped
enum Fruit  { apple, banana, red };    // ERROR: 'red' already declared

int n{green};                          // compiles: green silently becomes 1
if (n == blue) { /* comparing an int to a Color, no complaint */ }
```

- The names **leak** into the surrounding scope - you write `red`, not
  `Color::red` - so two enums cannot share a name.
- The values **implicitly convert to `int`**, so nonsense comparisons and
  assignments compile without warning.

`enum class` (a **scoped** enum) fixes both:

```cpp
enum class Color { red, green, blue };
enum class Fruit { apple, banana, red };   // fine - the two 'red's are separate

Color c{Color::green};

// int n{c};                 // ERROR: no implicit conversion to int
// if (c == 1) { ... }       // ERROR: can't compare Color to int
if (c == Color::green) { }   // this is how you compare
int n{static_cast<int>(c)};  // explicit, if you really need the number (1)
```

So for `Session`:

```cpp
enum class Session { open, closed };
```

- The names live **inside** `Session`: you write `Session::open`, never a
  bare `open`. No name clashes with anything else.
- A scoped enum **does not implicitly convert to `int`**, so you cannot
  accidentally compare it to a count or a different enum.

Rule of thumb: **reach for `enum class` by default**; use a plain `enum`
only when you specifically want the integer conversion.

**The loop.** `main` keeps a `Session` and runs until it flips to
`Session::closed`:

```cpp
Session session{Session::open};
while (session == Session::open) {
    std::print("Shall the cards speak? (y/n) ");
    char answer{};
    std::cin >> answer;

    if (answer == 'y' || answer == 'Y') {
        std::println("  The cards say: {}", next_fortune());
    }
    else {
        std::println("Bye!");
        session = Session::closed;
    }
}
```

---

## 6.7 Lifetime and scope

**Scope** = where a name is visible. **Lifetime** = how long the object
exists.

| Kind            | Scope                          | Lifetime                      |
|-----------------|--------------------------------|-------------------------------|
| local variable  | its enclosing `{ }`            | until that block ends         |
| block variable  | the inner `{ }`                | until that inner block ends   |
| global variable | its declaration → end of file  | whole program                 |
| `static` local  | its function                   | whole program (created once)  |

### Hiding

An inner name **hides** an outer one of the same name:

```cpp
int high_score{1};                // global

int main() {
    int high_score{5};            // hides the global inside main
    {
        int high_score{7};        // hides both, inside this block
        std::println("{}", high_score);   // 7
    }
    std::println("{}", high_score);       // 5  (block's high_score is gone)
}
```

### `static` local

An ordinary local is **recreated every call**. A `static` local is
created **once**, on the first call, and keeps its value between calls:

```cpp
void tally_round() { int high_score{25};        ++high_score; }   // 25→26 every call
void grow_combo()  { static int high_score{50}; ++high_score; }   // 50→51, 51→52, 52→53 …
```

```
   ordinary:   call1 [25→26]   call2 [25→26]   call3 [25→26]
   static:     call1 [50→51]   call2 [51→52]   call3 [52→53]
                             (value carried across calls)
```

---

## 6.8 Passing by value and reference

### A copy is a separate variable

Copy one variable into another with `=` and you get two independent
objects that happen to hold the same value. Change one and the other is
untouched:

```cpp
int original{100};
int copy{original};           // copy gets original's VALUE, nothing more

copy = 250;                   // only the copy changes

std::println("original: {}", original);   // 100
std::println("copy:     {}", copy);        // 250
```

Print their addresses and the proof is right there - two different memory
locations:

```cpp
std::println("&original: {}", static_cast<void*>(&original));   // e.g. 0x7ffc5968e520
std::println("&copy:     {}", static_cast<void*>(&copy));       // e.g. 0x7ffc5968e524 - different!
```

`&original` and `&copy` are different addresses because `copy` is its own
object, living in its own storage. Nothing you do to `copy` can reach back
and touch `original`.

### A reference is another name for the same variable

Declare a reference with `&` in the type and it does **not** create a new
object. It binds to the existing one and becomes another name for it:

```cpp
int original{100};
int& alias{original};         // alias IS original, under a second name

alias = 250;                  // writes straight through to original

std::println("original: {}", original);   // 250 - changed!
std::println("alias:    {}", alias);       // 250
```

Print the addresses this time and they are identical:

```cpp
std::println("&original: {}", static_cast<void*>(&original));   // e.g. 0x7ffc5968e520
std::println("&alias:    {}", static_cast<void*>(&alias));      // e.g. 0x7ffc5968e520 - same!
```

Same address, because there is only **one** object. `alias` never held a
value of its own - it is just another label on `original`'s storage, so a
change through either name shows up through both.

```
   copy                              reference
   ────                              ─────────
   original ──┐                     original ──┬── alias
              │  &original          (one object)  &original == &alias
   copy ──────┘  &copy (different)
   (two objects, two addresses)     (one object, one address, two names)
```

This is the whole idea behind passing arguments to functions, too:

- **Pass by value**: the function gets a **copy** of the argument. Changes
  inside the function do not affect the caller's variable.

- **Pass by reference**: the function gets an **alias** for the caller's
  variable. Changes inside the function *do* affect the caller's variable.

### Pass by value - the function gets a copy

The parameter is a **separate copy** of the argument. The function can
scribble all over it; the caller's variable never sees it. The only way a
result gets back is through the `return`.

```cpp
double charged_copy(double balance, double fee) {
    balance -= fee;
    return balance;         // new value visible ONLY via the return
}
```

```
   caller                          charged_copy(checking, 15)
   ──────                          ──────────────────────────
   ┌───────────────────┐  copy      ┌───────────────────┐
   │ checking  100.00  │ ─────────► │ balance   100.00  │
   └───────────────────┘            └─────────┬─────────┘
             │                                │  balance -= 15
             │                                ▼
             │                      ┌───────────────────┐
             │                      │ balance    85.00  │ ── return ──┐
             │                                                        │
             ▼                                                        ▼
   checking is STILL 100.00                        the returned 85.00 is
   (the copy was thrown away)                      the caller's to use or ignore
```

### Pass by reference - the function shares the variable

Write the parameter as `T&` and it becomes an **alias**: another name for
the caller's own variable. No copy. A change through the alias *is* a
change to the original.

```cpp
void charge(double& balance, double fee) {
    balance -= fee;         // lands on the caller's variable directly
}
```

```
   caller                          charge(savings, 15)
   ──────                          ───────────────────
   ┌───────────────────┐           ┌───────────────────┐
   │ savings   100.00  │ ◄───────► │ balance  (alias)  │
   └───────────────────┘   same    └─────────┬─────────┘
             ▲             object            │  balance -= 15
             │                               │
             └───────────────────────────────┘
                     writes straight through

   savings is now 85.00   (no return needed)
```

### Which to use

- You only **read** the argument, and it is a small type (`int`,
  `double`): pass **by value** - a plain copy.
- The function must **change** the caller's variable: pass **by reference** - `T&`.

---

## 6.9 Function overloading

C++ lets **several functions share one name**, as long as they differ in
their **parameter lists**. At each call the compiler looks at the
**number, types, and order** of the arguments and selects the version
that fits. This is **function overloading**.

It exists for one idea applied to different inputs - the same reason the
standard math library ships `float`, `double`, and `long double` versions
of its functions under one name each. Overloading closely-related work
keeps the call site readable: you write `area(...)` and let the argument
say which shape.

```cpp
int    area(int side)               { return side * side; }        // square
double area(double radius)          { return 3.14159 * radius * radius; }  // circle
int    area(int width, int height)  { return width * height; }     // rectangle
```

```
   call             arguments        picked
   ────             ─────────        ──────
   area(4)      →    one int      →   area(int)            → square
   area(2.5)    →    one double   →   area(double)         → circle
   area(3, 6)   →    two ints     →   area(int, int)       → rectangle
```

### What the compiler compares: the signature

A **signature** is a function's **name plus its parameter types, in
order**. That - and only that - is what tells two overloads apart.

```
   int    area    (int, int)
   ───    ────     ──────────
    │      │           │
    │      │           └── parameter types, in order
    │      └── name
    └── return type — NOT part of the signature
```

Consequences:

- **The return type alone cannot distinguish overloads.** `int area(int)`
  and `double area(int)` in the same program is a compile error - the
  call `area(4)` gives the compiler no way to choose. Overloads *may*
  have different return types, but only when their parameter lists also
  differ.
- **Overloads need not take the same number of parameters** - `area(int)`
  and `area(int, int)` above.
- If no overload matches exactly, the compiler tries conversions to find
  the best one. If two are equally good, that is an **ambiguous call** -
  a compile error, not a silent pick.
- A parameterless function and an all-defaults overload **clash** when
  called with no arguments:

  ```cpp
  void reset();                 // (a)
  void reset(int level = 0);    // (b)
  reset();                      // ERROR: ambiguous - (a) or (b) with its default?
  ```

### Type-safe linkage and name mangling

The compiler enforces overloading by **encoding each function's name
together with its parameter types** into a single internal symbol - **name mangling**. 
The linker then only ever sees distinct names, so the overloads cannot collide.

```
   your code                    GNU C++ mangled symbol
   ─────────                    ──────────────────────
   int    area(int)        →    _Z4areai
   double area(double)     →    _Z4aread
   int    area(int, int)   →    _Z4areaii

   breaking down  _Z4areai :

      _Z     4              area      i
      ───    ───            ────      ─────────────────────────
      tag    length of      the       parameter-type codes,
             the name       name      in order:
             (how many                i = int   d = double
             chars follow             c = char  f = float
             before the               Ri = int&   Rd = double&
             type codes)
```

That number is the **character count of the function name** - it tells
the demangler how many of the following characters are the name before
the parameter codes start. `area` is 4 chars, so `_Z4area...`; `square`
would be `_Z6square...`.

`main` is the exception - it is never mangled.

**This encoding is compiler-specific.** GNU C++ produces `_Z4areai`;
MSVC produces something like `?area@@YAHH@Z` for the same function.
Everything linked into one program must therefore be built with the same
compiler (and settings), or the symbols will not match up.

### This is only the start

What we have seen here - overloading on the **number** and **plain type**
of parameters - is the everyday case, but the parameter list can differ
in more ways than that. As the course goes on and the type system grows,
you will see the same name overloaded on:

- **by value vs. by reference**: `f(Widget)` vs. `f(Widget&)`
- **pointer vs. reference vs. value**: `f(Widget*)`, `f(Widget&)`, `f(Widget)`
- **`const`-ness**: `f(const std::string&)` vs. `f(std::string&)`, and
  `const` vs. non-`const` member functions
- **lvalue vs. rvalue**: `f(const T&)` vs. `f(T&&)` - the basis of move
  semantics

Each of these is a distinct signature, so each is a valid overload. Come
back to this section once those types are on the table; the resolution
rules are the same, there are just more ways for two signatures to
differ.

---

## 6.10 Const variables and parameters

In this lecture, we are zooming in on the `const` keyword in the context of 
free standing variables and even functions.

### Const standalone variables

```cpp
const int max_players{4};
int current_players{1};   // NOT const - this one is meant to change
```

`const` is a compiler-enforced promise: 
**this variable's value will not change after initialization.** If you try to assign to it later, the
compiler will  rejects the change and trow a compiler error. 

```
   const int max_players{4};
   max_players = 5;
        │
        ▼
   COMPILE ERROR: cannot assign to variable 'max_players'
                  with const-qualified type 'const int'

   int current_players{1};
   current_players = 2;
        │
        ▼
   fine - current_players was never const
```

### Const function parameters - by value

```cpp
int square_by_value(const int x) {
    // x = x + 1;   // would not compile
    return x * x;
}
```
FRIENDLY NOTE: 
**`const` on a by-value parameter does not protect the caller's variable.** 
It never could - pass-by-value already makes a fresh **copy** the instant the function is
called, so the caller's original was never reachable from inside the function, `const` or not.

```
   caller                          square_by_value(n)
   ──────                          ───────────────────
   ┌──────────┐        copy         ┌──────────┐
   │ n   6    │ ─────────────────►  │ x   6    │   const on x protects
   └──────────┘                     └──────────┘   THIS copy from being
        │                                 │         reassigned INSIDE
        │ untouched no matter                the function body -
        │ what happens to x                  n was never at risk,
        ▼                                     with or without const
   n is still 6
```

What `const` *does* protect is the function's own local copy from an
**accidental** reassignment inside its own body.

### Const function parameters - by reference

```cpp
void print_label(const std::string& label) {
    // label += "!";   // would not compile
    std::println("label: {}", label);
}
```

A reference parameter is an **alias** for the caller's own object - no
copy is made. Changes done through the reference would affect the original
argument that was passed. **const** is doing **real** protection here.

```
   caller                          print_label(name)
   ──────                          ──────────────────
   ┌────────────┐      alias        ┌────────────┐
   │ name  "Ada"│ ◄───────────────► │ label      │   const on label means
   └────────────┘      same         └────────────┘   the function CANNOT
        ▲              object              │           write through this
        │                                  │           alias back into
        └──────────────────────────────────┘           the caller's own
                writes through label WOULD land               string
                on the caller's name - const rules
                this out
```

NOTE: Combining `const` with `&` gets both things at once: the no-copy speed
of a reference, and the safety of pass-by-value. 

### Constexpr variables: compile-time, not just unchanging

`const` says a value will not change after it is set - but that value
can still come from somewhere only known while the program is *running*:

```cpp
const int seed{current_players * 7};   // fine: computed from a runtime value
```

`constexpr` demands more: the compiler must be able to compute the value
**itself, while compiling** - before the program ever runs.

```cpp
constexpr int board_size{8 * 8};       // fine: knowable right now
// constexpr int bad_seed{current_players * 7};   // would NOT compile
```

```
   const int seed{current_players * 7};
        │
        └─ current_players is a runtime value - fine for const,
           because const only promises "won't change AFTER this point"

   constexpr int bad_seed{current_players * 7};
        │
        └─ COMPILE ERROR: constexpr variable 'bad_seed' must be
           initialized by a constant expression
           (current_players is not known until the program runs)
```

Every `constexpr` value is also implicitly `const` - immutability is
part of the deal - but not every `const` value is `constexpr`. `const`
is about the promise *after* initialization; `constexpr` is about *when*
the value can be computed.

### Constexpr functions: compile time when possible, runtime otherwise

```cpp
constexpr int cube(int x) {
    return x * x * x;
}
```

A `constexpr` function **can** run at compile time - but only when every
argument it is called with is itself known at compile time. Called with
a runtime value, the exact same function just runs normally, like any
other function:

```cpp
constexpr int compile_time_cube{cube(3)};   // 3 is a literal
int runtime_cube{cube(side)};               // side is a runtime value
```

```
   cube(3)                              cube(side)
   ───────                              ──────────
   3 is a literal - known               side is only known once
   right now, while compiling            the program is running
        │                                      │
        ▼                                      ▼
   compiler evaluates cube(3)            ordinary function call,
   ITSELF; 27 lands in the               happens at run time,
   binary - no runtime cost              same result either way
```

### A brief word on `consteval` and `constinit` (C++20)

Two more C++20 keywords sit near `constexpr`, worth recognizing even
without a dedicated example here:

- **`consteval`** - like `constexpr`, but stronger: a `consteval`
  function *must* run at compile time, every time, with no runtime
  fallback. Calling it with a value only known at runtime is a compile
  error, not a graceful drop to ordinary execution.
- **`constinit`** - just know it exists. Will explore later. 

```
   const        constexpr        consteval           
   ─────        ─────────        ─────────           
   value fixed  value fixed,     FUNCTION must       
   after init,  computed at      run at compile     
   value itself compile time     time - no         
   may be a     (implies const)  runtime fallback 
   runtime                       allowed         
   value                                        
```

---

## 6.11 Functions across files

In this lecture, we are introducing a way to spread your code across several files.

```
   6.11FunctionsAcrossFiles/
   ├── geometry.h      circle_area(), circle_circumference()   ← declarations
   ├── geometry.cpp    ... their bodies                        ← definitions
   ├── money.h         add_tax(), apply_discount()             ← declarations
   ├── money.cpp       ... their bodies                        ← definitions
   ├── main.cpp        #include "geometry.h"  #include "money.h"
   └── CMakeLists.txt
```

### Header and source

The main idea is to **split the declaration from the definition**. We store 
the **declarations** in a **header** (`.h`) and the **definitions** in a **source** (`.cpp`). 

```
   geometry.h                       geometry.cpp
   ──────────                       ────────────
   #pragma once                     #include "geometry.h"

   double circle_area(double r);    double circle_area(double r) {
   double circle_circumference(         return pi * r * r;
                    double r);      }
                                    double circle_circumference(double r) {
   the DECLARATIONS - what a            return 2 * pi * r;
   caller needs to compile         }

                                    the DEFINITIONS - the actual work
```

- The **header** (`.h`) holds declarations. Anyone who wants to call
  these functions `#include`s it.
- The **source** (`.cpp`) holds the definitions. It `#include`s its own
  header too, so the compiler checks the bodies against the promises.

### Include guards

`#include` is a blind text paste (next section). If one `.cpp` pulls in
the same header **twice** - usually indirectly, `main.cpp` includes `a.h`
and `b.h`, and both of those include `common.h` - the header's contents
land in that file twice. For declarations that is harmless; for anything
that can only appear once (a `struct` definition, an `enum`, a
`constexpr` variable) the second copy is a **redefinition error**.

An **include guard** makes a header paste its body **at most once per
file**. Two ways to write one:

**1. `#pragma once`** - one line at the very top. Every mainstream
compiler supports it; it is what we use now.

```cpp
// geometry.h
#pragma once

double circle_area(double radius);
double circle_circumference(double radius);
```

**2. The `#ifndef` / `#define` / `#endif` trio** - the portable classic,
guaranteed by the standard. Wrap the whole file in a check on a macro
name unique to that header:

```cpp
// geometry.h
#ifndef GEOMETRY_H
#define GEOMETRY_H

double circle_area(double radius);
double circle_circumference(double radius);

#endif  // GEOMETRY_H
```

How it works: the first `#include` finds `GEOMETRY_H` undefined, defines
it, and processes the body. Any later `#include` in the **same** file
finds `GEOMETRY_H` already defined and skips straight to `#endif`.

```
   main.cpp
   ├─ #include "a.h"  ──► a.h  ──► #include "common.h"   GEOMETRY_H undefined → paste body, #define it
   └─ #include "b.h"  ──► b.h  ──► #include "common.h"   GEOMETRY_H defined    → skip to #endif
```

Pick one, not both. `#pragma once` is shorter and has no name to clash;
the `#ifndef` form works on the rare compiler that lacks `#pragma once`
and shows exactly what the mechanism is. The macro name must be unique -
`GEOMETRY_H` for `geometry.h`, `MONEY_H` for `money.h`.

### `#include` is copy-paste

`#include "geometry.h"` is not a link or an import. The preprocessor
literally **pastes the text of `geometry.h`** into `main.cpp` at that
line, before the compiler proper runs. After that paste, `main.cpp`
contains the declarations, so every call in it can be type-checked.

```
   main.cpp  (what the compiler actually sees, after preprocessing)
   ┌─────────────────────────────────────────┐
   │ double circle_area(double r);           │ ← pasted from geometry.h
   │ double circle_circumference(double r);   │
   │ double add_tax(double, double);          │ ← pasted from money.h
   │ double apply_discount(double, double);   │
   │                                         │
   │ int main() {                            │
   │     ... circle_area(2.0) ...            │ ← checks against the pasted decl
   │ }                                       │
   └─────────────────────────────────────────┘
```

The bodies are **not** here. The compiler emits `main.o` with the calls
left as **unresolved references** - "someone provides `circle_area`, fill
this in later."

### Separate compilation, then linking

Each `.cpp` is a **translation unit**, compiled on its own into an
**object file** (`.o` / `.obj`). The **linker** then stitches the object
files together, matching each unresolved reference to the definition that
supplies it.

```
   geometry.cpp ──compile──► geometry.o ─┐
   money.cpp    ──compile──► money.o   ──┼──link──► rooster (executable)
   main.cpp     ──compile──► main.o    ──┘
                              │            ▲
                    main.o needs           │
                    circle_area, add_tax  linker finds them
                    (unresolved)          in geometry.o / money.o
```

Two failure modes worth recognising:

- **Compile error** - a call in `main.cpp` does not match any
  declaration it can see (wrong argument count, typo in the name). Caught
  per file, before linking.
- **Linker error: "undefined reference to `circle_area`"** - the call
  type-checked (the declaration was there) but no object file defined it.
  Usually means the `.cpp` was left out of the build.

### Telling CMake about the extra files

`add_executable` lists **every `.cpp` that contributes code**. Miss one
and you get the linker error above.

```cmake
add_executable(rooster
    main.cpp
    geometry.cpp
    money.cpp
    geometry.h      # headers are optional here - listing them only makes
    money.h         # IDEs show them in the project tree; they are not compiled
)
```

CMake compiles each listed `.cpp` separately and links the results - the
pipeline in the diagram above.

### A first look at linkage

Why can a call in `main.cpp` reach a function defined in `geometry.cpp`
at all? Because an ordinary function has **external linkage**: its name
is published in its object file for the linker to see, and any other
translation unit that declares the same name links to it.

```
   external linkage   name is visible to the LINKER, across .cpp files
                      → ordinary functions and globals. This is the
                        default, and what makes multi-file programs work.

   internal linkage   name is private to its own .cpp - other files
                      cannot link to it even if they declare it
                      → marked with `static` at file scope, or put in an
                        unnamed namespace

   no linkage         local variables - not a linker concept at all
```

That is the whole idea you need here: **functions are external by
default, which is what lets you split them across files.** The full rules
about linkage will be covered later in the course.

---

## 6.12 Files in subfolders

The same four helpers, but now organised into folders by area:

```
   6.12FilesNested/
   ├── geometry/
   │   ├── geometry.h
   │   └── geometry.cpp
   ├── finance/
   │   ├── money.h
   │   └── money.cpp
   ├── main.cpp
   └── CMakeLists.txt
```

`main.cpp` is unchanged - it still says:

```cpp
#include "geometry.h"
#include "money.h"
```

no `geometry/` prefix. For that to compile, the compiler has to be told
where to look.

### The header search path

When the preprocessor hits `#include "geometry.h"` it searches a list of
folders **in order** and pastes the first match:

```
   #include "geometry.h"
        │
        ▼
   1. the folder of the file doing the #include   (here: 6.12FilesNested/)
   2. every folder added by -I on the compiler command line
   3. the system/standard-library folders
        │
        ▼
   not found in any → #error: geometry.h: No such file or directory
```

Out of the box, step 1 looks next to `main.cpp` and finds nothing -
`geometry.h` is one level down in `geometry/`. We need to add
`geometry/` and `finance/` to the step-2 list.

### `target_include_directories`

CMake's `target_include_directories` adds folders to that search path for
one target - it becomes `-I<folder>` on every compile of that target.

```cmake
target_include_directories(rooster PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/geometry
    ${CMAKE_CURRENT_SOURCE_DIR}/finance
)
```

```
   compiling main.cpp, the compiler is now invoked as:

     c++ ... -I .../6.12FilesNested/geometry
             -I .../6.12FilesNested/finance
             -c main.cpp

   so #include "geometry.h"  →  .../geometry/geometry.h    ✓
      #include "money.h"      →  .../finance/money.h        ✓
```

- **`${CMAKE_CURRENT_SOURCE_DIR}`** is the folder containing this
  `CMakeLists.txt`, so the paths work no matter where the project is
  checked out.
- **`PRIVATE`** means "for building `rooster` only." (The other scopes,
  `PUBLIC` and `INTERFACE`, matter when a target is a library that other
  targets link against - not our case here.)

### The alternative: path in the `#include`

You can skip `target_include_directories` and write the path instead:

```cpp
#include "geometry/geometry.h"
#include "finance/money.h"
```

This resolves by step 1 alone (relative to `main.cpp`). It is fine for a
small project. The include-path approach wins once many files in many
folders include each other: every file uses the bare name, and moving a
header to a different folder is a one-line CMake change instead of an
edit to every `#include` that mentions it.

The `.cpp` paths in `add_executable` are always relative to the
`CMakeLists.txt` and are not affected by any of this:

```cmake
add_executable(rooster
    main.cpp
    geometry/geometry.cpp
    finance/money.cpp
)
```

---

## 6.13 Function templates

In this lecture we are going to explore how you can set up blueprints for functions.

Assume you need a function to check and see if a **value is within two bounds** for `int`, 
for `double`, for `char`. One solution to this is **Overloading** as we have seen in a 
previous lecture. That means writing the same body three times:

```cpp
bool in_range(int    v, int    lo, int    hi) { return lo <= v && v <= hi; }
bool in_range(double v, double lo, double hi) { return lo <= v && v <= hi; }
bool in_range(char   v, char   lo, char   hi) { return lo <= v && v <= hi; }
```

A **function template** writes it **once, with the type left blank**:

```cpp
template <typename T>
bool in_range(T value, T low, T high) {
    return low <= value && value <= high;
}
```

`T` is a placeholder. It is not a function yet - it is a **recipe** for
making one.

### Instantiation: the compiler stamps out a version per call

At each call the compiler **deduces `T`** from the argument types and
**instantiates** the template - generates a concrete function with `T`
replaced throughout - then compiles that.

```
   your call                deduced        the compiler generates
   ─────────                ───────        ──────────────────────
   in_range(5, 1, 10)    →   T = int    →   bool in_range<int>(int, int, int)
   in_range(2.5,0.,1.)   →   T = double →   bool in_range<double>(double, double, double)
   in_range('g','a','m') →   T = char   →   bool in_range<char>(char, char, char)
```

Each distinct `T` produces its own function in the final program - the
same set you would have hand-written as overloads, just generated.

- **All arguments tied to `T` must agree.** `in_range(5, 1, 10.0)` -
  `int, int, double` - gives the compiler two candidates for one `T`, so
  deduction fails. Fix by making them match, or state the type:
  `in_range<double>(5, 1, 10)` (the `int`s then convert to `double`).
- **The body must compile for the `T` you use.** `in_range` needs `<=`
  to work on `T`; fine for the numeric types, `char`, `std::string`. Call
  it on a type without `<=` and the error points *into the template body*
  at the offending line.

### Where the template must live: a header

An ordinary function can be **declared** in a header and **defined** in
one `.cpp` - the linker joins the two. A template cannot work that
way, and the reason follows straight from instantiation:

> The compiler can only instantiate `in_range<int>` at a spot where it
> can **see the template body**.

So the body must be visible in **every `.cpp` that calls the template**.
In practice: put the whole template in a **header** and `#include` it
wherever it is used.

```
   in_range.h                       main.cpp
   ──────────                       ───────
   #pragma once                     #include "in_range.h"   ← body pasted in

   template <typename T>            int main() {
   bool in_range(T v, T lo, T hi) {     ... in_range(5, 1, 10) ...
       return lo <= v && v <= hi;           │
   }                                        └─ compiler has the body here,
                                               so it instantiates in_range<int>
```

### What goes wrong if you put the body in a `.cpp`

Split it like an ordinary function - declaration in `in_range.h`, body in
`in_range.cpp` - and it compiles but **fails to link**:

```
   in_range.h     template <typename T> bool in_range(T,T,T);   ← declaration only
   in_range.cpp   #include "in_range.h"
                  template <typename T>
                  bool in_range(T v,T lo,T hi){ return lo<=v && v<=hi; }

        compile in_range.cpp ──►  in_range.o
                                  │
                                  └─ no call to in_range in this file
                                     → nothing to instantiate
                                     → in_range.o contains NO in_range<int>

        compile main.cpp     ──►  main.o
                                  │
                                  └─ sees the declaration, call type-checks,
                                     leaves an unresolved reference

        link  main.o + in_range.o ──►  ERROR
               undefined reference to `bool in_range<int>(int, int, int)`
```

`in_range.cpp` had the body but no reason to stamp out any version;
`main.cpp` needed `in_range<int>` but never saw the body. Neither object
file ends up with the function.

Keeping the whole template in the header sidesteps this: every `.cpp`
that calls it gets the body and instantiates what it needs. (If two
`.cpp`s both instantiate `in_range<int>`, that is *not* an ODR violation
- the compiler marks template instantiations so the linker silently
folds the duplicates into one.)

---

## 6.14 Lambda functions

A **lambda** is a function written **inline** - defined right where you
need it, with no name and no separate declaration. It exists because many
functions (`std::sort`'s comparison, a "what to do with each element"
step) are used **once**, next to the call, and giving each a top-level
name just adds noise.

### The shape

```
   [ capture ] ( parameters ) -> return  { body }
   └────┬────┘  └────┬─────┘   └───┬───┘   └─┬─┘
        │            │             │         │
        │            │             │         the code to run
        │            │             optional - usually deduced
        │            same as any function's parameter list
        │
        which surrounding variables the body may use
        (the part that makes a lambda more than a plain function)
```

### A lambda is an object

`[](int a, int b) { return a + b; }` is an **expression** - it evaluates
to an unnamed function-like **object** you can store, copy, and call:

```cpp
auto add = [](int a, int b) { return a + b; };   // store it
add(3, 4);                                        // call it - 7
```

```
   auto add = [](int a, int b){ return a + b; };
        │                    │
        │                    └── this whole thing is a value
        └── ...bound to a variable, like `int x = 5;` binds a value

   add        ─ a callable object
   add(3, 4)  ─ invoke it, same syntax as any function call
```

`auto` is doing real work here: every lambda has its own compiler-made
type with no spelling you could write out, so you cannot name it - you
let `auto` hold it (or `std::function`, later in the course).

### Define and call in one step

Because the lambda literal is an expression, you can put an argument list
`( )` right after it and call it **on the spot** - no variable, no name:

```cpp
int difference{ [](int a, int b) { return a - b; }(10, 4) };
//              └──────────────┬──────────────────┘└──┬──┘
//                       the lambda              call it now,
//                                               a = 10, b = 4
```

```
   [](int a, int b){ return a - b; } (10, 4)
   └───────────────┬───────────────┘ └──┬──┘
        makes the lambda object      invoke it immediately with
                                     these arguments → 10 - 4 → 6
```

Useful when a variable needs a few lines of setup to compute its value:
wrap the setup in a lambda, call it once with whatever inputs it needs,
and the result initialises the variable - keeping the scratch work out of
the surrounding scope. (This is sometimes called an *immediately-invoked lambda*.)

### Captures: reaching outside the body

A lambda's parameters cover what the **caller** passes in. **Captures**
cover variables from the **surrounding scope** that the body wants to use.
List them in the `[ ]`.

```cpp
int offset{10};

auto shift_val = [ offset ](int n) { return n + offset; };   // by value
auto shift_ref = [&offset ](int n) { return n + offset; };   // by reference
```

**By value** - the lambda stores its **own copy**, taken when the lambda
is created. Later changes to the original do not reach it:

```
   int offset{10};
   auto shift = [offset](int n){ return n + offset; };
                   │
                   └── copy made NOW → the lambda carries offset = 10

   offset = 999;          ← changes the outer variable only
   shift(5);              → 5 + 10  = 15   (still the snapshot)

   outer:   offset  ┌────┐            lambda's copy:  ┌────┐
                    │999 │                            │ 10 │
                    └────┘                            └────┘
                       (independent from here on)
```

**By reference** - the lambda stores a **link** to the original. It sees
later changes, and its writes land on the original:

```
   int total{0};
   auto add_to = [&total](int n){ total += n; };
                    │
                    └── link, not a copy

   add_to(3);   ─┐
   add_to(4);   ─┴─► both write through the link

   outer:   total ◄──────────── lambda's &total
            ┌────┐   same object
            │ 7  │
            └────┘
```

### Capture-list shorthands

```
   [x]     just x, by value        [&x]   just x, by reference
   [x, &y] x by value, y by reference   ← mix freely
   [=]     everything the body uses, by value    (each one snapshotted)
   [&]     everything the body uses, by reference (each one linked)
   [ ]     capture nothing - body may only touch its parameters
```

```
                     copy in?              sees later changes?   can modify original?
   ────────────────  ───────────────────   ──────────────────    ───────────────────
   [x]  / [=]        yes, at creation      no                    no (copy is const-ish)
   [&x] / [&]        no, stores a link     yes                   yes
```

A **`[&]` capture is only safe while the captured variable is still alive.** 
If the lambda outlives the scope it captured from - stored in a
container, returned from a function - a `[&]` link becomes dangling.
Prefer `[=]` (or naming exactly what you need) for a lambda that travels.

### Where lambdas make most sense: passing a callable

Standard-library algorithms take a **callable** that decides ordering,
which elements match, what to do with each. A lambda at the call site is
the normal way to supply it - the logic sits right where it is used:

```cpp
std::vector<int> v{5, 2, 8, 1, 9, 3};

std::ranges::sort(v, [](int a, int b) { return a > b; });
//                │  └──────────────┬───────────────┘
//                │           "a comes before b when a > b"  → DESCENDING
//                └── the whole container - no begin()/end() pair
```

`std::ranges::sort` *(C++20)* takes the **container itself**. The older
`std::sort(v.begin(), v.end(), ...)` needs a start/end iterator pair;
`ranges::sort(v, ...)` is the same call with that boilerplate gone.

```
   ranges::sort walks the range and, whenever it must order two elements,
   calls your lambda:

      compare(5, 2) → 5 > 2 → true  → 5 before 2
      compare(8, 1) → true          → 8 before 1
      ...
   {5, 2, 8, 1, 9, 3}  ──sort with `a > b`──►  {9, 8, 5, 3, 2, 1}
```

The comparison slot takes any callable - a named function, a lambda, a
functor (later chapter). The lambda just spares you naming a one-use
comparison.

---

## 6.15 Recursion

A **recursive** function calls itself. Every one needs two parts:

- a **base case** - a plain answer it returns *without* recursing. This
  stops the chain.
- a **recursive step** - it calls itself with an argument **closer to the
  base case**, and builds its answer from what that call returns.

```cpp
long sum_to(int n) {
    if (n <= 0) { return 0; }        // base case
    return n + sum_to(n - 1);        // recursive step - n, then the rest
}
```

`sum_to(n)` reads as its own definition: "the sum up to `n` is `n` plus
the sum up to `n - 1`, and the sum up to `0` is `0`."

### Following a call: the wind-down and the wind-up

A recursive call goes **down** to the base case, then the returns come
**back up**, each level finishing its `n + ...` with the value it got:

```
   sum_to(4)
   │  return 4 + sum_to(3)
   │             │  return 3 + sum_to(2)
   │             │             │  return 2 + sum_to(1)
   │             │             │             │  return 1 + sum_to(0)
   │             │             │             │             │  return 0   ← base case
   │             │             │             │             ▼
   │             │             │             │  1 + 0  = 1
   │             │             │  2 + 1  = 3
   │             │  3 + 3  = 6
   │  4 + 6  = 10
   ▼
   10
```

Going down, nothing is added yet - each `n +` is **pending**, waiting on
the call below it. The additions only happen on the way back up.

### Each pending call is a stack frame

Those pending calls are not free. Every one is a live **stack frame**
- its own `n`, its own "return here" address - and they all sit on
the stack **at the same time**, until the base case lets them unwind.

```
   sum_to(4) running, at the deepest point:

        stack grows ↓
   ┌───────────────────────────┐
   │ sum_to(0)   n=0           │  ← base case, about to return 0
   ├───────────────────────────┤
   │ sum_to(1)   n=1   waiting │
   ├───────────────────────────┤
   │ sum_to(2)   n=2   waiting │
   ├───────────────────────────┤
   │ sum_to(3)   n=3   waiting │
   ├───────────────────────────┤
   │ sum_to(4)   n=4   waiting │
   ├───────────────────────────┤
   │ main()                    │
   └───────────────────────────┘

   depth of the recursion  =  number of frames stacked  =  memory used
```

`sum_to(4)` stacks 5 frames. `sum_to(100000)` stacks 100000 - and the
stack has a fixed size (often ~1 MB). Run out of room and the program
dies with a **stack overflow**: the recursive cousin of an infinite
loop. It happens when the base case is missing, unreachable, or just
very far away.

### When the tree fans out: `fibonacci`

The **Fibonacci sequence** starts with `0, 1`, and every number after
that is the **sum of the two before it**:

```
   index n:   0   1   2   3   4   5   6   7   8    9   10
   fib(n):    0   1   1   2   3   5   8  13  21   34   55
              └─┬─┘   │
              the two │ 0 + 1
              starts  └────────┐
                    1 + 1 = 2  │  2 + 3 = 5  ...  each term = sum of the two on its left
```

Written as a recursion, that definition drops straight in - `fib(0)` and
`fib(1)` are the two base cases, and every other term is `fib(n-1) +
fib(n-2)`. Note that is **two** recursive calls per step:

```cpp
long fibonacci(long n) {
    if (n == 0 || n == 1) { return n; }          // two base cases
    return fibonacci(n - 1) + fibonacci(n - 2);   // TWO calls
}
```

The stack depth is only about `n` (one branch runs fully before the
other starts), but the **total number of calls** explodes, because the
same values get recomputed on every branch:

```
                     fib(5)
              ┌─────────┴─────────┐
           fib(4)               fib(3)
        ┌────┴────┐           ┌────┴────┐
     fib(3)     fib(2)     fib(2)     fib(1)
    ┌──┴──┐    ┌──┴──┐    ┌──┴──┐
 fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)
 ┌─┴─┐
fib1 fib0

   fib(5): 15 calls.   fib(10): 177.   fib(20): 21891.
   fib(n): grows like 2ⁿ.   fib(40) is over 300 million calls.
```

`fib(3)` alone is computed 3 times here. Nothing is *wrong* with the
code - it just does exponential work for a problem a loop does in `n`
steps.

### Recursion vs iteration

Any recursion can be rewritten as a loop. `sum_to`, both ways:

```cpp
long sum_to(int n) {                      // recursive
    if (n <= 0) { return 0; }
    return n + sum_to(n - 1);
}

long sum_to_iterative(int n) {            // iterative
    long total{0};
    for (int i{1}; i <= n; ++i) { total += i; }
    return total;
}
```

```
                  recursion                      iteration
   ──────────  ─────────────────────────────  ──────────────────────
   stack use    one frame per level of depth   one frame, always
                → deep input can overflow
   speed        a call + return every step      just the loop body
                (setup/teardown overhead)      → usually faster
   state        held implicitly in the         held in explicit
                pending frames                 variables (accumulator)
   reads well   for things defined in terms    for counting and
                of themselves - trees,         accumulating over a
                divide-and-conquer, parsing    range
```

**Rule of thumb: iterate by default. Reach for recursion when the
problem is itself recursive** - walking a tree, `x^n` as `x * x^(n-1)`,
splitting a range in half - and the recursive version is the one that
reads clearly. Even then, watch the depth.

---

## 6.16 Intro to C++ attributes

An **attribute** is a note to the compiler, written in 
**double square brackets**: `[[name]]` or `[[name("some text")]]`. 
It does **not change what the code computes**. It tells the compiler 
something extra about a function, a variable, or a statement, so 
the compiler can **warn you better** (or, for a couple of them, optimise better).

```
   [[nodiscard]] bool username_is_available(std::string_view name);
   └─────┬─────┘ └──────────────────────┬───────────────────────┘
      the note        the thing it is attached to
```

Where an attribute can sit:

```
   [[nodiscard]] int f();          ← on a function
   [[maybe_unused]] int x{0};      ← on a variable
   [[deprecated]] void old_api();  ← on a function
   switch (t) {
       case A:
           step();
           [[fallthrough]];         ← on a statement, inside a switch
       case B:
           ...
   }
```

You do not need to memorise every attribute. Learn what the `[[...]]`
**shape** means - "hint to the compiler" - and the three below, and you
can look up any others you meet.

### `[[nodiscard]]` - don't throw the return value away

The reason to call the function **is** its return value. If a caller
ignores it, that is almost always a bug, so the compiler warns.

```cpp
[[nodiscard]] bool username_is_available(std::string_view name);

bool free{username_is_available("neo")};   // result used - fine
username_is_available("neo");               // ⚠ warning: [[nodiscard]] result ignored
```

```
   compiler sees a call to a [[nodiscard]] function
        │
        ├─ result is stored / tested / passed on   → fine
        └─ result is dropped on the floor           → emit a warning
```

Since C++20 you can attach a reason, which appears in the warning text:

```cpp
[[nodiscard("check the result before saving the profile")]]
bool profile_is_complete(std::string_view name, int age);
```

Good on: pure computations, functions that report success/failure, and
functions that hand back a resource the caller must deal with.

### `[[maybe_unused]]` - "unused on purpose, don't warn"

Compilers warn about a variable, parameter, or function that is never
used - usually a real mistake. When it is **deliberate** (a value kept
only for debugging, a parameter an interface forces you to accept),
`[[maybe_unused]]` silences that one warning without silencing the
others.

```cpp
[[maybe_unused]] bool verbose_logging{true};   // referenced only in debug builds

int handle(int request, [[maybe_unused]] int flags) {   // flags ignored for now
    return request * 2;
}
```

```
   without it :  warning: unused variable 'verbose_logging'   ← noise you learn to ignore
   with it    :  (silent)  ← and the warnings that DO matter stay visible
```

### `[[deprecated]]` - "still works, but stop using it"

Mark an old function (or type, or variable) `[[deprecated]]`. It keeps
working, but **every use produces a warning**. The optional message
points people at the replacement - this is how libraries retire an API
without breaking existing code overnight.

```cpp
[[deprecated("use display_name() instead")]]
std::string full_name(std::string_view first, std::string_view last);

std::string display_name(std::string_view first, std::string_view last);
```

```cpp
full_name("Thomas", "Anderson");
// ⚠ warning: 'full_name' is deprecated: use display_name() instead
```

```
   deprecated function still compiles and runs
        └─ but each call site gets a warning nudging you to move off it
```

### Others you may spot

You do not need these yet - just recognise them as the same idea, a hint
to the compiler:

```
   [[fallthrough]]              in a switch: "the missing break here is intentional"
                               (stops the compiler's fall-through warning)
   [[noreturn]]                 on a function that never returns to its caller -
                               it calls std::exit, throws, or loops forever
   [[likely]] / [[unlikely]]    tag the common / rare branch of an if or switch;
                               a pure optimisation hint, no effect on behaviour
```

An attribute the compiler does not recognise is **ignored**, not an
error - so an unknown `[[something]]` in code you read is safe to move
past and look up later.

---

## 6.17 Project: writing an image

Now is the time to do a fun project. We'll write a program that
**draws a picture and saves it to a file**. The picture will have
the following features: 
- A width of 400 and a height of 300
- A color gradient gradually going from one color to an other on the x axis
- A 8-px frame or border
- We'll write it in memory and save it to a file.

```
   ┌───────────────────────────────────┐   width  = 400
   │███████████████████████████████████│   height = 300
   │██                               ██│
   │██   blue ───────────► orange    ██│   gradient across x
   │██                               ██│
   │██        (8-px white frame)     ██│
   │███████████████████████████████████│
   └───────────────────────────────────┘
```

### A quick word on `std::vector`

We need to hold a lot of bytes - one big run of them - and we do not know
`width * height * 3` until the program runs. A raw array will not do
that. **`std::vector<T>`** is the standard **growable collection**: a
sequence of `T` values, all of one type, stored back-to-back, sized at
run time. It gets a proper chapter later; here is the 1% you need now.

```cpp
#include <vector>

std::vector<int> v{10, 20, 30};   // a vector of 3 ints

v.size();      // 3      - how many elements
v[0];          // 10     - element access by index, 0-based
v[2] = 99;     // set element 2
v.push_back(40);   // append - v is now {10, 20, 99, 40}, size 4

// make one of a given size, every element the same value:
std::vector<std::uint8_t> bytes(36, 0);   // 36 bytes, all 0
```

```
   std::vector<std::uint8_t> bytes(36, 0);

   index:   0    1    2    3    4    ...                        35
          ┌────┬────┬────┬────┬────┬─────────────────────────┬────┐
   bytes: │ 0  │ 0  │ 0  │ 0  │ 0  │  ...all zero...         │ 0  │
          └────┴────┴────┴────┴────┴─────────────────────────┴────┘
             ▲                                                  ▲
          bytes[0]                                        bytes[35]
          (bytes.data() points here - the address of the first element)
```

`bytes.data()` hands back a pointer to that first byte - which is how we
give the whole block to a file writer in one call, later.

### A quick word on the types: `std::uint8_t` and `std::size_t`

We are about to use two types some of you may not be familiar with: 
`std::uint8_t` for colour bytes and `std::size_t` for the vector index.
Neither is a new *kind* of type - both are just **aliases for built-in
integer types you already know**, arguably given clearer names.

**`std::uint8_t`** (from `<cstdint>`) means "an **u**nsigned **int**eger
exactly **8** bits wide" - so its range is `0` to `255`.

```cpp
#include <cstdint>

std::uint8_t red{255};        // same object as:  unsigned char red{255};
```

We use `std::uint8_t` instead of `unsigned char` for two reasons.
First, **intent**: `unsigned char` reads like text handling; a pixel
channel is a small number, and `uint8_t` says "one byte of data, 0-255"
out loud. Second, **the range is guaranteed in the name** - `char` is
only *required* to be at least 8 bits, and whether plain `char` is
signed is compiler-dependent; `std::uint8_t` pins both down. 

Related fixed-width aliases, all from `<cstdint>`, all just renamings of
built-in types:

```
   std::uint8_t   std::int8_t     8-bit   ( unsigned / signed char )
   std::uint16_t  std::int16_t   16-bit   ( unsigned / signed short )
   std::uint32_t  std::int32_t   32-bit   ( unsigned / signed int, usually )
   std::uint64_t  std::int64_t   64-bit   ( unsigned / signed long long, usually )
```

**`std::size_t`** (from `<cstddef>`, and pulled in by `<vector>` etc.)
is an **unsigned** integer type big enough to hold the size of any
object in memory - on a 64-bit build, a 64-bit unsigned integer, so
roughly `unsigned long long`. It is the type `vector::size()` returns
and the type `vector::operator[]` expects:

```cpp
std::vector<std::uint8_t> pixels(360'000, 0);

std::size_t n{pixels.size()};   // 360'000, as an unsigned 64-bit value
pixels[n - 1] = 255;            // the index is a std::size_t
```

Why not just `int`? An `int` is signed and, on Windows/MSVC, only
32 bits - fine for this project's `360'000`, but a 6000x4000 photo is
72 million bytes and a 4-byte-per-pixel buffer index blows past
`int`'s ~2.1-billion limit. `std::size_t` has the same reach as the
memory it is indexing, and matches the vector's own API so you get no
signed/unsigned comparison warnings. 

### The pixel model: mapping 2D `(x, y)` onto a 1D vector

We think about a picture in **two dimensions**: column `x` going right,
row `y` going down, a pixel addressed as `(x, y)`. But a
`std::vector` is **one dimension** - a single straight line of bytes,
index `0` to `size - 1`. So the whole job of the pixel model is a
mapping:

```
        a 2D position (x, y)   ───────►   a 1D index into the byte vector
```

Every time `set_pixel` is asked to colour `(x, y)`, it has to work out
*which byte* in that flat line the pixel lands on. Once we understand this 
mapping, everything else (gradient, border) boils down to just calling
`set_pixel` in a loop.

Two facts fix the mapping:

- **each pixel is 3 bytes** - red, then green, then blue, in that order
- **rows are stored one after another**, top row first, no gaps - this
  is called *row-major* order

#### The two views, side by side

A grid 400 wide will not fit on this page, so the next few diagrams use
a **4x3** image (`width = 4`, `height = 3`, `4 * 3 * 3 = 36` bytes).
Only the numbers shrink - the mapping is identical.

**View 1 - the 2D grid we picture.** `x` is the column (0 on the left,
`width - 1` on the right); `y` is the row (0 at the top, `height - 1`
at the bottom):

```
              x = 0        x = 1        x = 2        x = 3
            ┌──────────┬──────────┬──────────┬──────────┐
   y = 0    │  (0,0)   │  (1,0)   │  (2,0)   │  (3,0)   │
            ├──────────┼──────────┼──────────┼──────────┤
   y = 1    │  (0,1)   │  (1,1)   │  (2,1)   │  (3,1)   │
            ├──────────┼──────────┼──────────┼──────────┤
   y = 2    │  (0,2)   │  (1,2)   │  (2,2)   │  (3,2)   │
            └──────────┴──────────┴──────────┴──────────┘
   ──────────────────────────────────────────────────────►  x (column), 0 .. width-1
   │
   ▼  y (row), 0 .. height-1
```

**View 2 - the 1D vector it actually lives in.** Take the rows above
and lay them end to end, left to right, top row first. Then expand each
pixel into its 3 bytes. The view of the entire 36-byte vector is shown below:

```
   ┌─────────────── row y=0 (4 pixels) ─────┬─────────────── row y=1 (4 pixels) ─────┬─────────────── row y=2 (4 pixels) ─────┐
   │  (0,0)     (1,0)     (2,0)     (3,0)   │  (0,1)     (1,1)     (2,1)     (3,1)   │  (0,2)     (1,2)     (2,2)     (3,2)   │
   │ R  G  B   R  G  B   R  G  B   R  G  B  │ R  G  B   R  G  B   R  G  B   R  G  B  │ R  G  B   R  G  B   R  G  B   R  G  B  │
   byte:                                                                                                                                                   
   │ 0  1  2   3  4  5   6  7  8   9  10 11 │ 12 13 14  15 16 17  18 19 20  21 22 23 │ 24 25 26  27 28 29  30 31 32  33 34 35 │
   └────────────────────────────────────────┴────────────────────────────────────────┴────────────────────────────────────────┘
     ▲                                         ▲                                        ▲
   pixel 0                                     pixel 4                                  pixel 8
   (start of row 0)                            (start of row 1)                         (start of row 2)
```

Notice row `y` starts at pixel `y * width`: 
- row 0 at pixel 0, 
- row 1 at pixel `1 * 4 = 4`, 
- row 2 at pixel `2 * 4 = 8` 

#### The mapping formula

To turn `(x, y)` into a byte index, count the **pixels before it**,
then multiply by 3:

```
   pixels before (x, y)  =  y * width      ← all the full rows above it (row-major!)
                          + x              ← the pixels to its left in its own row
                          ─────────────
                          =  the pixel's number, counting from 0

   byte index of its RED byte   =  (y * width + x) * 3

   then:   + 0  →  Red
           + 1  →  Green
           + 2  →  Blue
```

**Worked example 1 - pixel `(2, 1)` in the 4x3 image.** From View 1 it
is the 3rd pixel of the 2nd row; from View 2 we can literally count to
it:

```
   y * width + x   =   1 * 4 + 2   =   6        ← pixel number 6 (0-based)
   * 3             =   18                       ← its Red byte is index 18

   ...  16   17   │  18    19    20    │  21    22  ...
                  │  R     G     B     │
                  └──────pixel (2,1) ──┘              bytes[18]=R  bytes[19]=G  bytes[20]=B
```


**Worked example 2 - the real image, `width = 400`.** Same formula, the
centre pixel `(200, 150)` of the 400x300 picture:

```
   y * width + x   =   150 * 400 + 200   =   60'200      ← the 60'200th pixel
   * 3             =   180'600                           ← its Red byte is index 180'600
                                                           (dead centre of the 360'000)
```

```cpp
const std::size_t i{(static_cast<std::size_t>(y) * width + x) * 3};
pixels[i + 0] = r;   // Red
pixels[i + 1] = g;   // Green
pixels[i + 2] = b;   // Blue
```

Some of the functions we'll use in this project. Just get an idea now. 
The details will come later:

```cpp
std::vector<std::uint8_t> make_canvas(int w, int h);              // all-zero buffer
void set_pixel(buf&, int w, int h, int x, int y, r, g, b);        // one pixel, bounds-checked
void draw_gradient(buf&, int w, int h, l_r,l_g,l_b, r_r,r_g,r_b); // fill, blend left→right
void draw_border(buf&, int w, int h, int thickness, r,g,b);       // frame
```

We'll use them in `main.cpp`:

```cpp
auto pixels = make_canvas(400, 300);                 // 360'000 bytes, all 0
draw_gradient(pixels, 400, 300,  20, 30, 90,         // left  colour: deep blue
                                240, 140, 40);       // right colour: warm orange
draw_border(pixels, 400, 300, 8, 255, 255, 255);     // 8-px white frame
```

### A. Writing PPM by hand: No dependency (`6.17ProjectImageWriter`)

#### What PPM is, and how it compares

**PPM** (Portable Pixmap) is about the simplest image format that
exists. A PPM file is a **tiny text header** followed by the **raw RGB
bytes**, with no compression and no metadata:

```
   P6\n              ← magic number: "P6" = binary RGB pixmap
   400 300\n         ← width height, in ASCII text
   255\n             ← the maximum value of one colour channel
   <360'000 bytes>   ← width * height * 3 = 400 * 300 * 3, straight from our vector
```

That is the *entire* specification we need. There is no table of
contents, no checksum, no colour profile - the pixels are stored
exactly as they sit in our `std::vector`, in the same row-major order.

How it compares to formats you have heard of:

```
   format   compression        what it's for                        write it by hand?
   ──────   ────────────        ─────────────                        ─────────────────
   PPM      none                learning, pipelines, quick dumps     yes - a few lines
   BMP      none (usually)      old Windows bitmaps                   almost - fiddly header
   PNG      lossless (DEFLATE)  screenshots, line art, transparency   no - needs a library
   JPEG     lossy (DCT)         photographs                          no - needs a library
   GIF      lossless, ≤256 col  simple animation                     no - needs a library
   TIFF     optional            scanning, print, archival            no - complex container
```

PPM is also a good **interchange format**: many
command-line image tools read and write it precisely because parsing it
is trivial, so it shows up as the "plumbing" between programs in image
pipelines.

#### Opening a `.ppm` file

PPM is not a format your OS previews by default, but plenty of software
reads it:

- **Krita** (free, cross-platform) - opens PPM directly via `File ▸ Open`.
- **GIMP** (free, cross-platform) - same, built-in PPM support.
- **IrfanView** (free, Windows) and **XnView MP** (free, cross-platform)
  - lightweight viewers that both handle PPM.
- **ImageMagick** (`magick image.ppm image.png`) and **FFmpeg** -
  command-line, convert PPM to anything.
- **macOS Preview** opens PPM; **Windows Photos** does **not** - convert
  first, or use one of the viewers above.
- Most code editors with an image preview (VS Code with an extension,
  for instance) will not show PPM - don't be surprised by that.

#### How the gradient is computed

For every column `x`, the function does three things: 
- work out **how far across** the image we are (`t`), 
- **blend** the two colours by that amount, then 
- **paint the whole column** with the result. 

**Step 1: `t`, how far across.** `t` turns the column number into a
fraction from `0.0` (left edge) to `1.0` (right edge):

```
   x :   0 ──────────── 133 ──────────── 266 ──────────── 399
   t :  0.0             1/3              2/3              1.0

   t = x / (width - 1)       e.g.  x = 133  →  133 / 399  =  0.333...
```

**Step 2: `mix`, blend one channel.** `mix(a, c)` starts at the left
value `a` and walks the fraction `t` of the way to the right value `c`:

```
   mix(a, c)  =  a  +  t * (c - a)
                 ▲     ▲    └──┬──┘
                 │     │    total distance from left to right
                 │     how much of that distance to cover
                 start at the left value
```

For red, `a = 20` and `c = 240`, so the distance is `220`:

```
   a = 20                                           c = 240
   ●────────────────── c - a = 220 ──────────────────●
   ●──── 1/3 of 220 = 73.3 ────►                            x = 133 :  20 + 73.3  =  93.3  →  93
   ●──────────── 2/3 of 220 = 146.7 ─────────►              x = 266 :  20 + 146.7 = 166.7  →  166
```
**Step 3: paint the column.** The colour depends only on `x`, never on
`y`, so we compute `r`, `g`, `b` once per column and the inner loop
paints every row of that column with it:

```
               x = 0          x = 1               x = 399
           ┌──────────────┬──────────────┬─────┬──────────────┐
   y = 0   │  (20,30,90)  │  (20,30,89)  │ ... │ (240,140,40) │
   y = 1   │  (20,30,90)  │  (20,30,89)  │ ... │ (240,140,40) │
   ...     │     ...      │     ...      │ ... │     ...      │
   y = 299 │  (20,30,90)  │  (20,30,89)  │ ... │ (240,140,40) │
           └──────────────┴──────────────┴─────┴──────────────┘
             one colour per column → vertical stripes that
             change a tiny bit each step → a smooth gradient
```

#### The code and the build

```cpp
bool write_ppm(std::string_view filename, int width, int height,
               const std::vector<std::uint8_t>& pixels) {
    std::ofstream out{std::string{filename}, std::ios::binary};
    if (!out) {
        return false;
    }
    // Header: "P6\n<width> <height>\n255\n", then width*height*3 raw bytes.
    out << "P6\n" << width << ' ' << height << "\n255\n";
    out.write(reinterpret_cast<const char*>(pixels.data()),
              static_cast<std::streamsize>(pixels.size()));
    return out.good();
}
```

The parts that matter:

- **`std::string{filename}`** - `std::ofstream` can't be opened from a
  `std::string_view`, so we build a `std::string` from it.
- **`std::ios::binary`** - writes the bytes exactly as they are. Without
  it, Windows turns every `0x0A` byte (newline) into `0x0D 0x0A`, which
  shifts every pixel after it and corrupts the image.
- **`if (!out)`** - the file failed to open (bad path, no permission).
- **`out << "P6\n" ...`** - the header is plain text, so the familiar
  `<<` from chapter 05 writes it.
- **`out.write(pointer, count)`** - the pixels are raw bytes, not text.
  `write` copies `count` bytes starting at `pointer`, with no
  formatting. Its signature is:

  ```cpp
  write(const char* s, std::streamsize count);
  ```

  Neither of our arguments has the type it wants, which is why both
  casts are there:

  ```
     what we have                            what write() wants
     pixels.data()  →  const std::uint8_t*   ──reinterpret_cast──►  const char*
     pixels.size()  →  std::size_t           ──static_cast───────►  std::streamsize
  ```

- **`reinterpret_cast<const char*>`** - a pointer to `std::uint8_t`
  does not convert to a pointer to `char` on its own, and `static_cast`
  refuses too: they point at different types. `reinterpret_cast` says
  "look at the same bytes as `char`s". Nothing moves in memory; it is
  only a new label on the address. It is safe here because both types
  are one byte, and viewing any data as `char` bytes is exactly what
  `char*` is allowed to do.
- **`static_cast<std::streamsize>`** - `size()` returns `std::size_t`
  (unsigned), but `write` takes `std::streamsize` (signed, 64-bit on
  typical builds). Passing one as the other silently converts, and
  stricter warning levels (such as GCC/Clang's `-Wsign-conversion`)
  flag it. The cast is us saying "I know, do it"; `360'000` fits easily.
- **`return out.good()`** - `true` if nothing has failed so far. The
  last buffered bytes only reach the disk when `out` closes at the end
  of the function, so a failure at that point is not caught here.


### B. A single header third party library (`6.18ProjectVendoredHeader`)

In this lecture, we will improve on our Image Writer project and get it
to write actual PNG files that you can open in any mainstream image viewer app.
PNG is great in that it compresses the image down to a smaller size so that it is
easier to share between apps and people. When the viewer app opens it, it first
decompresses the image, gets the bytes and then does the magic to display the 
image for all to see. We use a real library named **`stb_image_write.h`** by Sean Barrett.

This library is distributed as a single header you can download and put in your project
for use right away. Some important links: 

- GitHub Repo: https://github.com/nothings/stb (Read usage info from here)
- Image Writer: https://github.com/nothings/stb/blob/master/stb_image_write.h (Download this header)

We'll place the header in a `vendor` folder from the root of the project.

```
   6.18ProjectVendoredHeader/
   ├── vendor/
   │   ├── stb_image_write.h   
   │   └── LICENSE
   ├── image.h  image.cpp      ← our helpers (write_png calls stbi_write_png)
   ├── stb_impl.cpp            ← see below
   ├── main.cpp
   └── CMakeLists.txt
```

**The single-header pattern.** Single header libraries are usually shipped as a 
single `.h` file that you download, store in your project and include for use
right away. They usually are bundled with full definitions for the functions that
we need to use from them.

This library is a bit different. In addition to downloading the header, it also
requires to set up a companion `.cpp` file, in which we have to write some macro
before including the header file.

```
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
```

The macro will do some magic to generate the definitions we need. All the logic to 
make this work is bundled in the downloaded header file, but it's writen in some
complex C macro jargon we don't want to involve ourselves with right now. We'll just 
be happy to use the `stbi_write_png` function to write our **PNG** file.


```
   stb_impl.cpp                       image.cpp, main.cpp, ...
   ────────────                       ───────────────────────
   #define STB_IMAGE_WRITE_IMPLEMENTATION
   #include "stb_image_write.h"       #include "stb_image_write.h"
        │                                  │
        ▼                                  ▼
   declarations + DEFINITIONS         declarations only
   → the bodies compile here          → calls left for the linker

   linker: main.o / image.o's calls ──► resolved by stb_impl.o
```

NOTE: If you put the `#define` in two `.cpp`s, the bodies will compile
twice and that will generate "multiple definition" linker error. Make sure 
to have only one file defining this macro and including. 

Our `write_png` will just forward to the library:

```cpp
bool write_png(std::string_view name, int w, int h, const buf& pixels) {
    return stbi_write_png(std::string{name}.c_str(),
                          w, h, 3,               // 3 = RGB channels
                          pixels.data(), w * 3)  // stride: one row in bytes
           != 0;
}
```

**What the last argument, the "stride", means.** `stbi_write_png` gets a
bare pointer to our bytes (`pixels.data()`) and the width and height -
but a pointer alone does not say *where each row ends and the next begins*. 
The stride is that missing piece: 
**the number of bytes from the start of one row to the start of the next row.** 
Another way to look at this is that it is the number of pixels in a row.

For us the rows are packed end to end with no gap, so one row is exactly
`width * 3` bytes (one pixel = 3 bytes). This project's image is 400
wide, so the stride we pass is `400 * 3 = 1200`:

The `CMakeLists.txt` file will add the implementation file and the include path:

```cmake
add_executable(rooster
    main.cpp image.cpp image.h
    stb_impl.cpp                 # the one file that compiles stb's bodies
    vendor/stb_image_write.h
)
target_include_directories(rooster SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)
```

### C. Fetched by CMake (`6.19ProjectFetchContent`)

In this lecture, we are going to see that we can relegate the job to get the library
for us to CMake. CMake will automatically download the library the first time
we configure our project.

This a pattern you can use for any CMake powered project stored in some Git repository 
on the internet. You usually read the documentation for the library on how it works with 
CMake. For example, by digging into the docs I was able to find out that once the project
is downloaded, it sets up a cmake variable `${stb_SOURCE_DIR}` that I can use as an include
directory in my code, allowing me to include the library header from anywhere in the project.

Besides the CMake thing, the C++ code is **identical to what we did in the last lecture**.
`image.h`, `image.cpp`, `stb_impl.cpp`, `main.cpp` unchanged. What changes is that stb is 
no longer actively maintained in the `vendor` folder by us. CMake pulls it 
**at configure time** with **`FetchContent`**. It will store it in some sub-folder 
inside the build folder.

```cmake
include(FetchContent)
FetchContent_Declare(stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        2c980bb59875b0d32144a71867fbdebb2f77cd20   # an exact commit
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(stb)                               # → ${stb_SOURCE_DIR}

target_include_directories(rooster SYSTEM PRIVATE ${stb_SOURCE_DIR})
```

What happens when you press *Configure*:

```
   cmake -S . -B build
        │
        ▼
   FetchContent_Declare   "here is a repo and an exact commit"
        │
        ▼
   FetchContent_MakeAvailable
        │   git clone --depth 1 https://github.com/nothings/stb.git
        │   git checkout 2c980bb...
        ▼
   build/_deps/stb-src/stb_image_write.h        ← now on disk
        │
        ▼
   ${stb_SOURCE_DIR} = build/_deps/stb-src   → added to the include path

   then the normal build: stb_impl.cpp #includes it and compiles the
   bodies, exactly as in version B.
```

- **`GIT_TAG` is pinned to a commit hash** You will see some people out there
  also pin to Git tags. A commit works fine for our purposes here. This means
  that our project will work with whatever version of the header file is in that
  git commit. 
- stb is header-only, so `MakeAvailable` has **no build step** - it just
  puts the files on disk. It is still **compiled from source in our build**. 
- The download happens **once**, into `build/_deps/`. Later configures
  reuse it. Deleting `build/` forces a fresh fetch.

---

## 6.20 Assignment

One small program - a terminal stats / bar-chart tool over a fixed list
of numbers - built in eight steps. `main.cpp` has the eight stubbed
exercises, each with its problem statement and a sample run in a
comment; `main_solution.cpp` solves all eight with the statements
repeated above each solution. Built as two executables (`rooster`,
`rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `stats()` | prototype below `main`, reference out-parameters (three outputs), `<algorithm>` `std::min`/`max` |
| 2 | `bar()` | default arguments (prototype only), `<algorithm>` `std::clamp` |
| 3 | `clamp_to<T>()` | a function template instantiated for `int` and `double`, next to `std::clamp` |
| 4 | `describe()` | overloading (`int` / `double` / `string_view`), argument coercion, `<string>` `starts_with` |
| 5 | `next_roll()` | `static` local RNG (engine + distribution built once), `random_device` seed |
| 6 | `digit_sum()` | recursion (base case + step) with its iterative twin, `[[nodiscard]]` |
| 7 | `checksum()` | `[[nodiscard]]`, a `[&]` lambda accumulating over a range |
| 8 | `pack_rgb()` / `channel()` | `<bit>` `popcount`/`has_single_bit`, `std::uint8_t`/`std::uint32_t` and shifts - mirrors the image project's byte packing |

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole
chapter, including the expanded library tour and the image-project
concepts.

After this chapter the student can factor code into functions, pass and
return data, and is ready for classes.
