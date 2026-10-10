# Operator Overloading

You have been using operators since chapter 5: `+`, `==`, `<`, `[]`, `<<`. They work on numbers because the language defines them for numbers. But you have also been using them on things that are not numbers: you added two `std::string`s with `+`, compared two `std::vector`s with `==`, indexed a `std::vector` with `[]`, and sent text to `std::cout` with `<<`. Those operators are defined by the **classes**, and C++ lets you do the same for your own.

```
   built-in types                         your own types
   ──────────────                         ──────────────
   double a{1.5}, b{2.5};                 Vec2 a{1.0, 2.0}, b{3.0, 4.0};
   double sum{a + b};                     Vec2 sum{a + b};            ← the same notation
```

That is **operator overloading**: giving the operators a meaning for a class, so that code that uses it reads like the maths or the English it is modelling. A `Matrix` is added and multiplied, a `Version` is compared, a `Length` is written as `1.5_km`.

Done well, it makes code short and obvious. Done badly, it makes code baffling: a `+` that does something that has nothing to do with adding. So this chapter is as much about **restraint** as about syntax, and the first and last rule is the same one: **an operator should do what its symbol suggests.**

Two classes run through the chapter. A small `Vec2` (a wind arrow on a map) introduces each operator. A `Matrix` brings them together, and chapters 13 and 16 build on it. The chapter ends with a **project of a different kind**: using someone else's libraries, which you get with a package manager called **vcpkg**, including **ftxui**, a library whose whole interface is built on an overloaded `|`.

---

## 12.2 Operators are functions

In this lecture we look at what an operator really is, and write our first few.

### An operator is a function with a funny name

```cpp
struct Vec2 {
    double x;
    double y;
};

Vec2 operator+(Vec2 a, Vec2 b) {
    return Vec2{a.x + b.x, a.y + b.y};
}
```

The function is called **`operator+`**: the word `operator` followed by the symbol. It takes two `Vec2` values and returns a new one. And now this works:

```cpp
Vec2 a{1.0, 2.0};
Vec2 b{3.0, 4.0};

Vec2 sum{a + b};                 // the readable form
Vec2 sum_again{operator+(a, b)}; // exactly the same call
```

```
a + b              (4, 6)
operator+(a, b)    (4, 6)
```

The two lines are **the same thing**. The compiler turns `a + b` into `operator+(a, b)`. There is no magic in operator overloading: only a nicer way to write a function call.

### The family

The program defines four, and each one is just a function:

```cpp
Vec2 operator-(Vec2 a, Vec2 b);          // binary minus: two operands
Vec2 operator-(Vec2 v);                  // unary minus: ONE operand, same symbol
Vec2 operator*(Vec2 v, double factor);   // a vector times a number
```

```
a - b              (-2, -2)
-a                 (-1, -2)
b * 2.0            (6, 8)
```

The compiler tells `operator-(a, b)` from `operator-(v)` by the **number of operands**, just as it tells overloaded functions apart by their parameters (6.9).

### What does not change

Operator overloading changes **what an operator does for your type**. It does not change how the operator behaves in an expression:

```cpp
show("a + b * 2.0", a + b * 2.0);        // (7, 10)
show("a + b + a - b", a + b + a - b);    // (2, 4)
```

- **Precedence** is the built-in one: `*` still binds tighter than `+`, so the first line is `a + (b * 2.0)`.
- **Associativity** is the built-in one: the second line runs left to right.
- The **number of operands** stays: you cannot make a unary `/`.

### The limits

```
   can overload      + - * / % ++ -- == != < > <= >= <=> [] () -> << >>  and more
   cannot overload   ::  .  .*  ?:  sizeof
   cannot invent     there is no "**" for powers, however much you want one
   needs a user type at least one operand must be a type you wrote: you cannot redefine 1 + 2
```

### The rule that matters most

**An operator should do what its symbol suggests.** A `+` that subtracts, or a `<<` that opens a file, is legal and a disaster for whoever reads the code. Ask: *if a stranger saw this expression, would they guess what it does?* If you cannot think of an obvious meaning, **write a named function instead**. `matrix.transposed()` is better than inventing `~matrix`.

### What we have not done yet

```cpp
// show("2.0 * b", 2.0 * b);         // error: no operator*(double, Vec2)
```

We only wrote `Vec2 * double`, not `double * Vec2`. They are two different functions. 12.3 shows how to write both without repeating yourself.

**Code for this lecture**: `12.2OperatorsAreFunctions/main.cpp`.

---

## 12.3 Member or free, and compound assignment

In this lecture we write the operators the way real classes do: a few members, a few free functions, and the **compound** operators (`+=`) doing the real work.

### Where an operator can live

Every operator function can be written in two places:

```
   as a MEMBER function          a.operator+(b)       the left operand is the object itself
   as a FREE function            operator+(a, b)      both operands are parameters
```

Some operators **must** be members: `=` (assignment), `[]`, `()` and `->`. For the rest you choose, and the rule of thumb is:

```
   changes the object (+=, ++, =)                      member
   symmetric binary operators (+, -, ==, <)            free function, so both operands are treated alike
   needs the stream on the left (<<)                   free function, necessarily (12.4)
```

### Build `+` from `+=`

Look at the class:

```cpp
class Vec2 {
public:
    Vec2(double x, double y) : x_{x}, y_{y} {}

    Vec2& operator+=(const Vec2& other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    friend Vec2 operator+(Vec2 a, const Vec2& b) {
        a += b;
        return a;
    }
    // ...
};
```

The **compound** operator is the real work. It changes the object it is called on, so it is a **member**, and it **returns `*this` by reference** (10.10), like the built-in `+=`. The **binary** operator is built from it, in three lines:

- It takes the **left operand by value**: that is already a copy, which is exactly the thing to modify and return.
- It calls `+=` on that copy, and returns it.

So the addition is written **once**, in `+=`, and `+`, `-` and `*` need no loops of their own.

This is a **hidden friend**: a function **defined inside the class** with the keyword `friend`. It is a **free function** (not a member), which can see the private data, and which the compiler finds only when one of the arguments is a `Vec2`, so it does not clutter the rest of the program. It is the usual way to write binary operators for a class.

### Both orders

```cpp
friend Vec2 operator*(Vec2 v, double factor) { v *= factor; return v; }
friend Vec2 operator*(double factor, Vec2 v) { v *= factor; return v; }
```

A **member** `operator*(double)` could only ever handle `v * 2.0`, because the left operand of a member is always the object. The other order needs a free function. Both are written, and both work:

```cpp
show("position + wind", position + wind);   // (4, 6)
show("2.0 * wind", 2.0 * wind);             // (6, 8)
show("wind * 0.5", wind * 0.5);             // (1.5, 2)
show("-wind", -wind);                       // (-3, -4)
```

