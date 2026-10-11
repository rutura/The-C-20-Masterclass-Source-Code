# Exceptions and a First Look at Contracts

Everything you have written so far assumed that things work. The file opens, the text is a number, the index is inside the vector, the sensor answers. Real programs do not get that luxury. Files are missing, users type `warm` where a temperature should be, a network cable is pulled out. The question of this chapter is not *how do I prevent it* (you cannot) but **what does my code do when something goes wrong, and who gets to decide**.

You have already met the pieces without naming them. `std::vector::at` threw something when you went too far. `std::stoi("hello")` threw something. The `Matrix` of chapter 12 threw something when you added two matrices of different sizes, and its notes said "exceptions are chapter 13". This is chapter 13.

```
   a function cannot do its job
              │
              ├── tell the caller through the RETURN VALUE     optional, expected, error codes
              │       the caller stays in control, the failure is part of the normal flow
              │
              ├── leave by ANOTHER ROAD                         exceptions
              │       the failure skips every function in between, until someone handles it
              │
              └── declare that it should never have happened    assert, static_assert, contracts
                      a bug in the program, not a condition of the world
```

The chapter walks those three roads in order, always on the weather station: sensors that go offline, readings that make no sense, configuration text that is wrong. Then a **project** that closes the loop: you cannot trust code you have not tested, so we write tests for the `Matrix` of chapter 12, three ways: by hand, with **GoogleTest** and with **Catch2**.

One warning about compilers. `std::expected` and `std::source_location` are C++23 and C++20 and work on all three of our compilers. `std::stacktrace` needs one extra linker option on GCC and Clang. **Contracts** (`pre`, `post`) are C++26, and at the time of writing only **GCC 16** implements them, so that part is shown with GCC, and the notes say plainly where something does not run on MSVC or Clang.

---

## 13.2 Error-handling strategies

In this lecture we take one small job and report its failure in four different ways, so you can see what each one costs and what each one buys.

### The job

Turn text such as `"21.5"` into a temperature. The text might not be a number at all. The core of the job is the same in the four versions: a function that returns `true` and fills in a `double`, or returns `false`.

### 1. A return code and an output parameter

```cpp
bool parse_with_code(std::string_view text, double& result);
```

This is the C way. It works, but look at what it asks of the caller: remember to check the `bool`, and never use `result` when the answer is `false`. Nothing in the language forces either. Forgetting the check compiles, runs, and uses a garbage value.

### 2. `std::optional`

```cpp
std::optional<double> parse_optional(std::string_view text) {
    double value{0.0};
    if (parse_with_code(text, value)) {
        return value;
    }
    return std::nullopt;
}
```

"A value, or nothing". The result *is* the answer, so there is no half-filled output parameter. But the failure carries **no reason**: was it empty text, letters, a number out of range? The caller cannot tell.

### 3. `std::expected` (C++23)

```cpp
std::expected<double, std::string> parse_expected(std::string_view text) {
    double value{0.0};
    if (parse_with_code(text, value)) {
        return value;
    }
    return std::unexpected{std::string{"not a number: '"} + std::string{text} + "'"};
}
```

"A value, **or an error that says why**". The error type is part of the signature, `std::string` here (13.7 uses an enum). `std::unexpected{...}` is how you return the error side.

### 4. An exception

```cpp
double parse_throwing(std::string_view text) {
    double value{0.0};
    if (!parse_with_code(text, value)) {
        throw std::invalid_argument{"not a number: '" + std::string{text} + "'"};
    }
    return value;
}
```

The return type is just `double`. A failure does not come back through the return value at all: it leaves the function by a different road, and **it cannot be ignored**. If nobody handles it, the program ends.

### The four, side by side

The program runs the same two inputs through all four:

```
--- parsing '21.5'
  return code: ok
  optional:    21.500000
  expected:    21.500000
  exception:   21.5
--- parsing 'warm'
  return code: failed
  optional:    nothing
  expected:    not a number: 'warm'
  exception:   caught: not a number: 'warm'
```

### Which one to choose

```
   failure is NORMAL and expected (user input, a missing file, a lookup)   optional or expected
   failure is RARE, or cannot be handled where it happens                  exception
   constructors and operators: there is no return value to use             exception
   the failure is a BUG in the program, not a condition of the world       assertion or contract (13.9)
```

Two sentences to remember:

- If the **immediate caller** is the one who will deal with the failure, return it (`optional`, `expected`).
- If the failure has to travel **up through several layers** to somebody who can do something about it, throw it. Nobody in the middle needs to know.

There is a performance argument too. The usual implementations make the non-throwing path essentially free and pay when an exception is actually thrown, so exceptions suit failures that are rare. We have not measured it here, so treat it as the typical picture, not a promise.

Many code bases use both: `expected` at the boundaries where failure is routine, exceptions inside for the surprises. This chapter teaches both because you will meet both.

**Code for this lecture**: `13.2ErrorHandlingStrategies/main.cpp`.

---

## 13.3 `throw`, `try`, `catch` and stack unwinding

In this lecture we learn the three keywords, and watch what happens to the objects between the `throw` and the `catch`.

### The three keywords

```cpp
try {
    // code that might fail
}
catch (const std::out_of_range& error) {
    // what to do when it does
}
```

- **`throw expression;`** stops the current function immediately and starts looking for a handler.
- **`try { }`** marks a region whose exceptions we are prepared to handle.
- **`catch (type name) { }`** is a handler for one kind of exception.

### What happens in between

A helper class announces its creation and destruction (the same trick as in chapter 10):

```cpp
double read_sensor(int id) {
    Trace trace{"read_sensor trace"};
    if (id < 0) {
        throw std::out_of_range{"sensor id " + std::to_string(id) + " does not exist"};
    }
    return 20.0 + id;
}

double average_of_two(int first, int second) {
    Trace trace{"average_of_two trace"};
    double a{read_sensor(first)};
    double b{read_sensor(second)};          // an exception here skips everything below
    std::println("    (average_of_two finished normally)");
    return (a + b) / 2.0;
}
```

First a call that works, then one that throws on the second sensor:

```
a call that works:
    average_of_two trace created
    read_sensor trace created
    read_sensor trace destroyed
    read_sensor trace created
    read_sensor trace destroyed
    (average_of_two finished normally)
    average_of_two trace destroyed
  result 22

a call that throws:
    average_of_two trace created
    read_sensor trace created
    read_sensor trace destroyed
    read_sensor trace created
    read_sensor trace destroyed
    average_of_two trace destroyed
  caught: sensor id -7 does not exist
  the program carries on
```

Compare the two. In the failing call, the line `(average_of_two finished normally)` never appears: the function was abandoned at the throw. But **both traces were still destroyed**, the one in `read_sensor` and the one in `average_of_two`. That is **stack unwinding**:

```
   main
    └─ average_of_two        Trace destroyed  ◄── 3. each scope the exception leaves is cleaned up,
        └─ read_sensor       Trace destroyed  ◄── 2.   in reverse order of construction
             throw ─────────────────────────────── 1. the exception starts here

   main's catch handler receives it ◄── 4. execution continues AFTER the try block
```

This is the reason RAII (10.6) matters so much: a destructor is the one piece of code guaranteed to run on both roads, the normal one and the exceptional one. A file wrapper, a lock, a `std::vector`, a `std::unique_ptr` all clean up after themselves while an exception passes through. Code that closes things by hand at the end of a function (`close(file);`) does not run on the exceptional road, and leaks.

### Catch by `const` reference

```cpp
catch (const std::out_of_range& error) {
    std::println("  caught: {}", error.what());
}
```

Always by `const` reference. By value would **copy** the exception and, if you named a base class, **slice** it (11.4). `what()` returns a C string describing the problem.

### Handlers are tried in order

```cpp
try {
    read_sensor(-1);
}
catch (const std::invalid_argument&) {
    std::println("  not this one");
}
catch (const std::logic_error& error) {              // out_of_range derives from logic_error
    std::println("  logic_error handler caught: {}", error.what());
}
```

```
handlers in order:
    read_sensor trace created
    read_sensor trace destroyed
  logic_error handler caught: sensor id -1 does not exist
```

The first handler that can accept the exception wins. A handler for a **base class accepts every derived class too**, so put the specific handlers first and the general ones last. Reverse the order and the specific handler becomes unreachable. GCC warns about that with `-Wall` (`-Wexceptions`: "will be caught by earlier handler"); Clang stayed silent when we tried, so do not rely on the compiler.

### `catch (...)` and throwing anything

```cpp
try {
    throw 42;                          // anything can be thrown, even an int
}
catch (...) {
    std::println("\n  catch (...) caught something unknown");
}
```

You can throw an `int`, but you should not: use classes derived from `std::exception` (13.4) so that `what()` and the usual handlers work. `catch (...)` catches anything and gives you no way to look at it. Its legitimate use is "last resort": log something and rethrow (13.6), or stop an exception at a boundary where it must not escape (a thread, a destructor).

### An exception nobody catches

If no handler matches, `std::terminate` is called and the program ends. The `main` of this lecture ends with a commented line, `read_sensor(-1);`: uncomment it to see your platform's message. Reaching that is a sign that some layer forgot to decide who handles the failure.

### On Windows with `cl`

When you compile by hand with `cl`, add `/EHsc` so that exceptions behave as the standard says. CMake adds it for you.

**Code for this lecture**: `13.3ThrowTryCatchAndUnwinding/main.cpp`.

---

## 13.4 The standard hierarchy and your own exceptions

In this lecture we meet the exception classes the standard library offers, and write our own.

### The hierarchy

```
   std::exception                              what()
   ├── std::logic_error                        a bug in the caller: could have been avoided
   │   ├── std::invalid_argument
   │   ├── std::out_of_range
   │   ├── std::domain_error
   │   └── std::length_error
   ├── std::runtime_error                      something nobody could predict
   │   ├── std::range_error
   │   ├── std::overflow_error
   │   └── std::system_error
   └── std::bad_alloc, std::bad_cast, std::bad_variant_access, ...   thrown by language and library
```

A handler for `const std::exception&` catches *all* of them. That is a handy last net, and you saw `std::bad_cast` and `std::bad_variant_access` promised in chapter 11: they live here.

The split between `logic_error` and `runtime_error` is a hint about intent. A **logic error** means the caller broke a rule it could have checked (an index too large, a negative size). A **runtime error** means the world misbehaved (a file vanished, a device returned nonsense). Pick the closest one for what you throw.

### Writing your own

```cpp
class SensorError : public std::runtime_error {
public:
    SensorError(int sensor_id, const std::string& message)
        : std::runtime_error{"sensor " + std::to_string(sensor_id) + ": " + message},
          sensor_id_{sensor_id} {}

    int sensor_id() const noexcept { return sensor_id_; }

private:
    int sensor_id_;
};
```

Three rules, all visible above:

1. **Derive from the closest standard class.** Then every existing handler for `std::runtime_error` or `std::exception` still catches your type.
2. **Pass the message to the base class**, so `what()` works. Build it in the initializer list.
3. **Add the data a handler would want** (the sensor id, the bad value) and expose it with `noexcept` getters, because creating or inspecting an exception must not throw a second one.

Narrower types go below it:

```cpp
class SensorOffline final : public SensorError {
public:
    explicit SensorOffline(int sensor_id) : SensorError{sensor_id, "offline"} {}
};

class SensorOutOfRange final : public SensorError {
public:
    SensorOutOfRange(int sensor_id, double value)
        : SensorError{sensor_id, "reading " + std::to_string(value) + " is out of range"},
          value_{value} {}

    double value() const noexcept { return value_; }

private:
    double value_;
};
```

### Handling a family

```cpp
for (int id : {1, 2, 3, 4}) {
    try {
        std::println("sensor {} reads {}", id, read(id));
    }
    catch (const SensorOutOfRange& error) {
        std::println("sensor {} out of range, value was {}", error.sensor_id(), error.value());
    }
    catch (const SensorError& error) {
        std::println("sensor problem, id {}: {}", error.sensor_id(), error.what());
    }
    catch (const std::exception& error) {
        std::println("other failure: {}", error.what());
    }
}
```

```
sensor 1 reads 21.5
sensor problem, id 2: sensor 2: offline
sensor 3 out of range, value was 999.9
other failure: no sensor with id 4
```

Sensor 2 threw a `SensorOffline`, which no handler names, so the `SensorError` handler took it. Sensor 3 threw a `SensorOutOfRange`, which the first handler wants, so it gets the extra data. Sensor 4 threw a plain `std::out_of_range`, which is not a `SensorError` at all, so only the last handler matches. Specific first, general last, and the program stays up.

### The library throws too

```cpp
std::vector<int> values{1, 2, 3};
values.at(10);                // std::out_of_range
std::stoi("hello");           // std::invalid_argument
std::vector<int> huge(values.max_size() + 1);   // std::length_error
```

```
vector::at: vector::_M_range_check: __n (which is 10) >= this->size() (which is 3)
stoi: stoi
vector: length_error caught
```

The text of `what()` is **not specified by the standard**. This output is GCC's. On MSVC the same two lines read `vector::at: invalid vector subscript` and `stoi: invalid stoi argument`. So never compare `what()` against a string in real code to decide what happened: catch the right *type*, and use `what()` for people to read.

Note `at()` versus `operator[]`: `at()` checks and throws, `[]` does not check and misbehaves. That is the same trade as everywhere in C++: pay for the check or take the risk.

**Code for this lecture**: `13.4StandardAndCustomExceptions/main.cpp`.

---

## 13.5 `noexcept` and the safety guarantees

