# Chapter 27: STL Containers & Iterators

## From "how do you walk a container" to "how do you build one"

This chapter starts with iterators as a concept - what they are, how they
compare, how to walk a subset of a container, reverse traversal, constant
iterators - before ever looking at a specific container's own deep dive.
That ordering matters: once you have iterator vocabulary, the per-container
lectures that follow (vector, array, deque, list, set, map, the container
adapters...) all read the same way, because they're all just "here's this
container's specific API, plus the iterators/algorithms you already know
how to use on it." The chapter closes with a from-scratch build of every
iterator category (input, output, forward, bidirectional, random access) on
a custom container, `BoxContainer` - the natural capstone, since it only
makes sense once you've *used* iterators on the standard containers for the
whole rest of the chapter.

## Lecture by lecture

**Iterators (concepts, container-agnostic)**
- **29.2 Iterators** - `std::vector<int>::iterator`, `begin()`/`end()`,
  comparing iterators, walking off the end.
- **29.3 Traversing Container Subsets With Iterators** - iterator
  arithmetic (`begin() + n`, `end() - n`) to print any slice of a
  container, not just the whole thing.
- **29.4 Reverse Iterators** - `rbegin()`/`rend()`, and why a
  `reverse_iterator` can't be compared against a regular `end()`.
- **29.5 Constant Iterators** - `cbegin()`/`cend()`/`crbegin()`/`crend()`,
  and why they can read but not write through the container.
- **29.6 Std Begin Std End** - `std::begin()`/`std::end()` as free
  functions that work uniformly across C-style arrays and containers with
  their own `begin()`/`end()` members.

**Sequence containers**
- **29.7 Vector** - construction styles, element access, iterators,
  capacity (`reserve`/`shrink_to_fit`), and the full set of modifiers
  (`insert`/`emplace`/`erase`/`resize`/`swap`).
- **29.8 Array** - `std::array`'s fixed-size construction styles including
  `std::to_array`, `fill()`, and why it has no `capacity()`.
- **29.9 Deque** - double-ended queue operations, including why `at()` is
  the safe alternative to `operator[]`'s lack of bounds checking.
- **29.10 Forward List** - singly-linked list operations
  (`insert_after`/`emplace_after`/`erase_after`), `merge`, `splice_after`.
- **29.11 List** - doubly-linked list operations (ordinary `insert`, not
  `insert_after`), `merge`, `splice`.

**Associative containers**
- **29.12 Pair** - `std::pair`, CTAD, structured bindings.
- **29.13 Set** - ordering via `operator<`, insert/emplace returning a
  `pair<iterator, bool>`, changing the comparator.
- **29.14 Map** - key-ordered storage, the three ways to traverse
  key/value pairs, `operator[]`'s default-construct-on-missing-key
  behavior.
- **29.15 Multiset Multimap** - the duplicate-key-allowing counterparts to
  set/map.
- **29.16 Unordered Set Unordered Map** - hash-table-backed containers that
  trade ordering for faster average-case lookup.

**Container adapters**
- **29.17 Stack** - LIFO via `push`/`top`/`pop`, and how the same
  `print_stack` works unchanged over a vector-, list-, or deque-backed
  stack.
- **29.18 Queue** - FIFO via `push`/`front`/`back`/`pop`.
- **29.19 Priority Queue** - heap-ordered access via `top`, why `top()`
  returns a const reference (modifying it in place could break the heap),
  changing the comparator.

**Building custom iterators (capstone)**
- **29.20 Iterator Powers** - a tour of what each of the five iterator
  categories actually requires, uncommented one block at a time.
- **29.21 Custom Input Iterator** - the minimum iterator: readable,
  incrementable, single-pass.
- **29.22 Custom Output Iterator** - the same iterator, now writable
  through, enough for `std::ranges::copy` to target it.
- **29.23 Custom Forward Iterator** - upgrading to multi-pass, enough for
  `std::ranges::replace`.
- **29.24 Custom Bidirectional Iterator** - adding `operator--`, enough for
  `std::ranges::reverse`.
- **29.25 Custom Random Access Iterator** - jumping to any position in
  constant time, enough for `std::ranges::sort`.
- **29.26 Custom Iterators With Views** - once a container's iterator is a
  real random-access iterator, the standard ranges views work on it
  directly, same as on `std::vector`.
- **29.27 Constant Iterators** - a `ConstIterator` so a `const
  BoxContainer` still has something to `begin()`/`end()` with.
- **29.28 Raw Pointers As Iterators** - the payoff: a raw `T*` already
  satisfies everything the hand-written `Iterator`/`ConstIterator` classes
  built up to, so `begin()`/`end()` can just return pointers directly.
- **29.29 Wrapping Iterators From Other Containers** - a container doesn't
  have to build its own iterator at all - it can just expose whatever
  `std::vector` (or another container) already gives it internally.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.
