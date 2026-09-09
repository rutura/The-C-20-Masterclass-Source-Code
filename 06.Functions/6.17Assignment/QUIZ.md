# Chapter 6 Quiz — Functions

20 multiple-choice questions covering **Chapter 6 (Functions)**: program
components, the math library, prototypes and definitions, argument
coercion and evaluation order, standard-library headers, random numbers,
scope rules and static locals, `inline`, reference parameters, default
arguments, the `::` operator, overloading, templates, recursion,
`[[nodiscard]]`, and lambdas. Each question is followed immediately by
its correct answer and a short explanation.

---

### 1. What is the main reason to write your own function rather than repeat the code inline?

A. Functions run faster than the equivalent inline code
B. Reuse — define the work once and call it wherever it is needed, so a change is made in one place
C. The compiler requires all programs to have at least three functions
D. Inline code cannot use variables

**Answer: B** — factoring repeated work into a function means one definition to write, read, and change, instead of copies scattered through the program.

### 2. `std::sqrt(2.0)` and a function you wrote yourself are called...

A. with different syntax — library functions need `call` in front
B. the same way: name, then arguments in parentheses
C. only from `main`
D. library functions cannot take arguments

**Answer: B** — calling a standard-library function is identical to calling your own: `name(arguments)`. The library did the work of writing it.

### 3. Which header provides `std::sqrt`, `std::pow`, `std::ceil`, and `std::fmod`?

A. `<math>`
B. `<cmath>`
C. `<numbers>`
D. `<random>`

**Answer: B** — `<cmath>` is the C++ math-function header. `<numbers>` (C++20) holds math *constants* like `std::numbers::pi`.

### 4. What is a function prototype?

A. The full function including its body
B. The signature (return type, name, parameter types) followed by a semicolon, with no body
C. The first call to the function
D. A comment describing the function

**Answer: B** — a prototype tells the compiler everything a caller needs before the function is defined. Parameter names in it are optional.

### 5. Why put the prototype above `main` and the definition below it?

A. The compiler runs faster that way
B. It keeps `main` at the top where a reader looks first, and it is the only arrangement that works when two functions call each other
C. Definitions are not allowed above `main`
D. It is required by the C++ standard

**Answer: B** — the compiler only needs a prototype before the first call; the definition can come later. This keeps `main` prominent and handles mutual recursion.

### 6. In `double square(double value);`, what does the call `square(4)` do with the `int` argument `4`?

A. Fails to compile — the types don't match
B. Coerces `4` to `4.0` (a safe widening conversion) and squares it
C. Truncates the result to an `int`
D. Calls a different overload

**Answer: B** — argument coercion converts the `int` to the parameter's `double` type. `int`→`double` is a safe widening conversion, done silently.

### 7. Is the return type part of a function's signature?

A. Yes — it is the first thing in the signature
B. No — the signature is the name plus the parameter types; two functions differing only in return type cannot coexist
C. Only for `void` functions
D. Only for template functions

**Answer: B** — `int f(int)` and `double f(int)` have the same signature and are a conflict, not an overload.

### 8. What does the C++ standard say about the order in which a call's arguments are evaluated?

A. Strictly left to right
B. Strictly right to left
C. It is unspecified — the compiler may choose any order, so arguments must not have side effects other arguments observe
D. Alphabetical by parameter name

**Answer: C** — `f(n++, n)` is not portable because which argument reads `n` first is unspecified. Do side-effecting work in its own statement.

### 9. A `std::default_random_engine` that is default-constructed (`engine{}`) produces...

A. a different sequence of numbers every run
B. the same sequence of numbers every run
C. only zeros
D. a compile error — it must be seeded

**Answer: B** — an unseeded engine replays the same sequence each run, which is handy while testing. Seed it to vary the output.

### 10. What are the two cooperating pieces you need to generate a random die roll?

A. Two engines
B. An engine (raw random bits) and a distribution (shapes them into the range 1..6)
C. A distribution and a seed only
D. `rand()` and `srand()`

**Answer: B** — you call the distribution, passing it the engine: `die(engine)`. The engine supplies randomness; the distribution maps it to `{1, 6}`.

