---
marp: true
theme: masterclass
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# 3.5 Making Decisions

## Branching on what the user told us

---

*3.5 / if / else*

## Following a different path

```cpp
if (age >= 18) {
    std::println("You are an adult.");
} else {
    std::println("You are a minor.");
}
```

One condition, two possible outcomes.

---

*3.5 / Two variables*

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

*3.5 / The operators*

## The comparison operators used here

| Operator | Meaning |
|---|---|
| `==` | equal to |
| `<` | less than |
| `>=` | greater than or equal to |

Same operators, applied where they're actually useful - not memorized
as an isolated list before you have a reason to care.

---

*3.5 / A gotcha*

## Leftover newline

```cpp
std::cin >> age;
std::cin.ignore(); // discard the leftover newline

std::getline(std::cin, friendName); // otherwise this reads an empty line
```

<div class="callout"><code>std::cin >></code> leaves the <code>\n</code> you pressed sitting in the input buffer - the very next <code>getline</code> reads that leftover newline as an empty line if you don't clear it first.</div>

---

*3.5 / Try it*

<div class="shot tall" data-label="Screenshot: terminal — age vs. friend's age comparison output"></div>

---

*3.5 / Conditional breakpoints*

## Only stop when it matters

Right-click a breakpoint on the `if` line and add a **condition**, e.g.
`age < 18` - the debugger only pauses when that's true, instead of
every single run.

<div class="shot" data-label="Screenshot: breakpoint condition dialog (Visual Studio or Qt Creator)"></div>

---

<!-- _class: lead -->

# Next: 3.6
## Doing It Many Times
