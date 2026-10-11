# Containers and Iterators

Almost every program is, underneath, a program about **collections**: the readings of a sensor, the stations of a network, the requests in a log file. You already own the most important tool for that: `std::vector` (7.4), and `std::array` and `std::span` next to it. This chapter opens the rest of the toolbox, and, more importantly, teaches you how to **choose**.

Choosing means knowing what is inside. A container is not a magic bag: each one is a particular arrangement of memory, and the arrangement decides what is fast, what is slow, and what quietly stops working when you change the container while someone is looking at it.

```
   vector        [ a b c d e . . ]                  one block, elements side by side
   deque         [ a b c ] [ d e f ] [ g . . ]      a table of blocks
   list          [a]⇄[b]⇄[c]⇄[d]                    a node per element, linked both ways
   map / set     a balanced tree, sorted by key
   unordered_*   a table of buckets, found by hash
```

The thread that ties them together is the **iterator**. An iterator is how you walk through any container without knowing how it is built, and it is what the standard algorithms of the next chapter are written against. So we start there, and finish by writing one ourselves.

The chapter has four parts:

1. **Iterators** (14.2), the **inside of the vector** (14.3), and what goes wrong when the container changes under an iterator (14.4).
2. **The other sequence containers**: `deque`, `list`, `forward_list` (14.5).
3. **Lookup containers**: `set` and `map` (14.6), the unordered versions (14.7), and the **adaptors** (14.8). Then two C++23 newcomers (14.9).
4. **Writing your own iterator** (14.10), a **measurement** that answers "which container?" (14.11), and a **project**: a log analyzer that chews through 100,000 lines of a web server log.

Big O (7.5) is assumed. When a lecture says "O(log n)" or "O(1) on average", it is that language.

---

## 14.2 Iterators

In this lecture we meet the idea behind `begin()` and `end()`, and the five levels of iterator that decide what a container allows.

### What an iterator is

You used one without knowing in 7.2: the range-based `for` loop. Here is the same walk written out:

```cpp
std::vector<double> readings{18.5, 19.0, 21.5, 20.0, 22.5};

for (auto it{readings.begin()}; it != readings.end(); ++it) {
    std::print("{} ", *it);
}
```

```
18.5 19 21.5 20 22.5
```

An **iterator** is an object that points at an element of a container. It behaves like a pointer (9.2):

```
   *it         the element it points at
   ++it        move to the next element
   it != end   have we run out?
```

`begin()` points at the first element. `end()` points **one past the last**. That second one is the part to remember:

```
   [ 18.5 ][ 19.0 ][ 21.5 ][ 20.0 ][ 22.5 ]   ·
     ▲                                         ▲
   begin()                                   end()   ← one PAST the last element: never dereference it
```

The range `[begin, end)` is **half open**: it includes `begin`, and stops before `end`. That shape is convenient. An empty container has `begin() == end()`, the number of elements is `end - begin`, and a function that searches returns `end()` to mean "not found":

```cpp
auto found{std::find(readings.begin(), readings.end(), 21.5)};
if (found != readings.end()) {
    std::println("found 21.5 at index {}", std::distance(readings.begin(), found));
}
```

```
found 21.5 at index 2
```

`std::distance(a, b)` says how many steps from `a` to `b`: here, the index.

> `auto it{readings.begin()};` with braces gives `it` the iterator type, not a list of one element. That is the rule for `auto` with a single braced value (4.4).

### `const` and reverse

```cpp
for (auto it{readings.cbegin()}; it != readings.cend(); ++it) {
    // *it = 0.0;           // error: a const_iterator cannot change the element
}
for (auto it{readings.rbegin()}; it != readings.rend(); ++it) {
    std::print("{} ", *it);                       // ++ on a reverse iterator moves BACKWARD
}
```

```
22.5 20 21.5 19 18.5
```

`cbegin()` and `cend()` give **const iterators**: look but do not touch, like a `const&` (6.10). `rbegin()` and `rend()` walk the container backwards, and `++` on them still means "next", which is the previous element.

### The same tools on every container

Here is a function that finds the middle of **any** range:

```cpp
template <typename Iterator>
Iterator middle(Iterator first, Iterator last) {
    Iterator it{first};
    std::advance(it, std::distance(first, last) / 2);
    return it;
}
```

```
middle of the vector: 21.5
middle of the list:   east
middle of the forward_list: 3
```

(Function templates are 6.13.) The same code works on a vector, a list and a forward list, because it only asks the iterator for what every iterator can do. `std::advance` and `std::distance` do the work in the best way each container allows.

### The five levels of iterator

What an iterator **can** do depends on the container behind it:

```
   level             adds                               examples
   ───────────────   ────────────────────────────────   ──────────────────────────────
   input / output    one pass: * and ++                 reading from a stream
   forward           many passes                        std::forward_list
   bidirectional     also --                            std::list, std::map, std::set
   random access     also it + n, it[n], it1 - it2, <   std::deque, std::vector
   contiguous        random access, elements adjacent   std::vector, std::array
```

Each level includes the ones above it. The standard names them as **concepts** (concepts are chapter 16), and we can ask the compiler about them with `static_assert`:

```cpp
static_assert(std::forward_iterator<std::forward_list<int>::iterator>);
static_assert(!std::bidirectional_iterator<std::forward_list<int>::iterator>);
static_assert(std::bidirectional_iterator<std::list<int>::iterator>);
static_assert(!std::random_access_iterator<std::list<int>::iterator>);
static_assert(std::random_access_iterator<std::vector<int>::iterator>);
static_assert(std::contiguous_iterator<std::vector<int>::iterator>);
```

All six hold, so the program compiles. What the levels mean in practice:

```cpp
auto v_it{readings.begin()};
std::println("vector:  begin() + 3 is {}", *(v_it + 3));                 // jump, cheap
auto l_it{stations.begin()};
// l_it + 3                          // error: a list iterator cannot jump
std::println("list:    std::next(begin(), 3) is {}", *std::next(l_it, 3)); // walks 3 steps
```

```
vector:  begin() + 3 is 20
list:    std::next(begin(), 3) is west
```

A vector jumps in one step. A list must follow its links one at a time, so it offers no `+`, and `std::next` is honest about the cost: it walks. This is also why `std::sort` works on a vector but not on a `std::list`: sorting needs random access. The list has its own member function, `stations.sort()`.

### The pattern to remember

