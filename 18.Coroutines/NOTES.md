# Coroutines

Every function you have written so far follows one rule: it starts at the top, runs to the bottom (or to a `return`), and its local variables are gone. If you call it again, it starts over. A **coroutine** breaks that rule. It is a function that can **stop in the middle**, hand something to its caller, and later **continue from the same line**, with its local variables still there.

```
   a function                              a coroutine

   call ──► line 1                         call ──► line 1
            line 2                                  line 2
            line 3                                  co_yield 7  ──► caller gets 7, coroutine WAITS
            line 4 ── return ──► caller             ...
            (locals destroyed)                      resume ──► line 3   (locals still alive)
                                                    line 4
                                                    co_return   ──► finished
```

What is this good for? Anywhere code is naturally "produce a bit, wait, produce some more":

- a **sequence** that is computed on demand, even an endless one (a sensor, a file read line by line)
- work that has to **wait** for something (a file, a timer, another job), written as straight-line code instead of callbacks
- **many jobs sharing one thread**, taking turns

This chapter is organized by what the compiler does for you, and what it does not. C++20 added the language feature, but only the **keywords** (`co_yield`, `co_await`, `co_return`) and a few building blocks. A coroutine's return type, the thing that says what the coroutine *is*, was left to libraries. C++23 added the first ready-made one, `std::generator`. For everything else you write the type yourself, and that is where the chapter spends its time.

1. **Functions that pause** (18.2): the idea, as a hand-written state machine and as a coroutine.
2. **`std::generator`** (18.3): lazy sequences, endless ones, pipelines, recursion, and cleanup.
3. **The frame, the promise and the handle** (18.4): what the compiler builds, with every call printed.
4. **Writing your own generator** (18.5): a small `Generator<T>` that you can read in one sitting.
5. **`co_await` and awaiters** (18.6): the three-question protocol behind every pause.
6. **A lazy task** (18.7): `Task<T>`, one result later, awaiting other tasks.
7. **Lifetime pitfalls** (18.8): four bugs, found by the sanitizer, and their fixes.
8. **A round-robin scheduler** (18.9): many tasks, one thread, taking turns.
9. A **project** (18.10): the log analyzer of chapters 14 and 15, rebuilt as a lazy pipeline of generators with three jobs on a scheduler.

The running example is the weather station. It has shown up as readings, reports and logs, and here it supplies the sequences and the jobs.

## What works where

Everything was built and run on MSVC 19.51, GCC 16, Clang 21, and also with the MinGW compilers (GCC 14.2 and Clang 19.1) where it applies. The programs print identical output.

| | MSVC | GCC 16 | Clang 21 | MinGW GCC 14.2 | MinGW Clang 19.1 |
|---|---|---|---|---|---|
| `<coroutine>`, your own types (18.4 to 18.7, 18.9) | works | works | works | works | works (tested: 18.5, 18.7, 18.9) |
| `std::generator` (18.2, 18.3, 18.8, project, assignment) | works | works | works with libstdc++ (the Linux image) | works | **not available** |
| symmetric transfer in unoptimized builds | works | **needs a flag** (18.7) | works | **needs a flag** | not tested |
| AddressSanitizer inside a coroutine body (18.8) | **does not check it** | works | works | no sanitizer | no sanitizer |

Two notes. `std::generator` with Clang needs a standard library that has `<generator>`: the Linux image's libstdc++ does, libc++ 21 does not (`'generator' file not found`), and MinGW Clang 19.1 has no `std::generator`. On GCC, `<coroutine>` needs C++20 or later, which CMake's `CMAKE_CXX_STANDARD 23` gives. On MinGW remember `-lstdc++exp` for `std::println`.

---

## 18.2 Functions that pause

In this lecture we build the same thing twice: once with a class that remembers where it was, and once with a coroutine, so you see exactly what a coroutine saves you.

The weather station sends a report as lines: a title, one line per reading, and a closing line. We want to hand the lines out **one at a time**.

### The old way: a state machine

A function cannot do that, because after `return` it forgets everything. So we write a class that keeps the "where was I?" as data:

```cpp
class ReportLines {
public:
    explicit ReportLines(const std::vector<double>& readings) : readings_{readings} {}

    bool has_next() const { return phase_ != Phase::Finished; }

    std::string next() {
        switch (phase_) {
        case Phase::Title:
            phase_ = readings_.empty() ? Phase::Closing : Phase::Readings;
            return "station report";
        case Phase::Readings: {
            std::string line{std::format("reading {}: {} C", index_ + 1, readings_[index_])};
            ++index_;
            if (index_ == readings_.size()) {
                phase_ = Phase::Closing;
            }
            return line;
        }
        case Phase::Closing:
        default:
            phase_ = Phase::Finished;
            return "end of report";
        }
    }

private:
    enum class Phase { Title, Readings, Closing, Finished };

    const std::vector<double>& readings_;
    Phase phase_{Phase::Title};
    std::size_t index_{0};
};
```

It works, and look at the price: the *logic* of the report (a title, then a loop, then a closing line) is smeared across a `switch`, three phases and an index. Every extra step in the report makes it worse.

### The new way: a coroutine

```cpp
std::generator<std::string> report_lines(const std::vector<double>& readings) {
    co_yield "station report";
    std::size_t number{1};
    for (double celsius : readings) {
        co_yield std::format("reading {}: {} C", number, celsius);
        ++number;
    }
    co_yield "end of report";
}
```

The same logic, in the order you would explain it to a person. **`co_yield value;`** hands `value` to the caller and **pauses right there**. The next time the caller asks, the function continues on the next line. The compiler writes the class above for you: "which `co_yield` am I stopped at" is the phase, and `number` is an ordinary local variable that simply stays alive.

You use it like any sequence:

```cpp
for (const std::string& line : report_lines(readings)) {
    std::println("{}", line);
}
```

```
station report
reading 1: 18.5 C
reading 2: 24 C
reading 3: 21.5 C
end of report
```

The by-hand and the coroutine versions print exactly the same.

### Who runs when

Calling a coroutine does **not** run its body. It builds the pausable function and returns at once, before the first line. Each step of a loop then resumes it until the next `co_yield`. To see the conversation, here is a countdown that prints around every pause:

```cpp
std::generator<int> countdown(int from) {
    for (int value{from}; value > 0; --value) {
        std::println("  [countdown] giving {}", value);
        co_yield value;
        std::println("  [countdown] resumed after {}", value);
    }
    std::println("  [countdown] reached the end");
}
```

```
main: the generator exists, nothing has run
  [countdown] giving 2
main: received 2
  [countdown] resumed after 2
  [countdown] giving 1
main: received 1
  [countdown] resumed after 1
  [countdown] reached the end
main: the loop is over
```

Read it as a conversation between two functions on **one thread**. There is no parallelism and no waiting for another thread: `main` runs, the coroutine runs, `main` runs again. A coroutine is control flow, not concurrency.

### The three keywords

| keyword | meaning |
|---|---|
| `co_yield value;` | give a value to the caller and pause (18.3) |
| `co_await thing;` | pause until `thing` is ready (18.6) |
| `co_return value;` | finish, optionally with a final value (18.7) |

**Any one of them in the body makes the function a coroutine.** The return type then decides what the coroutine *is*: `std::generator<int>` means "a sequence of ints". In 18.4 and 18.5 we write such a type ourselves.

