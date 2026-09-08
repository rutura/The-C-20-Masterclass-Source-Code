# Chapter 6 Quiz — Functions

20 multiple-choice questions covering **Chapter 6 (Functions)**:
declarations vs definitions, pass by value / reference / const reference
/ pointer, `std::string_view` parameters, default arguments,
`[[nodiscard]]` return values, overloading, scope and lifetime,
`inline` / `constexpr`, recursion, function templates, and lambdas. Each
question is followed immediately by its correct answer and a short
explanation.

---

### 1. In `int maximum(int x, int y, int z)`, what are `x`, `y`, and `z` called, and what are the values passed at a call like `maximum(a, b, c)` called?

A. `x`, `y`, `z` are arguments; `a`, `b`, `c` are parameters
B. `x`, `y`, `z` are parameters; `a`, `b`, `c` are arguments
C. Both are called parameters
D. Both are called arguments

**Answer: B** — the names in the function's own definition are *parameters*; the values supplied at the call site are *arguments*.

### 2. What is true of a `void` function?

A. It cannot contain a `return` statement
B. It is called for its effect, not for a value; it may use a bare `return;` to exit early
C. It always returns `0`
D. It can only be called from `main`

**Answer: B** — a `void` function hands back nothing. It runs for side effects (printing, modifying), and `return;` with no value exits it early.

### 3. Why can `std::println("{}", maximum(a, b, c));` pass a function call directly as an argument?

A. `std::println` has a special overload for function calls
B. A function call is an expression that evaluates to the function's return value, so it can appear anywhere a value of that type is allowed
C. Only `maximum` can be used this way
D. It cannot — this line is a compile error

**Answer: B** — the call `maximum(a, b, c)` *is* an `int`-valued expression; it can be an argument, an initializer, or part of a larger expression.

### 4. A function's declaration (prototype) consists of...

A. the full function including its `{ body }`
B. its signature followed by a semicolon, with no body
C. just the function's name
D. the `return` statement only

**Answer: B** — a prototype is the return type, name, and parameter types (names optional), ending in `;`. The compiler needs it before the first call; the body can come later.

### 5. Do parameter names in a function's declaration have to match the names in its definition?

A. Yes, exactly, or it is a compile error
B. No — declaration parameter names are optional and need not match the definition
C. Only the first parameter name must match
D. They must match only for `void` functions

**Answer: B** — `int max_of(int, int);` is a valid prototype. The names in the definition are what the body actually uses.

### 6. After this code runs, what is `my_age`?

```cpp
void try_to_grow(int age) { ++age; }
int my_age{23};
try_to_grow(my_age);
```

A. `24`
B. `23`
C. `0`
D. undefined

**Answer: B** — `age` is a *copy* of `my_age` (pass by value). `++age` changes only the copy; `my_age` is still `23`.

### 7. What does `void square_in_place(int& n) { n *= n; }` do to the caller's variable when called as `square_in_place(value)` with `value` equal to `4`?

A. Nothing — `n` is a copy
B. `value` becomes `16`, because `n` is an alias for `value`
C. It is a compile error to pass `value` without `&`
D. `value` becomes `8`

**Answer: B** — `int&` makes `n` refer to the caller's `value` itself, so `n *= n` sets `value` to `16`.

### 8. Why prefer `const std::string&` over `std::string` for a read-only string parameter?

A. `const std::string&` is easier to type
B. It binds directly to the caller's object (no copy) while `const` prevents the function from modifying it
C. `std::string` parameters cannot be read
D. There is no difference

**Answer: B** — passing a `std::string` by value copies the whole string on every call; `const std::string&` avoids the copy and still guarantees the function won't change it.

### 9. Which parameter form should you choose when the function must modify the caller's object **and** "no object" is a legitimate case?

A. `T` (by value)
B. `const T&`
C. `T&`
D. `T*` (by pointer), checking for `nullptr`

**Answer: D** — a reference cannot be null, so it can't express "optional." A pointer parameter can be `nullptr`, and the function guards against it.

### 10. A single `std::string_view` parameter can accept a `std::string`, a string literal, and a substring without allocating. Why?

