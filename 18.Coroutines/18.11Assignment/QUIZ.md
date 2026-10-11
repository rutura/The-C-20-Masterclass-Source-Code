# Chapter 18 Quiz - Coroutines

20 multiple-choice questions covering **Chapter 18 (Coroutines)**: what a coroutine is, `std::generator`, the frame, promise and handle, awaiters, a lazy task, lifetime pitfalls and a round-robin scheduler. Each question is followed immediately by its correct answer and a short explanation.

---

### 1. What makes a function a coroutine?

A. Its return type is `std::generator`
B. Its body contains `co_await`, `co_yield` or `co_return`
C. It is declared `constexpr`
D. It is called from `main`

**Answer: B** - the keywords in the body are what turn a function into a coroutine. The return type then has to describe what the coroutine is (`std::generator<int>`, a `Task<int>`, ...), but a function that merely returns a `std::generator` (and has no such keyword in its body) is an ordinary function.

### 2. What happens when you call a coroutine that returns `std::generator<int>`, before looping over the result?

A. The whole body runs and the values are stored in a vector
B. The first value is computed and thrown away
C. The call blocks until somebody resumes it
D. The frame is created and the call returns; none of the body has run yet

**Answer: D** - in 18.2 the output "main: the generator exists, nothing has run" came before any line of the body. The coroutine starts paused (`initial_suspend`), and each step of the loop resumes it.

### 3. In `for (int value : countdown(2))`, what does each step of the loop do?

A. Resumes the coroutine until its next `co_yield`, or until it ends
B. Starts a new copy of `countdown` with a smaller number
C. Calls `countdown` again from its first line
D. Waits for a second thread to produce the next value

**Answer: A** - `++` on the generator's iterator is a `resume()`. The conversation in 18.2 alternates between the loop body and the coroutine: "giving 2", "received 2", "resumed after 2", and so on, all on one thread.

### 4. A coroutine is paused at a `co_await` and nobody ever resumes it or destroys its frame. What happens to its local variables?

A. They are destroyed when `main` returns
B. They are destroyed at once, because the coroutine lost its owner
C. Nothing: their destructors never run, so objects such as a database connection are never closed
D. The compiler reports an error

**Answer: C** - a local lives in the frame until the coroutine finishes or the frame is destroyed. In 18.8 the line "database connection closed" was never printed for the unowned `Job`, while the same coroutine inside a `Task` printed it, because the `Task`'s destructor destroyed the frame.

### 5. Why does `sensor() | std::views::filter(...) | std::views::take(4)` finish, although `sensor()` never ends?

A. Because `sensor` stops after 100 values
B. Because everything is lazy: values are pulled one by one, and `take(4)` stops asking after four
C. Because `filter` runs the generator to the end first
D. It does not finish: it runs out of memory

**Answer: B** - a generator is a range, so the views of chapter 15 attach to it. Each element is produced only when the loop asks for it, so a pipeline over an endless sequence is fine as long as something ends it.

### 6. A loop over a generator ends early with `break`. The coroutine has a local object whose destructor prints "link closed". What happens?

A. "link closed" is printed when the generator is destroyed, after the loop
B. It is never printed, because the coroutine did not finish
C. It is printed at once, at the `break`
D. The program terminates

**Answer: A** - destroying a paused coroutine destroys its live locals. In 18.3 the output "hour 2", then "[link] closed", then "after the loop" showed it: cleanup (RAII) still happens when the caller stops early.

### 7. Where does a coroutine's frame normally live, and what does it hold?

A. On the stack of the caller, holding only the return value
B. In a register, holding the current line number
C. In static memory, shared by all calls
D. On the heap, holding the parameters, the local variables, the promise and the point where it is paused

**Answer: D** - the frame has to survive after the call returns, so it is allocated on the heap (an optimizer may remove the allocation when it can prove the coroutine does not outlive the caller). In 18.4 the frame took 104 bytes with GCC, 120 with Clang and 400 with unoptimized MSVC.

### 8. A promise type's `initial_suspend()` returns `std::suspend_always`. What does that mean?

A. The coroutine runs to its end and never pauses
B. The coroutine pauses every time it is resumed
C. The coroutine pauses before its first line, so the caller decides when it starts (it is lazy)
D. The coroutine can only be resumed once

**Answer: C** - with `std::suspend_never` the coroutine would start at once (the `Job` of 18.6). `Task` and `Generator` use `suspend_always`, which is why nothing runs until the first `resume()`.

### 9. Why do `Generator` and `Task` return `std::suspend_always` from `final_suspend()`?

A. To make the program run faster
B. So the frame is still alive after the body ends, and the owner can ask `done()`, read the result, and then destroy it
C. To resume the coroutine a second time
D. Because `final_suspend` must always return the same type

**Answer: B** - if the coroutine destroyed its own frame at the end, `done()` and the stored result would be gone. The owner (the `Task` or `Generator` object) destroys the frame in its destructor.

### 10. What does `co_yield value;` turn into?

A. A `return value;` that ends the coroutine
B. A call to `std::println`
C. A call to `resume()`
D. `co_await promise.yield_value(value);`