### The pattern to remember

> **A coroutine is a function that can pause at `co_yield` or `co_await` and continue later with its locals intact. Calling it does not run it.**

**Code for this lecture**: `18.2FunctionsThatPause/`.

---

## 18.3 `std::generator`

In this lecture we use the one ready-made coroutine type of C++23: `std::generator<T>`, a **sequence of `T` values produced one at a time, only when somebody asks**.

### An endless sequence

Nothing can hold an endless list of readings in memory. A generator can, because it never "has" the rest:

```cpp
std::generator<double> sensor() {
    unsigned state{12345};
    while (true) {
        state = state * 1103515245u + 12345u;
        double fraction{static_cast<double>((state >> 16) % 1000) / 1000.0};
        co_yield 10.0 + 20.0 * fraction;
    }
}
```

The loop never ends, and that is fine: it is paused at `co_yield` most of the time. (The arithmetic is a simple pseudo-random step, written by hand so the numbers are the same on every compiler.)

```cpp
int shown{0};
for (double celsius : sensor()) {
    std::println("{:.1f}", celsius);
    if (++shown == 3) {
        break;
    }
}
```
```
14.7
25.1
27.7
```

### A generator is a range

A `std::generator` has `begin()` and `end()`, so it is a **range** (14.2), and the views of chapter 15 attach to it. Views are lazy too, so even a pipeline over an endless sequence is fine, as long as something ends it:

```cpp
auto hot{sensor()
    | std::views::filter([](double celsius) { return celsius > 25.0; })
    | std::views::take(4)};
for (double celsius : hot) {
    std::println("{:.1f}", celsius);
}
```
```
25.1
27.7
27.8
25.2
```

`take(4)` stops asking after four values. `std::ranges::to<std::vector>()` (15.10) also works to collect a finite part:

```cpp
auto mild{sensor() | std::views::take(6)
                   | std::views::transform([](double celsius) { return celsius - 10.0; })
                   | std::ranges::to<std::vector>()};
// 6 values, first 4.7, last 0.9
```

### Yielding references

`std::generator<std::string>` would copy every string it yields. Writing the type as `std::generator<const std::string&>` makes it yield a **reference**, so the caller reads the string where it already lives. That is safe because the coroutine is paused while the caller looks at it. (The other half of this safety, what can go wrong, is 18.8.)

### Recursion: `std::ranges::elements_of`

A recursive generator needs a way to say "yield everything that this other generator produces". That is `co_yield std::ranges::elements_of(...)`. The station network is a tree:

```cpp
struct Node {
    std::string name;
    std::vector<Node> children;
};

std::generator<const std::string&> names(const Node& node) {
    co_yield node.name;
    for (const Node& child : node.children) {
        co_yield std::ranges::elements_of(names(child));
    }
}
```
```
network
north
hill
valley
south
coast
```

A depth-first walk in four lines. The hand-written version needs an explicit stack.

### Cleanup runs, even when the caller stops early

What if the loop leaves before the generator is finished? The coroutine is paused in the middle, with live locals. Destroying the generator **destroys the paused coroutine, and its live locals are destroyed**, so their destructors run. That is RAII (10.6) doing its job:

```cpp
struct Link {
    Link() { std::println("  [link] opened"); }
    ~Link() { std::println("  [link] closed"); }
};

std::generator<int> hourly() {
    Link link;
    for (int hour{0}; hour < 24; ++hour) {
        co_yield hour;
    }
}

for (int hour : hourly()) {
    std::println("hour {}", hour);
    if (hour == 2) {
        break;
    }
}
std::println("after the loop");
```
```
  [link] opened
hour 0
hour 1
hour 2
  [link] closed
after the loop
```

The link is closed when the temporary generator dies at the end of the loop, after the `break`.

### Exceptions

An exception thrown inside the generator comes out **at the caller**, in the loop step that resumed it:

```
value 10
value 20
caught: the sensor stopped answering
```

### Two rules

- A generator is **single-pass**: you can walk it once, from the start. Asking for `begin()` a second time is not allowed.
- It is **move-only**, like a `std::unique_ptr` (9.10): it owns the paused function, and there is only one.

### The pattern to remember

> **`std::generator<T>` is a lazy, single-pass range of `T`. Use it whenever you would otherwise write a state machine that hands out one item at a time.**

**Code for this lecture**: `18.3StdGenerator/`.

---

## 18.4 The frame, the promise and the handle

In this lecture we open the box. What does the compiler build when it sees a coroutine, and what can *you* control? To find out we write the smallest possible coroutine type and make every function in it print a line.

### Three things

```
   caller                                heap
   ------                                -----------------------------
   StationDay  (the return object)  -->  | frame                     |
     holds a coroutine_handle            |   promise  (promise_type) |
                                         |   parameters and locals   |
                                         |   "where am I paused?"    |
                                         -----------------------------
```

- The **frame** is a block of memory, normally on the **heap**, that keeps the coroutine's parameters and locals alive while it is paused. The frame is why locals survive a pause.
- The **promise** is an object **inside the frame**. The coroutine talks to the outside world through it. **You write its type** (it must be called `promise_type` and live inside the return type), and the compiler calls its member functions at fixed moments.
- The **handle**, `std::coroutine_handle<promise_type>`, is a small pointer-like object that the outside world uses to `resume()` the coroutine, ask `done()`, or `destroy()` the frame.

The return type, `StationDay` here, is what the caller holds. It owns the handle and is responsible for destroying the frame (RAII, 10.6).

### The smallest coroutine type

```cpp
class StationDay {
public:
    struct promise_type {
        StationDay get_return_object() {
            return StationDay{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { throw; }
    };

    StationDay(StationDay&& other) noexcept : handle_{std::exchange(other.handle_, nullptr)} {}
    ~StationDay() { if (handle_) handle_.destroy(); }
    void resume() { handle_.resume(); }
    bool done() const { return handle_.done(); }
    // (copying is deleted)

private:
    explicit StationDay(std::coroutine_handle<promise_type> handle) : handle_{handle} {}
    std::coroutine_handle<promise_type> handle_;
};
```

Five members of the promise are required, and each is called at a fixed moment:

| promise member | called |
|---|---|
| `get_return_object()` | right after the frame exists, to build what the caller will receive |
| `initial_suspend()` | before the first line: `suspend_always` = pause (be lazy), `suspend_never` = run at once |
| `return_void()` | when the body ends without a value (`co_return;` or falling off the end) |
| `unhandled_exception()` | when an exception leaves the body; `throw;` hands it to whoever called `resume()` |
| `final_suspend()` | after the body: pausing here keeps the frame alive so the owner can ask `done()` and read results |

`std::suspend_always` is a ready-made type in `<coroutine>` that means "yes, pause here". It is an *awaiter*, the subject of 18.6.

The promise may also have `operator new` and `operator delete`. These are the functions that a `new` expression calls underneath to get and give back raw memory (9.9), and a class may supply its own versions. The compiler asks the promise's `operator new` for the memory of the frame, if it has one. Ours exist only to print a line, so you can see the frame being allocated and released.

### Watching the whole life

The coroutine, with a local that announces itself:

```cpp
StationDay record_day(std::string station) {
    Noisy sensor{"sensor of " + station};
    std::println("  body: start of the day at {}", station);
    co_await std::suspend_always{};
    std::println("  body: noon");
    co_await std::suspend_always{};
    std::println("  body: end of the day");
}
```

`co_await std::suspend_always{}` reads "pause here until somebody calls `resume()`". The output, the three `resume()` calls driven from `main`:

```
main: calling the coroutine
  frame: allocated on the heap
  promise: get_return_object
  promise: initial_suspend
main: the call returned; the body has NOT run
main: resume number 1
  sensor of north created
  body: start of the day at north
main: back in main, done() is false
main: resume number 2
  body: noon
main: back in main, done() is false
main: resume number 3
  body: end of the day
  sensor of north destroyed
  promise: return_void
  promise: final_suspend
main: back in main, done() is true
main: leaving the block
  ~StationDay: destroying the frame
  frame: released
main: finished
```

Read it top to bottom, it is the whole life story:

1. The frame is allocated, the promise is built inside it, and `get_return_object()` makes the object `main` receives.
2. `initial_suspend()` says pause, so the call **returns with the body not started**.
3. Each `resume()` runs the body to the next `co_await`. The local `sensor` is created only now, when the body starts, and it survives the pauses.
4. When the body ends, its locals are destroyed (**before** `return_void` and `final_suspend`), and `done()` becomes true.
5. The `StationDay` destructor destroys the frame, which releases the memory.

### How big is a frame?

We printed the `size` that `operator new` receives: **104 bytes with GCC, 120 with Clang, 400 with MSVC** (an unoptimized build, this exact coroutine). A frame is small, but it is one heap allocation per coroutine call, so a coroutine you call a million times has a cost. Compilers are allowed to **remove the allocation** when they can see that the coroutine does not outlive its caller (heap allocation elision), so an optimized build can be cheaper than what you see here.

### What must you never do

- **Resume a finished coroutine** (`done()` is true): undefined behavior.
- **Forget to destroy the frame**: the memory leaks, and (18.8) the locals' destructors never run.
- **Destroy it twice**: that is why `StationDay` is move-only and sets the moved-from handle to `nullptr`.

### The pattern to remember

> **A coroutine call builds a heap frame holding a promise and the locals. The return type owns a handle to it, resumes it, and destroys it. The promise's functions are called at fixed moments, and you write them.**

**Code for this lecture**: `18.4PromiseAndHandle/`.

---

## 18.5 Writing your own generator

In this lecture the coroutine type does a real job: a sequence of `T` values, like `std::generator<T>`, small enough to read in one sitting.

What is new compared to 18.4:

- `yield_value()` in the promise: called for every `co_yield`. It saves the value where the iterator can reach it and pauses.
- An **iterator**, so a range-based for loop (14.2) can drive the coroutine: `++` means "resume", and the end is "the coroutine is done".

```cpp
template <typename T>
class Generator {
public:
    struct promise_type {
        const T* current{nullptr};

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        // `co_yield x;` becomes `co_await promise.yield_value(x);`
        std::suspend_always yield_value(const T& value) {
            current = &value;
            return {};
        }

        void return_void() {}
        void unhandled_exception() { throw; }
    };
    ...
```

`co_yield x;` is turned into `co_await promise.yield_value(x);`. Ours stores the **address** of the value and returns `std::suspend_always` to pause. Storing the address is safe, because the coroutine is paused *inside* the `co_yield` expression: the operand (even a temporary) is still alive until the coroutine resumes.

### The end marker and the iterator

A range-based for loop needs a `begin()` and an `end()`. The end of a generator is not a position in a container, it is the state "the coroutine finished". A range-for loop accepts an end marker of **any** type, as long as `iterator == marker` compiles, so a tiny empty struct is enough (the standard library calls such a thing a *sentinel*):

```cpp
    struct EndMarker {};

    class Iterator {
    public:
        const T& operator*() const { return *handle_.promise().current; }

        Iterator& operator++() {
            handle_.resume();
            return *this;
        }

        bool operator==(EndMarker) const { return handle_.done(); }
        ...
    };

    Iterator begin() {
        handle_.resume();               // run to the first co_yield
        return Iterator{handle_};
    }
    EndMarker end() { return {}; }
```

`begin()` has a job to do: the coroutine starts paused, so `begin()` resumes it up to the first `co_yield`. That also explains why a generator can be walked **once**: a second `begin()` would resume it again.

The rest of the class is the owner's boilerplate from 18.4: a move constructor that steals the handle, a deleted copy, and a destructor that calls `destroy()`.

### Using it

```cpp
Generator<int> hours(int first, int last) {
    for (int hour{first}; hour <= last; ++hour) {
        co_yield hour;
    }
}

Generator<double> running_mean(const std::vector<double>& readings) {
    double total{0.0};
    int count{0};
    for (double celsius : readings) {
        total += celsius;
        ++count;
        co_yield total / count;
    }
}
```

`total` and `count` are the interesting part. They survive every pause, because they live in the frame and not on the stack of whoever resumed the coroutine.

```
--- hours
6:00
7:00
8:00
9:00

--- the running mean
18.50
21.25
21.33
19.12

--- strings
#1 18.5 C
#2 24.0 C
#3 21.5 C
#4 12.5 C

--- an endless one, stopped by the loop
1 1 2 3 5 8 13 21 34 55 89
```

The strings generator yields a temporary `std::format(...)` result, which is alive during the pause. The Fibonacci generator is endless and never finished: leaving the loop destroys the generator, and its destructor destroys the frame. Try removing `handle_.destroy()` and run it under AddressSanitizer on Linux (9.12): the four frames of this program are reported as leaked ("4 allocation(s)" with both GCC and Clang).

### Why use `std::generator` then?

Ours handles one thing. The standard one also works with views (`take`, `filter`), recursion with `elements_of`, references and allocators. We wrote ours to see that there is no magic: a promise, a handle, and an iterator that calls `resume()`.

### The pattern to remember

> **A generator type is a promise that saves the yielded value in `yield_value`, plus an iterator whose `++` is `resume()` and whose end is `done()`, plus an owner that destroys the frame.**

**Code for this lecture**: `18.5WritingYourOwnGenerator/`.

---

## 18.6 `co_await` and awaiters

In this lecture we meet the mechanism behind every pause: the **awaiter**, and the three questions the compiler asks it.

`co_await thing;` means "pause here until `thing` is ready". What "ready" means, and **who resumes the coroutine**, is decided by `thing`. It can be any type with three member functions:

```
   bool  await_ready()                      Is there anything to wait for?  true = no, carry on
   ...   await_suspend(coroutine_handle<>)   We are pausing now. Keep the handle, so someone can resume us
   T     await_resume()                     We are running again. What this returns is the value of the co_await
```

### The three questions, asked out loud

```cpp
std::coroutine_handle<> parked;      // where the traced coroutine leaves its handle

struct Traced {
    bool await_ready() const noexcept {
        std::println("  await_ready: nothing to wait for? no");
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle) const noexcept {
        std::println("  await_suspend: pausing, keeping the handle");
        parked = handle;
    }
    int await_resume() const noexcept {
        std::println("  await_resume: running again");
        return 42;
    }
};

Job traced_demo() {
    std::println("  coroutine: before the co_await");
    int answer{co_await Traced{}};
    std::println("  coroutine: the co_await produced {}", answer);
}
```

