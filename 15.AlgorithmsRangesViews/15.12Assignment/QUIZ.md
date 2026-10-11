# Chapter 15 Quiz - Algorithms, Ranges and Views

20 multiple-choice questions covering **Chapter 15 (Algorithms, Ranges and Views)**: the iterator
pair and ranges forms of the algorithms, the non-modifying and modifying families, removing and
`erase_if`, sorting, partitions and binary search, the numeric algorithms, callables and
projections, views, `ranges::to`, dangling iterators, and the log pipeline project. Each
question is followed immediately by its correct answer and a short explanation.

---

### 1. What is the main difference between `std::find(first, last, value)` and `std::ranges::find(range, value)`?

A. The ranges form is slower, because it checks more
B. The classic form cannot search a `std::vector`
C. The ranges form takes the container itself, is constrained so that mistakes give readable errors, and accepts projections
D. The ranges form modifies the container

**Answer: C** - both find the same element. The ranges form is shorter to write, its requirements are stated as concepts (chapter 16), and every `std::ranges` algorithm takes an optional projection (15.8).

### 2. Can `std::ranges::transform(source, destination.begin(), f)` make the destination bigger?

A. No: algorithms only write through iterators, so the destination must already have room
B. Yes, it calls `push_back` as needed
C. Yes, it calls `resize` first
D. Only when the destination is a `std::list`

**Answer: A** - an algorithm never changes the size of a container. To grow one, write through `std::back_inserter(destination)`, or size the destination first.

### 3. A vector of 6 elements goes through `std::ranges::remove_if` and two elements match. What is the vector's `size()` afterwards?

A. 4
B. 6, with the 4 kept elements at the front and the leftover tail after them
C. 2
D. It depends on the compiler

**Answer: B** - `remove_if` only moves the elements to keep to the front and returns where they end. It cannot shrink the container, so you follow it with `erase` (the erase-remove idiom).

### 4. Which single call removes every broken reading from a `std::vector` and tells you how many it removed?

A. `v.remove_if(is_broken)`
B. `std::ranges::remove_if(v, is_broken)`
C. `v.erase(is_broken)`
D. `std::erase_if(v, is_broken)`

**Answer: D** - the C++20 `std::erase_if` does both steps and returns the number of elements removed. It works on `vector`, `list`, `map` and the other standard containers.

### 5. What does `std::ranges::sort(people, {}, &Person::age)` do?

A. Sorts the people by age, comparing the ages with the default `<`
B. Sorts the people by age, descending
C. Sorts the ages only and leaves the people alone
D. Does not compile, because `&Person::age` is not a function

**Answer: A** - the third argument is a projection: "look at this part of each element". `{}` means the default comparison. Any callable works, and a pointer to a data member is one.

### 6. A view's `transform` function counts its calls. You iterate the view twice over 4 elements. How many calls were counted?

A. 0, nothing runs until `ranges::to`
B. 4
C. 8, because the function runs again on every pass
D. 2

**Answer: C** - a view is a recipe, evaluated each time you iterate it. If you need the results more than once, finish the pipeline with `std::ranges::to<std::vector>()`, which evaluates once.

### 7. `std::ranges::find_if(load_readings(), pred)` where `load_readings()` returns a vector by value. What is the type of the result?

A. A normal iterator
B. A pointer
C. `std::optional`
D. `std::ranges::dangling`, which cannot be dereferenced

**Answer: D** - an iterator into a temporary would point to destroyed memory. Instead of returning one, the algorithm returns `dangling` and a mistake like `found->station` does not compile. Give the container a name first.

### 8. What does `| std::ranges::to<std::vector>()` do at the end of a pipeline?

A. Nothing, it only changes the type name
B. Evaluates the view and stores the results in a new `std::vector`
C. Sorts the elements
D. Converts the view back into the container it started from

**Answer: B** - it is the step that turns the lazy recipe into real elements. The element type is deduced, and the same works for `std::set`, `std::map` and `std::string`.

### 9. What happens if you call `std::ranges::lower_bound` on a vector that is not sorted?

A. It sorts the vector first
B. It throws an exception
C. It fails to compile
D. It runs and returns a meaningless answer

**Answer: D** - the binary search family (and `merge`, `set_union`, `includes`) require sorted input and cannot check it cheaply. On unsorted data they quietly give wrong answers.

### 10. To order readings by station and, inside each station, by temperature, which sequence of `stable_sort` calls with projections is right?

