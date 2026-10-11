# Chapter 19 Quiz - Parallel Algorithms and Concurrency

20 multiple-choice questions covering **Chapter 19**: execution policies, threads, data races, mutexes, atomics, condition variables, futures, latches and semaphores, the thread pool and logger, ThreadSanitizer and the Mandelbrot project. Each question is followed immediately by its correct answer and a short explanation.

---

### 1. What does passing `std::execution::par` to an algorithm such as `std::transform` mean?

A. The algorithm is guaranteed to use every core of the machine
B. The algorithm runs on a new thread and returns at once
C. The library is allowed to run the work on several threads, but it may still run it on one
D. The algorithm checks your function for data races first

**Answer: C** - a policy is a permission, not an order. For a small range, or on a system without a parallel backend, the library may run it on one thread. In 19.2 a 1,000-element transform was slower with `par` (0.4x on GCC and Clang, 0.1x on MSVC), because handing out the work cost more than the work.

### 2. With GCC or Clang on Linux, a program using `std::execution::par` compiles and runs, but is not faster than the sequential version. What is the most likely cause?

A. oneTBB is not installed or not linked, so every policy runs on one thread
B. `par` only works with `std::vector<double>`
C. The lambda must be marked `noexcept`
D. The compiler must be told `-fparallel`

**Answer: A** - libstdc++ needs oneTBB for the parallel algorithms (`apt-get install libtbb-dev`, and `TBB::tbb` in CMake). Without it, we measured `par` at 316 ms against 112 ms for the plain algorithm on 20 million elements; with it, 28 ms. MSVC has its own thread pool and needs nothing.

### 3. Why may `std::reduce` give a slightly different `double` result from `std::accumulate` on the same data?

A. `reduce` rounds every number first
B. `reduce` ignores the last element
C. `accumulate` is not exact for integers
D. `reduce` may add the elements in any order and grouping, and floating-point addition is not associative

**Answer: D** - `accumulate` goes strictly left to right, `reduce` is free to split the range and combine the pieces, so the operation must be associative and commutative. With integers the answer is always the same; with doubles it can differ in the last digits.

### 4. A function passed to `std::for_each(std::execution::par, ...)` throws an exception. What happens?

A. The exception is caught by the algorithm and rethrown at the call, as with a sequential algorithm
B. `std::terminate` is called, and the program ends
C. The exception is ignored and the loop continues
D. Only the thread that threw stops, and the others finish

**Answer: B** - we tried it on MSVC, GCC and Clang: all three ended the program (the sequential call of the same code was caught normally). Parallel algorithms need functions that do not throw.

### 5. What happens if a `std::thread` that is still joinable is destroyed?

A. `std::terminate` is called
B. The thread is joined automatically
C. The thread is detached and keeps running
D. The thread is cancelled and its destructors run

**Answer: A** - the library refuses to guess whether you wanted `join()` or `detach()`. `std::jthread` removes the problem: its destructor requests a stop and joins.

### 6. `std::thread t{sum_slice, std::cref(readings), 0, 500, std::ref(result)};` Why are `std::cref` and `std::ref` needed?

A. They make the thread run faster
B. They are required for every argument of every thread
C. The thread copies its arguments, so a reference parameter would silently bind to a copy; `ref` and `cref` pass a real reference
D. Without them the thread cannot start

**Answer: C** - the constructor stores a copy of each argument inside the new thread (the compiler refuses a plain `double&` parameter). With `std::ref(result)` the thread writes into the variable of the starter, which reads it after `join()`.

### 7. A function takes `std::stop_token` as its first parameter and is started with `std::jthread`. What does the `jthread` do?

A. Nothing: you must create the token yourself
B. It passes a stop token to the function, and calling `request_stop()` on the `jthread` sets it
C. It stops the thread by force when the token is set
D. It starts the function twice, once per token

**Answer: B** - the token is passed automatically. The thread is *asked* to stop and checks `token.stop_requested()` (or waits with the token, as in 19.7). It is never killed from outside, because that would skip its destructors.

### 8. Which situation is a data race?

A. Four threads reading the same `const` vector
B. Each of four threads writing its own element of a pre-sized vector
C. A thread that locks a mutex, changes a variable and unlocks
D. One thread writing an `int` while another reads it, with nothing ordering the two

**Answer: D** - a data race needs two threads accessing the same memory location, at least one of them writing, and no synchronization. It is undefined behavior, not just "a slightly wrong number".

### 9. Four threads each did `++counter` one million times on a plain `int`. The result was about a quarter of 4,000,000 in an unoptimized build. In an optimized build, GCC and Clang printed exactly 4,000,000. What does this show?

A. The race exists in every build; the optimized code only happened to hide it (MSVC `/O2` printed 1,000,000)
B. Optimizing removes data races
C. GCC and Clang are thread safe and MSVC is not
D. The first result was a bug of `std::jthread`

**Answer: A** - `++counter` is three steps (read, add, write back), and threads can interleave between them and lose updates. An optimizer is allowed to turn the loop into one addition, which makes the window tiny, or to keep the counter in a register; the program is still wrong.

### 10. Why use `std::scoped_lock lock{from.mutex, to.mutex};` for a transfer between two accounts?

