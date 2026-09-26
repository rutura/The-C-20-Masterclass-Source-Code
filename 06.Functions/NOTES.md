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

### Two words to pin down: *declaration* and *signature*

**Declaration (prototype)** — a statement that names a function and
gives its return type and parameter types, ending in `;`, with **no
body**. It is a *promise*: "a function shaped like this exists somewhere;
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
- **parameter names** — not in the signature (`double average(double x,
  double y, double z)` and `double average(double, double, double)` have
  the identical signature)

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
integer division does not bite (the Chapter 5 pitfall):

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

A parameter can carry a **default** value. If the caller leaves that
argument out, the default is used in its place - so one function can be
called several ways without writing overloads.

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

**4. Order the parameters so the ones most often left to default come
last.** That is what makes the short calls read well - `greet("Sara")` is
the common case, so `name` comes first and the rarely-changed
`punctuation` comes last.

---

## 6.6 Random numbers

### What we are building

In this lecture, we are exploring the **random numbers** facilities in
C++. As an excuse to explore them, we will build a simple **fortune
teller** program.

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

An argument reaches a function in one of two ways. 

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
- The function must **change** the caller's variable: pass **by
  reference** - `T&`.
- You need more than one **result** out of one call: use several `T&`
  out-parameters, each written through.

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
together with its parameter types** into a single internal symbol - **name
mangling**. The linker then only ever sees distinct names, so the
overloads cannot collide.

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

`const` has shown up already, in passing - `const std::vector<int>&`
parameters, `constexpr std::array` sizes. This lecture makes it a
first-class topic: what `const` actually promises on a plain variable,
what it promises (and does not promise) on a function parameter, and how
`constexpr` is a stronger, different guarantee than `const`.

This section stays on **free functions and plain variables**. `const`
also shows up on class member functions (`void draw() const`) and we 
will talk more on that later in the course. 

### Const standalone variables

```cpp
const int max_players{4};
int current_players{1};   // NOT const - this one is meant to change
```

`const` is a compiler-enforced promise: **this variable's value will not
change after initialization.** If you try to assign to it later, the
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

Here is the part worth being precise about: **`const` on a by-value
parameter does not protect the caller's variable.** It never could -
pass-by-value already makes a fresh **copy** the instant the function is
called, so the caller's original was never reachable from inside the
function, `const` or not.

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
copy is made. This is the case where `const` is not just internal
housekeeping; it is the actual promise the caller depends on:

```
   caller                          print_label(name)
   ──────                          ──────────────────
   ┌────────────┐      alias        ┌────────────┐
   │ name  "Ada"│ ◄───────────────► │ label      │   const on label means
   └────────────┘      same          └────────────┘   the function CANNOT
        ▲              object              │           write through this
        │                                  │           alias back into
        └──────────────────────────────────┘           the caller's own
                writes through label WOULD land               string
                on the caller's name - const rules
                this out
```

```
   const int x           (by value)     const std::string& label  (by reference)
   ──────────────                       ─────────────────────────
   protects a COPY the function          protects the CALLER's own object -
   already owns - the caller was         this is the promise a reference
   never at risk either way              parameter actually needs const for
```

Combining `const` with `&` gets both things at once: the no-copy speed
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

Same function, same result - the only difference is *when* the
computation happens, decided entirely by what the caller passes in.

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

So far every function has shared one `main.cpp`. Real programs spread
functions across many files, grouped by topic. This lecture builds a
program from four files of helpers plus `main.cpp`.

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

Say you need "is this value between these two bounds?" for `int`, for
`double`, for `char`. Overloading (6.9) means writing the same body three
times:

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
the surrounding scope. (This is sometimes called an *immediately-invoked
lambda*.)

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

A **`[&]` capture is only safe while the captured variable is still
alive.** If the lambda outlives the scope it captured from - stored in a
container, returned from a function - a `[&]` link becomes dangling.
Prefer `[=]` (or naming exactly what you need) for a lambda that travels.

### Where lambdas earn their keep: passing a callable

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

An **attribute** is a note to the compiler, written in **double square
brackets**: `[[name]]` or `[[name("some text")]]`. It does **not change
what the code computes**. It tells the compiler something extra about a
function, a variable, or a statement, so the compiler can **warn you
better** (or, for a couple of them, optimise better).

```
   [[nodiscard]] bool username_is_available(std::string_view name);
   └─────┬─────┘ └──────────────────────┬───────────────────────┘
      the note        the thing it is attached to
```

Where an attribute can sit:

```
   [[nodiscard]] int f();          ← on a function
   [[maybe_unused]] int x{0};      ← on a variable
   [[deprecated]] void old_api();  ← on a declaration
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
                               (stops the compiler's fall-through warning - see 5.11)
   [[noreturn]]                 on a function that never returns to its caller -
                               it calls std::exit, throws, or loops forever
   [[likely]] / [[unlikely]]    tag the common / rare branch of an if or switch;
                               a pure optimisation hint, no effect on behaviour
```

An attribute the compiler does not recognise is **ignored**, not an
error - so an unknown `[[something]]` in code you read is safe to move
past and look up later.

---

## 6.17 Intro to assembly

Everything so far in this course has been "here is C++ code, here is
what it does when it runs." This lecture opens up the step in between:
**what does the computer actually do, physically, to run it?**