### Compound assignment in place

```cpp
position += wind;
position *= 2.0;

Vec2 a{0.0, 0.0};
(a += wind) += wind;          // chained, because += returns a reference
```

```
after position += wind (4, 6)
after position *= 2.0  (8, 12)
(a += wind) += wind    (6, 8)
```

The compound operators change the object in place and **create no temporary**. That makes them the right tool inside a loop. 12.7 comes back to the cost.

### Prefix and postfix

`++` and `--` come in two forms: `++c` (increase, then give the new value) and `c++` (give the **old** value, then increase). The compiler tells the two functions apart by a **dummy `int` parameter**:

```cpp
Countdown& operator--() {              // prefix
    --value_;
    return *this;
}

Countdown operator--(int) {            // postfix: the int is never used
    Countdown old{*this};              // a copy is needed...
    --value_;
    return old;
}
```

```
  --c gave 2, c is now 2
  c-- gave 3, c is now 2
```

The prefix form changes the object and returns it by reference. The postfix form has to **copy the old state** to return it, so it is the costlier one. That is why you should write `++i` rather than `i++` in a loop whenever you do not need the old value, and why the standard library's iterators are used the same way (chapter 14).

**Code for this lecture**: `12.3MemberOrFreeAndCompoundAssignment/main.cpp`.

---

## 12.4 Output and formatting

In this lecture we teach our class to **print**, the old way and the new way.

### The problem

```cpp
Vec2 wind{3.14159, 4.0};
std::println("{}", wind);              // error: no formatter for Vec2
```

`std::println` knows `int`, `double`, `std::string` and many more. It does not know about a class you just wrote, and cannot guess how to print it. There are two ways to tell it. The first is the classic one, still found in almost all older code.

### The classic way: `operator<<`

```cpp
friend std::ostream& operator<<(std::ostream& out, const Vec2& v) {
    return out << '(' << v.x_ << ", " << v.y_ << ')';
}
```

Output with `<<` takes a `std::ostream` on the **left**, which is not our class, so it **cannot be a member**: it is a free function (here a hidden friend). It returns the stream, so that `std::cout << a << b` chains. With it, `std::cout` works:

```cpp
std::cout << "with operator<<:  " << wind << '\n';
```

```
with operator<<:  (3.14159, 4)
```

That is the form you will meet in older code and tutorials, and the one everything built on streams (logging libraries, for example) expects.

### The modern way: `std::formatter`

For `std::format`, `std::print` and `std::println`, you specialize `std::formatter` for your type. It is boilerplate that you can copy (what it means is chapter 16, templates), with three parts:

```cpp
template <>
struct std::formatter<Vec2> {
    std::formatter<double> number;

    constexpr auto parse(std::format_parse_context& context) {
        return number.parse(context);
    }

    auto format(const Vec2& v, std::format_context& context) const {
        context.advance_to(std::format_to(context.out(), "("));
        context.advance_to(number.format(v.x(), context));
        context.advance_to(std::format_to(context.out(), ", "));
        context.advance_to(number.format(v.y(), context));
        return std::format_to(context.out(), ")");
    }
};
```

- **`std::formatter<Vec2>`** is the type that says "this is how to format a `Vec2`".
- **`parse`** reads what comes after the colon in `{:...}`.
- **`format`** writes the value to the output.

The trick is the member **`std::formatter<double> number`**: instead of inventing a format language, we **hand the spec to the formatter of `double`**, and let it write each coordinate. So everything that works for a `double` works for a `Vec2`, for free:

```cpp
std::println("with std::formatter:  {}", wind);
std::println("with a format spec:   {:.2f}", wind);
std::println("with width:           {:8.1f}", wind);
```

```
with std::formatter:  (3.14159, 4)
with a format spec:   (3.14, 4.00)
with width:           (     3.1,      4.0)
```

And it works with `std::format`, too, to build a string:

```cpp
std::string line{std::format("wind is {:.1f}", wind)};      // wind is (3.1, 4.0)
```

### Which one to write

```
   new code                          the std::formatter specialization: type-checked format strings, and a spec that works
   code that must work with streams  operator<< as well
```

The two are **independent**: one does not provide the other. A class that should print with both `std::cout` and `std::println` needs both, and that is fine: each is a few lines.

**Code for this lecture**: `12.4OutputAndFormatting/main.cpp`.

---

## 12.5 Comparison and the spaceship operator

In this lecture we make our own types comparable, which is what lets them be sorted, searched and used as keys.

### Six operators, or one

A type that can be ordered needs `==`, `!=`, `<`, `<=`, `>` and `>=`. Writing six functions is tedious and error-prone. C++20 replaced them with **one**: the three-way comparison operator **`<=>`**, nicknamed the **spaceship**. It answers "less, equal or greater" in a single call.

```cpp
struct Version {
    int major;
    int minor;
    int patch;

    auto operator<=>(const Version&) const = default;
};
```

`= default` makes the compiler write the comparison for us: it compares the members **in the order they are declared**, `major` first, then `minor`, then `patch`, which is exactly what a version needs. It also writes `operator==`. And from those two, the compiler **derives all six** comparisons.

```cpp
Version older{2, 9, 9};
Version newer{2, 10, 1};

std::println("{} < {}   {}", to_text(older), to_text(newer), older < newer);
std::println("{} == {}  {}", to_text(older), to_text(newer), older == newer);
std::println("{} >= {}  {}", to_text(older), to_text(newer), older >= newer);
```

```
2.9.9 < 2.10.1   true
2.9.9 == 2.10.1  false
2.9.9 >= 2.10.1  false
```

Notice `2.9.9 < 2.10.1`: the numbers are compared one by one, not as text (as text, `"2.9.9" > "2.10.1"`).

### Sorting for free

A type that can be compared with `<` can be sorted by the standard algorithms (chapter 15) with no comparison function at all:

```cpp
std::vector<Version> versions{{1, 4, 0}, {2, 10, 1}, {2, 9, 9}, {1, 4, 3}};
std::ranges::sort(versions);
```

```
sorted: 1.4.0 1.4.3 2.9.9 2.10.1
```

### What `<=>` returns

The result is a small object that says which way the comparison went. For integers it is a `std::strong_ordering`, which you can ask directly:

```cpp
std::strong_ordering ordering{older <=> newer};
std::println("older <=> newer says less: {}, equal: {}", std::is_lt(ordering), std::is_eq(ordering));
```

```
older <=> newer says less: true, equal: false
```

For `double` members it is a **`std::partial_ordering`**, because a `double` can be **NaN** ("not a number"), which is neither less than, equal to nor greater than anything, including itself. "Partial" means that some pairs have no ordering.

