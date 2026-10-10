# Chapter 9 Quiz - Pointers and Arrays

20 multiple-choice questions covering **Chapter 9 (Pointers and Arrays)**: pointers and
addresses, `const` with pointers, pointers versus references, built-in arrays and
decay, pointer arithmetic, C strings, `std::span`, `new` and `delete`, `unique_ptr`,
`shared_ptr` and `weak_ptr`, and what the sanitizers in the Memory Detective project
can and cannot see. Each question is followed immediately by its correct answer and a
short explanation.

---

### 1. After `int x{42}; int* p{&x};`, what does `p` hold?

A. The value 42
B. The address of `x`
C. A copy of `x`
D. The size of `x`

**Answer: B** - a pointer is a variable whose value is an address. `&x` ("address of x") produces it, and `*p` would follow it back to the 42.

### 2. What does `*p = 75;` do when `p` points at `reading`?

A. Stores 75 into `reading`, the object `p` points at
B. Makes `p` point at the address 75
C. Stores 75 into `p` itself
D. It does not compile

**Answer: A** - in an expression, `*` follows the address, so the assignment lands on the original variable. Pointing `p` somewhere else is `p = &other;`, with no star.

### 3. Which statement about a null pointer, `int* p{nullptr};`, is correct?

A. `*p` reads 0
B. `p` is automatically converted to the address of the first variable
C. Comparing it with `nullptr` is fine, dereferencing it is undefined behaviour
D. Every use of it is undefined behaviour

**Answer: C** - `nullptr` means "points at nothing". It exists so that you can test for it (`if (p != nullptr)`), and the test is safe. Only following it with `*p` is undefined.

### 4. In `int* first{&reading}, second{5};`, what are the types of `first` and `second`?

A. Both are `int*`
B. Both are `int`
C. `first` is an `int`, `second` is an `int*`
D. `first` is an `int*`, `second` is an `int`

**Answer: D** - the `*` belongs to the name next to it, not to the type. Declaring one variable per declaration avoids the trap.

### 5. What is the difference between `const int* p` and `int* const p`?

A. There is none, they are two spellings of the same type
B. The first cannot be used to change the int it points at, the second cannot be pointed somewhere else
C. The first cannot be pointed somewhere else, the second cannot change the int
D. The first is for arrays and the second for single values

**Answer: B** - read from the name outwards: `const int* p` is a pointer to a const int (the data is protected), `int* const p` is a const pointer to an int (the pointer is fixed, the data can change).

### 6. Why can `void print_reading(const int* r)` be called with the address of a `const int` as well as of a plain `int`?

A. A pointer to const only promises not to write, which is safe for both kinds of data
B. The compiler removes the `const` for you
C. Pointers ignore `const` in function parameters
D. It cannot: the call with a `const int` does not compile

**Answer: A** - `const int*` is the safest parameter for a function that only reads. A plain `int*` would refuse the address of a const object, because it could be used to modify it.

### 7. When is a pointer parameter a better choice than a reference?

A. Whenever the argument is large
B. Whenever the function modifies its argument
C. When the argument may legitimately be absent, so that `nullptr` can mean "none"
D. Never: references are always better

**Answer: C** - a reference must refer to something, a pointer can say "no object". Use a reference when there is always an object, a pointer when there might not be (or when the function needs to be repointed).

### 8. Why is this function wrong? `const int* broken() { int local{72}; return &local; }`

A. `local` is not const
B. A function cannot return a pointer
C. `&` cannot be used on a local variable
D. `local` is destroyed when the function returns, so the caller gets a pointer to an object that no longer exists

**Answer: D** - that is a dangling pointer. Using it is undefined behaviour, and it will often appear to work for a while, which makes it harder to find.

### 9. `void f(int values[5]) { std::println("{}", sizeof(values)); }` is called with an `int` array of 5. What does it print on a 64-bit machine?

A. 20
B. 8
C. 5
D. 4

**Answer: B** - an array parameter is really a pointer: the array decayed to the address of its first element when it was passed, and its size was left behind. `sizeof` therefore reports the size of a pointer, 8 bytes. In the scope where the array was declared, `sizeof` would give 20.

### 10. If `p` is an `int*` holding address 1000 and `sizeof(int)` is 4, what does `p + 3` hold?

A. 1003
B. 1004
C. 1012
D. 1024

**Answer: C** - adding to a pointer moves it by whole elements, and the compiler multiplies by `sizeof(int)`: 1000 + 3 * 4 = 1012. This is the same arithmetic as `[rdi + rcx*4]` in the assembly lab.

