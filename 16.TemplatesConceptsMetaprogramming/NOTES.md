# Templates, Concepts and Metaprogramming

Every chapter since 7 has used templates without saying so. `std::vector<int>`, `std::map<std::string, double>`, `std::optional<T>`, `std::expected<T, E>`, `std::array<int, 6>`, `std::ranges::sort`, the views of chapter 15: all of them are templates, and the angle brackets are the sign. You wrote your first one in 6.13, `in_range<T>`. This chapter finishes the story: how to write templates of your own, how to say what a template needs from its types, and how to make the compiler do work that would otherwise happen when the program runs.

```
   one definition, with a blank              the compiler fills the blank, once per type you use
   ─────────────────────────────             ───────────────────────────────────────────────────────
   template <typename T>                     History<double>    History<std::string>    History<int>
   class History { ... T ... };              three classes, written for you
```

Along the way the chapter keeps a series of promises made in earlier chapters:

- **12.4** gave you a `std::formatter` to paste in and said "what it means is chapter 16". 16.9 explains it.
- **14.2** asserted `std::forward_iterator<...>`; **13.5** and **13.9** asserted `std::is_nothrow_move_constructible_v` and `std::is_trivially_copyable_v`. 16.6 and 16.7 explain what those are.
- **14.7** specialized `std::hash`; **14.10** wrote a class with a `std::size_t Capacity` parameter. 16.9 and 16.5 explain both.
- **Chapter 15** passed lambdas around and kept `auto` parameters out of its code on purpose. 16.3 teaches them.

The order of the chapter follows what each lecture needs from the one before:

1. **Writing templates** (16.2 to 16.5): functions, generic lambdas, classes, and templates with a *value* as a parameter.
2. **Asking questions about types** (16.6 to 16.8): type traits, then concepts, which are those questions given a name and put in a template's declaration.
3. **Choosing at compile time** (16.9, 16.10): specialization, `if constexpr`, any number of parameters, and passing arguments on unchanged.
4. **Computing at compile time** (16.11), and a **project** (16.12) that brings all of it together: the `Matrix` of chapter 12, rebuilt as `Matrix<T, Rows, Columns>`, where a wrong shape is a compile error and the tests ask the compiler.

All the programs of this chapter were built and run on MSVC, GCC 16 and Clang 21, and **print byte-identical output on all three**.

---

## 16.2 Function templates, further

In this lecture we take the function template of 6.13 further: more than one type, a result type the compiler works out, a parameter the caller must name, a default, and how a template competes with an ordinary function.

### The reminder

```cpp
template <typename T>
bool in_range(T value, T low, T high) { ... }
```

`T` is deduced from the arguments, a version is **instantiated** per type, and the body must be visible wherever the template is used, so it lives in a header (6.13). Everything below works the same way.

### More than one type parameter

```cpp
template <typename T, typename U>
auto sum_of(T first, U second) {
    return first + second;
}
```

`T` and `U` are independent, so the two arguments may have different types. The result is written as **`auto`**: for a function, `auto` in the result position means "work it out from the `return` statement". Here the type of `first + second`:

```cpp
sum_of(2, 3)                       // 5      an int plus an int
sum_of(2, 3.5)                     // 5.5    an int plus a double is a double
sum_of(std::string{"north"}, "!")  // north! a string plus a const char*
```

```
sum_of(2, 3)        = 5
sum_of(2, 3.5)      = 5.5
sum_of(string, "!") = north!
```

(If a function has several `return` statements, they must all give the same type.)

### A parameter the compiler cannot deduce

```cpp
template <typename To, typename From>
To convert_to(From value) {
    return static_cast<To>(value);
}
```

`From` appears in the parameter list, so it is deduced. `To` does not: nothing in the arguments says what you want the result to be. So the caller **names it**:

```cpp
convert_to<int>(21.7)         // To = int (named), From = double (deduced)
convert_to<double>(21)        // To = double, From = int
// convert_to(21.7);          // error: nothing says what To is
```

```
convert_to<int>(21.7)    = 21
convert_to<double>(21)   = 21
```

Explicit arguments fill the parameters **from the left**; the rest are deduced. That is why `To` is declared first.

### A default for a template parameter

```cpp
template <typename Result = double, typename T>
Result mean_of(const std::vector<T>& values) {
    Result total{};
    for (const T& value : values) {
        total += value;
    }
    return total / static_cast<Result>(values.size());
}
```

`T` is deduced from the vector, as in the `show` helper of chapter 15. `Result` has a **default**, `double`, used when the caller says nothing:

```cpp
std::vector<int> counts{1, 2, 4};
mean_of(counts)            // 2.3333333333333335   Result = double, by default
mean_of<int>(counts)       // 2                    Result named: integer division
mean_of<float>(counts)     // 2.3333333
```

Averaging whole numbers in `double` is the sensible default, and a caller who wants something else can ask.

### A template and an ordinary function with the same name

```cpp
void describe(int value);                                   // an ordinary function

template <typename T>
void describe(T value);                                     // a template
```

```
describe(5);        the ordinary function for int: 5
describe(5.5);      the template: 5.5
describe('x');      the template: x
describe<int>(7);   the template: 7
```

The compiler picks the **best match** first. For `5` the two fit equally well, and the ordinary function wins a tie. For `5.5` only the template fits without a conversion. For `'x'` the template matches `char` exactly, while the function would have to convert `char` to `int`, so the **template wins**. And `describe<int>(7)` asks for the template by name. When you mix the two, check which one a call reaches.

### What the body needs

```cpp
template <typename T>
T larger_of(T a, T b) {
    return a < b ? b : a;
}
```

Works for `int`, `double`, `std::string`, and a `Reading` for which we wrote `operator<` (12.5). For a type without `<` the compiler reports the error **inside the body**, at `a < b`: the template never said what it needs. 16.7 shows how it can.

**Code for this lecture**: `16.2FunctionTemplates/main.cpp`.

---

## 16.3 Generic lambdas

In this lecture we meet the `auto` parameter, in lambdas and in ordinary functions.

### A lambda that accepts any type

A lambda from 6.14 has parameters of fixed types: `[](int a, int b)` works for `int` and nothing else. Declare a parameter with `auto` and it works for **any** type:

```cpp
auto show{[](auto value) { std::println("value: {}", value); }};
show(5);                               // makes the version for int
show(2.5);                             // makes the version for double
show(std::string{"north"});            // and the version for std::string
```

```
value: 5
value: 2.5
value: north
```

A **generic lambda** is a function template written without the word `template`. Its call operator (12.6) is a template, and the compiler generates a version for each type it is called with.

### The same for functions

C++20 lets an ordinary function do the same. `auto` in a function's parameter list is shorthand for a template:

```cpp
void print_pair(auto first, auto second) {
    std::println("({}, {})", first, second);
}

// is the same as
template <typename T, typename U>
void print_pair_longhand(T first, U second) { ... }
```

Each `auto` is a **new** template parameter, so the two arguments may have different types. `print_pair(21, 24.5)` prints `(21, 24.5)`. And with `auto` as the result as well (16.2), a whole function fits on three lines:

```cpp
auto sum_of(auto first, auto second) {
    return first + second;
}
```

### One lambda, two element types

```cpp
auto above_ten{[](auto value) { return value > 10; }};
std::ranges::count_if(counts, above_ten);          // a vector<int>
std::ranges::count_if(temperatures, above_ten);    // a vector<double>
```