A. `string_view` copies each into a `std::string` internally
B. `string_view` is a small non-owning window (pointer + length) onto characters that live elsewhere, so no copy or temporary is needed
C. The compiler rewrites the calls to use `const char*`
D. It only works for string literals

**Answer: B** — `std::string_view` owns nothing; it just points at existing characters and remembers how many. That is why one signature covers all three sources cheaply.

### 11. What is the danger of storing a `std::string_view` that outlives the string it was created from?

A. None — `string_view` keeps its text alive
B. The `string_view` points at characters that have been destroyed — a dangling view
C. It silently copies the text to stay valid
D. The program won't compile

**Answer: B** — a `string_view` does not extend the lifetime of its underlying text. It is safe as a parameter (the argument outlives the call) but not as long-lived storage.

### 12. Given `int box_volume(int length = 1, int width = 1, int height = 1);`, what does `box_volume(10, 5)` compute?

A. `10 * 5` = `50` (height defaults to `1`)
B. `10 * 1 * 1` = `10`
C. a compile error — you must pass all three
D. `10 * 5 * 5` = `250`

**Answer: A** — arguments fill left to right, so `length` is `10`, `width` is `5`, and the omitted `height` uses its default `1`.

### 13. Where do default argument values belong?

A. In both the declaration and the definition
B. In the definition only
C. In the declaration (prototype) only, written once
D. Anywhere, as long as they appear at least twice

**Answer: C** — defaults go in the declaration and are not repeated in the definition. Only trailing parameters may have them.

### 14. What does marking a function `[[nodiscard]]` do?

A. It forces the function to return `void`
B. It makes the compiler warn if a caller ignores the return value
C. It prevents the function from being overloaded
D. It runs the function at compile time

**Answer: B** — `[[nodiscard]]` signals that dropping the result is probably a bug, so the compiler flags calls whose return value is unused.

### 15. Why is `int& broken() { int local{42}; return local; }` wrong?

A. `local` is `const` and cannot be returned
B. `local` is destroyed when the function returns, so the returned reference dangles
C. `int&` is not a valid return type
D. It should be `return &local;`

**Answer: B** — the local's lifetime ends at the `return`. The caller gets a reference to memory that is no longer valid. Return by value instead.

### 16. Which pair of functions is a **valid** overload set?

A. `int f(int);` and `double f(int);`
B. `int f(int);` and `int f(double);`
C. `int f(int, int);` and `int f(int, int);`
D. `void f();` and `int f();`

**Answer: B** — overloads must differ in the number or types of parameters. A and D differ only in return type (not allowed); C is a redefinition.

### 17. What does a `static` local variable do that an ordinary local does not?

A. It is visible outside its function
B. It is created once, on the first call, and keeps its value between calls
C. It is stored on the call stack
D. It cannot be modified after initialization

**Answer: B** — an ordinary local is recreated fresh each call; a `static` local persists for the whole program and retains whatever value it last held.

### 18. Which statement about `constexpr` and `inline` is correct?

A. `constexpr` means "paste the body at the call site"
B. `inline` guarantees the function runs at compile time
C. `constexpr` allows a function to be evaluated at compile time when its arguments are known then; `inline` lets a function be defined in a header included by many files without a linker error
D. They are two spellings of the same keyword

**Answer: C** — `constexpr` enables compile-time evaluation (and still works at run time); `inline` is about the one-definition rule, not about literally inlining code.

### 19. Every recursive function must have...

A. exactly one parameter
B. a base case that returns without recursing, and a recursive step that moves toward that base case
C. a loop inside it
D. a `static` local variable

**Answer: B** — without a reachable base case the calls never stop, causing a stack overflow (the recursive equivalent of an infinite loop).

### 20. Given `template <typename T> T maximum(T a, T b, T c);`, what does the call `maximum(3, 9.0, 5)` do?

A. Deduces `T` as `double` and runs fine
B. Deduces `T` as `int` and truncates `9.0`
C. Fails to compile — the arguments are `int`, `double`, `int`, so the compiler cannot deduce a single `T`
D. Calls a non-template overload

**Answer: C** — template argument deduction needs all three arguments to agree on `T`. Mixing `int` and `double` is ambiguous; you would write `maximum<double>(3, 9.0, 5)` to force it.
