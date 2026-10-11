# Algorithms, Ranges and Views

Chapter 14 gave you the containers. This chapter gives you what you do with them. Look at what you have been writing by hand: a loop to find the biggest, a loop to count the ones that match, a loop to remove the bad ones, a loop to add things up. Each of those loops has been written, tested and tuned by the standard library already, and has a name.

```
   the loop you write                           the name it already has
   ──────────────────────────────────           ───────────────────────────────
   for (...) if (x > 20) ++n;                   std::ranges::count_if(v, hot)
   for (...) if (x < best) best = x;            std::ranges::min_element(v)
   for (...) out.push_back(f(x));               std::ranges::transform(v, out, f)
   for (...) sum += x;                          std::reduce, std::ranges::fold_left
   erase loop of 14.4                           std::erase_if(v, broken)
```

Why prefer the name? Three reasons that add up over a whole program:

- **It says what it does.** `count_if` tells the reader the intent; a loop makes the reader work it out.
- **It is already right.** The off-by-one, the skipped element after an erase, the forgotten empty case (14.4 was all about those) are not yours to get wrong.
- **It is often faster.** The library knows its containers.

The chapter has three parts:

1. **Algorithms** (15.2 to 15.7): the `<algorithm>` and `<numeric>` families, with the C++20 `std::ranges::` form as the default way to call them.
2. **Callables and projections** (15.8): how to tell an algorithm *what to do* and *what to look at*.
3. **Views** (15.9, 15.10): lazy pipelines, which you met in 7.6, and everything that goes with them: `ranges::to` and the rules about ownership. The **project** (15.11) redoes the chapter 14 log analyzer with all of it, and compares.

The running data is the weather station again: readings with a station, an hour and a temperature, and one reading of `-99.0`, which is what a broken sensor reports.

A note on compilers. Everything in this chapter was built and run on MSVC, GCC 16 and Clang 21, and **prints byte-identical output on all three**. The C++23 views (`zip`, `enumerate`, `chunk`, `slide`, `cartesian_product` and more) need a recent library. The Clang image of the course uses the GNU library `libstdc++` 14 by default and has them (except `std::ranges::starts_with`), but **Clang with libc++ does not yet**: it is the opposite of 14.9, where `flat_map` needed libc++. On Qt Creator with an older compiler, expect to find `zip`, `enumerate`, `chunk`, `slide` and `std::ranges::to` missing and fall back to the algorithms of 15.3 to 15.8, which work from C++20 on.

---

## 15.2 Algorithms: iterator pairs and ranges

In this lecture we meet the two ways of calling an algorithm, and what an algorithm can and cannot do.

### What an algorithm is

An **algorithm** is a function that works on a sequence of elements through its iterators (14.2). It does not know what container the elements are in. That is why one `find` serves a vector, a list and a deque.

There are two forms of every algorithm:

```cpp
auto classic{std::find(temperatures.begin(), temperatures.end(), 21.5)};   // an iterator PAIR
auto modern{std::ranges::find(temperatures, 21.5)};                         // the container itself
```

```
classic: index 2   ranges: index 2
```

They do the same work. The second form (C++20) is:

- **shorter**: no `begin()` and `end()`
- **checked**: the compiler verifies at your call that the range is suitable for the algorithm, so a mistake is reported where you made it (an example below)
- **richer**: it takes a *projection*, which 15.8 explains

Use the `std::ranges::` form in new code. You will still read the classic form everywhere, and the `<numeric>` algorithms of 15.7 are mostly still classic.

Both return an iterator, and `end()` means "not found" (14.2):

```cpp
if (std::ranges::find(temperatures, 99.0) == temperatures.end()) {
    std::println("99.0 is not there");
}
```

### A part of a container

An iterator pair can describe just a **part** of a container, which is what makes the classic form flexible. Sort only the first three of `{18.5, 24.0, 21.5, 12.5, 16.0}`:

```cpp
std::sort(sorted_part.begin(), sorted_part.begin() + 3);                    // the first three
```

```
first three sorted: 18.5 21.5 24 12.5 16
```

The first three are in order; the last two were not touched. (The ranges form has a neat way to say the same with *views*, which 15.9 introduces.)

### The iterator category still decides

Algorithms need iterators that are strong enough (14.2). `std::sort` needs random access, so:

```cpp
std::list<double> as_list{temperatures.begin(), temperatures.end()};
// std::ranges::sort(as_list);        // error
as_list.sort();                       // the list's own member function (14.5)
```

This is where the ranges form earns its keep. The same mistake, in both forms, on GCC and Clang:

```
std::sort(l.begin(), l.end());       error inside the library:  no match for 'operator-'
                                     (operand types are 'std::_List_iterator<int>' ...)   (over 30 lines in all)

std::ranges::sort(l);                error at YOUR call:        'std::list<int> &' does not satisfy
                                     'random_access_range'
```

The first tells you the library tried to subtract two list iterators; you have to work out why. The second names the requirement that failed.

### What they return

An algorithm returns what it knows:

```cpp
auto [smallest, largest]{std::ranges::minmax(temperatures)};     // both values, in one pass
auto result{std::ranges::copy(temperatures, copy.begin())};      // where input ended, where output ended
```

```
minmax: 12.5 and 24
max_element points at 24
copy returned two iterators: the output now ends at index 5
```

### An algorithm never changes the size of a container

This is the rule that explains the rest of the chapter. An algorithm only moves **values** around, through iterators. To add or remove elements, you either write through an *inserter* (15.4), or you tell the container itself (15.5).

### The families

```
   non-modifying   find, count, any_of, equal, mismatch ...          15.3
   modifying       copy, transform, fill, replace, reverse ...        15.4
   removing        remove, remove_if, unique, erase_if                15.5
   sorting         sort, partition, nth_element, binary search ...    15.6
   numeric         reduce, partial_sum, transform_reduce ...          15.7
```

**Code for this lecture**: `15.2AlgorithmsAndRanges/main.cpp`.

---

## 15.3 Non-modifying algorithms

In this lecture we ask questions of a range: is there one, how many, which one, are they the same. Nothing in the container changes.

### The data