### 11. For `int readings[8]` with `first` pointing at its first element and `last` at `readings + 8`, which statements are true?

A. `last - first` is 8, forming `last` is allowed, dereferencing it is not
B. `last` points at the final element
C. `last - first` is 32, the size in bytes
D. Forming `last` is undefined behaviour

**Answer: A** - the one-past-the-end pointer is allowed to exist so that a loop can test `p != last`. Subtracting two pointers into the same array gives a count of elements, not bytes. Reading through `last` would be out of bounds.

### 12. What is the `sizeof` of the literal `"sensor-12"`?

A. 8
B. 9
C. 11
D. 10

**Answer: D** - there are nine visible characters, and a C string always ends with a terminating `'\0'`, so the array has ten elements. `std::strlen` counts only up to the terminator and gives 9.

### 13. `const char* a{...}` and `const char* b{...}` hold the same text at different places. What does `a == b` test?

A. Whether the letters are equal
B. Whether the two pointers hold the same address
C. Whether the two strings have the same length
D. It does not compile

**Answer: B** - `==` on pointers compares addresses. Use `std::strcmp(a, b) == 0`, or compare two `std::string_view`s, to compare the text.

### 14. What is a `std::span<const int>`?

A. A container that owns a copy of the ints
B. A smart pointer that frees the ints
C. A non-owning view of a run of ints: a pointer and a count, which can be built from a built-in array, a `std::array` or a `std::vector`
D. A fixed-size array type

**Answer: C** - it owns nothing and copies nothing. That is why one function taking `std::span<const int>` can accept all three container kinds. The `const` is a promise not to write, as with `const int*`.

### 15. What can go wrong after `std::span<const int> view{growable}; growable.push_back(75);`?

A. The span may now dangle, if the vector had to move its elements to new storage
B. Nothing: a span always follows its container
C. The span is empty
D. The program does not compile

**Answer: A** - a span is a pointer and a count, so it has the same weakness as a pointer: when the vector reallocates, the old storage is freed and the span still points at it. Do not keep a span while the container changes size.

### 16. How must memory from `int* data{new int[100]};` be released?

A. `delete data;`
B. `free(data);`
C. It is released automatically when `data` goes out of scope
D. `delete[] data;`

**Answer: D** - `new[]` pairs with `delete[]`. A plain `delete` on an array is undefined behaviour. And nothing happens automatically when the pointer goes out of scope: only the pointer variable dies, not the memory it pointed at.

### 17. What does `auto second{first};` do when `first` is a `std::unique_ptr<int>`?

A. It copies the int and both pointers own a copy
B. It does not compile, because a `unique_ptr` cannot be copied, only moved with `std::move`
C. It makes the two pointers share ownership
D. It moves the pointer silently

**Answer: B** - there must be exactly one owner at any time, so copying is forbidden. `auto second{std::move(first)};` transfers ownership explicitly and leaves `first` empty.

### 18. Two objects hold `std::shared_ptr`s to each other and then both go out of scope. What happens?

A. Both are destroyed normally
B. The program crashes
C. Neither is destroyed: each keeps the other's count above zero, which is a leak. Making one of the links a `weak_ptr` fixes it
D. Only the first one is destroyed

**Answer: C** - a `shared_ptr` destroys its object when the count reaches zero, and each node holds the other's count at one. A `weak_ptr` observes without counting, so it breaks the cycle.

### 19. A planted heap-buffer overflow in the Memory Detective prints the right answer and exits with code 0 in a plain build. What does that tell you?

A. The program is correct, the bug is harmless
B. The compiler fixed the bug
C. The overflow was in an unused variable
D. Nothing: undefined behaviour is allowed to look like it works, which is why sanitizers exist

**Answer: D** - an out-of-bounds write has no guaranteed effect. It may corrupt other data, crash later, or do nothing at all this time. A sanitizer checks every access and reports the exact line, whether or not the program happens to survive.

### 20. On Windows with MSVC, which setup reports the leak in the project's `leak` case?

A. `/fsanitize=address`, which reports leaks on exit
B. `/fsanitize=undefined`
C. Nothing can: MSVC cannot detect leaks
D. A Debug build (`/MDd`, `_DEBUG`) with the CRT leak report turned on, which prints each leaked block and the line that allocated it

**Answer: D** - AddressSanitizer on Windows does not include leak detection, and MSVC has no UBSan. The Debug CRT does the job. On Linux, the same flag that enables AddressSanitizer also enables LeakSanitizer, and `valgrind` is another option.
