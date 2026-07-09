---
marp: true
theme: masterclass
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# 3.2 Your First Program

## The C++ 20/23/26 Masterclass

---

*Chapter 3 / First Steps*

## The running example

Throughout this chapter we build **one small program**: a personal profile
that greets you, asks a few questions, makes decisions, and - by the end -
remembers your friends between runs.

- Nothing fancy on purpose
- One idea added per lecture, on top of the last
- The same excuse to meet every foundational building block

---

*3.2 / Setup*

## Before we type anything

<div class="shot" data-label="Screenshot: empty lecture folder open in Visual Studio / Qt Creator"></div>

Every lecture folder has its own `CMakeLists.txt`, already scaffolded.
Open the folder, don't create a new project by hand.

---

*3.2 / Hello, C++*

## The smallest real program

```cpp
#include <print>

int main() {

    std::println("Hello there!");
    std::println("Welcome to your very first C++ program.");

    return 0;
}
```

---

*3.2 / Line by line*

## What's actually happening

| Line | What it does |
|---|---|
| `#include <print>` | pulls in `std::println` |
| `int main()` | every C++ program starts here |
| `std::println(...)` | prints text, adds the newline for you |
| `return 0;` | tells the OS the program finished successfully |

---

*3.2 / Run it*

## Build and run

Same three commands every lecture in this course:

```sh
cmake -B build -G Ninja .
cmake --build build
./build/rooster
```

---

*3.2 / Run it*

## What you should see

<div class="shot" data-label="Screenshot: terminal output — Hello there! / Welcome to your very first C++ program."></div>

---

*3.2 / Comments*

## Two kinds of comments

```cpp
// A one-line comment - the compiler ignores everything after //

/*
   A block comment.
   Can span multiple lines - handy for a longer explanation.
*/
```

<div class="callout"><strong>Rule of thumb:</strong> a comment earns its place by explaining <em>why</em>, not by narrating what the code obviously already says.</div>

---

<!-- _class: lead -->

# Next: 3.3
## Statements and Functions