```cpp
struct Reading {
    std::string station;
    int hour;
    double celsius;
};

std::vector<Reading> readings{
    {"north", 6, 11.5}, {"north", 12, 18.5}, {"north", 18, 15.0},
    {"south", 6, 14.0}, {"south", 12, 24.0}, {"south", 18, 20.5},
    {"east", 6, 12.5},  {"east", 12, 21.5},  {"east", 18, 17.0},
    {"west", 6, 9.0},   {"west", 12, 16.0},  {"west", 18, -99.0}};
```

Two small predicates (a function that answers yes or no, 6.14) are reused below:

```cpp
auto is_broken{[](const Reading& r) { return r.celsius < -50.0; }};
auto is_hot{[](const Reading& r) { return r.celsius > 20.0; }};
```

### Yes/no questions

```cpp
std::ranges::any_of(readings, is_broken)       // is there at least one?
std::ranges::all_of(readings, is_hot)          // are they all?
std::ranges::none_of(readings, ...)            // is there none?
```

```
any broken?   true
all hot?      false
none frozen?  true
```

On an empty range `all_of` and `none_of` are `true` and `any_of` is `false`: "all of nothing" is vacuously true.

### Counting

```
hot readings: 3
readings at hour 12: 4
```

```cpp
std::ranges::count_if(readings, is_hot)
```

### Finding

Finding returns an iterator; `end()` means none.

```cpp
if (auto it{std::ranges::find_if(readings, is_hot)}; it != readings.end()) {
    std::println("first hot one: {} at {}h, {}", it->station, it->hour, it->celsius);
}
auto not_north{std::ranges::find_if_not(readings, ...)};                // the first that does NOT match
auto last_hot{std::ranges::find_last_if(readings, is_hot)};             // C++23: a subrange, from the last match to the end
```

```
first hot one: south at 12h, 24
broken sensor: west at 18h
first reading that is not north: south
last hot one: east at 12h
```

`find_last_if` returns a *subrange* (a pair of iterators in one object); `.front()` is the last match.

### Smallest and largest

```cpp
auto by_temperature{[](const Reading& a, const Reading& b) { return a.celsius < b.celsius; }};
auto coldest{std::ranges::min_element(good, by_temperature)};
```

```
coldest: west 6h 9
warmest: south 12h 24
```

(`good` is the readings without the broken one, built here with a plain loop and `push_back`. The next lecture does the same in one line, with `copy_if`.) 15.8 shows a shorter way to say "by temperature": a projection.

### Comparing two sequences

```cpp
std::ranges::equal(expected_hours, actual_hours)
auto [first_expected, first_actual]{std::ranges::mismatch(expected_hours, actual_hours)};
```

```
hours as expected: true
first difference at index 7: expected 12, got 13
```

`mismatch` returns *two* iterators: the first position where the sequences differ, in each.

### Looking for a pattern

```cpp
auto where{std::ranges::search(hours, pattern)};        // a sub-sequence, as a subrange
auto twice{std::ranges::adjacent_find(hours)};          // two equal neighbours
std::ranges::contains(hours, 18)                        // C++23: just yes or no
```

```
pattern 12,18 first found at index 1
first repeated neighbour at index 4
contains 18: true   contains 24: false
```

### `for_each`

```cpp
double total{0.0};
std::ranges::for_each(good, [&](const Reading& r) { total += r.celsius; });
```

```
average of the 11 good readings: 16.32
```

`for_each` is the algorithm closest to a loop, and for a plain loop a range-based `for` is usually clearer. It earns its place when you already have a function to apply, or (15.8) because it hands back the callable.

### The pattern to remember

> **When you catch yourself writing a loop that asks a question, there is almost always an algorithm named after the question.**

**Code for this lecture**: `15.3NonModifyingAlgorithms/main.cpp`.

---

## 15.4 Modifying algorithms

In this lecture we change values, or copy them somewhere else.

### A helper to print

C++23 can print a whole vector with `std::println("{}", v)`. That works with GCC 15 and later and current MSVC, but **not** with the library of the Clang image (`libstdc++` 14), and the programs of this chapter must run on all three. So the lectures use a small helper:

```cpp
template <typename T>
void show(std::string_view label, const std::vector<T>& values) {
    std::print("{:<22}", label);
    for (const T& value : values) {
        std::print(" {}", value);
    }
    std::println();
}
```

It is a function template (6.13): `T` is whatever the element type of the vector you pass turns out to be, so the same helper prints a `vector<int>`, a `vector<double>` or a `vector<std::string>`. You can use `std::println("{}", v)` instead when your compiler supports it.

### `transform`

Apply a function to every element, writing the results out.

```cpp
std::vector<double> celsius{11.5, 18.5, 15.0, -99.0, 24.0, 20.5};
std::vector<double> fahrenheit(celsius.size());                 // () : N elements. {} would make a list (7.4)
std::ranges::transform(celsius, fahrenheit.begin(), [](double c) { return c * 9.0 / 5.0 + 32.0; });
```

```
celsius:               11.5 18.5 15 -99 24 20.5
fahrenheit:            52.7 65.3 59 -146.2 75.2 68.9
```

The destination must have room, because an algorithm cannot make room (15.2). When it has none yet, write through an **inserter**: an output iterator that calls `push_back` for every value it is given.

```cpp
std::vector<double> converted;
std::ranges::transform(celsius, std::back_inserter(converted), [](double c) { return c + 273.0; });
```

```
kelvin (rounded):      284.5 291.5 288 174 297 293.5
```

And the trap that goes with it:

```cpp
std::vector<double> converted;
converted.reserve(celsius.size());
std::ranges::transform(celsius, converted.begin(), ...);        // WRONG
```

`reserve` creates **no elements** (14.3): the vector is still empty and the algorithm writes into memory that does not hold elements yet. Undefined behaviour. Either size the vector with `(n)`, or use `back_inserter`.

`transform` can also take two inputs and combine them element by element:

```cpp
std::ranges::transform(celsius, offsets, std::back_inserter(corrected), std::plus<>{});
```

```
corrected:             12 19 14.5 -99 25 20.5
```

### `copy` and `copy_if`

```cpp
std::ranges::copy_if(celsius, std::back_inserter(warm), [](double c) { return c > 17.0; });
```

```
warm only:             18.5 24 20.5
```

### `replace`, `fill`, `iota`, `generate`

```cpp
std::ranges::replace_if(repaired, [](double c) { return c < -50.0; }, 0.0);      // change values in place
std::ranges::iota(hours, 6);                                                     // 6, 7, 8 ... (C++23 algorithm)
std::ranges::fill(hours, 0);
std::ranges::generate(hours, [&] { return next_hour += 4; });                    // call a function per element
```

