---
marp: true
theme: masterclass
paginate: true
---

<!-- _class: lead -->
# 3.4 Talking to the User

---

## Reading input

`std::print` sends text to the console.
`std::cin` / `std::getline` read text back from it.

```cpp
std::string name;
std::print("What is your name? ");
std::getline(std::cin, name); // reads a full line, including spaces
```

---

## Reading a number

```cpp
int age{};
std::print("How old are you? ");
std::cin >> age;
```

`>>` reads a single value (stops at whitespace) - different from
`getline`, which reads the whole line.

---

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

## Full program so far

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

<!-- _class: lead -->
# Next: 3.5
## Making Decisions