You will not write any assembly yourself. You will *read* a little of
it - on real examples pulled from chapters and lectures in the course, things you
already know - so that ideas which have so far just been words ("a
variable," "calling a function," "a loop") turn into something you can
point at and watch happen, instruction by instruction.

### Two pieces of hardware: memory and the CPU

Before any assembly makes sense, two physical things need to be
straight in your head: Memory and CPU.

**Memory (RAM)** is one enormous street of numbered mailboxes. Every
single byte your program uses - every variable, every piece of text -
lives in one of these mailboxes, at its own unique **address** (just a
number, like a house number). Two ideas for you to keep in mind: 

- Memory is **big** but **slow** to reach
- CPU storage is **smaller** but way **fast**

Memory is divided in `byte` sized chunks:

```
   memory - one giant column of numbered boxes, EACH HOLDING EXACTLY
   ONE BYTE.

   address 1000:  [ 7 ]
   address 1001:  [ 0 ]
   address 1002:  [ 0 ]
   address 1003:  [ 0 ]
   address 1004:  [ 3 ]
   address 1005:  [ 0 ]
   address 1006:  [ 0 ]
        ...          ...
```

Notice the addresses climb **by exactly 1 each time** - `1000`, `1001`,
`1002`...  **every single address names exactly one byte, always.** 

That raises an obvious question: if a 32-bit CPU and a 64-bit CPU both
address memory **one byte at a time**, what does "32-bit" or "64-bit"
actually describe? **The width of an address itself** - how large a
number a register (a bunch of bytes in the CPU) can hold to *name* a byte, 
not how many bytes that number points to.

**The 32-bit case, worked out in full.** A 32-bit address is a binary
number with 32 digits - each digit either a 0 or a 1, so there are
exactly `2 × 2 × 2 × ... ` (32 times) = `2^32` different numbers such an
address can hold: `2^32 = 4'294'967'296`. Since every address names
exactly one byte (established above), that is also the largest possible
number of distinct bytes a 32-bit address could ever reach - about 4.3
billion bytes.

That raw number, "4.3 billion bytes," is correct but not a size anyone
actually thinks in - nobody buys "4.3 billion bytes" of RAM, they buy
gigabytes. So the next question is simply: **how many gigabytes is
4.3 billion bytes?** Answering that means understanding the unit itself
first.

**What a GiB actually is, and why memory is measured in powers of 2 at
all.** In everyday language, "kilo" means 1,000 and "giga" means
1,000,000,000 - powers of **10**, because humans count in base 10 (we
have 10 fingers). A computer's memory, though, is built entirely out of
binary switches, each one either off or on, and memory addresses are
counted in binary - so the *natural* round numbers for memory sizes are
powers of **2**, not powers of 10. Because "kilo", "mega" and "giga"
already mean powers of 10, the power-of-2 sizes were given their own
names (standardized by the IEC in 1998) so the two can't be confused:

```
   1 KiB  ("kibibyte")  =  2^10 bytes  =              1,024 bytes
   1 MiB  ("mebibyte")  =  2^20 bytes  =          1,048,576 bytes
   1 GiB  ("gibibyte")  =  2^30 bytes  =      1,073,741,824 bytes
   1 TiB  ("tebibyte")  =  2^40 bytes  =  1,099,511,627,776 bytes

   each step up is exactly 2^10 (= 1,024) times the one before it
```

The `bi` in there stands for binary. For comparison, here are the 
regular (decimal, SI) units they are modelled on, where each step up is 
exactly 1,000 times the one before:

```
   1 kB  ("kilobyte")   =  10^3  bytes  =              1,000 bytes
   1 MB  ("megabyte")   =  10^6  bytes  =          1,000,000 bytes
   1 GB  ("gigabyte")   =  10^9  bytes  =      1,000,000,000 bytes
   1 TB  ("terabyte")   =  10^12 bytes  =  1,000,000,000,000 bytes

   binary vs. decimal, side by side:
      1 KiB is  2.4% bigger than 1 kB
      1 MiB is  4.9% bigger than 1 MB
      1 GiB is  7.4% bigger than 1 GB
      1 TiB is 10.0% bigger than 1 TB    (the gap grows at every step)
```

A `GiB` (gibibyte) is *not* the same unit as a `GB` (gigabyte): a GB is
exactly `10^9` bytes, a GiB is exactly `2^30` bytes. They are close
enough that people - and Windows, which calculates in GiB but labels it
"GB" - often use "GB" for both. 

**Now the division itself, spelled out.** "How many GiB is `2^32`
bytes?" is just `2^32 ÷ 2^30`. 

```
   2^32  written out in full is:  2 × 2 × 2 × ... × 2     (32 twos)
   2^30  written out in full is:  2 × 2 × 2 × ... × 2     (30 twos)

   2×2×2×...×2  (32 of them)          2×2  (only 2 left, uncancelled)
   ─────────────────────────    =     ──────────────────────────────
   2×2×2×...×2  (30 of them)                    1

```

```
   2^32 ÷ 2^30  =  2^(32 - 30)  =  2^2  =  2 × 2  =  4
```

So `2^32` bytes is exactly **4 GiB**, meaning that a 32-bit system can have
an address space of 4 GiB max!

**The 64-bit case is the same arithmetic, just with a bigger exponent -
and here real hardware quietly does not go all the way.** `2^64` is
about 18.4 quintillion - address space for exabytes of memory, far
beyond anything any computer is built with today. Chip makers do not
bother wiring up (or having software manage) all 64 bits for something
no machine can use, so real x86-64 CPUs only implement a **usable prefix** 
of those 64 bits, and leave the rest architecturally reserved for future growth:

```
   how many of the 64 possible address bits are ACTUALLY wired up,
   on real x86-64 hardware today

   48-bit addressing (the long-standing default, most machines):
        2^48 bytes  =  256 TiB of addressable memory

   57-bit addressing ("5-level paging" - newer server-class chips):
        2^57 bytes  =  128 PiB (petabytes) of addressable memory
```

**That 256 TiB is not a promise you could actually install that much
RAM** - it is only the CPU's own limit on how large a number it *could*
use to name a byte. Three completely different, narrower ceilings sit
in front of it before you would ever get near that number:

```
   the CPU's address width          "how big a number CAN
   (e.g. 48 bits = 256 TiB)          the CPU even write down?"
            │
            ▼
   the motherboard's own limit      "how much RAM will THIS BOARD'S
   (a fixed spec, per board)         circuitry actually talk to?"
            │
            ▼
   the number of physical slots     "how many separate memory
   × the largest module that        sticks can even be PLUGGED IN,
   fits in each one                 and how big can each one be?"
            │
            ▼
   what you actually have           "what is plugged in right now?"
   installed today
```

**Real numbers, read directly off the machine these lecture examples
were compiled on.** 

```
   this machine's motherboard, identified precisely:
        ASUS TUF Gaming H670-Pro WiFi D4

   the manufacturer's own official spec page for this exact board:
        4 x DIMM slots, DDR4, MAXIMUM 128 GB
                                        ↑ the board's real engineered ceiling

   this machine currently has installed:
        2 modules × 32 GiB  =  64 GiB total
        (occupying 2 of the 4 slots - 2 slots sit empty)
```

So the real ceiling for this specific machine, confirmed against the
manufacturer's own tech-spec page: **128 GiB**, of which 64 GiB is
currently installed and 64 GiB more is available across the 2 empty
slots. Note that an OS-reported "maximum capacity" field (as opposed to
the manufacturer's own published spec) can sometimes just reflect what
happens to be installed rather than the board's true engineered limit -
worth keeping in mind whenever a number like this comes from the
operating system rather than the hardware manufacturer directly.
Either way, the CPU's 256 TiB of *address space* (the 48-bit figure
from a moment ago, not the full theoretical 64-bit one) was never
remotely close to being the constraint - the actual ceiling, 128 GiB,
was sitting three steps closer to home the whole time, set by the
motherboard, not the CPU.

**So if that 256 TiB was never a promise about physical RAM, what is it
actually used for?** This is where **virtual memory** comes in - and
the short answer is: your 256 TiB figure is real, but it is not one
shared number for the whole machine. **Every single running program
gets its own private 256 TiB (or whatever the CPU's address width
allows) of address space, all to itself**, regardless of how much
physical RAM the machine actually has installed.

```
   what "virtual address space" means, concretely

   ┌─────────────────────────┐    ┌─────────────────────────┐
   │   Program A is running  │    │   Program B is running  │
   │                         │    │                         │
   │   thinks it owns a      │    │   thinks it ALSO owns a │
   │   private 0 .. 256 TiB  │    │   private 0 .. 256 TiB  │
   │   range of addresses    │    │   range of addresses    │
   └───────────┬─────────────┘    └───────────┬─────────────┘
               │                              │
               │   both ranges get privately  │
               │   translated, separately     │
               ▼                              ▼
      ┌──────────────────────────────────────────────┐
      │   the ONE real pool of physical RAM actually  │
      │   installed in the machine (say, 64 GiB)      │
      └──────────────────────────────────────────────┘
```

Neither program is lying to itself, and neither is somehow using more
memory than physically exists. **Every address a running program uses
is a *virtual* address - a number in its own private range - and the
CPU (working together with the operating system) silently translates
that virtual address into wherever the corresponding data actually
lives in physical RAM**, a step called address translation, done via
data structures called page tables. Two completely different programs
can both use the exact same-looking address, say `0x00007F0000001000`,
at the same moment, and land on two entirely different physical bytes -
because each program's addresses are translated through its *own*
private mapping, not a machine-wide one.

A couple of consequences worth knowing, since this is the real
foundation the earlier "one machine, one 256 TiB" framing was
simplifying away:

- **One process cannot see or corrupt another's memory just by
  guessing an address** - the addresses it can even form only translate
  through *its own* mapping. This isolation is a large part of why one
  crashing program does not normally take the whole machine down with
  it.
- **A program's own virtual space can be larger than the physical RAM
  installed.** The operating system can temporarily move a chunk of a
  program's data out to disk (this is what "paging" or a "swap file"
  is) and translate that virtual address to disk instead of RAM when
  it is not currently needed, then bring it back when it is.
- **On real 64-bit Windows specifically, a process does not even get
  the CPU's full 256 TiB** - Windows reserves half of the addressable
  range for its own kernel use and hands a 64-bit user program a
  private range of **128 TiB** (`0x0000000000000000` through
  `0x00007FFFFFFFFFFF`) to work with. The exact split is an operating
  system policy choice layered on top of what the CPU's address width
  makes possible, not a hardware limit itself.

None of this changes anything about the assembly you are about to read
- every `[rbp-4]`-style address in this lecture is, technically, one of
these virtual addresses, silently translated for you by hardware you
never see working. It is mentioned here so "each address names one
byte" and "the CPU can address 256 TiB" both stay true statements,
without accidentally implying your machine is somehow storing 256 TiB
per running program.

### What a process's own private address space actually looks like

One private range of addresses, all to itself, is not just one
undivided slab a program fills up from one end. It has an internal
**layout** - fixed regions with fixed jobs, at fixed ends of the range -
and understanding that layout is what finally answers "the stack grows
toward lower addresses, so where does it grow *into*, and why does that
never collide with anything else?"

```
   one process's own virtual address space, low addresses at the TOP
   of the page - a real, standard layout, not specific to this lecture

   address 0x00000000  ┌───────────────────────────────────┐
                       │ TEXT   - your compiled code       │  fixed size,
                       │ (the actual machine               │  never grows
                       │  instructions this lecture        │  (read-only,
                       │  has been reading all along)      │  fixed at
                       ├───────────────────────────────────┤  compile time)
                       │ DATA   - global / static          │  fixed size,
                       │ variables, string literals        │  set at
                       ├───────────────────────────────────┤  program start
                       │ HEAP   - grows toward HIGHER      │
                       │ addresses as the program          │  ▲ grows UP
                       │ requests more dynamic memory      │  (toward
                       │ (std::vector, "new", etc. -       │   higher
                       │  a later chapter's topic)         │   addresses)
                       ├───────────────────────────────────┤
                       │ (large UNUSED gap -                │  ← THIS is
                       │  deliberately left                 │    the part
                       │  empty, so heap and                │    missing
                       │  stack both have real              │    before:
                       │  room to grow into                 │    room to
                       │  without colliding)                │    grow INTO
                       ├───────────────────────────────────┤
                       │ STACK  - grows toward LOWER       │
                       │ addresses as functions call       │  ▼ grows DOWN
                       │ other functions (exactly what     │  (toward
                       │ this lecture has been drawing)    │   lower
   address 0x7FFFFFFF  └───────────────────────────────────┘   addresses)
```

Four things this settles, all at once:

- **The stack is not the only thing in a process's address space** -
  it is one region, deliberately placed at the *high* end, with the
  program's code and global data at the *low* end.
- **The heap and the stack grow toward each other, from opposite ends**
  - the heap climbing to higher addresses as the program allocates more
    dynamic memory, the stack descending to lower addresses as function
    calls nest deeper. This is why they are placed at opposite ends
    instead of next to each other: each one needs room to grow *without
    a neighbor immediately in the way*.
- **The large gap in the middle is not wasted or unusable - it is
  exactly the room the stack (and the heap) grow into.** A tiny
  program's stack might only use a sliver of addresses near the very
  top; a program with deep recursion (6.15) or many nested calls uses
  more of that gap, descending further into it. Run out of that gap
  entirely - grow either region so far it reaches the other - and that
  is a **stack overflow** in the most literal, address-space sense.
- **Every `rbp`/`rsp` value in this lecture's diagrams lives inside that
  STACK region**, near the high end of this layout - the small
  `0x6FE0`-`0x7020` range used throughout this lecture is a zoomed-in
  view of just that bottom strip of the diagram above, not the whole
  address space.

So "64-bit" describes the size of the *ruler* - how big a number the
CPU is built to use to point at a byte - not the size of the boxes
being measured, and in practice not even a promise that all 64 bits of
that ruler are switched on. An `int` still takes up 4 bytes and a
`char` still takes up 1, on a 32-bit or a 64-bit CPU alike; what changes
between them is only how far the addressing can reach, because
pointers/addresses themselves are 32 bits wide on one and (up to) 64
bits wide on the other. This is exactly why `rax` (a full 64-bit
register, wide enough to hold an address on this CPU) and `eax` (its
low 32 bits, wide enough for an `int` but not a full address) both
exist and both matter - you will see this pairing constantly from here
on.

