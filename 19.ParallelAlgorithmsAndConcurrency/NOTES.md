# Parallel Algorithms and Concurrency

Every program in this course so far has used **one core**. Your computer has many: the machine these notes were written on has 12 cores and 20 hardware threads, and a program that uses one of them leaves the rest idle. This chapter is about using the others, and about what it costs.

There are two reasons to do more than one thing at a time, and they are different:

- **Speed** (parallelism): the same work, split over several cores, finishes sooner. A picture of the Mandelbrot set, a sort of ten million numbers, a sum.
- **Responsiveness** (concurrency): several activities make progress "together" while some of them wait. A logger that writes in the background, a server that handles many clients.

The tools for both are the same, and so is the danger: **threads share memory**. In chapter 18 a coroutine could be paused only at a `co_await` that you wrote. A thread can be paused between any two instructions, and another thread can run in its place and change what the first one was about to read. Everything in this chapter, from mutexes to atomics, exists to manage that one fact.

The chapter climbs a ladder, from the easiest tool with the least control to the most control with the most danger:

```
   easiest, least control                                       most control, most danger

   parallel         async and         thread           threads, mutex, atomic,
   algorithms  -->  futures      -->  pool        -->  condition variable
   (19.2)           (19.8)            (19.10)          (19.3 to 19.7)
```

**Always start at the left.** If a parallel algorithm does the job, use it. Reach for the right side when the problem does not fit.

The lectures:

1. **Parallel algorithms** (19.2): one new argument, and your loop uses every core.
2. **Threads and `std::jthread`** (19.3): starting threads, getting results back, asking them to stop.
3. **Data races** (19.4): what goes wrong when threads share, in numbers.
4. **Mutexes and deadlock** (19.5): letting one thread at a time in, and the bug that comes with it.
5. **Atomics** (19.6): a cheaper tool for one shared variable.
6. **Condition variables** (19.7): waiting for something without wasting a core.
7. **`async` and futures** (19.8): getting a result back, or an exception.
8. **Latch, barrier, semaphore** (19.9): three small C++20 tools for common situations.
9. **A thread pool** (19.10): a fixed team of workers and a queue of jobs.
10. **A logger** (19.11): a background thread that writes for everybody else.
11. **Finding races with ThreadSanitizer** (19.12): letting a tool find the bugs of 19.4 and 19.5.
12. A **project** (19.13): the Mandelbrot set drawn onto the `Canvas` of chapter 10, four ways, with the speedups measured.

The running example is the weather network again: stations that report readings, counters, logs and a picture.

## What works where

Everything was built and run on MSVC 19.51, GCC 16.2 and Clang 21.1 (with libstdc++, as in the Linux images), and the lectures also on MinGW GCC 14.2. The programs print identical output, apart from the lines that are marked `[varies]` (timings and the size of your machine).

| | MSVC | GCC 16 | Clang 21 | MinGW GCC 14.2 |
|---|---|---|---|---|
| `std::thread`, `jthread`, mutex, atomic, condition variable, `async`, latch, barrier, semaphore | works | works | works | works |
| `std::execution::par` (19.2) | works, its own thread pool | **needs oneTBB** | **needs oneTBB** | compiles, **runs on one thread** |
| ThreadSanitizer (19.12) | **does not exist** | works (Linux) | works (Linux) | does not exist |
| `std::move_only_function` (19.10) | works | works | works | works |

Three notes. **oneTBB** is a library from Intel. GCC's and Clang's standard library use it for the parallel algorithms, and it is **not** in the course's Linux images: `apt-get update && apt-get install -y libtbb-dev` installs it, and `find_package(TBB)` with `TBB::tbb` in CMake links it. Without it the program still compiles and runs, which is the trap of 19.2. **MinGW Clang 19.1** could not link the thread library in our tests (`undefined reference to std::__once_callable`) and is not used in this chapter. And on Windows, **ThreadSanitizer is not available**: run 19.12 in Docker or WSL.

Linux programs that use threads should link the platform's thread library: the `CMakeLists.txt` files of this chapter say `find_package(Threads REQUIRED)` and `target_link_libraries(rooster PRIVATE Threads::Threads)`. On Windows it changes nothing, and on glibc 2.34 and later it is not strictly needed, but older systems add `-pthread` through it.

---

## 19.2 Parallel algorithms

In this lecture the algorithms of chapter 15 learn to use every core, with one extra argument.

Most standard algorithms accept an **execution policy** as a new first argument:

```cpp
std::transform(first, last, out, f);                          // one thread
std::transform(std::execution::par, first, last, out, f);     // many threads
```

The policies live in `<execution>`:

| policy | meaning |
|---|---|
| `std::execution::seq` | sequential: the same as no policy |
| `std::execution::par` | parallel: the work is split over threads |
| `std::execution::par_unseq` | parallel **and vectorized**: each thread may also interleave the steps of several elements (SIMD), so the function must not take locks or wait |
| `std::execution::unseq` | vectorized only, on the calling thread (C++20) |

A policy is a **permission, not an order**. The library may still run the work on one thread, for a small range, or because it has no way to do better (below).

### An ideal case

```cpp
std::vector<double> input(10'000'000);
std::iota(input.begin(), input.end(), 1.0);
std::vector<double> sequential_out(input.size());
std::vector<double> parallel_out(input.size());

auto heavy{[](double x) { return std::sqrt(x) * std::sin(x); }};

std::transform(input.begin(), input.end(), sequential_out.begin(), heavy);
std::transform(std::execution::par, input.begin(), input.end(), parallel_out.begin(), heavy);
```

Each result depends only on its own input, and the function is expensive enough to be worth sharing. The program times both calls (with a small helper `milliseconds(work)` whose parameter is a forwarding reference, 16.10) and prints a line that starts with `[varies]`, because the numbers belong to the machine:

```
[varies] transform of 10M doubles   seq    55.8 ms   par     7.2 ms   speedup 7.7x
same results: true
```

That is on 20 hardware threads, with GCC. MSVC gave 8.0x and Clang 7.2x. The results of the two calls are **identical**, and a speedup of 7 or 8 on 20 threads is typical: memory bandwidth and thread start-up eat the rest.

### The trap: nothing may be faster

Here is a similar program (20 million elements) on GCC with oneTBB **missing** (a plain `g++ -std=c++23 -O2`):

```
transform: seq 111.7 ms   par 315.8 ms
```

It compiles. It runs. It gives the right answers. And `par` is **three times slower** than not asking. libstdc++ falls back to a serial implementation of the parallel algorithms when it cannot find TBB, and that fallback has overhead of its own. MinGW has no TBB either, and shows `speedup 1.0x` for everything. With `libtbb-dev` installed and `-ltbb`, the same call took 27.9 ms. The `CMakeLists.txt` of 19.2 looks for TBB and warns when it is missing:

```cmake
if(NOT MSVC)
    find_package(TBB QUIET)
    if(TBB_FOUND)
        target_link_libraries(rooster PRIVATE TBB::tbb)
    else()
        message(WARNING "oneTBB not found: std::execution::par will run on one thread. ...")
    endif()
endif()
```

**Rule: measure.** If `par` is not clearly faster, you probably have no backend.

### Not everything is worth it

Handing work to other threads has a fixed cost. For a small range the cost is bigger than the work. The program times 2,000 calls of `transform` on 1,000 elements each:

```
MSVC:  seq 11.6 ms   par 111.3 ms   speedup 0.1x
GCC:   seq  7.5 ms   par  17.3 ms   speedup 0.4x
Clang: seq  7.7 ms   par  17.5 ms   speedup 0.4x
```

Ten times slower with MSVC, two to three times slower with GCC and Clang. A parallel algorithm pays off when there is **a lot of work per call**: a big range, or an expensive function.

### `reduce`: the parallel `accumulate`

`std::accumulate` (15.7) has no policy and goes strictly left to right. **`std::reduce`** is allowed to add the elements **in any order and grouping**, so it can split the range between threads:

```cpp
std::int64_t sum{std::reduce(std::execution::par, numbers.begin(), numbers.end(), std::int64_t{0})};
```

That has a consequence: the operation must be **associative and commutative**. With integers the grouping cannot change the answer. With `double` it can, because floating-point addition is not associative: the parallel sum agrees to about 15 digits and may differ in the last ones from run to run. The program checks that the two sums agree to six digits:

```
accumulate 83905887189790   reduce 83905887189790   equal: true
doubles: agree to 6 digits: true
```

