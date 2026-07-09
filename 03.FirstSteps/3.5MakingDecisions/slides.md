---
marp: true
theme: masterclass
paginate: true
---

<!-- _class: lead -->
# 3.5 Making Decisions

---

## if / else

Lets the program follow a different path depending on a condition.

```cpp
if (age >= 18) {
    std::println("You are an adult.");
} else {
    std::println("You are a minor.");
}
```

---

## Comparisons between two variables

Comparisons aren't just for one variable against a fixed number - they
work between two variables too.

```cpp
if (age == friendAge) {
    std::println("{} and {} are the same age.", name, friendName);
} else if (age < friendAge) {
    std::println("{} is younger than {}.", name, friendName);
} else {
    std::println("{} is older than {}.", name, friendName);
}
```

---

## The comparison operators used here

| Operator | Meaning |
|---|---|
| `==` | equal to |
| `<` | less than |
| `>=` | greater than or equal to |

Same operators, applied where they're actually useful - not memorized as
an isolated list.

---

## A gotcha: leftover newline

```cpp
std::cin >> age;
std::cin.ignore(); // discard the leftover newline

std::getline(std::cin, friendName); // otherwise this reads an empty line
```

`std::cin >>` leaves the `\n` you pressed sitting in the input buffer.

---

<!-- _class: lead -->
# Next: 3.6
## Doing It Many Times