When we later on show three `int` variables living at addresses `rbp-4`,
`rbp-8`, and `rbp-12` - 4 apart, not 1 - that gap is simply "an `int` is
4 bytes, so the next variable's *first* byte starts 4 addresses later,"
the same way a 3-letter mailbox label uses up 3 consecutive house
numbers. The underlying memory is still addressed one byte at a time
throughout; a multi-byte value just occupies several consecutive
one-byte addresses, and its own address is conventionally just the
first of them.

**The CPU** is the chip that actually does arithmetic and makes
decisions. It cannot compute directly on memory - it first has to pull a
value in from memory, into one of a small number of **registers**: tiny
storage slots built into the CPU chip itself, close enough that reading
or writing one is close to instant. A typical x86-64 CPU has around 16
of these. Each one has its own name, and - this is the part you should
remember - **each one also has its own job**. A couple are general
scratch space for whatever a calculation needs. A few others are
reserved, by long-standing convention, for one specific purpose each -
"the register that always holds a function's answer," "the register
that always tracks where the current function's workspace starts." You
will meet each register by name, one at a time, exactly at the point
where its job first matters in this lecture.

```
   CPU (a handful of registers, VERY fast)   memory (huge, slower)
   ┌───────────────────────────────┐         ┌──────────────────────┐
   │  [ a few named slots ]        │  ◄───►  │  address 1000: [ 7 ] │
   │  [ some general purpose ]     │  load   │  address 1004: [ 3 ] │
   │  [ some with a fixed job ]    │  store  │  address 1008: [   ] │
   └───────────────────────────────┘         └──────────────────────┘
```

One more thing about registers, worth knowing before names like `eax`
and `rax` both start showing up for what looks like "the same" register:
**every general-purpose register is 8 bytes wide, but has multiple
names, one per size**, because not every value needs all 8 bytes. An
`int` (4 bytes) does not need the full width; a memory *address* (8
bytes, on this CPU) does. Rather than waste a name, x86-64 lets you
address the *same physical register* at four different widths:

```
   one physical register, eight bytes wide - four names, each one
   naming a different amount of it, starting from the same low end

   byte:    7    6    5    4    3    2    1    0
          ┌────┬────┬────┬────┬────┬────┬────┬────┐
          │    │    │    │    │    │    │    │    │
          └────┴────┴────┴────┴────┴────┴────┴────┘
          └───────────────────────────────────────┘  rax  - all 8 bytes
                              └───────────────────┘  eax  - low 4 bytes
                                        └─────────┘  ax   - low 2 bytes
                                             └────┘  al   - low 1 byte

   writing to eax also changes what rax holds (its low 4 bytes) -
   these are not separate storage, just different "how much of it
   am I using" views onto the exact same physical register
```

The naming pattern is consistent across every general-purpose register,
not just this one: an `r` prefix means the full 8 bytes (`rax`, `rdi`,
`rbp`, `rsp`...), an `e` prefix means the low 4 bytes (`eax`, `edi`,
`ebp`...), and there are narrower 2-byte and 1-byte names too, for when
even 4 bytes is more than a value needs. You will see this exact
pattern later, live: the same argument shows up as `edi` when a function
takes a plain `int`, and as `rdi` when it takes something that needs a
full address, like a reference.

Quick reference - keep this in mind for the rest of the lecture:

- **`r`-prefix** (`rax`, `rdi`, `rbp`, `rsp`, ...) - the full 8 bytes;
  wide enough to hold a memory address on this CPU
- **`e`-prefix** (`eax`, `edi`, `ebp`, ...) - the low 4 bytes only;
  wide enough for an `int`, not for an address
- **no prefix, plain name** (`ax`, `di`, `bp`, `sp`, ...) - the low
  2 bytes only
- **`l`-suffix** (`al`, `dil`, `bpl`, `spl`, ...) - the low 1 byte only
- all four names for a given register (e.g. `rax`/`eax`/`ax`/`al`) refer
  to the **same physical storage** - writing through the narrower name
  changes the low bytes of the wider one too

Summing this up, programming at the assembly level is just a delicate dance
you do between the CPU and Memory.

```
   CPU (a handful of registers, VERY fast)   memory (huge, slower)
   ┌───────────────────────────────┐         ┌──────────────────────┐
   │  [ a few named slots ]        │  ◄───►  │  address 1000: [ 7 ] │
   │  [ some general purpose ]     │  load   │  address 1004: [ 3 ] │
   │  [ some with a fixed job ]    │  store  │  address 1008: [   ] │
   └───────────────────────────────┘         └──────────────────────┘
```

Every single instruction you will meet in this lecture does one of 
exactly three things:

- **move** a value between a register and memory (or another register)
- **compute** - arithmetic or comparison, on a register
- **jump** - decide where to continue running next

Assembly is just a very long, very literal to-do list built entirely
out of those three things.

### The tool: Compiler Explorer (Godbolt)

You do not need to install anything. **Compiler Explorer**, a free
website at **godbolt.org**, compiles code you type on the left and
shows the resulting assembly on the right, updating live as you type:

```
   ┌─────────────────────────┐   ┌─────────────────────────┐
   │  C++ source (you type)  │   │ assembly (auto-updates) │
   │                         │   │                         │
   │  int square(int num) {  │──►│ square(int):            │
   │      return num * num;  │   │      imul   edi, edi    │
   │  }                      │   │      mov    eax, edi    │
   │                         │   │      ret                │
   └─────────────────────────┘   └─────────────────────────┘
```

**Try it now, before reading any further**: open godbolt.org, delete
whatever is in the left pane, and type exactly the `square` function
above (no `#include`, no `main` needed - a lone function is enough).
Watch the right pane fill in as you type the closing `}`. That
live-updating link between a line of your C++ and the instructions it
produced - hover a line on either side and the matching one highlights
- is most of what makes this tool worth using.

Two settings matter, both on the assembly pane's toolbar:

- **Compiler** - a dropdown offering `x86-64 gcc`, `x86-64 clang`, and
  (search the dropdown, it is there) `x86-64 msvc`. This lecture shows
  **gcc and clang** output, both real, both run from this course's own
  Linux containers (chapter 2) to get it. Where MSVC genuinely differs,
  that is called out by name below, so if you build with MSVC day to
  day you are not left guessing.
- **Compiler options** - a text box where you type flags. Type `-O0`
  (the letter O, then a zero; MSVC spells the same idea `/Od`) to turn
  **optimisation off**. Leave that in for almost this entire lecture:
  `-O0` tells the compiler "do not get clever, just translate my code
  fairly literally," which keeps the assembly close enough to the
  source that you can match one against the other line by line. Only
  near the very end do we deliberately switch it to `-O2`, to see what
  "the compiler optimised it" actually removes.

### Assembly belongs to one specific CPU

One more thing before the first real example: assembly is **not portable** 
the way C++ is. It is written directly in one CPU family's
own private vocabulary of instruction names and register names, so the
exact same C++ function produces completely different-looking assembly
depending on which CPU it was compiled for.

```
   the SAME square(int) function, compiled for two different CPUs

   x86-64                              ARM64
   ───────────────────────────────     ───────────────────────────────
   square(int):                        square(int):
           sub   rsp, ...                      sub   sp, sp, #16
           mov   DWORD PTR [...], edi          str   w0, [sp, #12]
           mov   eax, DWORD PTR [...]          ldr   w8, [sp, #12]
           imul  eax, eax                      ldr   w9, [sp, #12]
           ret                                 mul   w0, w8, w9
                                                add   sp, sp, #16
                                                ret
```

That ARM64 column is real, verified output - not a guess - for the same
`square` function you just typed into Compiler Explorer, compiled for a
different chip. Different instruction names (`str`/`ldr` instead of
`mov`), a `mul` that takes three registers instead of `imul`'s two,
different register names (`w0`, `w8`, `w9`).

**This whole lecture, every example from here on, targets x86-64**
(also written `x86_64` or `amd64`) - the instruction set used inside
essentially every Windows and Linux desktop or laptop, and older
Intel-based Macs. If your own machine is an Apple Silicon Mac (M1/M2/M3/M4), 
its *native* code is actually the ARM64 shown above - Compiler Explorer will 
still compile to x86-64 (in the browser) for you regardless.

Two different things are being taught in this lecture, and telling them
apart matters more than anything else in it:

One of the main points we are trying to make in the lecture here is that the
C++ you write is portable and can be compiled for any CPU, but the compiled
version of the code (assembly), is specific to a given CPU. 

```
   WILL transfer to any CPU               will NOT transfer - x86-64 only
   ─────────────────────────              ────────────────────────────────
   a variable is an address in memory      the instruction is called "mov"
   a function call means: remember         the registers are called
   where you were, then jump in            eax, edi, rbp, rsp
   returning means jumping back            a multiply is spelled "imul"
   a loop is a jump backwards
```

If you switched Compiler Explorer to an ARM64 compiler, every
instruction on the right would change. Every idea on the left would
still be exactly, word-for-word, true. C++ allows us to write our ideas
out in a portable format, and the compiler takes on the heavy lifting of compiling
for the CPU architecture (think instruction set (mov, mul,...)) we are targeting.

### Before Step 1: the stack, before `main` even starts

**One piece of context the source code never shows you**: your program
does not start itself, and `main` is not the very first code that runs.
The operating system loads the compiled program into memory and jumps
to a fixed entry point - conventionally named **`_start`** - which is
not part of your code at all, but a small amount of startup code the
compiler links in automatically (part of the C runtime, "CRT"). `_start`
sets a few things up and only then calls `main` - the exact same kind
of function call `main` will later use to call your own functions. By
the time that happens, the stack already exists and is already partway
in use, handed to your program already set up.

