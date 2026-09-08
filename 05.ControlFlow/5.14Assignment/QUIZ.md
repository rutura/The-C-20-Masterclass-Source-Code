# Chapter 5 Quiz — Control Flow

20 multiple-choice questions covering everything from **Chapter 5 (Control
Flow)**: arithmetic and comparison operators, `if` / `else if` / `switch`
/ ternary, `while` / `for` / `do...while`, `break` / `continue`, logical
operators, `std::string` basics, and the file-IO bonus. Each question is
followed immediately by its correct answer and a short explanation.

---

### 1. After `int total{7 + 3 * 2 - 4};`, what value does `total` hold?

A. 16
B. 9
C. 5
D. 12

**Answer: B** — `*` has higher precedence than `+` and `-`, so this is `7 + (3 * 2) - 4` = `7 + 6 - 4` = `9`. The `+` and `-` then apply left to right.

### 2. What does `std::println("{}", 7501 / 2);` print?

A. `3750.5`
B. `3751`
C. `3750`
D. `3750.500000`

**Answer: C** — both operands are `int`, so this is integer division: the fractional part is discarded (not rounded), giving `3750`. You would need `7501 / 2.0` to keep the `.5`.

### 3. What is the value of `17 % 5`?

A. `3`
B. `2`
C. `3.4`
D. `0`

**Answer: B** — `%` is the remainder operator: `17` is `3 * 5 + 2`, so the remainder is `2`. It only works on integer operands.

### 4. Given `int x{3};`, what does `x` hold after `x += 7; x *= 2;`?

A. `13`
B. `20`
C. `17`
D. `26`

**Answer: B** — `x += 7` makes `x` equal to `10` (`x = x + 7`), then `x *= 2` makes it `20` (`x = x * 2`).

### 5. `int cars_owned{5}; int handed_out{cars_owned++};` — what are the two values afterward?

A. `handed_out` is `6`, `cars_owned` is `6`
B. `handed_out` is `5`, `cars_owned` is `5`
C. `handed_out` is `5`, `cars_owned` is `6`
D. `handed_out` is `6`, `cars_owned` is `5`

**Answer: C** — postfix `cars_owned++` hands out the **current** value (`5`) and then increments `cars_owned` to `6`. Prefix `++cars_owned` would have given `6` for both.

### 6. When you write `++counter;` on its own line (not inside a larger expression), how does it differ from `counter++;`?

A. `++counter;` is faster at run time
B. There is no observable difference — both just add 1 to `counter`
C. `counter++;` does not compile as a standalone statement
D. `++counter;` adds 1, `counter++;` adds 2

**Answer: B** — the prefix/postfix distinction only matters when you *use the result* of the expression. As a standalone statement the two forms have identical effect.

### 7. Each of `< <= > >= == !=` produces what kind of value?

A. An `int` that is `0` or `1`
B. A `bool` — `true` or `false`
C. The larger of the two operands
D. A `std::string` such as `"true"`

**Answer: B** — every relational and equality operator yields a `bool`. `std::println` prints that as the words `true` / `false`.

### 8. Why is `if (age = 18)` almost always a bug?

A. `=` is not allowed inside an `if` condition
B. It compares `age` to `18` but ignores the result
C. It **assigns** `18` to `age` and then treats that assigned value as the condition (which is truthy), instead of comparing
D. It only works when `age` was declared `const`

**Answer: C** — `=` is assignment, `==` is comparison. `if (age = 18)` overwrites `age`, and since `18` is non-zero the branch always runs. You meant `if (age == 18)`.

### 9. In this ladder, what prints when `age` is `34`?

```cpp
if      (age >= 65) { std::println("senior"); }
else if (age >= 18) { std::println("adult"); }
else if (age >= 13) { std::println("teenager"); }
else                { std::println("child"); }
```

A. `senior`
B. `adult`
C. `teenager`
D. `adult` and `teenager` both print

**Answer: B** — an `else if` ladder stops at the **first** true branch. `age >= 65` is false, `age >= 18` is true, so `"adult"` prints and the remaining branches are skipped.

### 10. Why must an `else if` grade ladder test `>= 90` before `>= 60` rather than the other way around?

A. The compiler requires conditions in descending order
B. `>= 60` is slower to evaluate than `>= 90`
C. The first true branch wins, so a lower bound like `>= 60` would match a grade of `95` first and the `>= 90` branch would never be reached
D. It makes no difference; either order gives the same result

**Answer: C** — because only the first matching branch runs, the tests must go most-specific to least-specific (here, highest bound first). Otherwise a broad condition swallows values meant for a narrower one below it.

### 11. `bool safe{(count != 0) && ((100 / count) > 10)};` with `count` equal to `0` — what happens?

A. The program crashes with a divide-by-zero
B. `safe` becomes `true`
C. `safe` becomes `false`, and `100 / count` is never evaluated
D. It fails to compile because of the division