In this lecture we answer two questions. What does `noexcept` promise, and why does `std::vector` care? And when an operation fails halfway, what state is the object left in?

### `noexcept`

```cpp
Careful(Careful&&) noexcept { ++moves; }
```

`noexcept` says: **this function will not let an exception escape.** It is a promise, and it is enforced: if an exception tries to leave a `noexcept` function, the program ends with `std::terminate`. It is not a request for the compiler to check your work; it is a contract you sign.

There is also a `noexcept` operator that asks the compiler a question:

```cpp
noexcept(std::string{std::declval<std::string>()})     // true: moving a string cannot throw
```

### Why `std::vector` cares

When a vector is full and you add one more element, it allocates a bigger block and has to bring the old elements over. If it **moves** them and the third move throws, the old block is already damaged and the vector cannot go back. If it **copies** them, a throw leaves the old block untouched and the vector can simply give up. So the rule is: the vector moves its elements only if the move **cannot throw** (`noexcept`); otherwise it copies. This is `std::move_if_noexcept`.

Two types that differ in exactly one word:

```cpp
struct Careful {
    Careful() = default;
    Careful(const Careful&) { ++copies; }
    Careful(Careful&&) noexcept { ++moves; }
};

struct Nervous {
    Nervous() = default;
    Nervous(const Nervous&) { ++copies; }
    Nervous(Nervous&&) { ++moves; }              // may throw, as far as the compiler knows
};
```

Grow a vector of each to 100 elements with `emplace_back`:

```
growing a vector of a type with a noexcept move:
  100 elements: 0 copies, 127 moves
growing a vector of a type whose move may throw:
  100 elements: 127 copies, 0 moves
```

**Exactly the same code, and every reallocation copies instead of moves**, because one word is missing. For a type that owns a big buffer, that is the difference between pointer swaps and duplicating megabytes. This is the promise chapter 10 made when it said "mark the move operations `noexcept`".

The number 127 is GCC's and Clang's growth pattern (the capacity doubles). With MSVC the same program printed 284 moves for 100 elements, because it grows by 1.5 times. The count depends on the standard library; the point, **zero copies against all copies**, does not.

Rule of thumb: mark `noexcept` on move operations, on `swap`, on destructors (they are by default), and on simple getters. If you are not sure it cannot throw, leave it off.

### The exception safety guarantees

An operation can fail halfway. What is left? There are four levels people talk about, from weakest to strongest:

```
   no guarantee   anything may happen: leaks, broken objects        avoid at all costs
   basic          nothing leaks, every object is valid,             "valid but unspecified"
                  but values may have changed
   strong         commit or rollback: if it throws, nothing         "as if it never happened"
                  observable has changed
   nothrow        it never throws                                   destructors, moves, swap
```

A small class shows the difference between basic and strong:

```cpp
class ReadingLog {
public:
    // Basic guarantee
    void append_basic(const std::vector<std::string>& texts) {
        for (const auto& text : texts) {
            values_.push_back(std::stod(text));        // may throw invalid_argument
        }
    }

    // Strong guarantee
    void append_strong(const std::vector<std::string>& texts) {
        std::vector<double> staged{values_};
        for (const auto& text : texts) {
            staged.push_back(std::stod(text));
        }
        values_ = std::move(staged);
    }
    ...
};
```

Feed both the same batch with a bad value in the third position:

```
basic guarantee:
  failed, log holds 2 readings (valid, but half done)
strong guarantee:
  failed, log holds 0 readings (as if nothing happened)
```

`append_basic` leaves the two readings that were parsed before the failure. Nothing leaked, the log is perfectly usable, but it holds half of the batch, which is probably not what anyone wanted. `append_strong` does the risky work on a **copy**, and only when everything succeeded does it commit with a move, an operation that cannot fail. That recipe, *work on a copy, then commit with something that cannot throw*, is the way to get the strong guarantee. It has a cost (the copy), which is why the standard library offers the strong guarantee only where it is cheap, and the basic guarantee otherwise.

### A `noexcept` function that throws

The program ends this lecture with a commented line:

```cpp
[]() noexcept { throw std::runtime_error{"too late"}; }();
```

Uncomment it to watch `std::terminate`. `noexcept` is how you tell the compiler that a failing path does not exist, so it can generate simpler code; the price of being wrong is the program.

**Code for this lecture**: `13.5NoexceptAndSafetyGuarantees/main.cpp`.

---

## 13.6 Rethrow, nested exceptions and constructors

In this lecture we deal with three situations: passing an exception on, wrapping it with more context, and an exception that happens while an object is being built.

### Constructors that fail

A constructor has no return value, so an exception is its natural way to report failure. But the object is half built. What happens to it?

```cpp
class Station {
public:
    Station() : antenna_{"antenna"}, battery_{"battery", true}, display_{"display"} {
        std::println("    Station constructed");              // never reached
    }
    ~Station() {
        std::println("    Station destroyed");                // never runs either
    }
private:
    Part antenna_;
    Part battery_;
    Part display_;
};
```

The `Part` constructor throws when it is asked to (`true` in the second one):

```
a constructor that fails:
    antenna built
    antenna destroyed
  caught: battery could not be built
```

Read it carefully:

- `antenna` was fully built, so it **is destroyed** during unwinding.
- `battery` threw while being constructed, so it was never alive and has no destructor call.
- `display` was never reached.
- `Station`'s own destructor does **not** run, because the `Station` object never finished existing.

```
   Station()   antenna ✓ built      → destroyed, in reverse order
               battery ✗ throws     → the construction stops here
               display   never built
               body      never reached        ~Station() never runs
```

So: **the members that were fully built are cleaned up by their own destructors.** That is the whole reason to hold resources in members that own them (a `std::unique_ptr`, a `std::vector`, your own RAII class) and not in raw pointers released by the destructor: if the destructor is not going to run, the members' destructors must do the work.

### The function-try-block

```cpp
class Gateway {
public:
    Gateway() try : link_{"link", true} {
    }
    catch (const std::exception& error) {
        std::println("    Gateway constructor saw: {}", error.what());
    }
private:
    Part link_;
};
```

Ordinary `try` blocks inside the constructor body cannot see exceptions from the member initializers. A **function-try-block** (the `try` before the `:` and the `catch` after the body) can. It is useful to log or to translate, but it cannot make the constructor succeed: when the handler ends, the exception is **rethrown automatically**.

```
function-try-block on a constructor:
    Gateway constructor saw: link could not be built
  main still receives it: link could not be built
```

### Rethrowing with `throw;`

```cpp
void log_and_pass_on() {
    try {
        read_file();
    }
    catch (...) {
        std::println("  logging the failure, then passing it on");
        throw;                                  // rethrows the SAME exception, not a copy
    }
}
```

```
rethrow with throw;
  logging the failure, then passing it on
  main caught: file not found
```