> **A container hands out iterators. An algorithm takes a pair of them. Neither knows about the other.** That is why `std::find`, `std::sort` and the rest work on whatever you give them (chapter 15), and why a class of your own can join in by providing `begin()` and `end()` (14.10).

**Code for this lecture**: `14.2Iterators/main.cpp`.

---

## 14.3 Inside the vector

In this lecture we open `std::vector` and look at what it does when it grows. That explains most of its speed, and most of its surprises.

### Size and capacity

A vector owns **one block** of memory, usually bigger than it needs:

```
   size() = 3, capacity() = 5

   [ 18.5 ][ 19.0 ][ 21.5 ][  ·  ][  ·  ]
     ▲ elements that exist        ▲ room for two more
```

- **`size()`** is how many elements there are.
- **`capacity()`** is how many fit in the block the vector currently owns.

When `push_back` finds `size() == capacity()`, the vector must **allocate a bigger block, move every element across, and release the old block**. That is a **reallocation**. Let us watch:

```cpp
std::vector<int> v;
std::size_t last_capacity{v.capacity()};
for (int i{0}; i < 100; ++i) {
    v.push_back(i);
    if (v.capacity() != last_capacity) {
        std::println("size {:3}: capacity {:3} -> {:3}", v.size(), last_capacity, v.capacity());
        last_capacity = v.capacity();
    }
}
```

On GCC and Clang:

```
size   1: capacity   0 ->   1
size   2: capacity   1 ->   2
size   3: capacity   2 ->   4
size   5: capacity   4 ->   8
size   9: capacity   8 ->  16
size  17: capacity  16 ->  32
size  33: capacity  32 ->  64
size  65: capacity  64 -> 128
8 reallocations for 100 elements
```

The capacity **doubles**. On MSVC the same program grows by one and a half times and reallocates 13 times (`1, 2, 3, 4, 6, 9, 13, 19, 28, 42, 63, 94, 141`). The standard does not say how much; it only guarantees that growth is geometric, so that `push_back` is **amortized constant**: most calls are a plain write, and the rare expensive one is paid for by the many cheap ones.

### `reserve`

If you know roughly how many elements are coming, say so once:

```cpp
std::vector<int> reserved;
reserved.reserve(100);
const int* block{reserved.data()};
for (int i{0}; i < 100; ++i) {
    reserved.push_back(i);
}
```

```
size 100, capacity 100, still the same block: true
```

`reserve(n)` changes the **capacity**, never the size: no elements are created. With it there is one allocation instead of eight (or thirteen), and, as 14.4 shows, the elements do not move while you fill it.

Giving memory back:

```
after clear: size 0, capacity 100
after shrink_to_fit: capacity 0
```

`clear()` destroys the elements but **keeps the block**, ready for reuse. `shrink_to_fit()` asks for the surplus back. It is a request, not a command, but the libraries we tried honoured it.

### `push_back` versus `emplace_back`

A small type that counts what happens to it (with `noexcept` moves, 13.5) makes it visible:

```cpp
items.push_back(Counted{1});
// push_back(Counted{1}): 1 constructed, 1 moves

items.emplace_back(2);
// emplace_back(2):        1 constructed, 0 moves
```

`push_back(Counted{1})` builds a **temporary** `Counted`, then moves it into the vector. `emplace_back(2)` passes the arguments **to the constructor**, which builds the element directly in the vector's memory. For a type that is cheap to move the difference is small; for one that is expensive it adds up. Rule of thumb: `emplace_back(arguments...)` when you are constructing, `push_back(existing_object)` when you already have one.

### The price of the front

A vector keeps its elements side by side, so inserting in the middle or at the front means **shifting everything after it**:

```
emplace_back on 9 elements: 0 moves
emplace at begin() of 10 elements: 11 moves
```

At the back: nothing moves. At the front of ten elements: eleven moves, about one per element (ten shifted, plus one for the temporary). With a thousand elements it would be a thousand. That cost is the reason `deque` exists (14.5).

### What contiguous buys you

```
contiguous: &items[1] - &items[0] is 4 bytes (sizeof(Counted) is 4)
```

The elements are adjacent. That means `v.data()` can be handed to C code or to `std::span` (9.8), and walking the vector is friendly to the processor's cache, which is the main reason it beats the node-based containers in practice (14.11 measures it).

**Code for this lecture**: `14.3InsideTheVector/main.cpp`.

---

## 14.4 Iterator invalidation

In this lecture we look at the most common way iterators go wrong: the container changed, and the iterator did not notice.

### The rule

An iterator, a pointer or a reference into a container stays valid **only while the container does not rearrange its elements**. Operations that can move elements **invalidate** them. Using an invalidated iterator is **undefined behaviour**, and it rarely fails loudly.

### `push_back` can move everything

```cpp
std::vector<double> readings{18.5, 19.0, 21.5};
readings.reserve(3);                       // full: the next push_back must reallocate

const double* first{readings.data()};      // a pointer into the old block
auto it{readings.begin()};                 // an iterator into the old block

readings.push_back(20.0);                  // reallocates: it and first now dangle

std::println("the block moved: {}", first != readings.data());
// std::println("{}", *it);                // undefined behaviour: reads freed memory
it = readings.begin();                     // the fix: ask again after the change
std::println("after asking again: {}", *it);
```

```
the block moved: true
after asking again: 18.5
```

The commented line is the bug. We tried it five ways:

```
   plain build               prints garbage, e.g. 2.211e-319, and carries on
   AddressSanitizer          ERROR: AddressSanitizer: heap-use-after-free ... READ of size 8
   g++ -D_GLIBCXX_DEBUG      aborts with a message from the checked iterator
   MSVC Debug build          opens the debug dialog (a script waits for someone to click it)
```

The plain build is the dangerous one: **it looks fine**. Always ask for the iterator again after anything that might have rearranged the container, and use the sanitizers of 9.12 on code that holds iterators for a while.

### Erasing inside a loop

The tempting version:

```cpp
for (auto t{temperatures.begin()}; t != temperatures.end(); ++t) {
    if (*t < 0) temperatures.erase(t);      // t is invalid after erase, and then ++t
}
```

`erase` invalidates the iterator at and after the erased element, and then the loop increments it. The right way uses what `erase` **returns**: an iterator to the element after the one removed.

```cpp
for (auto t{temperatures.begin()}; t != temperatures.end();) {
    if (*t < 0) {
        t = temperatures.erase(t);          // use the returned iterator, do NOT advance
    } else {
        ++t;                                // advance only when nothing was erased
    }
}
```

