# Chapter 28: Algorithms, Ranges & Views

## From classic algorithms to ranges and views

The Standard Library's classic algorithms (`std::sort`, `std::find_if`,
`std::copy`...) all operate on a pair of iterators - a beginning and an end.
C++20's ranges library rebuilds the same algorithms as `std::ranges::`
versions that take a whole range directly, adds *projections* (comparing or
transforming elements through a member or a lambda before the algorithm
ever sees them), and introduces *views* - lazy, composable transformations
of a range (`filter`, `transform`, `take`, `drop`...) that don't copy or
compute anything until you actually iterate. This chapter teaches the
classic algorithms first, then walks through the same ideas again as
ranges/views - deliberately, since seeing `std::ranges::sort` right after
`std::sort` (and even the *exact same demo re-run* with the ranges version)
is what makes clear what ranges actually add.

## Lecture by lecture

- **31.2 All Of** - `std::all_of`/`std::any_of`/`std::none_of`, with a
  lambda, a function object, and a function pointer as the three ways to
  write a predicate.
- **31.3 For Each** - `std::for_each`, including that it returns the functor
  it was given (handy for a stateful functor whose accumulated result you
  want back).
- **31.4 Max Elt Min Elt** - `std::max_element`/`std::min_element`/
  `std::minmax_element`, including a custom comparator (closest/furthest
  from a target value).
- **31.5 Find And Find If** - `std::find` vs. `std::find_if`.
- **31.6 Copy** - `std::copy` and `std::copy_if`, and the caller's
  responsibility to make sure the destination range is large enough.
- **31.7 Sort** - `std::sort` with a type's own `operator<`, an explicit
  comparator, and sorting a vector of custom objects.
- **31.8 Transform** - `std::transform`, and why `std::back_inserter` is
  usually what you want over writing into a fixed-size destination.
- **31.9 Range Algorithms** - the exact same algorithms from 31.2-31.6, now
  as `std::ranges::` versions that take a whole range instead of an
  iterator pair.
- **31.10 Range Library Iterator Pair Algorithms** - `std::ranges::`
  algorithms also accept an iterator pair when you only have (or only want)
  a subrange - not just a whole range.
- **31.11 Projections** - sorting (and `for_each`-ing) by a projection: a
  member, a pointer-to-member, or a lambda applied to each element before
  the comparator or function ever sees it.
- **31.12 Views And Range Adaptors** - `filter_view`, `transform_view`,
  `take_view`, `take_while_view`, `drop_view`, `drop_while_view`, and
  `keys_view`/`values_view` - including *why* constructing `keys_view`/
  `values_view` directly on a container fails to compile, and why
  `std::views::keys`/`std::views::values` are the idiomatic way to get the
  same result.
- **31.13 View Composition And Pipe Operator** - composing several views
  together, first as nested calls, then with the `|` pipe operator that
  reads left to right in application order.
- **31.14 Range Factories** - `std::views::iota`, a range factory that
  generates values lazily rather than storing them.
- **31.15 Parallel Algorithms** - the execution-policy overloads
  (`std::execution::par`, `std::execution::par_unseq`) that let the standard
  library run a classic algorithm across multiple threads (or vectorize it)
  instead of running it on one thread - a permission the implementation can
  act on, not a guarantee it will.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