A bare `throw;` inside a handler rethrows the exception object that is being handled, with its **real type**. Do not write `throw error;`: that throws a *copy* of the static type of `error`, which slices a derived exception down to the type in your `catch`.

### Adding context with nested exceptions

"File not found" is accurate and useless at the top of the program: *which* file, *why* was it being read? A layer in the middle knows. It can add that without losing the original:

```cpp
void load_config() {
    try {
        read_file();
    }
    catch (const std::exception&) {
        std::throw_with_nested(std::runtime_error{"configuration could not be loaded"});
    }
}
```

`std::throw_with_nested` throws the new exception **with the current one stored inside it**. At the top, walk the chain:

```cpp
void print_chain(const std::exception& error, int depth = 0) {
    std::println("  {}{}", std::string(static_cast<std::size_t>(depth) * 2, ' '), error.what());
    try {
        std::rethrow_if_nested(error);
    }
    catch (const std::exception& cause) {
        print_chain(cause, depth + 1);
    }
}
```

```
nested exceptions:
  configuration could not be loaded
    file not found
```

`std::rethrow_if_nested` throws the stored cause if there is one and does nothing if there is not, which is why the recursion ends by itself.

### Destructors must not throw

Destructors are `noexcept` by default. A destructor can run *while another exception is unwinding the stack*, and two active exceptions cannot be handled, so an exception escaping a destructor ends the program. If something in a destructor can fail (flushing a file, say), catch it inside and log it or ignore it.

### The summary of the lecture

```
   constructor throws        built members destroyed, the object's destructor does not run
   throw;                    pass the same exception on
   throw_with_nested         wrap it with context, keep the cause
   destructor                never lets an exception out
```

**Code for this lecture**: `13.6RethrowNestedAndConstructors/main.cpp`.

---

## 13.7 `std::expected` in practice

In this lecture we use the other road: errors as values. We build a small chain of steps that can each fail, and see why `std::expected` is nicer than a pile of `if`s.

### The problem

A setting arrives as text, `"interval=30"`, and has to become a number of seconds between 1 and 3600. Three different things can go wrong, and the caller wants to know *which*:

```cpp
enum class ConfigError {
    MissingEquals,
    NotANumber,
    OutOfRange,
};
```

An enum is a perfect error type: small, comparable, no allocation. A helper turns it into text for people.

### Three steps, each can fail

```cpp
std::expected<Setting, ConfigError> split(std::string_view line);
std::expected<int, ConfigError>     to_number(const Setting& setting);
std::expected<int, ConfigError>     check_range(int seconds);
```

Each returns the value it produces, or `std::unexpected{error}`. None throws. (`to_number` uses `std::stoi` internally, catches whatever it throws, and turns it into a `ConfigError`: the boundary where exceptions become values.)

### The long way

```cpp
std::expected<int, ConfigError> interval_plain(std::string_view line) {
    auto setting{split(line)};
    if (!setting) {
        return std::unexpected{setting.error()};
    }
    auto number{to_number(*setting)};
    if (!number) {
        return std::unexpected{number.error()};
    }
    return check_range(*number);
}
```

Correct, and noisy: three lines of plumbing for every step. `if (!x)` tests whether it holds a value, `*x` reads the value, `x.error()` reads the error.

### The chained way

```cpp
std::expected<int, ConfigError> interval_chained(std::string_view line) {
    return split(line)
        .and_then(to_number)
        .and_then(check_range);
}
```

**`and_then(f)`** calls `f` with the value **only if there is one**. If the previous step failed, `f` is skipped and the same error flows to the end. The first error wins and nothing after it runs. The whole function says what it does and nothing else.

```
chained steps:
  'interval=30' -> interval 30 s
  'interval' -> error: no '=' in the setting
  'interval=soon' -> error: the value is not a number
  'interval=99999' -> error: the value is outside 1..3600

same answer both ways: true
```

### The rest of the family

```
   and_then(f)         f(value) returns another expected         chain a step that can fail
   transform(f)        f(value) returns a plain value            change the value, leave errors alone
   transform_error(f)  f(error) returns a new error             change the error type
   or_else(f)          f(error) returns an expected              try to recover
   value_or(x)         the value, or x                           give a default
```

```cpp
auto good{interval_chained("interval=30")};
auto bad{interval_chained("interval=zero")};

good.value_or(60)                                     // 30
bad.value_or(60)                                      // 60
good.transform([](int seconds) { return seconds / 60.0; })       // 0.5 minutes
bad.transform_error([](ConfigError e) { return std::string{describe(e)}; })
bad.or_else([](ConfigError) -> std::expected<int, ConfigError> { return 60; })
```

```
value_or: 30 and 60
transform: 0.5 minutes
transform_error: the value is not a number
or_else: 60
```

### The bridge back to exceptions

```cpp
try {
    std::println("{}", bad.value());
}
catch (const std::bad_expected_access<ConfigError>& access) {
    std::println("value() on an error threw, error was: {}", describe(access.error()));
}
```

`value()` on an `expected` that holds an error **throws** `std::bad_expected_access<E>`, carrying the error. That is the way to go from "errors as values" to "errors as exceptions" in one word, at the place where you decide the failure cannot be handled locally. Using `*bad` instead (without checking) is **undefined behaviour**, the same as dereferencing an empty `std::optional`.

### A guideline

```
   expected    when the caller is likely to handle it, and the error is part of the contract
   exception   when it has to travel far, or in constructors and operators
   both        convert at the boundary: value() turns an error into an exception,
               a catch block turns an exception into an error
```

If your compiler is older: `std::expected` needs GCC 12, Clang 16 (with a library that has it) or MSVC 19.33. Below that, the `tl::expected` library offers the same interface.

**Code for this lecture**: `13.7ExpectedInPractice/main.cpp`.

---

## 13.8 `source_location` and `stacktrace`

In this lecture we look at two tools for the question every failure raises: *where did this happen?*

### `std::source_location`

```cpp
void log_failure(const std::string& message,
                 std::source_location where = std::source_location::current()) {
    std::println("[{}:{}] {}: {}", where.file_name(), where.line(), where.function_name(), message);
}
```

The trick is the **default argument**. A default argument is evaluated **at the call site**, so `current()` captures the location of whoever called `log_failure`, not the location inside it. The old way was a macro (`__FILE__`, `__LINE__`); this needs none.

```cpp
log_failure("the first problem");
log_failure("the second problem");
```

On MSVC:

```
[D:\Sandbox\...\13.8SourceLocationAndStacktrace\main.cpp:40] int __cdecl main(void): the first problem
[D:\Sandbox\...\13.8SourceLocationAndStacktrace\main.cpp:41] int __cdecl main(void): the second problem
```

and on GCC `int main()` for the function name. The text is compiler specific; the file and line are what you need. A source location can be a default argument of a constructor too, which is how an exception can record where it was *created*:

```cpp
explicit TracedError(const std::string& message,
                     std::source_location where = std::source_location::current())
    : std::runtime_error{message + " (at line " + std::to_string(where.line()) + ")"},
      trace_{std::stacktrace::current()} {}
```

### `std::stacktrace`

A source location says *one* place. A **stack trace** says the whole chain of calls that led there, as in the debugger's call stack. `std::stacktrace::current()` captures it, and you can store it, here inside the exception, and print it later when you handle it:

```cpp
catch (const TracedError& error) {
    std::println("\ncaught: {}", error.what());
    std::println("the stack when it was created ({} frames):", error.trace().size());
    for (const auto& frame : error.trace()) {
        std::println("  {}", std::to_string(frame));
    }
}
```

On MSVC, a Debug build:

```
caught: negative sensor id (at line 29)
the stack when it was created (10 frames):
  ...\main.cpp(19): rooster!TracedError::TracedError+0x189
  ...\main.cpp(29): rooster!read_sensor+0xE1
  ...\main.cpp(35): rooster!average+0x25
  ...\main.cpp(44): rooster!main+0x1B2
  ...\exe_common.inl(79): rooster!invoke_main+0x39
  ...
  KERNEL32!BaseThreadInitThunk+0x17
  ntdll!RtlUserThreadStart+0x2C
```

Read from the top: the exception was created in `TracedError`'s constructor, called from `read_sensor` at line 29, called from `average` at line 35, called from `main` at line 44, called by the runtime start-up code. Exactly what you need to find a failure in a log file from a customer's machine.

### On GCC and Clang

Two things to know:

1. **`<stacktrace>` lives in a separate library.** Link with `-lstdc++exp` (GCC 14 and later; older GCC used another name, so check your compiler's documentation). The `CMakeLists.txt` of this lecture does it for you:

   ```cmake
   if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
       target_link_libraries(rooster PRIVATE stdc++exp)
   endif()
   ```

   By hand: `g++ -std=c++23 -g main.cpp -o rooster -lstdc++exp`.

2. **Without `-g` the trace has no file names and line numbers.** On GCC you get only function names and addresses; Clang prints `at :0` for every frame. Build with `-g` (CMake's Debug configuration does) and you get lines like `read_sensor(int) at .../main.cpp:29`.

MinGW GCC 14 does not have `<stacktrace>` at all. If you use it, skip this lecture's second half.

### A word of caution

Capturing a stack trace costs time, because the runtime must walk the stack. Do it for failures that are rare, in diagnostics, in debug builds. Do not put it in an exception that you throw a million times a second.

**Code for this lecture**: `13.8SourceLocationAndStacktrace/main.cpp`.

---

## 13.9 Assertions and a first look at contracts

In this lecture we deal with the third road: the failures that are **bugs**, not conditions of the world. There is no point recovering from "the caller passed an empty vector to a function that documents it needs data". The right response is to find out early, loudly, and fix the caller.

### `static_assert`: checked by the compiler

```cpp
static_assert(std::is_trivially_copyable_v<Reading>, "Readings are copied byte for byte into the log file");
static_assert(sizeof(int) >= 4);
```

`static_assert` is evaluated **while compiling**. If the condition is false, the program does not build, and the message is printed. It costs nothing at run time. Use it to turn a silent assumption into a build error the day it stops being true: a size, a property of a type, a value of a constant. (You saw the same idea in 13.5: `static_assert(std::is_nothrow_move_constructible_v<Frame>)`.)

### `assert`: checked at run time, in Debug

```cpp
double average(const std::vector<Reading>& readings) {
    assert(!readings.empty() && "average of no readings");
    ...
}
```

Calling `average({})` in a Debug build, on GCC:

```
rooster: .../main.cpp:20: double average(const std::vector<Reading>&): Assertion `!readings.empty() && "average of no readings"' failed.
Aborted (core dumped)
```

The condition, the file, the line and the function: enough to go straight to the bug. The `&& "message"` trick puts text in the report, because a string literal is always true.

On **MSVC** the same failure opens a **dialog box** from the debug runtime, and a program started from a script waits for someone to click it. (Our test run hung until we killed it.) If you run tests unattended, that matters.

### What `assert` does in a Release build

Release builds define `NDEBUG`, and `assert` **disappears**:

```
average: -nan          ← GCC, Release, same call; Clang prints "nan"
```

The program carries on with 0 divided by 0. That is the contract of `assert`: it is for bugs found **while developing**. Two rules follow:

- **Never put real work inside an `assert`.** `assert(file.open());` opens the file in Debug and does nothing in Release.
- **Do not use `assert` for conditions that can legitimately happen**, such as an empty list typed in by a user. That is an `expected` or an exception (13.2).

### Design by contract

A function has an **interface** and a **contract** behind it: *what must be true when I am called* (the **precondition**), and *what I promise when I return* (the **postcondition**). Until now the contract lived in comments and in `assert`s inside the body, where the caller cannot see it. C++26 puts it in the **declaration**.

### Contracts in C++26: `pre`, `post`, `contract_assert`

```cpp
double battery_percent(const double volts)
    pre(volts >= 0.0)
    post(r : r >= 0.0 && r <= 100.0)
{
    const double raw{(volts - 3.0) / 1.2 * 100.0};
    const double result{raw < 0.0 ? 0.0 : (raw > 100.0 ? 100.0 : raw)};
    contract_assert(result == result);              // a NaN is never equal to itself
    return result;
}
```

- **`pre(condition)`**: checked on entry. The caller's responsibility.
- **`post(r : condition)`**: checked on return; `r` names the returned value. The function's responsibility. A parameter used in a postcondition must be `const`, which is why the parameter is `const double volts` (the compiler tells you otherwise).
- **`contract_assert(condition)`**: a check in the middle of the body, the contract-world `assert`.

Because `pre` and `post` sit in the declaration, a caller, a reader and a tool can all see the rules without reading the body.

### Running it (GCC 16 only)

**At the time of writing GCC 16 is the only one of our compilers with contracts.** Clang 21 does not know `-fcontracts`, and MSVC has no contracts. So this part of the lecture runs in the GCC container, or on Compiler Explorer (godbolt.org) with GCC trunk and the options below. The `CMakeLists.txt` builds the second program only when the compiler is GCC 16 or newer:

```cmake
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 16)
    add_executable(rooster_contracts main_contracts.cpp)
    target_compile_features(rooster_contracts PRIVATE cxx_std_26)
    target_compile_options(rooster_contracts PRIVATE -fcontracts)
    target_link_options(rooster_contracts PRIVATE -fcontracts)
endif()
```

The flag `-fcontracts` is needed at **link** time too: without it the link fails with an undefined reference to `handle_contract_violation`. By hand: `g++ -std=c++26 -fcontracts main_contracts.cpp -o rooster_contracts`.

A good run:

```
2.5 V -> 0 %
3.6 V -> 50 %
4.2 V -> 100 %
5.0 V -> 100 %
```

Run it with any argument and it calls `battery_percent(-1.0)`, which breaks the precondition:

```
contract violation in function double battery_percent(double) at .../main_contracts.cpp:12: volts >= 0.0
[assertion_kind: pre, semantic: enforce, mode: predicate_false, terminating: yes]
terminate called without an active exception
Aborted (core dumped)
```

The report names the function, the line, the condition and the *kind* (a precondition). **It is not an exception**: the default way of enforcing a contract is to terminate. And unlike `assert`, in our test the precondition **stayed active in a Release build**, because contracts are not tied to `NDEBUG`. How violations are handled, observed or ignored is configurable (the compiler has options for the "evaluation semantic"), and C++26 allows a program to install its own violation handler. We stay with the default here.

### The three tools

```
   static_assert     compile time    a fact about types, sizes, constants            costs nothing
   assert            run time        "this is a bug if false"; gone with NDEBUG      development only
   pre/post          run time        part of the interface; C++26, GCC 16 so far     stays on by default
```

None of these is for errors that happen to correct programs. For those, return an `expected` or throw.

**Code for this lecture**: `13.9AssertionsAndContracts/` (`main.cpp`, and `main_contracts.cpp` for GCC 16).

---

## 13.10 Project 6a: testing by hand

Chapters 12 and 13 have produced a class, `Matrix`, with a long list of promises: it adds, multiplies, transposes, and **throws** `std::invalid_argument` and `std::out_of_range` when asked to do something impossible. How do you know it keeps those promises? You test it. And since a test is only a program that checks another program, the best way to understand testing frameworks is to **write a tiny one first**.

The project has three folders that test the **same** `Matrix` with the **same** thirteen ideas:

```
   13.10ProjectTestingByHand    our own harness, 100 lines          nothing to install
   13.11ProjectGoogleTest       GoogleTest                          vcpkg, manifest mode
   13.12ProjectCatch2           Catch2                              vcpkg, manifest mode
```

Each folder holds its own copy of `matrix.h` (from 12.7) so that it is self-contained.

### What a test framework has to do

```
   1. run each test in isolation        one failing test must not hide the others
   2. keep going after a failed check   report ALL the failures
   3. report which test, which line     so you can find it
   4. tell the build system the result  through the exit code
```

### Our harness

```cpp
struct TestCase {
    std::string name;
    std::function<void()> body;
};

void check(bool condition, std::string_view expression,
           std::source_location where = std::source_location::current()) {
    ++checks_run;
    if (!condition) {
        report_failure(expression, where);
    }
}
#define CHECK(expression) check((expression), #expression)
```

`check` records a failure instead of stopping, and the `source_location` default argument (13.8) reports the line of the **caller**. The one macro in the whole file exists for a single reason: only the preprocessor can turn the expression `a == b` into the *text* `"a == b"` for the failure message. (GoogleTest and Catch2 are built on macros for the same reason.)

Checking that something **throws** is where lambdas help. The code under test goes in a lambda, so the harness can run it inside its own `try`:

```cpp
template <typename Expected>
void check_throws(const std::function<void()>& code,
                  std::source_location where = std::source_location::current()) {
    ++checks_run;
    try {
        code();
    }
    catch (const Expected&) {
        return;                                          // the right type: pass
    }
    catch (const std::exception& error) {
        report_failure(std::format("threw a different exception: {}", error.what()), where);
        return;
    }
    report_failure("did not throw", where);
}
```

Three outcomes, all distinguished: it threw the right type (pass), it threw something else (fail, with the message), it did not throw (fail).

### The tests

One behaviour each, named for what they prove:

```cpp
void ragged_initializer_list_is_rejected() {
    check_throws<std::invalid_argument>([] { Matrix m{{1, 2}, {3}}; });
}

void matrix_product_multiplies_rows_by_columns() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};          // 2 x 3
    Matrix b{{1, 0}, {0, 1}, {2, 2}};        // 3 x 2
    CHECK((a * b == Matrix{{7, 8}, {16, 17}}));
    CHECK((a * Matrix::identity(3) == a));
}