```
12 18 21 15
```

(from `{12, -3, 18, -7, 21, -1, 15}`). Notice the loop has no increment in its header: only one of the two branches moves on. The one-line version, `std::erase_if`, is in chapter 15.

### What invalidates what

```
   container        operation                     invalidates
   ─────────────    ───────────────────────────   ────────────────────────────────────────
   vector           push_back, insert             everything if it reallocates; else from the change on
                    erase                         from the erased element on
                    reserve                       everything, if it reallocates
                    clear                         everything
   deque            insert/erase in the middle    everything
                    push_front/push_back          iterators, but not references to elements
   list, map, set   erase                         only the erased element
   unordered_*      insert that rehashes          iterators, but references to elements stay valid
```

The pattern behind the table: **the more a container moves its elements, the more it invalidates.** The vector moves a lot, so it invalidates a lot. The list and the map never move a node, so only the erased one disappears. That is the real reason to pick them sometimes (14.5, 14.6).

### A cheap safety net

The standard library can check iterators for you in a Debug build: the MSVC Debug configuration does it by default, and GCC does with `-D_GLIBCXX_DEBUG`. AddressSanitizer catches the actual read of freed memory in either. Uncomment the dereference in the program and try them.

**Code for this lecture**: `14.4IteratorInvalidation/main.cpp`.

---

## 14.5 `deque`, `list` and `forward_list`

In this lecture we meet the three sequence containers that are not the vector, and learn what each is for.

### `deque`: both ends

A **deque** ("deck", double-ended queue) keeps a table of fixed-size blocks:

```
   deque    [*]──► [ a b c ]
            [*]──► [ d e f ]
            [*]──► [ g · · ]
```

Adding at either end only touches the first or last block, so `push_front` and `push_back` are both cheap, and indexing still works (it finds the block, then the position in it).

```cpp
std::deque<std::string> jobs;
jobs.push_back("upload");
jobs.push_back("calibrate");
jobs.push_front("ALARM");                 // vector has no push_front
jobs.push_front("shutdown");
```

```
shutdown ALARM upload calibrate
jobs[2] = upload   (random access, like a vector)
after pop_front: ALARM
```

The price: the elements are not in one block, so `data()` does not exist, and walking a deque is a little slower than walking a vector. Use it when you add and remove at **both ends** (a queue of jobs where urgent ones jump the line).

### `list`: nodes that never move

A **list** allocates every element on its own, linked to the previous and the next:

```
   list     [a]⇄[b]⇄[c]⇄[d]       each box is a separate allocation
```

No random access (no `[]`, no `+`), and every element costs an allocation. In return, **a node never moves once it exists**:

```cpp
std::list<std::string> queue{"north", "east", "west"};
auto east{++queue.begin()};               // an iterator to "east"
const std::string* address{&*east};       // and a pointer to the element itself

queue.push_front("far north");
queue.insert(east, "north east");         // insert BEFORE east
queue.push_back("south");
std::println("still the same element: {} (iterator), {} (pointer)",
             *east, address == &*east);
```

```
still the same element: east (iterator), true (pointer)
```

After three insertions around it, the iterator **and** the raw pointer to `"east"` are still valid and still equal. Do the same on a vector and 14.4 tells you what could happen. Stable positions are the real reason to choose a list.

The other reason is **`splice`**: moving nodes from one list to another by relinking, with no element copied or moved:

```cpp
std::list<std::string> urgent{"fix antenna", "replace battery"};
queue.splice(queue.begin(), urgent);      // moves ALL of urgent's nodes to the front
```

```
urgent now has 0 items, queue has 8
[fix antenna] [replace battery] [far north] [north] [north east] [east] [west] [south]
```

And two member functions that exist because the generic versions would not work or would be slow:

```cpp
queue.remove("north");                    // erases every element equal to "north"
queue.sort();                             // std::sort needs random access; list has its own
```

### `forward_list`: the smallest

A **forward list** is a list with only the "next" link: one pointer less per node, and in exchange no `size()`, no `back()`, no going backwards, and insertion happens **after** a position:

```cpp
std::forward_list<int> ids{10, 20, 30};
ids.push_front(5);
ids.insert_after(ids.begin(), 7);         // 5 7 10 20 30
```

```
5 7 10 20 30
```

It is rarely the right choice, but it is the lightest possible sequence, and it is why `forward_iterator` exists as a category (14.2).

### Which one?

```
   vector       the default. Walk it, add at the back, index into it.
   deque        add and remove at BOTH ends, and still index.
   list         elements must keep their address, or you move nodes between lists.
   forward_list the same as list, with the smallest possible node.
```

If you cannot name a reason for the others, use a vector. 14.11 puts numbers on it.

**Code for this lecture**: `14.5DequeListForwardList/main.cpp`.

---

## 14.6 `set` and `map`

In this lecture we meet the **ordered associative containers**: collections that find an element by what it **is** (its key), not by where it sits.

### What a map is

A `std::map` holds **key → value** pairs. Keys are unique, and they are kept **sorted**, in a balanced tree. Find, insert and erase cost O(log n), and a loop over the map visits the elements in key order.

```cpp
std::map<std::string, double> latest;
latest["north"] = 18.5;                   // operator[] creates the entry if needed
latest["south"] = 24.0;
latest.insert({"east", 21.5});            // insert does NOT replace an existing key
latest.insert({"east", 99.0});            // ignored: east is already there
latest.insert_or_assign("south", 25.5);   // this one replaces
latest.emplace("west", 16.0);
```

Iterating gives pairs in key order. A structured binding (10.11) names the two halves:

```cpp
for (const auto& [station, temperature] : latest) {
    std::println("{:<6} {:5.1f}", station, temperature);
}
```

```
east    21.5
north   18.5
south   25.5
west    16.0
```

Not the order of insertion: the order of the keys.

### The trap of `operator[]`

```cpp
std::println("size before: {}", latest.size());
if (latest["centre"] > 20.0) {            // looks like a question, is an insert
    std::println("warm");
}
std::println("size after asking about 'centre': {}", latest.size());
```

```
size before: 4
size after asking about 'centre': 5
```

**Reading a missing key with `[]` creates it** (with a default value, 0 here). `[]` is right when you mean "give me this entry, make it if it is not there", and wrong for a question. The ways to ask without changing anything:

```cpp
if (auto it{latest.find("east")}; it != latest.end()) {
    std::println("find: east is {}", it->second);   // it->first is the key, it->second the value
}
std::println("contains(\"moon\"): {}", latest.contains("moon"));   // C++20
```

```
find: east is 21.5
contains("moon"): false
```

and `at("moon")`, which **throws** `std::out_of_range` (13.4) when the key is missing. A map's iterator points to a `std::pair<const Key, Value>`: the key is `const` because changing it would break the sorting.

### The classic use: counting

```cpp
std::map<std::string, int> readings_per_station;
for (const auto& station : log) {
    ++readings_per_station[station];      // a missing key starts at 0, which is what we want
}
```

```
east   2
north  3
west   1
```

Here the `[]` behaviour is exactly right: a new key appears with 0, and `++` makes it 1. This three-line pattern will carry the whole project at the end of the chapter.

### Ordered means ranges are cheap

```cpp
auto from{latest.lower_bound("d")};       // first key not less than "d"
auto to{latest.upper_bound("o")};         // first key greater than "o"
for (auto it{from}; it != to; ++it) {
    std::print("{} ", it->first);
}
```

```
east north   (keys from d to o)
```

`lower_bound` and `upper_bound` find the edges in O(log n), and everything between is a walk. A hash table cannot do this.

### `set`: just the keys

```cpp
std::set<int> hours{14, 9, 14, 3, 9, 22};
```

```
3 9 14 22   (4 distinct)
insert(9): new? false, already at 9
descending: 22 14 9 3
```

Duplicates disappear, the rest comes out sorted, and `insert` returns a pair: an iterator to the element, and a `bool` that says whether it was new. The third line used a different ordering, `std::set<int, std::greater<>>`: the comparison is a template argument.

### `multimap` and `multiset`

If one key may appear several times:

```cpp
std::multimap<std::string, double> by_station;
by_station.emplace("north", 18.5);
by_station.emplace("north", 19.0);
by_station.emplace("south", 24.0);
by_station.emplace("north", 17.5);
auto [first, last]{by_station.equal_range("north")};
```

```
north: 18.5 19 17.5   (3 readings)
```

`equal_range` returns the pair of iterators that bracket all the elements with that key.

### What to remember

```
   std::map / std::set     sorted by key, O(log n), stable iterators, range queries
   operator[]              creates the key if missing: for counting, not for asking
   find, contains, at      ask without changing (at throws)
   the key is const        it decides the position in the tree
```

**Code for this lecture**: `14.6SetAndMap/main.cpp`.

---

## 14.7 Unordered containers and hashing

In this lecture we meet the container that finds things **fastest** when you only have one question: *is this exact key here?*

### How a hash table works

```
   hash("north") % buckets ──► bucket 3 ──► [north: 18.5]
   hash("south") % buckets ──► bucket 0 ──► [south: 24.0] ─► [west: 16.0]   (a collision)
   hash("east")  % buckets ──► bucket 5 ──► [east: 21.5]
```

The key is turned into a number (its **hash**). The number picks a **bucket**. The element lives in that bucket, and when two keys land in the same one (a **collision**) they share it. Find, insert and erase are O(1) **on average**, whatever the size.

The interface is that of the map, so what you learned in 14.6 carries over:

```cpp
std::unordered_map<std::string, double> latest;
latest["north"] = 18.5;
latest.emplace("east", 21.5);
latest.insert_or_assign("west", 16.0);
```

```
north: 18.5   contains(moon): false   size: 4
```

### The order is unspecified

```
GCC:   west=16 east=21.5 south=24 north=18.5
MSVC:  east=21.5 north=18.5 south=24 west=16
```

Same program, same data, different order. The order is whatever the buckets hold, and it can change between compilers, between versions of one library, and **after the next insertion**. Never depend on it. If you need an order, use `std::map`, or copy to a vector and sort.

### Buckets, load factor, rehash

```cpp
std::unordered_map<int, int> numbers;
for (int i{0}; i < 1'000; ++i) {
    numbers[i] = i;
}
```

```
GCC:   1000 elements in 1109 buckets, load factor 0.90, max 1.00, 7 rehashes on the way
MSVC:  1000 elements in 1024 buckets, load factor 0.98, max 1.00, 3 rehashes on the way
```

The **load factor** is elements per bucket. When it passes the maximum (1.0), the table grows and **rehashes**: every element is placed again. That costs time, and it invalidates the iterators (14.4), though references to the elements stay valid. Like `vector::reserve`, `reserve(n)` sizes the table up front and avoids the rehashes. The numbers above differ per library, which is the point of not depending on them.

### A key of your own

For a built-in or standard key, a hash already exists. For your own type you provide two things: the **hash**, and `operator==` to tell apart different keys in the same bucket.

```cpp
struct GridCell {
    int row;
    int column;
    bool operator==(const GridCell&) const = default;
};

template <>
struct std::hash<GridCell> {
    std::size_t operator()(const GridCell& cell) const noexcept {
        return std::hash<int>{}(cell.row) * 31 + std::hash<int>{}(cell.column);
    }
};
```

```cpp
std::unordered_set<GridCell> visited;
visited.insert({1, 2});
visited.insert({2, 1});
visited.insert({1, 2});                                // already there
```

```
2 distinct cells; (2,1) visited: true; (3,3) visited: false
```

The multiplication by 31 matters. If the hash were `row + column`, then `(1, 2)` and `(2, 1)` would always collide. A good hash spreads different keys across the buckets; a bad one that puts everything in one bucket makes the "O(1)" table as slow as a list.

### `map` or `unordered_map`?

```
   need sorted iteration, range queries, or a key with only operator<     map
   only lookups by exact key, many elements, speed matters                unordered_map
   a bad hash (everything in one bucket)                                  unordered_map degrades to O(n)
```

14.11 measures both.

**Code for this lecture**: `14.7UnorderedContainers/main.cpp`.

---

## 14.8 Container adaptors

In this lecture we meet `stack`, `queue` and `priority_queue`. They are not containers of their own: they are **adaptors**, a small interface on top of a real container.

### The idea

An adaptor deliberately offers **less**. No iterators, no `begin()`, no indexing. You touch the ends, and to see everything you take elements out. The narrow interface is the point: a `stack` is last in, first out, and nothing else can happen to it.

### `stack`: last in, first out

