# Chapter 13 Quiz - Exceptions and a First Look at Contracts

20 multiple-choice questions covering **Chapter 13 (Exceptions and Contracts)**: choosing an
error-handling strategy, `throw`, `try` and `catch`, stack unwinding, the standard
hierarchy and custom exceptions, `noexcept` and the safety guarantees, rethrowing and
nested exceptions, `std::expected`, `std::source_location`, assertions and contracts, and
the testing project (a hand-rolled harness, GoogleTest, Catch2). Each question is followed
immediately by its correct answer and a short explanation.

---

### 1. A function turns text typed by a user into a number, and bad input is expected to be common. Which way of reporting failure fits best?

A. Throw an exception for every bad input
B. Return `std::expected<double, Error>` so the caller must look at the outcome
C. Call `std::terminate` and restart the program
D. Return `-1` and document that it means "failed"

**Answer: B** - when failure is a normal outcome, a return type that carries the reason keeps the failure on the main road and cannot be ignored by accident. Exceptions are for rare failures that the immediate caller cannot handle. A magic return value like `-1` can be a legal result and is easy to forget to check.

### 2. Why does GoogleTest offer `TEST_F` with a fixture class?

A. It makes tests run faster by sharing one object
B. It lets a test call private members of the code under test
C. It runs the tests in a fixed order
D. A fresh fixture object is built for every test, so each test starts from the same state

**Answer: D** - the members of the fixture are rebuilt before each `TEST_F`, so one test cannot leave behind data that changes the result of another. Sharing state between tests is exactly what you want to avoid.

### 3. An exception is thrown inside a function. What happens to the local objects of the functions it leaves?

A. Their destructors run, in reverse order of construction (stack unwinding)
B. They are leaked, because the function never reached its end
C. Their destructors run only if they were declared `noexcept`
D. They are kept alive until the handler finishes, then copied

**Answer: A** - as the exception travels up the call stack, every scope it leaves is cleaned up properly. That is why RAII classes (10.6) make exception-safe code almost free.

### 4. What is wrong with this code?

```cpp
try { risky(); }
catch (const std::exception& e)    { std::println("{}", e.what()); }
catch (const std::out_of_range& e) { std::println("range"); }
```

A. Nothing, the second handler catches range errors first
B. `std::out_of_range` cannot be caught by reference
C. The second handler can never run, because the first one already matches it
D. It does not compile

**Answer: C** - handlers are tried in order and the first match wins. `std::out_of_range` derives from `std::exception`, so the general handler catches it first. Put the specific handlers first and the general one last (GCC warns about this with `-Wall`; Clang does not).

### 5. Why should you catch exceptions by `const` reference and not by value?

A. By value is not allowed in C++
B. A reference avoids a copy and slicing, so the exception keeps its real derived type
C. A reference makes the handler `noexcept`
D. A `const` reference lets the handler change the exception

**Answer: B** - catching a `std::runtime_error` by value when a `SensorError` was thrown would slice it (11.4) and lose the extra data. A `const` reference cannot modify the exception, it only avoids copying and slicing.

### 6. `std::out_of_range` and `std::invalid_argument` share a parent class in the standard hierarchy. Which one?

A. `std::logic_error`
B. `std::runtime_error`
C. `std::bad_alloc`
D. `std::system_error`

**Answer: A** - both belong to the "logic errors", problems the caller could have avoided by checking first. `std::runtime_error` and its children (`std::overflow_error`, `std::system_error`) describe failures nobody could have predicted.

### 7. How should you write your own exception class for a sensor failure?

A. Derive from `int`, so it can be thrown cheaply
B. Make it a standalone class with no base, to keep it small
C. Make it a function that returns an error text
D. Derive from the closest standard class, such as `std::runtime_error`, and add the data a handler needs

**Answer: D** - a handler for `std::runtime_error` or `std::exception` still catches your type, and you can add members (the sensor id, the bad value) for handlers that care. Any type can be thrown, but anything that is not a `std::exception` escapes the usual catch-all.

### 8. Why does the move constructor of a type usually need `noexcept`?

A. Without it the type cannot be stored in a `std::vector`
B. Without it the move constructor is deleted
C. `std::vector` only moves its elements when it grows if the move cannot throw; otherwise it copies them
D. `noexcept` makes the move faster by skipping the copy

**Answer: C** - when the vector reallocates it must keep its old contents safe if an element move throws halfway. So it uses `std::move_if_noexcept`: a throwing move is replaced by a copy. In 13.5 the same type made 0 copies with `noexcept` and a copy per element without it.

### 9. A function marked `noexcept` lets an exception escape. What happens?

A. The exception propagates normally to the caller
B. `std::terminate` is called and the program ends
C. The exception is silently discarded
D. The compiler refuses to compile the function

**Answer: B** - `noexcept` is a promise, and it is enforced at run time. The exception does not leave the function; the program ends. That is why you only mark functions that truly cannot fail.

