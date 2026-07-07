# Chapter 9: Function Basics

## Why functions come before Arrays

Arrays, pointers, and references are how C++ manages raw, low-level access
to data - genuinely useful, but not what a beginner needs before they can
write and organize real logic. Functions are the more fundamental idea: a
named, reusable, testable piece of behavior, and everything in this chapter
can be taught using only what earlier chapters already introduced (numbers,
`bool`, `std::string`) - no array, pointer, or reference syntax required.
That's deliberate: this chapter covers the roughly 20% of function knowledge
that does 80% of the everyday work. Passing by pointer, passing by
reference, returning references/pointers, and array parameters all need
Arrays (chapter 10), Pointers (chapter 11), and References (chapter 12) as
prerequisites, so they're covered later, in their own dedicated chapters,
once those tools exist to explain them properly.

## Lecture by lecture

- **9.2 Your First Functions** - declaring, calling, parameters, return
  values, and functions that take or return nothing.
- **9.3 Declarations and Definitions** - separating a function's prototype
  from its body, and why that lets you call a function before its
  definition appears.
- **9.4 Functions Across Multiple Files** - splitting a declaration (header)
  from its definition (source file), and how the compiler and linker piece
  them back together.
- **9.5 Pass by Value** - every parameter is a local copy; changing it
  doesn't affect the caller's variable, and marking a parameter `const`
  documents (and enforces) that a function has no intention of changing it.
- **9.6 Default Parameters** - giving a parameter a fallback value so callers
  can omit it, and why every parameter after a defaulted one needs a default
  too.
- **9.7 String View Parameters** - `std::string_view` as a cheap, read-only
  way to accept text without copying it.
- **9.8 Implicit Conversions** - what happens when an argument's type doesn't
  match a parameter's exactly, including the narrowing this can cause.
- **9.9 Overloading Basics** - multiple functions sharing a name,
  distinguished by parameter types, resolved at compile time - and why a
  `const` by-value parameter alone doesn't create a valid overload.
- **9.10 Returning Values and Auto Deduction** - returning a value by value,
  and letting the compiler deduce a function's return type with `auto`.
- **9.11 std::optional** - representing "this function might not have an
  answer" without a sentinel value the caller has to remember to check for.
- **9.12 Lambda Basics** - small, unnamed functions written inline, with no
  captures yet (captures need references, covered later alongside chapter
  12's Lambda Functions chapter).
- **9.13 Static, Inline, and Recursion** - a local variable that remembers
  its value between calls, a hint to the compiler about inlining a call, and
  a function that solves a problem by calling a smaller version of itself.
- **9.14 constexpr and consteval Functions** - functions that can (or must)
  run at compile time instead of runtime.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