### More algorithms

`std::sort` takes a policy too. On ten million integers:

```
GCC:   seq  632.7 ms   par  54.5 ms   speedup 11.6x
Clang: seq  617.8 ms   par  63.7 ms   speedup  9.7x
MSVC:  seq 2187.0 ms   par 404.4 ms   speedup  5.4x
```

`for_each`, `count_if`, `transform_reduce`, `copy`, `find`, `any_of` and many more accept one. The program also checks that `count_if` gives the same answer with and without it (`4999990 and 4999990`).

### The rules of the road

1. **The function you pass must not touch shared data without protection.** A lambda that does `++counter` on an outer variable is a data race (19.4). Each element should be processed independently.
2. **An exception that escapes the function calls `std::terminate`.** We tried it on all three compilers: the sequential call of the same code was caught normally, and the parallel one ended the program. Parallel algorithms need functions that do not throw.
3. **The `std::ranges::` algorithms have no policy overloads.** For a policy, use the iterator-pair form (15.2), as the program does.
4. **Measure.** Release build, a large input, and a real comparison.

### The pattern to remember

> **A parallel algorithm is a normal algorithm with a policy in front. It pays off for a lot of independent work per call, it needs oneTBB with GCC and Clang, and the only way to know it helped is to measure.**

**Code for this lecture**: `19.2ParallelAlgorithms/`.

---

## 19.3 Threads and `std::jthread`

In this lecture we start threads ourselves, get results back, and ask them to stop.

A **thread** is an independent line of execution inside your program. All the threads of a program **share its memory** (the heap and the globals), and each has its **own stack**. The operating system decides which ones run, on which core, and in which order.

### Starting a thread and joining it

```cpp
std::thread hello{[] {
    std::println("hello from the new thread");
}};
hello.join();
std::println("main: the thread has finished");
```

The thread starts running as soon as the object is constructed. **`join()` waits** until it has finished. A `std::thread` that is destroyed while it is still **joinable** (neither joined nor detached) calls `std::terminate`: the library refuses to guess what you wanted. The other option, `detach()`, lets a thread run on its own for ever, and is almost always a mistake.

If `main` printed a line too, the two lines could come in either order: nothing says which thread reaches its `println` first.

### Arguments and results

```cpp
void sum_slice(const std::vector<double>& readings, std::size_t first, std::size_t last, double& result);

std::thread left{sum_slice, std::cref(readings), 0, 500, std::ref(first_half)};
std::thread right{sum_slice, std::cref(readings), 500, 1'000, std::ref(second_half)};
left.join();
right.join();
std::println("halves: {} + {} = {}", first_half, second_half, first_half + second_half);
```
```
halves: 125250 + 375250 = 500500
```

Two things to notice:

- The constructor **copies every argument** into the new thread (like `std::async` and `std::bind`). A parameter of type `double&` would silently bind to the copy and the answer would be lost, so the compiler refuses it unless you say **`std::ref`** (or **`std::cref`** for `const`). That is why the vector is passed with `cref` and the result with `ref`.
- A thread **cannot return a value**. It writes into something that outlives it, and the starter reads it **after `join()`**. (19.8 has a better way.)

### Many threads, no sharing

```cpp
std::vector<double> partial(thread_count, 0.0);
{
    std::vector<std::jthread> team;
    for (std::size_t i{0}; i < thread_count; ++i) {
        team.emplace_back(sum_slice, std::cref(readings), i * slice, (i + 1) * slice, std::ref(partial[i]));
    }
}   // leaving the block joins all four
```
```
thread 0 summed 31375
thread 1 summed 93875
thread 2 summed 156375
thread 3 summed 218875
total: 500500
```

Each thread writes only **its own element** of `partial`, and the vector is sized *before* the threads start. No two threads touch the same memory, so nothing needs protecting. **The cheapest synchronization is not sharing.**

### `std::jthread`: a thread that cleans up after itself

`std::jthread` (C++20) is a `std::thread` that **joins in its destructor**. That is RAII (10.6) applied to threads, and it removes the "forgot to join" crash. Use `std::jthread` unless you have a reason not to.

### Asking a thread to stop

A thread cannot be killed from outside (that would skip its destructors). It is **asked** to stop, and it checks. A `std::jthread` has a stop request built in: if the thread's function takes a **`std::stop_token`** as its first parameter, the `jthread` passes one in:

```cpp
int samples_taken_by_worker{0};
{
    std::jthread sensor{[&samples_taken_by_worker](std::stop_token token) {
        std::stop_callback on_stop{token, [] {
            std::println("[varies] stop requested, the worker will leave its loop");
        }};
        while (!token.stop_requested()) {
            ++samples_taken_by_worker;
            std::this_thread::sleep_for(std::chrono::milliseconds{1});
        }
    }};

    std::this_thread::sleep_for(std::chrono::milliseconds{30});
    sensor.request_stop();
}
std::println("the worker took samples before it stopped: {}", samples_taken_by_worker > 0);
```
```
[varies] stop requested, the worker will leave its loop
the worker took samples before it stopped: true
```

`request_stop()` sets the token. A `std::stop_callback` is a function that runs when that happens: on the thread that called `request_stop()`, and at once. And because the destructor of a `jthread` calls `request_stop()` and then joins, leaving the block stops the worker too.

### Errors in a thread

An exception that leaves a thread's function calls `std::terminate`: there is no caller to catch it. The way out is the tool of 18.7. Catch inside the thread, keep the `std::exception_ptr`, and rethrow after `join()`:

```cpp
std::exception_ptr failure;
std::thread fragile{[&failure] {
    try {
        throw std::runtime_error{"the sensor in the thread failed"};
    }
    catch (...) {
        failure = std::current_exception();
    }
}};
fragile.join();
if (failure) {
    std::rethrow_exception(failure);       // main's try block catches it
}
```
```
main caught: the sensor in the thread failed
```

### Also useful

```
   std::thread::hardware_concurrency()   how many threads the machine can run at once (20 here)
   std::this_thread::get_id()            the id of the running thread
   std::this_thread::sleep_for(d)        pause the current thread
```

### The pattern to remember

> **Start threads with `std::jthread`, pass references with `std::ref`, give every thread its own output slot, read results after the join, and stop a thread by asking it (`stop_token`).**

**Code for this lecture**: `19.3ThreadsAndJthread/`.

---

## 19.4 Data races

In this lecture we make four threads share one counter, and watch it go wrong.

The weather network has four stations. Each reports 1,000,000 readings, and we count them all in **one shared counter**:

```cpp
void count_readings_unprotected(int& counter) {
    for (int i{0}; i < readings_per_station; ++i) {
        ++counter;
    }
}
```

Four `std::jthread` run it on the same `int`. The result:

```
[varies] expected 4000000, got 1036930
[varies] updates lost: 2963070
```

Nearly three quarters of the increments vanished, and the number is different on every run.

### Why

`++counter` looks like one step. It is **three**:

```
1. read the value from memory into a register
2. add one
3. write the result back
```

Two threads can both do step 1 before either does step 3:

```
thread A: read 41 ............ add -> 42 ............ write 42
thread B: ........ read 41 ............ add -> 42 ............ write 42
```

Two increments happened, and the counter went up by one. An update was **lost**.

### A data race is undefined behavior

It is not just "a bit off". A **data race** is:

> two threads access the same memory location, at least one of them writes, and nothing orders the accesses.

It is **undefined behavior**: the compiler is allowed to assume that it never happens, and may keep `counter` in a register for the whole loop, reorder reads and writes, or do anything else that is correct for **one** thread. Reading from several threads is fine. Writing to memory that nobody else uses is fine (19.3). The combination is the problem.

### Optimized builds can hide it

We ran the same program optimized:

| build | result of the race |
|---|---|
| unoptimized (all three) | about 1,000,000 of 4,000,000 |
| GCC `-O2`, Clang `-O2` | **4,000,000**, three runs out of three |
| MSVC `/O2` | **1,000,000**, three runs out of three |

GCC and Clang turned each loop into one addition of a million, which makes the window for losing an update tiny, so the result happened to be right. MSVC kept the counter in a register for the whole loop and wrote it once, so the last thread to finish won. **The bug is the same in all of them.** The optimized GCC program is not correct; it is lucky, and a different machine, compiler or load will take the luck away.

> **This is the worst thing about data races: a test that passes proves nothing.** 19.12 shows a tool that finds them without waiting for bad luck.

### First cure: share nothing