### 10. What does the **strong** exception safety guarantee promise?

A. If the operation throws, nothing observable has changed, as if it had never been called
B. The operation never throws
C. No memory is leaked, but the object may be half modified
D. The exception is always caught inside the function

**Answer: A** - strong means "commit or rollback". The usual recipe is to do the risky work on a copy and swap or move it in at the end. The weaker **basic** guarantee (C) only promises no leaks and a valid object.

### 11. What is the difference between `throw;` and `throw error;` inside a `catch (const std::exception& error)` block?

A. There is none, both rethrow the same object
B. `throw;` ends the program
C. `throw error;` is the only one that keeps the derived type
D. `throw;` rethrows the same exception object with its real type, `throw error;` throws a copy of the static type `std::exception`

**Answer: D** - a bare `throw;` passes on exactly what was caught. `throw error;` copies the object as a plain `std::exception`, slicing away the derived part.

### 12. A constructor throws after two of its three member objects were built. What is destroyed?

A. Nothing, the object never existed
B. The whole object, including the member that failed
C. The two fully built members, in reverse order. The object's own destructor does not run
D. All three members, using the object's destructor

**Answer: C** - an object whose constructor did not finish was never fully alive, so its destructor does not run, but everything that was fully constructed is cleaned up. This is why members that own resources (RAII) make a failing constructor safe.

### 13. What does `std::throw_with_nested(new_exception)` do inside a `catch` block?

A. Throws only the new exception and forgets the old one
B. Throws the new exception with the currently handled exception stored inside it, retrievable with `std::rethrow_if_nested`
C. Throws the old exception again
D. Throws both exceptions at the same time

**Answer: B** - it adds context ("cannot load station north") without losing the cause ("cannot open north.dat"). Only one exception travels; the cause rides inside it.

### 14. Why must you never let an exception escape from a destructor?

A. Destructors cannot contain `try` blocks
B. The exception would be caught by the constructor
C. Destructors are `noexcept` by default, so an escaping exception ends the program, and it is also deadly during unwinding
D. It would leak the object's memory only

**Answer: C** - a destructor can run while another exception is already unwinding the stack, and two active exceptions cannot be handled. Catch inside the destructor and log or ignore.

### 15. What does `.and_then(f)` do on a `std::expected<T, E>`?

A. Calls `f` with the value only if there is one, and passes an existing error through untouched
B. Calls `f` with the error
C. Always calls `f`, even when the result holds an error
D. Throws if `f` returns an error

**Answer: A** - it chains steps that can each fail: the first error skips everything after it and comes out unchanged. `.or_else` is the one that reacts to the error, `.transform` changes the value.

### 16. What does `value()` do on a `std::expected` that holds an error?

A. Returns an empty value
B. Returns the error
C. Is undefined behaviour
D. Throws `std::bad_expected_access<E>` carrying the error

**Answer: D** - `value()` is the bridge back to exceptions. `operator*` on an error is undefined behaviour (check first, or use `value_or`).

### 17. What does `std::source_location::current()` record when it is used as a default argument?

A. The location of the function definition
B. The location of the call, where the caller wrote the call
C. The location of the first `#include`
D. Nothing in a Release build

**Answer: B** - a default argument is evaluated at the call site, so a logging helper reports the line of the caller without a macro. Calling `current()` in the body of the helper would report the helper's own line.

### 18. Which statement about `assert` and `static_assert` is true?

A. `static_assert` is checked by the compiler and costs nothing at run time. `assert` is checked at run time and disappears when `NDEBUG` is defined
B. Both are checked at run time
C. `assert` is always active, `static_assert` only in Debug builds
D. Both are removed in Release builds

**Answer: A** - `static_assert` turns a wrong assumption into a build error. `assert` guards against bugs while you develop, so a Release build (which defines `NDEBUG`) removes it, side effects included: never put real work inside it.

### 19. How do C++26 contracts such as `pre(x >= 0)` differ from `assert`?

A. They are only comments for the reader
B. They are checked by the compiler before the program runs
C. They are written in the function's declaration, so callers and tools can see them, and they can describe the result too (`post`)
D. They throw `std::logic_error`

**Answer: C** - a contract is part of the interface. In the GCC 16 test of 13.9 a violation printed the failed expression and terminated by default (not an exception), and the precondition stayed active in a Release build. As of this chapter only GCC 16 implements contracts.

### 20. Why does the hand-rolled test program of 13.10 return `1` when a check failed?

A. It makes the program print the failure message
B. It is required by the C++ standard
C. It stops the remaining tests from running
D. A non-zero exit code is how CTest and build servers learn that the tests failed

**Answer: D** - a test runner is just a program. Whoever starts it (CTest, a CI job, a script) only sees the exit code, so `0` means pass and anything else means fail. GoogleTest and Catch2 do the same.