A. By station first, then by temperature
B. By station only
C. By temperature first, then by station
D. Either order gives the same result

**Answer: C** - sort by the minor key first, then by the major key. Because the sort is stable, readings of the same station keep the temperature order from the first sort.

### 11. What does `std::ranges::nth_element(v, middle)` guarantee?

A. The whole vector is sorted
B. The element at `middle` is the one a full sort would put there, with smaller elements before it and larger after it, in no particular order
C. The first `middle` elements are sorted
D. Only that the vector is partitioned by a predicate

**Answer: B** - it is the cheap way to get a median or a percentile without sorting everything. `partial_sort` (the front sorted) and `partition` (split by a test) answer different questions.

### 12. About how many comparisons does `std::ranges::lower_bound` need on a sorted vector of n elements?

A. About n
B. About n / 2
C. About 1
D. About log n, because it is a binary search

**Answer: D** - it halves the range at every step (7.5). That is why keeping data sorted pays when you search it many times.

### 13. What is the difference between `std::accumulate` and `std::reduce`?

A. `reduce` may combine the elements in any order, so its operation must give the same result in any order; `accumulate` always goes left to right
B. `reduce` only works on integers
C. `accumulate` is parallel and `reduce` is not
D. There is none, they are aliases

**Answer: A** - that freedom is what allows `reduce` to run in parallel (chapter 19). For doubles the last digits of the result can differ, because floating point addition is not exactly associative.

### 14. What do `std::inclusive_scan` and `std::exclusive_scan` (with start value 0) produce for `{1, 2, 3}`?

A. `1 3 6` and `1 3 6`
B. `0 1 3` and `0 1 3`
C. `1 3 6` and `0 1 3`
D. `6 5 3` and `5 3 0`

**Answer: C** - inclusive includes the current element in the running total, exclusive stops just before it.

### 15. You pass a function object with a call counter to `std::ranges::count_if`, and the counter still shows 0 afterwards. Why?

A. `count_if` never calls the function
B. The algorithm worked on a copy of the function object; use a reference capture, `std::ref`, or the object that `for_each` returns
C. Counters cannot be members
D. The function is `const`

**Answer: B** - the standard allows algorithms to copy their callables. State you want to observe must live outside the copy.

### 16. What does `std::views::chunk_by(f)` group?

A. All equal elements, wherever they are
B. Elements by position, three at a time
C. The elements of each container
D. Consecutive elements for which `f(previous, next)` stays true

**Answer: D** - it only looks at neighbours. To group all equal values (the status codes of the log, say), sort first so that equal values become neighbours.

### 17. What is the difference between `std::views::slide(3)` and `std::views::chunk(3)`?

A. `slide` gives overlapping windows (one per position), `chunk` gives separate consecutive groups
B. `slide` is lazy and `chunk` is not
C. They are the same
D. `chunk` overlaps, `slide` does not

**Answer: A** - for 8 elements, `slide(3)` gives 6 windows (a moving average), `chunk(3)` gives 3 groups, the last one shorter.

### 18. Why can a `const` `filter_view` not be iterated?

A. Filters are not allowed on `const` data
B. Because `filter` always copies the container
C. Its `begin()` remembers where the first match is, so it changes the view
D. Because lambdas are not `const`

**Answer: C** - the cached position makes `begin()` a function that changes the view, so a `const` view cannot call it. A filter view has to be iterated through a non-`const` variable (a plain `for (auto x : view)` does that).

### 19. `std::vector<int> v; v.reserve(10); std::ranges::copy(source, v.begin());`. What is wrong?

A. Nothing, `reserve` makes room for the elements
B. It writes into elements that do not exist: `reserve` creates none, so use `std::back_inserter(v)` or size the vector
C. `copy` cannot write to a vector
D. It copies in the wrong direction

**Answer: B** - `reserve` changes the capacity, never the size (14.3). The vector is still empty, so writing through `begin()` is undefined behaviour.

### 20. How did the pipeline version of the log analyzer (15.11) compare with the loops of chapter 14?

A. Shorter, an identical report, but slower
B. Longer, an identical report, and slower
C. Shorter, a different report, and slower
D. Shorter, an identical report, and faster

**Answer: A** - about a fifth fewer lines of code and the same numbers, but it sorts and re-walks the data where the hash tables count in one pass, so it ran roughly 1.6 to 2.4 times slower in our runs.
