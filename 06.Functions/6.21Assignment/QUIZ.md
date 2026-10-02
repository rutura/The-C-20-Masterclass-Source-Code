# Chapter 6 Quiz — Functions

20 multiple-choice questions covering **Chapter 6 (Functions)** as it now
stands: program components and the call stack, the standard-library tour
(`<cmath>`/`<numbers>`, `<numeric>`, `<algorithm>`, `<string>`, `<bit>`),
declarations vs signatures, argument coercion and evaluation order,
default arguments, random numbers, scope / `static` locals / `::`,
passing by value vs reference, overloading, function templates, recursion,
attributes, and the image project (fixed-width integer types, the 2D→1D
pixel mapping, stride). Each question is followed immediately by its
correct answer and a short explanation.

---

### 1. Why factor a repeated block of code into a function?

A. Functions always run faster than the same code written inline
B. The compiler rejects any function longer than 20 lines unless it is split up
C. Reuse — one definition to write, read, and change, called from wherever it is needed
D. Only functions are allowed to declare local variables

**Answer: C** — a function gives repeated work a single home. A fix or change happens in one place instead of in every copy.

### 2. Calling `std::clamp(v, 0, 100)` versus calling a function you wrote yourself is...

A. the same syntax: the name, then the arguments in parentheses
B. different — library calls need the keyword `call` in front
C. only possible from `main`
D. slower, because library functions live in a separate file

**Answer: A** — `#include` the header, then `name(arguments)`. A standard-library call looks exactly like a call to your own function; the library just already wrote it.

### 3. Which header would you include for `std::gcd` and `std::lcm`?

A. `<cmath>`
B. `<algorithm>`
C. `<numbers>`
D. `<numeric>`

**Answer: D** — `<numeric>` holds the numeric helpers `std::gcd` (greatest common divisor) and `std::lcm` (least common multiple). `<cmath>` is floating-point math functions; `<numbers>` is math *constants* like `std::numbers::pi`.

### 4. `std::lerp(0.0, 100.0, 0.25)` produces...

A. `0.25`
B. `25.0` — a quarter of the way from `0` to `100`
C. `100.0`
D. a compile error — `lerp` takes two arguments

**Answer: B** — `std::lerp(a, b, t)` (C++20) slides from `a` to `b` by the fraction `t`: `t = 0` gives `a`, `t = 1` gives `b`, `t = 0.25` gives `25.0`.

### 5. What does `std::clamp(v, lo, hi)` return when `v` is above `hi`?

A. `hi`
B. `v` unchanged
C. `lo`
D. the midpoint of `lo` and `hi`

**Answer: A** — `clamp` (C++17) forces `v` into `[lo, hi]`: below `lo` it returns `lo`, above `hi` it returns `hi`, otherwise `v` itself. Exercise 2's `bar()` uses it so the bar length can never exceed the width.

### 6. `s.starts_with("http")` and `s.contains("lo wo")` on a `std::string` were added in which standards?

A. Both in C++11
B. Both in C++23
C. Neither exists — you must use `s.find(...)`
D. `starts_with` / `ends_with` in C++20, `contains` in C++23

**Answer: D** — `starts_with` and `ends_with` arrived in C++20; `contains` in C++23. Before `contains`, the idiom was `s.find(sub) != std::string::npos`.

### 7. `std::popcount(x)` from `<bit>` (C++20) tells you...

A. the value of `x` doubled
B. how many bits of `x` are set to `1`
C. the position of the lowest set bit
D. whether `x` is negative

**Answer: B** — `popcount` is the population count: the number of `1` bits. `std::has_single_bit(x)` is the related "is exactly one bit set", i.e. "is `x` a power of two".

### 8. What is a function *prototype* (declaration)?

A. The full function including its `{ }` body
B. The first call to the function in the program
C. The signature — return type, name, parameter types — ended with a semicolon, no body
D. A comment above the function describing what it does

**Answer: C** — a prototype is a promise that a function of this shape exists somewhere. Parameter names in it are optional; only the types matter. A program may repeat the declaration but must have exactly one definition.

### 9. Why is the return type *not* part of a function's signature?

A. Because two functions differing only in return type could not be told apart at a call site, so the language forbids that pair
B. It is — the return type is the first element of the signature
C. Only `void` is excluded from the signature
D. Return types are only ignored for templates

**Answer: A** — `int parse(std::string_view)` and `double parse(std::string_view)` have the same signature `parse(std::string_view)`. `parse("42")` alone cannot say which you meant, so this is a redefinition error, not an overload.

### 10. Given `void bar(int value, int width = 40, char fill = '*');`, where do the default values belong, and what does `bar(10)` do?

A. In the definition; it is an error to omit an argument
B. In both the prototype and the definition, with identical values
C. Anywhere, and `bar(10)` is a compile error
D. In the prototype only (not repeated in the definition); `bar(10)` uses `width = 40`, `fill = '*'`