```
counts above 10: 2   temperatures above 10: 3
```

Captures (6.14) work as before: `[limit](auto value) { return value > limit; }`.

### By value or by reference

`auto` takes the argument **by value**. A `std::string` would be copied on every call. Write `const auto&` when the type may be big, as you would for any parameter:

```cpp
auto long_name{[](const auto& name) { return name.size() > 4; }};
```

This is the form you will see in code written for the algorithms of chapter 15.

### One version per type

Each type gets its own version of the lambda, and so its **own** `static` local variable (6.7):

```cpp
auto count_calls{[](auto) {
    static int calls{0};
    return ++calls;
}};
count_calls(1);  count_calls(2);
int third{count_calls(3)};          // the third call with an int
int first_double{count_calls(1.5)}; // the first call with a double
```

```
third call with an int: calls = 3
first call with a double: calls = 1
```

Three calls with `int` counted 1, 2, 3; the call with a `double` started at 1: a different function, with a different `calls`.

### When the parameters must match

With two `auto` parameters, the types are independent. When two parameters must be the **same** type, give the lambda an explicit template parameter list (C++20), like a function template:

```cpp
auto larger_of{[]<typename T>(T a, T b) { return a < b ? b : a; }};
larger_of(3, 8)            // 8
// larger_of(3, 8.5);      // error: T would have to be both int and double
```

while `[](auto a, auto b) { return a < b ? b : a; }` accepts `larger_mixed(3, 8.5)` (the result is converted to a common type: 8.5).

### The pattern to remember

> **Fixed types for a lambda that serves one purpose; `auto` for one that should work for many. `const auto&` when the type may be big.**

**Code for this lecture**: `16.3GenericLambdas/main.cpp`.

---

## 16.4 Class templates

In this lecture we write a template for a **class**: the same idea as a function template, and the way every container you have used was made.

### The problem

A history of the values a station has measured: temperatures (doubles), alarm counts (ints), station names (strings). Writing `HistoryOfDoubles`, `HistoryOfInts` and `HistoryOfStrings` is writing the same class three times.

### The template

```cpp
template <typename T>
class History {
public:
    History() = default;
    History(std::initializer_list<T> start) : items_{start} {}

    void add(const T& value) { items_.push_back(value); }
    std::size_t size() const { return items_.size(); }
    const T& latest() const { return items_.back(); }

    const T& largest() const;                        // defined below

    double mean() const {
        double total{0.0};
        for (const T& item : items_) {
            total += item;
        }
        return total / static_cast<double>(items_.size());
    }

private:
    std::vector<T> items_;
};
```

`T` is used throughout, and the class is used by naming the type: `History<double>`, `History<std::string>`. Each one is a **different class**, generated from the same template, and `History<int>` cannot be assigned from a `History<double>`.

A member function can be defined outside the class. It then needs the template header again, and the class name carries its parameter:

```cpp
template <typename T>
const T& History<T>::largest() const {
    const T* best{&items_.front()};
    for (const T& item : items_) {
        if (*best < item) {
            best = &item;
        }
    }
    return *best;
}
```

Like a function template, the whole class template goes in a **header** (6.13).

### Only what you call is compiled

```cpp
History<double> temperatures;
temperatures.add(18.5);  temperatures.add(24.0);  temperatures.add(21.5);

History<std::string> stations;
stations.add("north");  stations.add("south");

History<Note> notes;                       // a Note has no operator< and no number inside
notes.add(Note{"check the battery"});
```

```
temperatures: 3 values, latest 21.5, largest 24, mean 21.33
stations: 2 names, latest south, largest south
notes: 1 note, latest 'check the battery'
```

Look at what compiled. `mean()` cannot work for a `std::string` (`total += item` does not give a number), and `largest()` cannot work for a `Note` (no `<`), yet `History<std::string>` and `History<Note>` are fine. **A member function of a class template is compiled for a type only if somebody calls it.** The error, if you do call `notes.largest()`, appears inside `largest()`, at `*best < item`. 16.7 shows how to state such requirements up front.

### The compiler deduces `T`

In 7.2 you wrote `std::array arr{1, 2, 3}` and the compiler worked out `<int, 3>`. That is **class template argument deduction** (CTAD), and it works for your own classes too, when a constructor gives it something to deduce from. `std::initializer_list<T>` is the type of a braced list of values such as `{4, 12, 7}`; it is how `std::vector v{1, 2, 3}` receives its elements. A constructor that takes one lets you write:

```cpp
History counts{4, 12, 7};              // History<int>
History readings{18.5, 24.0};          // History<double>
```

```
counts has 3 values, readings has 2
largest count: 30
```

### A deduction guide

```cpp
template <typename T>
class Box {
public:
    Box(T value) : value_{std::move(value)} {}
    const T& get() const { return value_; }
private:
    T value_;
};

Box(const char*) -> Box<std::string>;          // the deduction guide
```

```cpp
Box number{21.5};            // Box<double>: deduced from the value
Box name{"north"};           // Box<std::string>, thanks to the guide
```

```
number: 21.5   name: north (5 letters)
```

When the compiler deduces `T` from a string literal it picks `const char*`, which is rarely what you want. A **deduction guide** says: *for this kind of argument, use this instantiation*. Without it, `name` would be a `Box<const char*>` and `name.get().size()` would not compile.

### The pattern to remember

> **A class template is a recipe for classes. Only the members you use are compiled. The compiler deduces the parameters when the constructor lets it; a deduction guide helps when it guesses wrong.**

**Code for this lecture**: `16.4ClassTemplates/main.cpp`.

---

## 16.5 A value as a template parameter

In this lecture we meet the second kind of template parameter: a **value**.

### You have used one already

`std::array<int, 6>` has two parameters: the type `int` and the **number** 6, and the 6 is part of the type (7.2). `std::array<int, 6>` and `std::array<int, 10>` are different types. 14.10's `RecentReadings<std::size_t Capacity>` was the same. Here is how to write one:

```cpp
template <typename T, std::size_t N>
class Buffer {
public:
    static_assert(N > 0, "a Buffer must have room for at least one value");

    bool push(const T& value) {
        if (size_ == N) {
            return false;                          // full: refuse
        }
        items_[size_] = value;
        ++size_;
        return true;
    }

    std::size_t size() const { return size_; }
    constexpr std::size_t capacity() const { return N; }

private:
    std::array<T, N> items_{};
    std::size_t size_{0};
};
```

`N` is an ordinary constant inside the class. The `static_assert` (13.9) checks a mistake in the template arguments when the class is made. The room lives **inside the object**, in a `std::array`: no heap allocation.

```cpp
Buffer<int, 4> counts;
for (int value : {10, 20, 30, 40, 50}) {
    std::println("push({}): {}", value, counts.push(value) ? "stored" : "refused, the buffer is full");
}
```

```
push(10): stored
push(20): stored
push(30): stored
push(40): stored
push(50): refused, the buffer is full
a Buffer<int, 4> holding 4 of 4
Buffer<double, 128> has capacity 128 and holds 0
```

`Buffer<double, 128>` is a different type, with room for 128. A function `report(const Buffer<int, 4>&)` accepts only the first kind.

### The value is part of the type

```
sizeof(Buffer<char, 4>)   = 16
sizeof(Buffer<char, 100>) = 112
```