Picture that hand-off as a snapshot, right before `main` is called - a
zoomed-in view of just the STACK region from the full address-space
layout above, the small strip near the very top of that earlier
diagram, at its own scale. Stack addresses on a real 64-bit machine are
long, ugly hex numbers (something like `0x00007ffd74aa7500`), so to
keep this readable, the diagrams below use a shortened, made-up but
realistic-shaped stand-in: **`0x7000`** as the address `rsp` happens to
be sitting at, right this moment, before your program has run a single
instruction:

```
   the stack, drawn growing DOWNWARD on the page - meaning toward
   LOWER memory addresses, exactly like the full layout diagram
   above. This is the same direction, just zoomed in.

   address 0x6FE0:  ┌───────────────────────────────┐   ← further into
                    │                               │      the big gap
                    │      (unused address space -   │      from the full
                    │       part of the same large    │      layout above:
                    │       gap shown in the full     │      room this
                    │       layout diagram above -    │      stack has
                    │       room for the stack to     │      not needed
                    │       grow further into, if     │      yet, but
                    │       deeper calls need it)     │      COULD grow
                    │                               │      into
   address 0x7000:  ├───────────────────────────────┤ ◄── rsp = 0x7000
                    │                               │      (the boundary
                    │      (free - already claimed   │       IS 0x7000:
                    │       stack space, not yet      │       claimed
                    │       written to)               │       above, still
                    │                               │      unwritten
   address 0x7020:  └───────────────────────────────┘       below)
```

Every address label in these diagrams sits on a **horizontal line**, never
inside a box's text - because an address names a *boundary*, the exact
edge where one byte ends and the next begins, not a labeled "room." The
line at `address 0x7000:` above is not "roughly where `rsp` is" - it
*is* `0x7000`, the precise dividing line `rsp` points at.

**Two directions are at play here, and they are opposites - this is
worth being completely explicit about.** Reading the diagram top to
bottom, addresses climb: `0x6FE0` is lower than `0x7000`, which is
lower than `0x7020`. But the **stack itself grows upward on this page**
- toward `0x6FE0`, the lower numbers - as more gets pushed onto it. So
"the stack grows" and "addresses increase" point in **opposite**
directions from each other. Concretely: pushing something onto the
stack does not add to `rsp`, it **subtracts** from it - `rsp` moving
from `0x7000` to `0x6FF8` (coming up in the very next diagram) is a
subtraction of 8, and that subtraction *is* the stack growing by 8
bytes. "Stack grows toward lower addresses" and "pushing subtracts from
rsp" are two phrasings of the exact same fact.

There is a register called **`rsp`**, and it holds an actual address -
`0x7000` in this diagram - marking the boundary between "stack space
already claimed" (above it in this drawing, at the lower addresses) and
"stack space not yet claimed" (below it, at the higher addresses, all
the way down into that large gap from the full layout diagram).

**`rsp`** stands for "stack pointer." Its one job, for the entire time
your program runs, is to always **hold the address** of the current top
of the stack - whatever the next free address is. Nothing else is
special about it; it is simply the register every instruction that
touches the stack keeps in sync, the same way any other register can
hold any other address.

Now watch what happens the instant the OS calls `main`, with the
addresses tracked at every step. A return address on this CPU is
**8 bytes**, so pushing one onto the stack always moves `rsp` down by exactly
8:

```
   the OS calls main() - "call" is covered properly in Step 6; for now,
   just watch what it does to the stack, address by address

   BEFORE the call - same as the diagram just above, rsp still at 0x7000:

   address 0x6FE0:  ┌───────────────────────────────┐  ← "_start" - the C
                    │        the C runtime's        │     runtime's own
                    │    startup frame ("_start")   │     startup code,
                    │                               │     NOT the OS and
                    │                               │     NOT main - the
                    │                               │     thing that
                    │                               │     actually calls
                    │                               │     main. Below it:
                    │                               │     the big gap.
   address 0x7000:  ├───────────────────────────────┤ ◄── rsp = 0x7000
                    │                               │      (the boundary
                    │             (free)            │       IS 0x7000)
   address 0x7020:  └───────────────────────────────┘

   THE INSTANT main starts running - "call" wrote 8 bytes right at the
   0x7000 boundary above, and pushed rsp down past them to a NEW boundary:

   address 0x6FE0:  ┌───────────────────────────────┐
                    │        the C runtime's        │
                    │    startup frame ("_start")   │
   address 0x6FF8:  ├───────────────────────────────┤ ◄── rsp = 0x6FF8
                    │  return address: "come back   │      (moved down
                    │   here when main ends"        │       by 8, from
   address 0x7000:  ├───────────────────────────────┤       0x7000)
                    │             (free)            │
   address 0x7020:  └───────────────────────────────┘
```

Calling a function does not just "jump" to it - it first **writes**
that 8-byte return address into the next free spot (which was `0x7000`,
where `rsp` was already pointing), then moves `rsp` DOWN by exactly 8,
from `0x7000` to `0x6FF8`, so `rsp` again points at wherever the *new*
top of the stack is. That written-down address is how `main` - or any
function - eventually finds its way back to whoever called it. (The
instruction that does this writing-down is `call`, covered properly
once you have a second function to call in Step 6. For now, the point
is only: by the time `main`'s own first instruction runs, an address
has already been written to memory at `0x6FF8`, and `rsp` has already
moved down by 8, from `0x7000` to `0x6FF8`, to reflect it.)

`main` is about to want a private workspace of its own - somewhere to
keep its own bookkeeping, separate from `_start`'s. That is what its
very first two instructions set up, and this needs one more register,
**`rbp`** ("base pointer"), which does not hold anything meaningful yet
at the moment shown above - `main` is about to give it a purpose. Watch
`rsp` move down by another 8 bytes as this happens:

```
   right after main's first two instructions run - "push rbp" wrote
   another 8 bytes right at the 0x6FF8 boundary, and pushed rsp down
   to a new boundary, 0x6FF0, which rbp then copies for itself:

   address 0x6FE0:  ┌─────────────────────────────────┐
                    │         the C runtime's         │
                    │     startup frame ("_start")    │
   address 0x6FF0:  ├─────────────────────────────────┤ ◄── rsp = 0x6FF0
                    │     main's saved copy of the    │ ◄── rbp = 0x6FF0
                    │         CALLER's old rbp        │      (both agree,
   address 0x6FF8:  ├─────────────────────────────────┤       for now)
                    │    return address (unchanged,   │
                    │    written earlier by "call")   │
   address 0x7000:  ├─────────────────────────────────┤
                    │              (free)             │
   address 0x7020:  └─────────────────────────────────┘
```

`rsp` moved AGAIN here - from `0x6FF8` down to `0x6FF0` - because
`push rbp` just wrote another 8 bytes (the value `rbp` held a moment
ago) onto the stack, at the new top. `rbp` then **copies** that same
address, `0x6FF0`, via `mov rbp, rsp` - so `rsp` and `rbp` now briefly
agree, both holding `0x6FF0`.

From here on, though, they behave differently: `rsp` will keep moving to
lower addresses as `main` uses more stack space, but `rbp` will **not**
change again for the rest of `main`'s run. `rbp` becomes a fixed anchor:
the moment `main` declares a local variable, its address will be
described as "so many bytes below `rbp`" - e.g. `0x6FF0 - 4 = 0x6FEC` -
and that arithmetic stays correct all the way through `main`, precisely
because `rbp` itself never changes.

That fixed anchor is worth having, but setting it up spends `rbp` -
overwrites whatever it held before, which belonged to `_start`'s own
code, not main's. Throwing that away would be a problem the instant
`main` finishes and control needs to go back to code that still expects
to find its own `rbp` value intact. So the very first thing any
function does, before repointing `rbp` at itself, is **save the old
value of `rbp` on the stack** - and the very last thing it does, right
before returning, is **put that old value back**:

```
   push    rbp        first: save whatever rbp held before (the
                       CALLER's anchor point), so it is not lost
   mov     rbp, rsp    now: repoint rbp here - THIS function's own anchor

   ...the function's own body runs here, measured from rbp...

   pop     rbp         restore the CALLER's rbp value, exactly as found
   ret                 (Step 6) jump back to the address "call" saved
```

This four-line shape - **push rbp, mov rbp/rsp, ..., pop rbp** - opens
and closes essentially every function you are about to look at. It has
two names: the opening two lines are a function's **prologue** (the
setup), the closing two are its **epilogue** (the teardown). You now
know exactly what both are protecting and why.

Two more instructions, met just now and worth naming plainly before
moving on:

```
   push   <register>   write that register's value into the next free
                        stack spot, then move rsp past it (rsp goes DOWN)

   pop    <register>   the exact reverse: read a value back off the top
                        of the stack into that register, then move rsp
                        back to point at it as free space again (rsp
                        goes back UP)
```

### Step 1 - the smallest possible program

```cpp
int main() {
    return 0;
}
```

You already have everything needed to read this one. Here is what gcc,
at `-O0`, turns it into:

```
main:
        push    rbp
        mov     rbp, rsp
        mov     eax, 0
        pop     rbp
        ret
```

The first two lines and the last two are exactly the prologue and
epilogue you just walked through above - nothing new to figure out
there. That leaves exactly one line in the middle that is new, plus
`ret`:

```
   mov     eax, 0    copy the literal value 0 into a register called
                     eax. eax has a fixed, special job on this ABI
                     (the calling convention chapter 2's containers and
                     Compiler Explorer both use): it is always where a
                     function leaves its return value for whoever
                     called it to find. "return 0;" in your source
                     becomes, quite literally, "put 0 in eax."

   ret               "return." Jump back to wherever this function was
                     CALLED from - for main, that is the operating
                     system's own startup code from a moment ago. (How
                     "wherever it was called from" is actually
                     remembered is Step 6's `call`/`ret` pair - main
                     here is simply on the receiving end of one.)
```

