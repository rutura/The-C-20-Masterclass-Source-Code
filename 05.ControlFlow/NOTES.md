# Control Flow

In the last chapters, we covered variables and datatypes. Every program so far has run
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

### `=` vs `==`

```
   if (salary1 = salary2)  { ... }   ← assigns salary2 to salary1, result is that value
   if (salary1 == salary2) { ... }   ← compares them   ✓ what you meant
```
Be careful: `=` is assignment, `==` is equality. 

---

## 5.6 Logical operators

Three operators that combine `bool` values: AND, OR and NOT.

### Truth tables

```
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

```cpp
bool heavy_user{sessions != 0 && total_requests / sessions > 100};
```

### Where the logical operators sit

Here is the precedence table with the logical operators.

| Level | Operators (same line = same precedence)      | Associativity  | Kind             |
|:-----:|----------------------------------------------|----------------|------------------|
| 1     | `::`                                         | left to right  | scope            |
| 2     | `()`  `[]`  `.`  `->`  `x++`  `x--`          | left to right  | postfix          |
| 3     | `++x`  `--x`  `+x`  `-x`  `!`  `static_cast` | right to left  | unary (prefix)   |
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
the condition in the header, the update buried in the body. `for` collects 
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
This loop is practical when the job has to be done at least once.

Body **first**, condition **after**

```
   while     :  CHECK, then maybe do        (body may run 0 times)
   do...while:  DO, then check whether again (body runs >= 1 time)
```

The counting example shows the other shape - a straight `for`-style loop
written with `do...while`, which runs the body for `roll` = 1..10:

```cpp
int roll{1};
do {
    std::print("{} ", roll);
    ++roll;
} while (roll <= 10);
```

### Useful when something needs to be done before the test.

The example below needs the user to type in the guess, so we do something 
before we check. It's very suitable for a do while loop.

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

The semicolon after `while (...)` is easy to forget.

---

## 5.11 The `switch` statement

Compare **one integer expression** against a list of constant `case`
labels and jump to the match. This is cleaner than a long `else if` chain of
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
// using if/else if
int bucket{score / 20};
if (bucket == 0) {
    ++one_star;
}
else if (bucket == 1) {
    ++two_star;
}
else if (bucket == 2) {
    ++three_star;
}
else if (bucket == 3) {
    ++four_star;
}
else if (bucket == 4 || bucket == 5) {   
    ++five_star;                          
}
else {
    std::println("  ignoring out-of-range score {}", score);
}
```

```cpp
switch (score / 20) {
    case 0:
        ++one_star;
        break;
    case 1:
        ++two_star;
        break;
    case 2:
        ++three_star;
        break;
    case 3:
        ++four_star;
        break;
    case 4:                // 80-99  ─┐  both reach the same body,
    case 5:                // 100    ─┘  so 4 "falls through" into 5
        ++five_star;
        break;
    default:               // score outside 0-100
        std::println("  ignoring out-of-range score {}", score);
        break;
}
```

### Fall-through

```
   case 1:
       ++two_star;
       break;   ◄── STOP here, jump past the whole switch

   case 1:
       ++two_star;
       ▼         ◄── NO break: execution falls straight into
   case 2:           case 2's body and runs ++three_star too
       ++three_star;
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

The example reads scores until the user types the sentinel `-1`, the same
convention 5.8's while-loop example already used:

```
   while (std::cin >> score && score != -1)
          └──────┬──────┘      └────┬────┘
          a number was read     and it isn't the -1 sentinel
```

If the user types `-1`, `score != -1` is `false` and the loop stops before
the switch ever runs - `-1 / 20` never gets a chance to hit `default`.

### Other things you can switch on

The controlling expression just has to boil down to an integer, so the
`case` labels aren't limited to bucketed scores. A few other compile-time
constants that show up often:

```cpp
// a menu choice typed as a plain number
switch (menu_choice) {
    case 1: /* add item */    break;
    case 2: /* remove item */ break;
    case 3: /* checkout */    break;
    default: /* invalid */    break;
}

// a char works too - it's just a small integer under the hood
switch (grade) {
    case 'A': std::println("Excellent"); break;
    case 'B': std::println("Good");      break;
    case 'C': std::println("Passing");   break;
    default:  std::println("Unknown grade"); break;
}
```

An `enum`/`enum class` is the same idea and is where `switch` really earns
its keep - the compiler can warn you if a case is missing:

```cpp
enum class Direction { North, South, East, West };

