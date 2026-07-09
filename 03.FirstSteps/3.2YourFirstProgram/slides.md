---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# Your First Program

## The C++ 20/23/26 Masterclass

---

*First Steps With C++*

**What We Do**: .

- Entry Point
- Build and Run on The Command Line
- Output to the Screen
- Debugging through Qt Creator and Visual Studio (IDE)

---

*The Files*

- `CMakeLists.txt` - the build instructions for CMake, which we use to compile and run our program
- `main.cpp` - the main program file, where we write our code

---

*Main.cpp*

## The Entry Point

```cpp
#include <print>

int main() {

    std::println("Hello there!");
    std::println("Welcome to your very first C++ program.");

    return 0;
}
```

---

*CMakeLists.txt*

## The Build Instructions

```cmake
cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(rooster main.cpp)

# For multi-file projects with headers and separate .cpp files
# add_executable(rooster main.cpp dog.cpp dog.h cat.cpp cat.h)
```


---

*Run it*

## Build and run

Same three commands every lecture in this course:

```sh
cmake -B build -G Ninja .
cmake --build build
./build/rooster
```

---

*Run it*

## Run the Executable

```sh
build/rooster
```

---

*Comments*

## Two kinds of comments

```cpp
// A one-line comment - the compiler ignores everything after //

/*
   A block comment.
   Can span multiple lines - handy for a longer explanation.
*/
```

<div class="callout"><strong>Rule of thumb:</strong> a comment earns its place by explaining <em>why</em>, not by narrating what the code obviously already says.</div>