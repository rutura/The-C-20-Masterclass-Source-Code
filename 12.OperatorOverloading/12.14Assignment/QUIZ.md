# Chapter 12 Quiz - Operator Overloading

20 multiple-choice questions covering **Chapter 12 (Operator Overloading)**: operators
as functions, members and free functions, compound assignment, output and
`std::formatter`, comparison and `<=>`, the subscript and call operators,
conversions and `explicit`, user-defined literals, the pipe operator, and the
vcpkg project (classic mode, manifest mode, the toolchain file and baselines). Each
question is followed immediately by its correct answer and a short explanation.

---

### 1. For two `Vec2` values, what does the expression `a + b` actually do?

A. It adds the memory addresses of `a` and `b`
B. It calls a function named `operator+` with `a` and `b`
C. It converts both to `double` and adds those
D. It is an error unless `Vec2` is a built-in type

**Answer: B** - an operator is a function with a funny name. `a + b` and `operator+(a, b)` are the same call, and the compiler turns the first into the second.

### 2. Which of these operators can NOT be overloaded?

A. `::` (scope resolution), `.` and `?:`
B. `+` and `-`
C. `[]` and `()`
D. `<<` and `>>`

**Answer: A** - a few operators are fixed by the language. Most others, including `[]`, `()`, `<<`, `==` and `<=>`, can be overloaded.

### 3. Which operators must be written as MEMBER functions?

A. All binary operators
B. Only `+` and `-`
C. `=` (assignment), `[]`, `()` and `->`
D. Only the comparison operators

**Answer: C** - the language insists on members for those four. Everything else may be a member or a free function, and symmetric binary operators are best as free functions.

### 4. A `Vec2` has a member `operator*(double)`. Why does `2.0 * v` not compile?

A. `double` cannot be multiplied
B. `operator*` must be `const`
C. Vectors cannot be scaled
D. The left operand of a member operator is always the object itself, so a free function `operator*(double, Vec2)` is needed for that order

**Answer: D** - `v * 2.0` calls `v.operator*(2.0)`, but `2.0 * v` would need a member of `double`, which does not exist. Write the second order as a free (or hidden friend) function.

### 5. What is the usual way to write `operator+` for a class that already has `operator+=`?

A. Duplicate the code of `+=`
B. Take the left operand by value, call `+=` on it, and return it
C. Make `+=` call `+`
D. Use a macro

**Answer: B** - `friend Vec2 operator+(Vec2 a, const Vec2& b) { a += b; return a; }`. The by-value parameter is already the copy to modify, so the real work is written once, in `+=`.

### 6. How do the prefix and postfix forms of `++` differ in their declarations?

A. The postfix form takes a dummy `int` parameter, and the prefix form takes none
B. The postfix form returns a reference
C. They are the same function
D. The prefix form takes a dummy `int` parameter

**Answer: A** - `operator++()` is the prefix form, `operator++(int)` the postfix form. Postfix returns the old value, which needs a copy, so it is the costlier of the two.

### 7. Why can `operator<<(std::ostream&, const Vec2&)` not be a member of `Vec2`?

A. `<<` cannot be a member of any class
B. A member must be `const`
C. The left operand is the stream, which is not a `Vec2`, and a member's left operand is always the object itself
D. Streams are not copyable

**Answer: C** - so it is written as a free function (often a friend), and it returns the stream so that `std::cout << a << b` chains.

### 8. What does a `std::formatter<Vec2>` specialization give you?

A. Faster output
B. Support for `std::cout <<`
C. Nothing: it must be written together with `operator<<`
D. Support for `std::format`, `std::print` and `std::println` with `{}`, independent of `operator<<`

**Answer: D** - the two are independent: one does not provide the other. Write the formatter for new code, and `operator<<` as well if the class must work with streams.

### 9. What does `auto operator<=>(const Version&) const = default;` do?

A. Nothing until a body is written
B. Compares the members in declaration order, and the compiler can then provide all six comparison operators (it also writes `==`)
C. Compares only the first member
D. Makes the class abstract

**Answer: B** - for a version with members in the order major, minor, patch, that is exactly the right comparison. Writing it once replaces six operators.

### 10. A class defines its own `<=>` with a hand-written body. Is `operator==` generated automatically?

A. No: `==` is only generated from a DEFAULTED `<=>`, so a hand-written one needs its own `operator==`
B. Yes, always
C. Yes, but only for integer members
D. Only if the class is `final`