### 11. How do you get a *different* random sequence on every run?

A. Call the distribution more times
B. Seed the engine from a nondeterministic source such as `std::random_device` — `std::default_random_engine engine{rd()};`
C. Use a larger distribution range
D. You cannot — engines are always deterministic

**Answer: B** — `std::random_device` provides a nondeterministic value to seed the engine with, giving a fresh sequence each run. A fixed seed instead gives reproducibility.

### 12. What does `enum class Status { keep_rolling, won, lost };` (a scoped enum) give you over a plain `enum`?

A. Faster comparisons
B. The names are scoped (`Status::won`, not a bare `won`) and it does not implicitly convert to `int`, preventing accidental mix-ups
C. It can hold string values
D. Nothing — they are identical

**Answer: B** — a scoped enum keeps its enumerators out of the surrounding scope and refuses silent conversion to integers, so you can't accidentally compare it to a number.

### 13. An ordinary local variable versus a `static` local variable in a function — what is the difference?

A. There is none
B. An ordinary local is recreated fresh on every call; a `static` local is created once (first call) and keeps its value between calls
C. A `static` local is visible outside the function
D. An ordinary local lives for the whole program

**Answer: B** — `static int x{50};` initializes once; subsequent calls see whatever value it last held. An ordinary local starts over each call.

### 14. When a local variable hides a global of the same name, how do you access the global?

A. You cannot — the global is permanently shadowed
B. With the unary scope resolution operator: `::name`
C. By renaming the local
D. With `global::name`

**Answer: B** — `::value` skips local declarations and refers to the global. Inside the local's scope, a bare `value` still means the local.

### 15. What does `inline` on a function actually permit?

A. It forces the compiler to paste the function body at every call site
B. It lets the function's definition appear in multiple translation units (e.g. a header included by many files) without a "multiple definition" linker error
C. It makes the function run at compile time
D. It makes the function private

**Answer: B** — `inline` relaxes the one-definition rule for that function. Whether the body is literally inlined at call sites is the optimizer's decision, keyword or not.

### 16. After `square_by_value(x)` with `int square_by_value(int number) { number *= number; return number; }` and `x` equal to `2`, what is `x`?

A. `4`
B. `2` — `number` is a copy; the caller's `x` is unchanged
C. `0`
D. undefined

**Answer: B** — pass by value copies the argument. `number *= number` changes the copy; the new value is only visible through the return.

### 17. `void square_by_reference(int& ref) { ref *= ref; }` called as `square_by_reference(z)` with `z` equal to `4` leaves `z` as...

A. `4`
B. `16` — `ref` is an alias for `z`, so `z` itself is modified
C. `8`
D. a compile error

**Answer: B** — `int&` makes `ref` refer to the caller's `z`. Modifying `ref` modifies `z` in place.

### 18. Given `int box_volume(int length = 1, int width = 1, int height = 1);`, where must the default values be written, and what does `box_volume(10, 5)` compute?

A. In the definition; `10 * 5` = `50`
B. In the prototype (once); `10 * 5 * 1` = `50` (height defaults)
C. In both prototype and definition; `10 * 5 * 5` = `250`
D. Anywhere; it is a compile error to omit an argument

**Answer: B** — defaults go in the prototype, not repeated in the definition. Arguments fill left to right, so `height` takes its default `1`.

### 19. Every recursive function must have...

A. exactly one parameter
B. a base case that returns without recursing, plus a recursive step that moves toward that base case
C. a loop inside it
D. a `static` local

**Answer: B** — without a reachable base case the calls never stop and the call stack overflows — the recursive form of an infinite loop.

### 20. In a lambda, what is the difference between `[=]` and `[&]` in the capture list?

A. `[=]` captures nothing; `[&]` captures everything
B. `[=]` captures used variables by value (a snapshot); `[&]` captures them by reference (a live link to the originals)
C. `[=]` is for numbers, `[&]` is for strings
D. They are interchangeable

**Answer: B** — with `[=]`, later changes to the outside variable don't affect the lambda's copy. With `[&]`, the lambda reads and writes the actual variable.