`Job` is the simplest coroutine type there is: the coroutine starts at once (`initial_suspend` returns `std::suspend_never`), destroys its own frame at the end (`final_suspend` also `suspend_never`), and the caller gets nothing back. Nobody can wait for it, ask if it is done, or read a result, which is fine for an example and nothing more. Lecture 18.7 builds a proper one.

```
main: calling the coroutine
  coroutine: before the co_await
  await_ready: nothing to wait for? no
  await_suspend: pausing, keeping the handle
main: it is paused; resuming it
  await_resume: running again
  coroutine: the co_await produced 42
```

The order: `await_ready` asks, `await_suspend` runs **as the coroutine pauses** (the handle is the coroutine itself; it is the moment to store it where someone will find it), and `await_resume` runs when the coroutine continues, and gives the value of the expression: `answer` is 42. This is the same `std::coroutine_handle` as in 18.4, now without the promise type in it (`std::coroutine_handle<>`).

The ready-made awaiters are the simplest possible:

```
   std::suspend_always    await_ready() is false: always pause
   std::suspend_never     await_ready() is true:  never pause
```

They are what `initial_suspend` and `final_suspend` returned in the earlier lectures: "should the coroutine pause here?"

### Deciding at the last moment

`await_suspend` may also return a `bool`. `true` means "stay paused", `false` means "I changed my mind, carry on at once":

```cpp
struct Door {
    bool open;

    bool await_ready() const noexcept { return false; }
    bool await_suspend(std::coroutine_handle<> handle) const noexcept {
        if (!open) {
            parked = handle;
        }
        return !open;
    }
    void await_resume() const noexcept {}
};
```
```
  coroutine: at the door (open)
  coroutine: through the door
main: the open door let it through at once
  coroutine: at the door (closed)
main: the closed door parked it; opening
  coroutine: through the door
```

Why not decide in `await_ready`? In a program with threads (chapter 19) the answer can change between "not ready" and the moment of pausing; `await_suspend` is where you re-check safely. A third form returns another `std::coroutine_handle<>`: "pause me, and resume **that** one instead". 18.7 uses it.

| `await_suspend` returns | meaning |
|---|---|
| `void` | pause, and give control back to whoever resumed us |
| `bool` | `true` = pause, `false` = carry on |
| `std::coroutine_handle<>` | pause, and resume that coroutine now |

### Waiting for time to pass

A real use. A clock that measures nothing: somebody calls `tick()`. A coroutine that wants to wait asks the clock for an awaiter, and the clock **remembers the handle together with the time to resume it**:

```cpp
class Clock {
public:
    struct WaitAwaiter {
        Clock& clock;
        int ticks;

        bool await_ready() const noexcept { return ticks <= 0; }
        void await_suspend(std::coroutine_handle<> handle) const {
            clock.waiting_.push_back({clock.now_ + ticks, handle});
        }
        void await_resume() const noexcept {}
    };

    WaitAwaiter wait(int ticks) { return WaitAwaiter{*this, ticks}; }

    void tick() {
        ++now_;
        // collect the due handles first: a resumed coroutine may wait again
        ...
        for (std::coroutine_handle<> handle : due) {
            handle.resume();
        }
    }
    ...
};

Job sampler(Clock& clock, std::string station, int every) {
    for (int reading{1}; reading <= 3; ++reading) {
        co_await clock.wait(every);
        std::println("t={}  {} takes reading {}", clock.now(), station, reading);
    }
}
```

Two samplers, "north" every 2 ticks and "south" every 3, and a loop of nine `tick()` calls in `main`:

```
t=2  north takes reading 1
t=3  south takes reading 1
t=4  north takes reading 2
t=6  south takes reading 2
t=6  north takes reading 3
t=9  south takes reading 3
```

Look at what we have: two functions that each "wait for time" in a plain loop, with no callbacks and no threads. Someone else (`main`, here) decides when time passes, and resumes whoever is due. **This is the heart of every coroutine runtime**: an awaiter that stores a handle, and a loop that resumes handles. 18.9 turns it into a scheduler.

Notice that `station` is taken **by value**. It is copied into the frame (18.4), so it is still alive when the coroutine continues. 18.8 shows what happens with a reference.

### The pattern to remember

> **`co_await` asks the awaiter: `await_ready` (skip the pause?), `await_suspend` (we are pausing: keep the handle), `await_resume` (we are back: produce the value). An awaiter that stores the handle lets someone else resume the coroutine later.**

**Code for this lecture**: `18.6CoAwaitAndAwaitables/`.

---

## 18.7 A lazy task

In this lecture we build the second most useful coroutine type: a **`Task<T>`**, one result produced later, which can wait for other tasks with `co_await`.

A generator gives many values. A task gives **one**, and lets you write asynchronous-looking code as straight lines:

```cpp
Task<double> average_of_two() {
    int north{co_await measure("north", 18)};    // runs measure, then comes back here
    int south{co_await measure("south", 25)};
    co_return (north + south) / 2.0;             // the result of the whole task
}
```

The new keyword is **`co_return value;`**: it finishes the coroutine and hands the value to the promise (`return_value`).

Three problems to solve in the promise, a few lines each:

1. **Lazy**: `initial_suspend` pauses, so nothing runs until somebody asks.
2. **Who continues**: when a task ends, the coroutine that was waiting for it has to carry on. The task keeps its handle: the **continuation**.
3. **Errors**: an exception in the task has to come out where the result is read, not vanish.

### A tool for errors: `std::exception_ptr`

Number 3 needs a small new piece of `<exception>`:

```
   std::exception_ptr          a copyable handle to an exception object, which can be stored
   std::current_exception()    inside a catch block (and in unhandled_exception): captures the exception being handled
   std::rethrow_exception(p)   throws the stored exception again, from anywhere
```

It is how you move an exception from one place to another, which is exactly what a task has to do.

### The promise

Everything the two kinds of promise (`Task<int>` and `Task<void>`) share goes in a base class:

```cpp
struct PromiseBase {
    std::coroutine_handle<> continuation;      // who awaited this task, if anybody
    std::exception_ptr error;

    std::suspend_always initial_suspend() noexcept { return {}; }       // lazy

    struct FinalAwaiter {
        bool await_ready() const noexcept { return false; }
        template <typename Promise>
        std::coroutine_handle<> await_suspend(std::coroutine_handle<Promise> finished) const noexcept {
            std::coroutine_handle<> next{finished.promise().continuation};
            return next ? next : std::noop_coroutine();
        }
        void await_resume() const noexcept {}
    };
    FinalAwaiter final_suspend() noexcept { return {}; }

    void unhandled_exception() { error = std::current_exception(); }

    void rethrow_if_failed() {
        if (error) {
            std::rethrow_exception(error);
        }
    }
};
```

`unhandled_exception` stores the exception instead of throwing it. `final_suspend` is the clever part: when the body ends, it does not just stop, it **hands control to the continuation**. Returning a handle from `await_suspend` (the third form of 18.6) resumes that coroutine as a **jump**, not as a nested call. This is called **symmetric transfer**, and the reason for it is below. If nobody waits (the top of a chain), it returns `std::noop_coroutine()`, a coroutine that does nothing, which sends control back to whoever resumed us.

