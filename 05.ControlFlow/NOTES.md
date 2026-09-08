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
   score1 = 88, score2 = 92

   score1 <  score2   ──►  true
   score1 == score2   ──►  false
   score1 >= score2   ──►  false
```

The result is an ordinary value - name it and reuse it:

```cpp
bool first_is_better{score1 > score2};
```

### `=` vs `==`

```
   if (x = 5)  { ... }     ← assigns 5 to x, condition is always true
   if (x == 5) { ... }     ← compares x with 5   ✓ what you meant
```
Be careful: `=` is assignment, `==` is equality. 

---

## 5.5 `if` statements

Four shapes, built up one at a time.

### 1. Plain `if` - single selection

```
        ┌───────────────┐  false
   ────►│ grade >= 60 ? ├──────────►────┐
        └───────┬───────┘               │
                │ true                  │
                ▼                       │
        ┌───────────────┐               │
        │ print "Passed"│               │
        └───────┬───────┘               │
                ▼                       ▼
                └──────────►────────────┘
```

```cpp
if (grade >= 60) {
    std::println("Passed");
}
```

### 2. `if` / `else` - double selection

```
      false   ┌───────────────┐   true
   ┌──────────┤ grade >= 60 ? ├──────────┐
   ▼          └───────────────┘          ▼
┌───────────────┐              ┌───────────────┐
│ print "Failed"│              │ print "Passed"│
└───────┬───────┘              └───────┬───────┘
        └──────────►────┬────◄─────────┘
                        ▼
```

```cpp
if (grade >= 60) {
    std::println("Passed");
}
else {
    std::println("Failed");
}
```

### 3. `else if` ladder - the first true branch wins

```
   grade = 95

   grade >= 90 ?  ──true──►  "A"   ──┐   (done - rest skipped)
      │ false                        │
   grade >= 80 ?                     │
      │ false                        │
   grade >= 70 ?                     │
      │ false                        │
   grade >= 60 ?                     │
      │ false                        │
   else ──────────►  "F"             │
                                     ▼
```

```cpp
if      (grade >= 90) { std::println("A"); }
else if (grade >= 80) { std::println("B"); }
else if (grade >= 70) { std::println("C"); }
else if (grade >= 60) { std::println("D"); }
else                  { std::println("F"); }
```

**Order matters.** Written the other way around:

```
   if (grade >= 60) ... else if (grade >= 90) ...
       ▲
       └─ grade 95 matches HERE first and prints "D"; the >= 90
          branch is never reached.
```

Tests must go **most specific → least specific**.

### 4. Nested `if` - a decision inside a branch

```
   grade >= 60 ?
   ├─ yes ─► grade >= 90 ?
   │         ├─ yes ─► "Passed - honor roll"
   │         └─ no  ─► "Passed"
   └─ no  ─► (nothing)
```

```cpp
if (grade >= 60) {
    if (grade >= 90) {
        std::println("Passed - eligible for the honor roll.");
    }
    else {
        std::println("Passed.");
    }
}
```

### Block scope

A variable declared inside `{ }` exists **only** inside those braces:

```cpp
if (grade >= 60) {
    int margin{grade - 60};        // ┐ margin lives
    std::println("+{} pts", margin);// │ only in here
}                                   // ┘
// margin does not exist here
```

```
   { ─────────────────────────── }
     ^ margin born            ^ margin gone
```

That rule is exactly what makes the initializer form in 5.13 useful, so
plant it here.

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
bool passes{grade >= 60 && attendance_pct >= 75};
bool needs_review{grade < 60 || attendance_pct < 50};
```

### Short-circuit evaluation

`&&` stops the instant it meets a `false`; `||` stops at the first
`true`. The rest of the expression is **never evaluated**.

```
   count != 0   &&   100 / count > 10
   └────┬────┘        └───────┬──────┘
   evaluated first     only evaluated if the left side was true

   count == 0  ─►  left side false  ─►  division SKIPPED  (no crash)
```

```cpp
bool safe{count != 0 && 100 / count > 10};   // divide-by-zero avoided
```

Swap the two operands and the program crashes when `count` is `0`. This
left-guard ordering is a real idiom, not a curiosity.

### Where the logical operators sit

Back on the precedence table in 5.2, `&&` is **level 9** and `||` is
**level 10** - below every arithmetic, relational, and equality operator,
and above only `?:`, assignment, and the comma. That is why

```
   grade >= 60 && attendance_pct >= 75
```

groups as `(grade >= 60) && (attendance_pct >= 75)` with no parentheses:
both `>=` (level 7) run first, then `&&` combines the two `bool`s.

`&&` also outranks `||`, so a mixed expression groups the `&&` parts
first, exactly like `*` before `+`:

```
   a || b && c        ─►   a || (b && c)
   passed a re-sit    OR   (passed the exam AND showed up)
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
std::string result{grade >= 60 ? "pass" : "fail"};
std::println("You {} the class.", grade >= 60 ? "passed" : "did not pass");
```