```
broken became 0:       11.5 18.5 15 0 24 20.5
iota from 6:           6 7 8 9 10 11
fill with 0:           0 0 0 0 0 0
generate +4:           4 8 12 16 20 24
```

### `reverse` and `rotate`

```cpp
std::ranges::reverse(day);                                       // 0 6 12 18  ->  18 12 6 0
std::ranges::rotate(shifted, shifted.begin() + 2);               // 0 6 12 18  ->  12 18 0 6
```

`rotate` makes the middle element the new first one: the day now starts at noon. It is the neat way to move a block of elements without a temporary.

### `unique`

```cpp
std::ranges::sort(stations_seen);                                // 3 1 3 2 1 3  ->  1 1 2 3 3 3
auto removed{std::ranges::unique(stations_seen)};                // moves the distinct ones forward
stations_seen.erase(removed.begin(), removed.end());             // and the container drops the tail
```

```
distinct:              1 2 3
```

`unique` removes **consecutive** duplicates, so sort first. And it is another case of "an algorithm cannot shrink a container", which is the next lecture.

**Code for this lecture**: `15.4ModifyingAlgorithms/main.cpp`.

---

## 15.5 Erase-remove and `erase_if`

In this lecture we remove elements from a container, the right way. The right way used to be a famous trap.

### `remove_if` does not erase

"Remove the broken readings" sounds like one step. It is two, because `remove_if` is an algorithm, and an algorithm only has iterators.

```cpp
std::vector<double> celsius{11.5, -99.0, 15.0, -99.0, 24.0, 20.5};
auto garbage{std::ranges::remove_if(celsius, is_broken)};        // a subrange: the leftover tail
```

```
before:                    11.5 -99 15 -99 24 20.5
size after remove_if: 6 (unchanged)
kept: 4 elements, tail: 2 elements
```

`remove_if` moves the elements to **keep** to the front, in order, and returns where they end. The vector is exactly as long as before. What lies in the tail is "valid but unspecified": do not read it.

```
   before     [11.5][-99][15][-99][24][20.5]
   after      [11.5][ 15][24][20.5][ ? ][ ? ]
                                    ▲
                           returned: the new logical end
```

The second step belongs to the **container**:

```cpp
celsius.erase(garbage.begin(), garbage.end());
```

```
after erase:               11.5 15 24 20.5
size now: 4
```

Together, those two lines are the **erase-remove idiom**, and for years it was written as `v.erase(std::remove_if(v.begin(), v.end(), pred), v.end())`. Forget the `erase` and you have a vector that looks the same size, with junk at the end: a classic bug.

### `std::erase_if`

C++20 did the obvious thing: one function that does both steps and returns how many it removed.

```cpp
auto count{std::erase_if(readings, is_broken)};
std::erase(hours, 6);                                            // by value
```

```
erase_if removed 2
readings:                  11.5 15 24 20.5
hours without 6:           12 18
```

14.4 solved the same problem with a loop and the iterator that `erase` returns. `erase_if` is that loop, written once, correctly, for every container.

### The same function on every container

```cpp
std::list<std::string> jobs{"upload", "test", "calibrate", "test", "report"};
std::erase(jobs, "test");

std::map<std::string, double> latest{{"north", 18.5}, {"south", -99.0}, {"east", 21.5}, {"west", -99.0}};
std::erase_if(latest, [](const std::pair<const std::string, double>& entry) { return entry.second < -50.0; });
```

```
list without test:          upload calibrate report
map without broken:         east=21.5 north=18.5
```

For a map the predicate receives one element, which is a pair of (`const` key, value) as you saw in 14.6, and `entry.second` is the value. A map cannot use `remove_if`: it would have to assign over elements whose key is `const` (14.6), and the order of keys must not change under the map's feet. So `erase_if` for a map erases the matching nodes one by one. That is a good reason to have a function per container, behind one name.

### The pattern to remember

> **To remove elements: `std::erase_if(container, predicate)`. Never a hand-written erase loop, never `remove_if` without its `erase`.**

**Code for this lecture**: `15.5EraseRemoveAndEraseIf/main.cpp`.

---

## 15.6 Sorting, partitions and binary search

In this lecture we meet the sorting algorithms that are not `sort`, and the family of binary searches. `sort` itself and `binary_search` were 7.5.

### Not everything needs a full sort

Sorting everything costs O(n log n). Often the question is smaller.

```cpp
std::vector<int> temperatures{21, 15, 24, 9, 18, 12, 24, 6, 15, 27};
```

```
sort:                    6 9 12 15 15 18 21 24 24 27
```

**`partial_sort`**: the n smallest, in order. The rest is left in no particular order.

```cpp
std::ranges::partial_sort(three_coldest, three_coldest.begin() + 3);
```

```
partial_sort, first 3:   6 9 12
```

**`nth_element`**: the element that *would be* at position n in a sorted range goes there, smaller ones before it, larger ones after, in no order. That is the cheap way to get a **median**:

```cpp
auto middle{for_median.begin() + for_median.size() / 2};
std::ranges::nth_element(for_median, middle);
```

```
median (position 5): 18
```

**`stable_sort`** keeps equal elements in their original order. It matters when you sort records by one field after sorting by another (15.8).

`is_sorted` asks whether a range is already in order.

### Partitions

**`partition`** reorders a range so that everything satisfying a test comes first. **`stable_partition`** also keeps the order inside each group.

```cpp
auto cold{[](int t) { return t < 15; }};
auto boundary{std::ranges::stable_partition(split, cold)};
```

```
cold first:              9 12 6 21 15 24 18 24 15 27
3 cold readings; the rest start at index 3
```

On a range that is already partitioned, `partition_point` finds the boundary with a **binary search** instead of a scan:

```
partition_point: index 3
```

### The binary search family

7.5's `binary_search` says whether a value is there. The rest of the family says **where**, and how many. All of them need the data **sorted**.

```cpp
auto first_24{std::ranges::lower_bound(all, 24)};              // first element >= 24
auto after_24{std::ranges::upper_bound(all, 24)};              // first element > 24
auto run{std::ranges::equal_range(all, 24)};                   // both, as a subrange
```

```
lower_bound(24): index 7   upper_bound(24): index 9
24 appears 2 times
readings above 20: 4
```

