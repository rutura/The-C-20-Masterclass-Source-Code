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

### Counting side by side

In decimal, each position holds 10 symbols (`0`-`9`) before it rolls over
and carries into the next position. In binary, each position holds only 2
symbols (`0` and `1`), so it rolls over and carries far more often.
Counting the same sequence in both bases side by side shows the pattern:

| Decimal | Binary     |
|--------:|:----------:|
|       0 | `00000000` |
|       1 | `00000001` |
|       2 | `00000010` |
|       3 | `00000011` |
|       4 | `00000100` |
|       5 | `00000101` |
|       6 | `00000110` |
|       7 | `00000111` |
|       8 | `00001000` |
|       9 | `00001001` |
|      10 | `00001010` |
|      11 | `00001011` |
|      12 | `00001100` |
|      13 | `00001101` |
|      14 | `00001110` |
|      15 | `00001111` |
|      16 | `00010000` |
|      17 | `00010001` |
|      18 | `00010010` |
|      19 | `00010011` |
|      20 | `00010100` |
|      21 | `00010101` |
|      22 | `00010110` |
|      23 | `00010111` |
|      24 | `00011000` |
|      25 | `00011001` |
|      26 | `00011010` |
|      27 | `00011011` |
|      28 | `00011100` |
|      29 | `00011101` |
|      30 | `00011110` |
|      31 | `00011111` |
|      32 | `00100000` |
|      33 | `00100001` |
|      34 | `00100010` |
|      35 | `00100011` |
|      36 | `00100100` |
|      37 | `00100101` |
|      38 | `00100110` |
|      39 | `00100111` |
|      40 | `00101000` |
|      41 | `00101001` |
|      42 | `00101010` |
|      43 | `00101011` |
|      44 | `00101100` |
|      45 | `00101101` |
|      46 | `00101110` |
|      47 | `00101111` |
|      48 | `00110000` |
|      49 | `00110001` |
|      50 | `00110010` |
|      51 | `00110011` |
|      52 | `00110100` |
|      53 | `00110101` |
|      54 | `00110110` |
|      55 | `00110111` |
|      56 | `00111000` |
|      57 | `00111001` |
|      58 | `00111010` |
|      59 | `00111011` |
|      60 | `00111100` |
|      61 | `00111101` |
|      62 | `00111110` |
|      63 | `00111111` |
|      64 | `01000000` |
|      65 | `01000001` |
|      66 | `01000010` |
|      67 | `01000011` |
|      68 | `01000100` |
|      69 | `01000101` |
|      70 | `01000110` |
|      71 | `01000111` |
|      72 | `01001000` |
|      73 | `01001001` |
|      74 | `01001010` |
|      75 | `01001011` |
|      76 | `01001100` |
|      77 | `01001101` |
|      78 | `01001110` |
|      79 | `01001111` |
|      80 | `01010000` |
|      81 | `01010001` |
|      82 | `01010010` |
|      83 | `01010011` |
|      84 | `01010100` |
|      85 | `01010101` |
|      86 | `01010110` |
|      87 | `01010111` |
|      88 | `01011000` |
|      89 | `01011001` |
|      90 | `01011010` |
|      91 | `01011011` |
|      92 | `01011100` |
|      93 | `01011101` |
|      94 | `01011110` |
|      95 | `01011111` |
|      96 | `01100000` |
|      97 | `01100001` |
|      98 | `01100010` |
|      99 | `01100011` |
|     100 | `01100100` |

## 3. Hex is binary's shorthand

Hex (base 16) exists because **one hex digit always represents exactly 4
bits.** That makes it a compact way to write binary values without a wall
of 0s and 1s.

```
 binary:   0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111
   hex:      0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
decimal:     0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
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

## 4. Octal

Octal (base 8, digits `0`-`7`) is rarely written by hand in modern
application code. Its main surviving use is Unix/Linux file permissions.

Octal follows the same place-value idea as decimal and binary — just with
8 symbols (`0`-`7`) available per position instead of 10 or 2. Counting
decimal alongside octal and binary side by side shows where it sits
between the two:

| Decimal | Octal | Binary     |
|--------:|:-----:|:----------:|
|       0 | `0`   | `00000000` |
|       1 | `1`   | `00000001` |
|       2 | `2`   | `00000010` |
|       3 | `3`   | `00000011` |
|       4 | `4`   | `00000100` |
|       5 | `5`   | `00000101` |
|       6 | `6`   | `00000110` |
|       7 | `7`   | `00000111` |
|       8 | `10`  | `00001000` |
|       9 | `11`  | `00001001` |
|      10 | `12`  | `00001010` |
|      11 | `13`  | `00001011` |
|      12 | `14`  | `00001100` |
|      13 | `15`  | `00001101` |
|      14 | `16`  | `00001110` |
|      15 | `17`  | `00001111` |
|      16 | `20`  | `00010000` |
|      17 | `21`  | `00010001` |
|      18 | `22`  | `00010010` |
|      19 | `23`  | `00010011` |
|      20 | `24`  | `00010100` |
|      21 | `25`  | `00010101` |
|      22 | `26`  | `00010110` |
|      23 | `27`  | `00010111` |
|      24 | `30`  | `00011000` |
|      25 | `31`  | `00011001` |
|      26 | `32`  | `00011010` |
|      27 | `33`  | `00011011` |
|      28 | `34`  | `00011100` |
|      29 | `35`  | `00011101` |
|      30 | `36`  | `00011110` |
|      31 | `37`  | `00011111` |
|      32 | `40`  | `00100000` |
|      33 | `41`  | `00100001` |
|      34 | `42`  | `00100010` |
|      35 | `43`  | `00100011` |
|      36 | `44`  | `00100100` |
|      37 | `45`  | `00100101` |
|      38 | `46`  | `00100110` |
|      39 | `47`  | `00100111` |
|      40 | `50`  | `00101000` |
|      41 | `51`  | `00101001` |
|      42 | `52`  | `00101010` |
|      43 | `53`  | `00101011` |
|      44 | `54`  | `00101100` |
|      45 | `55`  | `00101101` |
|      46 | `56`  | `00101110` |
|      47 | `57`  | `00101111` |
|      48 | `60`  | `00110000` |
|      49 | `61`  | `00110001` |
|      50 | `62`  | `00110010` |

Notice `15` is `17` in octal — which is exactly the `017` literal in
`main.cpp`. That's the point of the opening hook: `017` looks like it
should read as "seventeen," but the leading `0` marks it as octal, and
octal's `17` is decimal `15`.

Octal rolls over every 8 steps (`7 → 10`, `17 → 20`, `27 → 30`, ...) —
slower than binary's constant rollover, faster than decimal's every-10.

Octal's other convenient property: each octal digit is exactly 3 bits, so
it groups binary into 3s the way hex groups it into 4s. That 3-bit
grouping is why it survives in one place — Unix/Linux file permissions,
where each permission group (owner/group/others) is 3 bits (read/write/
execute), so it fits neatly into one octal digit per group:

```
chmod 755 file.sh
        │└└─ 5 = read + execute        (4+0+1 = r-x)
        │
        └─── 7 = read + write + execute (4+2+1 = rwx)
```

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