So the whole five-line function reads, once you have both halves: save
the caller's `rbp`, claim this frame as your own, put the answer `0`
where callers look for it, give the caller's `rbp` back, jump back to
whoever called you. Every one of those five lines is either "move a
value" or "jump" - nothing more exotic happens anywhere in assembly.

**Try it**: type this exact `main` into Compiler Explorer (gcc, `-O0`)
and confirm you see the same five lines.

### Step 2 - a variable is an address in memory

```cpp
int rectangle_area() {
    int width{4};
    int height{3};
    int area{width * height};
    return area;
}
```

```
rectangle_area():
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 4     ← width
        mov     DWORD PTR [rbp-8], 3     ← height
        mov     eax, DWORD PTR [rbp-4]   ← read width into eax
        imul    eax, DWORD PTR [rbp-8]   ← eax = eax * height
        mov     DWORD PTR [rbp-12], eax  ← area
        mov     eax, DWORD PTR [rbp-12]  ← return value = area
        pop     rbp
        ret
```

The prologue and epilogue are the same two lines as Step 1 - skip past
those, you already know what they are doing. What is new is the body,
and one piece of new notation: **`DWORD PTR [rbp-4]`**. Read it in
pieces:

```
   [rbp-4]        "the memory address that is 4 bytes below wherever
                  rbp is pointing" - an address, computed from the
                  frame's own anchor point.

   DWORD PTR      "treat whatever is at that address as a 4-byte value"
                  (DWORD = "double word" = 4 bytes, the size of an int
                  on this compiler). Without this, the CPU would not
                  know how many bytes at that address to read/write.
```

So `mov DWORD PTR [rbp-4], 4` reads as: "write the 4-byte value 4 into
memory, at the address 4 bytes below rbp." **That address is `width`.**
Not a name the CPU knows about - the name `width` existed only in your
source code, for you to read. To the compiled program, `width` simply
*is* a particular address, and every place your C++ used the name
`width`, the compiler substituted that same address.

Three variables, three addresses, spaced 4 bytes apart because each is
a 4-byte `int`:

```
   this function's stack frame:

        rbp  ──────────────────────►  ┌─────────────────────────┐
                                       │  (rbp's saved old value) │
             rbp - 4    width         ├─────────────────────────┤
                                       │           4              │
             rbp - 8    height        ├─────────────────────────┤
                                       │           3              │
             rbp - 12   area          ├─────────────────────────┤
                                       │          12               │
                                       └─────────────────────────┘
```

And `int area{width * height};` itself is not one step to the CPU - it
is three: **load** `width` from its address into the register `eax`,
**multiply** `eax` by whatever is at `height`'s address, **store** the
result at `area`'s address. C++ lets you write the whole idea as one
line; the CPU only ever does one small thing at a time.

**Try it**: paste this exact function into Compiler Explorer. Then
change `int height{3};` to `int height{9};` and watch only the `3` in
the assembly change to a `9` - nothing else about the shape moves,
because the *addresses* `width`, `height`, and `area` live at did not
change, only the number stored at one of them.

### Step 3 - `if` is a comparison plus a jump

```cpp
int pass_or_fail(int score) {
    if (score >= 60) {
        return 1;
    } else {
        return 0;
    }
}
```

```
pass_or_fail(int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi
        cmp     DWORD PTR [rbp-4], 59
        jle     .L2
        mov     eax, 1
        jmp     .L3
.L2:
        mov     eax, 0
.L3:
        pop     rbp
        ret
```

That very first body line introduces a new register: `edi`. `score` is
a **parameter** here, not a local variable the function invented for
itself - it is a value the *caller* has to hand over. Registers are the
fastest way to hand a value from one function to another, so this ABI
(the same convention Step 6 covers properly) reserves `edi` as a fixed,
agreed-on slot: **"the first whole-number argument always arrives in
`edi`."** Every compiler targeting this platform honours that agreement,
which is exactly how a function compiled by gcc can call one compiled
by clang and both land on the same page about where the argument is.
`mov DWORD PTR [rbp-4], edi` is simply this function's very first move:
copy whatever the caller left in `edi` into `score`'s own stack slot, so
the rest of the function can treat `score` the same way Step 2 treated
`width` and `height` - a plain address, read and written by `mov`.

Two new *kinds* of instruction also show up here, both used for the
first time:

```
   cmp   DWORD PTR [rbp-4], 59    "compare score against 59" - this does
                                   not store a result anywhere visible;
                                   it just sets some internal CPU flags
                                   (e.g. "was the first value bigger,
                                   smaller, or equal") for the very next
                                   instruction to read.

   jle   .L2                      "jump if less-or-equal" - reads the
                                   flags cmp just set. If score <= 59,
                                   jump to the label .L2. Otherwise, do
                                   nothing and fall straight into the
                                   next line.
```

**A `.L2:` on its own line is a label** - not an instruction, just a
named marker in the code that a jump instruction can target. It exists
purely so `jle .L2` and `jmp .L3` have somewhere to point.

Trace it as a flowchart, which is really all this is:

```
                    cmp score, 59
                          │
                    is score <= 59 ?
                    ╱             ╲
                 yes               no
                  │                 │
                  ▼                 ▼
            jump to .L2       fall through:
            (the "else"        mov eax, 1   (the "if" branch)
             branch below)     jmp .L3  (skip over the else branch)
                  │                 │
           .L2:  mov eax, 0         │
                  │                 │
                  └────────┬────────┘
                            ▼
                      .L3: pop rbp ; ret
```

There is no dedicated "if" instruction anywhere on this CPU. `if`/`else`
in your source compiles down to exactly this: one `cmp`, one
conditional jump, two runs of plain instructions, and labels for the
jumps to land on. Every relational operator from 5.4 (`<`, `<=`, `>`,
`>=`, `==`, `!=`) has its own matching conditional jump - `jl`, `jle`,
`jg`, `jge`, `je`, `jne`.

One thing worth pointing out so it does not look like a mistake: the
condition got **flipped**. Your source says `score >= 60`; the assembly
tests `score <= 59` and jumps to the *else* branch on true. That is a
compiler doing the exact same job a different, equally correct way -
"jump away from the if-branch when the condition is false" reaches the
same outcome as "jump into the if-branch when the condition is true."
Compilers do this kind of restructuring constantly; it is not something
to chase in your own code.

**Try it**: change `>= 60` to `> 60` and watch `jle .L2` become `jg`
followed by different logic, or just `jle .L2` change its comparison
value.

### Step 4 - a loop is a jump backwards

```cpp
int sum_below_five() {
    int total{0};
    for (int i{0}; i < 5; ++i) {
        total += i;
    }
    return total;
}
```

```
sum_below_five():
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 0    ← total = 0
        mov     DWORD PTR [rbp-8], 0    ← i = 0
        jmp     .L2
.L3:
        mov     eax, DWORD PTR [rbp-8]
        add     DWORD PTR [rbp-4], eax  ← total += i
        add     DWORD PTR [rbp-8], 1    ← ++i
.L2:
        cmp     DWORD PTR [rbp-8], 4    ← is i <= 4 ?  (same as i < 5)
        jle     .L3                     ← if true, jump BACK UP to .L3
        mov     eax, DWORD PTR [rbp-4]
        pop     rbp
        ret
```

Notice this uses **exactly** the same two instructions as Step 3 - one
`cmp`, one `jle` - nothing new. The only structural difference from an
`if` is *where the label being jumped to sits*: `.L3` (the loop body)
is written **above** `.L2` (the check) in the instruction list, so
jumping to it means jumping **backward**, re-running instructions the
CPU already ran once.

```
   .L2:  cmp i, 4  ──true──►  .L3:  run the body  ──┐
          │                                          │  (jumps back up)
        false                                        │
          │                                           │
          ▼                                           │
   fall through, return total  ◄─────────────────────┘
                                   (this arrow is the "backward jump")
```

Also notice the very first instruction after `i`'s initialization is
`jmp .L2` - an **unconditional** jump (no `cmp` needed first, it always
happens) straight down to the check, *before* the body has run even
once. That is `for`'s "check the condition before the first iteration"
rule (5.9), made literal: the very first thing that happens is the
check, not the body.

Every loop shape you know - `while`, `for`, `do...while` - compiles
down to some arrangement of *label*, *body*, *check*, *jump backward*.
The one structural difference you can usually spot for `do...while` is
that it skips the initial `jmp` straight to the check - it falls
straight into the body first, exactly matching "run the body once
before checking" from 5.10.

**Try it**: change the `for` loop above to an equivalent `while` loop
and compare - the assembly should end up nearly identical, because
`for` and `while` are the same loop, just spelled differently in
source.

### Step 5 - `unsigned` wraparound: the CPU never saw a bug

This is 4.3 and 4.4's wraparound bug, with nothing left to take on
faith.

```cpp
unsigned int mistaken_refund() {
    unsigned int points{350u};
    points = points - 400u;   // "should" be -50
    return points;
}
```

```
mistaken_refund():
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 350
        sub     DWORD PTR [rbp-4], 400
        mov     eax, DWORD PTR [rbp-4]
        pop     rbp
        ret
```

That `sub DWORD PTR [rbp-4], 400` is the entire subtraction - one
instruction, no branch, no check. Now compare it to what you get if
`points` were declared `int` (signed) instead of `unsigned int`, same
numbers:

```
   unsigned int version                 int version
   ─────────────────────                ─────────────────────
   sub   DWORD PTR [rbp-4], 400          sub   DWORD PTR [rbp-4], 400

   IDENTICAL. Same instruction, same operands, either way.
```