Between `lower_bound` and `upper_bound` is the block of equal elements. That makes **counting in a range** trivial: "how many readings are between 15 and 25?" is the distance between `lower_bound(15)` and `lower_bound(25)`. (That is exercise 5.)

### Merging and set operations on sorted ranges

Two sorted ranges can be combined in a single pass:

```cpp
std::vector<int> monday{6, 9, 12, 15, 18};
std::vector<int> tuesday{9, 10, 15, 21};
std::ranges::merge(monday, tuesday, std::back_inserter(both));
std::ranges::set_union(monday, tuesday, std::back_inserter(either));
std::ranges::set_intersection(monday, tuesday, std::back_inserter(common));
std::ranges::set_difference(monday, tuesday, std::back_inserter(only_monday));
```

```
merge:                   6 9 9 10 12 15 15 18 21
set_union:               6 9 10 12 15 18 21
set_intersection:        9 15
set_difference:          6 12 18
monday includes {9, 15}: true
```

(`merge` keeps duplicates; `set_union` does not.)

### The warning to repeat

Everything in this lecture that says "sorted" means it. On unsorted data these functions **compile, run and quietly give wrong answers**. There is no check. If you are not sure the data is sorted, `std::ranges::is_sorted` is the question to ask first.

**Code for this lecture**: `15.6SortingPartitionsBinarySearch/main.cpp`.

---

## 15.7 Numeric algorithms

In this lecture we meet the algorithms that **combine** values: sums, products, running totals, differences. They live in `<numeric>`.

Most of them are older than C++20 and have no `std::ranges::` twin, so they take iterator pairs (14.2). The exceptions are `iota` and the C++23 folds.

The data is the millimetres of rain in each hour of a morning:

```cpp
std::vector<int> rain{0, 2, 5, 0, 1, 7, 3, 0};
```

### Adding up

```cpp
std::accumulate(rain.begin(), rain.end(), 0)                         // 7.5: left to right
std::reduce(rain.begin(), rain.end(), 0)                             // any order
std::ranges::fold_left(rain, 0, std::plus<>{})                       // C++23: takes a range
```

```
accumulate: 18
reduce:     18
fold_left (C++23, takes a range): 18
```

**`reduce` may combine the elements in any order.** Its operation must therefore give the same result in any order (`+` on integers does). That freedom is what lets it run in parallel (chapter 19). With `double`s the last digits can differ from `accumulate`, because floating point addition is not exactly associative, the same warning as comparing doubles in 12.7.

`fold_left` is the C++23 version of `accumulate`, over a range, with any operation. The largest value is a fold with `max`:

```cpp
int largest{std::ranges::fold_left(rain, 0, [](int a, int b) { return std::max(a, b); })};
```

### `transform_reduce`: transform, then reduce

```cpp
// the dot product: multiply pairs, add up
double total{std::transform_reduce(prices.begin(), prices.end(), quantities.begin(), 0.0)};

// sum of squares: transform each element, then add
std::transform_reduce(rain.begin(), rain.end(), 0, std::plus<>{}, [](int x) { return x * x; });

// counting with a test: transform each value to 0 or 1, then add
std::transform_reduce(rain.begin(), rain.end(), 0, std::plus<>{}, [](int x) { return x > 0 ? 1 : 0; });
```

```
dot product (total cost): 26.5
sum of squares of rain: 88
hours with any rain: 5
```

(The first is `2.5 * 3 + 4.0 * 1 + 1.5 * 10`: price times quantity.)

### Running totals: scans

A **scan** keeps every intermediate result of a fold.

```cpp
std::inclusive_scan(rain.begin(), rain.end(), running.begin());          // includes the current element
std::exclusive_scan(rain.begin(), rain.end(), before.begin(), 0);        // the total BEFORE the current one
```

```
rain per hour:             0 2 5 0 1 7 3 0
inclusive_scan:            0 2 7 7 8 15 18 18
exclusive_scan:            0 0 2 7 7 8 15 18
```

`partial_sum` is the older name for `inclusive_scan` (the output is the same; `inclusive_scan` may also run in parallel).

### `adjacent_difference`: the inverse

What changed from one element to the next? The first element is copied as it is.

```cpp
std::adjacent_difference(running.begin(), running.end(), change.begin());
```

```
running total -> back:     0 2 5 0 1 7 3 0
recovered the original: true
```

Feeding a running total into `adjacent_difference` returns the original rain. Applied to temperatures it gives "how much warmer than the hour before".

### Small helpers

```cpp
std::gcd(12, 18)            // 6
std::lcm(4, 6)              // 12
std::midpoint(10, 20)       // 15, without the overflow risk of (a + b) / 2
std::iota(begin, end, 6)    // 6 7 8 9 10 ...
```

### The mean, carefully

```cpp
double mean{static_cast<double>(std::reduce(rain.begin(), rain.end(), 0)) / static_cast<double>(rain.size())};
```

```
average rain per hour: 2.250 mm
```

Cast before you divide: integer division throws away the fraction (5.2).

**Code for this lecture**: `15.7NumericAlgorithms/main.cpp`.

---

## 15.8 Callables and projections

In this lecture we answer the two questions every algorithm asks: *what should I do?* and *what should I look at?*

### Six ways to say "what to do"

An algorithm that takes "a function" takes anything **callable**. Six different things, one question: how many temperatures are above 20?

```cpp
bool is_hot_function(double celsius) { return celsius > 20.0; }                 // 1. a plain function

struct HotterThan {                                                              // 2. a function object (12.6)
    double limit;
    bool operator()(double celsius) const { return celsius > limit; }
};

auto lambda{[](double c) { return c > 20.0; }};                                  // 3. a lambda (6.14)
std::function<bool(double)> stored{lambda};                                      // 4. a std::function
auto bound{std::bind_back(std::greater<>{}, 20.0)};                              // 5. bind_back: fixes the SECOND argument
double limit{20.0};
// 6. a lambda with a capture (6.14):  [limit](double c) { return c > limit; }
```

All six give the same answer:

```
function pointer: 3
function object:  3
lambda:           3
std::function:    3
bind_back:        3
lambda with a capture: 3
```

Which to use?

- A **lambda** for almost everything: it is local, it can capture, and the compiler can inline it.
- A **function object** when the callable has a name and state you want to reuse.
- **`std::function`** when you must *store* callables of different origins in one type: a table of commands, a callback member. It costs an indirect call and sometimes an allocation, so not as a default parameter type for an algorithm.
- A plain **function pointer** for C-style interfaces.

