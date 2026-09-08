# Control Flow

Chapter 4 gave us variables and datatypes. Every program so far has run
**straight down the page**: statement, statement, statement, done.

```
      START
        │
        ▼
   ┌──────────┐
   │ read a   │
   │ value    │
   └────┬─────┘
        │
        ▼
   ┌──────────┐
   │ compute  │
   └────┬─────┘
        │
        ▼
   ┌──────────┐
   │ print    │
   └────┬─────┘
        │
        ▼
       END
```

That is the **sequence structure**, and it is built into C++: unless you
say otherwise, statements run in the order they appear. This chapter adds
the other two things every program needs:

- **Selection** - look at a value and choose what to do
  (`if`, `if/else`, `else if`, `switch`, `?:`).
- **Iteration** - repeat a piece of work without copy-pasting it
  (`while`, `for`, `do...while`, plus `break` and `continue`).

---

## 5.2 Arithmetic operators and input

What we do: **reading a value the user types**, and **doing
arithmetic on it**.

### Input with `std::cin`

`std::cin` is the input side of the same iostream library we use for
`std::cout`. The arrows point the way the data flows:

```
   std::cout  <<  value     value  ──►  screen
   std::cin   >>  variable  keyboard ──►  variable
```

```cpp
std::print("Enter two monthly salaries, separated by a space: ");
int salary1{};
int salary2{};
std::cin >> salary1 >> salary2;
```

- One `>>` reads **one** whitespace-separated token and converts it to
  the type on its right.
- Chained `>>` reads several in order. The user may separate answers with
  spaces **or** newlines - `>>` skips leading whitespace either way.
- `std::cin` lives in `<iostream>`, so that header comes back for every
  lecture that takes input.
- `int salary1{};` brace-initializes to `0`, so the variable still holds
  something defined if the read fails.

```
   user types:   3500   4000 <Enter>
                   │      │
      salary1 ◄────┘      │
      salary2 ◄───────────┘
```

### The five arithmetic operators

| Operation      | Operator | Algebra        | C++          |
|----------------|:--------:|----------------|--------------|
| Addition       | `+`      | f + 7          | `f + 7`      |
| Subtraction    | `-`      | p − c          | `p - c`      |
| Multiplication | `*`      | bm             | `b * m`      |
| Division       | `/`      | x / y          | `x / y`      |
| Remainder      | `%`      | r mod s        | `r % s`      |

All five are **binary** operators (two operands). Two of them need a
closer look.

### Integer division truncates

When **both** operands of `/` are integers, the result is an integer and
any fractional part is **discarded, not rounded**.

```
    7 / 4   ─►  1           (not 1.75, not 2)
   17 / 5   ─►  3           (not 3.4)
 7501 / 2   ─►  3750        (not 3750.5)  ◄── the "average" bug
```

For the two salaries, `(salary1 + salary2) / 2` is the average pay. If the sum is an odd number ─► the division by 2 gives a fractional result, but we are dealing with integers, so the computer throws away the fraction : `3500 + 4001` is `7501`, and `7501 / 2` gives `3750`, losing the `.5`.

To keep the fraction, make at least one operand floating-point:

```
 7501 / 2     ─►  3750        int / int    = int
 7501 / 2.0   ─►  3750.5      int / double = double
 7501.0 / 2   ─►  3750.5      double / int = double
```

### The remainder operator `%`

`%` gives what is left over after integer division. Integers only.

```
   17 % 5  =  2          because 17 = 3*5 + 2
   20 % 4  =  0          20 divides evenly
 7501 % 100 =  1         7501 is seventy-five whole 100s, plus 1
```

In the example, `(salary1 + salary2) % 100` is the part of the combined
pay that does not make up a full 100.

### Precedence and associativity

An expression like `a + b * c - d` has several operators in it. Two
questions decide what it means:

1. **Precedence** - *which operator acts first?* Higher-precedence
   operators grab their operands before lower ones. `*` outranks `+`, so
   `b * c` happens before either `+` or `-`.
2. **Associativity** - *when two operators have the SAME precedence,
   which side goes first?* `+` and `-` are equal rank and **left-to-right
   associative**, so `a + b - d` is `(a + b) - d`, not `a + (b - d)`.

Here is the table for every operator in this chapter, highest precedence
at the top. 

