# First Steps

In this lecture, we are officially starting our C++ journey. You will write
your first program, see 


---

## 3.2 Your first C++ program

### Comments: two flavors

```cpp
// This is a one-line comment: the compiler ignores everything after //.

/*
    This is a block comment. It can span multiple lines and is handy
    for longer explanations.
*/
```

A `//` comment runs to the end of the line. A `/* ... */` comment can
span several lines - useful for a longer explanation, or for temporarily
"commenting out" a whole block of code without deleting it.

### `std::cout` - the traditional way to print

```cpp
std::cout << "Hello, C++!\n";
std::cout << "This is the classic way to print output.\n";
```

```
   std::cout  <<  "text"  <<  "more text"  <<  '\n'
              │              │                 │
              └──────────────┴─────────────────┘
              each << chains another piece onto the stream
```

`std::cout` lives in `<iostream>`. You chain values onto it with `<<`,
and you are responsible for adding `'\n'` (or `std::endl`, though this
course avoids it - see the callout below) yourself, on every line.

`std::cout` is what most existing C++ code, tutorials, and documentation
still use, which is why it comes first - so you recognize it when you
see it in the wild - even though the course moves off it once `<print>`
shows up.

### `std::println` - the modern way (C++23)

```cpp
std::println("Hello, C++!");
std::println("This is the modern way to print output.");
```

```
   std::cout                                std::println
   ──────────                               ────────────
   chains values with <<                    one call, a format string
   you add '\n' yourself                    newline added for you
   no built-in placeholder syntax           {}-style formatting, like
                                            Python or Rust
```

`std::println` needs `#include <print>`. Side by side, printing a name
and an age looks like this:

```cpp
std::string name{"Ada"};
int age{28};

std::cout << name << " is " << age << " years old.\n";
std::println("{} is {} years old.", name, age);
```

Both lines print the same thing. From this point in the course onward,
`std::print`/`std::println` is the default - `std::cout` only reappears
when a lecture is specifically contrasting the two, or reading input
(there is no `<print>`-family input function; see 3.4).

> Never use `std::endl`. It does what `'\n'` does, plus an extra
> performance-costing stream flush you almost never need. Use `'\n'`
> with `std::cout`, or let `std::println` add the newline for you.

### Two kinds of mistakes

```
   COMPILE-TIME error                     RUN-TIME error
   ───────────────────                    ───────────────
   std::printline("...")                  int total{7 / 0};
        │                                      │
        ▼                                      ▼
   caught before the program              compiles fine - crashes or
   ever runs. The compiler can't          misbehaves only once this
   find a function by that name.          line actually executes.
```

A typo'd function name (`std::printline` instead of `std::println`) is
caught by the compiler - it never finds a matching declaration, so the
build fails before the program exists as a runnable thing. A division by
zero on `int`s compiles without complaint; the mistake only shows up
once that exact line executes. The compiler only catches what it can
reason about statically - it cannot see that `7 / 0` will actually run.

---

## 3.3 Function basics

A function packages a piece of work under a name, so you can ask for the
answer instead of writing the steps out again everywhere you need them.

```cpp
int add_numbers(int first, int second) {
    int result{first + second};
    return result;
}
```

```
   int   add_numbers   ( int first, int second )   {  ...  return result; }
    │         │                  │                          │
    │         │                  │                          └── the value handed back
    │         │                  └── parameters - inputs this function needs
    │         └── name - how you call it
    └── return type - the type of value it hands back
```

### Calling it

```cpp
int sum{add_numbers(25, 7)};
std::println("Sum: {}", sum);
```

```
   add_numbers(25, 7)
        │
        ▼
   first = 25, second = 7  →  result = 32  →  return 32
        │
        ▼
   sum = 32
```

### A function call is itself a value

You do not have to store the result in a variable first - a call can sit
directly wherever a value is expected, including inside a format
argument:

```cpp
std::println("Sum: {}", add_numbers(3, 42));
```

```
   std::println("Sum: {}", add_numbers(3, 42))
                                  │
                                  ▼
                          runs first, produces 45
                                  │
                                  ▼
                          {} is filled with 45
```

This is worth pausing on: `add_numbers(3, 42)` is not a statement on its
own here, it is an **expression** - something that evaluates to a value -
exactly like `3 + 42` would be. Anywhere C++ expects a value, a function
call that produces the right type of value is welcome.

---

## 3.4 Reading input

Everything printed so far has been a literal baked into the source code.
Real programs need to read what the user actually typed.

### Why input still uses `std::cin`, not `<print>`

`<print>` (C++23) only standardized formatted **output**. There is no
`<print>`-family equivalent for input, so reading a value still goes
through the `<iostream>` facilities - `std::cin` and `std::getline` -
even in code that uses `std::println` for everything it prints.

```
   OUTPUT                                  INPUT
   ──────                                  ─────
   std::cout   <<  value                   std::cin  >>  variable
   std::print / std::println("...")        std::getline(std::cin, str)
   (both have a C++23 modern option)        (no <print>-family equivalent -
                                            still <iostream>, either way)
```

### Reading a full line vs. reading one token

```cpp
std::string full_name{};
std::getline(std::cin, full_name);

int age{};
std::cin >> age;
```

```
   std::getline(std::cin, full_name)
        reads an ENTIRE line, spaces included, up to the next '\n'
        → "Ada Lovelace" stays "Ada Lovelace", not just "Ada"

   std::cin >> age
        reads ONE whitespace-separated token, converts it to the
        type on the left (here, int)
```

`std::getline` is the right tool when the input might contain spaces (a
full name, a sentence). Plain `std::cin >>` stops at the first
whitespace, which would truncate "Ada Lovelace" down to just "Ada".

### Putting it together

```cpp
std::println("Please type in your full name and age:");

std::string full_name{};
std::getline(std::cin, full_name);

int age{};
std::cin >> age;

std::println("Hello {}, you are {} years old!", full_name, age);
```

```
   user types:   Ada Lovelace <Enter>
                 28 <Enter>

   full_name ◄── "Ada Lovelace"   (the whole line)
   age       ◄── 28               (one token, converted to int)

   prints:  Hello Ada Lovelace, you are 28 years old!
```

Both `full_name` and `age` are brace-initialized to an empty/zero value
before being read into - a habit that carries forward from here on:
every declaration gets a `{}`, even one that is about to be overwritten
by the very next line.
