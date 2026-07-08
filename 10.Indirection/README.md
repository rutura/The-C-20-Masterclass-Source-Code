# Chapter 10: Indirection - Arrays, Pointers, References & span

## Why these three used to be three chapters, and aren't anymore

Arrays, pointers, and references are all, at bottom, ways of indirectly
getting at data - an array names a block of contiguous storage, a pointer
holds an address that can point anywhere (including into an array), and a
reference is a permanent alias for one specific variable. Splitting them
into three separate chapters made pointers - by far the most error-prone of
the three - occupy just as much space as the other two put together. This
chapter deliberately **downplays pointers**: the array and reference
sections stay close to full strength, but the pointer section is thinned
down to the handful of ideas that actually earn their keep in modern C++
(pointer/array duality, dynamic memory, passing by pointer, and enough
pointer arithmetic to recognize it when you see it) - the reference section
right after it is there to show the safer alternative you should reach for
in new code.

## Lecture by lecture

**Arrays**
- **10.2 Declaring and Using Arrays** - declaring, initializing, and
  looping over a `int[]`.
- **10.3 Size of an Array** - `std::size()` as the safe, generic
  replacement for manual `sizeof(arr)/sizeof(arr[0])` arithmetic.
- **10.4 Arrays of Characters** - `char` arrays, C-strings, and why a
  string literal needs room for the null terminator it adds.
- **10.5 Array Bounds** - why reading or writing past an array's bounds is
  undefined behavior, not a checked error.
- **10.7 Practice: Fortune Teller V1** - a first pass at a small
  interactive project, predictions stored as separate named variables.
- **10.8 Multi-Dimensional Arrays** - 2D and 3D arrays, and the rule that
  only the leftmost dimension can be omitted from a declaration.
- **10.9 Multi-Dimensional Arrays of Characters** - arrays of C-strings,
  and why printing one safely needs either a null terminator or manual
  bounds.
- **10.10 Practice: Fortune Teller V2** - the same project, now storing
  predictions in one array of C-strings instead of ten separate variables.
- **10.11 Array Function Parameters** - array parameters decay to a
  pointer, so the function also needs a separate count.
- **10.12 Sized Array Function Parameters** - the same idea with
  `type name[]` syntax instead of a raw pointer parameter.
- **10.13 Span and to_array** - `std::span`, a lightweight non-owning view
  that lets one function accept a raw array, `std::vector`, or
  `std::array` without an overload for each - the modern alternative to the
  two lectures just before it; `std::to_array` as the modern, standard
  alternative to declaring a raw array and tracking its size by hand.
- **10.14 Sized Arrays by Reference** - a reference-to-array parameter,
  which (unlike a plain array parameter) doesn't decay, so the compiler
  enforces the exact size at the call site.
- **10.15 Multi-Dimensional Array Function Parameters** - the same
  decay/parameter rules extended to 2D and 3D arrays.
- **10.16 Returning Array Element Index by Pointer** - returning a pointer
  to a specific element instead of just its value, so the caller can see
  (or modify) it in place.

**Pointers (downplayed - the essentials only)**
- **10.17 Declaring and Using Pointers** - declaring, assigning, and
  dereferencing a pointer.
- **10.18 Pointers and Arrays** - an array decays to a pointer to its
  first element, and why the array name itself still isn't a reassignable
  pointer variable.
- **10.19 Pointer-Based C-Strings, Briefly** - what string-handling looked
  like before `std::string`/`std::string_view` existed, kept brief and
  explicitly retrospective - the Strings chapter already covers the modern
  way.
- **10.20 Swapping Array Data** - swapping what two pointers point to
  (three assignments) instead of copying every element through a
  temporary array.
- **10.21 Pointer Arithmetic** - incrementing, adding to, subtracting, and
  comparing pointers.
- **10.22 Const Pointer and Pointer to Const** - the four combinations of
  const applied to a pointer and to what it points to.
- **10.23 Dynamic Memory Allocation** - `new`/`delete`, initializing a
  pointer with a fresh allocation, why every `new` needs exactly one
  matching `delete`, and what `new(std::nothrow)` does when an allocation
  can't be satisfied.
- **10.24 Dangling Pointers** - the ways a pointer can end up pointing at
  invalid memory, and three practical ways to avoid it.
- **10.25 Null Pointer Safety** - checking a pointer before using it, and
  why deleting a `nullptr` is always safe.
- **10.26 Memory Leaks** - how memory gets orphaned when the only pointer
  to it is overwritten, reassigned, or goes out of scope before `delete`.
- **10.27 Dynamically Allocated Arrays** - `new[]`/`delete[]`, and why
  `std::size()` only works on a real array, not a decayed pointer.
- **10.28 Pass by Pointer** - passing a pointer, a pointer-to-const, and a
  const-pointer-to-const as function parameters.

**References (kept at full strength - the safer alternative)**
- **10.29 Declaring and Using References** - a reference as a permanent
  alias for one variable, not a separate object.
- **10.30 Comparing Pointers and References** - reading and writing
  through both, and the common misconception that assigning through a
  reference "rebinds" it (it doesn't - references bind for life; the
  assignment just writes a value through the existing binding).
- **10.31 References and Const** - a `const` reference can read but not
  modify what it's bound to.
- **10.32 References with Range-Based for Loops** - `for (auto& x : ...)`
  to modify a container in place, vs. `for (auto x : ...)`'s copies.
- **10.33 Pass by Reference** - avoiding a copy while still allowing the
  callee to modify the caller's variable.
- **10.34 Pass by Const Reference** - avoiding a copy without allowing
  modification.
- **10.35 Bare Auto Type Deduction** - why plain `auto` never deduces a
  reference (even when initialized from one), and why `auto&` does.
- **10.36 Implicit Conversions with References** - why a reference
  parameter can't bind directly to a value of a different type the way a
  pass-by-value parameter can.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