| Level | Operators (same line = same precedence)      | Associativity  | Kind             |
|:-----:|---------------------------------------------|----------------|------------------|
| 1     | `::`                                        | left to right  | scope            |
| 2     | `()`  `[]`  `.`  `->`  `x++`  `x--`         | left to right  | postfix          |
| 3     | `++x`  `--x`  `+x`  `-x`  `!`  `static_cast`| right to left  | unary (prefix)   |
| 4     | `*`  `/`  `%`                                | left to right  | multiplicative   |
| 5     | `+`  `-`                                     | left to right  | additive         |
| 6     | `<<`  `>>`                                   | left to right  | stream I/O       |
| 7     | `<`  `<=`  `>`  `>=`                         | left to right  | relational       |
| 8     | `==`  `!=`                                   | left to right  | equality         |
| 9     | `&&`                                         | left to right  | logical AND      |
| 10    | `\|\|`                                       | left to right  | logical OR       |
| 11    | `?:`                                         | right to left  | conditional      |
| 12    | `=`  `+=`  `-=`  `*=`  `/=`  `%=`            | right to left  | assignment       |
| 13    | `,`                                          | left to right  | comma            |

Most rows are left-to-right. We will unpack more of this as we go, but just be aware of the concept. 

### We can add parentheses anyway

You do not have to memorize the whole table. Two rules cover almost
everything:

- If precedence already groups it the way you mean, leave 
   it bare - extra parentheses just add noise.
- If you have to stop and think about it, **add the parentheses**. They
  cost nothing at runtime and the next reader does not have to consult
  the table.

```
   salary1 + salary2 * 12     ← fine, * clearly binds first
   (salary1 + salary2) * 12   ← parentheses REQUIRED to force + first
   (a + b) - c                ← redundant (left-to-right already), but harmless
```

### Compound assignment

Each of these rewrites `x = x OP y` in short form:

| You write | It means        | Start `x = 3` | After |
|-----------|-----------------|:-------------:|:-----:|
| `x += 7`  | `x = x + 7`     | 3             | 10    |
| `x -= 4`  | `x = x - 4`     | 3             | −1    |
| `x *= 5`  | `x = x * 5`     | 3             | 15    |
| `x /= 3`  | `x = x / 3`     | 3             | 1     |
| `x %= 2`  | `x = x % 2`     | 3             | 1     |

In the example the two friends pool their pay into a `pot`:

```cpp
int pot{salary1};
pot += salary2;   // pot = pot + salary2
pot -= 1200;      // pot = pot - 1200
```

---

## 5.3 Increment and decrement

`++` adds 1, `--` subtracts 1. The catch is **prefix vs postfix** when
the operator sits inside a larger expression.

| Operator | Name              | In `... = ++n` / `... = n++`                      |
|:--------:|-------------------|---------------------------------------------------|
| `++n`    | prefix increment  | increment `n` first, **then** use the new value   |
| `n++`    | postfix increment | use the **current** value, **then** increment `n` |
| `--n`    | prefix decrement  | decrement first, then use                         |
| `n--`    | postfix decrement | use current, then decrement                       |

Trace it with `cars_owned` starting at 5 (someone about to buy one more):

```
   int cars_owned{5};
   int handed_out{cars_owned++};   // handed_out = 5   ← old value handed out
                                   // cars_owned = 6   ← then bumped

   int cars_owned{5};
   int handed_out{++cars_owned};   // cars_owned = 6   ← bumped first
                                   // handed_out = 6   ← new value handed out
```

```
   postfix  cars_owned++ :   read ──► 5 ──► (use it)
                                   └──► cars_owned becomes 6

   prefix   ++cars_owned :   cars_owned becomes 6 ──► read ──► 6 ──► (use it)
```

As a **statement on its own line** the two forms are identical:

```cpp
++cars_owned;   // same effect as
cars_owned++;   // this
```

That standalone form is how you will write it ~95% of the time (stepping
a loop counter). The prefix/postfix difference only matters when you read
the result in the same expression - and code that does that is usually
harder to read. 

---

## 5.4 Relational and equality operators

Six operators, each producing a `bool` (`true` / `false`). `std::println`
prints those as the words `true` and `false`.

| Algebra | C++  | Sample     | Reads as                         |
|:-------:|:----:|------------|----------------------------------|
| >       | `>`  | `x > y`    | x is greater than y              |
| <       | `<`  | `x < y`    | x is less than y                 |
| ≥       | `>=` | `x >= y`   | x is greater than or equal to y  |
| ≤       | `<=` | `x <= y`   | x is less than or equal to y     |
| =       | `==` | `x == y`   | x is equal to y                  |
| ≠       | `!=` | `x != y`   | x is not equal to y              |

```
   salary1 = 3500, salary2 = 4000

   salary1 <  salary2   ──►  true
   salary1 == salary2   ──►  false
   salary1 >= salary2   ──►  false
```

The result is an ordinary value - name it and reuse it:

```cpp
bool first_earns_more{salary1 > salary2};
```

### `=` vs `==`

```
   if (salary1 = salary2)  { ... }   ← assigns salary2 to salary1, result is that value
   if (salary1 == salary2) { ... }   ← compares them   ✓ what you meant
```
Be careful: `=` is assignment, `==` is equality. 

---

## 5.5 `if` statements