void floating_point_needs_a_tolerance() {
    Matrix sum{Matrix{{0.1}} + Matrix{{0.2}}};
    CHECK((sum[0, 0] != 0.3));                // the trap: 0.1 + 0.2 is not exactly 0.3
    check_near(sum[0, 0], 0.3);
}
```

Notice the double parentheses in `CHECK((a * b == Matrix{{7, 8}, {16, 17}}))`: the macro splits its arguments at commas, and braces do not protect a comma. Extra parentheses do. That is the price of macros.

And the floating-point test: `0.1 + 0.2` is **not** `0.3` (the warning in 12.7), so you compare with a **tolerance**. `Matrix::operator==` compares exactly, which is right for exact data but a trap after arithmetic.

`main` collects the tests in a vector, runs each inside a `try` (an exception nobody expected is a failure, not a crash) and decides the exit code:

```cpp
return checks_failed == 0 ? 0 : 1;
```

### Build and run

```
cmake -S . -B build -G Ninja
cmake --build build
./build/rooster              (build\rooster.exe on Windows)
```

```
[ ok ] construction_sets_shape_and_fill
[ ok ] initializer_list_reads_row_by_row
[ ok ] ragged_initializer_list_is_rejected
[ ok ] identity_has_ones_on_the_diagonal
[ ok ] at_checks_the_index
[ ok ] addition_subtraction_and_scaling
[ ok ] adding_different_shapes_is_rejected
[ ok ] matrix_product_multiplies_rows_by_columns
[ ok ] product_with_incompatible_shapes_is_rejected
[ ok ] transposing_swaps_rows_and_columns
[ ok ] equality_compares_shape_and_cells
[ ok ] floating_point_needs_a_tolerance
[ ok ] formatter_prints_one_row_per_line

13 tests, 0 failed; 33 checks, 0 failed
```

It passed on MSVC, GCC 16 and Clang 21.

### What a failure looks like

Run it with any argument and it adds one test that is wrong on purpose:

```
$ ./build/rooster x
...
  FAILED in deliberately_wrong (line 187): m.rows() == 3
  FAILED in deliberately_wrong (line 188): did not throw
[FAIL] deliberately_wrong

14 tests, 1 failed; 35 checks, 2 failed
```

Both failures are reported (it did not stop at the first), with the test name and line.

### CTest: telling the build system

```cmake
enable_testing()
add_test(NAME matrix_tests COMMAND rooster)
```

A test, to CTest, is **a command**. Exit code `0` means pass, anything else means fail. That is why `main` returns `1`. After building:

```
ctest --test-dir build
100% tests passed, 0 tests failed out of 1
```

This is also how a CI server asks "did it work": it runs a command and looks at the exit code.

### Testing the tests

A test that cannot fail proves nothing. Try it: in `matrix.h`, comment out the shape check in the first `require_same_shape(other);` (in `operator+=`) and rebuild. We did, and the harness reports:

```
  FAILED in adding_different_shapes_is_rejected (line 121): did not throw
  FAILED in adding_different_shapes_is_rejected (line 122): did not throw
