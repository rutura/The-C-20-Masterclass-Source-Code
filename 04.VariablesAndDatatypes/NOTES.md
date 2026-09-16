# Variables and Data Types

Chapter 3 got a value on screen and a value back in. This chapter is
about what a value actually *is* to the compiler: how the same number
can be spelled four different ways, which built-in type to reach for and
why, how `auto` saves you from writing the type out by hand, and one
particularly sneaky bug that ties both of those together.

The running example throughout is a small **retail / loyalty-points**
scenario - purchases, discounts, customer records - carried forward
lecture by lecture.

```
   4.2  number systems       the same value, four spellings
   4.3  data types            which built-in type, and why
   4.4  auto                  let the compiler write the type down
   4.5  assignment            exercises pulling 3-4 together
```

---

## 4.2 Number systems

`main.cpp` opens with the same value written four ways:

```cpp
int decimal{15};        // base 10: the default
int octal{017};         // base 8: leading 0
int hexadecimal{0x0F};  // base 16: leading 0x
int binary{0b00001111}; // base 2: leading 0b
```

```
   decimal{15}   octal{017}   hexadecimal{0x0F}   binary{0b00001111}
        │             │                │                   │
        └─────────────┴────────────────┴───────────────────┘
                    all four store the SAME value

   print any of them back with {}  →  15, regardless of which
   base you used to WRITE the literal
```

The prefix (`0`, `0x`, `0b`) only changes how the literal is *spelled*
in source code - it has no effect on what is stored or how the program
behaves. This is the same idea as `#FF5733` being a hex color and
`chmod 755` being an octal permission: notations you have likely already
seen without labeling them "hex" or "octal."

### Converting an existing value to other bases

The second half of `main.cpp` runs the idea in reverse: start from one
`int` and ask `std::println`'s format spec to print it in every base:

```cpp
int reading{1024};
std::println("{} in decimal is {}, octal {:#o}, hex {:#x}, binary {:#b}",
    reading, reading, reading, reading);
```

| Format spec | Base    |
|:-----------:|---------|
| `{}`        | decimal |
| `{:#o}`     | octal   |
| `{:#x}`     | hex     |
| `{:#b}`     | binary  |

The `#` in each spec is what adds the base prefix (`0`, `0x`, `0b`) to
the printed output - drop it and you get the digits with no prefix.

This lecture is deliberately light here - the full breakdown of *why*
binary exists (place value with only two digits), how hex lines up
exactly with 4-bit groups, why octal survives only in `chmod`, and how
many values fit in a given number of bits, lives in
[`4.2NumberSystems/NOTES.md`](4.2NumberSystems/NOTES.md) alongside the
lecture's own code. Read that alongside this section if you want the
binary/hex/octal deep dive; this file stays focused on how the four
notations relate to the rest of the chapter.

---

## 4.3 Data types

The four literal bases from 4.2 were all still `int`. This lecture is
about the **other** axis: which built-in type to declare a variable as
in the first place, walked through by category.

### Integers - whole numbers

```cpp
int items_purchased{42};
long long yearly_total_cents{1'284'950'000};
unsigned int loyalty_points{350};
```

```
   int                    the everyday default for a whole number
   long long              buys a much bigger range - for a value an
                          int would overflow (a yearly total in cents)
   unsigned int           never negative - communicates that intent,
                          but easy to misuse (4.4 shows exactly how)
```

`1'284'950'000` uses a **digit separator** (`'`) purely for
readability - it groups the digits the way a comma would in prose, and
the compiler ignores it entirely. Always reach for `'` in a literal this
large; `1284950000` and `1'284'950'000` are the identical value, only
one of them is countable at a glance.

`sizeof` answers "how many bytes does this type actually occupy":

```cpp
std::println("sizeof(int): {}, sizeof(long long): {}", sizeof(int), sizeof(long long));
```

### Floating point - fractional numbers

```cpp
float discount_rate{0.15f};
double amount_spent{93.33};
long double very_precise_rate{0.1512345678901234L};
```

```
   float          smallest, least precise - trades precision for size
   double         the practical DEFAULT for money and measurements,
                  unless you have a specific reason not to
   long double    more precision still, at the cost of more bytes
```

The `f` and `L` suffixes on the literals (`0.15f`, `...L`) tell the
compiler which floating-point type the literal itself is, independent of
the variable it is initializing into - worth noticing now because 4.4
leans on exactly this mechanism for `auto`.

Scientific notation is just another way to spell a `double`:

```cpp
double national_debt{3.4e13};   // 3.4 x 10^13
```

The compiler reads `3.4e13` the same way it reads `34000000000000.0` -
scientific notation exists for readability once a number is very large
or very small, not as a different type or behavior.

### Booleans and characters/text

```cpp
bool over_budget{amount_spent > 100.0};

char currency_symbol{'$'};
std::string customer_name{"Ada"};
```

```
   bool         true / false - here, the RESULT of a comparison,
                not a literal true/false typed by hand
   char         exactly one character, single-quoted: '$'
   std::string  a sequence of characters, double-quoted: "Ada"
```

`over_budget` is a good example of a `bool` that is *computed*, not
written literally - `amount_spent > 100.0` is itself an expression that
produces `true` or `false`, brace-initialized straight into the
variable.

### The `unsigned` catch, previewed

`loyalty_points` above is declared `unsigned int` because a point
balance can never legitimately go negative - the type communicates that
guarantee to any reader. But that guarantee is easy to break by
accident, and 4.4 shows exactly how and why, once `auto` is in the
picture too.

