# Control Flow

Chapter 4 gave us variables and datatypes. Every program so far has run
straight down: statement, statement, statement, done. This chapter is
where programs start making decisions and repeating work.

The running example throughout is a **class results analyzer**: we read
test scores, decide pass/fail and letter grades, and total things up. It
starts as a two-line calculation in 5.2 and by the assignment it reads
an arbitrary stream of grades and prints a histogram.

---

## 5.2 Arithmetic operators and input

Two new things at once: reading from the keyboard, and doing arithmetic
on what we read.

### Input with `std::cin`

```cpp
std::print("Enter two test scores (0-100), separated by a space: ");
int score1{};
int score2{};
std::cin >> score1 >> score2;
```

`std::cin >>` is the input counterpart to `std::cout <<`. It reads
whitespace-separated tokens: one `>>` per value, or chain them as above.
`std::cin` lives in `<iostream>`, so that header comes back for any
lecture that takes input. The variables are brace-initialized to `0`
first (`int score1{};`) so they hold a defined value even if the read
fails.

### The operators

`+ - * /` do what you expect. Two things to call out on camera:

- **Integer division truncates.** `(74 + 75) / 2` is `74`, not `74.5` -
  the fractional part is discarded, not rounded. Make one operand a
  `double` (`/ 2.0`) and you get `74.5` back. This trips up every
  beginner writing an average.
- **`%` is the remainder operator**, integers only. `score1 % 2 == 0`
  tests "is this even?" - we'll use exactly that pattern to do something
  "every other iteration" later in the chapter.

### Precedence and associativity

`*` and `/` bind tighter than `+` and `-`, so `score1 + score2 * 2` is
`score1 + (score2 * 2)`. When operators tie (like `a - b + c`),
associativity decides - left to right for arithmetic. When in doubt,
parenthesize; it costs nothing and the intent is unambiguous.

### Compound assignment

`total += score2` is shorthand for `total = total + score2`. The same
form exists for `-= *= /= %=`. We lean on `+=` constantly once loops
arrive (accumulating a running total), so introduce it here where it's
just a typing shortcut.

---

## 5.3 Increment and decrement

`++` adds 1, `--` subtracts 1. The subtlety is **prefix vs postfix** when
the operator appears inside a bigger expression:

| Form | Meaning | `x` starts at 5; value of the expression | `x` afterward |
|------|---------|------------------------------------------|---------------|
| `x++` | use old value, then add | `5` | `6` |
| `++x` | add first, then use | `6` | `6` |

As a **standalone statement** - `++counter;` on its own line - the two
are interchangeable, and that's how you'll write them 95% of the time
(stepping a loop counter). The prefix/postfix distinction only matters
when you *use the result* in the same expression, which is worth showing
once and then generally avoiding for readability.

---

## 5.4 Relational and equality operators

`== != < > <= >=`. Each one produces a **`bool`** - `true` or `false` -
which `std::println("{}", ...)` prints as the words `true` / `false`.

The result is an ordinary value you can name:

```cpp
bool first_is_better{score1 > score2};
```

The one thing to hammer: **`=` assigns, `==` compares.** `if (x = 5)`
compiles, assigns `5` to `x`, and is always "true". `if (x == 5)` is the
comparison. Modern compilers warn about the former; still worth the
callout.

---

## 5.5 `if` statements

Four shapes, building up:

1. **Plain `if`** - run a block only when the condition holds.
2. **`if` / `else`** - one branch or the other, never both.
3. **`else if` ladder** - the first true branch wins and the rest are
   skipped. **Order matters:** check `>= 90` before `>= 60`, or every
   passing grade prints "D". Walk through why on camera.
4. **Nested `if`** - a decision inside a branch (passed *and* honor
   roll).

Also introduce **block scope** here: a variable declared inside `{ }`
exists only inside those braces.

```cpp
if (grade >= 60) {
    int margin{grade - 60};
    std::println("cleared by {} points", margin);
}
// margin does not exist here
```