Four shapes, built up one at a time.

### 1. Plain `if` - single selection

```
        ┌───────────────┐  false
   ────►│ age >= 18 ?   ├──────────►────┐
        └───────┬───────┘               │
                │ true                  │
                ▼                       │
        ┌───────────────┐               │
        │ print "adult" │               │
        └───────┬───────┘               │
                ▼                       ▼
                └──────────►────────────┘
```

```cpp
if (age >= 18) {
    std::println("adult");
}
```

### 2. `if` / `else` - double selection

```
      false   ┌───────────────┐   true
   ┌──────────┤ age >= 18 ?   ├──────────┐
   ▼          └───────────────┘          ▼
┌───────────────┐              ┌───────────────┐
│ print "minor" │              │ print "adult" │
└───────┬───────┘              └───────┬───────┘
        └──────────►────┬────◄─────────┘
                        ▼
```

```cpp
if (age >= 18) {
    std::println("adult");
}
else {
    std::println("minor");
}
```

### 3. `else if` ladder - the first true branch wins

```
   age = 34

   age >= 65 ?  ──true──►  "senior"   ──┐   (done - rest skipped)
      │ false                           │
   age >= 18 ?  ──true──►  "adult"  ────┤
      │ false                           │
   age >= 13 ?                          │
      │ false                           │
   age >= 0  ?                          │
      │ false                           │
   else ──────────►  "invalid age"      │
                                        ▼
```

```cpp
if      (age >= 65) { std::println("senior"); }
else if (age >= 18) { std::println("adult"); }
else if (age >= 13) { std::println("teenager"); }
else if (age >= 0)  { std::println("child"); }
else                { std::println("invalid age"); }
```

**Order matters.** Written the other way around:

```
   if (age >= 0) ... else if (age >= 65) ...
       ▲
       └─ age 34 matches HERE first and prints "child"; the >= 65
          branch is never reached.
```

Tests must go **most specific → least specific** (here: highest bound
first).

### 4. Nested `if` - a decision inside a branch

```
   age >= 18 ?
   ├─ yes ─► age >= 21 ?
   │         ├─ yes ─► "may enter the club"
   │         └─ no  ─► "adult, but under 21"
   └─ no  ─► (nothing)
```

```cpp
if (age >= 18) {
    if (age >= 21) {
        std::println("Adult, and old enough to enter the club.");
    }
    else {
        std::println("Adult, but under 21.");
    }
}
```

### Block scope

A variable declared inside `{ }` exists **only** inside those braces:

```cpp
if (age >= 18) {
    int years_since_adult{age - 18};              // ┐ lives only
    std::println("adult for {} years", years_since_adult); // │ in here
}                                                 // ┘
// years_since_adult does not exist here
```

```
   { ────────────────────────────────── }
     ^ years_since_adult born       ^ it's gone
```

---

## 5.6 Logical operators

Three operators that combine `bool` values.

### Truth tables

```
        &&  (AND)                ||  (OR)               !  (NOT)
   ┌───────┬───────┬─────┐  ┌───────┬───────┬─────┐  ┌───────┬─────┐
   │  a    │  b    │ a&&b│  │  a    │  b    │ a||b│  │  a    │  !a │
   ├───────┼───────┼─────┤  ├───────┼───────┼─────┤  ├───────┼─────┤
   │ false │ false │ F   │  │ false │ false │ F   │  │ false │ T   │
   │ false │ true  │ F   │  │ false │ true  │ T   │  │ true  │ F   │
   │ true  │ false │ F   │  │ true  │ false │ T   │  └───────┴─────┘
   │ true  │ true  │ T   │  │ true  │ true  │ T   │
   └───────┴───────┴─────┘  └───────┴───────┴─────┘
     T only when BOTH        T when EITHER
```

Build these on screen by printing every combination - it is the clearest
way to show them.

### Combining conditions

```cpp
bool locked{failed_attempts >= 3 && minutes_since_reset < 15};
bool allow_in{failed_attempts < 3 || minutes_since_reset >= 15};
```

### Short-circuit evaluation

`&&` evaluates its **left** side first. If the left side is `false`, the
whole `&&` is already `false` no matter what the right side is - so C++
**does not evaluate the right side at all**. `||` is the mirror image: a
`true` on the left settles it, and the right side is skipped.

```
   sessions != 0   &&   total_requests / sessions > 100
   └─────┬─────┘        └────────────────┬────────────┘
   evaluated first        only reached if the left side was true
```

Now walk it with `sessions = 0`:

```
   step 1   sessions != 0            ─►  0 != 0  ─►  false
   step 2   left side is false       ─►  && is already false
   step 3   total_requests / sessions ─►  NEVER RUNS
```

