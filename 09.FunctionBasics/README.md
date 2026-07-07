# Chapter 9: Function Basics

## Why functions come before Arrays

Arrays, pointers, and references are how C++ manages raw, low-level access
to data - genuinely useful, but not what a beginner needs before they can
write and organize real logic. Functions are the more fundamental idea: a
named, reusable, testable piece of behavior, and lectures 9.2-9.14 are taught
using only what earlier chapters already introduced (numbers, `bool`,
`std::string`) - no array, pointer, or reference syntax required. That's
deliberate: those lectures cover the roughly 20% of function knowledge that
does 80% of the everyday work.

The rest of this chapter (9.15 onward) is everything else about functions
that doesn't reduce to "a new Arrays/Pointers/References concept" - output
parameters, returning a reference/pointer and the dangling pitfalls that come
with it, overload resolution once pointers/references are in the mix,
`argc`/`argv`, and using a debugger - collected here once Arrays (chapter
10), Pointers (chapter 11), and References (chapter 12) exist to make those
examples make sense. The exception is lambda *captures*, which live in their
own chapter (14, right before Classes) since a capture is really a small
class in disguise and reads better once Classes exist to compare it to.

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
  captures yet (captures need references and a comparison to classes,
  covered later in chapter 14, Lambda Functions).
- **9.13 Static, Inline, and Recursion** - a local variable that remembers
  its value between calls, a hint to the compiler about inlining a call, and
  a function that solves a problem by calling a smaller version of itself.
- **9.14 constexpr and consteval Functions** - functions that can (or must)
  run at compile time instead of runtime.
- **9.15 Implicit Conversions From string_view to string** - why a
  `std::string_view` parameter won't implicitly convert to a
  `std::string`/`const std::string&` parameter at a second call site, and the
  explicit fix.
- **9.16 Input and Output Parameters** - using a reference or pointer
  parameter purely to hand a result back to the caller, instead of (or
  alongside) a return value.
- **9.17 Returning by Reference** - returning `T&` from a function, and the
  dangling reference that results from returning a reference to a local
  variable.
- **9.18 Returning by Pointer** - the same idea with pointers: valid when
  returning a pointer the caller already owns, dangling when returning the
  address of a local.
- **9.19 Return Type Deduction with References** - why `auto&` as a deduced
  return type doesn't reliably give you a reference back, even when every
  `return` statement inside looks like it should.
- **9.20 Optional Output from Functions** - signaling "no result" with a
  `bool&` success flag, contrasted with a sentinel value like `-1`.
- **9.21 Optional Output with std::optional** - the same problem solved by
  returning `std::optional<T>` instead of relying on an output parameter.
- **9.22 Overloading with Pointer Parameters** - how overload resolution
  picks between overloads that differ only in pointee type.
- **9.23 Overloading with Reference Parameters** - overload ambiguity and
  resolution rules once by-value and by-reference overloads coexist.
- **9.24 Overloading with Const Pointer and Pointer-to-Const Parameters** -
  which pointer/const combinations count as distinct overloads.
- **9.25 Overloading with Const References** - the same question for `T&`
  vs. `const T&` overloads.
- **9.26 Grab and Use the Arguments** - `int main(int argc, char* argv[])`,
  and looping over the command line arguments a program was launched with.
- **9.27 Calculator V1** - a first, hardcoded pass at an arithmetic dispatcher
  with `switch`, before wiring it up to real command-line input.
- **9.28 Calculator V2** - the same calculator, now driven entirely by
  `argc`/`argv` parsed from the command line.
- **9.29 Debugging in VS Code** - setting breakpoints and stepping through a
  call stack in the editor's debugger.
- **9.30 Debugging Arrays, Loops, and Pointers** - the same debugging
  technique applied to a loop summing an array through a pointer parameter.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
