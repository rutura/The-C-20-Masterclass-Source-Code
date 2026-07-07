# Chapter 4: Variables and Data Types

## The running example: an arcade high-score tracker

Throughout this chapter we build up one small, fictional program: something
like the machine standing in the corner of an old-school arcade, the one that
remembers your score, flashes "GAME OVER", and asks for your initials when
you've earned a spot on its leaderboard.

We're not writing the actual game (no graphics, no game loop) - just the
*data* a machine like that would need to keep track of while you play. That
turns out to be a perfect excuse to meet every basic data type C++ offers,
one lecture at a time, instead of learning them in the abstract.

## What does a machine like this actually need to remember?

| Need | Example | Kind of value |
|---|---|---|
| A big running score | `1,000,000` | A whole number that can get large |
| Which power-ups are active | shield on, extra life on, double points off | A handful of yes/no bits packed together |
| The current level | `7` | A small whole number |
| Total coins ever inserted | `9,000,000,000` over the machine's lifetime | A *very* large whole number |
| How accurate your last run was | `93.3333%` | A number with a fractional part |
| Whether the game is over | yes or no | A single true/false switch |
| Your 3-letter initials | `A`, `C`, `E` | Individual letters |

Every one of these is a "number" or "yes/no" or "letter" in the loosest
sense, but they don't all behave the same way, and they don't all need the
same amount of memory. Picking the right type for the job - not too small
(it overflows), not too imprecise (it drifts), not too wasteful (it burns
memory for no reason) - is exactly what this chapter teaches.

## Lecture by lecture

- **4.2 Number Systems** - the same power-up bits can be written in decimal,
  binary, octal, or hex. Same value, different spelling in the source code -
  useful once you start reading flags or memory dumps.
- **4.3 Integer Types** - `short`, `int`, `long long`, `unsigned`, and the
  modern `<cstdint>` fixed-width types (`std::int32_t` and friends), chosen
  by asking "how big can this stat realistically get?"
- **4.4 Fractional Numbers** - `float`, `double`, and `long double` for
  accuracy and timing stats, plus their precision limits, scientific
  notation, and the special `inf`/`NaN` values you get from dividing by zero.
- **4.5 Booleans** - the `isGameOver` / `isNewHighScore` on/off switches.
- **4.6 Characters and Text** - the 3-letter initials you type in when you
  make the leaderboard.
- **4.7 Auto and Assignment** - letting the compiler deduce types with
  `auto`, and the difference between *initializing* a variable and later
  *assigning* to it (including the narrowing pitfalls that come with each).

## How C++'s latest features help

A few of these lectures lean on things older C++ courses either skipped or
did the hard way:

- **`std::print` / `std::println`** (C++23) replace `std::cout <<` chains
  with a single, readable, `{}`-style format string - and can print numbers
  in a different base (`{:#x}`, `{:#b}`) without touching stream state like
  `std::hex`/`std::setprecision` used to require.
- **Digit separators** (`1'000'000`) make large literals readable at a
  glance - handy once a stat like lifetime coins inserted climbs into the
  billions.
- **`<cstdint>` fixed-width types** (`std::int32_t`, `std::uint16_t`, ...)
  give you an exact, portable bit width instead of relying on
  compiler/platform-dependent guesses about what `long` means.
- **Brace initialization (`{}`)** is used everywhere a variable is declared,
  because unlike `=`, it refuses to silently truncate a value you didn't
  mean to lose (a *narrowing conversion*) - the compiler catches it for you.

## Capstone project: 4.8 Expense Tracker

Once you've been through 4.2-4.7, `4.8ExpenseTrackerProject` puts it all to
work on something you might actually use: a small command-line expense
logger. You log expenses one at a time (category, amount, whether you have a
receipt), and it tracks a running total, a bitmask of which categories you
used, and a transaction id - then saves a ledger to disk so the next run
picks up where you left off, the same file-persistence idea chapter 3 ended
on.

It deliberately includes one bug on purpose: storing the running total in an
`int` instead of a `double`. Read the comment next to it once you spot the
missing cents in the output - it's the narrowing conversion from 4.7, shown
doing real damage instead of just being a warning in an isolated example.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