**This is the entire point of the example.** `sub` does not know, and
does not care, whether the 4 bytes it is subtracting from are meant to
represent a signed or an unsigned number - it just flips bits according
to one fixed binary rule, every time. `350 - 400` under that rule
produces the bit pattern that `int` would read back as `-50`, and that
the exact same bits, read back as `unsigned int`, become
`4'294'967'246`. **The value in memory is identical either way; only the
meaning your C++ type assigns to those bits differs.** There is no
"unsigned subtract" instruction standing by to catch this and no flag
raised - which is exactly why 4.4 called this bug *silent*: nothing at
the machine level was ever positioned to notice.

**Try it**: change `unsigned int` to `int` in this function on Compiler
Explorer and confirm the assembly does not change at all - proving the
CPU genuinely cannot tell the difference at this step.

### Step 6 - calling a function: `call` and `ret`, made concrete

Back to 3.3's own example, `add_numbers`, called from `main`:

```cpp
int add_numbers(int first, int second) {
    int result{first + second};
    return result;
}

int main() {
    int sum{add_numbers(25, 7)};
    return 0;
}
```

```
add_numbers(int, int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi   ← first  = whatever main put in edi
        mov     DWORD PTR [rbp-8], esi   ← second = whatever main put in esi
        mov     eax, DWORD PTR [rbp-4]
        add     eax, DWORD PTR [rbp-8]   ← eax = first + second
        mov     DWORD PTR [rbp-12], eax  ← result = eax
        mov     eax, DWORD PTR [rbp-12]  ← return value = result
        pop     rbp
        ret

main:
        push    rbp
        mov     rbp, rsp
        mov     esi, 7                        ← 2nd argument
        mov     edi, 25                       ← 1st argument
        call    add_numbers(int, int)
        mov     DWORD PTR [rbp-4], eax        ← sum = whatever came back in eax
        mov     eax, 0
        pop     rbp
        ret
```

Two brand new instructions here, plus one new register.

The register first, since it is the smaller idea: `add_numbers` takes
*two* parameters, and Step 3 already covered where the first one, `edi`,
comes from. The second whole-number argument gets its own fixed slot
too, by that same convention - `esi`. Same idea as `edi`, just the
agreed-on spot for argument number two.

Now the two instructions that actually make a function call happen:

```
   call    jump to another function's first instruction - but FIRST,
           push the address of the instruction right after this "call"
           onto the stack. That is the one and only way the CPU has of
           remembering where to come back to once the called function
           finishes.

   ret     pop that saved address back off the stack, and jump to it.
           This is how a function knows where to return TO - it is not
           magic, the address was written there by "call" itself, the
           moment this function was entered.
```

Put the two together and every function call you have seen `ret` end
with so far makes sense: `ret` always jumps back to whatever `call`
most recently pushed - which, for every function *except* `main`, was
written by another one of your own functions; for `main`, by the
operating system's own startup code (Step 1).

Walk through the whole call as one sequence:

```
   main calls add_numbers(25, 7)

   ┌────────────────────────────────┐
   │  main:                         │
   │      mov  esi, 7               │  1. 2nd argument goes into esi
   │      mov  edi, 25              │  2. 1st argument goes into edi
   │      call add_numbers(int,int) │  3. remember here, jump in
   │  ┌─────────────────────────┐   │
   │  │ add_numbers(int, int):  │◄──┘
   │  │   reads edi, esi        │      4. new stack frame, its OWN
   │  │   ...computes...        │         first/second/result
   │  │   mov  eax, result      │      5. answer placed in eax
   │  │   ret                   │───┐  6. pop remembered address, jump back
   │  └─────────────────────────┘   │
   │      mov  [rbp-4], eax  ◄──────┘  7. main stores add_numbers's answer
   └────────────────────────────────┘
```

This is 6.2's stack-frame diagram, now with an actual instruction
(`call`) behind every arrow in it. It is also *why* 6.2 said a function
call is "not free": steps 1 through 7 above are all real instructions
that run on **every single call**, on top of whatever work happens
inside `add_numbers` itself. For a large, complex function that
overhead is negligible; for a one-line function called millions of
times in a loop, it can matter - which is exactly the problem `inline`
(Step 8, below) exists to address.

**Try it**: paste both functions into Compiler Explorer together and
find, in `main`'s assembly, the exact moment control transfers into
`add_numbers` - the `call` line - and the exact moment it comes back -
right after it.

### Step 7 - a reference is a hidden address

6.8's pass-by-value vs. pass-by-reference, made completely literal.

```cpp
void add_one_by_value(int n) {
    n += 1;
}

void add_one_by_ref(int& n) {
    n += 1;
}
```

```
add_one_by_value(int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi   ← n = its OWN 4-byte copy
        add     DWORD PTR [rbp-4], 1     ← changes only that copy
        pop     rbp
        ret

add_one_by_ref(int&):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi   ← n = an 8-byte ADDRESS
        mov     rax, QWORD PTR [rbp-8]   ← load that address into rax
        mov     eax, DWORD PTR [rax]     ← follow it - read the int it points to
        lea     edx, [rax+1]             ← edx = (that value) + 1
        mov     rax, QWORD PTR [rbp-8]   ← reload the address
        mov     DWORD PTR [rax], edx     ← write through it - the CALLER's int changes
        pop     rbp
        ret
```

Three things to notice, in order down that second listing.

First, `QWORD PTR` instead of `DWORD PTR` for `add_one_by_ref`'s `n`:
**QWORD** means 8 bytes (a "quad word"), because on this CPU a memory
address itself is 8 bytes long - `add_one_by_ref`'s `n` is not holding a
4-byte `int` at all, it is holding the *address of* one.

Second, `edi` (4 bytes, from Step 3) became `rdi` (8 bytes) - the exact
same register, just its full 64-bit width instead of its 4-byte one,
because an address needs all 8 bytes to store. The same relationship as
`eax` and `rax`: one physical register, two names, depending how many of
its bytes an instruction is using.

Third, one new register and one new instruction on the `lea` line:
`edx` is simply another general-purpose register, playing the same role
`eax` usually does - a scratch spot to hold a value briefly. `lea` -
"load effective address" - normally computes an address without reading
memory at all, but here it is being used as a shortcut for plain
addition: `lea edx, [rax+1]` means "put `rax + 1` into `edx`," done this
way because this particular addition happened to line up with an
address-arithmetic instruction the compiler already had available. It
is worth being able to recognise, not worth dwelling on.

```
   by value:   n IS the int itself                    4-byte value in edi
               add_one_by_value never touches
               the caller's own variable at all

   by ref:     n IS the ADDRESS of the caller's int    8-byte address in rdi
               every use of "n" in the source costs
               an extra step: follow the address
               ([rax]) to reach the real int
```

`n += 1` in `add_one_by_ref` is not one instruction, the way it was for
`add_one_by_value` - it is **load the address**, **follow it to read
the value**, **add one**, **follow the address again to write the
result back**. This is the entire mechanism behind 6.8's "an alias for
the caller's variable": a C++ reference is, underneath, an address. The
difference from a plain address is entirely at the C++ level - the
language will only let you use `n` as if it were the `int` itself, and
never lets you ask for the address it is secretly built from.

**Try it**: paste both functions in together and count the instructions
in each body - `add_one_by_ref` needs noticeably more, purely to keep
following that address.

### Step 8 - `inline`: watching the call disappear

```cpp
inline int cube(int num) {
    return num * num * num;
}

int main() {
    int result{cube(3)};
    return result;
}
```

At `-O0`, `inline` usually changes **nothing** you can see - `call
cube(int)` is still sitting right there in `main`'s assembly. That is
because `-O0` deliberately does the least amount of clever rewriting
possible, and `inline` (6.2) is only ever a *suggestion* to the
compiler, never a command it is obliged to follow.

Switch Compiler Explorer's optimisation flag from `-O0` to **`-O2`**
and look again:

```
   -O0  (optimisations off)          -O2  (optimisations on)
   ───────────────────────           ───────────────────────
   main:                             main:
       mov   edi, 3                      mov   eax, 27      ← no call at all
       call  cube(int)                   ret
       ...
   cube(int):                       cube(int) does not even
       ... multiply, multiply ...   appear in the output
       ret
```

At `-O2`, gcc does two things at once: it pastes `cube`'s body straight
into `main` instead of calling it (exactly what "inline" describes in
plain words), and then - since `cube(3)`'s argument never changes - it
goes ahead and does the multiplication itself, at compile time, leaving
only the finished number `27` behind. Nothing is computed while the
program runs; the entire function call has vanished. Clang and MSVC
reach the same outcome at their own equivalent "optimise for speed"
levels (`-O2`/`-O3` for clang, `/O2` for MSVC); the exact size or call
count at which a given compiler decides a function is worth inlining
can differ between them, but "a small, frequently-called function tends
to disappear into its caller once optimisation is turned on" holds
across all three.

**Try it**: flip the compiler options box between `-O0` and `-O2` on
this exact example and watch `cube(int)` appear and disappear.

### Step 9 - `constexpr`: computed before the program even runs

```cpp
constexpr int square_ce(int num) {
    return num * num;
}

constexpr int nine{square_ce(3)};
```

```
   square(6) at runtime            square_ce(3) as a constexpr call
   ───────────────────             ─────────────────────────────────
   argument only known             argument is a literal, known
   while the program runs          while the compiler is still running
        │                                    │
        ▼                                    ▼
   mov edi, 6 ; call square         mov [rbp-8], 9    ← just the answer, no work
```

A `constexpr` function *can* run at compile time - but only when every
value it is called with is itself known at compile time (6.10 has the
full rule). Call it with a literal, like `square_ce(3)` here, and the
compiler does not emit a multiply instruction at all: it works out
`3 * 3` itself, while compiling, and the assembly shows only the
finished number `9` being stored. Call the exact same function with a
value the program will not know until it runs (something typed in by
the user, say), and the assembly falls back to an ordinary `call` - a
`constexpr` function never *forces* compile-time evaluation, it only
*allows* it when the inputs make that possible.