The cheapest fix is not to share. Each thread counts into its **own** variable, and the partial counts are added after the joins:

```cpp
void count_readings_alone(int& my_count) {
    int local{0};
    for (int i{0}; i < readings_per_station; ++i) {
        ++local;
    }
    my_count = local;
}
```
```
expected 4000000, got 4000000
```

Each thread writes only its own element of a vector of counts (sized first), and `main` adds them up. That is also the **fastest** version, because nothing waits for anything: 19.6 times it at 1 to 2 ms for the four million increments. When you cannot avoid sharing, the next two lectures have the tools: the mutex and the atomic.

### Other races you will meet

- **A `std::vector` that several threads `push_back` into**: the vector's internals are corrupted, and the program may crash.
- **Check, then act**: `if (stock > 0) --stock;` is two steps, and another thread can empty the stock between them.
- **A flag**: `bool done` written by one thread and read by another (19.12).
- **One member function that forgets to lock** in a class that otherwise does (19.12).

### The pattern to remember

> **Two threads, the same memory, one of them writing, nothing ordering them: a data race, and undefined behavior. A test that passes proves nothing. Share nothing when you can.**

**Code for this lecture**: `19.4DataRaces/`.

---

## 19.5 Mutexes and deadlock

In this lecture we protect shared data with a **mutex**, and meet the bug that mutexes make possible.

A **mutex** ("mutual exclusion") lets only **one thread at a time** into a stretch of code, the **critical section**:

```
mutex.lock();         if another thread holds it, wait here
++counter;            only one thread at a time gets here
mutex.unlock();       let the next one in
```

Calling `lock()` and `unlock()` by hand is the same mistake as `new` and `delete` (9.9): an early `return` or an exception skips the `unlock`, and the mutex stays locked for ever. So a mutex is always locked by an object whose destructor unlocks it. RAII again (10.6).

### `std::lock_guard`

```cpp
void count_readings(int& counter, std::mutex& counter_mutex) {
    for (int i{0}; i < readings_per_station; ++i) {
        std::lock_guard<std::mutex> lock{counter_mutex};   // locks here, unlocks at the end of each iteration
        ++counter;
    }
}
```
```
expected 4000000, got 4000000
[varies] took 228 ms (a mutex per increment is slow; 19.6 has a cheaper tool)
```

Correct, every time, and slow: every one of the four million increments queues up for the lock (the share-nothing version of 19.4 takes 1 to 2 ms; 19.6 compares them all).

### A mutex belongs with the data it protects

The safest design is a class that **owns both**, and whose member functions are the only way in. Nobody can forget to lock, because nobody can reach the data:

```cpp
class SharedReadings {
public:
    void add(double celsius) {
        std::lock_guard<std::mutex> lock{mutex_};
        values_.push_back(celsius);
    }
    std::size_t size() const {
        std::lock_guard<std::mutex> lock{mutex_};
        return values_.size();
    }
    ...
private:
    mutable std::mutex mutex_;     // mutable (10.5): locking changes the mutex, not the readings
    std::vector<double> values_;
};
```

Four threads add 1,000 readings each:

```
4000 readings, largest 39
```

### Three kinds of lock

| type | use |
|---|---|
| `std::lock_guard` | the simple one: locks in the constructor, unlocks in the destructor |
| `std::unique_lock` | the flexible one: can unlock early, lock again, try with a timeout, and is what condition variables need (19.7) |
| `std::scoped_lock` (C++17) | locks **several** mutexes in one step, without deadlock |

### Deadlock

Two stations share a power budget and move battery between them. A transfer needs **both** mutexes. If thread 1 locks A then B, while thread 2 locks B then A:

```
thread 1: holds A ......... waits for B ......... (for ever)
thread 2: holds B ......... waits for A ......... (for ever)
```

Each holds one mutex and waits for the other. That is a **deadlock**: the program hangs and nothing reports it. To show it without hanging, the demo uses `std::timed_mutex` and gives up after 200 ms:

```cpp
bool transfer_in_opposite_orders(Station& first, Station& second, int amount) {
    std::unique_lock<std::timed_mutex> first_lock{first.mutex};
    std::this_thread::sleep_for(std::chrono::milliseconds{50});      // the other thread locks ITS first mutex
    std::unique_lock<std::timed_mutex> second_lock{second.mutex, std::defer_lock};
    if (!second_lock.try_lock_for(patience)) {
        ...
        return false;                                                // gave up
    }
    ...
}
```
```
both threads gave up waiting: true
nothing moved: north 100, south 100
```

(`std::defer_lock` builds the lock object **without locking**, so that `try_lock_for` can do it with a time limit. The function also pauses for a while before returning, still holding its first mutex. Without that, the thread that gave up first would release its mutex and the other would get through: giving up is not free, and a timeout does not fix a deadlock, it only reports it.)

### The cure: lock them together

```cpp
void transfer_safely(Station& from, Station& to, int amount) {
    std::scoped_lock lock{from.mutex, to.mutex};
    from.battery -= amount;
    to.battery += amount;
}
```
```
north 110, south 90
```

`std::scoped_lock` takes any number of mutexes with an algorithm that **cannot deadlock**, whatever order you list them in. (The alternative is to lock in the **same order everywhere**, for example by address or by an id.)

### Many readers, one writer

A mutex lets one thread in, even when all of them only **read**. A `std::shared_mutex` has two modes: any number of readers at once (**shared**), or exactly one writer (**exclusive**):

```cpp
int hottest() const {
    std::shared_lock<std::shared_mutex> lock{mutex_};     // many threads can be here together
    return hottest_;
}
void report(int celsius) {
    std::unique_lock<std::shared_mutex> lock{mutex_};     // exclusive: waits for all readers to leave
    ...
}
```
```
hottest reported: 30, checks made: 3000
```

It pays off when reads are frequent, slow-ish, and writes are rare. For a counter, a plain mutex is simpler and often faster.

### Rules that prevent most trouble

- Keep critical sections **short**: no sleeping, no waiting for the network, no printing while holding a lock.
- Lock several mutexes with **one `scoped_lock`**, or always in the same order.
- Never call code you do not control (a callback, a virtual function) while holding a lock.
- The data and its mutex belong in **one class**.

### The pattern to remember

> **A mutex lets one thread at a time into a critical section; lock it with an RAII object, keep it with its data, take several together with `scoped_lock`, and keep the section short.**

**Code for this lecture**: `19.5MutexAndDeadlock/`.

---

## 19.6 Atomics

In this lecture we meet a cheaper tool for the case where all you need is **one variable** updated safely.

A mutex is the general tool: it protects any amount of code and data. An **atomic** is a variable whose operations are **indivisible**: no other thread can see, or interleave with, half of one. `std::atomic<T>` comes from `<atomic>`:

```cpp
std::atomic<int> counter{0};
++counter;                       // one indivisible read-modify-write
counter.fetch_add(5);            // the same, with a name; returns the OLD value
int now{counter.load()};         // a safe read
counter.store(0);                // a safe write
```

### The counter of 19.4, atomic

```cpp
void count_readings(std::atomic<int>& counter) {
    for (int i{0}; i < readings_per_station; ++i) {
        ++counter;
    }
}
```
```
expected 4000000, got 4000000
```

Correct, and much cheaper than the mutex. The same four threads and four million increments, timed on the three compilers:

| | mutex | atomic | relaxed atomic | share nothing |
|---|---|---|---|---|
| MSVC | 122 ms | 56 ms | 54 ms | 1 ms |
| GCC | 380 ms | 51 ms | 50 ms | 2 ms |
| Clang | 225 ms | 49 ms | 48 ms | 2 ms |

The ladder is clear: **not sharing** is by far the best, an atomic is 2 to 7 times faster than a mutex (the gap depends on the compiler and the machine), and a mutex is the slowest. (`is_always_lock_free` was `true`: a `std::atomic<int>` is a single machine instruction, not a hidden lock.)

The "relaxed" column uses `counter.fetch_add(1, std::memory_order_relaxed)`: it says "I only need the increments not to be lost, not ordered against other memory operations". On x86 it made no difference. The default, `memory_order_seq_cst`, is the strictest and easiest to reason about. **Reach for weaker orderings only after measuring**, and only when you know why.

### An update that has no operation: `compare_exchange`

We want the **highest reading of all stations** in one shared atomic. There is no atomic "maximum". "Read it, compare, write if bigger" is three steps, and another thread can change the value in between. **`compare_exchange_weak`** does the last two as ONE step:

> if the atomic still holds `seen`, replace it with `value` and return `true`; otherwise load the **current** value into `seen` and return `false`

so we simply try again:

```cpp
void record_peak(std::atomic<int>& peak, int value) {
    int seen{peak.load()};
    while (value > seen && !peak.compare_exchange_weak(seen, value)) {
        // `seen` now holds what another thread wrote; the loop checks again
    }
}
```

This loop is the standard pattern for any atomic update that has no ready-made operation. Four threads record 100,000 readings each, and the answer is compared with a single-threaded pass:

```
peak 4999 and the single-threaded answer 4999
```

### Publishing data with an atomic flag

One thread prepares a forecast (ordinary variables) and then sets a flag. The other waits for the flag and reads the forecast:

```cpp
Forecast forecast;                                  // ordinary data, no atomics
std::atomic<bool> ready{false};
std::jthread reader{[&] {
    ready.wait(false, std::memory_order_acquire);   // sleeps until the value is no longer false
    std::println("reader sees hottest {}, coldest {}", forecast.hottest, forecast.coldest);
}};
...
forecast.hottest = 31;
forecast.coldest = 12;
ready.store(true, std::memory_order_release);
ready.notify_one();                                 // wakes a thread blocked in wait()
```
```
reader sees hottest 31, coldest 12
```

The flag is atomic, and the **order** matters:

```
store(true, release)   "everything I wrote before this is visible to whoever sees this value with an acquire"
wait / load (acquire)  "after I see true, I also see all of that"
```

Without that pairing, the reader could see the flag set and still read the old forecast, because compilers and processors reorder memory operations. A **release** store and an **acquire** load form a pair: that is the one pattern of memory ordering most programs ever need. `wait` (C++20) puts the thread to sleep instead of spinning, and `notify_one` wakes it.

### Limits of atomics

- They protect **one variable**. "north + south == total" involves three variables, and making each one atomic does not make the *group* consistent. That needs a mutex.
- `if (count.load() < limit) count.fetch_add(1)` is a race: the check and the update are two operations. Use `compare_exchange`.
- Atomics make a data race impossible **on that variable**. They do not make a program correct.

### The pattern to remember

> **One shared variable: an atomic, updated with `fetch_add` or a `compare_exchange` loop. A group of variables or an invariant: a mutex. Best of all: share nothing.**

**Code for this lecture**: `19.6Atomics/`.

---

## 19.7 Condition variables

In this lecture we solve a different problem: not "who may touch the data", but "how do I **wait** until there is something to touch".

A consumer that finds a queue empty could loop and look again (**spinning**: burning a whole core for nothing), or sleep for a while and hope (late, and wasteful). A **condition variable** is the right tool: the thread goes to sleep, and the thread that changes things wakes it.

```cpp
std::unique_lock<std::mutex> lock{mutex};
cv.wait(lock, [&] { return there_is_something; });    // sleep until the condition is true
// ...use the data, still holding the lock...
```

and in the thread that changes the state:

```cpp
{
    std::lock_guard<std::mutex> lock{mutex};
    make_something_true();
}
cv.notify_one();                                       // wake one sleeper
```

`wait()` does three things in one indivisible step: it checks the condition, and if it is false it **unlocks the mutex and sleeps**; when woken it **locks the mutex again** and checks the condition again. That is why it needs a `std::unique_lock` (which can unlock and lock again; a `lock_guard` cannot). The re-check is not optional:

- a thread can **wake up when nothing happened** (a *spurious wakeup*), and
- another thread may have taken the item first.

**Always pass the condition to `wait`.** The condition is the thing that is true, and the notification is only a nudge.

### A queue between threads

`push()` waits while the queue is full, `pop()` waits while it is empty. The queue is **bounded**, which matters: if producers are faster than consumers, an unbounded queue grows until memory runs out.

```cpp
template <typename T>
class BoundedQueue {
public:
    explicit BoundedQueue(std::size_t capacity) : capacity_{capacity} {}

    void push(T item) {
        std::unique_lock<std::mutex> lock{mutex_};
        not_full_.wait(lock, [this] { return items_.size() < capacity_; });
        items_.push_back(std::move(item));
        ...
        not_empty_.notify_one();
    }

    // Returns std::nullopt when the queue is closed AND empty: "no more items, ever".
    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock{mutex_};
        not_empty_.wait(lock, [this] { return !items_.empty() || closed_; });
        if (items_.empty()) {
            return std::nullopt;
        }
        T item{std::move(items_.front())};
        items_.pop_front();
        not_full_.notify_one();
        return item;
    }

    void close() {
        {
            std::lock_guard<std::mutex> lock{mutex_};
            closed_ = true;
        }
        not_empty_.notify_all();       // wake EVERY sleeping consumer, so each can see "closed" and leave
    }
    ...
};
```

A new piece of syntax: the lambdas say **`[this]`**. A lambda inside a member function may use the object's members only if it captures the object, and `[this]` does that.

Two stations produce 1,000 readings each, two analysts consume them, and the queue holds at most 8, so the fast side has to wait for the slow side:

```
consumed 2000 readings, sum 1999000
the queue never held more than 8: true
[varies] the two consumers took 1066 and 934 readings
```

All 2,000 readings arrived, none twice (the sum is 0 + 1 + ... + 1999), and the split between the two consumers is different on every run.

The shutdown order is part of the design: the producers are joined first (everything is pushed), then `close()` is called, then the consumers drain what is left and leave when `pop()` returns `std::nullopt`.

### Stopping a waiting thread

What if the thing a thread waits for never happens? `close()` above is one way out. A `std::stop_token` (19.3) is another: with **`std::condition_variable_any`**, `wait` accepts a token, and `request_stop()` wakes the sleeper:

```cpp
std::jthread waiter{[&](std::stop_token token) {
    std::unique_lock<std::mutex> lock{mutex};
    bool condition_true{wakeup.wait(lock, token, [&] { return news_arrived; })};
    std::println("the waiter woke up; the news arrived: {}", condition_true);
}};
...
waiter.request_stop();
```
```
the waiter woke up; the news arrived: false
```

`wait` returns the value of the condition, which is `false` here: it woke because of the stop request, not the news. The thread pool of 19.10 and the logger of 19.11 end their workers this way.

### Mistakes to avoid

- **Calling `wait()` without a condition**: a `notify` that comes *before* the wait is lost, and the thread sleeps for ever (the "lost wakeup").
- **Changing the condition without holding the mutex**: the sleeper can check it, miss the change, and go to sleep after the notify.
- **Using `notify_one` when several threads must react**: use `notify_all`.

### The pattern to remember

> **A condition variable puts a thread to sleep until a condition is true. Always wait with a predicate, always change the condition under the mutex, and `notify_all` when everybody must look.**

**Code for this lecture**: `19.7ConditionVariables/`.

---

## 19.8 `async` and futures

In this lecture we get a result back from another thread, the proper way.

In 19.3 a thread could not return a value: we wrote into a variable and read it after `join()`. That is clumsy, and an exception in the thread ends the program. `<future>` adds a better way:

```
std::future<T>     a ticket for a T that will exist LATER
future.get()       waits until it is ready, then gives the value (or throws the exception the work threw)
```

The other end of the ticket, where the value is put in, comes in three forms: **`std::async`** (runs a function for you), **`std::promise`** (you set the value yourself) and **`std::packaged_task`** (wraps a callable, runs it when you say).

### `std::async`

```cpp
std::future<double> first_half{std::async(std::launch::async, sum_of, std::cref(readings), 0, 500)};
std::future<double> second_half{std::async(std::launch::async, sum_of, std::cref(readings), 500, 1'000)};
// main is free to do other work here; get() waits only if the answer is not ready yet.
std::println("halves: {} + {}", first_half.get(), second_half.get());
```
```
halves: 125250 + 375250
```

The first argument says **where**: `std::launch::async` runs the call on a new thread now; `std::launch::deferred` does not start anything, and runs the call in the thread that calls `get()`. The rest is the callable and its arguments, copied like a thread's. A future gives its value **once**: calling `get()` a second time is an error.

```cpp
std::future<std::thread::id> on_thread{std::async(std::launch::async, [] { return std::this_thread::get_id(); })};
std::future<std::thread::id> lazily{std::async(std::launch::deferred, [] { return std::this_thread::get_id(); })};
```
```
launch::async ran on another thread: true
launch::deferred ran on main, at get(): true
```

