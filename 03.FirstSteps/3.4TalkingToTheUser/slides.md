---
marp: true
theme: masterclass
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# 3.4 Talking to the User

## Input, and doing something with it

---

*3.4 / Reading a line*

## Reading input

`std::print` sends text to the console.
`std::cin` / `std::getline` read text back from it.

```cpp
std::string name;
std::print("What is your name? ");
std::getline(std::cin, name); // reads a full line, including spaces
```

---

*3.4 / Reading a number*

## `>>` vs. `getline`

```cpp
int age{};
std::print("How old are you? ");
std::cin >> age;
```

`>>` reads a single value and **stops at whitespace** - different from
`getline`, which reads the whole line, spaces included.

---

*3.4 / The payoff*

## It's not just echoing back

Reading input only gets interesting once the program **does something**
with it.

```cpp
int birthYear{};
std::print("What year were you born? ");
std::cin >> birthYear;

int turns100In = birthYear + 100;
std::println("You'll turn 100 in the year {}.", turns100In);
```

---

*3.4 / Full program*

## Where we are now

```cpp
std::print("What is your name? ");
std::getline(std::cin, name);

std::print("How old are you? ");
std::cin >> age;

std::print("What year were you born? ");
std::cin >> birthYear;

greetPerson(name);
std::println("You are {} years old.", age);

int turns100In = birthYear + 100;
std::println("You'll turn 100 in the year {}.", turns100In);
```

---

*3.4 / See it run*

<div class="shot tall" data-label="Screenshot: terminal — prompts answered, turns-100 output"></div>

---

*3.4 / Debugging input*

## Debugging a read

You can't step **into** `std::cin >> age` to watch it read - it's atomic
as far as the debugger sees it.

<div class="callout">The pattern: breakpoint on the line <strong>after</strong> the read, step over the read itself, then inspect the variable that just got filled in.</div>

<div class="shot" data-label="Screenshot: IDE debugger stopped after getline(std::cin, name), Locals showing name populated"></div>

---

<!-- _class: lead -->

# Next: 3.5
## Making Decisions
