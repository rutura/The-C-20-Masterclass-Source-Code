# Functions

Up to now every program has lived inside `main`. That works while a
program is small, but it does not scale: the same few lines get copied
around, `main` grows into a wall of code, and a change has to be made in
five places instead of one.

A **function** is a named, reusable block of code. You **call** it by
name, optionally hand it some **inputs**, it runs, and it optionally
hands back a **result**.

```
   caller                          function
   ──────                          ────────
   int m = maximum(a, b, c);       int maximum(int x, int y, int z) {
        │        └──arguments──┐        └──parameters──┘
        │                      ▼        ...
        │                  x=a, y=b, z=c
        │                      │        return largest;
        └──────result──────────┘◄───────────┘
```

This chapter builds functions up from that idea: how to declare and
define them, the several ways to pass arguments in, how to get results
out, overloading, scope and lifetime, `inline`/`constexpr`, recursion,
function templates, and lambdas.

The running example is a small set of **number tools** - `maximum`,
`box_volume`, a recursive `factorial` - carried through the lectures so
the code is one story rather than disconnected snippets.

---

## 6.2 Why functions

### Anatomy

```
   int maximum(int x, int y, int z) {
   └┬┘ └──┬──┘ └───────┬────────┘  │
    │     │            │           └─ body: the code that runs
    │     │            └───────────── parameter list (inputs)
    │     └────────────────────────── the function's name
    └──────────────────────────────── return type (what comes back)
```

- **Parameter** - a variable in the function's own definition
  (`int x`).
- **Argument** - the actual value you pass at the call
  (`maximum(a, b, c)` - `a`, `b`, `c` are arguments).
- **`return expr;`** - stops the function and sends `expr` back to the
  caller as the function's value.

### `void` vs value-returning

```
   int  lucky_number()  { return 99; }     ← hands back an int
   void print_banner()  { std::println(...); }   ← hands back nothing
```

A `void` function is called for its **effect** (printing, modifying
something), not for a value. It may use a bare `return;` to exit early,
or just run off the end.

### A call is an expression

The call `maximum(a, b, c)` **evaluates to** the return value, so it can
be used anywhere a value of that type is allowed:

```cpp
std::println("{}", maximum(a, b, c));   // as an argument
int biggest{maximum(a, b, c)};          // as an initializer
int t{maximum(a, b, c) * 2};            // inside a bigger expression
```

### Control flow of a call

```
   main runs ─┐
              │  maximum(a,b,c)   ── control jumps INTO maximum
              ▼
          maximum runs its body
              │
              │  return largest;  ── control jumps BACK, carrying the value
              ▼
   main continues with the result
```

---

## 6.3 Declarations and definitions

A function has two forms:

```
   int max_of(int a, int b);          ← DECLARATION (prototype): signature + ';'
                                        no body

   int max_of(int a, int b) {         ← DEFINITION: declaration + { body }
       return a > b ? a : b;
   }
```

**The compiler reads top to bottom** and must have seen a declaration
**before** the first call. Two ways to satisfy that:

```
   Option A: define before use            Option B: declare first, define later
   ───────────────────────────            ────────────────────────────────────
   int max_of(int a,int b){...}           int max_of(int a, int b);   ← prototype
                                          int main() { ... max_of(x,y) ... }
   int main(){ ... max_of(x,y) ... }      int max_of(int a,int b){...} ← definition
```

Option B keeps `main` at the top where a reader looks first, and is the
only option when two functions call each other. Notes:

- The **signature** is the name + parameter types. The return type is
  **not** part of it for overload/matching purposes.
- Parameter **names** in the declaration are optional and need not match
  the definition (`int max_of(int, int);` is a valid prototype).

---

## 6.4 Pass by value

The parameter is a **copy** of the argument. The function has its own
object; changing the parameter does not touch the caller's variable.

```
   main:              try_to_grow:
   ┌───────────┐      ┌───────────┐
   │ my_age 23 │──copy──►│ age 23 │
   └───────────┘      └─────┬─────┘
        ▲                   │ ++age  → age becomes 24 (the COPY)
        │                   ▼
   still 23 after the call  (caller untouched)
```