### A seventh kind: a pointer to a member

There is one more callable you have not met, and the projections below depend on it. Look at this expression:

```cpp
auto which_member{&Reading::celsius};
```

`&Reading::celsius` is **not** the temperature of any reading. It means *"the `celsius` member of a `Reading`"*, to be applied to a particular reading later. It is called a **pointer to a member**: a pointer, not to a place in memory, but to a *part of a type*.

To use it, you need an object to apply it to. `std::invoke(callable, arguments...)` calls *any* callable in one uniform way, and for a pointer to a member, "calling" it means reading that member of the object you pass:

```cpp
Reading sample{"south", 12, 24.0};
std::invoke(which_member, sample)        // the same as sample.celsius
```

```
std::invoke(which_member, sample) = 24
```

That is what lets an algorithm that wants "a function that takes a `Reading`" accept `&Reading::celsius`: for the algorithm, it *is* such a function. It is the shortest way to say "look at the celsius".

### Projections: "what to look at"

Every `std::ranges` algorithm takes an optional **projection** after the comparison: a callable applied to each element *before* it is compared. Instead of writing a comparison that digs out the field on both sides, you name the field.

```cpp
std::ranges::sort(by_temperature, {}, &Reading::celsius);                 // sort(range, comparison, projection)
```

`{}` means "the default comparison" (`<`). The projection is applied to both sides of every comparison, so the comparison itself stays ordinary. To sort descending, change only that:

```cpp
std::ranges::sort(by_temperature, std::ranges::greater{}, &Reading::celsius);
```

```
start:                       n6:11.5 n12:18.5 n18:15 s6:14 s12:24 s18:20.5 e6:12.5 e12:21.5 e18:17
sorted by temperature:       n6:11.5 e6:12.5 s6:14 n18:15 e18:17 n12:18.5 s18:20.5 e12:21.5 s12:24
hottest first:               s12:24 e12:21.5 s18:20.5 n12:18.5 e18:17 n18:15 s6:14 e6:12.5 n6:11.5
```

(Each reading is shown as the first letter of the station, the hour, and the temperature.)

Compare it with the lambda version of 15.3: `[](const Reading& a, const Reading& b) { return a.celsius < b.celsius; }`. The projection is the same idea in a quarter of the text, and it cannot be wrong in the one way that comparisons often are (comparing `a.celsius` with `b.hour`).

### Sorting by two keys

Sort by the **minor** key first, then by the **major** key with a *stable* sort. Equal majors keep their minor order.

```cpp
std::ranges::stable_sort(grouped, {}, &Reading::hour);
std::ranges::stable_sort(grouped, {}, &Reading::station);
```

```
by station, then hour:       e6:12.5 e12:21.5 e18:17 n6:11.5 n12:18.5 n18:15 s6:14 s12:24 s18:20.5
```

Inside each station the hours are 6, 12, 18: the first sort put them in numeric order, and the second sort, being stable, did not disturb it. (Had the hours been sorted as text, `"12"` would have come before `"6"`: the projection decides what is compared.)

### Finding and extremes

Projections work with finding as well. `find` compares the *projected* value with the value you give:

```cpp
auto warmest{std::ranges::max_element(readings, {}, &Reading::celsius)};
auto first_south{std::ranges::find(readings, "south", &Reading::station)};
```

```
warmest: south at 12h (24)
first south reading: 6h
```

A projection can be a lambda too:

```cpp
std::ranges::stable_sort(names, {}, [](const std::string& name) { return name.size(); });
```

```
names by length: east west north south
```

(`stable_sort` because `east` and `west` have the same length, and plain `sort` does not say which comes first: the output could differ between compilers.)

### The algorithm may copy your callable

```cpp
struct Counter {
    int calls{0};
    bool operator()(double c) { ++calls; return c > 20.0; }
};
Counter counter;
auto hot{std::ranges::count_if(temperatures, counter)};
```

```
found 3 hot, but the counter object says 0 calls (the algorithm worked on a copy)
```

`count_if` found three, but the `calls` member of *your* object is still zero: the algorithm was given a copy and counted in that. The standard allows it. Three ways to see the state:

```cpp
// 1. a reference capture
int calls{0};
std::ranges::count_if(temperatures, [&calls](double c) { ++calls; return c > 20.0; });

// 2. std::ref: a wrapper that copies a REFERENCE to your object
std::ranges::count_if(temperatures, std::ref(by_reference));

// 3. for_each hands the callable back
auto [end, finished]{std::ranges::for_each(temperatures, Counter{})};
```

```
reference capture:  6 calls (found 3)
std::ref(counter):  6 calls (found 3)
for_each returns the callable: 6 calls
```

### `std::function` in a table

```cpp
std::map<std::string, std::function<double(double)>> conversions{
    {"to fahrenheit", [](double c) { return c * 9.0 / 5.0 + 32.0; }},
    {"to kelvin", [](double c) { return c + 273.0; }},
    {"doubled", [](double c) { return c * 2.0; }}};
```

```
doubled        40
to fahrenheit  68
to kelvin      293
```

Three lambdas of three different types (each lambda has its own type) live in one container because `std::function<double(double)>` erases the difference. That is what `std::function` is for.

### The pattern to remember

> **Say what to do with a lambda, and what to look at with a projection.**

**Code for this lecture**: `15.8CallablesAndProjections/main.cpp`.

---

## 15.9 More views

In this lecture we meet the rest of the views worth knowing. 7.6 introduced the three basics: `iota`, `filter` and `transform`, and the idea of **laziness**: a view is a recipe, evaluated when you iterate it, and it owns no elements.

### Seeing inside a view

A view holds no elements, so there is nothing in it to print. To **look at what a view contains**, collect it into a vector. `std::ranges::to<std::vector>()` at the end of a pipeline does exactly that:

```cpp
std::vector<int> hours{6, 7, 8, 9, 10, 11, 12, 13};
auto first_three{hours | std::views::take(3) | std::ranges::to<std::vector>()};
show("take(3):", first_three);
```

```
take(3):               6 7 8
```

`to` evaluates the recipe once and stores the results in a new `std::vector`. That is all we need for now (the `show` helper is the one from 15.4, for vectors); 15.10 says more about `to`, including the other containers it can build.

Here are the views in groups. Each line shows what the view does to the vector `hours`.