The size of the object grows with `N`, because the room is inside it (the rest is the `size_` member and padding). A value known to the compiler can be used where only constants are allowed, such as a `static_assert`: `static_assert(Buffer<int, 4>{}.capacity() == 4);`.

### A default for a value

```cpp
template <typename T, std::size_t N = 8>
class Window { ... };

Window<double> usual;            // N = 8
Window<double, 24> day;
```

### A shape in the type

The step towards the project of this chapter:

```cpp
template <typename T, std::size_t Rows, std::size_t Columns>
class Grid {
public:
    T& operator[](std::size_t row, std::size_t column) { return cells_[row * Columns + column]; }
    static constexpr std::size_t rows() { return Rows; }
    static constexpr std::size_t columns() { return Columns; }
private:
    std::array<T, Rows * Columns> cells_{};      // an expression of the parameters: the compiler computes it
};
```

`Grid<double, 2, 3>` and `Grid<double, 3, 2>` are different types. And addition can say, in its **declaration**, that both operands have the same shape:

```cpp
template <typename T, std::size_t Rows, std::size_t Columns>
Grid<T, Rows, Columns> add(const Grid<T, Rows, Columns>& a, const Grid<T, Rows, Columns>& b) { ... }
```

`Rows` and `Columns` appear in both parameters, so the compiler can deduce them only when the two grids agree. `add(a, tall)` with a 2 x 3 and a 3 x 2 grid **does not compile**; there is no run-time check, and no exception to throw. This is the idea behind the whole project.

### Deduced from the argument

The compiler can deduce a value parameter too:

```cpp
template <typename T, std::size_t N>
T sum_of(const std::array<T, N>& values) { ... }

std::array<int, 4> hours{6, 12, 18, 24};
sum_of(hours)            // N = 4 is deduced: there is no size argument to get wrong
```

```
sum[1, 2] = 13   shape 2 x 3
sum_of(hours) = 60   sum_of(readings) = 64
```

### What can be a value parameter

In practice: integers (including `bool` and `char`) and enumerations. C++20 widened the list, but these are the ones to reach for.

**Code for this lecture**: `16.5NonTypeParameters/main.cpp`.

---

## 16.6 Type traits

In this lecture we meet `<type_traits>`: a library of **questions** and **transformations** about types, all answered while the program is being compiled.

You have already seen three of them used, with the promise that they would be explained: `std::is_nothrow_move_constructible_v` (13.5), `std::is_trivially_copyable_v` (13.9), and the `decltype` of 14.8. Here is the family.

### Questions: is this type ...?

The `_v` at the end of a trait's name means "give me the **value**": a `bool` constant, known at compile time.

```cpp
std::is_integral_v<int>              // true
std::is_floating_point_v<double>     // true
std::is_arithmetic_v<char>           // true  (integers and floating point)
std::is_arithmetic_v<std::string>    // false
std::is_pointer_v<int*>              // true
std::is_const_v<const int>           // true
std::is_same_v<int, long>            // false
std::is_convertible_v<int, double>   // true
std::is_convertible_v<std::string, int>   // false
```

```
is_integral_v<int>               = true
is_integral_v<double>            = false
is_floating_point_v<double>      = true
is_arithmetic_v<char>            = true
is_arithmetic_v<std::string>     = false
is_pointer_v<int*>               = true
is_const_v<const int>            = true
is_same_v<int, int>              = true
is_same_v<int, long>             = false
is_convertible_v<int, double>    = true
is_convertible_v<std::string, int> = false
```

### The questions of earlier chapters

```cpp
struct Careful { Careful(Careful&&) noexcept {} ... };
struct Nervous { Nervous(Nervous&&) {} ... };         // the move may throw, as far as the compiler knows
```

```
is_nothrow_move_constructible_v<Careful> = true
is_nothrow_move_constructible_v<Nervous> = false
is_trivially_copyable_v<Reading>         = true
is_trivially_copyable_v<std::string>     = false
```

That is the question behind 13.5: a `std::vector` that grows moves its elements only if `std::is_nothrow_move_constructible_v` is true for them, and copies them otherwise. And 13.9's `std::is_trivially_copyable_v<Reading>` asked whether a `Reading` may be copied byte for byte.

### Transformations: give me a related type

A transformation produces a **type**, named with `_t`:

```cpp
std::remove_const_t<const int>         // int
std::remove_reference_t<int&>          // int
std::remove_cvref_t<const int&>        // int   (no reference, no const, no volatile)
std::add_const_t<int>                  // const int
std::common_type_t<int, double>        // double  (the type 2 + 3.5 has)
std::make_unsigned_t<int>              // unsigned int
```

A type cannot be printed, so we ask `std::is_same_v` about it:

```
remove_const_t<const int> is int           : true
remove_reference_t<int&> is int            : true
remove_cvref_t<const int&> is int          : true
add_const_t<int> is const int              : true
common_type_t<int, double> is double       : true
make_unsigned_t<int> is unsigned int       : true
```

### `decltype`: the type of an expression

`decltype(expression)` is the type that an expression has. It is how a trait can be asked about a **value** you have, instead of a type you name (14.8 used it for a lambda):

```cpp
auto total{2 + 3.5};
std::is_same_v<decltype(total), double>             // true
std::vector<int> counts{1, 2, 3};
std::is_same_v<decltype(counts.size()), std::size_t>   // true
std::is_same_v<decltype(counts[0]), int&>              // true: operator[] returns a reference
```

### A trait that chooses a type

```cpp
template <std::size_t N>
using SmallestIndex = std::conditional_t<(N <= 255), std::uint8_t,
                      std::conditional_t<(N <= 65535), std::uint16_t, std::uint32_t>>;
```

Two new things in this definition. `using Name = ...;` with a `template <...>` in front is an **alias template**: a name for a type that depends on a parameter (the `using` aliases of 7.10 were plain ones). And `std::conditional_t<condition, A, B>` is `A` when the condition is true and `B` otherwise, decided while compiling. Chained, it picks the smallest unsigned integer that can hold the numbers up to N:

```
sizeof(SmallestIndex<100>)     = 1 byte
sizeof(SmallestIndex<1000>)    = 2 bytes
sizeof(SmallestIndex<100000>)  = 4 bytes
```

### A trait in a template, with a message of our own

```cpp
template <typename T>
T half_of(T value) {
    static_assert(std::is_arithmetic_v<T>, "half_of needs a number");
    return value / 2;
}
```

`half_of(21)` and `half_of(24.0)` work. `half_of(std::string{"north"})` stops with *half_of needs a number*, the sentence we wrote, instead of a failure at `value / 2`. That is the trick of this lecture: ask a question about `T` in a `static_assert`. The next lecture does the same thing with a nicer tool.

### The pattern to remember

> **`std::xxx_v<T>` answers a yes/no question about a type; `std::xxx_t<T>` produces a related type; both while compiling. `decltype(x)` is the type of `x`.**

**Code for this lecture**: `16.6TypeTraits/main.cpp`.

---

## 16.7 Constraining templates with concepts

In this lecture we use the **concepts** of the standard library to say what a template needs.

### The problem

In 16.2, `larger_of(Marker{}, Marker{})` for a type without `<` failed with an error **inside** the template, at `a < b`. The template needed a type that can be ordered, and nothing in its declaration said so. A **concept** is a name for a requirement on a type. It is a compile-time yes or no, like the traits of 16.6, but meant to be written in the template's declaration. The standard library has dozens, in `<concepts>`, `<iterator>` and `<ranges>`.

