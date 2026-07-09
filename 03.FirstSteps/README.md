# Chapter 3: First Steps

## The running example: a personal profile

Throughout this chapter we build up one small program: something that greets
you by name, asks a few questions about you, and - by the end of the chapter -
remembers your friends list between runs. Nothing fancy, but it's a natural
excuse to meet every foundational building block of a C++ program, one
lecture at a time, instead of learning them in isolation.

## What does a program like this actually need to do?

| Need | Example | C++ building block |
|---|---|---|
| Say something to the screen | `"Hello there!"` | Output |
| Do a named, reusable action | greet a person by name | A function |
| Ask the user something and read the answer | "What is your name?" | Input |
| Compute something new from what was typed | the year you'll turn 100 | Arithmetic on variables |
| Follow a different path depending on the answer | adult vs. minor, comparing two ages | A decision (`if`/`else`) |
| Repeat an action until told to stop | collecting friend names | A loop (`while`) |
| Hold a growing list of things | the friends you added | `std::vector` - a ready-made collection |
| Remember data between separate runs of the program | friends saved to disk | File I/O |

Every one of these is something almost any program needs to do, which is why
they come first - before we even talk about the different kinds of data a
variable can hold (that's chapter 4).

## Lecture by lecture

- **3.2 Your First Program** - printing text to the screen, and the
  difference between a one-line `//` comment and a `/* block */` comment.
- **3.3 Statements and Functions** - grouping repeatable behavior into a
  function (`greetPerson`), and the difference between a compile-time error
  (the program won't even build) and a runtime error (it builds, but breaks
  while running).
- **3.4 Talking to the User** - reading input with `std::cin`/`std::getline`
  and printing prompts without a trailing newline. The lecture doesn't stop
  at just echoing input back - it computes something new from it (the year
  you'll turn 100), because that's the moment a program starts being useful
  instead of just being a fancy printer.
- **3.5 Making Decisions** - branching program flow with `if`/`else`, first
  against a fixed value (adult vs. minor), then between two variables
  (comparing your age with a friend's) - the same comparison operators,
  applied where they're actually useful instead of listed in isolation.
- **3.6 Doing It Many Times** - looping with `while`, breaking out of a loop,
  and collecting values into a `std::vector`. You don't need to know how a
  `std::vector` works inside to use one - it's a ready-made, growable
  collection C++ gives you, the same way `std::string` is a ready-made
  collection of characters.
- **3.7 Remembering Things** - saving that vector to a file and loading it
  back with `<fstream>`, proving the data survives after the program ends -
  this lecture is the chapter's capstone, pulling together every idea before
  it into one program.

## How C++'s latest features help

- **`std::print` / `std::println`** (C++23) replace `std::cout <<` chains
  with a single, readable, `{}`-style format string from the very first
  lecture - no stream operators to explain before you can print anything.
  `std::cin`/`std::getline` are still used for input, since C++23 doesn't
  yet have a formatted-input equivalent.
- **Brace initialization (`{}`)**, e.g. `int age{}`, is used for every
  variable that needs a starting value - it's the same safe habit this
  course leans on again once chapter 4 explains *why* it matters
  (narrowing conversions).

## Building the code

Every lecture folder has its own `CMakeLists.txt`. If you don't have a C++23
compiler installed locally, use one of the ready-made Docker images in
[`../docker`](../docker) - see that folder's README for exact commands.