### Writing your own comparison

The default is not always right. Suppose two readings should be ordered **by their value only**, ignoring which sensor made them:

```cpp
class Reading {
public:
    std::partial_ordering operator<=>(const Reading& other) const {
        return value_ <=> other.value_;
    }

    bool operator==(const Reading& other) const {
        return value_ == other.value_;
    }
    // ...
};
```

Two things to remember. The **`operator==` is written separately**: the compiler generates it only from a **defaulted** `<=>`, because equality and ordering can mean different things (and cost different amounts), so a hand-written ordering does not imply a hand-written equality. And the two must **agree**: if `a == b` is true, `a < b` and `a > b` must be false.

```
north == east (different sensors, same value): true
north < roof:  true
roof > east:   true
```

### Which one to write

```
   a plain bundle of data, members in the right order          <=> = default
   its own idea of order or equality                           write <=> and ==
   equality only, no sensible order                            write == alone
```

A comparison that is **almost** right is worse than none. For floating-point numbers in particular, remember that `==` after arithmetic is risky (12.7).

**Code for this lecture**: `12.5ComparisonAndSpaceship/main.cpp`.

---

## 12.6 The subscript and call operators

In this lecture we meet two operators that make an object behave like something else: like an **array** (`[]`), and like a **function** (`()`).

### `operator[]`: an object that is indexed

A table of numbers with rows and columns is natural to write as `grid[row, column]`. In C++23 the subscript operator may take **more than one argument**, so it can:

```cpp
class Grid {
public:
    Grid(std::size_t rows, std::size_t columns)
        : rows_{rows}, columns_{columns}, cells_(rows * columns, 0.0) {}

    double& operator[](std::size_t row, std::size_t column) {
        return cells_[row * columns_ + column];
    }

    const double& operator[](std::size_t row, std::size_t column) const {
        return cells_[row * columns_ + column];
    }

private:
    std::size_t rows_;
    std::size_t columns_;
    std::vector<double> cells_;
};
```

The numbers are stored in **one** vector, row after row (the same trick as the pixel buffer in 6.17), and the operator turns a row and a column into the index `row * columns_ + column`. Two things to notice:

- It returns a **reference** (`double&`), not a value. That is what lets you **write** through it: `grid[0, 0] = 1.5;` assigns to the cell itself, not to a copy.
- There are **two versions**, as in 10.5: one for ordinary grids (writable) and a `const` one for grids held through a `const` reference (read-only).

```cpp
Grid grid{2, 3};
grid[0, 0] = 1.5;
grid[1, 2] = 7.0;

const Grid& read_only{grid};
std::println("through a const reference: {}", read_only[1, 2]);
// read_only[1, 2] = 9.0;                 // error: the const overload returns a const reference
```

```
grid[0, 0] = 1.5, grid[0, 1] = 2.5, grid[1, 2] = 7
through a const reference: 7
```

Like the built-in `[]` and `std::vector::operator[]`, this one does **not check** the indices: `grid[5, 5]` would be undefined behaviour. A checked version belongs in a function with a name, `at(row, column)`, which is what 12.7 does.

Before C++23, `operator[]` could only take one argument, and multi-dimensional access used the call operator instead:

```cpp
double& operator()(std::size_t row, std::size_t column);        // grid(0, 1) = 2.5;
```

The `grid(0, 1)` spelling is all over older code, and works in every standard.

### `operator()`: an object you can call

The call operator lets an object be used **like a function**:

```cpp
class Offset {
public:
    explicit Offset(double amount) : amount_{amount} {}

    double operator()(double reading) const {
        return reading + amount_;
    }

private:
    double amount_;
};
```

```cpp
Offset calibrate{1.5};
calibrate(68.0);               // 69.5: it looks like a call to a function, and it is a call to operator()
```

An object like this is a **function object**, or **functor**. What makes it more than a function is that it **remembers things**: the `amount_` was stored when it was built. Standard algorithms accept functors wherever they accept functions:

```cpp
std::vector<double> readings{68.0, 71.5, 69.0};
std::vector<double> calibrated(readings.size());
std::ranges::transform(readings, calibrated.begin(), Offset{1.5});
```

```
calibrated: 69.5 73 70.5
```

The algorithm calls it for each element, and cannot tell it from a function. A functor can also keep state that **changes**:

```cpp
class CountingScale {
public:
    double operator()(double reading) {          // not const: it counts
        ++calls_;
        return reading * factor_;
    }
    int calls() const { return calls_; }
    // ...
};
```

```
CountingScale was called 3 times
```

### You have been using functors since 6.14

A **lambda** is a functor that the compiler writes for you. This lambda becomes, behind the scenes, a class with an `operator()` very much like `Offset`:

```cpp
double amount{1.5};
auto offset_lambda = [amount](double reading) { return reading + amount; };
```

```
the lambda gives 69.5 for 68, the Offset class gives 69.5
```

The captured variable `[amount]` is the `amount_` member, and the body is the body of `operator()`. Use a lambda for a short, one-off function. Write a class with `operator()` when the function object needs a name, several functions of its own, or to be reused (the visitors of 11.11 and the pipeline steps of 12.10 are exactly that).

**Code for this lecture**: `12.6SubscriptAndCallOperators/main.cpp`.

---

## 12.7 The Matrix in context

In this lecture we bring the operators together in one class that you will keep using: a **`Matrix`**, a rectangular grid of numbers with the arithmetic of linear algebra.

The class lives in `matrix.h` (it is a header-only class, so it is easy to copy into another project, which chapters 13 and 16 do). Read it with the previous lectures in mind: every operator in it was introduced in 12.2 to 12.6.

### What it looks like to use

```cpp
Matrix a{{1.0, 2.0, 3.0},
         {4.0, 5.0, 6.0}};                  // 2 x 3
Matrix b{{1.0, 0.0},
         {0.0, 1.0},
         {2.0, 2.0}};                       // 3 x 2

std::println("a (2 x 3):\n{}", a);
std::println("a * b (2 x 2):\n{}", a * b);
```

```
a (2 x 3):
  [   1.0    2.0    3.0 ]
  [   4.0    5.0    6.0 ]

b (3 x 2):
  [   1.0    0.0 ]
  [   0.0    1.0 ]
  [   2.0    2.0 ]

a * b (2 x 2):
  [   7.0    8.0 ]
  [  16.0   17.0 ]
```

A `std::formatter<Matrix>` (12.4) prints one row per line. The initializer syntax comes from a constructor that takes a list of lists. And `a * b` is the **matrix product**, not a cell-by-cell product: each cell of the result is a row of the left matrix multiplied, element by element, by a column of the right one, and the results added. The top-left cell above is `1*1 + 2*0 + 3*2 = 7`.