The value-carrying part comes next. `Task<int>` has `return_value`, and `Task<void>` has `return_void`, which cannot live in one class:

```cpp
template <typename T>
struct Promise : PromiseBase {
    std::optional<T> value;

    Task<T> get_return_object();
    void return_value(T result) { value = std::move(result); }

    T result() {
        rethrow_if_failed();
        return std::move(*value);
    }
};

template <>
struct Promise<void> : PromiseBase {
    Task<void> get_return_object();
    void return_void() {}
    void result() { rethrow_if_failed(); }
};
```

`result()` is where a stored exception comes out.

### The task itself

```cpp
template <typename T>
class Task {
public:
    using promise_type = Promise<T>;
    using Handle = std::coroutine_handle<promise_type>;

    // move-only, and the destructor destroys the frame
    ...

    struct Awaiter {
        Handle task;

        bool await_ready() const noexcept { return false; }

        // Remember who is waiting, then START the task by returning its handle.
        std::coroutine_handle<> await_suspend(std::coroutine_handle<> waiting) const noexcept {
            task.promise().continuation = waiting;
            return task;
        }

        // The task is finished: its result (or its exception) is the value of co_await.
        T await_resume() const { return task.promise().result(); }
    };
    Awaiter operator co_await() && noexcept { return Awaiter{handle_}; }

    void resume() { handle_.resume(); }
    bool done() const { return handle_.done(); }
    std::coroutine_handle<> handle() const { return handle_; }
    T result() { return handle_.promise().result(); }
    T get() { handle_.resume(); return result(); }
    ...
};
```

**`operator co_await`** lets a type say which awaiter it uses (it is an operator like the ones of chapter 12). `co_await some_task` records the waiting coroutine as the continuation, and starts the task by *returning its handle*. When the task ends, `FinalAwaiter` returns the continuation. Control goes there and back by jumps, all through `await_suspend`.

`get()` is for the top of a chain, where no coroutine is waiting: it resumes the task and returns the result. The class is `task.h`, about 150 lines with comments. It is the biggest piece of machinery in this chapter, and the only one you reuse unchanged (18.8, 18.9, the project).

### Using it

```cpp
Task<int> measure(std::string station, int celsius) {
    std::println("  measuring {}", station);
    co_return celsius;
}

Task<double> average_of_two() {
    std::println("  average: asking the north station");
    int north{co_await measure("north", 18)};
    std::println("  average: asking the south station");
    int south{co_await measure("south", 25)};
    co_return (north + south) / 2.0;
}

Task<double> task{average_of_two()};
std::println("main: the task exists, nothing has run");
std::println("main: the result is {}", task.get());
```
```
main: the task exists, nothing has run
  average: asking the north station
  measuring north
  average: asking the south station
  measuring south
main: the result is 21.5
```

The task is **lazy**: nothing printed until `get()`. And a task that is never started simply never runs; its destructor destroys the frame:

```
main: created and thrown away
```

### Exceptions travel up through `co_await`

```cpp
Task<int> broken_sensor() {
    std::println("  the sensor is about to fail");
    throw std::runtime_error{"sensor offline"};
    co_return 0;                          // never reached; it makes this a coroutine
}

Task<int> careful() {
    try {
        co_return co_await broken_sensor();
    }
    catch (const std::exception& error) {
        std::println("  careful: caught \"{}\" and uses a default", error.what());
        co_return -1;
    }
}
```
```
  the sensor is about to fail
  careful: caught "sensor offline" and uses a default
main: careful gives -1
  the sensor is about to fail
main: caught "sensor offline"
```

The exception was stored in the promise of `broken_sensor`, and `await_resume` rethrew it **in the awaiting coroutine**, where the `try` is. In `main`, `.get()` rethrows it. Errors travel exactly where the code reads the result, which is where you would expect them.

### Why symmetric transfer matters

Tasks await tasks await tasks. If finishing a task *called* `continuation.resume()`, that call would sit on the stack until the continuation paused or ended. In a loop that awaits a million small tasks, a million calls would pile up. The jump (return a handle from `await_suspend`) uses no stack. We measured: a loop with one million `co_await one()`, where `one()` is a task that returns at once (`main2.cpp`):

| compiler | result |
|---|---|
| MSVC (`/Od` and `/O2`) | works |
| Clang 21 (`-O0` and `-O2`) | works |
| **GCC 16**, no optimization (`-O0`), also `-Og` and `-O1` | **crashes** (stack overflow) |
| GCC 16, `-O2` | works |
| GCC 16, `-O0 -foptimize-sibling-calls` | works |
| GCC 16, `-O2 -fno-optimize-sibling-calls` | **crashes** again |
| MinGW GCC 14.2, default | **crashes** (`0xC00000FD`, stack overflow); `-O2` or the flag fixes it |

GCC implements "resume that handle instead" as a tail call, and only does tail calls when it optimizes sibling calls (`-foptimize-sibling-calls`, switched on by `-O2`). So a Debug build with GCC can overflow the stack on a deep chain of tasks, where MSVC and Clang cannot. The `CMakeLists.txt` of this lecture adds the flag for `rooster2`, and the lesson is: **if your coroutine code crashes in a Debug build with GCC and works optimized, this is the first suspect.**

### The pattern to remember

> **A Task is a lazy coroutine with one result. `co_await task` records the waiting coroutine as the continuation and starts the task by returning its handle; when the task ends, `final_suspend` jumps back. Exceptions are stored with `exception_ptr` and rethrown where the result is read.**

**Code for this lecture**: `18.7ALazyTask/` (`task.h`, `main.cpp`, `main2.cpp`).

---

## 18.8 Lifetime pitfalls

In this lecture we meet the bugs coroutines are famous for. They all have one cause: **a coroutine outlives the statement that called it**. Everything it uses after its first pause must still be alive when it comes back, and the compiler does not check that.

The program has four classic bugs, each with its fix, and it runs one of them by number:

```
rooster          the FIXED versions of all four (safe)
rooster 1..4     the BUGGY version of one case
```

It is built with **AddressSanitizer** (9.12), and the `CMakeLists.txt` does that for you. These bugs often "work" without it, and that is what makes them dangerous.

### 1. A reference parameter bound to a temporary

```cpp
Task<void> greet_by_reference(const std::string& name) {
    std::println("hello, {}", name);
    co_return;
}

Task<void> task{greet_by_reference("station-with-a-name-too-long-to-fit-inside-the-string-object")};
task.get();
```

The frame stores the **reference**, not the string. The call builds a temporary `std::string`, which is destroyed at the end of that statement. The task is lazy, so its body runs later, in `get()`, reading a string that is gone. With a normal function this is fine: the temporary lives until the function returns. A lazy coroutine returns *before running*.

```
==10195==ERROR: AddressSanitizer: stack-use-after-scope on address 0x7b489a7d0340 ...
READ of size 8 at 0x7b489a7d0340 thread T0
    #0 ... std::__cxx11::basic_string<...>::_M_data() const
    ...
    #8 ... in greet_by_reference main.cpp:30
```

GCC, Clang and MSVC all reported `stack-use-after-scope`. **The fix**: take the parameter **by value**:

```cpp
Task<void> greet_by_value(std::string name) {
    std::println("hello, {}", name);
    co_return;
}
```

