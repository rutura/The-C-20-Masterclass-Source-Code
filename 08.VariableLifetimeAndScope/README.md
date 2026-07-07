# Chapter 8: Variable Lifetime and Scope

## Why this chapter comes right after Loops

Chapters 6 and 7 introduced `if`/`else`, `switch`, and every loop form - each
one opens its own block of code with its own `{ }`. That's exactly what makes
scope worth a real chapter now instead of earlier: a variable declared inside
an `if` or a loop body behaves differently from one declared in `main()`
directly, and until those blocks existed there wasn't much to show. This
chapter uses the expense-tracker examples from earlier chapters to make that
concrete before chapter 9 (Arrays) and chapter 10 (Pointers) start leaning on
the same idea implicitly.

## Lecture by lecture

- **8.2 Variable Scope** - global vs. local variables, and how `if` blocks and
  loop bodies each introduce their own scope: a variable declared inside one
  is created and destroyed with that block, and a loop-local variable gets a
  fresh copy on every iteration rather than carrying its value forward.
- **8.3 Shadowing** - what happens when an inner block declares a variable
  with the same name as an outer one, why it compiles without complaint, and
  why picking a different name is almost always the better call.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
