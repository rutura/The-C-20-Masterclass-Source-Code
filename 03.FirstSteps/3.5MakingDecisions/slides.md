---
marp: true
theme: editorial
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# Making Decisions

## Branching on what the user told us

---

*if / else*

## Following a different path

```cpp
if (age >= 18) {
    std::println("You are an adult.");
} else {
    std::println("You are a minor.");
}
```

We have one condition and two possible outcomes.

---

*Two variables*

## Comparisons between two variables

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

*3.5 / The operators*

## The comparison operators used here

| Operator | Meaning |
|---|---|
| `==` | equal to |
| `<` | less than |
| `>=` | greater than or equal to |

---

*A gotcha*

## Leftover newline

```cpp
std::cin >> age;
std::cin.ignore(); // discard the leftover newline

std::getline(std::cin, friendName); // otherwise this reads an empty line
```

<div class="callout"><code>std::cin >></code> leaves the <code>\n</code> you pressed sitting in the input buffer - the very next <code>getline</code> reads that leftover newline as an empty line if you don't clear it first.</div>

---

*3.5 / Conditional breakpoints*

## Only stop when it matters

Right-click a breakpoint on the `if` line and add a **condition**, e.g.
`age < 18` - the debugger only pauses when that's true, instead of
every single run.