### Three ways to write the same requirement

"`T` can be ordered with `<`, `>`, `<=`, `>=`":

```cpp
// 1. in the template header, in place of `typename`
template <std::totally_ordered T>
T larger_of(T a, T b) { return a < b ? b : a; }

// 2. with a requires clause after the header
template <typename T>
    requires std::totally_ordered<T>
T smaller_of(T a, T b) { return b < a ? b : a; }

// 3. with the concept in front of `auto` (16.3): the shortest
auto clamp_low(std::totally_ordered auto value, std::totally_ordered auto floor) {
    return value < floor ? floor : value;
}
```

```
larger_of(3, 8)              = 8
larger_of("a", "b") strings  = south
smaller_of(2.5, 1.5)         = 1.5
clamp_low(18, 20)            = 20
```

### The error moves to the call

What does `larger_of(Marker{}, Marker{})` say now? On Clang:

```
error: no matching function for call to 'larger_of'
note: candidate template ignored: constraints not satisfied [with T = Marker]
note: because 'Marker' does not satisfy 'totally_ordered'
note: because 'Marker' does not satisfy 'equality_comparable'
note: because '__t == __u' would be invalid ...
```

and on GCC:

```
error: no matching function for call to 'larger_of(Marker, Marker)'
  constraints not satisfied
  required for the satisfaction of 'totally_ordered<T>' [with T = Marker]
  required for the satisfaction of 'equality_comparable<_Tp>' [with _Tp = Marker]
```

Different words, same message: it names **your call**, the requirement that was not met, and the chain down to the reason. Compare with an error buried inside the template.

### A constraint on one member function

A `requires` clause can also follow the parameter list of a **member function**, to restrict that one function. The class works for every `T`; `larger()` exists only for a `T` that can be ordered:

```cpp
template <typename T>
class Pair {
public:
    Pair(T first, T second) : first_{first}, second_{second} {}

    T larger() const
        requires std::totally_ordered<T>
    {
        return first_ < second_ ? second_ : first_;
    }
    ...
};

Pair numbers{3, 8};                      // Pair<int>: numbers.larger() is 8
Pair<Marker> markers{Marker{}, Marker{}};    // fine
// markers.larger();                     // error: the constraint of larger() is not satisfied
```

