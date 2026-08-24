# Chapter 3 & 4 Quiz

15 multiple-choice questions covering everything from **Chapter 3 (First
Steps)** through **Chapter 4 (Variables and Data Types)**. Each question is
followed immediately by its correct answer and a short explanation.

---

### 1. What's the difference between `std::cout << "Hi\n";` and `std::println("Hi");`?

A. There's no difference, they're two spellings of the same function
B. `std::println` is older and `std::cout` is the modern C++23 replacement
C. `std::cout` chains values with `<<` and needs a manual `\n`; `std::println` takes a format string, supports `{}` placeholders, and adds the newline for you
D. `std::cout` can only print numbers, `std::println` can only print text

**Answer: C** — `std::cout` is the traditional stream-chaining style; `std::println` (C++23) takes a format string with `{}` placeholders and appends the newline automatically.

### 2. Which of these is a compile-time error rather than a run-time error?

A. A program dividing an integer by zero while it's running, causing it to crash
B. Calling a misspelled function name that doesn't exist, such as `std::printline(...)` instead of `std::println(...)`
C. A user typing letters when the program asks them to enter their age
D. An `unsigned int` counter being assigned a negative value and wrapping around to a huge positive number

**Answer: B** — a typo'd function name is caught by the compiler before the program ever runs, because the compiler can't find a matching declaration. The others are all mistakes that only surface while the program executes.

### 3. Given `int add_numbers(int first, int second) { return first + second; }`, which statement is true?

A. The function must be called on its own line and can't be used inside another expression
B. `std::println("{}", add_numbers(3, 42));` is valid — a function call can be used directly wherever a value is expected
C. `add_numbers` needs a `return` type of `void` since it doesn't print anything
D. `first` and `second` must be declared as global variables before the function can use them

**Answer: B** — a function call is itself an expression producing a value, so it can be passed directly as an argument, assigned, etc.

### 4. C++23 introduces `std::print`/`std::println` for formatted output. Why does reading user input still rely on `std::cin`/`std::getline` instead of a `<print>`-family function?

A. `std::cin` is faster than any C++23 alternative
B. C++23's `<print>` only covers formatted output — there's no formatted-input equivalent yet, so reading still goes through `std::cin`/`std::getline`
C. `std::getline` is part of the `<print>` header
D. Reading input was removed from the language in C++23

**Answer: B** — `<print>` standardized formatted *output*; input still relies on the existing `<iostream>` facilities.

### 5. What is the purpose of a comment like `// A quantity can never go negative, so unsigned communicates that intent`?

A. It restates what the next line of code does, line by line
B. It's required by the compiler before every variable declaration
C. It explains the *why* behind a choice — a non-obvious reason or intent that the code alone doesn't convey
D. It disables the line of code that follows it

**Answer: C** — good comments explain reasoning or intent, not what the code already says on its face.

### 6. `int octal{017};`, `int hexadecimal{0x0F};`, and `int binary{0b00001111};` all store the same value as `int decimal{15};`. Why?

A. They don't — each literal produces a different value depending on its prefix
B. The prefix (`0`, `0x`, `0b`) only changes how the literal is *spelled* in source code; the compiler stores the same value regardless of which base you wrote it in
C. `octal` and `hexadecimal` store the same value, but `binary` is always different
D. Only decimal literals are stored as numbers — the others are stored as text

**Answer: B** — the base prefix is purely a source-code spelling choice; all four literals evaluate to the integer 15.

### 7. Which format specifier would you use with `std::println` to print an existing `int` value back out in hexadecimal?

A. `{:#x}`
B. `{:#o}`
C. `{:hex}`
D. `std::hex`

**Answer: A** — `{:#x}` formats the value as hexadecimal (with the `0x` prefix); `{:#o}` is octal, and `std::hex` is the `std::cout` stream manipulator, not a `std::println` format spec.

### 8. A store's yearly revenue in cents is a large number: `long long yearly_total_cents{1'284'950'000};`. Why use `long long` here instead of a plain `int`?