```cpp
std::stack<std::string> undo;
undo.push("set interval 30");
undo.push("calibrate north");
undo.push("reboot");
while (!undo.empty()) {
    std::println("undoing: {}", undo.top());
    undo.pop();                              // pop returns nothing: read top() first
}
```

```
size 3, top is 'reboot'
undoing: reboot
undoing: calibrate north
undoing: set interval 30
```

`push` adds, `top` reads the newest, `pop` removes it and **returns nothing**. Read first, then pop. A stack is how an undo list works, and how a program's own calls work (6.15).

### `queue`: first in, first out

```cpp
std::queue<std::string> uploads;
uploads.push("north.dat");
uploads.push("south.dat");
uploads.push("east.dat");
```

```
front 'north.dat', back 'east.dat'
sending north.dat
sending south.dat
sending east.dat
```

`push` at the back, `front` and `pop` at the front. A line at a shop.

Both adaptors sit on a `std::deque` by default. A different underlying container is the **second template argument**, as long as it offers the operations the adaptor needs: `std::stack<int, std::vector<int>>` is a stack in a vector.

### `priority_queue`: the largest comes first

A priority queue always has its **largest** element at the top, whatever order they arrived in. Inside is a **binary heap** stored in a vector: `push` and `pop` cost O(log n), `top` costs O(1).

```cpp
std::priority_queue<int> largest_first;
for (int v : {5, 1, 8, 3}) {
    largest_first.push(v);
}
```

```
popping: 8 5 3 1
smallest first, top is 1
```

The second line used `std::priority_queue<int, std::vector<int>, std::greater<>>`, a queue with the **smallest** on top (the third argument is the container, the fourth is the comparison). By default it compares with `std::less`, which puts the largest on top.

### The pair trick

Pairs compare field by field, so a pair of `(count, name)` sorts by count first. That makes a ranking trivial:

```cpp
std::map<std::string, int> counts{{"north", 40}, {"south", 12}, {"east", 31}, {"west", 7}, {"centre", 25}};
std::priority_queue<std::pair<int, std::string>> ranking;
for (const auto& [station, count] : counts) {
    ranking.push({count, station});
}
for (int place{1}; place <= 3; ++place) {
    std::println("{}. {} ({})", place, ranking.top().second, ranking.top().first);
    ranking.pop();
}
```

```
1. north (40)
2. east (31)
3. centre (25)
```

### A comparison of your own

For a type of your own, give the queue a comparison. It answers "does `a` come **after** `b`?", so `a.severity < b.severity` puts the less severe alarm lower:

```cpp
auto less_severe{[](const Alarm& a, const Alarm& b) { return a.severity < b.severity; }};
std::priority_queue<Alarm, std::vector<Alarm>, decltype(less_severe)> alarms{less_severe};
```

`decltype(x)` means "the type of `x`": a lambda has a type with no name we can write, so this is how to name it (and the lambda is also passed to the constructor).

```
[5] sensor offline
[4] storm warning
[2] low battery
[1] clock drift
```

### Keeping the best three of a stream

You do not need to sort a million readings to find the three highest. Keep a **smallest-first** queue of size 3: every new reading goes in, and when there are four the smallest is dropped.

```cpp
std::priority_queue<int, std::vector<int>, std::greater<>> best_three;
for (int reading : {17, 29, 4, 31, 22, 8, 35, 19}) {
    best_three.push(reading);
    if (best_three.size() > 3) {
        best_three.pop();                    // drop the smallest of the four
    }
}
```

```
best three: 29 31 35 (smallest first)
```

The cost is O(M log 3) for M readings instead of O(M log M) for a full sort, and the memory is three numbers. The log analyzer uses exactly this to rank pages.

**Code for this lecture**: `14.8ContainerAdaptors/main.cpp`.

---

## 14.9 `flat_map` and `mdspan` (C++23)

In this lecture we meet two newcomers: a map that is built like a vector, and a view that gives a flat array rows and columns.

### Which compilers have them

`<flat_map>`, `<flat_set>` and `<mdspan>` need **GCC 15 or later** (the course image has GCC 16), a current **MSVC**, or **Clang with libc++**. Clang that uses the GNU library `libstdc++` 14, as the course Clang image does by default, has neither header: compile with `clang++ -stdlib=libc++` (it works in the image). On Qt Creator with an older compiler, skip this lecture or use Compiler Explorer.

### `std::flat_map`

Same interface as `std::map`, a different layout. Instead of a tree of nodes, **two sorted vectors**:

```
   std::map       node ─► node ─► node        pointers everywhere, one allocation per element
   std::flat_map  keys   [east north south]   contiguous
                  values [21.5 18.5  24.0 ]   contiguous
```

```cpp
std::flat_map<std::string, double> latest{
    {"south", 24.0}, {"north", 18.5}, {"east", 21.5}};      // sorted for you
latest["west"] = 16.0;
latest.insert_or_assign("north", 19.0);
```

```
east    21.5
north   19.0
south   24.0
west    16.0
contains(east): true   at(south): 24
keys() is a plain vector with 4 elements
first temperature in key order: 21.5
```

Lookup is a binary search in a vector, which is friendly to the cache, and walking it is as quick as walking a vector. The price is the vector's: inserting in the middle **shifts elements**, and the iterators and references are invalidated like a vector's (14.4), not like a map's. So: good for tables that are **built once and read many times**; poor for a collection with constant insertions and deletions.

`keys()` and `values()` give you the two vectors, which is the whole point of the design.

### `std::mdspan`

`std::mdspan` is to a matrix what `std::span` (9.8) is to an array: a **non-owning view**. You have a flat vector, you want to read it as rows and columns, and you do not want to copy.

```cpp
std::vector<double> data{
    18.5, 19.0, 21.5, 20.0,       // north: 4 readings
    24.0, 25.5, 26.0, 23.5,       // south
    16.0, 15.5, 17.0, 16.5};      // west
std::mdspan grid{data.data(), 3, 4};                         // 3 rows, 4 columns

for (std::size_t row{0}; row < grid.extent(0); ++row) {
    for (std::size_t column{0}; column < grid.extent(1); ++column) {
        std::print("{:5.1f} ", grid[row, column]);        // the C++23 multi-index (12.6)
    }
    std::println();
}
```

```
rank 2, rows 3, columns 4, size 12
 18.5  19.0  21.5  20.0
 24.0  25.5  26.0  23.5
 16.0  15.5  17.0  16.5
```

It indexes with `grid[row, column]`, the multi-argument `operator[]` of 12.6. It is a **view**: writing through it changes the vector.