**Answer: A** - equality and ordering can have different costs and meanings, so the compiler only writes `==` for you when you ask for the defaulted comparison.

### 11. What is new in C++23 about the subscript operator?

A. It can be `static`
B. It can return `void`
C. It can take more than one argument, so `grid[row, column]` is possible
D. It can no longer be `const`

**Answer: C** - before C++23 it was limited to one argument, which is why multi-dimensional access used `operator()` or nested `[][]`.

### 12. What is a function object (functor)?

A. A function that takes another function as a parameter
B. A function declared `inline`
C. A pointer to a function
D. An object of a class that defines `operator()`, so it can be called like a function and can keep state between calls

**Answer: D** - a lambda is a functor that the compiler writes for you. A class with `operator()` is the same thing written by hand.

### 13. Why make a conversion operator or a one-argument constructor `explicit`?

A. It makes the call faster
B. It stops the compiler from using it for silent, implicit conversions: the conversion happens only when you write it
C. It makes the class abstract
D. It makes the conversion private

**Answer: B** - without it, a bare number could quietly turn into a class object, or a class object into a number, in places you never meant.

### 14. A class has `explicit operator bool() const`. Where is it used automatically?

A. In conditions such as `if (x)`, `while (x)`, `!x`, `&&` and `||`
B. Everywhere a number is expected
C. In every assignment
D. Nowhere: it must always be called with `static_cast`

**Answer: A** - an explicit `operator bool` is the standard way to make an object testable in a condition, the way pointers and smart pointers are, without letting it turn into the number 1 elsewhere.

### 15. Which rule applies to the suffix of a user-defined literal, as in `operator""_km`?

A. It must be uppercase
B. It must be one letter
C. Your own suffixes must start with an underscore: the ones without are reserved for the standard library
D. It cannot take a floating-point value

**Answer: C** - `1.5_km` is allowed, `1.5km` is not available to you. The standard's own literals (`s`, `ms`, `h`, and so on) are the suffixes without an underscore.

### 16. In `text("north") | bold | border` (or the `Panel` pipeline of 12.10), why can `|` be chained?

A. `|` is always associative
B. Chaining needs a macro
C. Each `|` is evaluated in a different thread
D. Each `|` returns the decorated element, which becomes the left operand of the next `|`

**Answer: D** - the operator takes the value on the left, applies the step on the right, and returns the result. That is all a pipeline is. Like all operators, `|` has fixed precedence, lower than `+` and `*`.

### 17. What is the most important rule for overloading an operator?

A. Always make it a member
B. It should do what its symbol suggests, so that a reader is not surprised: if there is no obvious meaning, write a named function instead
C. It should be `inline`
D. It should return `void`

**Answer: B** - a `+` that subtracts, or a `<<` that opens a file, is legal and a disaster for whoever reads the code. You also cannot invent new operators, change precedence, or redefine the ones on built-in types.

### 18. What is the difference between vcpkg's classic mode and manifest mode?

A. Classic mode installs libraries once, for the whole machine, into the vcpkg folder (`vcpkg install fmt`). Manifest mode lists the project's libraries in a `vcpkg.json` next to the code, and installs them per project during the build
B. Manifest mode is only for Linux
C. Classic mode cannot be used with CMake
D. There is no difference

**Answer: A** - classic mode is a shared pool you manage by hand. Manifest mode makes the dependency list part of the project, so anyone who builds it gets the same libraries, with nothing to install first.

### 19. What does passing `-DCMAKE_TOOLCHAIN_FILE=.../vcpkg.cmake` to CMake do?

A. It chooses the C++ compiler
B. It switches CMake to the Visual Studio generator
C. It teaches CMake about vcpkg: where the installed packages are (classic mode), or how to install them first from `vcpkg.json` (manifest mode), so that `find_package` finds them
D. It builds vcpkg itself

**Answer: C** - the toolchain file is vcpkg's integration with CMake. The same line can live in a `CMakePresets.json`, so the command line stays short.

### 20. What does `"builtin-baseline"` in a `vcpkg.json` do?

A. It sets the C++ standard
B. It chooses the compiler
C. It limits the number of dependencies
D. It pins the project to one commit of vcpkg's list of libraries, so every machine gets the same versions, and it is required by vcpkg instances that have no ports tree of their own, such as the copy bundled with Visual Studio

**Answer: D** - without a baseline, versions depend on whatever your vcpkg checkout happens to contain. `vcpkg x-update-baseline --add-initial-baseline` writes the current commit into the manifest.