A by-value parameter is **copied into the frame** (18.4), so it lives exactly as long as the coroutine. Remember this rule: **in a coroutine, take parameters by value**, unless you are certain that the caller's object outlives the coroutine (a `Scheduler&` that outlives all its tasks is such a case).

### 2. A lambda that is a coroutine and captures

```cpp
Task<void> task{[name]() -> Task<void> {
    std::println("hello, {}", name);
    co_return;
}()};
task.get();
```

A lambda's captures live in the **closure object**, not in the coroutine frame, and the coroutine reaches them through the closure's address. The closure here is a temporary, called at once, and destroyed at the end of the statement, with `name` inside it. The sanitizer again reports `stack-use-after-scope`, on all three compilers.

**The fix**: pass the data as a **parameter** of the lambda, because parameters are copied into the frame:

```cpp
Task<void> task{[](std::string copy) -> Task<void> {
    std::println("hello, {}", copy);
    co_return;
}(name)};
```

### 3. A generator that outlives what it walks over

```cpp
std::generator<int> walk(std::span<const int> values) {
    for (int value : values) {
        co_yield value;
    }
}

std::generator<int> todays_readings_bug() {
    std::vector<int> readings{18, 21, 24, 19, 17, 22, 25, 20};
    return walk(readings);
}
```

A `std::span` (9.8) is a **view**: a pointer and a size, owning nothing. The span parameter is copied into the frame, but the elements it points at are not. `readings` is destroyed when the function returns, and the generator, which is lazy, reads freed memory later.

```
==10199==ERROR: AddressSanitizer: heap-use-after-free on address 0x7bb642de0040 ...
READ of size 4 at 0x7bb642de0040 thread T0
```

GCC and Clang report `heap-use-after-free`. **MSVC reports nothing here.** The program printed `22 0 24 19 17 22 25 20`: garbage, and the sanitizer stayed silent. We tested a plain function and a coroutine reading the same freed vector: with MSVC 19.51 the plain function was caught at once (`heap-use-after-free`) and the coroutine was not. So AddressSanitizer on MSVC **does not check accesses written directly inside a coroutine body**. Cases 1 and 2 were caught on MSVC, as far as we can tell, only because the bad read happened inside library code (the top of the report is in `std::string`), which *is* instrumented. The lesson: a sanitizer's silence is not proof, and **coroutines are where it is weakest**. Test the lifetime-sensitive parts with GCC or Clang on Linux too.

**The fix**: give the generator its own copy (a parameter taken by value is stored in the frame), or make sure the vector outlives it:

```cpp
std::generator<int> walk_copy(std::vector<int> values) {
    for (int value : values) {
        co_yield value;
    }
}
```

This is the same rule as for views in chapter 15 (`dangling`) and for iterators in chapter 14: anything that **refers** to a container is invalid when the container goes away.

### 4. A paused coroutine nobody owns or resumes

```cpp
Job leaked_job() {
    Resource connection;          // prints "opened" in the constructor and "closed" in the destructor
    co_await Park{};              // parks the handle, as in 18.6
    std::println("  (never printed)");
}
```
```
  database connection opened
main: the job is paused, and nobody will ever resume it
```

There is no "closed". If a coroutine never finishes and its frame is never destroyed, its local variables are **never destroyed either**: no destructor runs, so every RAII object in it is silently skipped. A `Resource` here could be a file, a lock or a network connection. No sanitizer reports it either: the global `parked` still points at the frame, so it is not "leaked" in the sanitizer's sense, only forgotten.

**The fix**: give the frame an **owner**. A `Task` destroys its frame in its destructor, and destroying a paused frame runs the destructors of its live locals:

```
  main: starting it
  database connection opened
  main: it is paused; the owner goes out of scope
  database connection closed
```

### The rules, in one list

1. **Take coroutine parameters by value.** A reference or a view in a parameter must outlive the coroutine, and a lazy coroutine runs later than you think.
2. **Do not capture in a lambda that is a coroutine.** Pass the data as parameters.
3. **Every coroutine frame needs an owner** that destroys it, once. Prefer types like `Task` and `std::generator`, which are owners.
4. **Test on GCC or Clang with AddressSanitizer** (and MSVC too, but do not rely on it alone for coroutine bodies).

### The pattern to remember

> **A coroutine's parameters and locals live in its frame; what they refer to does not. Pass by value, never capture, give the frame an owner.**

**Code for this lecture**: `18.8LifetimePitfalls/`.

---

## 18.9 A round-robin scheduler

In this lecture we put 18.6 and 18.7 together. 18.6 showed that an awaiter can park the coroutine's handle somewhere. 18.7 gave us `Task<T>`. A queue of parked handles and a loop that resumes them one after the other is a **scheduler**.

```
   ready_ (front -> back):   [ A ] [ B ] [ C ]

   run() takes A and resumes it.  A works, then   co_await scheduler.yield_now()   puts A at the back:

   ready_:                   [ B ] [ C ] [ A ]
```

**Round robin** means everybody gets a turn, in order, again and again. There are no threads here: it is **one thread, taking turns**. Only one task runs at any moment, and a task can only be interrupted at a `co_await` it wrote itself, so the tasks never need a mutex (chapter 19).

### The code

```cpp
class Scheduler {
public:
    void spawn(Task<void> task) {
        ready_.push_back(task.handle());
        tasks_.push_back(std::move(task));
    }

    void run() {
        while (!ready_.empty()) {
            std::coroutine_handle<> next{ready_.front()};
            ready_.pop_front();
            next.resume();
        }
        for (Task<void>& task : tasks_) {
            task.result();                 // rethrows the first exception, if any
        }
    }

    struct YieldAwaiter {
        Scheduler& scheduler;

        bool await_ready() const noexcept { return false; }
        void await_suspend(std::coroutine_handle<> waiting) const {
            scheduler.ready_.push_back(waiting);
        }
        void await_resume() const noexcept {}
    };

    YieldAwaiter yield_now() { return YieldAwaiter{*this}; }

private:
    std::deque<std::coroutine_handle<>> ready_;       // 14.5: a queue of turns
    std::vector<Task<void>> tasks_;                   // owns the frames until the scheduler is gone
};
```

`spawn` takes the task (the scheduler becomes its owner, so the frame is destroyed with the scheduler) and queues its first turn. `run` pops a handle, resumes it, and repeats until nobody is waiting. `yield_now()` is an awaiter in the style of 18.6: it **puts the running coroutine at the back of the queue** and pauses it.

### Taking turns

```cpp
Task<void> worker(Scheduler& scheduler, std::string name, int steps) {
    for (int step{1}; step <= steps; ++step) {
        std::println("{} step {}", name, step);
        co_await scheduler.yield_now();
    }
    std::println("{} is finished", name);
}
```

Three workers with 3, 2 and 4 steps:

```
north step 1
south step 1
east step 1
north step 2
south step 2
east step 2
north step 3
south is finished
east step 3
north is finished
east step 4
east is finished
```

They interleave, and when a short one ends the others keep taking turns. Each worker is written as a plain loop; the interleaving is the scheduler's.

### Switching happens only at a `co_await`

This kind of multitasking is **cooperative**: a task is never interrupted, it *gives* the thread away. A task that never yields keeps it until it ends:

```cpp
Task<void> greedy(std::string name, int steps) {
    for (int step{1}; step <= steps; ++step) {
        std::println("{} step {}", name, step);
    }
    co_return;
}
```
```
north step 1
greedy step 1
greedy step 2
greedy step 3
south step 1
north step 2
south step 2
north is finished
south is finished
```

"greedy" had no `co_await`, so all three of its steps ran in one go. One misbehaving task stalls everybody. That is the price of not needing locks, and the reason cooperative schedulers are used for many small, well-behaved jobs (the project) and not for code you do not control.

### Yielding from inside a task that was awaited

Real jobs are made of tasks that await tasks (18.7). Does a yield deep inside still let the others run?

```cpp
Task<int> read_sensor(Scheduler& scheduler, std::string name, int celsius) {
    std::println("  {}: reading started", name);
    co_await scheduler.yield_now();                // pretend the hardware is slow
    std::println("  {}: reading done", name);
    co_return celsius;
}

Task<void> station_report(Scheduler& scheduler, std::string name, int celsius) {
    int first{co_await read_sensor(scheduler, name + " (1)", celsius)};
    int second{co_await read_sensor(scheduler, name + " (2)", celsius + 2)};
    std::println("{} reports {} and {}", name, first, second);
}
```
```
  north (1): reading started
  south (1): reading started
  north (1): reading done
  north (2): reading started
  south (1): reading done
  south (2): reading started
  north (2): reading done
north reports 18 and 20
  south (2): reading done
south reports 25 and 27
```

Yes. `yield_now()` receives the handle of the **innermost** running coroutine (`waiting` in `await_suspend`), however many `co_await task` levels deep it is. When it is resumed, it finishes, and symmetric transfer (18.7) jumps back up the chain.

### Errors

A task that ends with an exception does not stop the others; `run()` rethrows the first one when everything has finished:

```
north step 1
north step 2
north is finished
run() threw: the failing task gave up
```

### What is missing

