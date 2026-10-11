# Chapter 14 Quiz - Containers and Iterators

20 multiple-choice questions covering **Chapter 14 (Containers and Iterators)**: iterators and
their categories, the inside of a `std::vector`, iterator invalidation, `deque`, `list` and
`forward_list`, `set` and `map`, the unordered containers and hashing, the container
adaptors, `flat_map` and `mdspan`, writing an iterator, choosing a container, and the log
analyzer project. Each question is followed immediately by its correct answer and a short
explanation.

---

### 1. What does `v.end()` return for a `std::vector`?

A. An iterator to the last element
B. A null pointer
C. An iterator one position past the last element, which is compared against but never dereferenced
D. An iterator to a special element holding the value 0

**Answer: C** - a range is half open, `[begin, end)`. That is why an empty container has `begin() == end()`, and why the loop condition is `it != v.end()`. Dereferencing `end()` is undefined behaviour.

### 2. Which of these containers has iterators that can do `it + 3` directly?

A. `std::deque`
B. `std::list`
C. `std::forward_list`
D. `std::map`

**Answer: A** - only random access iterators (`std::vector`, `std::deque`, `std::array`) can jump. The iterators of `list` and `map` are bidirectional and `forward_list`'s is forward only; for those you use `std::next(it, 3)`, which walks step by step.

### 3. A `std::vector` has size 10 and capacity 16. What does `push_back` do for the 11th element?

A. Allocates a new block of 32 and copies everything
B. Allocates a new block and moves the 10 elements
C. Copies the vector into a temporary first
D. Constructs the element in the spare room, with no reallocation

**Answer: D** - a reallocation only happens when `size` would exceed `capacity`. Until then `push_back` is a cheap write at the end. This is why growth is "amortized constant": most calls are cheap, and the rare reallocation is paid for by many cheap ones.

### 4. What does `v.reserve(100)` do to an empty vector?

A. Sets the size to 100
B. Sets the capacity to at least 100 and leaves the size at 0
C. Sets both size and capacity to 100
D. Nothing, it is only a hint that the compiler may ignore

**Answer: B** - `reserve` allocates room up front so the following `push_back`s never reallocate. It never creates elements. (`shrink_to_fit` is the one that is only a request.)

### 5. What is the difference between `v.push_back(Counted{1})` and `v.emplace_back(1)`?

A. `emplace_back` is slower because it checks its arguments
B. `push_back` can only be used with built-in types
C. `emplace_back` builds the element in place from the constructor arguments, while `push_back` builds a temporary and moves it in
D. There is none, the compiler removes the difference

**Answer: C** - in 14.3 the counters showed 1 construction and 1 move for `push_back(Counted{1})`, and 1 construction and 0 moves for `emplace_back(1)`.

### 6. You keep an iterator `it` into a vector, then call `push_back` and the vector reallocates. What is true of `it`?

A. It is invalid, and using it is undefined behaviour
B. It still points to the same element, in the new block
C. It points to the same element, but now it is `const`
D. It becomes equal to `end()`

**Answer: A** - the elements were moved to a new block, and the old iterator, pointer and references point into freed memory. In 14.4 a plain build printed garbage, AddressSanitizer reported a heap-use-after-free, and MSVC's Debug build stopped with its debug dialog.

### 7. What is the correct way to erase elements that match a condition while looping over a vector with iterators?

A. Call `v.erase(it)` and then `++it` as usual
B. Assign `it = v.erase(it)` and advance only when nothing was erased
C. Collect the elements and erase them after the loop, in any order
D. Erasing during a loop is not allowed in C++

**Answer: B** - `erase` returns an iterator to the element after the erased one, and it invalidates the old iterator. Advancing after an erase would also skip an element (two negatives in a row would leave one behind).

### 8. When is `std::list` a better choice than `std::vector`?

A. Whenever you need fast lookup by index
B. Whenever you need to store many elements
C. Whenever the elements are small
D. When elements must keep their address and iterators while others are inserted or removed, or nodes must be moved between lists with `splice`

**Answer: D** - a list node never moves once created, and `splice` relinks nodes without copying. For ordinary sequences the vector is faster, because its elements sit next to each other in memory.

### 9. What can a `std::deque` do that a `std::vector` cannot?

A. Insert and remove at the front in constant time, and still offer random access
B. Store elements of different types
C. Keep its elements sorted
D. Guarantee that elements are contiguous in memory

**Answer: A** - a deque is a table of blocks, so both ends are cheap and indexing still works. The price is that its elements are not in one contiguous block (answer D describes the vector).