```cpp
void try_to_grow(int age) { ++age; }   // local copy only

int my_age{23};
try_to_grow(my_age);                   // my_age is still 23
```

Pass by value is the right default for small types (`int`, `double`,
`char`, `bool`). For large objects the copy is wasteful - see 6.6.

---

## 6.5 Pass by reference

`T&` makes the parameter an **alias** for the caller's variable. No copy;
the function works on the original, and changes persist after the call.

```
   main:              square_in_place:
   ┌───────────┐      ┌──────────────────┐
   │ value  4  │◄────►│ n  (alias of value)
   └───────────┘      └────────┬─────────┘
        ▲                      │ n *= n
        └──────────────────────┘ → value is now 16
```

```cpp
void square_in_place(int& n) { n *= n; }

int value{4};
square_in_place(value);        // value becomes 16
```

### Multiple "outputs"

A function returns one value, but reference parameters let it write
several results:

```cpp
void split_seconds(int total, int& minutes, int& seconds) {
    minutes = total / 60;
    seconds = total % 60;
}

int m{}, s{};
split_seconds(200, m, s);      // m == 3, s == 20
```

---

## 6.6 Pass by const reference

`const T&` - a reference the function promises **not to modify**.

Why it exists: for a big object, pass-by-value copies the whole thing on
every call. `const T&` binds straight to the caller's object (no copy),
and `const` stops the function changing it. **This is the default for
read-only parameters that aren't tiny** - `std::string`, containers,
large structs.

```
   pass by value           pass by const ref
   ─────────────           ─────────────────
   "The C++ ..."           "The C++ ..."
        │ copy                  │ (no copy - bind to the original)
        ▼                       ▼
   text (a full copy)      text (a read-only alias)
```

```cpp
std::size_t length_by_value(std::string text);          // copies
std::size_t length_by_const_ref(const std::string& t);  // no copy, read-only
```

`const T&` also accepts temporaries and literals directly
(`length_by_const_ref("hello")`).

| Want to... | Use |
|------------|-----|
| read a small value | `T` (by value) |
| read a large object | `const T&` |
| modify the caller's object | `T&` |
| modify, and "no object" is valid | `T*` (6.7) |

---

## 6.7 Pass by pointer

The parameter is `T*` - the **address** of the caller's variable. Inside,
`*p` reads or writes the pointed-to value; at the call site you pass
`&arg`.

```cpp
void square_in_place(int* n) {
    if (n == nullptr) { return; }   // guard: no object to work on
    *n *= *n;
}

int value{5};
square_in_place(&value);            // value becomes 25
square_in_place(nullptr);           // safe - guard returns early
```

### Pointer vs reference parameter

Both let a function reach the caller's variable. Differences:

```
   reference  int&    always refers to a real object; cannot be null;
                      call looks like a normal call: f(x)

   pointer    int*    can be nullptr (models "optional"); can be
                      repointed; call shows the address: f(&x)
```

Rule of thumb: **reference when the argument is always required**,
**pointer when "nothing" is a legitimate argument**.

---

## 6.8 `std::string_view` parameters

`std::string_view` is a small read-only **window** onto characters that
live elsewhere - internally just a pointer + a length. It owns nothing
and copies nothing.

As a parameter type, one `std::string_view` signature accepts them all
without allocating:

```cpp
void greet(std::string_view name);

greet(owned);         // from a std::string   - no copy
greet("Bob");         // from a string literal - no temporary std::string
greet(sub);           // from a substring
```

Compare the alternatives for a read-only string parameter:

```
   std::string        - copies the caller's text every call
   const std::string& - no copy, but a literal makes a temporary std::string
   std::string_view   - no copy, no temporary; accepts all three sources
```

**Caveat:** a `string_view` does not keep its text alive. Fine for a
parameter (the argument outlives the call); do **not** store one that
outlives the string it points into.

---

## 6.9 Default arguments

A parameter can carry a default. Omit that argument at the call and the
default is used.

```cpp
int box_volume(int length = 1, int width = 1, int height = 1);
```

```
   box_volume()          → 1 * 1 * 1  = 1
   box_volume(10)        → 10 * 1 * 1 = 10
   box_volume(10, 5)     → 10 * 5 * 1 = 50
   box_volume(10, 5, 2)  → 10 * 5 * 2 = 100
```