[FAIL] adding_different_shapes_is_rejected
13 tests, 1 failed; 33 checks, 2 failed
```

Lines 121 and 122 are `a + b` and `a += b`, the two operations that go through `+=`. `a -= b` still throws, so the third check passed. The tests found exactly the change. Restore the line.

**Code for this project**: `13.10ProjectTestingByHand/` (`main.cpp`, `matrix.h`, `CMakeLists.txt`).

---

## 13.11 Project 6b: GoogleTest

**GoogleTest** (gtest) is the most widely used C++ test framework, from Google. Everything you wrote by hand in 13.10 is already in it, polished, plus a lot more. We get it through **vcpkg in manifest mode**, exactly as in 12.12.

### The project files

```
   13.11ProjectGoogleTest/
      matrix.h            the Matrix, copied from 12.7
      matrix_tests.cpp    the tests
      vcpkg.json          "dependencies": [ "gtest" ], and the builtin-baseline
      CMakePresets.json   configure, build and TEST presets, using the vcpkg toolchain file
      CMakeLists.txt
      build-windows.ps1, build-linux.sh      the answer key
```

`vcpkg.json` is just:

```json
{
  "name": "matrix-tests-gtest",
  "version": "0.1.0",
  "dependencies": [
    "gtest"
  ],
  "builtin-baseline": "30ef65cad98f08e7197c9a1656fbd871bcb72f2d"
}
```

The `CMakeLists.txt` adds three things to the usual:

```cmake
find_package(GTest CONFIG REQUIRED)

add_executable(rooster matrix_tests.cpp matrix.h)
target_link_libraries(rooster PRIVATE GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(rooster)
```

`GTest::gtest_main` supplies `main()`, so the file contains only tests. `gtest_discover_tests` asks the finished program for its list of tests and registers **each one separately** with CTest.

### The tests

```cpp
TEST(MatrixConstruction, SetsShapeAndFill) {
    Matrix m{2, 3, 7.0};
    EXPECT_EQ(m.rows(), 2u);
    EXPECT_EQ(m.columns(), 3u);
    EXPECT_DOUBLE_EQ((m[1, 2]), 7.0);          // extra parentheses: the macro sees the comma
}

TEST(MatrixConstruction, RaggedInitializerListIsRejected) {
    EXPECT_THROW((Matrix{{1, 2}, {3}}), std::invalid_argument);
}
```

`TEST(Suite, Name)` defines a test. The `EXPECT_*` macros are our `CHECK`: they record a failure and **continue**. Their cousins `ASSERT_*` stop the test at the first failure, useful when later lines would crash without the earlier check (a null pointer, say). The ones we use:

```
   EXPECT_EQ(a, b)            equal                       EXPECT_NE   not equal
   EXPECT_DOUBLE_EQ(a, b)     equal within 4 ULPs, for doubles (the 0.1 + 0.2 case)
   EXPECT_NEAR(a, b, tol)     within an explicit tolerance
   EXPECT_THROW(code, Type)   throws exactly that type (or a derived one)
   EXPECT_NO_THROW(code)      does not throw
```

### A fixture

```cpp
class MatrixTest : public testing::Test {
protected:
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{10, 20}, {30, 40}};
};

TEST_F(MatrixTest, AdditionSubtractionAndScaling) {
    EXPECT_EQ(a + b, (Matrix{{11, 22}, {33, 44}}));
    EXPECT_EQ(b - a, (Matrix{{9, 18}, {27, 36}}));
    ...
}
```

`TEST_F` runs the test as a member of the fixture class, and GoogleTest builds a **fresh** `MatrixTest` for every test that uses it. The members are your common setup, rebuilt each time, so one test cannot leave behind anything that changes another. (The `F` stands for *fixture*.)

### Teaching it to print a `Matrix`

When `EXPECT_EQ` fails it prints both sides. For a type it does not know, it prints raw bytes, which is useless. `PrintTo` teaches it:

```cpp
void PrintTo(const Matrix& matrix, std::ostream* out) {
    *out << "\n" << std::format("{}", matrix);
}
```

(It reuses the `std::formatter<Matrix>` of 12.4. GoogleTest finds `PrintTo` through the argument, as it would an `operator<<`.)

### Build and run

On Windows, in a Developer PowerShell, and in the Linux containers, the answer-key scripts do the same four commands:

```
cmake --preset default            # vcpkg reads vcpkg.json and builds gtest (first time: a few minutes)
cmake --build --preset default
./build/rooster                   # the program itself
ctest --preset default            # through CTest
```

`CMakePresets.json` now has a `testPresets` section too, so `ctest --preset default` needs no arguments.

```
[==========] 13 tests from 8 test suites ran. (0 ms total)
[  PASSED  ] 13 tests.
```

and through CTest, one line per test:

```
 1/13 Test  #1: MatrixConstruction.SetsShapeAndFill ....................   Passed    0.00 sec
 2/13 Test  #2: MatrixConstruction.InitializerListReadsRowByRow ........   Passed    0.00 sec
...
13/13 Test #13: MatrixFormatter.PrintsOneRowPerLine ....................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 13
```

All 13 passed on MSVC (with the Visual Studio copy of vcpkg), on GCC 16 and on Clang 21.

### What a failure looks like

At the bottom of `matrix_tests.cpp` there is a commented-out test that is wrong on purpose. Uncommenting it gives:

```
[ RUN      ] Demo.DeliberatelyWrong
.../matrix_tests.cpp:112: Failure
Expected equality of these values:
  m
    Which is:
  [   1.0    2.0 ]
  [   3.0    4.0 ]
  (Matrix{{1, 2}, {3, 5}})
    Which is:
  [   1.0    2.0 ]
  [   3.0    5.0 ]

[  FAILED  ] Demo.DeliberatelyWrong (0 ms)
```

Compare with our harness: the same information (file, line, what was compared) and, thanks to `PrintTo`, **both values**, which is the thing the hand-made `CHECK` could not give.

**Code for this project**: `13.11ProjectGoogleTest/`.

---

## 13.12 Project 6c: Catch2

**Catch2** (version 3 here) has the same job and a different feel. Fewer macros to learn, tests written as plain functions with sections, and a very readable failure report. Same recipe: vcpkg manifest mode.

### The project files

The same as 13.11, with `"catch2"` in `vcpkg.json`, and in `CMakeLists.txt`:

```cmake
find_package(Catch2 3 CONFIG REQUIRED)

add_executable(rooster matrix_tests.cpp matrix.h)
target_link_libraries(rooster PRIVATE Catch2::Catch2WithMain)