One detail worth being precise about: this needs no `-O2`. Unlike
`inline` in Step 8, folding away a genuinely compile-time-computable
`constexpr` call is not an optimisation being applied to generated
code - there was never any runtime code generated for it to begin with,
even at `-O0`.

**Try it**: paste `square_ce` in, call it once with a literal (like
`square_ce(3)`) and once with a variable whose value the compiler
cannot know ahead of time - compare the two call sites' assembly.

### Step 10 - recursion: a function calling itself, literally

6.15's `sum_to`, in its own assembly.

```cpp
long sum_to(int n) {
    if (n <= 0) { return 0; }
    return n + sum_to(n - 1);
}
```

Two small new pieces show up here, worth naming before the full listing:
`rbx` is just another general-purpose register, being borrowed here as
extra scratch space; and `leave` is a one-instruction shorthand for the
`mov rbp, rsp` / `pop rbp` pair you have already seen close out every
other function in this lecture - same epilogue, spelled more briefly.

```
sum_to(int):
        push    rbp
        mov     rbp, rsp
        push    rbx                       ← save rbx, this call is about to use it
        sub     rsp, 24
        mov     DWORD PTR [rbp-20], edi   ← THIS call's own n
        cmp     DWORD PTR [rbp-20], 0
        jg      .L2                       ← n > 0 ? skip the base case
        mov     eax, 0                    ← base case: return 0
        jmp     .L3
.L2:
        mov     eax, DWORD PTR [rbp-20]
        movsxd  rbx, eax                  ← copy n into rbx, widened to 8 bytes -
                                           ←   parked there so the call below cannot
                                           ←   disturb it (eax is about to be overwritten)
        mov     eax, DWORD PTR [rbp-20]
        sub     eax, 1                    ← compute n - 1
        mov     edi, eax                  ← argument for the next call
        call    sum_to(int)               ← sum_to calling sum_to
        add     rax, rbx                  ← n + (whatever the recursive call returned)
.L3:
        pop     rbx                       ← restore rbx to what it was before this call
        leave                             ← shorthand for: mov rsp, rbp ; pop rbp
        ret
```

There is no separate "recursive call" instruction - `call sum_to(int)`
is the **exact same `call`** you saw in Step 6, it just happens to
target the very function that is currently running. What makes
recursion work is something you already know from Step 1: every `call`
gets **its own fresh stack frame**, stacked on top of whichever frame
made the call. `[rbp-20]` in the outer call and `[rbp-20]` in the
nested call are two genuinely different addresses in memory, because
`rbp` itself points somewhere different in each frame - so each call's
`n` is kept completely separate, automatically, purely because each
call pushed its own new frame onto the stack. This is precisely 6.15's
"each pending call is a stack frame" diagram, now with the actual
instruction (`call`) responsible for building each one.

**Try it**: paste `sum_to` in and find the line that reads `call
sum_to(int)` - a function's assembly containing a call to its own name
is the tell-tale sign of recursion, visible before you have even worked
out what the function computes.

### What to take away

```
   variable             →  a named address in memory, read/written by mov
   if / loop             →  cmp + a conditional jump (jle, jg, je, ...) + labels
   unsigned wraparound    →  the same sub/add as signed - no hardware check exists
   function call           →  call / ret; arguments in fixed registers, answer in eax
   reference parameter      →  an address passed in a register, followed on every use
   inline (-O2)              →  the call disappears, body pasted into the caller
   constexpr (literal)        →  the whole computation disappears, only the answer remains
   recursion                   →  call targeting the same function, a fresh frame each time
```

You will not be asked to write assembly, and most day-to-day C++ never
needs it. What this gives you, even glanced at occasionally, is a way
to settle "wait, what does this actually do?" with certainty instead of
a guess - and a first, concrete look at what "the compiler optimised it
away" means in practice, a phrase you will hear constantly from here
on.

---

## 6.18 Project: writing an image

Everything in this chapter comes together in one small program that
**draws a picture and saves it to a file**. The picture is deliberately
plain - a left-to-right colour gradient with a solid frame - so the
focus stays on *how the program is put together*, not on graphics.

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

`image.h` and `image.cpp` use two type names you have not met yet:
`std::uint8_t` for colour bytes and `std::size_t` for the vector index.
Neither is a new *kind* of type - both are just **aliases for built-in
integer types you already know**, given clearer names.

**`std::uint8_t`** (from `<cstdint>`) means "an **u**nsigned **int**eger
exactly **8** bits wide" - so its range is `0` to `255`, exactly one
byte. On every compiler you will use, that is a plain `unsigned char`:

```cpp
#include <cstdint>

std::uint8_t red{255};        // same object as:  unsigned char red{255};
unsigned char also_a_byte{0}; // the two names are interchangeable here
```

We use `std::uint8_t` instead of `unsigned char` for two reasons.
First, **intent**: `unsigned char` reads like text handling; a pixel
channel is a small number, and `uint8_t` says "one byte of data, 0-255"
out loud. Second, **the range is guaranteed in the name** - `char` is
only *required* to be at least 8 bits, and whether plain `char` is
signed is compiler-dependent; `std::uint8_t` pins both down. The `8` is
the whole point: `240` fits, `256` wraps back to `0`, which is why
`draw_gradient` casts its blended result back to `std::uint8_t`
deliberately.

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
signed/unsigned comparison warnings. This is exactly why `set_pixel`
computes its index as `std::size_t` (see the pixel model below).

You will still learn and use `short`, `int`, `long long`, `unsigned`,
`char` directly - these aliases are the same types wearing a name that
states their size and signedness at the point of use.

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
*which byte* in that flat line the pixel lands on. Get that mapping
right and everything else (gradient, border) is just calling
`set_pixel` in a loop.

Two facts fix the mapping:

- **each pixel is 3 bytes** - red, then green, then blue, in that order
- **rows are stored one after another**, top row first, no gaps - this
  is called *row-major* order

The picture this project actually draws is **`width = 400`,
`height = 300`** (see `main.cpp`), so `make_canvas(400, 300)` allocates
`400 * 300 * 3 = 360'000` bytes, all zero.

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
pixel into its 3 bytes. This is the entire 36-byte vector, nothing
hidden:

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

Notice row `y` starts at pixel `y * width`: row 0 at pixel 0, row 1 at
pixel `1 * 4 = 4`, row 2 at pixel `2 * 4 = 8`. That is the whole trick.

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

   ...  16  17 │ 18  19  20 │ 21  22  ...
               │  R   G   B │
               └── pixel (2,1) ──┘              bytes[18]=R  bytes[19]=G  bytes[20]=B
