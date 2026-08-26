# Number Systems

Companion notes for this lecture's `main.cpp`. Reference this alongside the
code — it doesn't repeat the whole lecture, just the parts worth having in
writing.

---

## 1. Same value, four spellings

```cpp
int decimal{15};        // base 10: the default
int octal{017};         // base 8: leading 0
int hexadecimal{0x0F};  // base 16: leading 0x
int binary{0b00001111}; // base 2: leading 0b
```

All four lines above store the **same value**. The prefix (`0`, `0x`,
`0b`) only changes how you *spell* the literal in source code — it has no
effect on what's stored or how the program behaves. Print any of these
back out with `{}` and you get `15`, regardless of which base you used to
write it.

You've likely already seen numbers written in a non-decimal base without
realizing it — a color like `#FF5733` is hex, and a Unix permission like
`chmod 755` is octal.

---

## 2. Why binary exists

A computer is built from switches. A switch is either off or on — there's
no "off-ish" in between.

```
switch:     [ OFF ]      [ ON ]
bit:           0            1
voltage:      ~0V          ~5V
```

Binary (base 2) is ordinary place-value counting, just like decimal,
except only two digits are available (`0` and `1`) instead of ten
(`0`-`9`). Everything about binary follows from that one constraint.

### Place value, side by side

Decimal — each position is worth **10x** the one to its right:

```
   1     0     2     4     (decimal: 1024)
   |     |     |     |
 10^3  10^2  10^1  10^0
1000   100    10     1
```

Binary — each position is worth **2x** the one to its right:

```
   1     0     0     0     0     0     0     0     0     0     0
   |     |     |     |     |     |     |     |     |     |     |
 2^10  2^9   2^8   2^7   2^6   2^5   2^4   2^3   2^2   2^1   2^0
1024  512   256   128    64    32    16     8     4     2     1
```

Only the `2^10` column is a 1 in that row, so `10000000000` in binary is
`1024` in decimal.

### The odometer picture

A car odometer's wheels each hold 10 symbols (`0`-`9`) and roll over to
the next wheel when they pass 9: `9 → 10`. A binary "odometer" wheel only
has **two** symbols, so it rolls over far more often:

```
decimal counting:   8 →  9 → 10 → 11
binary   counting: 1000 → 1001 → 1010 → 1011
```

### Counting from 0 to 7

| Decimal | Binary | What just happened                          |
|--------:|:------:|----------------------------------------------|
|       0 |  `000` | all wheels at 0                               |
|       1 |  `001` | rightmost wheel ticks to 1                    |
|       2 |  `010` | rightmost wheel rolls over, next wheel ticks  |
|       3 |  `011` | rightmost wheel ticks again                   |
|       4 |  `100` | first two wheels roll over, third wheel ticks |
|       5 |  `101` |                                                |
|       6 |  `110` |                                                |
|       7 |  `111` | all three wheels maxed out                    |

Using the place-value table above, `0b00001111` from `main.cpp` decodes as
`8 + 4 + 2 + 1 = 15` — matching `decimal{15}` exactly.

---

## 3. Hex is binary's shorthand

Hex (base 16) exists because **one hex digit always represents exactly 4
bits.** That makes it a compact way to write binary values without a wall
of 0s and 1s.

```
 binary:   0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111
   hex:      0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
decimal:      0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
```

Because a byte is 8 bits, a full byte always fits in exactly **2 hex
digits**:

```
  byte:   1111 0000
          ----+----
           F     0     →   0xF0
```

`0x0F` from `main.cpp` splits into two 4-bit groups, `0000` and `1111`,
which are the hex digits `0` and `F` — the same value as `0b00001111` on
the line above it.

### Binary ↔ hex ↔ decimal lookup

| Binary | Hex | Decimal |
|:------:|:---:|:-------:|
| 0000   |  0  |    0    |
| 0001   |  1  |    1    |
| 0010   |  2  |    2    |
| 0011   |  3  |    3    |
| 0100   |  4  |    4    |
| 0101   |  5  |    5    |
| 0110   |  6  |    6    |
| 0111   |  7  |    7    |
| 1000   |  8  |    8    |
| 1001   |  9  |    9    |
| 1010   |  A  |   10    |
| 1011   |  B  |   11    |
| 1100   |  C  |   12    |
| 1101   |  D  |   13    |
| 1110   |  E  |   14    |
| 1111   |  F  |   15    |

---

## 4. Octal, briefly

Octal (base 8, digits `0`-`7`) is rarely written by hand in modern
application code. Its main surviving use is Unix/Linux file permissions:

```
chmod 755 file.sh
        │└└─ 5 = read + execute        (4+0+1 = r-x)
        │
        └─── 7 = read + write + execute (4+2+1 = rwx)
```

Each octal digit is 3 bits, which conveniently matches the 3 permission
bits (read/write/execute) for one of owner, group, or others.

---

## 5. Converting an existing value with `std::println`

`main.cpp` also shows the reverse direction — starting from one decimal
value and asking the compiler to format it in other bases:

```cpp
int reading{1024};
std::println("{} in decimal is {}, octal {:#o}, hex {:#x}, binary {:#b}",
    reading, reading, reading, reading, reading);
```

| Format spec | Base    |
|:-----------:|---------|
| `{}`        | decimal |
| `{:#o}`     | octal   |
| `{:#x}`     | hex     |
| `{:#b}`     | binary  |

The `std::cout` equivalent uses stream manipulators (`std::oct`,
`std::hex`) instead of format specs, and — once set — the manipulator
stays in effect for everything printed afterward until changed again:

```cpp
std::cout << reading << " in decimal is " << std::dec << reading
    << ", octal " << std::oct << reading
    << ", hex " << std::hex << reading
    << std::dec << "\n";
```

There is no `std::bin` manipulator — printing binary with `std::cout`
isn't supported without extra work, which is one reason `std::println`'s
format specs are the more convenient option.

---

## 6. Where this shows up in practice

| Base    | Where you'll actually see it                                   |
|---------|------------------------------------------------------------------|
| Decimal | Everywhere — the default for ordinary numbers                    |
| Hex     | Memory addresses, color codes (`#FF5733`), hashes, debugger output |
| Binary  | Bit flags, understanding how values are stored, low-level work   |
| Octal   | Almost nowhere except Unix file permissions (`chmod`)            |