**Answer: C** — `&&` evaluates its left operand first. `count != 0` is `false`, which settles the whole `&&` as `false`, so the right operand (with `100 / count`) is short-circuited and never runs — no divide-by-zero.

### 12. `&&` sits at a higher precedence level than `||`. How does `a || b && c` group?

A. `(a || b) && c`
B. `a || (b && c)`
C. `((a || b) && c)` only if `a` is `false`
D. It is a syntax error without parentheses

**Answer: B** — `&&` binds tighter than `||` (the same way `*` binds tighter than `+`), so the `&&` part groups first: `a || (b && c)`. You must parenthesize to get `(a || b) && c`.

### 13. The conditional operator `age >= 18 ? "adult" : "child"` differs from an `if` statement how?

A. It can only be used with numeric conditions
B. The whole expression **is a value**, so it can go directly into an initializer or a function argument
C. It always runs both branches and keeps the last one
D. It requires `#include <ternary>`

**Answer: B** — `?:` produces a value, so `std::string category{age >= 18 ? "adult" : "child"};` works. An `if` statement does not produce a value and cannot be used that way. Both branches must be the same type.

### 14. A `while` loop checks its condition **before** running the body. What is the consequence for `while (loop_count < 5)` when `loop_count` starts at `5`?

A. The body runs exactly once, then the loop exits
B. The body never runs — the condition is false on the first check
C. The loop runs forever
D. It is a compile error

**Answer: B** — `while` tests first. `5 < 5` is `false`, so the body is skipped entirely and the loop runs zero times.

### 15. In sentinel-controlled iteration (loop until the user enters `-1`), why is there a "priming read" before the `while` and another read at the bottom of the body?

A. To make the loop run at least once
B. So the condition has a value to test on the very first check, and each later pass reads the next value before the condition is re-tested
C. Because `std::cin` can only be called from inside a loop
D. To skip the first value the user types

**Answer: B** — the condition tests `score`, so `score` must be read once *before* the loop (the priming read). The read at the end of the body supplies the next value for the following re-test.

### 16. Which statement about the `for` loop `for (int page{1}; page <= 10; ++page)` is correct?

A. `++page` runs before the body on every pass
B. `int page{1}` runs once; then the cycle is condition → body → update, repeating until the condition is false
C. The condition is checked only once, at the start
D. `page` is still readable after the loop ends

**Answer: B** — the init runs a single time, then the loop cycles condition, body, update. The condition is re-checked before every pass, and `page` (declared in the header) goes out of scope when the loop ends.

### 17. A `do...while` loop is the right choice when...

A. you know the exact number of iterations up front
B. the body must run **at least once** before the condition is checked — e.g. an input prompt that must appear before you can validate the answer
C. you need to loop over the characters of a `std::string`
D. the loop should never run if the condition is initially false

**Answer: B** — `do...while` runs the body first and tests afterward, so it always executes at least once. That fits "ask, then decide whether to ask again."

### 18. In this `switch`, what happens when `score / 20` is `4`?

```cpp
switch (score / 20) {
    case 3: ++fourStar; break;
    case 4:
    case 5: ++fiveStar; break;
    default: /* ... */ break;
}
```

A. Nothing — `case 4` has no body
B. `++fourStar` runs
C. `case 4` has an empty body, so execution falls through into `case 5` and `++fiveStar` runs
D. It is a compile error to stack two `case` labels

**Answer: C** — `case 4:` with no statements before `case 5:` deliberately falls through, so both `score/20 == 4` and `score/20 == 5` reach `++fiveStar`. This is intentional fall-through; a *missing* `break` mid-case would be the accidental-bug version.

### 19. Why does this `while` loop hang forever?

```cpp
int p{0};
while (p < 10) {
    if (p == 5) { continue; }
    ++p;
}
```

A. `p < 10` is never true
B. Once `p` reaches `5`, `continue` jumps back to the condition and skips `++p`, so `p` stays `5` and the condition stays true
C. `continue` is not allowed in a `while` loop
D. `++p` should be `p++`

**Answer: B** — in a `while` loop `continue` goes straight back to the condition; it does **not** run any update for you. When `p == 5`, the `++p` line is skipped every time, so `p` is stuck at `5` and `p < 10` is always true.

### 20. `std::string base{"report"}; std::string filename{base + ".pdf"};` — which is true?

A. `base` is now `"report.pdf"`, and `filename.starts_with("report")` is `true`
B. `base` is unchanged (`"report"`), `filename` is a new string `"report.pdf"`, and `filename.ends_with(".pdf")` is `true`
C. `filename` shares storage with `base`, so changing one changes the other
D. `base + ".pdf"` is a compile error because `".pdf"` is not a `std::string`

**Answer: B** — `+` produces a **new** string and leaves its operands untouched, so `base` stays `"report"`. You can concatenate a `std::string` with a string literal directly. `.ends_with(".pdf")` and `.starts_with("report")` are C++20 `bool` checks.