```cpp
grid[1, 2] = 99.0;
std::println("data[6] is now {}", data[6]);
```

```
data[6] is now 99
```

### Layout

The **layout** says how `(row, column)` maps to a position in the flat data. The default, `layout_right`, is row after row, as C++ arrays do. `layout_left` is column after column, as Fortran and many maths libraries do. The same data, read the other way:

```cpp
std::mdspan<double, std::dextents<std::size_t, 2>, std::layout_left> by_column{data.data(), 3, 4};
```

```
the same data, read by column: [0,1] is 20 (default layout: 19)
```

### Sizes in the type

Sizes known at compile time can be part of the type, so the view stores nothing for them:

```cpp
std::mdspan<double, std::extents<std::size_t, 3, 4>> fixed{data.data()};
```

```
fixed extents, sizeof the view: 8 bytes (dynamic: 24)
```

The `Matrix` of chapter 12 owns its cells in one vector with `row * columns + column`, which is exactly the arithmetic of `layout_right`. An `mdspan` is how you would let other code see such a vector as a grid.

**Code for this lecture**: `14.9FlatMapAndMdspan/main.cpp`.

---

## 14.10 Writing your own iterator

In this lecture we give a container of our own an iterator, so that range-based `for` and the standard algorithms work on it.

### The container

A **ring** of the most recent readings (the idea of the ring buffer in the 9.12 project): fixed room for `Capacity` values, and when full, a new reading overwrites the oldest.

```
   storage    [ 23.5 ][ 19.0 ][ 21.5 ][ 22.0 ]       circular, after the fifth reading wrapped
                         ▲ start_ = 1: the oldest reading
   what a user should see     19.0  21.5  22.0  23.5     oldest to newest
```

The storage is circular but we want the user to see **oldest to newest**. That job belongs to the iterator.

### What a forward iterator needs

```cpp
class const_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = double;
    using difference_type = std::ptrdiff_t;
    using pointer = const double*;
    using reference = const double&;

    const_iterator() = default;                    // a forward iterator must be default constructible
    const_iterator(const RecentReadings* ring, std::size_t position)
        : ring_{ring}, position_{position} {}

    reference operator*() const {
        return ring_->slots_[(ring_->start_ + position_) % Capacity];
    }
    pointer operator->() const { return &**this; }

    const_iterator& operator++() {                 // prefix
        ++position_;
        return *this;
    }
    const_iterator operator++(int) {               // postfix: copy, then advance (12.3)
        const_iterator before{*this};
        ++position_;
        return before;
    }

    friend bool operator==(const const_iterator&, const const_iterator&) = default;

private:
    const RecentReadings* ring_{nullptr};
    std::size_t position_{0};
};
```

- The **five type names** are what the standard algorithms look for to learn what the iterator is.
- The iterator keeps the ring and a **logical position** (0 is the oldest) and turns it into the circular slot in `operator*`. That is the whole trick.
- Prefix and postfix `++` are the pair from 12.3. `==` is defaulted (12.5).
- The container supplies `begin()` (position 0) and `end()` (position `size_`).

The compiler can check that we built what we meant:

```cpp
static_assert(std::forward_iterator<RecentReadings<4>::const_iterator>);
```

If we forgot the default constructor, or the postfix `++`, this line would fail to compile and name the missing piece.

### Using it

Five readings into a ring of four:

```cpp
RecentReadings<4> recent;
for (double reading : {18.5, 19.0, 21.5}) {
    recent.add(reading);
}
for (double value : recent) {
    std::print("{} ", value);
}
```

```
18.5 19 21.5
```

then two more than there is room for:

```
19 21.5 22 23.5
```

The ring has wrapped, the oldest two are gone, and the loop still reads oldest to newest. And because it is a proper iterator pair, the algorithms accept it with no extra work:

```cpp
std::accumulate(recent.begin(), recent.end(), 0.0)                     // 86
*std::max_element(recent.begin(), recent.end())                        // 23.5
std::count_if(recent.begin(), recent.end(), [](double v) { return v > 21.0; })   // 3
std::distance(recent.begin(), std::find(recent.begin(), recent.end(), 22.0))     // position 2
```

### What we left out

A **random access** iterator also needs `+`, `-`, `[]`, `<` and more. Each one is a few lines, and the effort is rarely worth it; a forward iterator is the usual place to stop. (`RecentReadings` is also a class template, since the capacity is a template argument: templates are chapter 16.)

**Code for this lecture**: `14.10WritingYourOwnIterator/main.cpp`.

---

## 14.11 Choosing a container

In this lecture we stop describing and **measure**. "Which container?" is best answered on your own data, and this program shows how.

### The experiment

100,000 keys (even numbers, shuffled), then 200,000 lookups of random numbers: about half find something, half do not. The same question is asked of six structures, and the program prints the time to build each and the time per lookup. The random numbers come from a `std::mt19937` with a fixed seed, so the data is identical every run.

> **Build with optimization.** The timings of a Debug build say nothing. Use `cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release`. (The `CMakeLists.txt` of this folder defaults to Release when no type is given, but **CMake with MSVC and Ninja chooses Debug on its own** on the first configure, so pass the option explicitly there.)

```cpp
template <typename Work>
double milliseconds(Work&& work) {
    auto start{Clock::now()};
    work();
    return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}
```

### The result

On GCC 16 with `-O2` (nanoseconds per lookup):

```
100000 keys, 200000 queries (the vector scan: 500)

vector, linear find    build     0.10 ms    16494.4 ns per lookup   (252 hits)
sorted vector          build     4.76 ms       67.6 ns per lookup   (100104 hits)
std::set               build    15.10 ms      144.6 ns per lookup   (100104 hits)
std::map               build    17.87 ms      162.3 ns per lookup   (100104 hits)
std::unordered_set     build     6.76 ms       12.9 ns per lookup   (100104 hits)
unordered_set+reserve  build     1.70 ms       13.2 ns per lookup   (100104 hits)
```

On MSVC, Release:

```
vector, linear find    build     0.08 ms     3113.8 ns per lookup   (252 hits)
sorted vector          build     5.24 ms       73.0 ns per lookup   (100104 hits)
std::set               build    17.92 ms      153.9 ns per lookup   (100104 hits)
std::map               build    19.51 ms      151.4 ns per lookup   (100104 hits)
std::unordered_set     build     6.44 ms       14.1 ns per lookup   (100104 hits)
unordered_set+reserve  build     5.07 ms       15.0 ns per lookup   (100104 hits)
```