Without a policy, `std::async(f)` may choose either. **Always say which.**

### The future of an `async` waits when it is destroyed

This one surprises everybody. A future that came from `std::async` **waits for its work in its destructor**. So "fire and forget" does not exist: if you throw the future away, the statement does not finish until the work does, and two such calls run one after the other:

```cpp
static_cast<void>(std::async(std::launch::async, fetch_reading, 1));   // the temporary future dies at once: waits 100 ms
static_cast<void>(std::async(std::launch::async, fetch_reading, 2));   // and then another 100 ms
```
```
[varies] futures discarded: 201 ms, futures kept: 100 ms
[varies] keeping the futures lets the two calls overlap: true
```

(All three compilers warn when you discard the result of `std::async`, MSVC with a dedicated warning, C4858, that explains exactly this; the `static_cast<void>` is there to quiet it.) Keep the futures, start all the calls, and `get()` afterwards.

### Exceptions come out of `get()`

```cpp
std::future<int> broken{std::async(std::launch::async, fetch_reading, -1)};
try {
    broken.get();
}
catch (const std::exception& error) {
    std::println("get() threw: {}", error.what());
}
```
```
get() threw: no such station
```

The exception was captured in the future (with the `std::exception_ptr` of 18.7, which is what the library uses inside) and thrown again where the result is read. The `try`/`catch` we wrote by hand in 19.3 is done for you.

### `std::promise`: set the value yourself

A promise is the **writing end**, a future the **reading end**, of the same slot. Use it when the value comes from something that is not a function call:

```cpp
std::promise<int> forecast_promise;
std::future<int> forecast{forecast_promise.get_future()};
std::jthread forecaster{[&forecast_promise] {
    std::this_thread::sleep_for(std::chrono::milliseconds{20});
    forecast_promise.set_value(27);                  // or set_exception(std::current_exception())
}};
std::println("tomorrow: {} C", forecast.get());
```
```
tomorrow: 27 C
```

### `std::packaged_task`: a callable that remembers its future

It does not run by itself: you call it, on whichever thread you like. That is the missing piece for a thread pool (19.10).

```cpp
std::packaged_task<int(int)> job{fetch_reading};
std::future<int> job_result{job.get_future()};
std::thread worker{std::move(job), 5};               // a packaged_task is move-only
worker.join();
```
```
the job has not run yet; the result is ready: false
after running: ready true, value 25
```

### Waiting with a limit

```cpp
if (slow.wait_for(std::chrono::milliseconds{10}) == std::future_status::timeout) {
    std::println("not ready after 10 ms, doing something else");
}
```
```
not ready after 10 ms, doing something else
then: 23
```

`wait_for` returns `std::future_status::ready`, `timeout` or `deferred`. A trap in the program is worth a comment: the two arguments of the call that printed `ready` and the value cannot be written as `println(..., job_result.wait_for(...) == ready, job_result.get())`. The order in which the arguments of a call are evaluated is **not specified**, and `get()` empties the future. GCC evaluated them right to left, and the program died with `future_error: No associated state`. The version in the lecture computes them in two statements.

### The pattern to remember

> **A future is a ticket for a result. `async` runs a call for you (always name the launch policy and keep the future), `promise` hands over a value you set yourself, `packaged_task` wraps work to run later. `get()` brings back the value or the exception.**

**Code for this lecture**: `19.8AsyncAndFutures/`.

---

## 19.9 Latch, barrier and semaphore

In this lecture we meet three small C++20 tools for situations that mutexes and condition variables handle awkwardly:

| tool | idea |
|---|---|
| `std::latch` | a countdown that can be used **once**: threads count it down, others wait for zero |
| `std::barrier` | a meeting point that can be used **again and again**, one round after another |
| `std::counting_semaphore<N>` | N tickets: `acquire()` takes one (waiting if none is left), `release()` gives it back |

### A latch: a starting gun and a finish line

```cpp
std::latch start_gun{1};                       // opened by main
std::latch finish_line{static_cast<std::ptrdiff_t>(station_count)};   // opened by the stations
std::vector<int> results(station_count, 0);
{
    std::vector<std::jthread> stations;
    for (std::size_t id{0}; id < station_count; ++id) {
        stations.emplace_back([&, id] {
            start_gun.wait();                  // nobody starts before main says so
            results[id] = static_cast<int>(id * id);
            finish_line.count_down();          // "I am done"
        });
    }
    start_gun.count_down();                    // Go.
    finish_line.wait();                        // returns when the count has reached zero
    std::println("all stations finished, results {} {} {} {}", results[0], results[1], results[2], results[3]);
}
```
```
all stations finished, results 0 1 4 9
```

(`[&, id]` captures everything by reference except `id`, which is copied: each thread needs its own `id`.) The same latch cannot be reused: once it reaches zero it stays there.

### A barrier: work in rounds

Every round, each station computes one number. Nobody may start round 2 before everybody finished round 1, because round 2 uses all the numbers of round 1. `arrive_and_wait()` is the **meeting point**. When the last thread arrives, the barrier runs its **completion function once** (on that thread), then releases everybody into the next round:

```cpp
auto end_of_round{[&slot, &round_number]() noexcept {
    std::println("round {} complete, total {}", ++round_number, std::accumulate(slot.begin(), slot.end(), 0));
}};
std::barrier meeting{static_cast<std::ptrdiff_t>(station_count), end_of_round};

// in each station's thread:
for (int round{1}; round <= 3; ++round) {
    slot[id] = static_cast<int>(id) * 10 + round;
    meeting.arrive_and_wait();
}
```
```
round 1 complete, total 64
round 2 complete, total 68
round 3 complete, total 72
```

Four stations, each adding `id * 10 + round`: 0 + 10 + 20 + 30 + 4 * round gives 64, 68 and 72. The completion function runs when all four have written, and before anyone moves on, so it needs no lock. (It must be `noexcept`.)

### A semaphore: at most two at a time

The weather service lets us have only two connections open. Six stations want to upload. Each takes a ticket first:

```cpp
std::counting_semaphore<4> connections{2};     // 4 is the largest count this type can hold; we start with 2
std::atomic<int> open_now{0};
std::atomic<int> most_open{0};
...
connections.acquire();                         // waits while both tickets are in use
int now{++open_now};
// record the maximum with a compare_exchange loop (19.6)
std::this_thread::sleep_for(std::chrono::milliseconds{20});
--open_now;
connections.release();
```
```
never more than 2 connections open at once: true
[varies] the most that were open together: 2
```

### Which one when

```
   latch      one-time gate or countdown ("wait for all the workers")
   barrier    the same gate again and again ("end of each round")
   semaphore  limit how many threads may be inside at once
   mutex      exactly one at a time, and protects data
```

### The pattern to remember

> **A latch is a one-time countdown, a barrier is a meeting point for rounds, a semaphore limits how many threads are inside. A mutex is for exclusive access to data.**

**Code for this lecture**: `19.9LatchBarrierSemaphore/`.

---

## 19.10 A thread pool

In this lecture we build the tool that most real programs use for "run this somewhere else": a pool of worker threads and a queue of jobs.

Starting a thread costs time and memory, and a program that starts one per small job (19.3) spends more on starting than on working. A **thread pool** starts a fixed number of workers once, and gives them jobs through a queue (19.7). Submitting a job returns a `std::future` (19.8) for its result:

```
   submit(job) ---> [ job | job | job ] ---> worker 1
                        the queue      \--> worker 2
                                        \-> worker 3 ...
```

### The pool

The class is in `thread_pool.h`, about 85 lines with comments. Its pieces:

```cpp
class ThreadPool {
public:
    explicit ThreadPool(std::size_t thread_count) {
        for (std::size_t i{0}; i < thread_count; ++i) {
            workers_.emplace_back([this](std::stop_token token) { work(token); });
        }
    }
    ~ThreadPool() = default;       // std::jthread's destructor stops and joins each worker

    template <typename F>
    auto submit(F&& job) -> std::future<decltype(job())> {
        using Result = decltype(job());
        std::packaged_task<Result()> task{std::forward<F>(job)};
        std::future<Result> result{task.get_future()};
        {
            std::lock_guard<std::mutex> lock{mutex_};
            jobs_.push_back(std::move(task));
        }
        wakeup_.notify_one();
        return result;
    }
    ...
```