---

## 4.4 `auto`

`auto` asks the compiler to work out a variable's type from its
initializer, instead of writing the type out by hand.

```cpp
auto amount_spent{93.33};    // double - deduced from the literal
auto items_purchased{42};    // int
```

```
   auto amount_spent{93.33};
              │
              ▼
   the compiler already knows 93.33 is a double literal,
   so writing "double" again would be redundant - auto reads
   the SAME type off the initializer
```

`auto` only changes how the type is *written down* in source code - the
deduced type still sticks around for the variable's entire lifetime,
exactly as if you had spelled it out. `amount_spent` is a `double` for
as long as it exists; `auto` is not some looser, dynamically-typed
stand-in.

### Literal suffixes steer what `auto` deduces

```cpp
auto loyalty_points{350u};   // 'u' suffix -> unsigned int
```

A literal's suffix is part of the literal's own type, and `auto` simply
reads it off:

| Suffix | Deduced type   |
|:------:|----------------|
| (none) | `int`          |
| `u`    | `unsigned int` |
| `f`    | `float`        |
| `L`    | `long double`  |
| `ll`   | `long long`    |
| `s`    | `std::string`  |

### Bare string literal vs. `s`-suffixed

```cpp
using namespace std::string_literals;

auto store_id{"store-42"};     // const char* - the C-style string type
auto customer_name{"Ada"s};    // std::string - because of the 's' suffix
```

```
   "store-42"     no suffix  →  auto deduces const char*
                                (the type C++ inherited from C)

   "Ada"s          's' suffix →  auto deduces std::string
                                (from std::string_literals)
```

This is the one that trips people up: a bare double-quoted literal is
*not* a `std::string` by default. If you want `auto` to deduce
`std::string`, the literal itself has to say so with the `s` suffix -
otherwise you get `const char*`, a different type with a much smaller
set of member functions available.

`sizeof` makes the difference concrete - a `const char*` is a pointer
(a fixed few bytes on any given platform), while a `std::string` object
is larger and manages its own buffer:

```cpp
std::println("store id: {} ({} bytes)", store_id, sizeof(store_id));
std::println("customer: {} ({} bytes)", customer_name, sizeof(customer_name));
```

### The `unsigned` wraparound bug

This is the payoff of pairing `auto` with the `unsigned` type from 4.3.
`auto` silently deduced `unsigned int` for `loyalty_points` (because of
the `u` suffix) - and an `unsigned` type has **no bit patterns set aside
for negative numbers at all**:

```cpp
auto loyalty_points{350u};   // unsigned int

loyalty_points = -10;        // DANGER
std::println("loyalty points after mistaken refund: {}", loyalty_points);
```

```
   loyalty_points = -10;
        │
        ▼
   there is no "negative" representation available in unsigned -
   every bit pattern is already spoken for by the unsigned range
        │
        ▼
   the bits for -10 get REINTERPRETED as a huge positive number
   instead (wraps around from 0, the same way an odometer wraps
   from 000000 back around past the top of its range)
```

No compiler error, no crash - the program runs and prints a number that
looks nothing like `-10` or a sensible point balance. The bug is exactly
as dangerous as it looks: it is silent. The full explanation of *why*
the wraparound lands where it does - the signed-vs-unsigned bit-range
table - lives in
[`4.2NumberSystems/NOTES.md`](4.2NumberSystems/NOTES.md#6-how-many-bits-how-big-a-number),
since it depends on the binary place-value groundwork from that lecture.

The practical takeaway pulls 4.3 and 4.4 together: `unsigned` is worth
reaching for *deliberately*, when a value genuinely can never be
negative and you want the compiler and reader to know it - never as a
reflexive default, and doubly not through an `auto` deduction you did
not consciously notice (that stray `u` suffix). When in doubt, check
what `auto` actually deduced with `sizeof` or a debugger before trusting
it silently.

---

## 4.5 Assignment

Five exercises, each isolating one idea from 4.2-4.4. `main.cpp` in
`4.5Assignment/` has the prompts as comments with `TODO` markers;
`main_solution.cpp` has a worked solution.

1. **Personal profile card** - declare a name, age, height (`double`,
   meters), and student status (`bool`); print all four in one sentence.
   Straight brace-initialization practice, nothing new.
2. **Receipt printer** - six literals (three prices, three quantities),
   compute per-item and grand totals, print with `{:.2f}` and aligned
   labels. Exercises the `std::format` precision spec.
3. **Base converter tool** - read a decimal `int` from `std::cin`, print
   it back in octal/hex/binary with the same `{:#o}`/`{:#x}`/`{:#b}`
   specs from 4.2, but on a value read at runtime instead of a hardcoded
   literal.
4. **Unit price calculator** - write a free function,
   `double unit_price(double total_cost, int quantity)`, defined above
   `main` (3.3's function-basics pattern), called with at least two
   different inputs.
5. **`auto` detective** - predict the deduced type for a handful of
   `auto` declarations (a plain `int` literal, suffixed literals, a bare
   string literal vs. an `s`-suffixed one, a mixed `int`/`double`
   expression) *before* compiling, then check each prediction with
   `sizeof` - direct practice of the 4.4 gotcha above.

Chapter 4 closes with `4.6Quiz`, 15 multiple-choice questions spanning
Chapter 3 and this chapter, each followed immediately by its answer and
a short explanation - a self-check rather than a lecture, so it has no
`main.cpp`/`CMakeLists.txt` of its own.