### Selecting

```cpp
hours | std::views::take(3)                      // the first three
hours | std::views::drop(5)                      // all but the first five
hours | std::views::take_while(less_than_9)      // from the start, while the test holds
hours | std::views::drop_while(less_than_11)     // skip from the start, while the test holds
hours | std::views::stride(3)                    // every third
hours | std::views::reverse                      // backwards
hours | std::views::drop(2) | std::views::take(3)  // views compose
```

(In the program each of these ends with `| std::ranges::to<std::vector>()` so that `show` can print it.)

```
take(3):               6 7 8
drop(5):               11 12 13
take_while(<9):        6 7 8
drop_while(<11):       11 12 13
stride(3):             6 9 12
reverse:               13 12 11 10 9 8 7 6
drop(2) | take(3):     8 9 10
iota(100) | take(4):   100 101 102 103
```

The last line starts from an **infinite** view, `iota(100)` with no end, and stops it with `take(4)`. Laziness makes that fine: nothing computes beyond what is asked.

A view can also stand in for an iterator pair. This is the ranges way to do what 15.2 did with `begin() + 3`, sorting just the first three, here largest first:

```cpp
std::vector<double> some{temperatures};
std::ranges::sort(some | std::views::take(3), std::ranges::greater{});
```

```
3 largest first:       14.5 12 11.5 17 20 23.5 24 22.5
```

The first three elements of `{11.5, 12.0, 14.5, ...}` were put in descending order, and the rest were not touched. (`std::ranges::greater{}` is the comparison "greater than", which 15.8 explains.)

### Looking inside pairs

```cpp
latest | std::views::keys                        // east north south
latest | std::views::values                      // 21.5 18.5 24
```

For a map or any range of pairs, `keys` and `values` give one half of each.

### Splitting and joining

```cpp
for (auto part : line | std::views::split(',')) {
    std::print(" [{}]", std::string_view{part});
}
```

```
split on ',':       [north] [south] [east] [west]
join_with ' / ':   north / south / east
join (flatten):        1 2 3 4 5 6
```

`split` cuts a range at a separator; each piece is a *subrange* of the original characters, so wrap it in a `std::string_view` (7.9) to print or search it. `join_with` is the opposite: glue the pieces with a separator between them. `join` flattens a range of ranges (here `{{1, 2}, {3}, {4, 5, 6}}`).

### Several ranges at once

```cpp
std::views::zip(hours, temperatures)             // pairs: (6, 11.5), (7, 12.0) ...
std::views::enumerate(words)                     // (0, "north"), (1, "south") ...
std::views::cartesian_product(stations, times)   // every station with every time
```

```
zip hour:temp:      6h:11.5 7h:12 8h:14.5 9h:17
enumerate:          0=north 1=south 2=east
cartesian_product:  N6 N12 S6 S12
```

`zip` walks several ranges in step, stopping at the shortest. `enumerate` is what other languages call `enumerate`: the index comes with the element, so a loop does not need a counter variable. Both are used with a structured binding, `for (auto [index, station] : ...)` (10.11).

### Groups and windows

```cpp
hours | std::views::chunk(3)                     // separate groups of 3
temperatures | std::views::slide(3)              // OVERLAPPING windows of 3
temperatures | std::views::adjacent<2>           // every element with its next one
gaps | std::views::chunk_by(f)                   // split where f(previous, next) is false
```

```
chunk(3):           [6 7 8 ] [9 10 11 ] [12 13 ]
3-hour average:     12.67 14.50 17.17 20.17 22.50 23.33
rise per hour:      +0.5 +2.5 +2.5 +3.0 +3.5 +0.5 -1.5
runs of hours:      3 2 1   (from 6 7 8 | 12 13 | 18)
```

- `chunk(3)` cuts into groups; the last may be shorter.
- `slide(3)` is the **moving window**. Each window is a view of three neighbouring temperatures, and adding them up with `fold_left` (15.7) gives a moving average:

  ```cpp
  for (auto window : temperatures | std::views::slide(3)) {
      double average{std::ranges::fold_left(window, 0.0, std::plus<>{}) / 3.0};
      std::print(" {:.2f}", average);
  }
  ```

  `auto window` is a plain variable declared with `auto` (4.4): its type is a view type with a long name, which `auto` saves you from writing.
- `adjacent<2>` (also called `pairwise`) gives each element with its successor: the differences between consecutive readings.
- `chunk_by(f)` groups **consecutive** elements while `f(previous, next)` holds. It only compares neighbours, so to group all equal values you must **sort first**: the project does exactly that.

### Availability

All of these are in GCC 15 and 16, current MSVC, and Clang with `libstdc++`. Clang with `libc++` lacks `chunk`, `slide`, `stride`, `enumerate`, `adjacent` and `cartesian_product` so far. `take`, `drop`, `reverse`, `split`, `join_with`, `zip` and `chunk_by` were present everywhere we tried.

**Code for this lecture**: `15.9MoreViews/main.cpp`.

---

## 15.10 `ranges::to`, ownership and dangling

In this lecture we look closer at finishing a pipeline, and learn the rules that keep views from pointing at things that are gone.

### From a recipe to a container

You used `std::ranges::to<std::vector>()` in 15.9 to look inside a view. A pipeline of views is a recipe, and `to` is how you turn it into real elements in a container. It can build other containers too:

```cpp
auto fahrenheit{celsius
                | std::views::transform([](double c) { return c * 9.0 / 5.0 + 32.0; })
                | std::ranges::to<std::vector>()};               // the element type is deduced
```

```
as a vector:             65.3 75.2 70.7 60.8
as a set:            6 12 18
zip into a map:       east=21.5 north=18.5 south=24 west=16
as a string:        NORTH
```

The same works for a `std::set`, for a `std::map` (a range of pairs, here from `zip`, becomes keys and values), and for a `std::string` (a range of characters). For the string, a `char`-to-`char` `transform` with `toupper` (take the parameter as `unsigned char`: `toupper` is not defined for negative values) does the job in one line.

### Lazy means: computed again on every pass

A view runs its function every time you iterate it:

```cpp
int calls{0};
auto doubled{std::views::iota(1, 5) | std::views::transform([&calls](int x) { ++calls; return x * 2; })};
for (int x : doubled) {}
for (int x : doubled) {}
```

```
two passes over 4 elements: the function ran 8 times
after ranges::to, then two passes: 4 times
```

