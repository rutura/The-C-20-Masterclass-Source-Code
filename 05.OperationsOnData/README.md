# Chapter 5: Operations on Data

## The running example: the expense tracker, now doing math

Chapter 4 was about picking the right type to hold a piece of data. Chapter 5
picks up the same expense-tracker idea and asks the next question: now that
we can store an amount, a category, a receipt flag - what do we actually
*do* with them? This chapter is about the operators C++ gives you to compute
totals, compare values, and make decisions from data, plus the tools to
print the results clearly.

## What does a program like this need to compute?

| Need | Example | C++ tool |
|---|---|---|
| Combine costs into a total | lunch + coffee | Arithmetic operators (`+ - * /`) |
| Control which part of a calculation happens first | tax added before or after a discount? | Operator precedence, parentheses |
| Bump a counter or a total up/down | one more expense logged | Increment/decrement, compound assignment |
| Check spending against a limit | did today's spend cross the budget? | Relational operators (`< <= > >= == !=`) |
| Combine several yes/no checks into one decision | over budget AND no receipt -> flag it | Logical operators (`&& \|\| !`) |
| Print a lined-up, readable table of expenses | a receipt-style printout | `std::format`/`std::println` format specs |
| Know exactly how far a type can stretch | will this total overflow an `int`? | `std::numeric_limits` |
| Understand what type an expression's result actually is | adding two `short`s - still a `short`? | Integer promotion |
| Round, take an absolute value, or work with exponents | rounding a price, compound interest | `<cmath>` |

## Lecture by lecture

- **5.2 Basic Operations** - `+ - * / %` on expense amounts: combining
  costs, applying discounts, splitting a bill, and the leftover-cents
  remainder from a division that doesn't come out even.
- **5.3 Precedence and Associativity** - why `lunch + coffee * snack` isn't
  computed left to right, and how parentheses force a different order when
  that's what you actually mean.
- **5.4 Increment and Compound Assignment** - the `++`/`--` shorthand for
  "add or subtract one", and the `+= -= *= /= %=` shorthand for "apply an
  operation to this variable and store the result back into itself" -
  adjusting an expense count and a monthly budget without repeating the
  variable's name twice.
- **5.5 Relational Operators** - comparing today's spend against a budget
  with `< <= > >= == !=`, and storing the true/false result in a `bool` for
  later.
- **5.6 Logical Operators** - combining multiple yes/no checks with
  `&& || !` to decide whether an expense should be flagged for review.
- **5.7 Output Formatting** - lining up a table of expenses, picking a
  number base, and controlling decimal precision, all through `std::format`'s
  `{}` spec mini-language.
- **5.8 Numeric Limits and Integer Promotion** - asking the compiler exactly
  how far a type can stretch with `std::numeric_limits`, and what type an
  expression actually produces once small integer types get promoted during
  arithmetic.
- **5.9 Math Functions** - `<cmath>` facilities like `floor`/`ceil`/`round`
  for rounding a price, `abs` for a balance's distance from zero, and
  `pow`/`exp`/`log` for compound-interest-style calculations.

## How C++'s latest features help

- **`std::format`/`std::println`'s spec mini-language** (C++20/23) replaces
  the `<iomanip>` manipulator style (`std::setw`, `std::fixed`,
  `std::hex`, `std::boolalpha`, ...) almost entirely. The old manipulators
  mutate hidden, persistent state on the stream - set `std::hex` once, and
  every subsequent `<<` stays in hex until something turns it off again.
  A format spec like `{:>10.2f}` is attached to one value and one value
  only, with no state to remember to reset. Chapter 5.7 rewrites the classic
  formatted-table lecture around this.
- **Uniform `{}` formatting** means the same `std::println` call handles
  width, fill, justification, base, precision, and sign - one small
  mini-language instead of memorizing a dozen separate manipulator names.

## Capstone project: 5.10 Bill Splitter

Once you've been through 5.2-5.9, `5.10.BillSplitterProject` puts every
operator in this chapter to work on something genuinely useful: splitting a
restaurant bill. You log each item's price, then the program works out tip
and tax (percentage math, with parentheses making the order of operations
explicit), splits the grand total evenly among the group, rounds the result
to a sensible cash amount, and flags anyone whose share blows past what they
budgeted for the meal.

Every lecture shows up for a reason: `+=`/`++` accumulate the running
subtotal and item count as you go (5.4), `std::round`/`std::ceil` turn an
exact-but-awkward share into something you'd actually hand over in cash
(5.9), relational and logical operators combine into an "over budget" and a
separate "cutting it close" check (5.5, 5.6), and the whole thing prints as
a lined-up receipt using `std::format`'s spec mini-language (5.7) - then
saves that receipt to a file, the same file-persistence idea chapter 3
ended on.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