enable_testing()
include(Catch)
catch_discover_tests(rooster)
```

`Catch2::Catch2WithMain` supplies `main()`. `catch_discover_tests` registers every `TEST_CASE` with CTest.

### Test cases and sections

```cpp
TEST_CASE("Matrix arithmetic", "[matrix]") {
    // Runs again for every SECTION below.
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{10, 20}, {30, 40}};

    SECTION("addition, subtraction and scaling") {
        CHECK(a + b == Matrix{{11, 22}, {33, 44}});
        CHECK(b - a == Matrix{{9, 18}, {27, 36}});
    }

    SECTION("different shapes are rejected") {
        Matrix wide{2, 3};
        CHECK_THROWS_AS(a + wide, std::invalid_argument);
        CHECK_THROWS_WITH(a + wide, "matrices must have the same shape");
    }
}
```

Catch2 has **no fixture classes**. A test case is a function, and the code above a `SECTION` is the setup. The test case runs **once per section, from the top**, so each section gets freshly constructed `a` and `b`. It gives you what `TEST_F` gave you with less ceremony.

Two details you can see above:

- `CHECK(a + b == Matrix{{11, 22}, {33, 44}})` has **no extra parentheses and no `EXPECT_EQ`**. `CHECK` takes the whole expression, even with commas in it (its macro is variadic), and decomposes it so the failure report can show both sides.
- `CHECK_THROWS_WITH` checks the *message* as well. Earlier we said never to compare `what()` to decide what happened; in a **test** of your own class, where the message is part of what you wrote, it is reasonable. For library messages (13.4) it would break between compilers.

For floating point, Catch2 has two idioms:

```cpp
CHECK((sum[0, 0] == Catch::Approx(0.3)));                          // relative tolerance
CHECK_THAT((sum[0, 0]), Catch::Matchers::WithinAbs(0.3, 1e-9));    // absolute tolerance
```

### Teaching it to print a `Matrix`

```cpp
template <>
struct Catch::StringMaker<Matrix> {
    static std::string convert(const Matrix& matrix) {
        return "\n" + std::format("{}", matrix);
    }
};
```

Without it, Catch2 prints `{?}` for an unknown type. This is its version of GoogleTest's `PrintTo`.

### Build and run

The scripts and commands are the same as in 13.11 (`cmake --preset default`, `cmake --build --preset default`, `./build/rooster`, `ctest --preset default`).

```
All tests passed (36 assertions in 6 test cases)
```

and CTest sees six tests:

```
1/6 Test #1: Matrix access .............................   Passed    0.00 sec
2/6 Test #2: Matrix arithmetic .........................   Passed    0.00 sec
3/6 Test #3: Matrix construction .......................   Passed    0.00 sec
...
100% tests passed, 0 tests failed out of 6
```

Also verified on MSVC, GCC 16 and Clang 21. (Catch2 prints a "Randomness seeded to" line at the start; it is for tests that use random numbers.)

### What a failure looks like

The commented-out demo at the bottom of the file, uncommented and run, prints:

```
.../matrix_tests.cpp:120: FAILED:
  CHECK( m == Matrix{{1, 2}, {3, 5}} )
with expansion:

  [   1.0    2.0 ]
    [   3.0    4.0 ]
  ==

  [   1.0    2.0 ]
    [   3.0    5.0 ]
```

Note that the report shows the **expression as you wrote it** (`CHECK( m == Matrix{{1, 2}, {3, 5}} )`) *and* its expansion with the values. That is the feature people love in Catch2.

### Which one?

```
                      by hand            GoogleTest              Catch2
   define a test      function in table  TEST(Suite, Name)       TEST_CASE("text")
   setup              lines in the test  fixture class (TEST_F)  code above a SECTION
   compare            CHECK(a == b)      EXPECT_EQ(a, b)         CHECK(a == b)
   expect a throw     check_throws<E>    EXPECT_THROW(code, E)   CHECK_THROWS_AS(code, E)
   print own types    nothing            PrintTo                 StringMaker
   mocks              no                 yes (GoogleMock)        no
```

Both are good and both are common. GoogleTest comes with GoogleMock for replacing collaborators in tests; Catch2 reads more like plain C++. Choose the one your team already uses, and write tests either way.

### The takeaway

- **Exceptions and tests belong together.** Half of what the `Matrix` promises is that it *refuses* impossible requests, and only a test that expects the throw can prove it.
- **A test framework is small.** You wrote one in 13.10.
- **Failing on purpose** is part of the work: once, to see the report; and by breaking the code (the mutation of 13.10) to prove the tests can fail.

Suggestion for yourself: add a test to each of the three for something we did not cover (`operator-=` with equal shapes, `*=` by zero, a one-by-one matrix), then try to make it fail.

**Code for this project**: `13.12ProjectCatch2/`.

---

## 13.13 Assignment

Eight small jobs for the weather station, one idea of the chapter each. `main.cpp` has the eight exercises, each with its statement and a sample run in a comment, plus a few provided pieces (a `Sensor` lookup that returns an `std::expected`, a file reader that always fails, and a tiny test harness). You write each function or class above `main()` and the lines that use it under its heading. `main_solution.cpp` solves all eight. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `parse_percent` | `std::from_chars`, `std::invalid_argument` and `std::out_of_range` in two separate handlers |
| 2 | `CalibrationError` | a custom exception derived from `std::runtime_error`, with data, built with `std::format` |
| 3 | `fahrenheit` | `std::expected::transform` instead of an `if` |
| 4 | `ReadingBuffer` | the strong guarantee: work on a copy, commit at the end |
| 5 | `Connection` | RAII and stack unwinding: a counter that returns to zero after a throw |
| 6 | `load_station` | `std::throw_with_nested`, `std::rethrow_if_nested`, a recursive `print_chain` |
| 7 | `Frame` | a `noexcept` move, `static_assert(std::is_nothrow_move_constructible_v<...>)`, and what `vector` does |
| 8 | `percent_of` | `std::domain_error`, `std::invalid_argument`, and five checks with the provided harness |

Exercise 7 ends with a question to answer in your own words: remove the `noexcept`, rebuild, and explain why the number of copies changed.

The testing project (13.10 to 13.12) has no exercise of its own: the exercise is to build and run each folder, break the `Matrix` on purpose to see a test fail, and add a test of your own.

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole chapter.

After this chapter the student can choose between returning an error and throwing one, write and catch exceptions in the right order, know what `noexcept` promises and why `std::vector` cares, write code that keeps the strong guarantee, use `std::expected` chains, find out where a failure came from, tell a bug from a condition (`assert`, `static_assert`, and the idea behind C++26 contracts), and test a class, including its error paths, with a hand-made harness, GoogleTest and Catch2. The next chapter turns to **containers and iterators**: how the standard library stores your data, and how to choose the right container for the job.