(The project's `Matrix` uses this for `identity()` and `trace()`, which exist only for square matrices.)

### Constraints choose between overloads

```cpp
void describe(std::integral auto value)       { std::println("  {} is a whole number", value); }
void describe(std::floating_point auto value) { std::println("  {} is a fraction", value); }
void describe(const std::string& value)       { std::println("  '{}' is text", value); }
```

```
  42 is a whole number
  21.5 is a fraction
  'north' is text
```

A constraint that fails is not an error when another overload fits: that overload is simply not a candidate. In 16.2 a template competed with an ordinary function; here constraints decide.

### Concepts for ranges and callables

```cpp
template <std::ranges::input_range R>
double total_of(const R& values) { ... }               // any range: vector, list, a view ...

template <std::invocable<double> F>
double apply_to_each(const std::vector<double>& values, F function) { ... }
```

```
total_of(vector<double>) = 64
total_of(list<int>)      = 23
total_of(iota(1, 5))     = 10
sum of doubled temperatures = 128
```

`std::ranges::input_range` is the concept behind the ranges of chapter 15, and `std::invocable<double>` says "something that can be called with a `double`". Misuse reads clearly:

```
total_of(5)                  GCC: required for the satisfaction of 'input_range<R>' [with R = int]
                             Clang: because 'int' does not satisfy 'input_range'
apply_to_each(temperatures, 5)   GCC: 'int' cannot be used as a function
                                 Clang: because 'std::invocable<int, double>' evaluated to false
```

### Asking a concept directly

A concept is a `bool` known at compile time, so it works in a `static_assert` exactly like a trait. This is what the assertions of 14.2 were:

```cpp
static_assert(std::forward_iterator<std::list<int>::iterator>);
static_assert(!std::random_access_iterator<std::list<int>::iterator>);
static_assert(std::random_access_iterator<std::vector<int>::iterator>);
```

```
integral<int> = true   integral<double> = false
totally_ordered<Marker> = false
same_as<int, int> = true   convertible_to<int, double> = true
derived_from<std::string, std::string> = true
```

(The iterator categories of 14.2 and the range categories of 15.2 are concepts: `std::forward_iterator`, `std::random_access_range`, ...)

### A few of the standard concepts

```
   numbers      std::integral   std::signed_integral   std::unsigned_integral   std::floating_point
   comparison   std::equality_comparable   std::totally_ordered
   objects      std::copyable   std::movable   std::default_initializable
   conversion   std::same_as<A, B>   std::convertible_to<From, To>   std::derived_from<D, B>
   callables    std::invocable<F, Args...>   std::predicate<F, Args...>
   iterators    std::forward_iterator   std::random_access_iterator ...
   ranges       std::ranges::range   std::ranges::input_range   std::ranges::random_access_range ...
```

### The pattern to remember

> **Say what your template needs, in its declaration. The error then names the call and the requirement, and overloads can step aside.**

**Code for this lecture**: `16.7UsingConcepts/main.cpp`.

---

## 16.8 Writing your own concepts

In this lecture we write concepts of our own.

### From traits and other concepts

```cpp
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
concept SmallNumber = Number<T> && (sizeof(T) <= 4);
```

A concept is defined with `concept Name = ...;` and a boolean expression of constants, joined with `&&` and `||`. `Number<int>` is `true`, `Number<std::string>` is `false`, and `SmallNumber<int>` and `SmallNumber<float>` are `true` while `SmallNumber<double>` is `false` (8 bytes).

```
Number<int> = true   Number<std::string> = false
SmallNumber<int> = true   SmallNumber<double> = false   SmallNumber<float> = true
```

### From a requires expression: "these must compile"

A **requires expression** lists code that must be valid for the type. The names in its parentheses stand for objects of the type; **nothing is ever run**.

```cpp
template <typename T>
concept Addable = requires(T a, T b) {
    a + b;                                       // a simple requirement: this must compile
};

template <typename T>
concept Resettable = requires(T& item) {
    item.reset();                                // a member function reset() must exist
};

// A compound requirement also checks what the expression gives back.
template <typename T>
concept Measurable = requires(const T& item) {
    { item.size() } -> std::convertible_to<std::size_t>;
};

// A type requirement: the type must have a nested type with this name.
template <typename T>
concept HasValueType = requires {
    typename T::value_type;
};
```

And one for the weather station, the shape of "something that reports a temperature":

```cpp
template <typename T>
concept Sensor = requires(const T& sensor) {
    { sensor.celsius() } -> std::convertible_to<double>;
    { sensor.name() } -> std::convertible_to<std::string>;
};
```

```
Addable<int> = true   Addable<std::string> = true   Addable<Silent> = false
Streamable<int> = true   Streamable<std::string> = true   Streamable<Silent> = false
Resettable<Counter> = true   Resettable<int> = false
Measurable<std::string> = true   Measurable<int> = false
HasValueType<std::vector<int>> = true   HasValueType<int> = false
Sensor<Thermometer> = true   Sensor<Counter> = false
```

(`Silent` is an empty struct; `Streamable` asks whether `stream << value` compiles for a `std::ostream`, the chapter 3 way of printing.) And a function that uses it:

```cpp
void report(const Sensor auto& sensor) {
    std::println("{} reads {} C", sensor.name(), sensor.celsius());     // roof reads 21.5 C
}
```

### A requirement a requires expression cannot see

A cautionary example, because we wrote it first. The obvious concept for "can be printed" looks like this:

```cpp
template <typename T>
concept Printable = requires(const T& value) {
    std::println("{}", value);
};
```

and it said `true` for `Silent`, a type with no formatter! The format string of `std::println` is checked by a function that must run while compiling (the `consteval` of 6.10, which 16.11 explains), and that check is not something a requires expression can detect: it is a hard error when it happens, not a "no". Only requirements that the compiler can ask about **while looking for a match** are reliable. In C++23 there is a ready-made concept for this question, `std::formattable`, but older libraries do not have it yet, so we used `Streamable` above instead. The lesson: **test your concepts with a type that should fail**, as the output above does with `Silent`.

### Subsumption: the more specific concept wins

```cpp
void classify(Number auto value)      { std::println("  {}: some number", value); }
void classify(SmallNumber auto value) { std::println("  {}: a number of at most 4 bytes", value); }
```

`SmallNumber` is built from `Number`, so it is **more constrained**. When both fit, the compiler picks it, without ambiguity:

```
  7: a number of at most 4 bytes        classify(7)     both fit, the specific one wins
  2.5: some number                      classify(2.5)   a double is 8 bytes: only the general one fits
  2.5: a number of at most 4 bytes      classify(2.5f)  a float is 4 bytes
```

(The rule only works because `SmallNumber` is *written in terms of* `Number`. Two unrelated concepts that happen to both be true would be ambiguous.)

### Why not just a `static_assert` with traits?

You could (16.6). A concept gives the requirement a **name**, which can be reused, combined and chosen between, and it fails **at the call**, so that overloads can step aside. A `static_assert` inside the body fires too late for that.

### The pattern to remember

> **Build a concept from other concepts with `&&` and `||`, or from a requires expression that lists the code that must compile. Then test it with a type that should NOT satisfy it.**

**Code for this lecture**: `16.8WritingConcepts/main.cpp`.

---

## 16.9 Specialization and `if constexpr`

In this lecture we deal with the type that needs something different from the general rule, and we keep the promise of 12.4 and 14.7.

### A specialization: a separate definition for one type

A template says what to do for **any** type. The "primary" template:

```cpp
template <typename T>
struct Label {
    static constexpr std::string_view text{"a value"};
};
```

and a **full specialization**: a complete, separate definition used for exactly one type.

```cpp
template <>
struct Label<double> {
    static constexpr std::string_view text{"degrees"};
};

template <>
struct Label<int> {
    static constexpr std::string_view text{"a count"};
};
```

`template <>` means *no parameters left to fill*: this is the whole answer for `Label<double>`.

```
Label<int>    : a count
Label<double> : degrees
Label<char>   : a value           no specialization for char: the general one
```

### A partial specialization: for a whole family

A pattern with some parameters still open:

```cpp
template <typename T>
struct Label<std::vector<T>> {                   // a vector of anything
    static constexpr std::string_view text{"a list"};
};

template <typename T>
struct Label<T*> {                               // a pointer to anything
    static constexpr std::string_view text{"an address"};
};
```

```
Label<std::vector<int>>    : a list
Label<std::vector<double>> : a list
Label<int*>                : an address
Label<std::string>         : a value
```

A *class* template can be partially specialized. A *function* template cannot: for functions use overloads, constrained by concepts (16.7).

### The promise kept

In 12.4 you pasted this:

```cpp
template <>
struct std::formatter<Vec2> { ... };
```

and in 14.7 this:

```cpp
template <>
struct std::hash<GridCell> { ... };
```

Now you can read them. `std::formatter` and `std::hash` are class templates of the standard library, whose primary templates say "this type has no formatter" and "this type has no hash". Your code is a **full specialization**: *for this type, the standard template should do the following*. The `std::formatter<Matrix<T, Rows, Columns>>` of the next project is a **partial** one: it covers every `Matrix` at once.

### `if constexpr`: a branch chosen while compiling

```cpp
template <typename T>
std::string describe(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        return "whole number " + std::to_string(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        return "fraction " + std::to_string(value);
    } else if constexpr (requires { value.size(); }) {      // a requires expression (16.8) as the test
        return "something with " + std::to_string(value.size()) + " elements";
    } else {
        return "something else";
    }
}
```

```
whole number 42
fraction 21.500000
something with 5 elements         a string
something with 3 elements         a vector
something else                    a Marker
```

The branches that are **not chosen are not compiled** for this `T`. That is the whole difference from a plain `if`. With a plain `if (std::is_integral_v<T>)`, the compiler would still have to compile the branch that calls `value.size()` for an `int`, and fail.

It also removes work: the unchosen branch generates no code.

```cpp
template <typename T>
T twice_or_negated(T value) {
    if constexpr (std::is_unsigned_v<T>) {
        return value * 2;                    // negating an unsigned value is meaningless: it wraps around
    } else {
        return -value;
    }
}
```

`twice_or_negated(21)` is -21, `twice_or_negated(21u)` is 42.

### Which tool?

```
   a different class or constant for particular types        specialization
   one function, small differences inside                    if constexpr
   different functions, chosen by what a type can do        overloads with concepts (16.7)
```

**Code for this lecture**: `16.9SpecializationAndIfConstexpr/main.cpp`.

---

## 16.10 Variadic templates, folds and forwarding

In this lecture we write templates that take **any number** of arguments, and pass arguments on without changing them. Together they are how `std::make_unique` (9.10), `std::vector::emplace_back` (14.3) and `std::println` itself work.

### A parameter pack

```cpp
template <typename... Args>
void count_args(Args... args) {
    std::println("  {} arguments", sizeof...(args));
}
```

`typename... Args` is a **parameter pack**: it stands for any number of types, zero or more. `Args... args` is the pack of the corresponding values, and `sizeof...(args)` is how many there are.

```
count_args();                           0 arguments
count_args(1);                          1 arguments
count_args(1, 2.5, std::string{"north"});   3 arguments
```

### Fold expressions: an operator across the pack

A **fold expression** applies an operator to all the elements of a pack:

```
   (pack + ...)             pack1 + (pack2 + (pack3 + ...))        a unary right fold
   (... + pack)             ((pack1 + pack2) + pack3) + ...        a unary left fold
   (init + ... + pack)      ((init + pack1) + pack2) + ...         a binary fold, with a start value
```

```cpp
template <typename... Numbers>
auto sum_all(Numbers... numbers) {
    return (0 + ... + numbers);            // the 0 also gives an answer for an empty pack
}

template <typename... Flags>
bool all_true(Flags... flags) {
    return (... && flags);                 // true for an empty pack
}

// The comma operator as the folded operator: do something for every element.
template <typename... Args>
void print_line(const Args&... args) {
    ((std::print("{} ", args)), ...);
    std::println();
}
```

```
sum_all()              = 0
sum_all(1, 2, 3)       = 6
sum_all(1, 2.5, 3)     = 6.5
all_true(true, 1 > 0)  = true
all_true(true, false)  = false
print_line:            21 24.5 north S
```

One function body, and it works for any number of arguments of any printable types.

### A constrained pack

Combine with 16.7: every argument must be the same type as the first.

```cpp
template <typename T, typename... Rest>
    requires (std::same_as<T, Rest> && ...)
T largest_of(T first, Rest... rest) {
    T best{first};
    ((best = rest > best ? rest : best), ...);
    return best;
}
```

`largest_of(3, 8, 5)` is 8, and `largest_of(3, 8.5)` does not compile: *constraint not satisfied*, an `int` is not a `double`.

### Forwarding: passing an argument on, unchanged

A function that receives an argument and passes it to another function has a problem. Take a type that counts what happens to it:

```cpp
struct Probe {
    static inline int copies{0};
    static inline int moves{0};
    Probe() = default;
    Probe(const Probe&) { ++copies; }
    Probe(Probe&&) noexcept { ++moves; }
    static void reset() { copies = 0; moves = 0; }
};
```

(`static inline` defines the shared counters right in the class: 10.10.) Now a function template that keeps what it is given:

```cpp
template <typename T>
void keep_wrong(T&& value) {
    [[maybe_unused]] Probe stored{value};                // always a copy
}
```

In a function template, **`T&&` with a `T` that is deduced is not an rvalue reference** (10.8). It is a **forwarding reference**: it binds to anything. If you pass an lvalue, `T` becomes `Probe&`; if you pass an rvalue, `T` becomes `Probe`.

But inside the function, `value` has a **name**, so it is an lvalue, whatever was passed. `Probe stored{value}` copies even when the caller passed a temporary. **`std::forward<T>(value)`** gives the value back as it arrived: an rvalue if an rvalue was passed, an lvalue if an lvalue was.

```cpp
template <typename T>
void keep_right(T&& value) {
    [[maybe_unused]] Probe stored{std::forward<T>(value)};
}
```

```
keep_wrong(rvalue):    1 copies, 0 moves   (the temporary was copied)
keep_right(rvalue):    0 copies, 1 moves   (the temporary was moved)
keep_right(lvalue):    1 copies, 0 moves   (a named object must be copied)
```

### Any number of arguments, passed on

Put the two together:

```cpp
class Log {
public:
    template <typename... Args>
    void emplace(Args&&... args) {
        items_.emplace_back(std::forward<Args>(args)...);       // construct in place from the arguments
    }
    ...
private:
    std::vector<Reading> items_;
};

log.emplace("north", 18.5);               // goes straight to Reading{"north", 18.5}
log.emplace(std::string{"south"}, 24.0);
```

```
2 readings, last: south 24
```

`Args&&... args` is a pack of forwarding references, and `std::forward<Args>(args)...` expands to one `std::forward` per argument. This is the whole mechanism behind `emplace_back` (14.3) and `make_unique` (9.10): take anything, pass it on as it came, and let the constructor do the work.

### The pattern to remember

> **`Args...` for any number of parameters; a fold to combine them; `T&&` plus `std::forward<T>` to pass them on without an extra copy.**

**Code for this lecture**: `16.10VariadicTemplates/main.cpp`.

---

## 16.11 Computing at compile time

In this lecture we finish the chapter's other half: not writing code for many types, but making the compiler **do the work**.

6.10 introduced `constexpr` variables and functions. A `constexpr` function can run while the program is being **compiled**, when its arguments are known then, and the answer becomes part of the executable. Doing work at compile time is what "metaprogramming" means in C++: the program writes parts of itself.

### The old way and the new way

The first metaprograms were *templates that compute*: recursion through instantiation, stopped by a specialization (16.9):

```cpp
template <unsigned N>
struct Factorial {
    static constexpr unsigned long long value{N * Factorial<N - 1>::value};
};

template <>
struct Factorial<0> {
    static constexpr unsigned long long value{1};
};
```

`Factorial<10>::value` is computed by the compiler. It works, and it is hard to read. Today the same thing is an ordinary function with `constexpr` in front of it:

```cpp
constexpr unsigned long long factorial(unsigned n) {
    unsigned long long result{1};
    for (unsigned i{2}; i <= n; ++i) {
        result *= i;
    }
    return result;
}
```

Loops, local variables and calls to other `constexpr` functions are all allowed. Both agree, and the compiler can check it:

```cpp
constexpr unsigned long long at_compile_time{factorial(10)};       // forced to be computed now
static_assert(at_compile_time == 3'628'800);
static_assert(Factorial<5>::value == factorial(5));
```

```
Factorial<10>::value = 3628800
factorial(10)         = 3628800
```

### A table made by the compiler

```cpp
constexpr std::array<double, 41> make_fahrenheit_table() {
    std::array<double, 41> table{};
    for (std::size_t celsius{0}; celsius < table.size(); ++celsius) {
        table[celsius] = static_cast<double>(celsius) * 9.0 / 5.0 + 32.0;
    }
    return table;
}

constexpr auto table{make_fahrenheit_table()};
static_assert(table[0] == 32.0 && table[10] == 50.0);
```

```
0 C = 32 F   20 C = 68 F   40 C = 104 F
```

The conversion table is computed once, by the compiler, and sits in the program. At run time, converting a temperature is an array lookup.

### Algorithms and classes

The standard algorithms are `constexpr` too (since C++20), and so can a class be: a constructor and member functions that may run at compile time.

```cpp
class Celsius {
public:
    constexpr explicit Celsius(double degrees) : degrees_{degrees} {}
    constexpr double fahrenheit() const { return degrees_ * 9.0 / 5.0 + 32.0; }
    constexpr bool freezing() const { return degrees_ <= 0.0; }
private:
    double degrees_;
};

constexpr Celsius boiling_point{100.0};
static_assert(boiling_point.fahrenheit() == 212.0);
```

```
sum_of_squares(4) = 30   100 C = 212 F   -5 C freezing: true
run time: Celsius{54}.fahrenheit() = 129.2
```

The same functions work at run time with run-time arguments. `constexpr` means *allowed at compile time*, not *only*.

### `consteval`: only at compile time

A `consteval` function **must** run at compile time. Calling it with a value the compiler does not know is an error. That makes it good for checking a setting early:

```cpp
consteval std::size_t slots_for(int hours, int readings_per_hour) {
    if (hours <= 0 || readings_per_hour <= 0) {
        throw "hours and readings per hour must be positive";
    }
    return static_cast<std::size_t>(hours * readings_per_hour);
}

constexpr std::size_t slots{slots_for(24, 4)};        // 96
std::array<double, slots> day{};                      // so the size is a constant, and checked
```

```
slots_for(24, 4) = 96   a day of readings holds 96
```

In a `consteval` function a `throw` that is reached is a **compile error**, which is exactly what we want. Two calls the compiler rejects:

```
slots_for(0, 4)          GCC: call to consteval function 'slots_for(0, 4)' is not a constant expression
                              expression '<throw-expression>' is not a constant expression
slots_for(degrees, 4)    GCC: the value of 'degrees' is not usable in a constant expression
```

### `if consteval` (C++23)

Different code depending on whether the function is being evaluated at compile time or at run time:

```cpp
constexpr std::string_view where_am_i() {
    if consteval {
        return "compile time";
    } else {
        return "run time";
    }
}

constexpr std::string_view during_compile{where_am_i()};
```

```
a constant:      compile time
a normal call:   run time
```

(Older compilers do not have `if consteval`. Its C++20 predecessor is `std::is_constant_evaluated()`.)

### `constinit`

```cpp
constinit int readings_taken{0};
```

`constinit` guarantees the variable is **initialized at compile time**, so there is no dynamic initialization to run before `main()`, but it is **not constant**: it can change later. It applies to variables that live for the whole program.

```
   const        never changes after initialization (it may be set at run time)
   constexpr    never changes, and its value is known at compile time
   consteval    a function that can only run at compile time
   constinit    changes later, but its first value is known at compile time
```

```
readings_taken = 2 (started at 0 without any code running at start-up)
```

### Why this matters

Everything the compiler computes is a thing that does not run on the user's machine, and a mistake the compiler finds is a mistake that cannot reach a user. The project makes both points with a matrix.

**Code for this lecture**: `16.11CompileTimeComputation/main.cpp`.

---

## 16.12 Project: the generic Matrix

In chapter 12 the `Matrix` stored `double`s in a `std::vector`, kept its shape as a run-time value, and **threw** `std::invalid_argument` when you added matrices of different sizes. In chapter 13 we wrote tests that checked those exceptions. Now we make it generic, with every tool of this chapter, and the mistakes stop being exceptions: they stop **compiling**.

```
   chapter 12                              this chapter
   --------------------------------------  --------------------------------------------
   cells are always double                 any number type: Matrix<int, ...>, Matrix<float, ...>
   the shape is a run-time value           the shape is part of the TYPE: Matrix<double, 2, 3>
   a wrong shape throws (chapter 13)       a wrong shape does not COMPILE
   cells live in a std::vector (heap)      cells live in a std::array (inside the object)
   operations run at run time              operations can run at compile time (constexpr)
```

### The files

```
   16.12ProjectMatrixTemplate/
      matrix.h        the Matrix<T, Rows, Columns> template
      main.cpp        a tour with weather data, and compile-time computation       target rooster
      tests.cpp       compile-time tests (static_assert) and run-time tests        target rooster_tests
      CMakeLists.txt  both targets, and `ctest`
```

### The template

```cpp
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number T, std::size_t Rows, std::size_t Columns>
class Matrix {
public:
    static_assert(Rows > 0 && Columns > 0, "a Matrix needs at least one row and one column");
    ...
private:
    std::array<T, Rows * Columns> cells_{};
};
```

- **`Number`** (16.8) is the concept that `T` must satisfy: `Matrix<std::string, 2, 2>` does not compile.
- **`Rows` and `Columns`** are value parameters (16.5), and the cells live in a `std::array` of `Rows * Columns`: no heap, and the compiler knows the size.

### Construction: exactly the right number of values

```cpp
template <typename... Values>
    requires (sizeof...(Values) == Rows * Columns && (std::convertible_to<Values, T> && ...))
constexpr explicit Matrix(Values... values) : cells_{static_cast<T>(values)...} {}
```

A variadic constructor (16.10) constrained (16.7) to take **exactly `Rows * Columns` values**, each convertible to `T`. So `Matrix<int, 2, 2> m{1, 2, 3, 4}` works, and `Matrix<double, 2, 2> d{1, 2, 3}` does not compile: three numbers for four cells. It is `explicit` (12.8) so that a single number cannot silently become a 1 x 1 matrix.

Also `Matrix::filled(value)`, `Matrix::identity()`, `operator[](row, column)` (C++23, 12.6) and a checked `at(row, column)` that still throws `std::out_of_range`: a *shape* can no longer be wrong, but an index computed at run time still can.

### Member functions that exist only for some shapes

```cpp
static constexpr Matrix identity()
    requires (Rows == Columns)
{ ... }

constexpr T trace() const
    requires (Rows == Columns)
{ ... }
```

The trailing `requires` (16.7) removes the function for a matrix that is not square. `Matrix<double, 2, 3>::identity()` does not exist.

### The operators

Element-wise arithmetic is written as in chapter 12 (compound assignment as members, the binary operators as hidden friends, 12.3), but now both operands are `Matrix<T, Rows, Columns>`: the same type, hence the same shape. Adding a 3 x 4 and a 4 x 3 matrix finds no `operator+`.

The **product** is a free function template where the inner size appears twice:

```cpp
template <Number T, std::size_t Rows, std::size_t Inner, std::size_t Columns>
constexpr Matrix<T, Rows, Columns> operator*(const Matrix<T, Rows, Inner>& left,
                                             const Matrix<T, Inner, Columns>& right) {
    ...
}
```

`(Rows x Inner)` times `(Inner x Columns)` is `(Rows x Columns)`. `Inner` is deduced from **both** arguments, so it only works when they agree, and the result type is worked out by the compiler. `transposed()` returns a `Matrix<T, Columns, Rows>`, with the numbers swapped in the type as well.

### Printing: a partial specialization

```cpp
template <typename T, std::size_t Rows, std::size_t Columns>
struct std::formatter<Matrix<T, Rows, Columns>> {
    std::formatter<T> cell;

    constexpr auto parse(std::format_parse_context& context) {
        return cell.parse(context);
    }

    auto format(const Matrix<T, Rows, Columns>& matrix, std::format_context& context) const { ... }
};
```

This is the 12.4 formatter, now that you can read it: a **partial specialization** (16.9) of the library's `std::formatter` for every `Matrix`, whatever its type and shape. As in 12.4, the format spec is handed to the formatter of the cell type, so `{:6.1f}` works for doubles and `{:3}` for ints.

### The tour

Three stations, four readings each (at 6, 12, 18 and 24 hours):

```cpp
Matrix<double, 3, 4> readings{
    11.5, 18.5, 15.0, 12.0,       // north
    14.0, 24.0, 20.5, 16.5,       // south
    12.5, 21.5, 17.0, 13.0};      // east
std::println("readings, {} stations x {} readings:\n{:6.1f}", readings.rows(), readings.columns(), readings);
```

```
readings, 3 stations x 4 readings:
  [   11.5   18.5   15.0   12.0 ]
  [   14.0   24.0   20.5   16.5 ]
  [   12.5   21.5   17.0   13.0 ]
```

A weighted average per station is a **matrix product**: (3 x 4) times (4 x 1) is (3 x 1). The midday readings count most:

```cpp
Matrix<double, 4, 1> weights{0.1, 0.4, 0.4, 0.1};
auto weighted{readings * weights};
static_assert(std::is_same_v<decltype(weighted), Matrix<double, 3, 1>>);     // the compiler knows the shape
```

```
weighted average per station, 3 x 1:
  [  15.75 ]
  [  20.85 ]
  [  17.95 ]
```

Then the transpose (4 x 3), the sum of all cells with `std::accumulate` (the cells form a range, so the algorithms of chapter 15 work: 196), operators (`2 * readings - readings == readings`), a matrix of `int`s (the alarms per station, printed with `{:3}`), and the identity of a 3 x 3 matrix with its trace.

### The compiler does the arithmetic

```cpp
constexpr Matrix<int, 2, 2> m{1, 2, 3, 4};
constexpr auto squared{m * m};
static_assert(squared[0, 0] == 7 && squared[0, 1] == 10 && squared[1, 0] == 15 && squared[1, 1] == 22);
```

The matrix, the product and the check are all done while compiling. A bigger example: the matrix `[[1, 1], [1, 0]]` raised to the power *n* has the *n*-th Fibonacci number in its corner, so the Fibonacci numbers are a loop of matrix products:

```cpp
constexpr long long fibonacci(int n) {
    Matrix<long long, 2, 2> step{1, 1, 1, 0};
    auto result{Matrix<long long, 2, 2>::identity()};
    for (int i{0}; i < n; ++i) {
        result = result * step;
    }
    return result[0, 1];
}

constexpr long long fib{fibonacci(30)};
static_assert(fib == 832'040);
```

```
fibonacci(30), computed by the compiler with matrix products: 832040
fibonacci(10) at run time: 55
```

### What does not compile

The five commented lines at the end of `main.cpp`. Each mistake is found by the compiler, at the line where it is made:

```
auto a{readings + by_hour};                 a 3 x 4 matrix plus a 4 x 3 one
    GCC:   no match for 'operator+' (operand types are 'Matrix<double, 3, 4>' and 'Matrix<double, 4, 3>')
    Clang: invalid operands to binary expression ... candidate function not viable:
           no known conversion from 'Matrix<[...], 4, 3>' to 'const Matrix<[...], 3, 4>'

auto b{readings * readings};                (3 x 4) times (3 x 4): the inner sizes 4 and 3 differ
    GCC:   no match for 'operator*' (operand types are 'Matrix<double, 3, 4>' and 'Matrix<double, 3, 4>')
    Clang: candidate template ignored: deduced conflicting values for parameter 'Inner' (4 vs. 3)

auto c{Matrix<double, 2, 3>::identity()};   a 2 x 3 matrix is not square
    GCC:   no matching function for call to 'Matrix<double, 2, 3>::identity()'
    Clang: invalid reference to function 'identity': constraints not satisfied
           because '2UL == 3UL' (2 == 3) evaluated to false

Matrix<double, 2, 2> d{1, 2, 3};            three numbers for four cells
    GCC:   no matching function for call to 'Matrix<double, 2, 2>::Matrix(<brace-enclosed initializer list>)'
    Clang: candidate template ignored: constraints not satisfied [with Values = <int, int, int>]

Matrix<std::string, 2, 2> e;                a string is not a Number
    GCC:   template constraint failure for ... requires Number<T> class Matrix
    Clang: constraints not satisfied for class template 'Matrix' [with T = std::basic_string<char>, ...]
           because 'std::basic_string<char>' does not satisfy 'Number'
```

Clang's note on the second one, *deduced conflicting values for parameter 'Inner' (4 vs. 3)*, says it all: the shapes did not agree.

### Testing code that must not compile

13.10 tested that wrong shapes **throw**. Now there is nothing to throw. How do you test that something does not compile? You ask the compiler, with a concept that wraps a requires expression (16.8), and a `static_assert` (13.9):

```cpp
template <typename A, typename B>
concept CanAdd = requires(A a, B b) { a + b; };

template <typename A, typename B>
concept CanMultiply = requires(A a, B b) { a * b; };

using M22 = Matrix<double, 2, 2>;
using M23 = Matrix<double, 2, 3>;
using M32 = Matrix<double, 3, 2>;

static_assert(CanAdd<M23, M23>);
static_assert(!CanAdd<M23, M32>, "adding different shapes must not compile");
static_assert(CanMultiply<M23, M32>);
static_assert(!CanMultiply<M23, M23>, "(2 x 3) times (2 x 3) must not compile");
static_assert(!HasIdentity<M23>, "a matrix that is not square has no identity");
static_assert(!std::constructible_from<M22, double, double, double>);
static_assert(std::same_as<decltype(M23{} * M32{}), M22>);
```

`tests.cpp` has two parts. **Part 1** is a list of such `static_assert`s, checked **while compiling**: if the file builds, they all passed. **Part 2** is the hand-made harness of 13.10 (with the same trap of the comma in `sum[0, 0]` inside the `CHECK` macro, needing double parentheses) running ten tests with 25 checks: row-by-row construction, `at()` throwing `std::out_of_range`, arithmetic, products of different shapes, identity and transpose, integers, the cells as a range, floating point with a tolerance (12.7), and the formatter for `int` and `double`.

```
$ ctest
100% tests passed, 0 tests failed out of 1
```

The run-time part printed:

```
[ ok ] construction_is_row_by_row
[ ok ] default_and_filled
[ ok ] at_checks_the_index
...
compile-time tests: passed (this file compiled)
10 run-time tests, 0 failed; 25 checks, 0 failed
```

### Build

```
cmake -S . -B build -G Ninja
cmake --build build
./build/rooster
./build/rooster_tests
ctest --test-dir build
```

Built and run on MSVC, GCC 16 and Clang 21 with identical output, and the tests are clean under AddressSanitizer and UndefinedBehaviorSanitizer on GCC.

### Things to try

1. Add `operator-` unary, or `row(r)` returning a `Matrix<T, 1, Columns>`. What is the return type, and who computes it?
2. Make `Matrix<T, R, C>` also accept `std::ranges::range`s of values in its constructor. Which concept would you use?
3. Add a `static_assert` test that `Matrix<int, 1, 1>{5}` is **not** implicitly convertible from an `int`. (Hint: `std::is_convertible_v`.)
4. Write `Matrix<T, R, C> power(const Matrix<T, R, R>& m, int n)` as a `constexpr` function, and use it in place of the loop in `fibonacci`.
5. Print `sizeof(Matrix<double, 3, 4>)`. Compare with chapter 12's `Matrix`, which keeps a `std::vector`.

**Code for this project**: `16.12ProjectMatrixTemplate/`.

---

## 16.13 Assignment

Eight small jobs for the weather station, one idea of the chapter each. `main.cpp` has the eight exercises, each with its statement and a sample run in a comment, and `matrix.h` is the generic Matrix of 16.12, provided for exercise 8. You write each template or function above `main()` and the lines that use it in `main()` under its heading. `main_solution.cpp` solves all eight. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `clamped` and `as` | a function template with one `T`; a parameter the caller must name |
| 2 | `between` and `print_labelled` | a generic lambda with captures; an abbreviated function template |
| 3 | `Series<T>` | a class template with an `initializer_list` constructor, so that `T` is deduced |
| 4 | `FixedStack<T, N>` | a value parameter, `static_assert`, `std::array`, `std::optional` |
| 5 | `Narrowest<N>` | an alias template with `std::conditional_t`, and traits |
| 6 | `Measurement` and `half` | a concept with compound requirements; overloads by `std::integral` and `std::floating_point` |
| 7 | `average_of_all`, `print_all`, `all_positive` | parameter packs and fold expressions |
| 8 | `sum_of_squares` and the Matrix | `constexpr`, and `static_assert` on a compile-time matrix product |

The generic Matrix project has no exercise of its own: the exercise is to try the list at the end of 16.12, and to read the compiler's complaint when you break a shape on purpose.

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole chapter.

After this chapter the student can write function and class templates, generic lambdas and abbreviated templates, templates with a value as a parameter, ask questions about types with traits and with concepts, write concepts of their own, specialize a template or branch with `if constexpr`, write variadic templates with folds and forward their arguments, and make the compiler compute with `constexpr` and `consteval`. They can also read the templates of the standard library with understanding: the formatter and the hash they pasted in earlier, the iterator and range concepts, `emplace_back` and `make_unique`. The next chapter turns to **modules**: how to stop including headers, so that a template, a class or a whole library is compiled once and imported.