A. `long long` is required for any variable name containing the word "total"
B. A regular `int` can't hold a number that large without overflowing; `long long` provides a much bigger range
C. `int` can only store negative numbers
D. The digit separators (`'`) only work with `long long`, not `int`

**Answer: B** — the value exceeds a typical 32-bit `int`'s range, so `long long` is needed to hold it without overflowing.

### 9. What is `sizeof(int)` actually telling you?

A. The largest value an `int` can hold
B. The number of digits an `int` can display
C. How many bytes the type occupies in memory
D. Whether the type is signed or unsigned

**Answer: C** — `sizeof` reports the size in bytes that the type occupies in memory.

### 10. Which type would be the most reasonable *default* choice for storing a monetary amount like `93.33`, per the chapter's guidance?

A. `float`, because it's the smallest floating-point type
B. `double`, the practical default for money and measurements unless there's a specific reason not to
C. `long double`, because more precision is always better
D. `int`, since money is always a whole number of cents

**Answer: B** — `double` is the practical default for money and measurements; `float` trades away precision and `long double` costs more bytes for precision rarely needed.

### 11. What does `unsigned int loyalty_points{350};` communicate, and what's the catch?

A. It communicates that the quantity can never go negative, but it's easy to misuse — assigning a negative value doesn't error, it wraps around to a huge positive number
B. It communicates that the value is temporary and will be deleted after use
C. `unsigned` types are strictly safer than signed types with no downsides
D. `unsigned int` can hold larger negative numbers than a regular `int`

**Answer: A** — `unsigned` signals "never negative," but assigning a negative value silently wraps around instead of raising an error, so it should be used deliberately.

### 12. In `auto amount_spent{93.33};`, what determines the type the compiler gives `amount_spent`?

A. `auto` always deduces `double`, no matter what the initializer is
B. The compiler deduces the type from the initializer — since `93.33` is a `double` literal, `amount_spent` becomes a `double`
C. `auto` postpones type deduction until the variable is printed
D. `auto` makes `amount_spent` compatible with every type, changing type as needed later

**Answer: B** — `auto` deduces the type at compile time from the initializer; the actual type of `93.33` is `double`.

### 13. Given `auto store_id{"store-42"};` and `auto customer_name{"Ada"s};` (with `using namespace std::string_literals;` in scope), what types do `store_id` and `customer_name` deduce to, respectively?

A. Both deduce to `std::string`
B. `store_id` deduces to `const char*` (a C-style string); `customer_name` deduces to `std::string` because of the `s` literal suffix
C. Both deduce to `const char*`
D. `store_id` deduces to `std::string`; `customer_name` deduces to `const char*`

**Answer: B** — a bare string literal deduces to `const char*`; the `s` suffix from `std::string_literals` makes it a `std::string` literal instead.

### 14. `auto loyalty_points{350u};` followed by `loyalty_points = -10;` compiles and runs without crashing. What actually happens?

A. The compiler rejects the assignment because `-10` is negative
B. `loyalty_points` stores `-10` correctly since `auto` adjusts the type automatically
C. `350u` deduces `loyalty_points` as `unsigned int`; assigning `-10` doesn't error, it silently wraps around to a huge positive number — a mistake that's easy to miss without checking what `auto` actually chose
D. The program pauses and asks the user to confirm the negative assignment

**Answer: C** — the `u` suffix deduces `unsigned int`; the deduced type sticks for the variable's lifetime, and `auto` doesn't change it afterward, so the wraparound bug is easy to miss.

### 15. Which of these declarations follows this course's brace-initialization convention?

A. `int age = 28;`
B. `int age;`
C. `int age{28};`
D. `int age(28);`

**Answer: C** — every variable declaration uses brace initialization (`{}`); `=`-style init is reserved only for deliberately demonstrating narrowing/overflow, and bare/uninitialized declarations are never acceptable.
