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

- `inline` is a **suggestoion, not a command**. The compiler may still
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

## 6.10 Functions across files

So far every function has shared one `main.cpp`. Real programs spread
functions across many files, grouped by topic. This lecture builds a
program from four files of helpers plus `main.cpp`.

```
   6.10FunctionsAcrossFiles/
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

## 6.11 Files in subfolders

The same four helpers, but now organised into folders by area:

```
   6.11FilesNested/
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
   1. the folder of the file doing the #include   (here: 6.11FilesNested/)
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

     c++ ... -I .../6.11FilesNested/geometry
             -I .../6.11FilesNested/finance
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

## 6.12 Function templates

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

## 6.13 Lambda functions

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

## 6.14 Recursion

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

## 6.15 Recursion vs iteration

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

## 6.16 The `[[nodiscard]]` attribute

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

## 6.17 Assignment

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