### Which operators, and where

| Operator | Written as | Why there |
|---|---|---|
| `+=`, `-=`, `*=` (by a number) | members, returning `*this` | they change the matrix: the real work (12.3) |
| `+`, `-`, `*` (by a number, both orders) | hidden friends, built from the compound ones | symmetric binary operators |
| `*` (matrix by matrix) | hidden friend | the matrix product: it needs the shapes to match |
| `[row, column]` | two members, const and not | the C++23 subscript of 12.6 |
| `==` | `friend bool operator==(...) = default;` | compares shape and every cell |
| `transposed()`, `identity(n)` | a named member and a static function | no obvious operator: a **name** is clearer (12.2) |

Notice the last row. A `transposed()` function is clearer than inventing an operator for it, and `Matrix::identity(3)` is a static factory function (10.10). Operators for the things that have an obvious symbol, **names for the rest**.

### The rule of zero again

```cpp
Matrix copy{a};
copy[0, 0] = 99.0;
std::println("after changing the copy: a[0, 0] = {}, copy[0, 0] = {}", a[0, 0], copy[0, 0]);

Matrix moved{std::move(copy)};
std::println("moved has {} x {}", moved.rows(), moved.columns());
```

```
after changing the copy: a[0, 0] = 1, copy[0, 0] = 99
moved has 2 x 3
```

`Matrix` contains **no destructor, no copy constructor, no move operations**. The data lives in a `std::vector`, so the compiler-written versions are exactly right: the rule of zero (10.9), and a good reminder that most of a class's work is operators and ordinary functions.

### Cost: temporaries

Every **binary** operator returns a **new** matrix, so a long expression creates temporaries:

```cpp
Matrix result{a + b + c + d};           // three temporaries
```

Each temporary is a new vector, allocated and freed. When it matters (large matrices, in a loop), build the result in place with the **compound** operators, which allocate nothing:

```cpp
Matrix result{a};
result += b;
result += c;
result += d;
```

The binary operators in `matrix.h` are written the way 12.3 taught: `operator+` takes its left operand **by value** and calls `+=` on it, so the cost is one copy of the left operand and no more. And returning a matrix **by value** is cheap (10.8): the result is built straight in the caller's variable, or moved, never copied.

### Errors

What should `a + b` do when the shapes differ? It cannot return a sensible matrix. The operators **throw an exception**:

```cpp
Matrix wrong{a + b};                    // throws std::invalid_argument: shapes differ
```

(This line is commented out in the program for that reason.) Exceptions are the subject of chapter 13, where you will see how to catch them, and where the project writes **tests** that check the error paths of this very class. For now, read `throw` as "stop here and report the mistake loudly", which is much better than quietly returning nonsense.

### A note on `==` and doubles

`operator==` compares the cells **exactly**. After arithmetic, two numbers that are mathematically equal can differ in the last bits (`0.1 + 0.2 == 0.3` is false for doubles). Our examples use values that are exact in binary, so `2 * a - a == a` is true. For real computations, compare with a **tolerance** (for example `std::abs(x - y) < 1e-9`) in a named function, rather than trust `==`.

**Code for this lecture**: `12.7MatrixInContext/` (`matrix.h`, `main.cpp`).

---

## 12.8 Conversions and `explicit`

In this lecture we deal with the quiet side of operators: the conversions that the compiler performs **without being asked**, and how to stay in control of them.

### The converting constructor

A constructor that can be called with **one argument** is also a **conversion**: it says how to turn that argument into the class. Since 10.3 you have been marking them `explicit`. Here is why it matters.

```cpp
class LooseMeters {
public:
    LooseMeters(double meters) : meters_{meters} {}      // NOT explicit
    // ...
};

void print_length(LooseMeters length);
```

```cpp
print_length(LooseMeters{5.0});
print_length(5.0);          // compiles: a plain number silently becomes a LooseMeters
print_length(true);         // compiles too: a bool becomes 1.0 meter
```

```
  length: 5 m
  length: 5 m
  length: 1 m
```

The second call is merely convenient, the third is nonsense, and **the compiler accepted both** without a word. With `explicit`, they would not compile:

```cpp
class Celsius {
public:
    explicit Celsius(double degrees) : degrees_{degrees} {}
    // ...
};

// print_temperature(21.5);               // error: no implicit conversion from double
print_temperature(Celsius{21.5});         // you must say what you mean
```

### The conversion operator

A **conversion operator** goes the other way: from the class **to** another type. Its name is `operator` followed by the target type, and it has **no return type** written (the type is the name):

```cpp
class Celsius {
public:
    explicit operator Fahrenheit() const;
    // ...
};

Celsius::operator Fahrenheit() const {
    return Fahrenheit{degrees_ * 9.0 / 5.0 + 32.0};
}
```

Marked `explicit`, it is used only when you ask, with `static_cast`:

```cpp
Celsius freezing{0.0};
Fahrenheit f{static_cast<Fahrenheit>(freezing)};
std::println("0 C is {} F", f.degrees());
```

```
0 C is 32 F
```

Without `explicit`, a `Celsius` could turn into a `Fahrenheit` anywhere a `Fahrenheit` was expected, with no sign in the code that a conversion happened. (The two types being different **units** is exactly the kind of thing that must never convert silently.)

### `explicit operator bool`

There is one conversion that is **meant** to be used in conditions: "is this object valid?". Pointers and smart pointers (9.2, 9.10) offer it. You write it as an **`explicit operator bool`**:

```cpp
class MaybeReading {
public:
    explicit operator bool() const { return valid_; }
    // ...
};

MaybeReading nothing;
MaybeReading something{21.5};

if (something) {
    std::println("  something holds {}", something.value());
}
if (!nothing) {
    std::println("  nothing holds nothing");
}
```

```
the explicit operator bool:
  something holds 21.5
  nothing holds nothing
```

Although it is explicit, it works **automatically in conditions**: `if`, `while`, `!`, `&&`, `||` and `?:` all count as a place where a `bool` is **explicitly** wanted. Everywhere else, it does not fire, so a `MaybeReading` can never turn into the number 1 by accident:

```cpp
// double oops{something};                // error: not allowed
// int count{nothing + something};        // error: no arithmetic on a MaybeReading
```

### The rule

```
   one-argument constructor        explicit, unless you can say why the silent conversion is right
   conversion operator              explicit, always (a condition is the only place it should fire alone)
   implicit is right when           the two types ARE the same thing: a text literal IS a std::string
```

If in doubt, `explicit`: the cost is a `static_cast` where you need one, and the gain is that **no conversion in your program can happen without you seeing it**.