switch (direction) {
    case Direction::North: std::println("Heading up");    break;
    case Direction::South: std::println("Heading down");  break;
    case Direction::East:  std::println("Heading right"); break;
    case Direction::West:  std::println("Heading left");  break;
}
```

### The same logic as `if`/`else if`

Every `switch` here could be written as an `else if` ladder instead. 
But it won't be as readable!

---

## 5.12 `break` and `continue`

Both are jump statements you put **inside a loop body** to change the
normal flow:

- **`break`** - leave the loop completely, right now. No more iterations.
- **`continue`** - skip the *rest of this pass only*. The loop moves on
  to its next iteration as normal.

```cpp
const std::string name{"Daniel"};

for (int i{0}; i < 10; ++i) {
    std::println("[{}]: Your name is {}", i, name);
}
```

```
   i:   0    1    2    3    4    5    6    7    8    9
        │    │    │    │    │    │    │    │    │    │
        ▼    ▼    ▼    ▼    ▼    ▼    ▼    ▼    ▼    ▼
   [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]     ◄── all 10 printed
```

### `break` - stop at `i == 5`

```cpp
for (int i{0}; i < 10; ++i) {
    if (i == 5) { break; }     // stop dead, don't print 5 or anything after
    std::println("[{}]: Your name is {}", i, name);
}
```

```
   i:   0    1    2    3    4    5    6    7    8    9
        │    │    │    │    │    │
        ▼    ▼    ▼    ▼    ▼    ✗  ◄── break fires here
       [0]  [1]  [2]  [3]  [4]            loop ends immediately
                                       6..9 are never even reached
```

### `continue` - skip just `i == 5`

```cpp
for (int i{0}; i < 10; ++i) {
    if (i == 5) { continue; }  // skip only this pass's println
    std::println("[{}]: Your name is {}", i, name);
}
```

```
   i:   0    1    2    3    4    5    6    7    8    9
        │    │    │    │    │    │    │    │    │    │
        ▼    ▼    ▼    ▼    ▼    ↷    ▼    ▼    ▼    ▼
   [0]  [1]  [2]  [3]  [4]      [6]  [7]  [8]  [9]     ◄── [5] skipped,
                            └─ println skipped,             loop keeps going
                               but ++i still runs
```

Side by side, the difference is: `break` cuts the whole loop short;
`continue` only cuts the current pass short.

```
   break:     [0] [1] [2] [3] [4]                          ← stops for good
   continue:  [0] [1] [2] [3] [4]      [6] [7] [8] [9]      ← keeps going
                                  └ 5 missing, rest intact ┘
```

---

## 5.13 First look at `std::string`

We used `std::string` in passing in chapter 4. Here is its own moment
before the chapter closes. Needs `<string>`.

A `std::string` is an object that holds a piece of text - a sequence of
characters - and manages its own memory. It grows and shrinks as needed;
you never say how long it is up front. The example builds a filename out
of a base name and an extension.

```cpp
std::string base{"report"};      // 6 characters
std::string extension{".pdf"};   // 4 characters
std::string suffix{};            // empty - no characters at all
```

An empty string (`std::string suffix{};` or `std::string suffix{""};`)
is a perfectly valid string; it just has length 0. It is not the same as
an uninitialized variable - it is a real, usable object holding no text.

### `.length()` and `.size()` - how many characters

The two names do **exactly** the same thing; `.size()` is the name shared
with the other standard containers, `.length()` reads more naturally for
text. Pick one and be consistent.

```
   base       "report"    ─►  .length() == 6
   extension  ".pdf"      ─►  .length() == 4   (the dot counts)
   suffix     ""          ─►  .length() == 0
```

### `.empty()` - is there any text at all

`str.empty()` returns `true` when the string has zero characters. It is
the clear way to ask that question - clearer than `str.length() == 0`,
and (for large strings) cannot be slower.

```
   suffix.empty()      ─►  true
   base.empty()        ─►  false
```

### `==` and `!=` - compare the contents

For `std::string`, `==` compares the **text**, character by character -
not the addresses, not the lengths alone. This is what you almost always
want, and it works just like comparing two `int`s.

```
   base == extension    ─►  "report" vs ".pdf"   ─►  false
   base != extension    ─►                            true
   base == "report"     ─►  true   (compare against a literal directly)