Rules:

- Defaults live in the **declaration** (the prototype), not the
  definition - and are written once, not in both places.
- Only **trailing** parameters may have defaults, so arguments fill
  **left to right**. `box_volume(10, , 2)` is not allowed.
- Order parameters so the ones most often left default come **last**.

---

## 6.10 Return values

`return expr;` sends a **copy** of `expr` back to the caller (return by
value). This is the normal, safe mechanism.

### `[[nodiscard]]`

Mark a function `[[nodiscard]]` when discarding its result is almost
certainly a mistake. The compiler then warns if a caller ignores it.

```cpp
[[nodiscard]] int add(int a, int b) { return a + b; }

int s{add(3, 4)};   // fine
add(3, 4);          // warning: result of a [[nodiscard]] call is unused
```

### Never return a reference or pointer to a local

```cpp
int& broken() {
    int local{42};
    return local;     // local is destroyed here → the reference dangles
}
```

The local's lifetime ends when the function returns. Return **by value**
instead - copying the value out is safe.

---

## 6.11 Overloading

Several functions may share a name if their **parameter lists differ**
(in count or types). The compiler picks the best match per call.

```cpp
int    square(int x)    { return x * x; }
double square(double x) { return x * x; }

int    area(int side)              { return side * side; }
int    area(int width, int height) { return width * height; }
```

```
   square(7)     → parameter is int      → int version
   square(7.5)   → parameter is double   → double version
   square(7.0f)  → float promotes to double → double version

   area(5)       → one argument   → area(int)
   area(4, 6)    → two arguments  → area(int, int)
```

- The **return type alone cannot distinguish overloads** -
  `int f(int);` and `double f(int);` together is an error.
- If no overload matches exactly, the compiler applies conversions to
  find the best one; an ambiguous tie is a compile error.

---

## 6.12 Scope and lifetime

**Scope** = where a name is visible. **Lifetime** = how long the object
exists.

| Kind | Scope | Lifetime |
|------|-------|----------|
| local variable | its enclosing `{ }` | until that block ends |
| block variable | the inner `{ }` | until that inner block ends |
| global variable | from its declaration to end of file | whole program |
| `static` local | its function | whole program (created once) |

```cpp
int counter{0};                 // global

void show() {
    int counter{100};           // local - hides the global in here
    std::println("{}", counter);   // 100
    std::println("{}", ::counter); // global, via ::
}
```

### `static` local

An ordinary local is **recreated every call**. A `static` local is
created **once**, on the first call, and keeps its value between calls:

```cpp
void next_id() {
    static int id{0};   // initialised once
    ++id;
    std::println("{}", id);
}

next_id();  // 1
next_id();  // 2
next_id();  // 3
```

```
   ordinary local:   call1 [0→1]   call2 [0→1]   call3 [0→1]
   static local:     call1 [0→1]   call2 [1→2]   call3 [2→3]
                                 (value carried across calls)
```

---

## 6.13 `inline` and `constexpr`

Two keywords that get confused. Neither is about "make it fast" directly.

### `constexpr` function

**Can run at compile time** when its arguments are known then. Use it for
small pure calculations you might need as a constant, an array size, or a
template argument.

```cpp
constexpr int cube(int side) { return side * side * side; }

constexpr int room{cube(3)};   // computed by the compiler → 27
int grid[cube(2)]{};           // array size from a constexpr call → 8

int side{4};
cube(side);                    // side is a run-time value → runs at run time
```

A `constexpr` function still works at run time; `constexpr` just makes
compile-time use *possible*.

### `inline` function

The ODR ("one definition rule") relaxation that lets a function be
**defined in a header** included by many translation units without a
"multiple definition" linker error. It is **not** an instruction to
paste the body at the call site - the optimizer decides that on its own,
`inline` or not.

```
   constexpr  → "may be evaluated at compile time"
   inline     → "this definition may appear in several files; treat them as one"
```

---

## 6.14 Recursion

A **recursive** function calls itself. Every one needs:

- a **base case** that returns without recursing (ends the chain), and
- a **recursive step** that calls itself with an argument closer to the
  base case.