This scheduler can only yield. A realistic one also lets tasks **wait for events**: a timer (18.6's clock), a file, a message. The pattern is always the same, an awaiter that parks the handle somewhere else than the ready queue, and something that moves it to the queue when the event happens. Libraries that do this for networking or threads exist (and `std::execution`, in C++26, standardizes the idea). You now know how they work inside.

### The pattern to remember

> **A scheduler is a queue of coroutine handles and a loop that resumes them. `yield_now()` is an awaiter that puts the running coroutine at the back of the queue. Tasks switch only at a `co_await`, so one thread is enough and no locks are needed.**

**Code for this lecture**: `18.9ARoundRobinScheduler/` (`main.cpp`, `scheduler.h`, `task.h`).

---

## 18.10 Project: the lazy pipeline

The log analyzer of chapter 14 answered its questions with loops and containers over a log it had read **completely**. Chapter 15 redid it with algorithms and views, and still read the whole file into one string first. This project rebuilds it with the tools of this chapter, and the file is **never held in memory**: a line is read, parsed, counted, and forgotten.

```
   file  ──►  lines()  ──►  requests()  ──►  filter(is_error)  ──►  a job's loop
              generator     generator        a view                  counts, sums, ...

   Each arrow is a PULL: the job asks for the next request, which asks for the
   next parsed line, which asks the file for the next line. Nothing is read
   until someone downstream asks.
```

And there are three jobs (top pages, busiest error hours, heaviest clients) that run on **one thread**, taking turns in the `Scheduler` of 18.9.

### The data

The same tool as in chapters 14 and 15 writes the log. Build and run:

```
cmake -S . -B build -G Ninja
cmake --build build
./build/rooster_generate 20000 access.log
./build/rooster access.log
```

(On Windows the programs are `build\rooster_generate.exe` and `build\rooster.exe`.) The generator is deterministic: with 20,000 lines the file has the MD5 `fc9f5b295a055f5aeda1a807dc2e94da` on every machine we tried (MSVC, GCC and Clang). A 20-line `sample.log` is also in the folder.

### Stage 1: lines, one at a time

```cpp
std::generator<std::string> lines(std::string path, std::size_t& lines_read) {
    std::ifstream file{path};
    if (!file) {
        throw std::runtime_error{"cannot open " + path + " (run rooster_generate first)"};
    }
    std::string line;
    while (std::getline(file, line)) {
        ++lines_read;
        co_yield line;
    }
}
```

The `path` is taken **by value** (18.8). `lines_read` is a reference, on purpose: it belongs to the caller and outlives the coroutine, and it counts how many lines were *really* pulled. We will use that number in a moment. The exception for a missing file is thrown at the first step of the loop, not when `lines` is called, because nothing runs before.

### Stage 2: parse, skip the damaged

```cpp
std::generator<Request> requests(std::generator<std::string> source, std::size_t& damaged) {
    for (const std::string& line : source) {
        std::optional<LogEntry> entry{parse_line(line)};
        if (!entry) {
            ++damaged;
            continue;
        }
        co_yield Request{std::string{entry->client}, std::string{entry->method}, std::string{entry->path},
                         entry->hour, entry->status, entry->bytes};
    }
}
```

A stage **takes the previous stage as a parameter**. A generator is move-only, so the call site moves one in (`requests(lines(path, n), damaged)` passes a temporary), and the frame keeps it alive for as long as `requests` runs (the by-value rule of 18.8 again). `parse_line` is the function of chapter 14. One difference: the old `LogEntry` held `std::string_view`s into the file's buffer, and here the line is gone after the next step. So the stage copies the text into a `Request` that owns its strings.

### Stage 3: a view

The third stage is not a coroutine at all. A generator is a range, so the views of chapter 15 attach to it:

```cpp
bool is_error(const Request& request) { return request.status >= 400; }

requests(lines(path, lines_read), damaged) | std::views::filter(is_error)
```

That is the nice thing about building on `std::generator`: coroutine stages and view stages mix freely.

### Laziness, measured

`main` starts with a question that needs very little of the file: the first three server errors.

```cpp
auto first_errors{requests(lines(path, lines_read), damaged)
    | std::views::filter(is_error)
    | std::views::take(3)};
for (const Request& request : first_errors) {
    std::println("{} {} {} -> {}", request.client, request.method, request.path, request.status);
}
std::println("pulled {} lines out of the file to find them", lines_read);
```
```
--- the first three server errors
203.0.113.26 GET /products/gadget -> 500
192.0.2.8 GET /index.html -> 500
192.0.2.73 GET /products/discontinued -> 404
pulled 58 lines out of the file to find them
```

Fifty-eight lines out of 20,000. After the third error, `take(3)` stops asking, the chain is destroyed from the outside in (each frame's destructor runs), and the file is closed having read 0.3% of it. The version of chapter 15 read the entire file before looking at the first line.

### The jobs

Each job is a `Task<void>` with the same shape: pull requests, update some state, and every `batch` requests give the other jobs a turn.

```cpp
Task<void> top_pages(Scheduler& scheduler, std::string path, std::size_t batch, std::string& report) {
    std::size_t lines_read{0};
    std::size_t damaged{0};
    std::unordered_map<std::string, std::size_t> hits;
    std::size_t seen{0};

    for (const Request& request : requests(lines(path, lines_read), damaged)) {
        ++hits[request.path];
        if (++seen % batch == 0) {
            std::println("[top pages]       {} requests so far", seen);
            co_await scheduler.yield_now();
        }
    }
    report += std::format("top pages ({} requests, {} damaged lines skipped)\n", seen, damaged);
    for (const auto& [page, count] : top_of(hits, 5)) {
        report += std::format("  {:>6}  {}\n", count, page);
    }
}
```

A `co_await` **inside a range-based for loop over a generator**: the job pauses with its loop, its counters and the open file all alive, in the job's frame and the generators' frames, and continues where it was. That is the whole benefit of coroutines in one sentence. In a program without them you would write a state machine for "read 5,000 lines, let someone else run, continue".

`error_hours` counts only errors, with the filter view in its loop, so it yields every 500 errors (errors are rarer than requests). `heavy_clients` adds up the bytes sent to each client. `top_of` sorts a table by count with the name as tie-breaker, so the output never depends on the order of an `unordered_map` (14.7).

The jobs write their reports into strings that `main` owns, and `main` prints them after `run()` returns, in a fixed order. The references to `main`'s variables are safe because `run()` finishes inside `main`'s scope (18.8: the by-reference rule has an exception, and this is it).

```cpp
Scheduler scheduler;
std::string pages_report;
std::string hours_report;
std::string clients_report;
scheduler.spawn(top_pages(scheduler, path, batch, pages_report));
scheduler.spawn(error_hours(scheduler, path, batch, hours_report));
scheduler.spawn(heavy_clients(scheduler, path, batch, clients_report));
scheduler.run();
```

### The run

```
--- three analyses taking turns
[top pages]       5000 requests so far
[error hours]     500 errors so far
[heavy clients]   5000 requests so far
[top pages]       10000 requests so far
[heavy clients]   10000 requests so far
[top pages]       15000 requests so far
[heavy clients]   15000 requests so far

--- results
top pages (19966 requests, 34 damaged lines skipped)
    3933  /
    1626  /index.html
    1257  /products
    1016  /products/widget
     948  /products/gadget

busiest hours for errors (997 errors in 20000 lines)
      89  11:00
      82  13:00
      76  12:00

clients that downloaded the most (bytes)
   115693407  203.0.113.1
    33107616  198.51.100.1
    23597292  192.0.2.1
```

MSVC, GCC and Clang print byte-identical output, and the program is clean under AddressSanitizer and UndefinedBehaviorSanitizer on GCC and Clang. The progress lines show the turns: each job reports as it passes a batch, and the three of them advance together. A second argument changes the batch (`./build/rooster access.log 1000`), and a missing file gives:

```
cannot open missing.log (run rooster_generate first)
```

That message travels the whole way: thrown in a generator, stored in the promise of the job (18.7), rethrown by `run()` (18.9), and caught in `main`.

### What we learned

- **Streaming**: with generators the memory use does not depend on the file size, and work that needs only the beginning reads only the beginning (58 of 20,000 lines).
- **Generators and views mix**: a coroutine stage and a `std::views::filter` stage are the same kind of thing, a range.
- **Tasks make sharing one thread easy**: each job is written as a straight loop, and the scheduler interleaves them. No locks, because they switch only at `co_await`.
- **The costs are honest**: every coroutine is a frame allocation (18.4), and reading the same file three times is wasteful. A real tool would read once and feed all three jobs. The chapter on concurrency (19) turns the same three jobs into threads, and then you can compare.

### Things to try

1. Add a fourth job, `slowest_pages`, that tracks the pages with the most bytes per request, and spawn it.
2. Add a stage between `requests` and the jobs: `only_gets(std::generator<Request>)`, a coroutine that skips every method except GET. Then replace it with a `std::views::filter` and compare.
3. Make `lines` read from standard input when no path is given, so the tool can sit at the end of a pipe: `generator | rooster`.
4. Run it on a 1,000,000-line log (`rooster_generate 1000000 big.log`) and watch the memory use of the process, then do the same with the chapter 15 project.

**Code for this lecture**: `18.10ProjectLazyPipeline/` (`main.cpp`, `log_entry.h`, `generate_log.cpp`, `task.h`, `scheduler.h`, `sample.log`).

---

## 18.11 Assignment

Eight small jobs for the weather station, one for each idea of the chapter. `task.h` and `scheduler.h` are provided in the folder; the generator is `std::generator`. The `CMakeLists.txt` builds AddressSanitizer in, because exercise 8 needs it.

| # | Exercise | Skill |
|---|---|---|
| 1 | `hours(first, last, step)`: a generator of hours | `co_yield`, a lazy sequence (18.2, 18.3) |
| 2 | An endless `sensor()`, and the first five readings above 20 | endless generator, `filter` and `take` (18.3) |
| 3 | `all_values(branch)`: a depth-first walk of a tree | recursive generator, `elements_of` (18.3) |
| 4 | `reading(n)` and `mean_of_three()`: tasks awaiting tasks | `Task`, `co_await`, `co_return` (18.7) |
| 5 | `checked(n)` and `safe_checked(n)`: an exception in a task | exceptions through `co_await` (18.7) |
| 6 | A `Gate` class with its own awaiter | `await_ready`, `await_suspend`, `await_resume` (18.6) |
| 7 | A `worker` that yields after every step, run by the `Scheduler` | cooperative scheduling (18.9) |
| 8 | Fix a lifetime bug and explain it | by-value parameters, sanitizers (18.8) |

Work as in the earlier assignments: the starter `main.cpp` has the statement of each exercise with its sample output, you write the coroutines above `main()` and the calls under the heading. `main_solution.cpp` builds as the target `rooster_solution`.

The solution's output:

```
--- Exercise 1: a generator of hours ---
0 6 12 18 24 

--- Exercise 2: readings above 20 ---
22 25 21 24 23 

--- Exercise 3: a tree of values ---
1 2 4 5 3 6 
sum 21

--- Exercise 4: awaiting three readings ---
  reading #1
  reading #2
  reading #3
mean 21.67

--- Exercise 5: an exception in a task ---
safe_checked(3) = 30
safe_checked(9) = -1
caught: no such sensor

--- Exercise 6: a gate ---
north waits at the gate
south waits at the gate
opening the gate
north walks through
south walks through
east waits at the gate
east walks through

--- Exercise 7: two workers ---
north read #1
south read #1
north read #2
south read #2
north read #3
south total 40
north total 65

--- Exercise 8: fix the lifetime bug ---
hello, a station name that is too long to hide inside the string object
```

The quiz has 20 questions on the whole chapter: what makes a coroutine, laziness, the frame, the promise, the three awaiter functions, symmetric transfer and the GCC flag, exceptions, the lifetime rules, and the scheduler. See `QUIZ.md` in the assignment folder.

That is coroutines: functions that pause, from the keyword down to a scheduler of your own. Everything here ran on one thread. In the next chapter we add the second ingredient of concurrency, **real threads**, with the parallel algorithms, mutexes, atomics and the problems they bring. The scheduler you just wrote will be the contrast: tasks that switch only where they say so, versus threads that can be interrupted anywhere.

**Code for this lecture**: `18.11Assignment/` (`main.cpp`, `main_solution.cpp`, `task.h`, `scheduler.h`, `QUIZ.md`).