That last point is why this matters. `total_requests / sessions` with
`sessions == 0` is a division by zero, which crashes the program. Because
the `sessions != 0` test sits on the **left** of the `&&`, the division
on the right is only ever reached when `sessions` is non-zero. The cheap
test is **guarding** the risky one.

```cpp
bool heavy_user{sessions != 0 && total_requests / sessions > 100};
```

Order matters. Flip the two sides:

```
   total_requests / sessions > 100   &&   sessions != 0
   └──────────────┬──────────────┘
   runs FIRST, sessions is 0  ─►  divide by zero  ─►  crash
```

The guard only works when it is the left operand. This left-guard pattern
is a real idiom - you will see it again in 5.8 for sentinel loops.

### Where the logical operators sit

Here is the same precedence table from 5.2 again, so you do not have to
scroll back. Highest precedence at the top; operators on one line share a
level.

| Level | Operators (same line = same precedence)      | Associativity  | Kind             |
|:-----:|---------------------------------------------|----------------|------------------|
| 1     | `::`                                        | left to right  | scope            |
| 2     | `()`  `[]`  `.`  `->`  `x++`  `x--`         | left to right  | postfix          |
| 3     | `++x`  `--x`  `+x`  `-x`  `!`  `static_cast`| right to left  | unary (prefix)   |
| 4     | `*`  `/`  `%`                                | left to right  | multiplicative   |
| 5     | `+`  `-`                                     | left to right  | additive         |
| 6     | `<<`  `>>`                                   | left to right  | stream I/O       |
| 7     | `<`  `<=`  `>`  `>=`                         | left to right  | relational       |
| 8     | `==`  `!=`                                   | left to right  | equality         |
| 9     | `&&`                                         | left to right  | logical AND      |
| 10    | `\|\|`                                       | left to right  | logical OR       |
| 11    | `?:`                                         | right to left  | conditional      |
| 12    | `=`  `+=`  `-=`  `*=`  `/=`  `%=`            | right to left  | assignment       |
| 13    | `,`                                          | left to right  | comma            |

`&&` is **level 9** and `||` is **level 10** - below every arithmetic,
relational, and equality operator, and above only `?:`, assignment, and
the comma. That is why

```
   failed_attempts >= 3 && minutes_since_reset < 15
```

groups as `(failed_attempts >= 3) && (minutes_since_reset < 15)` with no
parentheses: both comparisons (level 7) run first, then `&&` (level 9)
combines the two `bool`s.

`&&` also outranks `||`, so a mixed expression groups the `&&` parts
first, exactly like `*` before `+`:

```
   a || b && c        ─►   a || (b && c)
```

If you actually mean "(a or b) and c", you must parenthesize it.

---

## 5.7 The ternary (conditional) operator

```
   condition  ?  value_if_true  :  value_if_false
   └───┬────┘     └─────┬─────┘     └──────┬─────┘
      bool          result if true    result if false
```

Unlike `if`, the whole thing **is a value**, so it drops straight into an
initializer or a print call:

```cpp
std::string category{age >= 18 ? "adult" : "child"};
std::println("You pay the {} rate.", age >= 18 ? "adult" : "child");
```

Same thing the long way:

```
   age >= 18 ? "adult" : "child"
   ─────────────────────────────
   is equivalent to

   if (age >= 18)  category = "adult";
   else            category = "child";
```

Both branches must produce the **same type**. In the example the string
version deduces `const char*` on both sides; a numeric version works the
same way with two `int`s:

```cpp
int ticket_price{age >= 18 ? 12 : 7};
```

Guidance:

- Use it for **simple either/or value choices**.
- Both branches must produce the **same type**.
- `a ? (b ? x : y) : z` - nesting `?:` inside `?:` reads badly. An
  `else if` ladder is clearer once there are more than two outcomes.

---

## 5.8 The `while` loop

```
   ┌──────────────► test condition ──false──► exit
   │                     │ true
   │                     ▼
   │                 run body
   │                     │
   └─────────────────────┘
```

Test **first**, then maybe run the body, then repeat.

### The bare mechanics

Before wiring `while` to anything useful, run it on its own. This loop
just prints a number and counts up:

```cpp
int loop_count{0};
while (loop_count < 5) {
    std::println("loop_count: {}", loop_count);
    ++loop_count;           // without this line, loop_count stays 0 forever
}
```

Step through every pass:

```
   pass │ loop_count │ loop_count < 5 │ prints │ after ++loop_count
   ─────┼────────────┼────────────────┼────────┼───────────────────
    1   │     0      │     true       │   0    │        1
    2   │     1      │     true       │   1    │        2
    3   │     2      │     true       │   2    │        3
    4   │     3      │     true       │   3    │        4
    5   │     4      │     true       │   4    │        5
    -   │     5      │     false      │   -    │  (loop exits)
```

Three moving parts, and every counter-controlled loop has all three:

```
   int loop_count{0};          ← 1. set the counter up before the loop
   while (loop_count < 5) {     ← 2. a condition that will eventually be false
       ...
       ++loop_count;            ← 3. an update that moves toward that condition
   }
```

Drop part 3 and `loop_count` is always `0`, the condition is always
`true`, and the loop never ends.

### Counter-controlled iteration - count known up front

Same three parts, now the body does real work - read a value each pass:

```
   int entered{0};              entered:  0 → 1 → 2 → 3 → 4 → 5
   while (entered < 5) {         test:     T   T   T   T   T   F ─► exit
       // read a score
       ++entered;   ◄── advance, or the loop never ends
   }
```

### Sentinel-controlled iteration - count NOT known

The user signals the end with a marker value (a **sentinel**), here `-1`.
This shape needs a **priming read** before the loop and a **second read
at the bottom** of the body:

```
   read  ────────────────┐   ("prime the pump")
                          ▼
   ┌──────────► score != -1 ? ──false──► exit
   │                 │ true
   │                 ▼
   │            process score
   │                 │
   │            read next score
   │                 │
   └─────────────────┘
```

```cpp
std::cin >> score;              // priming read
while (score != -1) {
    total += score;
    ++count;
    std::cin >> score;          // read the next before re-testing
}
```

### Guard the arithmetic that follows

```
   if the user typed -1 first:   count == 0
                                 total / count  ──►  UNDEFINED
```

```cpp
if (count != 0) {
    double average{static_cast<double>(total) / count};
    // ...
}
else {
    std::println("No scores entered.");
}
```

---

## 5.9 The `for` loop

We have seen that a `while` loop has three parts: the setup above it, 
the condition in the header, the update buriedin the body. `for` collects 
all three into **one line** so you can see them together.

```
   the SAME loop, two ways
   ───────────────────────

   int page{1};                  ┌── for (int page{1}; page <= 10; ++page)
   while (page <= 10) {          │        └───┬────┘  └────┬────┘  └──┬──┘
       std::print("{} ", page);  │          setup      condition   update
       ++page;                   │
   }                             └── std::print("{} ", page);
```

### The three parts of the header

```
   for ( init ; condition ; update )
         │        │           │
         │        │           └─ runs AFTER every pass through the body
         │        └───────────── checked BEFORE every pass (false ⇒ stop)
         └────────────────────── runs ONCE, before the first check

   for (int page{1}; page <= 10; ++page) { body }
        └─────┬────┘  └────┬───┘  └──┬─┘
         page starts   keep going   move page
           at 1        while <= 10   on by 1
```

### Order of execution

`init` happens once. Then the loop cycles **condition → body → update**
until the condition is false:

```
        ┌───────────────────────────────────────┐
        │                                       │
   init ─► condition ──true──► body ──► update ─┘
              │
            false
              │
              ▼
             exit
```

Traced for `for (int page{1}; page <= 10; ++page)`:

```
   pass │ page (at check) │ page <= 10 │ body prints │ ++page ⇒
   ─────┼─────────────────┼────────────┼─────────────┼─────────
    1   │       1         │   true     │     1       │    2
    2   │       2         │   true     │     2       │    3
    3   │       3         │   true     │     3       │    4
    …   │       …         │    …       │     …       │    …
   10   │      10         │   true     │    10       │   11
    -   │      11         │   false    │     -       │  (exit)
```

### Three variants, one shape

The update does not have to be `++`, and the count does not have to go
up:

```cpp
// count up 1..10
for (int page{1}; page <= 10; ++page)          { std::print("{} ", page); }

// step by 2 - only the left-hand (even) page numbers
for (int page{2}; page <= 20; page += 2)       { left_page_total += page; }

// count DOWN 5..1
for (int chapters_left{5}; chapters_left >= 1; --chapters_left)
                                              { std::print("{} ", chapters_left); }
```

```
   ++page      : 1 → 2 → 3 → 4 → 5 → ...        (condition: page <= 10)
   page += 2   : 2 → 4 → 6 → 8 → 10 → ...       (condition: page <= 20)
   --chapters  : 5 → 4 → 3 → 2 → 1 → 0          (condition: chapters_left >= 1)
```

### Nested `for` - building a table

Put a `for` inside a `for`. The **outer** loop runs once per row; the
**inner** loop runs fully each time, once per column. Here chapter `N`
has `N` sections:

```
   outer chapter = 1 ─► inner runs 1x   (1 section)
   outer chapter = 2 ─► inner runs 2x   (2 more sections)
   outer chapter = 3 ─► inner runs 3x
   outer chapter = 4 ─► inner runs 4x
   outer chapter = 5 ─► inner runs 5x

   sections_read grows:  1, 3, 6, 10, 15
```