The `-> std::future<decltype(job())>` after the parameter list is a **trailing return type**: it is written after the parameters so that it can use the name `job`. `submit` takes **any callable that takes no arguments** (capture what it needs in a lambda), returns a future of whatever it returns (`decltype(job())`, 16.6), and uses what you know:

- a **`std::packaged_task`** (19.8) runs the callable and puts the result, or the exception it threw, into its future;
- the queue stores callables of one type, `void()`. A `packaged_task` can be **moved but not copied**, and `std::function` (15.8) needs copies. **`std::move_only_function`** (C++23) is `std::function` without that demand, and it is what the queue holds.

The worker's loop:

```cpp
void work(std::stop_token token) {
    while (true) {
        std::move_only_function<void()> job;
        {
            std::unique_lock<std::mutex> lock{mutex_};
            if (!wakeup_.wait(lock, token, [this] { return !jobs_.empty(); })) {
                return;                        // stop requested AND the queue is empty: time to leave
            }
            job = std::move(jobs_.front());
            jobs_.pop_front();
        }
        job();                                 // run it WITHOUT holding the lock
    }
}
```

Look at the exit condition. `wait(lock, token, predicate)` returns the value of the predicate when it wakes. When a stop was requested but jobs remain, the predicate is `true`, so the worker keeps going; only when the queue is **empty** *and* a stop is requested does it return `false` and leave. **The pool finishes everything that was submitted before it goes away.** The members are declared so that `workers_` comes last: it is destroyed (and joined) first, while the mutex and the queue still exist.

### Using it

```cpp
ThreadPool pool{4};

std::vector<std::future<int>> futures;
for (int station{0}; station < 8; ++station) {
    futures.push_back(pool.submit([station] { return reading_of(station); }));
}
int total{0};
for (std::future<int>& future : futures) {
    total += future.get();
}
```
```
a pool of 4 workers
total of 8 readings: 188
```

Who ran the jobs? Sixteen jobs that record their thread's id:

```
16 jobs ran on at most 4 threads: true
none of them was the main thread: true
```

### Errors travel in the future

```cpp
std::future<int> broken{pool.submit([] { return reading_of(13); })};
try {
    broken.get();
}
catch (const std::exception& error) {
    std::println("the job threw: {}", error.what());
}
std::println("the pool still works: {}", pool.submit([] { return reading_of(1); }).get());
```
```
the job threw: station 13 does not answer
the pool still works: 21
```

The `packaged_task` catches the exception, so the worker thread is not harmed: the pool keeps going.

### Splitting one big job

```cpp
constexpr std::size_t chunks{8};
std::size_t chunk_size{numbers.size() / chunks};
for (std::size_t c{0}; c < chunks; ++c) {
    partial_sums.push_back(pool.submit([&numbers, c, chunk_size] {
        auto first{numbers.begin() + static_cast<std::ptrdiff_t>(c * chunk_size)};
        return std::accumulate(first, first + static_cast<std::ptrdiff_t>(chunk_size), 0LL);
    }));
}
```
```
sum 500000500000
```

How big should a job be? A job costs one queue operation (a lock, a notification), so it should do **much more work than that**. One job per element is too fine, one job per thread can be uneven. The project of 19.13 compares the two.

### Shutting down

```cpp
{
    ThreadPool short_lived{2};
    for (int i{0}; i < 20; ++i) {
        short_lived.submit([&finished_jobs] { ...; ++finished_jobs; });     // the futures are thrown away
    }
}
std::println("jobs that ran before the pool went away: {}", finished_jobs.load());
```
```
jobs that ran before the pool went away: 20
```

Throwing the futures away is fine here, because a future from a `packaged_task` does **not** wait in its destructor, unlike the one from `std::async` (19.8). And all 20 jobs ran before the pool vanished.

What this pool does not do: it has no way to submit after destruction began, no job priorities, no way to cancel a queued job, and no work stealing. Real libraries (and the pool behind `std::execution::par`) have these. It is 85 lines, and it is enough for the project.

### The pattern to remember

> **A thread pool is a queue, a condition variable and N workers. `submit` wraps a job in a `packaged_task` and returns its future; the queue holds `move_only_function`s; the destructor drains the queue and joins the workers.**

**Code for this lecture**: `19.10ThreadPool/` (`thread_pool.h`, `main.cpp`).

---

## 19.11 A logger

In this lecture we build a second tool that every threaded program ends up wanting: a way for all the threads to say what they are doing, without waiting for the slow part.

### Why not just print from every thread?

`std::println` writes one whole line in one call, and different calls do not corrupt each other. But a line **built from several calls** can be cut in two by another thread's output. For a *stream*, `std::osyncstream` (C++20, `<syncstream>`) collects everything written to it and hands it over **in one piece** when it is destroyed:

```cpp
std::osyncstream out{std::cout};
out << "station " << station << " says " << "hello" << " from its own thread\n";
```
```
[varies] station 0 says hello from its own thread
[varies] station 2 says hello from its own thread
[varies] station 1 says hello from its own thread
[varies] station 3 says hello from its own thread
```

The order changes from run to run, but no line is ever cut in two. (This is the one place we use `std::cout`: `osyncstream` wraps a stream.)

Even then, printing is slow, and every thread that prints waits for the console. For a program that logs a lot, the better design is to take the slow part out of the working threads.

### A logger with its own writer thread

```
   station thread 1 ---+
   station thread 2 ---+--> [ queue of messages ] --> ONE writer thread --> the sink
   station thread 3 ---+
```

The caller only pays for locking and pushing a string. **A single thread does the writing**, so the sink (a file, say) is never used by two threads at once and needs no lock of its own, and the lines of one thread come out in the order that thread logged them. It is the queue of 19.7 and the shutdown of 19.10 once more:

```cpp
class Logger {
public:
    using Sink = std::function<void(const std::string&)>;

    explicit Logger(Sink sink)
        : sink_{std::move(sink)},
          writer_{[this](std::stop_token token) { write_lines(token); }} {}

    void log(Level level, std::string message) {
        {
            std::lock_guard<std::mutex> lock{mutex_};
            lines_.push_back(std::string{name_of(level)} + " " + std::move(message));
        }
        wakeup_.notify_one();
    }

private:
    void write_lines(std::stop_token token) {
        while (true) {
            std::string line;
            {
                std::unique_lock<std::mutex> lock{mutex_};
                if (!wakeup_.wait(lock, token, [this] { return !lines_.empty(); })) {
                    break;                          // stop requested and nothing left to write
                }
                line = std::move(lines_.front());
                lines_.pop_front();
            }
            sink_(line);                            // slow work, done without holding the lock
        }
        sink_("[info] logger shut down");
    }
    ...
    std::jthread writer_;                           // last member: stopped and joined first
};
```

The `Sink` is a `std::function` (15.8): any callable taking a line. In the demo it appends to a `std::vector<std::string>` that only the writer thread touches, and `main` reads after the logger is gone. When the logger is destroyed, `std::jthread` asks the writer to stop, and the writer **drains the queue first**, writes a goodbye line, and leaves. Nothing that was logged is lost.

### The test

Four stations log 50 readings each, and one logs a warning:

```cpp
for (int i{0}; i < 50; ++i) {
    logger.log(Level::info, "station " + std::to_string(station) + " reading " + std::to_string(i));
}
```
```
lines written: 202
last line: [info] logger shut down
each station's lines are in its own order: true
warnings: 1
```

202 is 4 x 50, plus the warning, plus the goodbye line. The check of the order looks at each station's lines **separately**: the order *between* stations is arbitrary, but a station's own lines must be in the order it logged them, because one thread pushes them one after the other into one queue.

### The pattern to remember

> **A logger is a queue and one writer thread. Callers pay only for a lock and a push, the sink needs no lock, each thread's lines keep their order, and the destructor drains the queue.**

**Code for this lecture**: `19.11ALogger/` (`logger.h`, `main.cpp`).

---

## 19.12 Finding races with ThreadSanitizer

In this lecture a tool finds the bugs of 19.4 and 19.5 for us.

A data race can hide for years. It needs two threads to touch the same memory at just the wrong moment, and the program may "work" ten thousand times (19.4 showed an optimized program that gave the right answer, wrongly). **ThreadSanitizer** (TSan) finds races without waiting for the wrong moment. It watches every memory access and every lock the program makes, and reports two accesses that **nothing orders**, even when this run happened to get away with it. In chapter 9 AddressSanitizer found memory bugs with `-fsanitize=address`; TSan is the same idea for threads, with `-fsanitize=thread`.

