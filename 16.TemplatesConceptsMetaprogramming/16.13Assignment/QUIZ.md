# Chapter 16 Quiz - Templates, Concepts and Compile-Time Computation

20 multiple-choice questions covering **Chapter 16 (Templates, Concepts and Metaprogramming)**:
function templates, generic lambdas, class templates and deduction, non-type template
parameters, type traits, concepts, specialization and `if constexpr`, variadic templates and
forwarding, `constexpr`, `consteval` and `constinit`, and the generic `Matrix` project. Each
question is followed immediately by its correct answer and a short explanation.

---

### 1. `template <typename To, typename From> To convert_to(From value)`. Why does `convert_to(21.7)` not compile?

A. `From` cannot be a `double`
B. Nothing in the arguments says what `To` is, so it cannot be deduced; the caller must name it, as in `convert_to<int>(21.7)`
C. Templates cannot have two type parameters
D. The function needs `auto` as its return type

**Answer: B** - the compiler deduces a template parameter only from the arguments. `From` appears in the parameter list, `To` does not. Explicit arguments fill the parameters from the left, so `convert_to<int>(21.7)` sets `To = int` and deduces `From = double`.

### 2. A program has `void describe(int)` and `template <typename T> void describe(T)`. What does `describe('x')` call?

A. The ordinary function, because ordinary functions always win
B. Neither: the call is ambiguous
C. The ordinary function, because `char` converts to `int`
D. The template, because it matches `char` exactly while the ordinary function needs a conversion

**Answer: D** - overload resolution picks the best match first. An ordinary function wins only when it fits equally well, as `describe(5)` does. `describe(5.5)` and `describe('x')` go to the template.

### 3. What makes a lambda generic?

A. A parameter declared with `auto`
B. A capture list that contains `[=]`
C. The word `template` in front of it
D. Returning another lambda

**Answer: A** - `[](auto value) { ... }` is a function template without the word `template`: the compiler generates a version of the lambda for each type it is called with. (C++20 also lets you write `[]<typename T>(T a, T b)`.)

### 4. A generic lambda contains `static int calls{0}; return ++calls;`. It is called three times with an `int` and then once with a `double`. What does the call with the `double` return?

A. 4, because there is one `calls`
B. 0
C. 1, because the version for `double` is a separate function with its own `calls`
D. It does not compile

**Answer: C** - each type produces its own version of the lambda, with its own static variable. The third `int` call returned 3 and the first `double` call returned 1.

### 5. `History<Note>` is a class template instantiated with a `Note` that has no `operator<`. Its member function `largest()` uses `<`. When is there an error?

A. When `History<Note>` is declared
B. Only if `largest()` is called for `History<Note>`: only the member functions you use are compiled for a type
C. Never, the compiler skips the comparison
D. When `Note` is defined

**Answer: B** - the class compiled and `add`, `size` and `latest` worked. The error appears, inside `largest()`, only when somebody calls it. Concepts (16.7) can state the requirement up front instead.

### 6. What does the deduction guide `Box(const char*) -> Box<std::string>;` do?

A. For a `Box` built from a string literal, the compiler deduces `Box<std::string>` instead of `Box<const char*>`
B. It converts every `Box` to a string
C. It makes `Box` a non-template class
D. It forbids string literals

**Answer: A** - without the guide, `Box name{"north"}` would be a `Box<const char*>`. A guide tells the compiler which instantiation to deduce from particular constructor arguments.

### 7. How are `Buffer<int, 4>` and `Buffer<int, 8>` related?

A. They are the same type with a different size at run time
B. One converts to the other
C. `Buffer<int, 8>` inherits from `Buffer<int, 4>`
D. They are two different, unrelated types, because the value is part of the type

**Answer: D** - a non-type template argument is part of the type, as with `std::array<int, 4>` and `std::array<int, 8>`. A function that takes a `Buffer<int, 4>` does not accept the other one.

### 8. `add(const Grid<T, Rows, Columns>&, const Grid<T, Rows, Columns>&)` is called with a 2 x 3 grid and a 3 x 2 grid. What happens?

A. A run-time exception is thrown
B. The extra cells are ignored
C. It does not compile: the compiler finds conflicting values for `Rows` and `Columns`
D. It adds the first 2 x 2 cells

**Answer: C** - the same `Rows` and `Columns` appear in both parameters, so the shapes must agree for deduction to succeed. The check costs nothing at run time. This is how the project Matrix rejects a wrong shape.

### 9. What is `std::remove_cvref_t<const int&>`?

A. `const int`
B. `int`
C. `int&`
D. `const int&`

**Answer: B** - it removes the reference and then `const` and `volatile`. It is a type, so we confirmed it with `std::is_same_v<std::remove_cvref_t<const int&>, int>`.

### 10. What does `std::conditional_t<(N <= 255), std::uint8_t, std::uint16_t>` give?

