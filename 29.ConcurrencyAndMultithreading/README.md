# Chapter 29: Concurrency & Multithreading

## Why this chapter exists

Every program up to this point runs one instruction at a time. This chapter
introduces the language's tools for doing more than one thing at once:
threads that genuinely run alongside each other, the synchronization
primitives that keep them from corrupting shared data, and coroutines - a
different, single-threaded way of pausing and resuming code on demand that
threads and generators alike are built on top of. Threads and coroutines are
both "run more than one logical task at a time" tools, which is why this
chapter folds in the existing Coroutines lectures (previously their own
short, 5-lecture chapter) as its closing section, right where `ref2`
(Deitel) sequences the same two ideas.

## What a program like this actually needs

| Need | Example | C++ tool |
|---|---|---|
| Run something alongside main() | logging while doing other work | `std::jthread` |
| Give a thread its own state/data to work with | a worker that needs a captured value | lambdas / function objects passed to `std::jthread` |
| Understand what goes wrong with shared data | two threads incrementing the same counter | race conditions (the motivating problem) |
| Protect shared data one thread at a time | fixing the race condition | `std::mutex` + `std::lock_guard` |
| Lock more flexibly, or lock several mutexes without deadlock | a bank transfer touching two accounts at once | `std::unique_lock`, `std::scoped_lock` |
| Update a single value safely without a lock | a lock-free counter | `std::atomic` |
| Wait efficiently for another thread's signal | a producer/consumer queue | `std::condition_variable` |
| Get a result back from a thread | running work and collecting its answer later | `std::future`/`std::promise`, `std::async` |
| Pause and resume a function on demand | a lazy sequence of values | coroutines (`co_await`/`co_yield`/`co_return`) |

## Lecture by lecture

**Threads**
- **29.2 Creating Threads** - `std::jthread` as the modern default over raw
  `std::thread`, since it joins automatically in its destructor.
- **29.3 Threads with Lambdas and Function Objects** - the two idiomatic
  ways to give a thread work: a capturing lambda, or a function object with
  its own state.
- **29.4 Race Conditions** - a deliberately broken, unsynchronized counter
  increment across several threads, as the motivating problem the rest of
  the chapter fixes.

**Synchronization**
- **29.5 Mutex and Lock Guard** - `std::mutex` + `std::lock_guard` fixing
  29.4's race condition, one thread at a time.
- **29.6 Unique Lock and Scoped Lock** - `std::unique_lock` for deferred/
  manual locking, `std::scoped_lock` for locking several mutexes together
  without risking deadlock (a two-account transfer running in both
  directions at once).
- **29.7 Atomics** - `std::atomic` as a lock-free fix to the same 29.4
  counter, plus `compare_exchange_strong` as the building block behind
  lock-free algorithms.
- **29.8 Condition Variables** - a small producer/consumer queue, waiting
  efficiently instead of busy-checking a flag in a loop.

**Results & higher-level concurrency**
- **29.9 Futures, Promises, and Async** - `std::async` for the common case
  of "run this and get a result back later," `std::promise`/`std::future`
  for the manual producer/consumer pair, and how an exception thrown on a
  worker thread propagates through `.get()`.

**Coroutines**
- **29.10 CoAwait** - what a coroutine is, and the minimal `promise_type`
  needed to make `co_await` pause and resume a function.
- **29.11 CoYield** - producing a value at each pause point.
- **29.12 CoReturn** - ending a coroutine, and the `return_void`/
  `return_value` choice (never both) a `promise_type` has to make.
- **29.13 Custom Generator** - turning the chapter's `CoroType` into a
  reusable `generator<T>` class template, driving a bounded sequence.
- **29.14 Third-Party Coroutine Types** - `unique_generator<T>` (adapted
  from a real external reference implementation - see the attribution
  comment in `unique_generator.h`), adding proper `begin()`/`end()`
  iterators so a generator can be used in an ordinary range-based `for`
  loop.

## How C++'s latest features help

- **`std::jthread`** (C++20) removes the single most common
  `std::thread` bug - forgetting to `join()` before the thread object is
  destroyed (which terminates the program) - by joining automatically.
- **`std::scoped_lock`** (C++17) locks multiple mutexes together in a
  deadlock-free order, replacing the older, easy-to-get-wrong pattern of
  locking each mutex individually and hoping every thread does it in the
  same order.
- **`std::atomic`** gives lock-free correctness for simple shared updates,
  without the cost of blocking every other thread the way a mutex does.
- **Coroutines** (C++20) are a language feature, not a library type - the
  compiler itself rewrites a `co_await`/`co_yield`/`co_return`-using
  function into something that can suspend and resume, which is what makes
  writing a `generator<T>` from scratch possible at all.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. Every threading lecture (29.2-29.9) additionally links the
platform's thread library via `find_package(Threads REQUIRED)` +
`target_link_libraries(rooster PRIVATE Threads::Threads)` - already wired
up in each lecture's `CMakeLists.txt`, but worth knowing about if you copy
one of these examples elsewhere. If you don't have a C++23 compiler
installed locally, use one of the ready-made Docker images in
[`../docker`](../docker) - see that folder's README for exact commands.