**Answer: D** - that is how the promise decides what to do with the value (our `Generator` stores its address) and whether to pause (it returns `std::suspend_always`). `co_yield` is just a convenient spelling of a `co_await` on the promise.

### 11. For `co_await thing;`, what does it mean when the awaiter's `await_ready()` returns `true`?

A. There is nothing to wait for, so the coroutine does not pause and carries on
B. The coroutine has finished
C. The coroutine must be destroyed
D. An exception is about to be thrown

**Answer: A** - `await_ready()` is the first question: "can I skip the pause?". `std::suspend_never` is the awaiter whose `await_ready()` is always `true`, and `std::suspend_always` is the one that is always `false`.

### 12. `await_suspend` of an awaiter returns `bool`, and it returns `false`. What happens?

A. The coroutine is destroyed
B. The program waits for another thread
C. The coroutine is not suspended after all and carries on at once
D. The coroutine is resumed twice

**Answer: C** - this is the `Door` of 18.6. An open door returned `false` from `await_suspend`, so the coroutine walked "through the door" immediately; a closed door returned `true` and parked the handle.

### 13. Where does the value of the expression `int answer{co_await Traced{}};` come from?

A. From the return value of `await_suspend`
B. From the return value of `await_resume`
C. From the return value of `await_ready`
D. From the promise's `return_value`

**Answer: B** - after the coroutine is resumed, the compiler calls `await_resume()`, and what it returns is the value of the whole `co_await` expression. The traced awaiter returned 42, and `answer` was 42.

### 14. You create a lazy `Task<int>` and never `co_await` it or call `get()`. What happens?

A. Nothing runs, and the task's destructor destroys the frame
B. The body runs when the task goes out of scope
C. The body runs on another thread
D. The program does not compile

**Answer: A** - in 18.7 `Task<int> unused{measure("west", 30)};` printed only "created and thrown away". Laziness is the point: the description of the work exists, the work does not happen until somebody asks.

### 15. Why does `FinalAwaiter::await_suspend` return the continuation's `std::coroutine_handle<>` instead of calling `resume()` on it?

A. Because `resume()` is private
B. To copy the result into the continuation
C. To make the task run in parallel with its caller
D. So the waiting coroutine is resumed by a jump (symmetric transfer) and a long chain of tasks does not use more and more stack

**Answer: D** - returning a handle from `await_suspend` means "resume that one instead". With a nested call, each finished task would leave a stack frame behind until the whole chain ended.

### 16. A chain of one million `co_await one()` calls crashed with GCC in a default (unoptimized) build, but worked with MSVC and Clang. Why, and what fixes it?

A. GCC does not support coroutines
B. The `Task` class is not copyable
C. GCC turns the symmetric-transfer jump into a real jump only when it optimizes sibling calls, so `-O2` or `-foptimize-sibling-calls` fixes it
D. The counter overflows

**Answer: C** - we measured it: `-O0`, `-Og` and `-O1` crashed (stack overflow), `-O2` worked, `-O0 -foptimize-sibling-calls` worked, and `-O2 -fno-optimize-sibling-calls` crashed again. `rooster2` of 18.7 adds the flag for GCC.

### 17. A task's body throws. Where does the exception come out?

A. The program terminates at once
B. It is stored by `unhandled_exception()` as a `std::exception_ptr`, and rethrown where the result is read: in the coroutine that does `co_await`, or in `get()`
C. It is ignored
D. It is thrown inside `final_suspend`

**Answer: B** - `std::current_exception()` captures it, `std::rethrow_exception()` throws it again. That is why a `try` / `catch` around a `co_await` in 18.7 caught the exception of the awaited task.

### 18. `Task<void> greet(const std::string& name)` is called as `greet("a long station name")` and the task runs later. What is wrong?

A. Nothing, a `const` reference is always safe
B. Coroutines cannot take string parameters
C. The string is copied twice
D. The frame stores only the reference; the temporary string it refers to is destroyed at the end of the statement, so the coroutine reads freed memory. Take the parameter by value

**Answer: D** - AddressSanitizer reported `stack-use-after-scope` on GCC, Clang and MSVC. A by-value parameter is copied into the frame, so it lives as long as the coroutine does.

### 19. Why is a lambda that is itself a coroutine, and captures a variable, dangerous when it is called right away as a temporary?

A. The captures live in the closure object, not in the coroutine frame, and the temporary closure is destroyed at the end of the statement while the coroutine still uses it
B. Lambdas cannot contain `co_await`
C. Captured variables are always copied twice
D. The compiler removes the captures

**Answer: A** - the fix is to pass the data as a parameter of the lambda: parameters are copied into the frame. The sanitizer saw the unfixed version read a destroyed `std::string` (`stack-use-after-scope`).

### 20. In the round-robin scheduler of 18.9, when does the scheduler switch from one task to another?

A. Every millisecond, using a timer
B. After every `std::println`
C. Only when the running task does a `co_await` that parks it, such as `co_await scheduler.yield_now()`; a task that never awaits keeps the thread until it ends
D. After every line of the coroutine

**Answer: C** - that is cooperative multitasking. The `greedy` worker, which never yielded, printed all its steps in a row. It also means the tasks of one scheduler share one thread, and cannot be interrupted at an unexpected place.