```cpp
int sections_read{0};
for (int chapter{1}; chapter <= 5; ++chapter) {
    for (int section{1}; section <= chapter; ++section) {
        ++sections_read;                 // inner loop runs `chapter` times
    }
    std::println("After chapter {}: {} sections read", chapter, sections_read);
}
```

Walk the two counters together:

```
   chapter │ section goes │ ++sections_read this row │ running total
   ────────┼──────────────┼─────────────────────────┼──────────────
      1    │ 1            │           1             │      1
      2    │ 1, 2         │           2             │      3
      3    │ 1, 2, 3      │           3             │      6
      4    │ 1, 2, 3, 4   │           4             │     10
      5    │ 1,2,3,4,5    │           5             │     15
```

### Scope

Each loop variable exists only inside its own loop body. Once the loop
ends, `page`, `chapters_left`, `chapter`, `section` are all gone - you
cannot read them afterward.

---

## 5.10 The `do...while` loop

```
   ┌────► run body
   │          │
   │          ▼
   │     test condition ──true──┐
   │          │ false           │
   │          ▼                 │
   │        exit                │
   └────────────────────────────┘
```

Body **first**, condition **after** - so the body always runs **at least
once**, even when the condition is false from the start.

```
   while     :  CHECK, then maybe do        (body may run 0 times)
   do...while:  DO, then check whether again (body runs >= 1 time)
```

Pick it when "do it, then decide whether to repeat" fits - the classic
case is a prompt that must appear at least once:

```cpp
int guess{};
do {
    std::print("Guess the die roll (1-6): ");
    std::cin >> guess;
} while (guess < 1 || guess > 6);   // ◄── note the trailing ;
```

A plain `while` here would need the prompt written twice - once before
the loop to prime it, once inside. `do...while` asks first, then only
loops back if the answer was out of range:

```
   ask ──► read guess ──► guess valid? ──yes──► carry on
              ▲                 │
              │ no              │
              └─────────────────┘

   guess = 4   ─►  body runs once, 1..6 check passes, loop exits
   guess = 9   ─►  body runs, check fails, "try again", body runs again
```

The semicolon after `while (...)` is easy to forget.

The counting example shows the other shape - a straight `for`-style loop
written with `do...while`, which runs the body for `roll` = 1..10:

```cpp
int roll{1};
do {
    std::print("{} ", roll);
    ++roll;
} while (roll <= 10);
```

---

## 5.11 The `switch` statement

Compare **one integer expression** against a list of constant `case`
labels and jump to the match. Cleaner than a long `else if` chain of
equality tests.

The example buckets a review score (0-100) into a star rating. Dividing
by 20 turns a whole range of scores into a single small number:

```
   score       score / 20    meaning
   ────────────────────────────────────
     0 .. 19       0          1 star
    20 .. 39       1          2 stars
    40 .. 59       2          3 stars
    60 .. 79       3          4 stars
    80 .. 99       4          5 stars
    100            5          5 stars   ◄── note: 100/20 is a clean 5
```

```
   switch (score / 20)          score   score/20   lands on
   ┌──────────────────┐         ─────────────────────────────
   │ case 0: ───► 1★   │          12        0        case 0
   │ case 1: ───► 2★   │          33        1        case 1
   │ case 2: ───► 3★   │          47        2        case 2
   │ case 3: ───► 4★   │          65        3        case 3
   │ case 4: ──┐       │          88        4        case 4 ─┐
   │ case 5: ──┴► 5★   │         100        5        case 5 ─┴► same body
   │ default: ─► ignore│          -7       -1        default
   └──────────────────┘
```

```cpp
switch (score / 20) {
    case 0:
        ++oneStar;
        break;
    case 1:
        ++twoStar;
        break;
    case 2:
        ++threeStar;
        break;
    case 3:
        ++fourStar;
        break;
    case 4:                // 80-99  ─┐  both reach the same body,
    case 5:                // 100    ─┘  so 4 "falls through" into 5
        ++fiveStar;
        break;
    default:               // score outside 0-100
        std::println("  ignoring out-of-range score {}", score);
        break;
}
```

### Fall-through

```
   case 1:
       ++twoStar;
       break;   ◄── STOP here, jump past the whole switch

   case 1:
       ++twoStar;
       ▼         ◄── NO break: execution falls straight into
   case 2:           case 2's body and runs ++threeStar too
       ++threeStar;
```

Stacking `case 4:` directly on top of `case 5:` with nothing between them
is fall-through used **on purpose**: `case 4` has an empty body, so
control slides straight into `case 5`'s body. Both 80-99 and exactly 100
end up counted as five stars.

Forgetting a `break` in the middle of a normal `case` is the same
mechanism happening **by accident**, and it is a classic bug.

### Rules

- `case` labels must be **compile-time constants**, not variables.
- The controlling expression must be an integer type (or `char`, or an
  `enum`).

The example reads scores until end-of-file:

```
   while (std::cin >> score)   ── true while a number was read
                              ── false at end-of-file:
                                    Windows      : Ctrl+Z then Enter
                                    macOS / Linux: Ctrl+D
```

---

## 5.12 `break` and `continue`

Both of these are jump statements you put **inside a loop body** to
change the normal flow:

- **`break`** - abandon the loop completely. Execution jumps to the first
  statement *after* the loop. No more iterations, no matter how far the
  counter still has to go.
- **`continue`** - abandon only the *current* pass through the body. The
  loop itself keeps running: execution jumps to the loop's next step (the
  `++i` update in a `for`, the condition re-check in a `while`).

In the diagram below, "the body" is whatever statements sit between the
loop's braces - the real work the loop does each pass. Reading them
top to bottom, `break`/`continue` cut that top-to-bottom flow short:

```
   break                              continue
   ─────                              ────────
   for (...) {                        for (...) {
       (first part of body)               (first part of body)
       if (found it) break; ──┐           if (skip this one) continue; ─┐
       (rest of body)         │           (rest of body)  ◄─ NOT run    │
   }                          │       }        ▲                        │
   (code after the loop) ◄────┘       (back to the for's ++ and re-test)┘
```

`break` leaves the loop entirely; `continue` only skips the *rest of this
pass* and lets the loop carry on.

### The page-reading example

We walk page numbers 1..10. `break` stops at a torn-out page; `continue`
skips a blank one.

```cpp
int page{};
for (page = 1; page <= 10; ++page) {
    if (page == 5) { break; }        // page torn out - stop reading
    std::print("{} ", page);         // only reached for pages 1..4
}
// page is still 5 here (see note below)

for (int p{1}; p <= 10; ++p) {
    if (p == 5) { continue; }        // page 5 is blank - skip just this pass
    std::print("{} ", p);            // reached for every page except 5
}
```

```
   break at page 5:      1  2  3  4  ✗
                                     └─ loop ends; pages 6..10 never seen

   continue at page 5:   1  2  3  4  ↷  6  7  8  9  10
                                    │
                                    └─ page 5's std::print is skipped,
                                       but the loop keeps going
```

**Why `page` is still `5` after the first loop.** The control variable is
declared *before* the loop (`int page{};`), not in the header. So it
outlives the loop, and you can read it afterward to find out *which*
page you stopped on. If it were declared in the header
(`for (int page = 1; ...)`) it would be gone the moment the loop ends,
exactly like the loop variables in 5.9. Declaring it outside is a
deliberate choice here so the "we stopped at page 5" information
survives.

### The `continue` gotcha in a `while` loop

`continue` means "go to the loop's next step". In a `for` loop that next
step is the update in the header, so the counter still moves:

```
   for (int p{1}; p <= 10; ++p) {
       if (p == 5) continue;   ──►  runs ++p  ──►  re-checks p <= 10  ──►  next pass
   }
```

In a `while` loop there is no update in the header - *you* are
responsible for advancing the counter inside the body. `continue` jumps
straight back to the condition and skips whatever body code came after
it, including your `++p`:

```
   while (p < 10) {
       if (p == 5) continue;   ──►  jumps straight back to  p < 10
       ++p;                     ▲         (this line is NEVER reached
   }                            └──────────  once p becomes 5)
```

So this loop is an **infinite loop**:

```cpp
int p{0};
while (p < 10) {
    if (p == 5) { continue; }   // when p == 5, we jump back to the top...
    ++p;                        // ...and never get here to make p go past 5
}
// p is stuck at 5 forever; the program hangs
```

The fix is to advance the counter *before* the `continue`, or to
restructure so the `++p` always runs:

```cpp
int p{0};
while (p < 10) {
    int current{p};
    ++p;                        // advance FIRST, unconditionally
    if (current == 5) { continue; }   // now safe - p has already moved
    std::print("{} ", current);
}
```

### `break` and `continue` only affect the innermost loop

When loops are nested, a `break` or `continue` inside the inner loop acts
on the **inner** loop only. The outer loop is untouched:

```cpp
for (int row{1}; row <= 3; ++row) {
    for (int col{1}; col <= 3; ++col) {
        if (col == 2) { break; }   // breaks the col loop, NOT the row loop
        std::print("({},{}) ", row, col);
    }
}
// prints (1,1) (2,1) (3,1) - the outer loop still runs all 3 rows
```

There is no built-in "break out of both loops" statement. If you need
that, the common options are a flag variable the outer loop checks, or
moving the nested loops into their own function and using `return`.

---

## 5.13 `if` and `switch` with an initializer

Since C++17 you can declare a variable in the header, before the
condition, separated by a `;`:

```
   if ( init-statement ; condition ) { ... } else { ... }
        └─────┬───────┘
        variable is in scope for the WHOLE if / else,
        and nowhere after it
```