```

Check it against View 2 above: pixel `(2,1)` sits at bytes `18..20`. It
matches.

**Worked example 2 - the real image, `width = 400`.** Same formula, the
centre pixel `(200, 150)` of the 400x300 picture:

```
   y * width + x   =   150 * 400 + 200   =   60'200      ← the 60'200th pixel
   * 3             =   180'600                           ← its Red byte is index 180'600
                                                           (dead centre of the 360'000)
```

That is exactly what `set_pixel` computes - `width` here is the same
value passed to `make_canvas`:

```cpp
const std::size_t i{(static_cast<std::size_t>(y) * width + x) * 3};
pixels[i + 0] = r;   // Red
pixels[i + 1] = g;   // Green
pixels[i + 2] = b;   // Blue
```

The `static_cast<std::size_t>` matters: `y * width` for the real image
is `149 * 400 ≈ 59'600` and the final index passes 180'000 - fine for
`std::size_t`, but doing the multiply in `int` first is a habit worth
dropping early.

The helper functions are all pure chapter-6 material (signatures as in
`image.h`):

```cpp
std::vector<std::uint8_t> make_canvas(int w, int h);              // all-zero buffer
void set_pixel(buf&, int w, int h, int x, int y, r, g, b);        // one pixel, bounds-checked
void draw_gradient(buf&, int w, int h, l_r,l_g,l_b, r_r,r_g,r_b); // fill, blend left→right
void draw_border(buf&, int w, int h, int thickness, r,g,b);       // frame
```

And `main.cpp` calls them with this project's actual numbers:

```cpp
auto pixels = make_canvas(400, 300);                 // 360'000 bytes, all 0
draw_gradient(pixels, 400, 300,  20, 30, 90,         // left  colour: deep blue
                                240, 140, 40);       // right colour: warm orange
draw_border(pixels, 400, 300, 8, 255, 255, 255);     // 8-px white frame
```

- a **header / source split** (6.11): declarations in `image.h`, bodies
  in `image.cpp`
- functions take the buffer **by reference** (6.8) and scalars by value
- `draw_gradient` blends the two colours with a **lambda** (6.14) - for
  the call above, `mix` runs `20 → 240` on red, `30 → 140` on green,
  `90 → 40` on blue as `x` sweeps `0 → 399`:

  ```cpp
  const double t{static_cast<double>(x) / (width - 1)};   // 0.0 at x=0 .. 1.0 at x=399
  const auto mix = [t](std::uint8_t a, std::uint8_t c) {
      return static_cast<std::uint8_t>(a + t * (c - a));   // linear blend
  };
  ```

**What changes between the three versions is only the last step - how
the pixel buffer becomes a file.** Same helpers, three ways to get the
output written.

```
   make_canvas → draw_gradient → draw_border → ┌─ A: write_ppm()      hand-rolled, no library
                                               ├─ B: stbi_write_png() vendored header
                                               └─ C: stbi_write_png() header fetched by CMake
```

### A. No dependency at all (`6.18ProjectImageWriter`)

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
That is why `write_ppm` is six lines: build the header string, dump the
buffer.

How it stacks up against formats you have heard of:

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

The trade is stark. Our 400x300 image is **360 KB as PPM** and would be
perhaps **15-40 KB as PNG** - PPM pays for its simplicity in file size,
every time, because it never compresses. In exchange, *you can write the
encoder yourself in an afternoon*, which is the entire point of this
first version. PNG and JPEG buy small files and wide compatibility at
the cost of a real dependency - that is versions B and C.

PPM is also a genuinely useful **interchange format**: many
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

If in doubt, convert once with ImageMagick and view the PNG.

#### The code and the build

```cpp
bool write_ppm(std::string_view name, int w, int h, const buf& pixels) {
    std::ofstream out{std::string{name}, std::ios::binary};
    out << "P6\n" << w << ' ' << h << "\n255\n";
    out.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    return out.good();
}
```

`std::ios::binary` matters on Windows: without it the stream would
translate every `0x0A` byte in the pixel data into `0x0D 0x0A` and
corrupt the image. `reinterpret_cast<const char*>` is needed because
`ostream::write` deals in `char`, while our buffer is `std::uint8_t` -
same one byte, different type name, so the cast is safe here.

#### Optional: reading the file we just wrote in a hex editor

*This part is a detour - skip it if you only care about the picture. But
if you have never looked at a binary file's raw bytes, a PPM is a
perfect first one, because half of it is text you can read and half is
data you cannot.*

Open `image.ppm` in a **hex editor** (in VS Code: install the Microsoft
**Hex Editor** extension, then right-click the open `image.ppm` tab ▸
*Reopen Editor With...* ▸ *Hex Editor*). You will see three columns:

```
   00000000   50 36 0A 34 30 30 20 33 30 30 0A 32 35 35 0A FF   P6.400 300.255..
   └───┬────┘  └──────────────────┬───────────────────────┘   └───────┬──────┘
    offset            16 bytes, each shown in hex              same bytes as text
   (address of                                                (a '.' = not printable)
    the first byte
    on this row)
```

**1. Every pair of characters is one byte, written in hexadecimal.**
`50` is not "fifty" - it is the hex number `0x50`, which is `80` in
decimal. One byte holds `0x00`..`0xFF`, i.e. `0`..`255`. The editor
shows bytes in hex because it is compact and lines up in columns; the
value is the same number your C++ code would call `80` or `0x50`.

**2. The left column is the offset - use it to locate any byte.**
The offset is the position of the **first** byte on that row, counted
from the start of the file, and it too is written in hex. Rows are 16
bytes wide, so the offsets go `00000000`, `00000010`, `00000020`, ...
(that is `+16` each time: `0x10` = 16). To find the offset of a
specific byte:

```
   byte offset  =  row offset  +  column number

   e.g. the byte in row 0x00000020, column 0x0A
        = 0x20 + 0x0A = 0x2A            (42 in decimal - the 43rd byte)
```

Going the other way, to jump to "byte number 10'000" (decimal): 10'000
= `0x2710`, so it is in the row whose offset is `0x2710` rounded down to
a multiple of 16 (`0x2710`), at column `0x00`. Most hex editors have a
*Go to offset* command (often `Ctrl+G`) that takes the number directly.

**3. The header is ASCII - printed characters, not numbers.** Look at
the decoded-text column for the first row: `P6.400 300.255.`. Our code
wrote `out << "P6\n" << 400 << ' ' << 300 << "\n255\n";`. The stream
turned the **number** `400` into the **three characters** `'4'`, `'0'`,
`'0'`, and those are the bytes on disk:

```
   text:   P     6    \n    4     0     0    ' '    3     0     0    \n    2     5     5    \n
   hex:   50    36    0A    34    30    30    20    33    30    30    0A    32    35    35    0A
   dec:   80    54    10    52    48    48    32    51    48    48    10    50    53    53    10
```

`'4'` is the byte `0x34` (52), **not** `0x04`. `'0'` is `0x30` (48).
This is the ASCII table at work: character `'0'` through `'9'` are bytes
48 through 57. `0x0A` is `'\n'`, a control character with no glyph, so
the text column shows it as `.`. The header ends at the `0x0A` at
offset `0x0E` - **15 bytes** in total (`P6\n` = 3, `400 300\n` = 8,
`255\n` = 4).

**4. After the header it is raw pixel bytes - not text.** From offset
`0x0F` on, the decoded-text column is mostly dots, because pixel values
like `0xFF` or `0x18` are not printable characters - they are just
numbers. Three bytes per pixel, R then G then B:

```
   offset 0x0F:  FF FF FF  FF FF FF  FF FF FF   ...
                 └pixel 0┘ └pixel 1┘ └pixel 2┘
                  R  G  B
```

`FF FF FF` is `(255, 255, 255)` - white. That is the 8-pixel border
`draw_border` painted, so the file opens with a long run of `FF`. Scroll
down: around offset `0x25A7` the border ends and the gradient begins -
the first non-white bytes are `18 20 58` = `(24, 32, 88)`, our deep-blue
left colour. Keep scrolling and each pixel's bytes drift up toward
`F0 8C 28` = `(240, 140, 40)`, the orange right colour, then snap back
to `FF FF FF` at the right border and the start of the next row.

**5. Watch the row wrap.** The hex view shows 16 bytes per row, but a
pixel is 3 bytes and `16 / 3` is not whole, so pixels straddle the row
boundary. A row starting `20 58 18 20 58 19 ...` has begun in the
*middle* of a pixel. Only the arithmetic in step 4 tells you where a
pixel starts - never assume a display row does.

**6. Check the total size.** Header (15) + pixels (`400 * 300 * 3` =
360'000) = **360'015 bytes**. The last byte sits at offset `360'014` =
`0x57E4E`. If the file is that many bytes, `write_ppm` wrote exactly
what it should.

The point: a binary file is just **a numbered sequence of bytes**. The
offset column is the numbering; whether a run of bytes "means" text or
pixels or something else is a matter of which part of the format you are
looking at. PPM makes that split obvious - a readable text header, then
the data.

`CMakeLists.txt` lists only our own files - there is nothing else:

```cmake
add_executable(rooster main.cpp image.cpp image.h)
```

The lesson: Writting your ppm file by hand. 

### B. A vendored single-header library (`6.19ProjectVendoredHeader`)

As we just saw, PPM is bulky and not something most people can
double-click to open. To write a compressed, universally-supported
**PNG** we use a real library - **`stb_image_write.h`** by Sean Barrett
- but we
**vendor** it: the one header file is committed straight into the
project under `vendor/`.

```
   6.19ProjectVendoredHeader/
   ├── vendor/
   │   ├── stb_image_write.h   ← the library, committed with our code
   │   └── LICENSE
   ├── image.h  image.cpp      ← our helpers (write_png calls stbi_write_png)
   ├── stb_impl.cpp            ← see below
   ├── main.cpp
   └── CMakeLists.txt
```

**The single-header pattern.** A single-header library ships as *one
file* that is both the header and the source. By default `#include`ing
it gives you only **declarations**. In **exactly one** `.cpp` you write
`#define STB_IMAGE_WRITE_IMPLEMENTATION` *before* the include, and that
translation unit gets the **function bodies** too.

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

Put the `#define` in two `.cpp`s and the bodies compile twice - a
"multiple definition" linker error. One file, always.

Our `write_png` just forwards to the library:

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
but a pointer alone does not say *where each row ends and the next
begins*. The stride is that missing piece: **the number of bytes from
the start of one row to the start of the next row.** The library uses it
to step down the image - row 1 starts `stride` bytes after row 0, row 2
starts `stride` bytes after row 1, and so on.

For us the rows are packed end to end with no gap, so one row is exactly
`width * 3` bytes (one pixel = 3 bytes). This project's image is 400
wide, so the stride we pass is `400 * 3 = 1200`:

```
   width = 400, stride = 400 * 3 = 1200

   byte:  0            1200         2400
          ▼            ▼            ▼
          [ row 0    ][ row 1    ][ row 2    ]     ← +1200 each time is the next row
```

`CMakeLists.txt` adds the implementation file and the include path:

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

- **`SYSTEM`** marks `vendor/` as third-party, so `-Wall -Wextra` do not
  flag warnings inside stb's own code.
- **No linking.** The header is compiled *from source* with our
  compiler, our flags, our standard library. There is no external `.lib` / `.a` /
  `.dll` in the picture, so there is **no ABI mismatch** possible - the
  class of "nasty linker error" that comes from mixing a prebuilt binary
  with a different toolchain simply cannot happen here.

### C. Fetched by CMake (`6.20ProjectFetchContent`)

The C++ code is **identical to B** - `image.h`, `image.cpp`,
`stb_impl.cpp`, `main.cpp` unchanged. What changes is that stb is no
longer committed here. CMake pulls it **at configure time** with
**`FetchContent`**.

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

- **`GIT_TAG` is pinned to a commit hash, not a branch.** A branch name
  would mean "whatever that branch points at the day you build" - the
  build stops being reproducible. Pin it.
- stb is header-only, so `MakeAvailable` has **no build step** - it just
  puts the files on disk. It is still **compiled from source in our
  build**, so the no-ABI-mismatch guarantee from B still holds.
- The download happens **once**, into `build/_deps/`. Later configures
  reuse it. Deleting `build/` forces a fresh fetch.
- Trade-off vs. B: version C needs network access and `git` the first
  time it configures; version B builds offline forever. Real projects
  usually accept that trade for not carrying copies of their
  dependencies in their own repo.

### The three side by side

```
                      A: hand-rolled     B: vendored        C: FetchContent
   ─────────────────  ───────────────    ───────────────    ────────────────
   output             PPM                PNG                PNG
   library code       none               in vendor/,        not in our repo;
                                         committed          cloned to build/
   gets the library   —                  git add            CMake, at configure
   offline build      yes                yes                first build needs net
   reproducible       yes                yes (file frozen)  yes (commit pinned)
   compiled here?     yes                yes                yes  → no ABI risk
```

---

## 6.21 Assignment

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