A. It is faster than `lock_guard`
B. It unlocks the mutexes early
C. It locks all the mutexes in one step with an algorithm that cannot deadlock, whatever order they are listed in
D. It makes the accounts atomic

**Answer: C** - two threads that lock `a` then `b` and `b` then `a` can each end up holding one mutex and waiting for the other. In 19.5 both threads gave up after 200 ms with the hand-ordered version; the `scoped_lock` version completed.

### 11. What is the classic recipe for a deadlock?

A. Two threads waiting on the same condition variable
B. Two threads that each hold one mutex and wait for the one the other holds, because they lock in opposite orders
C. A mutex that is locked and never used
D. A thread that calls `join()` twice

**Answer: B** - circular waiting. The cures are to lock several mutexes together (`std::scoped_lock`) or in the same order everywhere, and to keep critical sections short.

### 12. When is `std::atomic<int>` the right tool, and when is it not?

A. Always: it replaces every mutex
B. Only for `bool`
C. Only for variables that are never changed
D. For a single variable that must be updated safely; it cannot protect an invariant that involves several variables

**Answer: D** - in 19.6 the atomic counter took about 50 ms against 111 to 254 ms for the mutex version. But "north + south == total" involves three variables, and making each one atomic does not make the group consistent: that needs a mutex.

### 13. What is `compare_exchange_weak` used for in `record_peak`?

A. To update the shared maximum safely: "if it still holds what I saw, replace it; otherwise load the current value and try again"
B. To compare two atomics for equality
C. To swap two threads
D. To wait for another thread

**Answer: A** - an atomic has no "maximum" operation, and "read, compare, write" is three steps another thread can interleave with. The compare-and-exchange loop makes the last two steps one indivisible step.

### 14. Why must you pass a condition to `condition_variable::wait`, as in `cv.wait(lock, [this] { return !items_.empty(); })`?

A. It makes the wait faster
B. It is only needed with `notify_all`
C. A thread can wake up with nothing to do (a spurious wakeup) or find another thread took the item first, so it must re-check; and a notify that came before the wait would otherwise be lost
D. Without it the mutex is never unlocked

**Answer: C** - `wait` checks the condition, and if it is false unlocks the mutex and sleeps; when woken it locks the mutex again and checks again. The condition is the thing that is true, the notification is only a nudge.

### 15. What is surprising about discarding the `std::future` returned by `std::async`?

A. Nothing, the work is simply cancelled
B. The work runs twice
C. The program terminates
D. The destructor of that future waits for the work, so two discarded calls run one after the other

**Answer: D** - we measured 201 ms for two 100 ms calls whose futures were thrown away, and 100 ms when the futures were kept so that both calls overlapped. A future from a `packaged_task` (as in the thread pool) does not wait in its destructor.

### 16. Which tool fits "no more than two uploads at the same time"?

A. `std::latch`
B. `std::counting_semaphore` with two tickets
C. `std::barrier`
D. `std::atomic_flag`

**Answer: B** - each upload acquires a ticket and releases it when done. A latch is a one-time countdown ("wait until all workers have finished"), and a barrier is a meeting point reused round after round.

### 17. Why does the queue of `ThreadPool` store `std::move_only_function<void()>` instead of `std::function<void()>`?

A. A `std::packaged_task` can be moved but not copied, and `std::function` requires a copyable callable
B. `std::function` cannot call lambdas
C. `move_only_function` runs faster on every thread
D. `std::function` is not allowed in a class

**Answer: A** - `submit` wraps the job in a `packaged_task` so that the result or exception goes into a future. That task is move-only, and `std::move_only_function` (C++23) is the type-erased callable that accepts it.

### 18. What does the `Logger` of 19.11 gain from having ONE writer thread?

A. The messages are sorted by time
B. Messages are never lost, even when the program crashes
C. The callers do not wait for the slow write, the sink is never used by two threads at once, and each thread's lines keep their order
D. The lines are written in parallel

**Answer: C** - callers only lock and push a string. The test in 19.11 checked that each station's lines came out in the order it logged them (the order *between* stations is arbitrary), and that nothing was lost when the logger was destroyed.

### 19. ThreadSanitizer reported `lock-order-inversion (potential deadlock)` for two transfers that ran one after the other and finished normally. Why, and where can you use it?

A. It is a false alarm; the program cannot deadlock
B. It simulates a hang by pausing the threads
C. It only reports problems that actually happened in this run
D. It records the order in which mutexes are locked and reports a cycle, even if this run did not hang; it exists for GCC and Clang on Linux (and Clang on macOS), but not for MSVC

**Answer: D** - TSan reports the danger, not only the accident. That is its strength: it finds races and lock cycles without waiting for the unlucky timing. On Windows, run the lecture in Docker or WSL.

### 20. In the Mandelbrot project, one fixed band of rows per thread was about half as fast as `std::execution::par` or a pool with a job per row, with the same result. Why?

A. Threads cannot share a `Canvas`
B. The rows in the middle of the picture contain points of the set that take all the iterations, so the threads with those bands finish long after the others, which sit idle
C. `std::jthread` is slower than `std::thread`
D. The bands were written with a mutex

**Answer: B** - the work per row is uneven. Many small jobs balance themselves: a worker that got cheap rows simply takes more of them. We measured speedups of about 16x for `par`, 13 to 16x for the pool and 8x for the bands on 20 hardware threads.
