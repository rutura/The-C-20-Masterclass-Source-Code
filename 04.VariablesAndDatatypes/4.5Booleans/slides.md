---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 4 · Variables and Data Types'
---

<!-- _class: lead -->

# Booleans

## Yes/no switches

---

*The type*

## Only ever one of two values

```cpp
bool hasReceipt{false};
bool isOverBudget{true};
```

Perfect for the yes/no questions an expense tracker needs to answer:
did we keep the receipt? are we over budget?

---

*Using it in a condition*

## Explicit vs. direct

```cpp
if (hasReceipt == true) {
    std::println("Receipt on file.");
} else {
    std::println("No receipt - might get flagged in an audit.");
}
```

```cpp
if (isOverBudget) {   // no "== true" needed
    std::println("Over budget this month!");
}
```

<div class="callout">Comparing a bool to true/false explicitly works, but it's redundant - the bool itself already is the yes/no answer.</div>

---

*Size*

## The smallest type we've seen

```cpp
std::println("sizeof(bool): {}", sizeof(bool));
```

A `bool` only needs to distinguish two states, but C++ still gives it a
full byte - there's no smaller addressable unit of memory to use.

---

*Printing it*

## Words by default, digits on request

```cpp
std::println("hasReceipt   : {}", hasReceipt);   // true
std::println("hasReceipt   : {:d}", hasReceipt); // 1
```

`std::println` formats a `bool` as the word `true`/`false` by default -
`{:d}` instead prints the underlying integer: `1` for true, `0` for false.

---

*Debug it*

## Toggle it and watch the branch change

Breakpoint on the `if (isOverBudget)` line, then use your IDE's locals
view to flip the value from `true` to `false` mid-run and step forward -
watching the branch taken actually change confirms you understand which
path a bool controls.