**Code for this lecture**: `12.8ConversionsAndExplicit/main.cpp`.

---

## 12.9 User-defined literals

In this lecture we meet a small feature with a big payoff for code about **units**: giving a number a suffix that makes it a value of your own type.

### The idea

How long is `1500.0`? Metres? Kilometres? Millimetres? A bare number does not say, and a mistake of that kind has cost real spacecraft. A **user-defined literal** puts the unit **in the code**:

```cpp
Length without{1500.0};                        // metres? kilometres? who knows

Length road{1.5_km};
Length track{250.0_m};
Length crack{3.5_cm};
```

The type stores everything in one unit (metres), and each literal converts into it:

```cpp
struct Length {
    double meters;
};

constexpr Length operator""_m(long double value) {
    return Length{static_cast<double>(value)};
}

constexpr Length operator""_km(long double value) {
    return Length{static_cast<double>(value) * 1000.0};
}

constexpr Length operator""_cm(long double value) {
    return Length{static_cast<double>(value) / 100.0};
}
```

```
1.5_km   = 1500 m
250.0_m  = 250 m
3.5_cm   = 0.035 m

road + track + crack = 1750.035 m
```

### How it is written

A **literal operator** is a function named `operator""` followed by the suffix:

- The suffix **must start with an underscore** (`_km`). Suffixes without an underscore are reserved for the standard library: `s`, `ms`, `h`, `min`, `i`...
- The parameter is a **`long double`** for a literal with a decimal point (`1.5_km`) and an **`unsigned long long`** for a whole number (`5_km`). Write both overloads if you want both to work:

```cpp
constexpr Length operator""_km(unsigned long long value) {
    return Length{static_cast<double>(value) * 1000.0};
}
```

```
5_km     = 5000 m  (the whole-number overload)
```

- Mark them **`constexpr`**, so the literal also works in a constant expression, and the compiler can check it while compiling:

```cpp
constexpr Length marathon{42.195_km};
static_assert(marathon.meters > 42000.0);
```

- A literal for **text** receives the characters and their count:

```cpp
std::string operator""_tag(const char* text, std::size_t length) {
    return "[" + std::string{text, length} + "]";
}

std::println("{}", "north"_tag);                // [north]
```

### You already use them

The literals from chapter 7 are exactly this mechanism, defined by the standard library:

```cpp
using namespace std::chrono_literals;
auto timeout{250ms};
auto period{2min};
```

```
250ms is 250ms and 2min is 2min
```

They live in a namespace that you bring in with a using directive, which is why the line is there. The type of `250ms` is `std::chrono::milliseconds`, so the unit is part of the **type**, and the compiler refuses to add milliseconds to metres.

### When to use them

```
   good use     units, where a wrong guess is expensive: lengths, masses, durations, money
   poor use     anything whose suffix a reader cannot guess: 5_x, 12_widgets
```

**Code for this lecture**: `12.9UserDefinedLiterals/main.cpp`.

---

## 12.10 Pipe operators

In this lecture we meet the operator that the project is built around, and write a small version of it ourselves.

### You have already used it

In 7.6, the standard library's views were chained with `|`:

```cpp
auto hot_celsius = readings
    | std::views::filter([](int f) { return f > 70; })
    | std::views::transform([](int f) { return (f - 32) * 5.0 / 9.0; });
```

```
readings above 70 F, in Celsius:
  21.7
  27.2
  32.2
```

That `|` is an **overloaded operator**, and the library defines it so that data **flows left to right** through a series of steps, instead of being buried in nested calls:

```
   nested:   border(pad(bold(text("north"))))         read from the inside out
   piped:    text("north") | bold | pad | border      read left to right, in the order things happen
```

The second is much easier to read, and the same idea is used by `ftxui`, the library of the project.

### Building one

We can build the idea in about thirty lines. The thing that flows through the pipeline is a block of text lines, a `Panel`:

```cpp
struct Panel {
    std::vector<std::string> lines;

    Panel() = default;
    explicit Panel(const std::string& text) : lines{text} {}
};
```

Each step is a **decorator**: a function object (12.6) that takes a `Panel` and returns a new, decorated one:

```cpp
struct Bold {
    Panel operator()(Panel panel) const {
        for (std::string& line : panel.lines) {
            line = "*" + line + "*";
        }
        return panel;
    }
};

struct Pad {
    int amount;
    Panel operator()(Panel panel) const { /* surround each line with spaces */ }
};

struct Border {
    Panel operator()(Panel panel) const { /* draw a frame around the lines */ }
};
```

And the **pipe operator itself**, which is four lines:

```cpp
template <typename Decorator>
Panel operator|(Panel panel, Decorator decorator) {
    return decorator(std::move(panel));
}
```

It takes a `Panel` on the left and **any callable** on the right, **calls** the callable with the panel, and **returns the result**. Because the result is a `Panel`, the next `|` can take over. That is all a pipeline is. (The `template` makes the operator accept any decorator type, which is the subject of chapter 16.)

```cpp
print(station | Bold{} | Pad{1} | Border{});
```

```
+-----------------+
| *north station* |
+-----------------+
```

Read it left to right: start with the text, make it bold, pad it, frame it. **The order matters**, as in a pipeline in a shell:

```cpp
print(Panel{"alert"} | Border{} | Bold{});
```

```
*+-----+*
*|alert|*
*+-----+*
```

Here the border went on first, so bold wrapped the border, not the text.

### Precedence

`|` has a **lower** precedence than the arithmetic operators and the comparisons: `a + b | f` means `(a + b) | f`. And it binds **tighter** than `=` and `?:`. When mixing a pipe with other operators, use parentheses: nobody should have to look up the table.

### Where this goes

The project uses exactly this idea, from a library: `text("hello") | bold | border`. In ftxui, a decorator is anything callable that takes an element and returns an element, and the library's `operator|` applies it. That means **you can write your own decorators and use them in the same pipeline**: that is the last part of the project.

**Code for this lecture**: `12.10PipeOperators/main.cpp`.

---

## 12.11 Project: using libraries with vcpkg (classic mode)

Everything you have built so far used **your own code** and the **standard library**. Real programs also use code written by others: libraries for images, networking, compression, text interfaces. You have already met two ways to get one: copying a single header into your project (6.18), and having CMake download it at configure time (6.19). Neither scales to a library with its own dependencies, or one that has to be **compiled**.

That is the job of a **package manager**. This project uses **vcpkg**, Microsoft's package manager for C and C++. It works on Windows, Linux and macOS, with any compiler, and it plugs into CMake. In three parts you will:

```
   12.11   classic mode      install a library by hand with the vcpkg command line, see where it goes, use it from CMake
   12.12   manifest mode     list your project's libraries in a file, and let the build install them
   12.13   a real application: a text-mode dashboard with the library ftxui, and your own decorators for its | operator
```

