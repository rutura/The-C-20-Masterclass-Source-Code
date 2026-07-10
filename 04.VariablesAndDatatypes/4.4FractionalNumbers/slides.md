---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 4 · Variables and Data Types'
---

<!-- _class: lead -->

# Fractional Numbers

## float, double, and long double

---

*The need*

## Not every number is whole

An amount spent needs a fractional part - cents. C++ has three
floating-point types for that, each trading off size for precision.

```cpp
float amountSpent{93.3333333333333f};
double averageDailySpend{0.185185185185};
long double preciseAverage{93.3333333333333333L};
```

---

*Precision compared*

## How many digits can each type trust?

| Type | Size | Significant digits |
|---|---|---|
| `float` | 4 bytes | ~7 |
| `double` | 8 bytes | ~15-16 |
| `long double` | platform-dependent | more than `double` |

```cpp
std::println("amountSpent      : {:.15f}", amountSpent);
std::println("averageDailySpend: {:.15f}", averageDailySpend);
```

`{:.15f}` prints 15 digits after the decimal point - enough to expose
each type's real precision limit.

---

*Why it matters for money*

## Digit drift

```cpp
float totalSpentThisYear = 1'924'000.23f; // looks fine printed normally...
std::println("{:.5f}", totalSpentThisYear); // ...but isn't, at this precision
```

<div class="callout">float's limited precision is why it's a poor fit for a running total of money - this "obviously wrong" digit drift quietly corrupts a ledger over time if left unnoticed.</div>

---

*Scientific notation*

## For very large or very small numbers

```cpp
double roundingFeeFraction{3.498e-11};   // 3.498 * 10^-11
double annualRevenue{1.924e8};           // 1.924 * 10^8
```

Handy once numbers get very large (annual revenue) or very small (the
fraction of a cent a currency-conversion fee might round to).

---

*Dividing by zero*

## Infinity and NaN

```cpp
double totalSpent{-5.6};
double expenseCount{};          // zero expenses logged yet

double infinityResult{totalSpent / expenseCount};  // -inf
double nanResult{0.0 / expenseCount};              // nan
```

Floating-point division by zero doesn't crash the way integer division
does - it produces special values instead: infinity, or "not a number"
when the result is undefined (like `0.0 / 0.0`).

---

*Debug it*

## Inspect the special values directly

Breakpoint after `infinityResult` and `nanResult` are computed - your
IDE's locals view will show `inf`/`-inf` and `nan` directly, which is
the clearest way to recognize them the first time you see one in the wild.