Clang gives the same picture as GCC. The absolute numbers belong to this machine and these compilers; look at the **shape**.

### Reading the table

- **The linear scan** is thousands to tens of thousands of nanoseconds per lookup, because it walks tens of thousands of elements each time. (It got only 500 queries to stay quick; the hits column is therefore smaller.) That is O(n), the first row of the Big O table in 7.5. MSVC's `find` was much faster than GCC's here, but still about 40 times slower than a binary search.
- **A sorted vector** with binary search is O(log n) and, because the elements are adjacent, it is faster than the tree-based containers by a factor of two or more. Building it costs a sort.
- **`std::set` and `std::map`** are O(log n) too, but each step of the search is a pointer to a node somewhere else in memory. That costs cache misses, not comparisons.
- **`std::unordered_set`** is O(1) on average: a hash, a bucket, a short chain. The fastest lookup by roughly a factor of ten over the tree.
- **`reserve`** shaved the build on GCC (6.8 to 1.7 ms) and barely on MSVC (6.4 to 5.1 ms): it is a tool, not magic, and its benefit depends on the library.

The hits column is a check: all structures that searched the same 200,000 queries report the same 100,104 hits.

### A guide

```
   a sequence you walk through, add to at the back          vector (the default)
   adds and removes at both ends                            deque
   stable positions, splicing, insert in the middle         list (rarely)
   find by key, in order, ranges of keys                    map / set
   find by exact key, no order                              unordered_map / unordered_set
   built once, searched many times                          sorted vector (or flat_map)
   largest or smallest first                                priority_queue
```

And the rule behind it: **start with `std::vector`; change when you can say why, and measure before you do.** Whenever the iteration order or the number of elements is small, any container works and clarity wins.

**Code for this lecture**: `14.11ChoosingAContainer/main.cpp`.

---

## 14.12 Project: the log analyzer

A web server writes one line to a file for every request it serves. A busy server writes millions a day, and the file is the only record of what happened: which pages are popular, who is hammering the server, which links are broken, when is the quiet time to restart it. Reading such a file and answering those questions is **exactly** a job for the containers of this chapter.

Here is a line:

```
203.0.113.1 - - [01/Mar/2026:00:02:18 +0000] "GET /blog/2026/02/update HTTP/1.1" 200 18072
```

```
   203.0.113.1                 who asked (the client address)
   [01/Mar/2026:00:02:18 +0000]  when
   "GET /blog/... HTTP/1.1"    what: the method and the page
   200                         how the server answered (200 ok, 404 not found, 500 error ...)
   18072                       bytes sent back
```

This is the common format real servers use. We do not have a real log, so the project begins with a tool that **invents one**.

### The files

```
   14.12ProjectLogAnalyzer/
      generate_log.cpp    writes a made-up log                      target rooster_generate
      log_entry.h         LogEntry and parse_line()                 used by the analyzer
      main.cpp            reads the log and reports                 target rooster
      sample.log          the first 20 lines of a generated log, to look at
      CMakeLists.txt
```

(Why a C++ program and not a script? It runs the same on Windows and Linux with nothing to install, and the generated file is **identical** on every compiler: we checked it, the 100,000-line log has the same checksum, `eb37332a49c56be9df3d32909ba3f41d`, from MSVC, GCC and Clang. Everyone sees the same numbers in the report.)

### Step 1: generate a log

```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/rooster_generate                (build\rooster_generate.exe on Windows)
```

```
wrote 100000 lines to access.log
```

`rooster_generate [lines] [file]` takes optional arguments. The data is invented, but not uniform: a few pages, clients and hours are far busier than the rest, as in a real log, and about one line in 500 is damaged, because real logs have those too. Two details in the generator are worth a look:

- It uses a fixed seed (`std::mt19937 engine{2026}`) and plain arithmetic instead of `std::uniform_int_distribution`, because the standard fixes the engine's sequence but **not** the distributions: another library would produce another file.
- It writes in **binary mode**. On Windows, text mode turns every `\n` into `\r\n`, and the file would no longer be identical everywhere. (The analyzer also copes with `\r\n`, as a log that has travelled through Windows may have it.)

### Step 2: parse a line

Each line becomes a `LogEntry`:

```cpp
struct LogEntry {
    std::string_view client;
    std::string_view method;
    std::string_view path;
    int hour;
    int status;
    std::size_t bytes;
};
```

The text fields are `std::string_view`s (7.9) that point **into the buffer the whole file was read into**. No field of any line is ever copied, which makes parsing fast. The price: the buffer must outlive every entry, and `main` keeps it alive for the whole run. (Quiz question 20.)

`parse_line` returns a `std::optional<LogEntry>` (13.2): a damaged line is a **normal outcome** of reading real logs, not an exception.

```cpp
inline std::optional<LogEntry> parse_line(std::string_view line) {
    LogEntry entry{};
    auto space{line.find(' ')};
    auto open_bracket{line.find('[')};
    auto close_bracket{line.find(']')};
    if (space == std::string_view::npos || open_bracket == std::string_view::npos ||
        close_bracket == std::string_view::npos || close_bracket < open_bracket + 15) {
        return std::nullopt;
    }
    entry.client = line.substr(0, space);
    ...
    return entry;
}
```

It cuts the line apart with `find` and `substr` (7.9), and reads the numbers with `std::from_chars`, which reports failure with a code and never throws. Nothing here is a regular expression (7.11): for a format this regular, `find` and `substr` are enough, and they allocate nothing.

### Step 3: read, parse, and the first answers

`main` reads the file into one string, then walks it line by line, collecting the good entries in a `std::vector<LogEntry>` and counting the bad ones. The vector is the right container: we append, then walk it several times.

```
access.log: 100000 lines, 99775 requests, 225 damaged lines, 3985.5 MB served
```

### Step 4: one question, one container

Each question below picks the container that fits it. The reason is the chapter.

**How many requests per status code, in order?** A `std::map<int, std::size_t>`: counting (14.6), and the keys come out sorted.

```cpp
std::map<int, std::size_t> by_status;
for (const auto& entry : entries) {
    ++by_status[entry.status];
}
```

```
status codes
  200   86137   86.3 %
  301    2472    2.5 %
  304    6277    6.3 %
  404    3952    4.0 %
  500     937    0.9 %
```