Same thing the long way:

```
   grade >= 60 ? "pass" : "fail"
   ─────────────────────────────
   is equivalent to

   if (grade >= 60)  result = "pass";
   else              result = "fail";
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

### Counter-controlled iteration - count known up front

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

Same job as a counter-controlled `while`, with all three parts in one
header:

```
   for ( init ; condition ; update )
         │        │           │
         │        │           └─ runs AFTER every pass
         │        └───────────── checked BEFORE every pass
         └────────────────────── runs ONCE, first

   for (int i{1}; i <= 10; ++i) { body }
```

Order of execution:

```
   init ──► condition ──true──► body ──► update ──┐
              ▲                                    │
              └────────────────────────────────────┘
              │
             false ──► exit
```

```
   i:      1   2   3   4   5   6   7   8   9   10   11
   test:   T   T   T   T   T   T   T   T   T   T    F ─► exit
```

Three variants to show:

```cpp
for (int i{1}; i <= 10; ++i)          { std::print("{} ", i); }   // count up
for (int n{2}; n <= 20; n += 2)       { total += n; }             // sum evens
for (int c{5}; c >= 1; --c)           { std::print("{} ", c); }   // count down
```

### Nested `for` - a table

```
   outer year = 1 ─► inner runs 1x
   outer year = 2 ─► inner runs 2x
   outer year = 3 ─► inner runs 3x
   ...
```

```cpp
for (int year{1}; year <= 5; ++year) {
    double amount{principal};
    for (int k{0}; k < year; ++k) {
        amount *= 1.0 + rate;        // apply interest `year` times
    }
    std::println("Year {}: {:.2f}", year, amount);
}
```

The loop variable's scope is the loop body - `i`, `n`, `c`, `year`, `k`
are each gone once their loop ends.

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
int grade{};
do {
    std::print("Enter a grade in the range 0-100: ");
    std::cin >> grade;
} while (grade < 0 || grade > 100);   // ◄── note the trailing ;
```

The semicolon after `while (...)` is easy to forget.

---

## 5.11 The `switch` statement

Compare **one integer expression** against a list of constant `case`
labels and jump to the match. Cleaner than a long `else if` chain of
equality tests.

```
   switch (grade / 10)         grade   grade/10   lands on
   ┌────────────────┐          ────────────────────────────
   │ case 10: ──┐   │           100       10       case 10
   │ case  9: ──┴─► A│           95        9       case 9
   │ case  8: ────► B│           83        8       case 8
   │ case  7: ────► C│           71        7       case 7
   │ case  6: ────► D│           64        6       case 6
   │ default: ────► F│           42        4       default
   └────────────────┘
```

```cpp
switch (grade / 10) {
    case 9:
    case 10:               // 9 falls through into 10 - both mean A
        ++aCount;
        break;
    case 8:
        ++bCount;
        break;
    case 7:
        ++cCount;
        break;
    case 6:
        ++dCount;
        break;
    default:
        ++fCount;
        break;
}
```

### Fall-through

```
   case 8:
       ++bCount;
       break;   ◄── STOP here, jump past the whole switch

   case 8:
       ++bCount;
       ▼         ◄── NO break: execution falls straight into
   case 7:           case 7's body and keeps going
       ++cCount;
```

`break` ends a `case`. Leaving it out is **deliberate** for `case 9` into
`case 10` above; nearly everywhere else it is a bug.

### Rules

- `case` labels must be **compile-time constants**, not variables.
- The controlling expression must be an integer type (or `char`, or an
  `enum`).

The example reads grades until end-of-file:

```
   while (std::cin >> grade)   ── true while a number was read
                              ── false at end-of-file:
                                    Windows      : Ctrl+Z then Enter
                                    macOS / Linux: Ctrl+D
```

---

## 5.12 `break` and `continue`

```
   break                          continue
   ─────                          ────────
   for (...) {                    for (...) {
       if (x) break;  ──┐             if (x) continue; ──┐
       stmtA;           │             stmtA;             │
       stmtB;           │             stmtB;             │
   }                    │         }   ▲                  │
   nextThing;  ◄────────┘             └──────────────────┘
   (leave the loop entirely)     (skip to the next iteration)
```

```cpp
for (count = 1; count <= 10; ++count) {
    if (count == 5) { break; }       // stop the whole loop at 5
    std::print("{} ", count);        // prints 1 2 3 4
}

for (int i{1}; i <= 10; ++i) {
    if (i == 5) { continue; }        // skip just this pass
    std::print("{} ", i);            // prints 1 2 3 4 6 7 8 9 10
}
```

### The `continue` gotcha

```
   for loop   : continue ──► still runs the update (++i) ──► re-test
   while loop : continue ──► jumps STRAIGHT to the re-test
```

```cpp
int i{0};
while (i < 10) {
    if (i == 5) { continue; }   // ◄── BUG: ++i below is skipped forever
    ++i;
}
```

Both `break` and `continue` act only on the **innermost** loop that
contains them.

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