That fact is what makes the initializer form in 5.13 useful, so plant it
now.

---

## 5.6 Logical operators

`&&` (and), `||` (or), `!` (not). Build the three truth tables on screen
by printing each combination - it's the clearest way to show them:

- `&&` is `true` only when **both** sides are.
- `||` is `true` when **either** side is.
- `!` flips it.

Then combine them in a real check:

```cpp
bool passes{grade >= 60 && attendance_pct >= 75};
```

### Short-circuit evaluation

This is the part that matters beyond the truth tables. `&&` stops the
moment it sees a `false` - the right operand is **never evaluated**.
`||` stops on the first `true`. So you can guard a risky test with a
cheap one on its left:

```cpp
bool safe{count != 0 && 100 / count > 10};   // no divide-by-zero when count == 0
```

If `count` is `0`, the division never runs. Reorder those and the
program crashes. This is a real idiom students will use.

---

## 5.7 The ternary (conditional) operator

```cpp
condition ? value_if_true : value_if_false
```

Unlike `if`, the whole thing **is a value**, so it drops straight into
an initializer or a print:

```cpp
std::string result{grade >= 60 ? "pass" : "fail"};
std::println("You {} the class.", grade >= 60 ? "passed" : "did not pass");
```

Show the `if`/`else` equivalent side by side so it's clearly just a
compact form. Guidance: use it for **simple either/or value choices**.
Both branches must yield the same type. Nesting `?:` inside `?:` gets
unreadable fast - an `else if` ladder is clearer there.

---

## 5.8 The `while` loop

`while (condition) { body }` - test first, then maybe run the body, and
repeat. Two named patterns from the reference:

### Counter-controlled iteration

You know the repeat count up front. Keep a counter, test it, and
**advance it inside the loop** or it never ends:

```cpp
int entered{0};
while (entered < 5) {
    // read a score, add to total
    ++entered;
}
```

### Sentinel-controlled iteration

You *don't* know the count - the user signals the end with a marker
value (a "sentinel"), here `-1`. The shape needs a **priming read**
before the loop and another read at the **bottom** of the body:

```cpp
std::cin >> score;              // prime
while (score != -1) {
    // process score
    std::cin >> score;          // read the next before re-testing
}
```

Then guard the division: if no real scores were entered, `count` is `0`
and `total / count` is undefined. `if (count != 0) { ... } else { ... }`.

---

## 5.9 The `for` loop

Same job as a counter-controlled `while`, with all three pieces in one
header:

```cpp
for (int i{1}; i <= 10; ++i) { ... }
//   \_______/  \______/   \_/
//    once      before      after
//              each pass   each pass
```

- Init runs **once**.
- Condition is checked **before every** iteration.
- Update runs **after every** iteration.

Show three variants: counting up, summing evens with `number += 2` as the
update, counting down with `--`. Then a nested `for` for a
compound-interest-style table - one row per year, an inner loop applying
`* (1 + rate)` repeatedly - which also demos loop nesting.

The loop variable's scope is the loop; `i` is gone afterward.

---

## 5.10 The `do...while` loop

Body **first**, condition **after**. So the body always runs **at least
once**, even if the condition is false from the start. Pick it when "do
it, then decide whether to repeat" fits better than "check, then maybe
do it" - the classic case being an input prompt you must show once:

```cpp
do {
    std::print("Enter a grade in the range 0-100: ");
    std::cin >> grade;
} while (grade < 0 || grade > 100);
```

Note the trailing semicolon after `while (...)` - easy to forget.

---

## 5.11 The `switch` statement

Branch on **many discrete values of one integer expression**. Clearer
than a long `else if` chain doing equality checks.

```cpp
switch (grade / 10) {       // 95 -> 9, 100 -> 10
    case 9:
    case 10:                // 9 falls through into 10 - both are an A
        ++aCount;
        break;
    case 8:
        ++bCount;
        break;
    // ...
    default:
        ++fCount;
        break;
}
```

Two things to stress:

- **`break` ends the switch.** Leave it out and execution *falls
  through* into the next `case`'s body. That's deliberate for `9 -> 10`
  above; everywhere else it's usually a bug.
- **`case` labels must be compile-time constants**, not variables.

The example reads grades until end-of-file (`while (std::cin >> grade)` -
Ctrl+Z Enter on Windows, Ctrl+D on macOS/Linux) and tallies letter
grades, then prints the counts. This is the reference's grade-report
example.

---

## 5.12 `break` and `continue`

- **`break`** leaves the enclosing loop immediately - no more
  iterations. Here: stop counting at `count == 5`.
- **`continue`** skips the rest of the current iteration and moves to the
  next one. Here: skip printing `5` but keep going.

The gotcha to say out loud: in a `for` loop, `continue` still runs the
**update step** (`++i`) before re-testing. In a `while` loop it does
**not** - a `continue` that jumps over your `++counter` gives an
infinite loop.

Both only affect the **innermost** loop they sit in.

---

## 5.13 `if` and `switch` with an initializer

C++17 lets you declare a variable in the header, before the condition:

```cpp
if (int grade{87}; grade >= 60) {
    std::println("grade {} is a pass", grade);
}
// grade does not exist here
```

The variable is in scope for the **whole** `if`/`else` (or the whole
`switch`), and nowhere after. Use it whenever a value exists only to
drive one decision - it keeps that value's lifetime as short as the
decision. Ties back to the block-scope point from 5.5.

`switch` takes the same form: `switch (int score{73}; score / 10) { ... }`.

---

## 5.14 Floating-point pitfalls

Floating-point types store values in **binary**, and most decimal
fractions have no exact binary representation - the same way `1/3` has no
exact decimal form. So tiny representational errors accumulate.

```cpp
double sum{0.1 + 0.2};
std::println("{:.17f}", sum);   // 0.30000000000000004
std::println("{}", sum == 0.3); // false
```

**Never compare floating-point values with `==`.** Check that they're
*close enough* - within a small tolerance:

```cpp
bool close_enough{std::fabs(sum - 0.3) < 1e-9};
```

Then the money angle: a compound-interest table. Format to exactly two
decimals with the `{:.2f}` spec. Contrast with the classic
`std::cout << std::fixed << std::setprecision(2)` approach (from
`<iomanip>`): those manipulators set *stream state* that stays in effect
until changed, whereas `{:.2f}` applies to just that one value. This is
the one lecture in the chapter where showing both styles side by side
earns its place.

---

## 5.15 First look at `std::string`

We used `std::string` in passing in chapter 4; here's its own moment
before the chapter closes.

```cpp
std::string first{"happy"};
std::string second{" birthday"};
std::string empty_one{};
```

- **`length()` / `size()`** - same thing, character count.
- **`empty()`** - `true` when there are no characters.
- **`==` / `!=`** - compare contents, just like numbers.
- **`+`** - concatenation, produces a new string.
- **`starts_with` / `ends_with`** - C++20, quick prefix/suffix checks.

Needs `<string>`. This is the fig02_06 material from the reference, kept
to just these members - the deeper string API is a later chapter.

---

## 5.16 Assignment

`main.cpp` has six stubbed exercises; `main_solution.cpp` solves all six
using only this chapter's tools. Built as two executables (`rooster`,
`rooster_solution`) by the same `CMakeLists.txt` pattern as chapter 4's
assignment.

1. Letter grade classifier - `else if` ladder + ternary for pass/fail.
2. Average of `n` scores - counter-controlled `for`, real division,
   zero-guard.
3. Sentinel-controlled tally - primed `while`, `continue` to reject
   out-of-range input.
4. Grade histogram - `while (cin >> grade)` + `switch` + inner loop to
   draw bars of `*`.
5. Retry prompt - `do...while` that always prompts once.
6. String report line - concatenation, `length`, `starts_with` /
   `ends_with`.

After this chapter the student has decisions and repetition, and is
ready for functions.
