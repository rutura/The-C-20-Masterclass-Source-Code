---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 4 · Variables and Data Types'
---

<!-- _class: lead -->

# Const and Constexpr

## Locking values down

---

*const*

## Set once, never reassigned

```cpp
const double taxRate{0.08};
const int categoryCount{4}; // Food, Transport, Entertainment, Other

// taxRate = 0.10; // compiler error: can't reassign a const variable
```

Some values should never change once set - `const` says "initialize
once, then never reassign", enforced by the compiler.

---

*Mixing const and non-const*

## A const result from non-const ingredients

```cpp
double amountSpent{93.33};
const double amountWithTax{amountSpent * (1.0 + taxRate)};
```

A regular variable can still be used to compute a `const` one - the
*result* is locked in, even though one of its ingredients wasn't `const`.

---

*constexpr*

## Known before the program even runs

```cpp
constexpr double receiptRequiredAbove{25.0};
```

`constexpr` goes a step further than `const`: the value must be
computable at **compile time**, before `main()` even starts - not just
"never reassigned". Stronger than most everyday values need, but exactly
right for a fixed limit like a receipt threshold.

---

*What can feed a constexpr*

## Only what the compiler already knows

```cpp
constexpr int maxCategoriesSupported{8};

// constexpr double badExample{amountSpent}; // compiler error:
// amountSpent is only known once the program is running

constexpr int maxCategoriesDoubled{maxCategoriesSupported * 2}; // fine
```

<div class="callout">A constexpr variable can only be initialized from other constexpr values or literals - the compiler works out the whole chain during compilation.</div>

---

*const vs. constexpr*

## Choosing between them

| | When the value is known | Can it be computed at compile time? |
|---|---|---|
| `const` | Once, at runtime (e.g. user input) | Not required |
| `constexpr` | Before the program runs | Required |

---

*Debug it*

## Constants still show up in locals

Breakpoint after `amountWithTax` is computed - `const`/`constexpr`
variables still appear in your IDE's locals view like any other
variable, just without an option to edit their value while paused.
