---
marp: true
theme: masterclass
paginate: true
---

<!-- _class: lead -->
# 3.2 Your First Program

---

## What we're building

Throughout this chapter, one running example: a small **personal profile**
program.

By the end of the chapter it:
- greets you by name
- asks a few questions
- makes decisions
- remembers your friends between runs

Today: just get something on the screen.

---

## Hello, C++

```cpp
#include <print>

int main() {
    std::println("Hello there!");
    std::println("Welcome to your very first C++ program.");

    return 0;
}
```

---

## What's going on here

- `#include <print>` - pulls in `std::println`
- `int main()` - every C++ program starts here
- `std::println(...)` - prints text, adds a newline for you
- `return 0;` - tells the OS the program finished successfully

---

## Comments

```cpp
// A one-line comment - the compiler ignores everything after //

/*
   A block comment.
   Can span multiple lines.
*/
```

Use comments to explain **why**, not to narrate every line.

---

<!-- _class: lead -->
# Next: 3.3
## Statements and Functions