If the function is cheap or you walk the view once, laziness is free. If you walk it more than once, or the function is expensive, finish with `ranges::to` and iterate the result. The project (15.11) shows a recipe that is walked twice on purpose, and says so.

### Dangling

A view refers to a container, and an iterator points into one. If the container is a **temporary** (a value that is destroyed at the end of the statement, like the result of a function that returns by value), an iterator into it would point to something already destroyed (14.4). C++20 catches the easy cases **at compile time**:

```cpp
std::vector<Reading> load_readings() { ... }              // returns by value

auto found{std::ranges::find_if(load_readings(), [](const Reading& r) { return r.celsius > 20.0; })};
std::println("{}", found->station);      // error: does not compile
```

The algorithm refuses to return an iterator into the temporary. It returns a special empty type, `std::ranges::dangling`, which is not an iterator, so any attempt to use the result as one fails to compile. On GCC the message is "no match for operator*", on Clang "indirection requires pointer operand". (The program keeps these two lines as comments so that it compiles: remove the `//` to see the error.) The fixes:

```cpp
auto readings{load_readings()};                              // give the container a name
auto hot{std::ranges::find_if(readings, ...)};               // fine: it outlives the iterator

double warmest{std::ranges::max(load_readings() | std::views::transform(&Reading::celsius))};   // ask for a VALUE
```

```
with a named container: south
or ask for a value: warmest is 24
```

A few ranges can be searched even as temporaries, because their iterators do not point into storage that can die. A `std::string_view` and an `iota` view are among them (the standard calls them *borrowed* ranges); a `std::vector` is not:

```cpp
*std::ranges::find(std::views::iota(1, 10), 5)       // fine: iota makes its values on the fly
```

```
find in iota(1, 10) as a temporary: 5
```

### A view over a temporary container

```cpp
load_readings() | std::views::filter([](const Reading& r) { return r.celsius > 20.0; })
                | std::views::transform(&Reading::station)
```

```
filter over a temporary: south east
```

(In the program the pipeline ends with `| std::ranges::to<std::vector>()` so that `show` can print it.)

That is fine. Since C++20 the pipeline **takes ownership** of an rvalue container (it becomes an `owning_view`), so there is nothing left dangling.

### The rules of thumb

```
   a view over a NAMED container      valid while that container lives and is not modified:
                                      push_back, erase and the like invalidate it, like iterators (14.4)
   a view over a TEMPORARY container  owns it: fine
   a view holding a reference to something LOCAL
                                      must not be returned from the function
   a const filter_view                cannot be iterated: its begin() remembers where the first match is,
                                      so it changes the view.
```

The last rule produces this error on both compilers:

```
const auto v = readings | std::views::filter(...);
for (auto& r : v) {}          // error: passing 'const filter_view' as 'this' argument discards qualifiers
```

**Code for this lecture**: `15.10RangesToAndOwnership/main.cpp`.

---

## 15.11 Project: the log pipeline

In chapter 14 the log analyzer answered every question with a hand-made loop and the right container. Same file, same questions. This time: algorithms and views only. The report must come out **identical**, and then we compare what we gained and what we paid.

### The files

```
   15.11ProjectLogPipeline/
      generate_log.cpp    the generator of 14.12 (unchanged)         target rooster_generate
      log_entry.h         LogEntry and parse_line() of 14.12 (unchanged)
      main.cpp            the analyzer, as pipelines                  target rooster
      sample.log          the first 20 lines of a generated log
      CMakeLists.txt
```

The folder is self-contained: it carries its own copies of the generator and the parser. Build and run exactly as in 14.12 (`-DCMAKE_BUILD_TYPE=Release` with MSVC and Ninja):

```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/rooster_generate         (writes access.log: the same file as in chapter 14)
./build/rooster
```

### Parsing: one pipeline

In chapter 14 a `for` loop with `find('\n')` cut the text into lines, called `parse_line`, and kept the good ones. As a pipeline:

```cpp
// split gives, for a std::string, one subrange (a pair of iterators in one
// object, 15.3) per piece between the newlines.
using Piece = std::ranges::subrange<std::string::iterator>;

auto lines{text
    | std::views::split('\n')
    | std::views::transform([](const Piece& piece) {
          std::string_view line{piece};
          if (line.ends_with('\r')) {
              line.remove_suffix(1);
          }
          return line;
      })
    | std::views::filter([](std::string_view line) { return !line.empty(); })};

using Parsed = std::optional<LogEntry>;
auto entries{lines
    | std::views::transform(parse_line)
    | std::views::filter([](const Parsed& entry) { return entry.has_value(); })
    | std::views::transform([](const Parsed& entry) { return *entry; })
    | std::ranges::to<std::vector>()};
```

The two `using` lines give names to the long types (7.10 used `using` the same way), so that the lambdas can state their parameter types plainly. Read the pipeline as a sentence: the text, cut at each newline, turned into string views (without a trailing `\r`), dropping empty ones; then each parsed, keeping the ones that parsed, unwrapping the `std::optional` (13.2), collected into a vector.

`lines` is **only a recipe**, so counting the lines afterwards (`std::ranges::distance(lines)`) walks the text a second time. That is the cost of laziness from 15.10, accepted here to keep the code in one piece.

### One function for every ranking

The three rankings of chapter 14 (top pages, top clients, heaviest pages) are the same operation with different inputs: **group by a key, add up a value for each group, largest first.**

It is a function template (6.13) with two blanks to fill, `Key` and `Value`: the types of whatever callables you pass in, a lambda or a pointer to a member (15.8).

```cpp
template <typename Key, typename Value>
Ranking ranking_by(std::vector<LogEntry> items, Key key, Value value) {
    std::ranges::sort(items, {}, key);                                        // equal keys become neighbours

    auto same_key{[&](const LogEntry& a, const LogEntry& b) { return std::invoke(key, a) == std::invoke(key, b); }};
    Ranking totals;
    for (auto group : items | std::views::chunk_by(same_key)) {
        auto values{group | std::views::transform(value)};
        totals.push_back({std::ranges::fold_left(values, std::size_t{0}, std::plus<>{}),
                          std::string_view{std::invoke(key, group.front())}});
    }
    std::ranges::sort(totals, std::ranges::greater{});
    return totals;
}
```

(`Ranking` is `std::vector<std::pair<std::size_t, std::string_view>>`, a name made with `using`.)