```

### `+` - join two strings into a new one

`a + b` (concatenation) produces a **brand-new** string containing all of
`a` followed by all of `b`. Neither `a` nor `b` is modified.

```
   base        extension
   "report"  +  ".pdf"     ─►   "report.pdf"
   └──┬───┘    └──┬──┘          └─────┬────┘
    unchanged   unchanged   a new string, length 6 + 4 = 10
```

```cpp
std::string filename{base + extension};   // filename is "report.pdf"
// base is still "report", extension is still ".pdf"
```

### `.starts_with(...)` and `.ends_with(...)` - C++20 prefix / suffix tests

Each returns a `bool`: does the string begin (or end) with the given
piece of text? Handy for checks like "is this a PDF?" without pulling in
anything heavier.

```
   filename = "report.pdf"
              └────┬───┘└┬─┘
             starts_with  ends_with
              ("report")   (".pdf")

   filename.starts_with("report")  ─►  true
   filename.ends_with(".pdf")      ─►  true
   filename.ends_with(".txt")      ─►  false
```

### Summary

| Member                  | Does                        | On `filename` = `"report.pdf"` |
|-------------------------|-----------------------------|--------------------------------|
| `.length()` / `.size()` | character count (same thing)| `10`                           |
| `.empty()`              | `true` if no characters     | `false`                        |
| `==` / `!=`             | compare **contents**        | `filename == "report.pdf"` → `true` |
| `+`                     | join into a **new** string  | `base + extension` → `"report.pdf"` |
| `.starts_with(x)`       | C++20 prefix check          | `.starts_with("report")` → `true` |
| `.ends_with(x)`         | C++20 suffix check          | `.ends_with(".pdf")` → `true`   |

Kept to just these members - the deeper string API is a later chapter.

---

## 5.15 A first taste of files

Everything so far has read from the keyboard and written to the console.
This lecture is a bonus - a bridge to the chapters ahead - that swaps
those for a **file on disk**. It is the one piece of this chapter that is
not in the core reference material; treat it as a preview, not something
you will be tested on here.

### A file is just another stream

You already know two streams:

```
   std::cout  <<  "text"      characters go OUT  ──►  console
   std::cin   >>  variable    characters come IN ◄──  keyboard
```

Files work the exact same way, with two new stream types from
`<fstream>`:

```
   std::ofstream  out{"names.txt"};   out << "text";   ──►  the file
   std::ifstream  in {"names.txt"};   getline(in, s);  ◄──  the file
```

- **`ofstream`** = *output* file stream. Same `<<` as `std::cout`, aimed
  at a file. Opening it **creates the file if it does not exist, and
  wipes it if it does.**
- **`ifstream`** = *input* file stream. The file counterpart of
  `std::cin`.

The lecture is in two programs: `write.cpp` (builds `rooster_write`)
creates `names.txt`, then `read.cpp` (builds `rooster_read`) reads it
back.

```
   rooster_write ──writes──►  [ names.txt ]  ──read by──►  rooster_read
                                one name
                                per line
```

### Two targets in one `CMakeLists.txt`

Every lecture so far had one source file and one program. This one has
**two** independent programs from one folder, so the `CMakeLists.txt`
declares **two build targets** - one `add_executable` per `.cpp`:

```cmake
cmake_minimum_required(VERSION 3.20)
project(rooster)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rooster_write write.cpp)   # target 1
add_executable(rooster_read  read.cpp)    # target 2
```

A **target** is just a named thing CMake knows how to build. Here each
target is an executable: `rooster_write` compiled from `write.cpp`,
`rooster_read` from `read.cpp`. They share nothing and build
independently. 

The shape is the same in every toolset: **one build step produces both
executables**, then you **pick which one to run**, and run them in order
- `rooster_write` first (it creates `names.txt`), then `rooster_read`.
Here is where the buttons are.

**Command line**

- Build both: `cmake -B build`, then `cmake --build build` - this builds
  *every* target.
- Run: `./build/rooster_write`, then `./build/rooster_read`.
- On Windows the exes are usually under a config folder:
  `.\build\Debug\rooster_write.exe`, then `.\build\Debug\rooster_read.exe`.

**Visual Studio** (open the folder as a CMake project)

- Build both: *Build → Build All* compiles every target at once.
- Run: choose the target in the **Startup Item** dropdown on the top
  toolbar, run it, then switch the dropdown to the other target and run
  again.

**Qt Creator**

- Build both: the hammer (Build) button builds every target in the
  project.
- Run: the green **Run** button only runs the *active* target. Set the
  active one in the run selector at the bottom-left (the monitor icon),
  or via *Projects → Build & Run → Run → Run configuration*.
- Run `rooster_write`, then switch the active target to `rooster_read`
  and run again.

**VS Code + CMake Tools**

- Build both: *CMake: Build*, or the **Build** button in the status bar -
  builds all targets.
- Run: click the **[launch target]** name in the status bar to pick one,
  then press the ▶ button. Switch the target and run again.

### Writing - `write.cpp`

```cpp
std::ofstream out{"names.txt"};
if (!out) {                       // did the file actually open?
    std::println("Could not open names.txt for writing.");
    return 1;
}