**Answer: D** — defaults are written once, on the prototype. Arguments fill in left to right, so `bar(10)` leaves `width` and `fill` at their defaults. Repeating the defaults on the definition is an error.

### 11. In `double square(double v);`, what happens at the call `square(4)`?

A. It fails to compile — `int` is not `double`
B. The result is silently truncated back to an `int`
C. Argument coercion widens `4` to `4.0` (a safe `int`→`double` conversion) and squares it
D. It calls a different, `int`-taking overload

**Answer: C** — argument coercion converts the `int` to the parameter's type. `int`→`double` is a safe widening conversion, applied silently. This is also why `describe(4.0)` in Exercise 4 needs the `.0`: `describe(4)` would coerce nothing and just match `describe(int)`.

### 12. What does the standard guarantee about the order in which a call's arguments are evaluated?

A. Strictly left to right
B. Nothing — the order is unspecified, so arguments must not have side effects that another argument can observe
C. Strictly right to left
D. The order the parameters were declared in

**Answer: B** — `f(n++, n)` is not portable: which argument reads `n` first is unspecified. Do any side-effecting work in its own statement first.

### 13. A default-constructed `std::default_random_engine engine{};` (no seed) produces...

A. a different sequence every run
B. only zeros until it is seeded
C. a compile error — engines must be seeded
D. the same sequence every run

**Answer: D** — an unseeded engine has a fixed hidden starting point and replays the same sequence each run. Handy for reproducible tests; seed it to vary the output.

### 14. How do you make the engine produce a fresh sequence on each run?

A. Seed the engine from a nondeterministic source: `std::default_random_engine engine{std::random_device{}()};`
B. Call the distribution more times before using its result
C. Widen the distribution's range
D. You cannot — engines are always deterministic

**Answer: A** — `std::random_device` yields a nondeterministic value to seed with, giving a different sequence every run. A fixed integer seed instead gives reproducibility. Exercise 5 seeds a `static` local engine this way, once.

### 15. In Exercise 5, `next_roll()` declares its engine and distribution as `static` locals. What does that achieve?

A. Nothing — `static` on a local has no effect
B. It makes the engine visible to other functions in the file
C. They are constructed once, on the first call, and reused on every later call, so the engine is seeded a single time and the sequence continues across calls
D. It resets the engine to its seed on every call

**Answer: C** — a `static` local is initialized the first time control passes its declaration and keeps its state between calls. Without `static`, each call would build and reseed a new engine and you would get the same first roll every time.

### 16. A local variable named `count` hides a global also named `count`. How do you name the global inside that scope?

A. You cannot — the global is permanently shadowed
B. `::count` — the unary scope-resolution operator skips local declarations
C. Rename the local
D. `global::count`

**Answer: B** — `::count` refers to the global. A bare `count` in that scope still means the local.

### 17. After `int by_value(int n) { n *= n; return n; }` is called as `by_value(x)` with `x == 3`, what is `x`?

A. `9`
B. `0`
C. undefined
D. `3` — `n` is a copy; the caller's `x` is untouched

**Answer: D** — pass by value copies the argument. `n *= n` changes the copy; the new value is only visible through the return.

### 18. `void stats(const std::vector<int>& data, int& low, int& high, double& mean)` (Exercise 1) uses `int&` / `double&` parameters in order to...

A. return more than one result — the function writes `low`, `high`, and `mean` back through the references, into the caller's own variables
B. avoid copying the large vector
C. make the arguments optional
D. force the caller to pass literals

**Answer: A** — a reference parameter is an alias for the caller's variable, so writing to it updates the original. That is how one call fills three outputs. (The separate `const std::vector<int>&` is the "avoid the copy, don't modify it" use of references.)

### 19. What does the compiler do with `template <typename T> T clamp_to(T v, T lo, T hi)` when you call `clamp_to(120, 0, 100)` and later `clamp_to(-2.5, 0.0, 1.0)`?

A. Runs the template directly, deducing types at run time
B. Instantiates two concrete functions — one with `T = int`, one with `T = double` — and compiles each
C. Rejects the second call — a template can only be used for one type per program
D. Converts the doubles to `int` to match the first instantiation

**Answer: B** — a template is a pattern. Each distinct set of type arguments makes the compiler stamp out and compile a separate function. This is also why a template's body must be visible where it is used — hence templates live in headers, not `.cpp` files.

### 20. Every recursive function needs which two parts?

A. Exactly one parameter and a `static` local
B. A loop and an accumulator
C. A base case that returns without recursing, and a recursive step that moves toward that base case
D. Two recursive calls per step

**Answer: C** — `digit_sum` (Exercise 6): the base case is `n < 10` returning `n`; the step is `(n % 10) + digit_sum(n / 10)`, with `n / 10` closer to the base case each time. Without a reachable base case the calls never stop and the stack overflows.
