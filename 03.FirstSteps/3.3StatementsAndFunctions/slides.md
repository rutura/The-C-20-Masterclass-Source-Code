---
marp: true
theme: masterclass
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# 3.3 Statements and Functions

## Building blocks, not syntax trivia

---

*3.3 / Statements*

## Statements

Each instruction we give the computer is a **statement** - executed top
to bottom, one after another.

```cpp
greetPerson("Ada");
greetPerson("Grace");
greetPerson("Alan");
```

Three statements. Same function, three different inputs.

---

*3.3 / Functions*

## A function

A named, reusable block of statements - write the logic once, call it
as many times as you like.

```cpp
void greetPerson(std::string name) {
    std::println("Hello, {}!", name);
}
```

`name` is a **parameter** - a placeholder filled in by whoever calls it.

---

*3.3 / Putting it together*

## The whole program

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

*3.3 / Two kinds of errors*

## Compile-time vs. runtime

<div class="cols">
<div>

**Compile-time error**
The program won't even build.

```cpp
greetPersonn("Ada");
// typo: no such function
```

</div>
<div>

**Runtime error**
It builds, but breaks while running.

```cpp
int trouble = numerator / 0;
// compiles fine, crashes when run
```

</div>
</div>

---

*3.3 / Debugging habit*

## Start the debugging habit now

<div class="callout">Even here - before there's any input to read - breakpoint the first line inside <code>greetPerson</code> and look at what <code>name</code> holds. Get comfortable pausing a program and inspecting a value <strong>before</strong> it gets complicated.</div>

<div class="shot" data-label="Screenshot: breakpoint set on greetPerson's std::println line, Locals panel showing name"></div>

---

<!-- _class: lead -->

# Next: 3.4
## Talking to the User