It is available with **GCC and Clang on Linux** (Clang also on macOS). **MSVC has no ThreadSanitizer, and neither has MinGW.** On Windows run this lecture in the Docker container of chapter 2 (or WSL). The `CMakeLists.txt` switches it on where it exists:

```cmake
if(THREADS_SANITIZE)
    if(MSVC OR WIN32)
        message(STATUS "No ThreadSanitizer for this compiler: building without it")
    else()
        target_compile_options(rooster PRIVATE -fsanitize=thread -fno-omit-frame-pointer -g)
        target_link_options(rooster PRIVATE -fsanitize=thread)
    endif()
endif()
```

`-g` gives the report file names and line numbers. The program holds four classic bugs and runs one by number, like the one of 18.8:

```
rooster          the FIXED versions of all four (clean, exit 0)
rooster 1..4     the BUGGY version of one case
```

```
cmake -S . -B build -G Ninja
cmake --build build
./build/rooster 1
```

### 1. The shared counter (19.4)

```
==================
WARNING: ThreadSanitizer: data race (pid=2894)
  Read of size 4 at 0x000000449384 by thread T2:
    #0 count_to_hundred_thousand_plain() main.cpp:31
    ...
  Previous write of size 4 at 0x000000449384 by thread T1:
    #0 count_to_hundred_thousand_plain() main.cpp:31
```

It names the two threads, the two accesses, the line, and the address. The fix is `std::atomic<int>` (19.6).

### 2. One accessor that forgets to lock

```cpp
class Readings {
public:
    void add(double celsius) {
        std::lock_guard<std::mutex> lock{mutex_};
        values_.push_back(celsius);
    }
    // BUG: reads values_ while another thread may be inside add().
    std::size_t size_forgetting_the_lock() const {
        return values_.size();
    }
    ...
```
```
WARNING: ThreadSanitizer: data race
  Read of size 8 at 0x7ffc217b4460 by thread T2:
    #0 std::vector<double>::size() const
    #1 Readings::size_forgetting_the_lock() const main.cpp:53
```

This is the most common real-world race: most of the class is careful, and one accessor is not. Nothing in the language says "this member is protected". The fix is the same lock in `size()`.

### 3. Two mutexes in opposite orders: a deadlock that did not happen

The two transfers run **one after the other**, so this run cannot hang:

```
WARNING: ThreadSanitizer: lock-order-inversion (potential deadlock)
  Cycle in lock order graph: M0 (0x7ffc32c2e140) => M1 (0x7ffc32c2e170) => M0

  Mutex M1 acquired here while holding mutex M0 in thread T1:
    ...
```

TSan keeps a graph of "this mutex was locked while holding that one" and reports a **cycle**, even though the program finished normally. It reports the *danger*, not only the accident, which is exactly what you want from a tool for deadlocks, because they happen once a month on someone else's machine. The fix is `std::scoped_lock` (19.5).

### 4. A plain `bool` as a stop flag

```cpp
bool plain_stop{false};
...
while (!plain_stop) { ... }        // the worker
...
plain_stop = true;                 // main
```
```
WARNING: ThreadSanitizer: data race
  Write of size 1 at 0x00000044938c by main thread:
    #0 main main.cpp:196
  Previous read of size 1 at 0x00000044938c by thread T1:
    #0 operator() main.cpp:190
```

It looks harmless: one thread writes the flag, another polls it. It is still a data race, and the compiler is free to read the flag once and never look again. The fix is `std::atomic<bool>`, or better a `std::stop_token` (19.3).

All four reports end the program with **exit code 66**, which a test script can check. The fixed versions run clean with exit 0. GCC 16 and Clang 21 print the same four findings.

### How to read what it does and does not prove

- TSan only sees what **runs**. A race on a path your test never takes is invisible. It is a very good detector, not a proof.
- It is slow: expect 5 to 15 times slower and much more memory. Use it on tests, not in production.
- A clean TSan run on a program with several threads is **worth much more** than a passing ordinary test, because it is checking *ordering*, not outcomes.
- **Do not combine it with AddressSanitizer** in one build; they are separate runs.

### Two false alarms we met

1. **oneTBB.** On the parallel algorithms of 19.2 (and the project of 19.13), TSan reports dozens of races *inside oneTBB*, which is not built with the sanitizer and uses lock-free tricks it cannot see. Not our code: every report is in `oneapi/tbb` files. A suppression file silences them:

   ```
   race:oneapi/tbb
   race:tbb::
   race:__pstl::
   ```

   Pass it as `TSAN_OPTIONS=suppressions=suppressions.txt ./build/rooster`. With it, the assignment solution and the project are clean on GCC and Clang.

2. **`std::println` from several threads, with GCC 16.** Two threads calling `std::println` at the same time (2,000 lines each) gave three TSan reports from GCC 16's `<print>` header, where it reads and writes the internal buffer of `stdout`. The same program with `std::fputs` gave none, and Clang with libstdc++ 14 gave none. We did not find out whether this is a flaw of the library or only something TSan cannot see (the C library's lock is not visible to it); in our runs the output was never corrupted. If you want TSan to be silent, **print from one thread** (collect results, print in `main`), through the logger of 19.11, or with `std::osyncstream`, which gave no report. For this reason the lectures of this chapter print from `main` after the threads have finished.

### The pattern to remember

> **Build the threaded parts of your program with `-fsanitize=thread` and run your tests under it. It reports races and lock cycles that did not bite this time. A silent TSan proves little; a loud one is always worth reading.**

**Code for this lecture**: `19.12FindingRacesWithThreadSanitizer/`.

---

## 19.13 Project: parallel Mandelbrot

The project of this chapter draws a picture on the `Canvas` of chapter 10 four ways, and measures what the extra cores buy. The picture is the **Mandelbrot set**: for every pixel, treat it as a point `c` of the plane and repeat

```
z = z * z + c          starting from z = 0
```

until `z` gets farther than 2 from the origin (the point **escapes**), or we give up after `max_iterations` rounds (the point is **in the set**, painted black). The number of rounds picks the colour.

```cpp
int escape_time(double cr, double ci, int max_iterations) {
    double zr{0.0};
    double zi{0.0};
    int rounds{0};
    while (rounds < max_iterations && zr * zr + zi * zi <= 4.0) {
        double next_zr{zr * zr - zi * zi + cr};
        zi = 2.0 * zr * zi + ci;
        zr = next_zr;
        ++rounds;
    }
    return rounds;
}
```

Two properties of this problem decide everything:

1. **Every pixel is independent** of every other. There is nothing to share, which is the best case for parallel work.
2. **Not every pixel costs the same.** A point far outside the set escapes in a few rounds; a point inside runs the full `max_iterations`. The rows in the middle of the picture are expensive, the rows at the top and bottom are cheap.

### The unit of work: one row

```cpp
void render_row(Canvas& canvas, const View& view, int y) {
    double ci{view.top + y * view.step};
    for (int x{0}; x < canvas.width(); ++x) {
        double cr{view.left + x * view.step};
        canvas.set_pixel(x, y, colour_for(escape_time(cr, ci, view.max_iterations), view.max_iterations));
    }
}
```

Each call writes **only the pixels of its own row**, so no two threads ever write the same byte of the canvas: no data race (19.4), and no lock needed. The `Canvas` is the class of chapter 10, **unchanged**.

### Version 1: one thread

```cpp
void render_serial(Canvas& canvas, const View& view) {
    for (int y{0}; y < canvas.height(); ++y) {
        render_row(canvas, view, y);
    }
}
```

### Version 2: a parallel algorithm (19.2)

```cpp
void render_with_par(Canvas& canvas, const View& view) {
    std::vector<int> rows(static_cast<std::size_t>(canvas.height()));
    std::iota(rows.begin(), rows.end(), 0);
    std::for_each(std::execution::par, rows.begin(), rows.end(), [&canvas, &view](int y) {
        render_row(canvas, view, y);
    });
}
```

The least code: `for_each` over the row numbers with `par`. The library splits the rows into chunks and balances them between its workers.

### Version 3: one fixed band per thread (19.3)

```cpp
void render_with_bands(Canvas& canvas, const View& view, unsigned thread_count) {
    int rows_per_band{(canvas.height() + static_cast<int>(thread_count) - 1) / static_cast<int>(thread_count)};
    std::vector<std::jthread> threads;
    for (unsigned t{0}; t < thread_count; ++t) {
        int first{static_cast<int>(t) * rows_per_band};
        int last{std::min(first + rows_per_band, canvas.height())};
        threads.emplace_back([&canvas, &view, first, last] {
            for (int y{first}; y < last; ++y) {
                render_row(canvas, view, y);
            }
        });
    }
}
```