### What vcpkg is made of

```
   vcpkg                the program you run:  vcpkg install fmt
   ports                recipes: for each library, how to download, build and install it
   triplets             a target description: x64-windows, x64-linux ...  (CPU, operating system, DLL or static)
   installed tree       where the results go: include/, lib/, bin/ and share/ for each triplet
   toolchain file       a CMake file that teaches CMake where to find all of it
```

You do not write recipes. The Microsoft-maintained list has thousands of libraries. You ask for one by name and vcpkg downloads its source, compiles it with **your** compiler, and installs it.

### Step 1: get a vcpkg of your own

**On the course's Linux containers** vcpkg is already there: `VCPKG_ROOT` is set to `/opt/vcpkg`, and `vcpkg version` works. Nothing to do.

**On Windows**, Visual Studio comes with its own copy of vcpkg, and `VCPKG_ROOT` points at it in a Developer PowerShell. But that copy **only works in manifest mode** (12.12). Ask it for a classic install and it refuses:

```
error: Could not locate a manifest (vcpkg.json) above the current working directory.
This vcpkg distribution does not have a classic mode instance.
```

For classic mode you install your own. It takes two commands, once: clone the repository, and build the vcpkg program.

```powershell
git clone https://github.com/microsoft/vcpkg C:\dev\vcpkg
C:\dev\vcpkg\bootstrap-vcpkg.bat -disableMetrics
```

(The folder is up to you. Pick one **without spaces** in the path, and not under `Program Files`. The clone took about 30 seconds here, and the bootstrap 5 seconds. On Linux or macOS, use `./bootstrap-vcpkg.sh`.) Then tell your tools where it lives:

```powershell
$env:VCPKG_ROOT = 'C:\dev\vcpkg'            # for this shell. Set it permanently in the Windows environment settings.
C:\dev\vcpkg\vcpkg.exe version
```

### Step 2: install a library

The library is **{fmt}**, the library that `std::format` and `std::print` were standardized from (7.8). So its notation is familiar, and it has a few extras that the standard version lacks.

```powershell
vcpkg install fmt
```

```
Computing installation plan...
The following packages will be built and installed:
    fmt:x64-windows@12.2.0
...
fmt provides CMake targets:
  find_package(fmt CONFIG REQUIRED)
  target_link_libraries(main PRIVATE fmt::fmt)
...
All requested installations completed successfully in: 16 s
```

Read the end of the output: vcpkg **tells you exactly the two CMake lines to use it**. And look at `x64-windows`: that is the **triplet** (64-bit Windows, dynamic libraries). The one on Linux is `x64-linux` (64-bit Linux, static libraries). Other triplets exist, such as `x64-windows-static`, and you pick one with `vcpkg install fmt:x64-windows-static`.

### Step 3: where did it go?

```powershell
vcpkg list
```

```
fmt:x64-linux                    12.2.0#1    {fmt} is an open-source formatting library provi...
vcpkg-cmake-config:x64-linux     2026-07-21
vcpkg-cmake:x64-linux            2025-08-07
```