- `sort` with a **projection** (15.8) puts entries with the same key next to each other.
- `chunk_by` (15.9) cuts the sorted entries into one group per key; the loop visits the groups.
- For each group, `fold_left` (15.7) adds up the value of its entries, and the pair `(total, key)` is stored.
- `std::invoke` calls `key` whether it is a lambda or a member pointer such as `&LogEntry::path`.
- A final sort, descending, puts the largest first.

Then the three questions are one line each:

```cpp
ranking_by(entries, &LogEntry::path, one)                     // pages by number of requests
ranking_by(entries, &LogEntry::client, one)                   // clients by number of requests
ranking_by(entries, &LogEntry::path, &LogEntry::bytes)        // pages by bytes served
```

where `one` is a lambda that always returns 1, so the "total" is a count. Chapter 14 used the three hash tables and a heap; here the data is sorted, and the order of the sort breaks ties the same way as the heap did.

### The other questions

**Status codes**: collect the codes, sort them, and cut into runs of equal codes (`chunk_by` with `std::ranges::equal_to`):

```cpp
auto statuses{entries | std::views::transform(&LogEntry::status) | std::ranges::to<std::vector>()};
std::ranges::sort(statuses);
for (auto group : statuses | std::views::chunk_by(std::ranges::equal_to{})) {
    ... group.front() is the code, std::ranges::size(group) the count
}
```

**Requests per hour**: for each hour of `iota(0, 24)`, `count_if` over the entries. That is 24 passes over the data instead of one, but 24 passes over 100,000 entries is cheap, and the code is a single expression.

**Broken links**: keep the 404 entries, sort them by `(path, client)` with a projection that returns a pair, then `chunk_by` page, and inside each page `chunk_by` client to count the distinct clients:

```cpp
std::ranges::sort(missing, {}, [](const LogEntry& e) { return std::pair<std::string_view, std::string_view>{e.path, e.client}; });
```

The nested grouping replaces the `map` of `set`s of 14.12.

### The report is the same

Both programs on the same log (the 100,000-line one, md5 `eb37332a49c56be9df3d32909ba3f41d`), comparing every line except the last (a timing):

```
GCC 16 container      REPORTS IDENTICAL
Clang 21 container    REPORTS IDENTICAL
MSVC                  0 differing lines
```

```
access.log: 100000 lines, 99775 requests, 225 damaged lines, 3985.5 MB served

status codes
  200   86137   86.3 %
  301    2472    2.5 %
  304    6277    6.3 %
  404    3952    4.0 %
  500     937    0.9 %
...
broken links (404)
  /admin                       463 hits from 182 different clients
  ...
  /wp-login.php                691 hits from 221 different clients

whole analysis: 72.1 ms
```

(The middle is the report of 14.12, line for line.)

### What it cost, and what it bought

```
                            14.12 loops and containers     15.11 pipelines
   lines of code (no comments)        155                        120
   wall time, 100,000 lines
       GCC 16                       about 28 ms                62 to 72 ms
       Clang 21                     about 28 ms                58 to 62 ms
       MSVC, Release                about 56 ms                about 87 ms
```

- **Shorter**: about a fifth fewer lines, and the lines that remain say *what* is being asked (group, add up, rank) rather than how to loop.
- **Slower**: between 1.6 and 2.4 times, on a small program, on three compilers. The pipeline sorts where the hash tables count in one pass, copies entries for each ranking, and walks the text twice. Nothing here is a flaw of ranges: it is the price of the sort-based approach.
- **Neither is wrong**. For a one-off analysis of a log, 60 ms against 30 ms does not matter and the clearer code wins. In a loop that runs a million times, or on a log of a hundred million lines, measure (14.11) and pick the hash tables. The right habit is the one from 14.11: write the clear version, measure, and optimise what the measurement shows.

### Things to try

1. Make the rankings faster without giving up the pipeline: where does the time go? (Try `perf`, a profiler, or just time each section with `std::chrono`.) Is it the sorts?
2. Replace the full `sort` of the rankings by `partial_sort`, since only the top 5 or 3 are printed (15.6).
3. Add the busiest **minute** of the day to both programs. Which one needs more changes?
4. Print the report of a different file: `./build/rooster big.log`, generated with `rooster_generate 1000000 big.log`. How do the two programs scale?
5. Run it under AddressSanitizer (9.12): the entries hold `string_view`s into one buffer, and a pipeline that builds them from temporaries is where a mistake would show.

**Code for this project**: `15.11ProjectLogPipeline/`.

---

## 15.12 Assignment

Eight small jobs for the weather station, one idea of the chapter each. One rule for all of them: use the standard algorithms and views of this chapter, not a hand-written loop that does the same. A loop to *print* the result is fine. `main.cpp` has the eight exercises, each with its statement and a sample run in a comment, and some provided pieces: the readings table (with the broken `-99.0` reading), an `is_broken` function, and the `show` helper. You write each solution under its heading in `main()`. `main_solution.cpp` solves all eight. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | Asking questions | `any_of`, `count_if`, `find_if`, `copy_if` with `back_inserter`, `min_element` with a projection |
| 2 | Copy and transform | `copy_if` and `transform` into new vectors |
| 3 | Clean the data | `std::erase_if`, `transform` with a projection, `sort`, `unique` and `erase` |
| 4 | Order the readings | two `stable_sort` calls with projections, minor key first |
| 5 | Count in a range | `lower_bound` twice, the distance between two iterators |
| 6 | Rain | `inclusive_scan`, `max_element`, `reduce` |
| 7 | One pipeline | `filter`, `transform`, `take`, `join_with`, `ranges::to<std::string>` |
| 8 | Average per station | `ranges::to<std::set>`, a `filter` and `transform` view per station, `fold_left` |

The log pipeline project has no exercise of its own: the exercise is to run it beside the chapter 14 analyzer, compare the reports, and try the list at the end of 15.11.

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole chapter.

After this chapter the student can reach for a named algorithm instead of a loop, choose the `std::ranges::` form with a projection, remove elements with `erase_if`, sort and search sorted data in the ways that fit the question, combine values with the numeric algorithms, build lazy pipelines of views and finish them with `ranges::to`, and knows the rules that keep a view or an iterator from dangling. The next chapter turns to **templates**: the machinery these algorithms, these views and the standard containers are all written in, and how to write your own generic code.