A. `std::uint8_t` when the condition is true and `std::uint16_t` otherwise, decided while compiling
B. A value, either 8 or 16
C. A run-time choice between two types
D. Always `std::uint8_t`

**Answer: A** - it is a type chosen at compile time. Chained twice it picked the smallest unsigned integer that can hold N, and `sizeof` printed 1, 2 and 4 bytes.

### 11. What does a constraint such as `template <std::totally_ordered T>` change for a caller?

A. It makes the function faster
B. It converts the argument to an ordered type
C. It lets the function accept any type
D. A type that does not satisfy it is rejected at the call, with a message that names the unmet requirement

**Answer: D** - without it, the error is reported inside the template body. With it, the compiler reports "no matching function ... constraints not satisfied" at your call, and overloads that do not fit step aside.

### 12. What is a concept, in the way `static_assert(std::forward_iterator<std::list<int>::iterator>);` uses it?

A. A function that runs at run time
B. A kind of class
C. A named requirement on a type, which is a `bool` known at compile time
D. A comment checked by the compiler

**Answer: C** - a concept is evaluated while compiling, like the traits of 16.6. You can use it to constrain a template or ask it directly in a `static_assert`.

### 13. What does the concept `requires(T a, T b) { a + b; }` mean?

A. The expression `a + b` must be valid for objects of type `T`; nothing is executed
B. `T` must be an integer
C. `a + b` must be positive
D. `a` and `b` are added at run time to test `T`

**Answer: A** - a requires expression only checks that the code would compile. The parameters are made-up names used to write the expressions.

### 14. What is `template <> struct Label<double> { ... };`?

A. A template with no parameters
B. A full specialization: a separate definition used for exactly `Label<double>`
C. A partial specialization for all floating point types
D. An error

**Answer: B** - `template <>` means "no parameters left to fill". The `std::formatter<Wind>` of 12.4 and the `std::hash<GridCell>` of 14.7 are specializations of standard templates in the same way, and `std::formatter<Matrix<T, R, C>>` of 16.12 is a partial one.

### 15. What is the difference between `if constexpr` and a plain `if` in a template?

A. `if constexpr` is slower
B. A plain `if` cannot test a type trait
C. With `if constexpr`, the branch that is not chosen is not compiled for that type, so it may contain code that would be invalid for it
D. There is none

**Answer: C** - `describe` could call `value.size()` in one branch and be used with an `int`, because that branch was discarded. A plain `if` would still have to compile it.

### 16. What is `(0 + ... + numbers)`?

A. A syntax error
B. A unary right fold
C. A function call
D. A binary left fold with the start value 0, which also gives an answer for an empty pack

**Answer: D** - it expands to `((0 + n1) + n2) + ...`. The start value makes `sum_all()` return 0 instead of failing to compile.

### 17. A function `template <typename T> void keep(T&& value)` passes `value` on without `std::forward`. What goes wrong when it is called with a temporary?

A. The temporary is copied instead of moved, because inside the function the named parameter is an lvalue
B. It does not compile
C. The temporary is destroyed twice
D. Nothing, it behaves like `std::forward`

**Answer: A** - `T&&` with a deduced `T` is a forwarding reference, but the parameter has a name and so it is an lvalue. `std::forward<T>(value)` gives the argument back as it arrived. In 16.10 the copy count went from 1 to 0 and the move count from 0 to 1.

### 18. What is the difference between `constexpr` and `consteval` on a function?

A. None
B. `consteval` functions are slower
C. A `constexpr` function may run at compile time or at run time, while a `consteval` function must run at compile time: a call with run-time arguments is an error
D. `consteval` applies only to variables

**Answer: C** - `constexpr` is "allowed at compile time". `consteval` is "only at compile time", good for checking a setting early, as `slots_for(24, 4)` did.

### 19. What does `constinit int readings_taken{0};` promise?

A. The variable is constant
B. The variable is initialized at compile time, but it can change later
C. The variable is initialized at run time
D. The variable lives on the stack

**Answer: B** - `constinit` guarantees there is no dynamic initialization to run before `main()`, but unlike `constexpr` the variable is not `const`. In 16.11 it was incremented twice.

### 20. In the generic `Matrix<T, Rows, Columns>`, what happens with `readings * readings` when `readings` is a `Matrix<double, 3, 4>`?

A. It multiplies cell by cell
B. It throws `std::invalid_argument` at run time
C. It transposes one of them automatically
D. It does not compile: the inner sizes (4 and 3) differ, so no `operator*` matches

**Answer: D** - the shape is part of the type, and `operator*` shares `Inner` between its two parameters. In chapter 12 this was a run-time exception that chapter 13 tested; now the compiler catches it, and the tests ask the compiler (`static_assert(!CanMultiply<M23, M23>)`).