Cut the picture into as many equal bands as there are hardware threads, and give each thread one. Simple, and flawed: the bands in the middle are full of the expensive points, so those threads finish long after the ones that got the cheap top and bottom. Most threads then sit idle waiting for the slowest.

### Version 4: a pool with one job per row (19.10)

```cpp
void render_with_pool(ThreadPool& pool, Canvas& canvas, const View& view) {
    std::vector<std::future<void>> rows;
    for (int y{0}; y < canvas.height(); ++y) {
        rows.push_back(pool.submit([&canvas, &view, y] { render_row(canvas, view, y); }));
    }
    for (std::future<void>& row : rows) {
        row.get();
    }
}
```

Many small jobs: whenever a worker finishes a row, it takes the next one from the queue. A worker that got cheap rows simply does more of them, so the work **balances itself**, at the price of one queue operation per row.

### Run it

```
cmake -S . -B build -G Ninja
cmake --build build
./build/rooster                       # 1600 x 1200, up to 500 rounds
./build/rooster 800 600 200           # width, height, rounds
```

The `CMakeLists.txt` defaults to a Release build (timings of an unoptimized build are meaningless) and links oneTBB for the `par` version (19.2). Every version is run three times and the best time is kept.

### The results

On the 12-core, 20-thread machine used for these notes (your numbers will differ, and with them the exact speedups):

| | MSVC 19.51 | GCC 16 | Clang 21 | MinGW GCC 14.2 |
|---|---|---|---|---|
| one thread | 1123 ms | 477 ms | 486 ms | 489 ms |
| `std::execution::par` | 72 ms (15.6x) | 30 ms (16.0x) | 30 ms (16.1x) | 482 ms (**1.0x**) |
| one band per thread | 139 ms (8.1x) | 62 ms (7.7x) | 62 ms (7.8x) | 61 ms (8.1x) |
| pool, a job per row | 71 ms (15.8x) | 35 ms (13.5x) | 35 ms (14.1x) | 30 ms (16.1x) |

(MinGW built by hand with `-O2` and no oneTBB.) What to read from it:

1. **The speedup is large and near the number of threads.** Sixteen times on 12 cores: the 8 extra "threads" of hyper-threading and the small efficiency cores give more than 12.
2. **The fixed bands reach about half.** Same threads, same work, same picture. The unevenness of the work wastes half of the machine.
3. **Many small jobs fix the balance**, whether a library (`par`) or a pool of ours does the cutting. The pool pays a little for the queue (13.5 against 16.0 on GCC), and MSVC's pool is about as good as its algorithm.
4. **MinGW's `par` is not parallel**: 1.0x. Its threads and our pool work fine (8x and 16x). The parallel algorithms need a backend (19.2); threads do not.
5. **MSVC is slower on one thread** (1123 ms against 477): the code is simply compiled differently, and has nothing to do with threads.

### The same picture, every time

A faster program that draws a different picture would be a bug, so the program compares every version with the serial one **pixel by pixel**, and writes `mandelbrot.png`:

```
par is identical to serial: true
bands are identical to serial: true
pool is identical to serial: true
wrote mandelbrot.png (1600 x 1200)
```

We also compared the PNG files: **byte-identical** across MSVC, GCC, Clang and MinGW (MD5 `d4ca91d492696924b498200d053ef0f7` for the default 1600 x 1200). The project is clean under AddressSanitizer and UndefinedBehaviorSanitizer, and under ThreadSanitizer with the oneTBB suppressions of 19.12 (GCC and Clang): the only thing all the threads share is the canvas, and they write different rows.

### What we learned

- **Look at the shape of the work before choosing a split.** Uneven work needs many small pieces; even work does fine with equal bands.
- **Disjoint writes need no lock.** Dividing the *data* so that every thread owns its part is the best synchronization, and the cheapest (19.4).
- **Start at the left of the ladder** (the chapter intro): the one-line `par` version was as fast as anything we wrote, and **measure** (19.2): on a machine without a backend it would have been no faster than the plain loop.
- **Check that the fast version is right.** Identical pixels is a test you can write in ten lines.

### Things to try

1. Change `max_iterations` to 50 and to 5,000. How do the four versions react? (Fewer rounds means less work per row and a bigger share of overhead.)
2. Give the bands interleaved rows (thread `t` renders rows `t`, `t + n`, `t + 2n`, ...) and compare with the contiguous bands. Why does it balance?
3. Give the pool jobs of 8 rows instead of 1. Is it faster or slower than one row per job?
4. Zoom in: change `View` to a window of width 0.01 centred on `-0.745 + 0.113i`.

**Code for this lecture**: `19.13ProjectParallelMandelbrot/` (`main.cpp`, `canvas.h`, `canvas.cpp`, `color.h`, `thread_pool.h`, `stb_impl.cpp`, `vendor/`).

---

## 19.14 Assignment

Eight small jobs for the weather network. `thread_pool.h` is provided in the folder. Write the helpers above `main()`, and the calls under each exercise heading. **Print from `main`, after the threads have finished**, so the output is the same on every run.

| # | Exercise | Skill |
|---|---|---|
| 1 | `transform`, `count_if` and `reduce` with `std::execution::par` on a million values | parallel algorithms (19.2) |
| 2 | Four `std::jthread` add four slices of a vector into four slots | threads, share nothing (19.3) |
| 3 | A shared counter, with a `std::mutex` and with a `std::atomic<int>` | races, mutex, atomic (19.4 to 19.6) |
| 4 | A class `StationLog` that owns its mutex | mutex belongs with its data (19.5) |
| 5 | Three accounts and three threads in a ring, with `std::scoped_lock` | deadlock (19.5) |
| 6 | A one-slot `Mailbox` with a condition variable | condition variables (19.7) |
| 7 | `std::async` per slice, one slice throws | futures and exceptions (19.8) |
| 8 | Ten jobs on a `ThreadPool`, add their futures | thread pool (19.10) |

Work as in the earlier assignments: the starter `main.cpp` has the statement of each exercise with its sample output. `main_solution.cpp` builds as the target `rooster_solution`. The `CMakeLists.txt` links oneTBB with GCC and Clang for exercise 1 (see 19.2).

The solution's output (it is the same on MSVC, GCC and Clang):

```
--- Exercise 1: parallel algorithms ---
first five: 32 33.8 35.6 37.4 39.2
hotter than 86 F: 225000
sum: 500000500000

--- Exercise 2: four threads, four slices ---
thread 0: 125250
thread 1: 375250
thread 2: 625250
thread 3: 875250
total: 2001000

--- Exercise 3: a shared counter ---
with a mutex: 1000000
with an atomic: 1000000

--- Exercise 4: a thread-safe log ---
400 notes, the longest has 17 characters

--- Exercise 5: a ring of transfers ---
north 100, south 100, east 100
total 300

--- Exercise 6: a mailbox ---
received sum: 55

--- Exercise 7: futures and an exception ---
slice 0: mean 125.5
slice 1: mean 375.5
slice 2: empty slice
slice 3: mean 750.5

--- Exercise 8: a thread pool ---
sum of squares 1..1000: 333833500
```

The solution was also run under ThreadSanitizer (GCC and Clang, with the oneTBB suppressions of 19.12) and is clean. When one of *your* answers gives a wrong number, build it with `-fsanitize=thread` and let the tool tell you where the race is.

The quiz has 20 questions on the whole chapter: execution policies and the oneTBB trap, threads and `jthread`, data races, mutexes and deadlock, atomics, condition variables, futures, latches and semaphores, the pool and the logger, ThreadSanitizer, and the Mandelbrot project. See `QUIZ.md` in the assignment folder.

That is the last chapter of the course. You started with how a program is built, went down to the instructions the processor runs, and came back up through classes, templates, modules, coroutines and threads. The tools of this chapter are the sharpest in the box: the reward is a program that uses the whole machine, the price is bugs that appear once a month. The habits that keep that price low are the ones this chapter kept repeating: **share nothing when you can, protect what you must, wrap every lock in an object, measure before you believe, and let a sanitizer read your code before your users do.**

**Code for this lecture**: `19.14Assignment/` (`main.cpp`, `main_solution.cpp`, `thread_pool.h`, `QUIZ.md`).