**How busy is each hour?** The hours are exactly 0 to 23, so a plain `std::array<std::size_t, 24>`: the key *is* the index, and no map can beat that.

```
requests per hour (each # is about 201 requests)
  00h   322 #
  01h  1113 #####
  ...
  11h  7959 #######################################
  12h  8010 #######################################
  13h  7324 ####################################
  ...
  23h   341 #
```

(The generator makes the middle of the day busy; the whole table is in your terminal.) The quiet hours, 00h to 02h and 22h to 23h, are the time to restart the server.

**What are the top 5 pages, and who are the top clients?** Counting by name in a `std::unordered_map<std::string_view, std::size_t>` (14.7): we only ask exact questions, no order needed, and there are many requests. Then a function takes the top N out of any such table with the **small heap** of 14.8:

```cpp
template <typename Counts>
std::vector<std::pair<std::size_t, std::string_view>> top_n(const Counts& counts, std::size_t n) {
    using Entry = std::pair<std::size_t, std::string_view>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<>> heap;
    for (const auto& [name, count] : counts) {
        heap.push({count, name});
        if (heap.size() > n) {
            heap.pop();
        }
    }
    std::vector<Entry> result;
    while (!heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }
    std::ranges::reverse(result);
    return result;
}
```

It never sorts the whole table; it keeps the best N seen so far. It works for a `std::map` too (they are both "name to number"), which is why it is a template (6.13).

```
top 5 pages
   19664  /
    8081  /index.html
    6103  /products
    5099  /products/widget
    4629  /products/gadget

top 5 clients (of 300 different clients)
   15089  203.0.113.1
    3993  198.51.100.1
    2739  192.0.2.1
    2114  203.0.113.2
    1740  198.51.100.2

heaviest 3 pages by bytes served
   2366.5 MB  /downloads/manual.pdf
    286.1 MB  /
    239.9 MB  /static/logo.png
```

Look at the last block: the most popular page is not the one that costs the most. A rarely requested 1 MB PDF outweighs the home page. The same `top_n`, fed a table of **bytes** instead of **hits**, answers a different question.

**Which links are broken, and who follows them?** A **map of sets**: for each missing page (the map, sorted by page), the set of distinct clients that asked for it.

```cpp
std::map<std::string_view, std::unordered_set<std::string_view>> clients_per_missing;
for (const auto& entry : entries) {
    if (entry.status == 404) {
        clients_per_missing[entry.path].insert(entry.client);
    }
}
```

```
broken links (404)
  /admin                       463 hits from 182 different clients
  /favicon.old.ico             426 hits from 178 different clients
  /old-page                   1819 hits from 285 different clients
  /products/discontinued       553 hits from 195 different clients
  /wp-login.php                691 hits from 221 different clients
```

`/old-page` is the one to fix first: 1,819 requests from 285 different people, so it is a link still printed or bookmarked somewhere. `/wp-login.php` and `/admin` from 200 clients are probes by scanners, not by visitors: a different problem, found by the same table.

### Step 5: does the container choice matter?

The last block counts the pages twice, once in a `std::map` and once in a `std::unordered_map`, and times both:

```
counting 99775 pages: std::map 3.15 ms, std::unordered_map 2.26 ms (same result: true)
```

(GCC 16, Release. MSVC Release printed 4.26 and 2.15 ms.) With 24 distinct pages the difference is small, because the tree is small too: 14.11 showed the gap opening up with 100,000 distinct keys. A good habit: when you are not sure, put both in and look.

### Things to try

1. Generate a bigger log: `rooster_generate 1000000 big.log` and run `rooster big.log`. What grows, and what does not?
2. Add a report of requests per **method** (GET, POST, HEAD). Which container?
3. Find the busiest **minute**. (Hint: you need the minute in `LogEntry`, and a `std::map` or a plain array of 1,440.)
4. Print the 3 clients that caused the most **404** responses.
5. Replace `std::map<int, std::size_t>` by `std::unordered_map` for the status codes, and print them again. What changed in the output, and why?
6. Run the analyzer under AddressSanitizer (9.12). We did, and it was clean: break the program on purpose by freeing the buffer early, and watch the sanitizer catch the views.

**Code for this project**: `14.12ProjectLogAnalyzer/` (`generate_log.cpp`, `log_entry.h`, `main.cpp`, `sample.log`, `CMakeLists.txt`).

---

## 14.13 Assignment

Eight small jobs for the weather station, one container idea each. `main.cpp` has the eight exercises, each with its statement and a sample run in a comment. You write each function or class above `main()` and the lines that use it in `main()` under its heading. `main_solution.cpp` solves all eight. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | Iterators by hand | `begin()`, `end()`, `rbegin()`, `rend()`, `std::distance`, no range-for and no algorithm |
| 2 | `count_reallocations` | `reserve`, `capacity()`, counting the changes |
| 3 | Erase while iterating | `it = v.erase(it)`, advancing only when nothing was erased, two negatives in a row |
| 4 | List and splice | `std::list::splice`, an iterator that stays valid |
| 5 | Counting words | `std::map<std::string, int>`, `operator[]` counting, an `istringstream`, alphabetical ties |
| 6 | A hash for `Coordinate` | `std::hash` specialization, `operator==`, `unordered_set::insert(...).second` |
| 7 | Priority queue | a `Task` with a comparison of your own, `decltype` of a lambda, ties by name |
| 8 | `Strided` | a forward iterator written from the pattern of 14.10, `std::accumulate` on it |

Exercise 8 asks a question to answer in your own words: where does `end()` point for ten elements and a stride of three? (Answer: at position 4 of the view, ten divided by three rounded up. That would be index 12 of the vector, which does not exist, and that is fine: `end()` is never dereferenced.)

The log analyzer project has no exercise of its own: the exercise is to run it, change it (the list "Things to try" at the end of 14.12), and compare the three environments if you have them.

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole chapter.

After this chapter the student can walk any container with iterators and knows what each iterator category allows, understands size, capacity and reallocation, spots and avoids invalidated iterators, picks between `vector`, `deque`, `list`, `map`, `unordered_map` and the adaptors for a reason, can give a type of their own a hash or an iterator, and has used all of it on a real-sized file. The next chapter is about **what you do with these containers**: the standard **algorithms** and **ranges**, where `std::sort`, `std::find`, `std::transform` and `erase_if` take the iterator pairs of this chapter, and where the log analyzer comes back as a pipeline.
