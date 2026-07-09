---
marp: true
theme: masterclass
paginate: true
---

<!-- _class: lead -->
# 3.3 Statements and Functions

---

## Statements

Each instruction we give the computer is a **statement**.

```cpp
greetPerson("Ada");
greetPerson("Grace");
greetPerson("Alan");
```

Three statements, executed top to bottom.

---

## A function

A named, reusable block of statements.

```cpp
void greetPerson(std::string name) {
    std::println("Hello, {}!", name);
}
```

Call it as many times as you like, with different input each time.

---

## Putting it together

```cpp
#include <print>
#include <string>

void greetPerson(std::string name) {
    std::println("Hello, {}!", name);
}

int main() {
    greetPerson("Ada");
    greetPerson("Grace");
    greetPerson("Alan");

    return 0;
}
```

---

## Two kinds of errors

**Compile-time error** - the program won't even build.

```cpp
greetPersonn("Ada"); // typo: no such function
```

**Runtime error** - it builds, but breaks while running.

```cpp
int trouble = numerator / 0; // compiles fine, crashes when run
```

---

<!-- _class: lead -->
# Next: 3.4
## Talking to the User