```cpp
if (int grade{87}; grade >= 60) {
    std::println("grade {} is a pass", grade);
}
else {
    std::println("grade {} is a fail", grade);   // grade visible here too
}
// grade does not exist here
```

```
   ┌── if (int grade{87}; grade >= 60) { ... } else { ... } ──┐
   grade born                                          grade gone
```

`switch` takes the same form:

```cpp
switch (int score{73}; score / 10) {
    case 10:
    case 9:  std::println("{}: A", score); break;
    // ...
}
```

Use it whenever a value exists **only** to drive one decision - it keeps
the variable's lifetime exactly as short as the decision. This is the
block-scope idea from 5.5, applied to the condition itself.

---

## 5.14 Floating-point pitfalls

Floating-point types store values in **binary**. Most decimal fractions
have **no exact binary form** - the same way 1/3 has no exact decimal
form (0.3333...).

```
   0.1  in binary  = 0.0001100110011001100...   (repeats forever)
   stored as       ≈ 0.1000000000000000055511151231257827
```

So small errors creep in and add up:

```cpp
double sum{0.1 + 0.2};
std::println("{:.17f}", sum);    // 0.30000000000000004
std::println("{}", sum == 0.3);  // false   ◄── surprise
```

```
   0.1 + 0.2  ─►  0.30000000000000004
        0.3   ─►  0.29999999999999999
                  └──────────┬──────┘
                  not bit-for-bit equal
```

### Never compare floating-point with `==`

Check they are **close enough** - within a small tolerance (epsilon):

```
   | a - b |  <  epsilon        e.g. epsilon = 1e-9
```

```cpp
bool close_enough{std::fabs(sum - 0.3) < 1e-9};   // <cmath>
```

### Money: format, don't round the value

A compound-interest table, every amount to exactly 2 decimals:

```
   Year    Amount on deposit
      1              1050.00
      2              1102.50
      3              1157.63
     ...
```

```cpp
std::println("{:>4}  {:>18.2f}", year, amount);   // {:.2f} = 2 decimals
```

Contrast the two styles - the one lecture where showing both earns its
place:

```
   classic:  std::cout << std::fixed << std::setprecision(2);   // <iomanip>
             std::cout << amount << "\n";
             ▲ sets STREAM STATE - stays on until you change it back

   modern:   std::println("{:.2f}", amount);
             ▲ applies to just THIS value - nothing to set up or reset
```

---

## 5.15 First look at `std::string`

We used `std::string` in passing in chapter 4. Here is its own moment
before the chapter closes. Needs `<string>`.

```cpp
std::string first{"happy"};
std::string second{" birthday"};
std::string empty_one{};        // length 0
```

| Member            | Does                          | Example → result             |
|-------------------|-------------------------------|------------------------------|
| `.length()` / `.size()` | character count (same thing) | `first.length()` → `5`   |
| `.empty()`        | `true` if no characters       | `empty_one.empty()` → `true` |
| `==` / `!=`       | compare **contents**          | `first == second` → `false`  |
| `+`               | join into a new string        | `first + second` → `"happy birthday"` |
| `.starts_with(x)` | C++20 prefix check            | `phrase.starts_with("happy")` → `true` |
| `.ends_with(x)`   | C++20 suffix check            | `phrase.ends_with("day")` → `true` |

```
   "happy"  +  " birthday"   ─►   "happy birthday"
   └──┬──┘     └────┬─────┘        └──────┬───────┘
   first        second          a brand-new string
```

Kept to just these members - the deeper string API is a later chapter.

---

## 5.16 Assignment

`main.cpp` holds six exercises as stubs; `main_solution.cpp` solves all
six using only this chapter's tools. Built as two executables (`rooster`,
`rooster_solution`) by the same `CMakeLists.txt` pattern as chapter 4's
assignment.

| # | Exercise                 | Tools exercised                                   |
|---|--------------------------|--------------------------------------------------|
| 1 | Letter grade classifier  | `else if` ladder + `?:` for the pass/fail line   |
| 2 | Average of `n` scores    | counter-controlled `for`, real division, zero-guard |
| 3 | Sentinel-controlled tally| primed `while`, `continue` to reject 0-100 outliers |
| 4 | Grade histogram          | `while (std::cin >> grade)` + `switch` + inner bar loop |
| 5 | Retry prompt             | `do...while` that always prompts once            |
| 6 | String report line       | `+`, `.length()`, `.starts_with` / `.ends_with`  |

Sample run of exercise 4:

```
   Enter grades, end-of-file to finish: 95 88 82 71 60 55 91 <Ctrl+Z>
   A: ***
   B: **
   C: *
   D: *
   F: *
```

By the end of this chapter the student can express **decisions** and
**repetition** - everything needed before moving on to functions.