```cpp
long factorial(int n) {
    if (n <= 1) { return 1; }          // base case
    return n * factorial(n - 1);       // recursive step
}
```

```
   factorial(4)
   = 4 * factorial(3)
       = 3 * factorial(2)
           = 2 * factorial(1)
               = 1                 ← base case, unwinding starts
           = 2 * 1  = 2
       = 3 * 2  = 6
   = 4 * 6  = 24
```

Miss the base case (or fail to move toward it) and the calls never stop -
a **stack overflow** crash, the recursive cousin of an infinite loop.

### Recursion vs iteration

The same `factorial` as a loop:

```cpp
long factorial_iterative(int n) {
    long result{1};
    for (int i{2}; i <= n; ++i) { result *= i; }
    return result;
}
```

Iteration is usually faster and uses no call-stack depth. Reach for
recursion when it makes the problem **clearer** - trees, nested
structures, divide-and-conquer - not as a default.

---

## 6.15 Function templates

A **function template** is a pattern with a type left blank. `T` is a
placeholder the compiler fills in from the call's arguments, generating a
concrete function on demand. One template → a whole family of functions.

```cpp
template <typename T>
T maximum(T a, T b, T c) {
    T largest{a};
    if (b > largest) { largest = b; }
    if (c > largest) { largest = c; }
    return largest;
}
```

```
   maximum(3, 9, 5)          T deduced as int      → generates maximum<int>
   maximum(2.5, 1.1, 3.8)    T deduced as double   → generates maximum<double>
   maximum('q', 'a', 'm')    T deduced as char     → generates maximum<char>
   maximum(s1, s2, s3)       T deduced as string   → generates maximum<string>
```

- The compiler **deduces `T`** from the arguments. All three must agree
  on the type (mixing `maximum(3, 9.0, 5)` fails to deduce a single
  `T`).
- You can state it explicitly: `maximum<double>(3, 9, 5)` forces the
  ints to be treated as `double`.
- The body must be valid for whatever `T` ends up being - `maximum`
  needs `>` to work on `T`, which it does for the numeric types and
  `std::string`.

---

## 6.16 Lambda functions

A **lambda** is a function written **inline**, right where it is used -
usually to hand to another function. Shape:

```
   [ capture ] ( parameters ) { body }
   └───┬────┘
   which surrounding variables the lambda can see
```

```cpp
auto add = [](int a, int b) { return a + b; };
add(3, 4);   // 7 - stored in a variable, called like any function
```

### Captures

```cpp
int offset{10};

auto by_value = [=](int n) { return n + offset; };   // copies offset (10)
offset = 999;                                        // by_value still uses 10

int total{0};
auto by_ref = [&](int n) { total += n; };            // refers to the real total
by_ref(3); by_ref(4);                                // total is now 7
```

```
   [=]   capture everything used, BY VALUE   (a snapshot)
   [&]   capture everything used, BY REFERENCE (live link to the original)
   [x]   capture just x by value
   [&x]  capture just x by reference
   []    capture nothing
```

### Passing a lambda where a callable is expected

```cpp
std::sort(nums.begin(), nums.end(),
          [](int a, int b) { return a > b; });   // custom "which comes first?"
```

Standard-library algorithms take a callable to decide comparisons,
filtering, and so on - a lambda written at the call site is the usual way
to supply it.

---

## 6.17 Assignment

`main.cpp` has six stubbed exercises, each with its problem statement and
a sample run in a comment; `main_solution.cpp` solves all six with the
statements repeated above each solution. Built as two executables
(`rooster`, `rooster_solution`).

| # | Exercise | Tools exercised |
|---|----------|-----------------|
| 1 | `is_even` + count evens 1..20 | writing a `bool` function, calling it in a loop |
| 2 | `swap_values(int&, int&)` | pass by reference |
| 3 | `describe(sv, width=40, fill='-')` | default arguments + `std::string_view` |
| 4 | `area` overloads, both `[[nodiscard]]` | overloading + return-value attribute |
| 5 | `sum_to(n)` recursively | base case + recursive step |
| 6 | `smallest<T>(a,b,c)` + a `times` lambda | function template + lambda |

After this chapter the student can factor code into functions, choose how
to pass and return data, and is ready for classes.