for (const std::string& name : {"Ada", "Alan", "Grace", "Linus", "Bjarne"}) {
    out << name << '\n';          // '\n' puts each name on its own line
}
out.close();
```

`if (!out)` is the same idea as guarding a division - check the operation
is valid before you depend on it. A file open can fail (a read-only
folder, a bad path), and writing to a failed stream silently does
nothing.

The `'\n'` after each name matters: it is what makes each name its own
line, and `read.cpp` reads the file **one line at a time**.

### Reading - `read.cpp`

```cpp
std::ifstream in{"names.txt"};
if (!in) {
    std::println("Could not open names.txt. Run rooster_write first.");
    return 1;
}

std::string name{};
int count{0};
while (std::getline(in, name)) {  // one pass per line in the file
    ++count;
    std::println("{}: {}", count, name);
}
std::println("Read {} names from names.txt", count);
```

`std::getline(in, name)` reads characters into `name` up to (and
discarding) the next newline. It returns the stream, and a stream tests
`false` once it hits the end of the file - so `while (std::getline(...))`
is the **same shape** as `while (std::cin >> grade)` from the `switch`
lecture, just pulling lines from a file instead of numbers from the
keyboard. The `count` is the counter pattern from 5.8, reused.

### The working directory - where `names.txt` actually goes

This trips up almost everyone the first time. The filename `"names.txt"`
has **no folder in it**, so the program creates and looks for the file in
its **working directory** (also called the "current directory") - and
that is *not* necessarily the folder your `write.cpp` lives in.

The working directory is: **the folder that was current in whatever
launched the program.**

| How you run it                         | Working directory is usually...                     |
|----------------------------------------|-----------------------------------------------------|
| Double-click the `.exe`                | the folder the `.exe` is in                         |
| Terminal: `cd somewhere` then run it   | `somewhere` (wherever you `cd`'d to)                |
| Visual Studio (F5 / Ctrl+F5)           | the project's build folder, e.g. `out/build/x64-Debug/` |
| Qt Creator (green Run button)          | the **build** directory shown in *Projects → Build & Run*, not the source folder |
| VS Code + CMake Tools                  | the folder set by `cmake.launchTargetPath` / your `launch.json` `cwd`, often `build/` |

So after running `rooster_write`, `names.txt` will **not** appear next to
`write.cpp`. It appears next to the compiled `rooster_write` executable,
somewhere under your build folder.

**How to find it, three reliable ways:**

1. **Ask the program.** Add this near the top of `main` and run it once:

   ```cpp
   #include <filesystem>
   std::println("working directory: {}",
                std::filesystem::current_path().string());
   ```

   It prints the exact absolute path. `names.txt` is in that folder.

2. **Search for it.** After running `rooster_write`, search your project
   tree for `names.txt`:
   - Windows Explorer search box, from the project root
   - or a terminal: `dir /s /b names.txt` (Windows), `find . -name names.txt` (macOS/Linux)

3. **Run from a folder you choose.** Open a terminal, `cd` into a folder
   you can see (say the lecture folder), and run the executable **by its
   full path** from there:

   ```
   cd  D:\...\05.ControlFlow\5.15FilesIntro
   .\out\build\...\rooster_write.exe
   ```

   Now `names.txt` lands in `5.15FilesIntro`, because that is the working
   directory you launched from.

**Whatever you do, run `rooster_write` before `rooster_read`, from the
same working directory.** If `read.cpp` prints "Could not open
names.txt", it is almost always one of: you skipped `rooster_write`, or
you ran the two programs from different directories.

Two run of the pair, from the same directory:

```
   > rooster_write
   Wrote 5 names to names.txt

   > rooster_read
   1: Ada
   2: Alan
   3: Grace
   4: Linus
   5: Bjarne
   Read 5 names from names.txt
```