### 10. `std::map<std::string, int> m;` does not contain `"moon"`. What does `if (m["moon"] > 0)` do?

A. Throws `std::out_of_range`
B. Evaluates to `false` and leaves the map unchanged
C. Inserts `"moon"` with the value 0, then compares it with 0
D. Does not compile

**Answer: C** - `operator[]` creates the entry when the key is missing, even if you only meant to look. Use `find`, `contains` or `at` to ask without changing the map.

### 11. In which order does a loop over a `std::map` visit the elements?

A. The order in which they were inserted
B. In ascending order of the keys (by default), because the map is a balanced tree and lookup costs O(log n)
C. In descending order of the values
D. In an unspecified order

**Answer: B** - sorted by key is the defining property of `std::map` and `std::set`. Insertion order (A) is what a vector gives you; unspecified order (D) is the unordered containers.

### 12. How do you test whether a key is in a `std::map` without changing it?

A. `m[key] != 0`
B. `m.insert(key)`
C. `m.at(key)`, because it never throws
D. `m.contains(key)` (C++20), or `m.find(key) != m.end()`

**Answer: D** - both only look. `m[key]` inserts the key (question 10), `insert` changes the map, and `at` throws when the key is missing.

### 13. In which order does a loop over a `std::unordered_map` visit the elements?

A. Unspecified, and it can differ between compilers, library versions and even after inserting more elements
B. Sorted by key
C. In insertion order
D. Sorted by hash value

**Answer: A** - the order is that of the buckets of the hash table. Never write code that depends on it; if you need an order, use `std::map` or sort the result.

### 14. What do you need to provide to use your own struct as the key of an `std::unordered_set`?

A. A `<` operator
B. A `<=>` operator only
C. A hash (a `std::hash` specialization or a hash function object) and an `operator==`
D. A default constructor

**Answer: C** - the hash chooses the bucket, and `==` tells apart different keys that landed in the same bucket. An ordered `std::set` would instead need `<`.

### 15. What does `top()` of a default `std::priority_queue<int>` return?

A. The element pushed first
B. The largest element
C. The smallest element
D. The element pushed last

**Answer: B** - by default it is a max-heap (it uses `std::less`). Pass `std::greater<>` as the comparison to get the smallest first, as in 14.8.

### 16. Which statement about `std::stack` and `std::queue` is true?

A. They are faster than a `std::vector` for every operation
B. They keep their elements sorted
C. They are separate containers that cannot be built on a vector
D. They are adaptors without iterators: you can only reach the ends, and to see everything you take elements out

**Answer: D** - an adaptor offers a small interface on top of another container (a `deque` by default). That narrow interface is the point: a stack is last in, first out and nothing else.

### 17. What is `std::mdspan`?

A. A multi-dimensional container that owns and allocates its elements
B. A sorted table of keys and values
C. A non-owning view that gives multi-dimensional indexing, `grid[row, column]`, over contiguous data you already have
D. A smart pointer for 2D arrays

**Answer: C** - it is to a matrix what `std::span` is to an array. Writing through it changes the underlying vector, and the layout decides how `(row, column)` maps to a position.

### 18. You write your own forward iterator class. Which operations must it provide, besides the five type aliases?

A. `operator*`, prefix and postfix `operator++`, `operator==`, and a default constructor
B. Only `operator*` and `operator++`
C. `operator+`, `operator-` and `operator[]`
D. `begin()` and `end()`

**Answer: A** - those are the operations the forward iterator concept checks (14.10 used `static_assert(std::forward_iterator<...>)`). `begin()` and `end()` belong to the container, and `+`, `-` and `[]` are for random access iterators.

### 19. In the 14.11 measurement, which way of finding a key among 100,000 was by far the slowest?

A. `std::unordered_set`
B. Scanning an unsorted vector from the start with `std::find`
C. Binary search in a sorted vector
D. `std::map`

**Answer: B** - roughly 3,000 to 17,000 ns per lookup, depending on the compiler, against 10 to 160 ns for the others. That is O(n) against O(log n) and O(1), and the same shape as the Big O curves of 7.5.

### 20. In the log analyzer, the `LogEntry` fields are `std::string_view`s into one big string. What must stay true while the entries are used?

A. The log file must stay open
B. The string must be sorted
C. The entries must be stored in a `std::list`
D. The string that holds the text must stay alive and unchanged, otherwise the views dangle

**Answer: D** - a `string_view` does not own its characters (7.9). Parsing without copying a single field is what makes the analyzer fast, and the price is that `main` keeps the buffer alive for the whole run.