(The two extra lines are helper packages that vcpkg's own build scripts need.) And on disk:

```
   C:\dev\vcpkg\installed\
   ├── vcpkg\                    bookkeeping: what is installed
   └── x64-windows\              one folder per triplet
       ├── include\fmt\...       the headers
       ├── lib\                  fmt.lib (and fmt-c.lib): what the linker needs
       ├── bin\                  fmt.dll: what the running program needs
       ├── debug\                the same again, built in Debug mode
       └── share\fmt\            fmt-config.cmake: what find_package reads
```

On Linux it is the same shape under `/opt/vcpkg/installed/x64-linux`, with `libfmt.a` instead of `fmt.lib` and `fmt.dll`. Two commands you will want: `vcpkg search <word>` finds a library, and `vcpkg remove fmt` takes one out.

Libraries live in **one shared place**, **outside every project**. That is classic mode: install once, use from any project on the machine.

### Step 4: use it from CMake

The project (`12.11ProjectVcpkgClassicMode`) is a small program that prints a table, a vector, a coloured line:

```cpp
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

fmt::print("{:<10} | {:>8} | {:^8}\n", "sensor", "reading", "status");
fmt::print("\nreadings: {}\n", readings);
fmt::print("joined:   {}\n", fmt::join(readings, " / "));
fmt::print(fg(fmt::color::orange) | fmt::emphasis::bold, "warm day: {} F\n", readings[3]);
```

Its `CMakeLists.txt` has two new lines, the same two that vcpkg printed:

```cmake
find_package(fmt CONFIG REQUIRED)
target_link_libraries(rooster PRIVATE fmt::fmt)
```

- **`find_package(fmt CONFIG REQUIRED)`** looks for the package: `CONFIG` means "read the `fmt-config.cmake` file the library installed", `REQUIRED` means "stop with an error if it is missing".
- **`fmt::fmt`** is an **imported target**: linking against it brings along the include folder, the library file and any compile options, without you listing any of them.

But CMake does not know where vcpkg put things. You tell it with vcpkg's **toolchain file**, on the command line, when you configure:

```powershell
cmake -S . -B build -G Ninja "-DCMAKE_TOOLCHAIN_FILE=$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build build
.\build\rooster.exe
```

```
sensor     |  reading |  status
north      |     68.0 |    ok
east       |     71.5 |    ok

readings: [68, 71.5, 69, 72, 70.5]
joined:   68 / 71.5 / 69 / 72 / 70.5
warm day: 72 F
5 readings, first 68
```

That one option is all the connection between CMake and vcpkg. (The "warm day" line is orange and bold in a terminal that shows colours.) Notice that your `CMakeLists.txt` contains **no path to vcpkg**: the project works on any machine where vcpkg is installed anywhere.

On Linux the commands are the same, with `$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake` and `./build/rooster`.

### Gotchas

- **The editor shows red squiggles** on `#include <fmt/color.h>` until your IDE has run the CMake configure with the toolchain file: before that, it does not know where the headers are. Configure first, then reload.
- **The build type matters on Windows.** A Ninja build with no `CMAKE_BUILD_TYPE` counts as a Debug build, and vcpkg's toolchain then links the **debug** libraries: we saw `fmtd.dll`, the debug one, copied next to the program. Pass `-DCMAKE_BUILD_TYPE=Release` (as above) for the release ones.
- **DLLs next to the program.** On Windows with the default dynamic triplet, the program needs `fmt.dll` at run time. vcpkg's toolchain file copies it beside your executable for you. Without the toolchain file, you would get a "DLL not found" error (7.14).
- **Everything is built from source by your compiler**, so libraries match your toolchain. That is why the first install takes a while, and why a library installed for one compiler is not shared with another: the course containers each have their own.
- **Classic mode is a shared pool.** Two projects that need different versions of the same library will fight over it. Manifest mode, next, solves that.

**Code for this project**: `12.11ProjectVcpkgClassicMode/` (`main.cpp`, `CMakeLists.txt`, and `build-windows.ps1` and `build-linux.sh`, which run every command of this section).

---

## 12.12 Project: manifest mode, and ftxui

Classic mode has a flaw for anything you share: nothing in the **project** says what it needs. Someone who clones it has to know which libraries to install first. **Manifest mode** puts the list in a file **inside the project**, and the build installs it.

### The manifest

`vcpkg.json` sits next to `CMakeLists.txt`:

```json
{
  "name": "weather-panel",
  "version": "0.1.0",
  "dependencies": [
    "ftxui"
  ],
  "builtin-baseline": "30ef65cad98f08e7197c9a1656fbd871bcb72f2d"
}
```

- **`dependencies`** is the list of libraries the project needs.
- **`builtin-baseline`** pins **which commit** of vcpkg's list of libraries to take versions from, so that everybody who builds the project gets the same versions. More on it below.

The library is **ftxui**, a library for text-mode user interfaces: boxes, colours, gauges and layouts drawn in the terminal. Its whole interface is built on the `|` operator of 12.10.

### Using it: nothing to install

```powershell
cmake --preset default
cmake --build --preset default
.\build\rooster.exe
```

That is the whole procedure. When CMake configures with vcpkg's toolchain file, vcpkg **reads `vcpkg.json`**, downloads ftxui, **builds it**, and installs it into a folder inside **this project's build folder** (`build/vcpkg_installed`). The first configure took about 25 seconds here (15 of them compiling ftxui), and the output shows it:

```
-- Running vcpkg install
Installing 1/3 vcpkg-cmake-config:x64-windows@2026-07-21...
Installing 2/3 vcpkg-cmake:x64-windows@2025-08-07...
Installing 3/3 ftxui:x64-windows@7.0.3...
Building ftxui:x64-windows@7.0.3...
-- Note: ftxui only supports static library linkage. Building static library.
...
-- Configuring done (24.2s)
```

After that, vcpkg's **binary cache** keeps the compiled package, so the next project that needs the same library, built the same way, installs it in a fraction of a second.

### Presets: keeping the command line short

The options CMake needs (the generator, the toolchain file, the build type) would make a long command. `CMakePresets.json` stores them under a name:

```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "default",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "toolchainFile": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake",
      "cacheVariables": { "CMAKE_BUILD_TYPE": "Release" }
    }
  ],
  "buildPresets": [ { "name": "default", "configurePreset": "default" } ]
}
```

`cmake --preset default` is then the whole configure command. The toolchain file comes from the **environment variable `VCPKG_ROOT`**, so the same file works for the Visual Studio copy, your own clone and the containers, with no path inside it. (Visual Studio and VS Code read `CMakePresets.json` too, so the same preset works from the IDE.)

### Using it from CMake

```cmake
find_package(ftxui CONFIG REQUIRED)

add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE ftxui::screen ftxui::dom ftxui::component)
```

ftxui is split into three libraries, each its own target: **`screen`** (the grid of coloured character cells that gets drawn), **`dom`** (the layout elements: `text`, `hbox`, `vbox`, `border`, `gauge`...) and **`component`** (interactive pieces such as buttons and menus, not used in this folder, but linked so that you can).

### The program

```cpp
Element panel = vbox({
    text("Weather station") | bold | center,
    separator(),
    hbox({text("north  "), text("21.5 C") | color(Color::Green)}),
    hbox({text("east   "), text("19.0 C") | color(Color::Blue)}),
    hbox({text("roof   "), text("33.5 C") | color(Color::Red)}),
}) | border;

auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(panel));
ftxui::Render(screen, panel);
screen.Print();
```

An ftxui screen is described as a **tree of elements**, built from the inside out: text, joined by `hbox` (a row) and `vbox` (a column), decorated with `|`. `Render` fills a `Screen` (a grid of character cells) from the tree, and `Print` writes it to the terminal. In a terminal that understands colours and UTF-8, you see:

```
╭───────────────╮
│Weather station│
├───────────────┤
│north  21.5 C  │
│east   19.0 C  │
│roof   33.5 C  │
╰───────────────╯
```

with the heading in bold, and the three temperatures in green, blue and red. And every line above that has a `|` is the overloaded operator from 12.10: `text("21.5 C") | color(Color::Green)` wraps the text in a colour, and `... | border` frames the whole thing.

(**Windows consoles**: the box characters are UTF-8. Windows Terminal shows them correctly. If you see strange symbols in an older console window, switch it to UTF-8 with `chcp 65001`.)

### Where did the libraries go?

```
   build/vcpkg_installed/
   ├── vcpkg/
   └── x64-windows/lib/        ftxui-component.lib, ftxui-dom.lib, ftxui-screen.lib
```

Inside the **project's** build folder, not in vcpkg's own folder. Delete `build` and everything is gone; nothing is shared with other projects, which is what makes each project **reproducible**.

### Baselines, and the three kinds of vcpkg

The `builtin-baseline` is where vcpkg environments differ, and the differences are worth knowing.

- **The Visual Studio copy of vcpkg has no list of libraries of its own.** Without a baseline in the manifest, it stops:

  ```
  error: this vcpkg instance requires a manifest with a specified baseline in order to interact with ports.
  Please add 'builtin-baseline' to the manifest ...
  ```

  With one, it fetches that commit's list from GitHub.
- **Your own clone, and the course containers, have the list on disk**, so they work without a baseline, and use whatever commit they are at.
- **The course containers keep a shallow clone**: only one commit of vcpkg's history, `30ef65ca…` (31 August 2026). A baseline has to be a commit that vcpkg can find, so the one in this folder is **that commit**: it exists in the containers, in a full clone, and on GitHub, and it therefore works in every environment of the course. Pick a newer one in a container, and vcpkg complains that it cannot `git show` the baseline.

For **your own projects**, you do not copy a hash by hand. Ask vcpkg to write the current one:

```powershell
vcpkg x-update-baseline --add-initial-baseline
```

It adds `"builtin-baseline"` to your `vcpkg.json`, with the newest commit. Commit that file: from then on, everyone who builds the project gets the same versions, today and in a year.

> **If vcpkg fails with `SSL certificate problem: unable to get local issuer certificate`**: vcpkg uses your `git` to fetch the list, and your git does not trust the certificate (a corporate proxy, or an old git on Windows). On Windows, `git config --global http.sslBackend schannel` makes git use the Windows certificate store. Do not turn certificate checking off.

**Code for this project**: `12.12ProjectVcpkgManifestMode/` (`vcpkg.json`, `CMakePresets.json`, `CMakeLists.txt`, `main.cpp`, and the scripts `build-windows.ps1` and `build-linux.sh`).

---

## 12.13 Project: the ftxui dashboard

Now a real small application: a **weather dashboard** in the terminal, with one row per sensor: the name, a gauge showing where the reading falls on a 0 to 40 degree scale, and the value with a status badge, all coloured by how warm it is. The code is in `12.13ProjectFtxuiDashboard`, with the same `vcpkg.json`, `CMakePresets.json` and commands as 12.12.

```
╭ Weather station ───────────────────────────────╮
│north   ████████████▉           [OK]   21.5 C   │
│east    ████▊                   [COLD]    8.0 C │
│roof    ████████████████████    [HOT]   33.5 C  │
│cellar  ████████▎               [OK]   14.0 C   │
├────────────────────────────────────────────────┤
│              4 sensors reporting               │
╰────────────────────────────────────────────────╯
```

(In a terminal the bars and values are green, blue or red. `COLD` is under 10 degrees, `HOT` is over 30.)

### The row

```cpp
Element row(const SensorReading& reading) {
    return hbox({
        text(reading.name) | size(WIDTH, EQUAL, 8),
        gauge(static_cast<float>(reading.celsius / 40.0)) | size(WIDTH, EQUAL, 24) | level_color(reading.celsius),
        text(std::format(" {:5.1f} C ", reading.celsius)) | level_color(reading.celsius) | badge(status_for(reading.celsius)),
    });
}
```

Read it as a pipeline per cell: **text, fixed to 8 columns**; **a gauge, fixed to 24 columns, coloured by level**; **a text, coloured by level, with a badge in front**. `size(WIDTH, EQUAL, 8)` is a decorator that fixes a width, and `gauge` draws a bar from a number between 0 and 1.

### Your own decorators

Two of the decorators in that row are **not from ftxui**: `level_color` and `badge`. They are in `decorators.h`, and they are the part of the project that is yours:

```cpp
inline ftxui::Decorator badge(std::string label) {
    return [label = std::move(label)](ftxui::Element inner) {
        return ftxui::hbox({
            ftxui::text("[" + label + "] ") | ftxui::bold,
            std::move(inner),
        });
    };
}
```

Here is why this works. ftxui defines `Element operator|(Element, Decorator)`, where a **`Decorator`** is simply a callable that takes an element and returns an element (a `std::function<Element(Element)>`). A function that **returns a lambda of that shape** is therefore a decorator, and it plugs into the pipe exactly like `bold` and `border`:

```cpp
text("21.5 C") | level_color(21.5) | badge("OK")
```

You are using the library's overloaded operator with a step you wrote, which is exactly the point of 12.10: the operator only needs "something callable".

```cpp
inline ftxui::Decorator level_color(double celsius) {
    ftxui::Color chosen{ftxui::Color::Green};
    if (celsius < 10.0) {
        chosen = ftxui::Color::Blue;
    }
    else if (celsius > 30.0) {
        chosen = ftxui::Color::Red;
    }
    return ftxui::color(chosen);
}
```

`level_color` chooses a colour from the reading, and **returns ftxui's own `color(...)` decorator**: one decorator built from another.

### The whole window

```cpp
Element dashboard = window(
    text(" Weather station ") | bold,
    vbox({
        vbox(std::move(rows)),
        separator(),
        text(std::format("{} sensors reporting", readings.size())) | center,
    })
);

auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(dashboard));
ftxui::Render(screen, dashboard);
screen.Print();
```

The rows are collected into a `std::vector<Element>` with an ordinary loop, and `vbox` accepts the vector. `window` draws a framed box with a title. Nothing here is new beyond what you have seen: an element tree, decorated with `|`.

### Try it

- **Add a decorator of your own**: for instance `underlined_if(bool)`, which returns `ftxui::underlined` when its condition is true and a decorator that does nothing otherwise.
- **Add a sensor** to the vector, and a threshold for a new status.
- **Look at the ftxui documentation** for `ScreenInteractive`: the `component` library is already linked, and the same layouts can become a dashboard that refreshes by itself.

### What you have learned

```
   a package manager       vcpkg: install a library by name, built with YOUR compiler
   classic mode            one shared install on the machine, for experiments
   manifest mode           vcpkg.json in the project: the project lists what it needs
   the toolchain file      the one line that connects CMake to vcpkg
   a baseline              pins the versions, so a build is reproducible
   an overloaded |         the same operator you wrote in 12.10, in a library you did not write
```

**Code for this project**: `12.13ProjectFtxuiDashboard/` (`main.cpp`, `decorators.h`, `vcpkg.json`, `CMakePresets.json`, `CMakeLists.txt`, and the scripts).

---

## 12.14 Assignment

Eight small types for the weather station, one operator idea each: arithmetic operators, `std::formatter`, the spaceship operator, the multi-argument subscript, the call operator, explicit conversions, user-defined literals, and a pipe. `main.cpp` has the eight exercises, each with its statement and a sample run in a comment; a small `Wind` struct is provided for exercise 2. You write each type above `main()` and the lines that use it in `main()` under its heading. `main_solution.cpp` solves all eight. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `Vec2` | compound `+=` as a member, hidden-friend `+`, unary `-`, `*` in both orders |
| 2 | `std::formatter<Wind>` | a formatter that reuses `std::formatter<double>`, so one format spec applies to both numbers |
| 3 | `Version` | a defaulted `<=>`, `std::ranges::sort`, comparing with `>` |
| 4 | `Grid` | the C++23 `operator[](row, column)`, const and non-const |
| 5 | `Clamp` | a function object with `operator()`, applied with `std::ranges::transform` |
| 6 | `Percent` | an `explicit` constructor, `explicit operator double`, `explicit operator bool` used in an `if` |
| 7 | `Mass` | the literals `_kg` and `_g`, a free `operator+` |
| 8 | `Series` | function objects as pipeline steps, and a template `operator|` |

The vcpkg project has no exercise of its own: the exercise is to do it, in each environment you have, with the scripts of each folder as an answer key.

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole chapter, including two on vcpkg and one on baselines.

After this chapter the student can give their own types the operators that fit them, choose between a member and a free function, make a class printable with `std::println`, comparable with one line, indexable and callable, and can pull a third-party library into a project with vcpkg and CMake. The next chapter deals with **what happens when something goes wrong**: exceptions, and a first look at contracts, which is where the `Matrix` class and its error paths come back.
