# Intro to Assembly

Everything so far in this course has been "here is C++ code, here is
what it does when it runs." This chapter opens up the step in between:
**what does the computer actually do, physically, to run it?**

You will not write any assembly yourself, except briefly at the very
end of the chapter, which shows you how, if you want to go further. The
main job here is to *read* a little of it - on real examples pulled
from chapters and lectures you already know - so that ideas which have
so far just been words ("a variable," "calling a function," "a loop")
turn into something you can point at and watch happen, instruction by
instruction.

---

## 8.2 Memory and the CPU

Before any assembly makes sense, two physical things need to be
straight in your head: memory and the CPU.

### Two pieces of hardware: memory and the CPU

**Memory (RAM)** is one enormous street of numbered mailboxes. Every
single byte your program uses - every variable, every piece of text -
lives in one of these mailboxes, at its own unique **address** (just a
number, like a house number). Two ideas for you to keep in mind:

- Memory is **big** but **slow** to reach
- CPU storage is **smaller** but way **fast**

Memory is divided in `byte` sized chunks:

```
   memory - one giant column of numbered boxes, EACH HOLDING EXACTLY
   ONE BYTE.

   address 1000:  [ 7 ]
   address 1001:  [ 0 ]
   address 1002:  [ 0 ]
   address 1003:  [ 0 ]
   address 1004:  [ 3 ]
   address 1005:  [ 0 ]
   address 1006:  [ 0 ]
        ...          ...
```

Notice the addresses climb **by exactly 1 each time** - `1000`, `1001`,
`1002`...  **every single address names exactly one byte, always.**

That raises an obvious question: if a 32-bit CPU and a 64-bit CPU both
address memory **one byte at a time**, what does "32-bit" or "64-bit"
actually describe? **The width of an address itself** - how large a
number a register (a bunch of bytes in the CPU) can hold to *name* a byte,
not how many bytes that number points to.

**The 32-bit case, worked out in full.** A 32-bit address is a binary
number with 32 digits - each digit either a 0 or a 1, so there are
exactly `2 × 2 × 2 × ... ` (32 times) = `2^32` different numbers such an
address can hold: `2^32 = 4'294'967'296`. Since every address names
exactly one byte (established above), that is also the largest possible
number of distinct bytes a 32-bit address could ever reach - about 4.3
billion bytes.

That raw number, "4.3 billion bytes," is correct but not a size anyone
actually thinks in - nobody buys "4.3 billion bytes" of RAM, they buy
gigabytes. So the next question is simply: **how many gigabytes is
4.3 billion bytes?** Answering that means understanding the unit itself
first.

**What a GiB actually is, and why memory is measured in powers of 2 at
all.** In everyday language, "kilo" means 1,000 and "giga" means
1,000,000,000 - powers of **10**, because humans count in base 10 (we
have 10 fingers). A computer's memory, though, is built entirely out of
binary switches, each one either off or on, and memory addresses are
counted in binary - so the *natural* round numbers for memory sizes are
powers of **2**, not powers of 10. Because "kilo", "mega" and "giga"
already mean powers of 10, the power-of-2 sizes were given their own
names (standardized by the IEC in 1998) so the two can't be confused:

```
   1 KiB  ("kibibyte")  =  2^10 bytes  =              1,024 bytes
   1 MiB  ("mebibyte")  =  2^20 bytes  =          1,048,576 bytes
   1 GiB  ("gibibyte")  =  2^30 bytes  =      1,073,741,824 bytes
   1 TiB  ("tebibyte")  =  2^40 bytes  =  1,099,511,627,776 bytes

   each step up is exactly 2^10 (= 1,024) times the one before it
```

The `bi` in there stands for binary. For comparison, here are the
regular (decimal, SI) units they are modelled on, where each step up is
exactly 1,000 times the one before:

```
   1 kB  ("kilobyte")   =  10^3  bytes  =              1,000 bytes
   1 MB  ("megabyte")   =  10^6  bytes  =          1,000,000 bytes
   1 GB  ("gigabyte")   =  10^9  bytes  =      1,000,000,000 bytes
   1 TB  ("terabyte")   =  10^12 bytes  =  1,000,000,000,000 bytes

   binary vs. decimal, side by side:
      1 KiB is  2.4% bigger than 1 kB
      1 MiB is  4.9% bigger than 1 MB
      1 GiB is  7.4% bigger than 1 GB
      1 TiB is 10.0% bigger than 1 TB    (the gap grows at every step)
```

A `GiB` (gibibyte) is *not* the same unit as a `GB` (gigabyte): a GB is
exactly `10^9` bytes, a GiB is exactly `2^30` bytes. They are close
enough that people - and Windows, which calculates in GiB but labels it
"GB" - often use "GB" for both.

**Now the division itself, spelled out.** "How many GiB is `2^32`
bytes?" is just `2^32 ÷ 2^30`.

```
   2^32  written out in full is:  2 × 2 × 2 × ... × 2     (32 twos)
   2^30  written out in full is:  2 × 2 × 2 × ... × 2     (30 twos)

   2×2×2×...×2  (32 of them)          2×2  (only 2 left, uncancelled)
   ─────────────────────────    =     ──────────────────────────────
   2×2×2×...×2  (30 of them)                    1

```

```
   2^32 ÷ 2^30  =  2^(32 - 30)  =  2^2  =  2 × 2  =  4
```

So `2^32` bytes is exactly **4 GiB**, meaning that a 32-bit system can have
an address space of 4 GiB max! (Some 32-bit systems used a trick called
PAE to install more *physical* RAM than that, but each program still
only ever saw a 4 GiB address space.)

**The 64-bit case is the same arithmetic, just with a bigger exponent -
and here real hardware quietly does not go all the way.** `2^64` is
about 18.4 quintillion bytes. Using the same division trick with the
biggest unit from the table above, TiB (`2^40` bytes):

```
   2^64 ÷ 2^40  =  2^(64 - 40)  =  2^24  =  16,777,216 TiB
```

That is almost **17 million TiB** of address space (16 EiB, "exbibytes"),
far beyond anything any computer is built with today. Chip makers do not
bother wiring up (or having software manage) all 64 bits for something
no machine can use, so real x86-64 CPUs only implement the **low bits**
of those 64 (the upper bits must just repeat the highest implemented bit),
and leave the rest architecturally reserved for future growth:

```
   how many of the 64 possible address bits are ACTUALLY wired up,
   on real x86-64 hardware today

   48-bit addressing (the long-standing default, most machines):
        2^48 bytes  =  256 TiB of addressable memory

   57-bit addressing ("5-level paging" - newer server-class chips):
        2^57 bytes  =  128 PiB (pebibytes) of addressable memory
```

**Let's put this in perspective.**

- You are using a 64-bit system -> 2^64 addressable space
- Out of the 2^64 addresses, the CPU states you could use 2^48 : 256 TiB
- In 2026, there's no computer with this amount of RAM so this must be impossible!
- What happens, the OS lies to each program that it can access such amounts of memory
   and it has a way to map the address space the program sees to the address space that is
   actually available on your machine.

**So if that 256 TiB was never a promise about physical RAM, what is it
actually used for?** This is where **virtual memory** comes in - and
the short answer is: your 256 TiB figure is real, but it is not one
shared number for the whole machine. **Every single running program
gets its own private 256 TiB (or whatever the CPU's address width
allows) of address space, all to itself**, regardless of how much
physical RAM the machine actually has installed.

```
   what "virtual address space" means, concretely

   ┌─────────────────────────┐    ┌─────────────────────────┐
   │   Program A is running  │    │   Program B is running  │
   │                         │    │                         │
   │   thinks it owns a      │    │   thinks it ALSO owns a │
   │   private 0 .. 256 TiB  │    │   private 0 .. 256 TiB  │
   │   range of addresses    │    │   range of addresses    │
   └───────────┬─────────────┘    └───────────┬─────────────┘
               │                              │
               │   both ranges get privately  │
               │   translated, separately     │
               ▼                              ▼
      ┌──────────────────────────────────────────────┐
      │  the ONE real pool of physical RAM actually  │
      │  installed in the machine (say, 64 GiB)      │
      └──────────────────────────────────────────────┘
```

Neither program is lying to itself, and neither is somehow using more
memory than physically exists. **Every address a running program uses
is a *virtual* address - a number in its own private range - and the
CPU (working together with the operating system) silently translates
that virtual address into wherever the corresponding data actually
lives in physical RAM**, a step called address translation, done via
data structures called page tables. Two completely different programs
can both use the exact same-looking address, say `0x00007F0000001000`,
at the same moment, and land on two entirely different physical bytes -
because each program's addresses are translated through its *own*
private mapping, not a machine-wide one.

A couple of consequences worth knowing:

- **One process cannot see or corrupt another's memory just by
  guessing an address** - the addresses it can even form only translate
  through *its own* mapping. This isolation is a large part of why one
  crashing program does not normally take the whole machine down with
  it.
- **A program's own virtual space can be larger than the physical RAM
  installed.** The operating system can temporarily move a chunk of a
  program's data out to disk (this is what "paging" or a "swap file"
  is) when it is not currently needed, marking that virtual address as
  "not in RAM right now". The next time the program touches it, the CPU
  stops and lets the operating system bring the data back into RAM
  first, then the program carries on as if nothing happened.
- **On real 64-bit Windows specifically, a process does not even get
  the CPU's full 256 TiB** - Windows reserves half of the addressable
  range for its own kernel use and hands a 64-bit user program a
  private range of **128 TiB** (`0x0000000000000000` through
  `0x00007FFFFFFFFFFF`) to work with. The CPU's address rules already
  split the range into a low half and a high half; giving the high half
  to the kernel is the choice Windows (and Linux) make on top of that.

The addresses we will be working with in our assembly programs, are
**virtual addresses**.

### What a process's own private address space actually looks like

We have seen that each process running on your OS has its own virtual address
space. Let's draw it out.

```
   one process's own virtual address space, low addresses at the TOP
   of the page - a simplified, classic layout:

   0x0000000000000000  ┌───────────────────────────────────┐
                       │ TEXT   - your compiled code       │
                       │ (the actual machine               │
                       │  instructions this lecture        │
                       │  has been reading all along)      │
                       ├───────────────────────────────────┤
                       │ DATA   - global / static          │
                       │ variables, string literals        │
                       ├───────────────────────────────────┤
                       │ HEAP   - grows toward HIGHER      │
                       │ addresses as the program          │  ▼ grows DOWN
                       │ requests more dynamic memory      │  (toward
                       │ (std::vector, "new", etc. -       │   higher
                       │  a later chapter's topic)         │   addresses)
                       ├───────────────────────────────────┤
                       │                                   │
                       │                                   │
                       │                                   │
                       │                                   │
                       │                                   │
                       │                                   │
                       ├───────────────────────────────────┤
                       │ STACK  - grows toward LOWER       │
                       │ addresses as functions call       │  ▲ grows UP
                       │ other functions (exactly what     │  (toward
                       │ this lecture has been drawing)    │   lower
   0x00007FFFFFFFFFFF  └───────────────────────────────────┘   addresses)
```

Three things this settles, all at once:

- **The stack is not the only thing in a process's address space** -
  it is one region, deliberately placed at the *high* end, with the
  program's code and global data at the *low* end.
- **The heap and the stack grow toward each other, from opposite ends**
  - the heap growing DOWN the page, toward higher addresses, as the
    program allocates more dynamic memory; the stack growing UP the
    page, toward lower addresses, as function calls nest deeper. This
    is why they are placed at opposite ends instead of next to each
    other: each one needs room to grow *without a neighbor immediately
    in the way*.
- **The large gap in the middle is the room the stack (and the heap)
  grow into** - and on 64-bit it is enormous, with shared libraries and
  other mappings living in it too. A tiny program's stack might only
  use a sliver of addresses near the very bottom of the diagram (the
  highest addresses); a program with deep recursion or many nested
  calls uses more, climbing further up the page into the gap. But
  the stack never gets the whole gap: its maximum size is fixed up
  front (1 MiB by default on Windows/MSVC, typically 8 MiB on Linux),
  with a guard page at the end. Grow past that limit and you get a
  **stack overflow**, long before the stack could ever reach the heap.

**The CPU** is the chip that actually does arithmetic and makes
decisions. It cannot compute directly on memory - it first has to pull a
value in from memory, into one of a small number of **registers**: tiny
storage slots built into the CPU chip itself, close enough that reading
or writing one is close to instant. A typical x86-64 CPU has around 16
of these. Each one has its own name, and - this is the part you should
remember - **each one also has its own job**. A couple are general
scratch space for whatever a calculation needs. A few others are
reserved, by long-standing convention, for one specific purpose each -
"the register that always holds a function's answer," "the register
that always tracks where the current function's workspace starts." You
will meet each register by name, one at a time, exactly at the point
where its job first matters in this chapter.

```
   CPU (a handful of registers, VERY fast)   memory (huge, slower)
   ┌───────────────────────────────┐         ┌──────────────────────┐
   │  [ a few named slots ]        │  ◄───►  │  address 1000: [ 7 ] │
   │  [ some general purpose ]     │  load   │  address 1004: [ 3 ] │
   │  [ some with a fixed job ]    │  store  │  address 1008: [   ] │
   └───────────────────────────────┘         └──────────────────────┘
```

**every general-purpose register is 8 bytes wide, but has multiple
names, one per size**, because not every value needs all 8 bytes. An
`int` (4 bytes) does not need the full width; a memory *address* (8
bytes, on this CPU) does. Rather than waste a name, x86-64 lets you
address the *same physical register* at four different widths:

```
   We can access parts of a register

   byte:    7    6    5    4    3    2    1    0
          ┌────┬────┬────┬────┬────┬────┬────┬────┐
          │    │    │    │    │    │    │    │    │
          └────┴────┴────┴────┴────┴────┴────┴────┘
          └───────────────────────────────────────┘  rax  - all 8 bytes
                              └───────────────────┘  eax  - low 4 bytes
                                        └─────────┘  ax   - low 2 bytes
                                             └────┘  al   - low 1 byte

   writing to eax also changes what rax holds (its low 4 bytes)
```

The naming pattern is consistent across every general-purpose register,
not just this one: an `r` prefix means the full 8 bytes (`rax`, `rdi`,
`rbp`, `rsp`...), an `e` prefix means the low 4 bytes (`eax`, `edi`,
`ebp`...), and there are narrower 2-byte and 1-byte names too, for when
even 4 bytes is more than a value needs. You will see this exact
pattern later: the same argument shows up as `edi` when a function
takes a plain `int`, and as `rdi` when it takes something that needs a
full address, like a reference.

Quick reference - keep this in mind for the rest of the chapter:

- **`r`-prefix** (`rax`, `rdi`, `rbp`, `rsp`, ...) - the full 8 bytes;
  wide enough to hold a memory address on this CPU
- **`e`-prefix** (`eax`, `edi`, `ebp`, ...) - the low 4 bytes only;
  wide enough for an `int`, not for an address
- **no prefix, plain name** (`ax`, `di`, `bp`, `sp`, ...) - the low
  2 bytes only
- **`l`-suffix** (`al`, `dil`, `bpl`, `spl`, ...) - the low 1 byte only
- all four names for a given register (e.g. `rax`/`eax`/`ax`/`al`) refer
  to the **same physical storage** - writing through the narrower name
  changes the low bytes of the wider one too

Summing this up, programming at the assembly level is just a delicate dance
you do between the CPU and Memory.

```
   CPU (a handful of registers, VERY fast)   memory (huge, slower)
   ┌───────────────────────────────┐         ┌──────────────────────┐
   │  [ a few named slots ]        │  ◄───►  │  address 1000: [ 7 ] │
   │  [ some general purpose ]     │  load   │  address 1004: [ 3 ] │
   │  [ some with a fixed job ]    │  store  │  address 1008: [   ] │
   └───────────────────────────────┘         └──────────────────────┘
```

Every instruction you will meet in this chapter does one of
exactly three things:

- **move** a value between a register and memory (or another register)
- **compute** - arithmetic or comparison, on a register
- **jump** - decide where to continue running next

Assembly is just a very long, very literal to-do list built entirely
out of those three things.

### `reinterpret_cast`: the same bits, viewed as a different type

`8.2MemoryAndTheCPU/main.cpp` does this to get a printable address:

```cpp
int width{4};
auto width_address{reinterpret_cast<std::uintptr_t>(&width)};
```

`&width` is a value of type `int*` - a pointer. `std::uintptr_t` (from
`<cstdint>`) is an **integer** type - on a typical 64-bit Linux system,
literally `unsigned long`; on 64-bit Windows/MSVC, `unsigned __int64`.
That can look like a contradiction: is the result an address, or just
some number? It is both, because - and this is the entire point of
this lecture - **an address already is just a number**. `int*` is a
*C++-level* abstraction built on top of that number: it remembers "this
points at an `int`," lets you dereference it, and restricts what
arithmetic you're allowed to do on it. `reinterpret_cast` does not
convert the value into something new - it takes the *exact same bits*
and relabels them with a different type, dropping the pointer-specific
rules and exposing the plain number that was underneath all along:

```
   the SAME 8 bytes in memory, looked at through two different types

   ┌─────────────────────────────────┐
   │   7f  fc  6a  f4  23  7c  00 00  │   <- the actual bits never change
   └─────────────────────────────────┘
       as int*                            as std::uintptr_t
       ───────                            ──────────────────
       "points at an int"                 "is the number 0x7ffc6af4237c"
       can be dereferenced (*ptr)          can be added, subtracted,
       arithmetic moves by sizeof(int)     formatted with {:x}, etc.
       can't be printed with {:x}          can't be dereferenced
```

This particular cast - pointer to `std::uintptr_t` - is one of the few
places the C++ standard explicitly guarantees `reinterpret_cast` works
exactly as expected: convert any pointer to `std::uintptr_t` and back to
the same pointer type, and you get the original pointer back, unchanged.
That guarantee is *why* `uintptr_t` exists at all, and it is also why
this is the **only** integer type to reach for here - not `int`, not
`unsigned`, not whatever happens to compile.

**Three things worth being careful about any time `reinterpret_cast` is
involved** - this is a tool for "trust me, compiler," so the usual
compiler safety net (type checking) is exactly what you are opting out
of:

**1. Size mismatch would truncate the address - both gcc and clang
refuse outright.** `std::uintptr_t` is guaranteed wide enough for a
pointer; a plain `unsigned int` is not, on a 64-bit system:

```cpp
auto truncated{reinterpret_cast<unsigned int>(&width)};  // error on both gcc and clang
```

```
   what this would do, IF it compiled - the same 8-byte address,
   forced into a 4-byte box:

   ┌─────────────────────────────────┐
   │   7f  fc  6a  f4  23  7c  00 00  │   the real, 8-byte address
   └─────────────────────────────────┘
                       ┌───────────────┐
                       │ 23  7c  00 00 │   all that fits in an unsigned int -
                       └───────────────┘   the top half is just gone
```

Both compilers consider the information loss serious enough to reject
this by default - `cast from pointer to smaller type 'unsigned int'
loses information` on clang, `loses precision [-fpermissive]` on gcc
(the `[-fpermissive]` name is a hint: gcc *will* compile it if you
explicitly pass `-fpermissive`, downgrading the error to a warning -
which is not a reason to do it, just an explanation of the flag name).
This is one of the rarer cases where the compiler itself enforces a
`reinterpret_cast` safety rule for you, rather than silently compiling
something that only breaks at runtime.

The rule to take away: only cast a pointer to an integer type you
*know* is at least as wide as a pointer on every platform you care
about - which is precisely the one guarantee `std::uintptr_t` gives
you, and `unsigned int` does not.

**2. Reinterpreting one pointer type as another is usually undefined
behaviour ("strict aliasing"), even when the sizes match.** The compiler
is allowed to assume a `float*` and an `int*` never point at the same
memory (there are narrow exceptions - `char*`, `unsigned char*`, and
`std::byte*` - none of which apply here), and it optimises on that
assumption:

```cpp
float value{3.14f};
int* fooled{reinterpret_cast<int*>(&value)};
int bits{*fooled};   // undefined behaviour - NOT a safe way to inspect a float's bits
```

This is the genuinely dangerous case, because at `-O0` it will often
print a plausible-looking number and seem to work - then silently break
when you turn optimisations on, because the optimiser takes the
no-aliasing promise at face value and reorders or discards code that
depends on it. If what you actually want is "look at this value's raw
bits, as a different type, safely," **C++20's `std::bit_cast`** (from
`<bit>`) is the modern replacement for exactly this case - same idea,
but the compiler *checks* that both types are the same size, and the
result is well-defined instead of undefined:

```cpp
#include <bit>

float value{3.14f};
auto bits{std::bit_cast<std::uint32_t>(value)};  // well-defined, sizes checked at compile time
```

**3. `reinterpret_cast` does not fix up alignment.** Some types must
start at addresses that are multiples of their size (a common CPU
requirement). Reinterpreting a pointer as a type with a stricter
alignment requirement than the original object actually has, and then
dereferencing it, is undefined behaviour - even when the byte sizes
match exactly and no aliasing rule is broken.

A quick summary to keep nearby:

```
   reinterpret_cast<std::uintptr_t>(ptr)   fine - the one standard-guaranteed round trip
   reinterpret_cast<void*>(int_ptr)        unnecessary - int* -> void* already converts
                                            implicitly, no cast needed at all
   reinterpret_cast<int*>(a float*)        risky - strict-aliasing UB if dereferenced
   reinterpret_cast<unsigned int>(ptr)     risky - truncates the address on 64-bit systems
   std::bit_cast<To>(from)      (C++20)    prefer this for same-size reinterpretation -
                                            compiler-checked sizes, defined behaviour
```

**Code for this lecture**: `8.2MemoryAndTheCPU/main.cpp` prints two real
variables' own addresses on your machine, plus how wide an address is
here - run it a few times and watch what stays the same between runs
and what moves.

---

## 8.3 Compiler Explorer and targeting x86-64

### The tool: Compiler Explorer (Godbolt)

You do not need to install anything. **Compiler Explorer**, a free
website at **godbolt.org**, compiles code you type on the left and
shows the resulting assembly on the right, updating live as you type:

```
   ┌─────────────────────────┐   ┌─────────────────────────┐
   │  C++ source (you type)  │   │ assembly (auto-updates) │
   │                         │   │                         │
   │  int square(int num) {  │──►│ square(int):            │
   │      return num * num;  │   │      imul   edi, edi    │
   │  }                      │   │      mov    eax, edi    │
   │                         │   │      ret                │
   └─────────────────────────┘   └─────────────────────────┘
```

**Try it now, before reading any further**: open godbolt.org, delete
whatever is in the left pane, and type exactly the `square` function
above (no `#include`, no `main` needed - a lone function is enough).
Watch the right pane fill in as you type the closing `}`.

Two settings matter, both on the assembly pane's toolbar:

- **Compiler** - a dropdown offering `x86-64 gcc`, `x86-64 clang`, and
  (search the dropdown, it is there) `x86-64 msvc`. This chapter shows
  **gcc and clang** output, both real, both run from this course's own
  Linux containers (chapter 2) to get it. Where MSVC genuinely differs,
  that is called out by name below, so if you build with MSVC day to
  day you are not left guessing.
- **Compiler options** - a text box where you type flags. Type `-O0`
  (the letter O, then a zero; MSVC spells the same idea `/Od`) to turn
  **optimisation off**. Leave that in for almost this entire chapter:
  `-O0` tells the compiler "do not get clever, just translate my code
  fairly literally," which keeps the assembly close enough to the
  source that you can match one against the other line by line. Only
  near 8.9 do we deliberately switch it to `-O2`, to see what
  "the compiler optimised it" actually removes.

### Assembly belongs to one specific CPU

Assembly is **not portable** the way C++ is. It is written directly in
one CPU family's own private vocabulary of instruction names and register
names, so the exact same C++ function produces completely different-looking
assembly depending on which CPU it was compiled for.

```
   the SAME square(int) function, compiled for two different CPUs

   x86-64                              ARM64
   ───────────────────────────────     ───────────────────────────────
   square(int):                        square(int):
           sub   rsp, ...                      sub   sp, sp, #16
           mov   DWORD PTR [...], edi          str   w0, [sp, #12]
           mov   eax, DWORD PTR [...]          ldr   w8, [sp, #12]
           imul  eax, eax                      ldr   w9, [sp, #12]
           ret                                 mul   w0, w8, w9
                                                add   sp, sp, #16
                                                ret
```

Different instruction names (`str`/`ldr` instead of
`mov`), a `mul` that takes three registers instead of `imul`'s two,
different register names (`w0`, `w8`, `w9`).

**This chapter targets x86-64** (also written `x86_64` or `amd64`) -
the instruction set used inside essentially every Windows and Linux
desktop or laptop, and older Intel-based Macs. If your own machine is
an Apple Silicon Mac (M1/M2/M3/M4), its *native* code is actually the
ARM64 shown above - Compiler Explorer will still compile to x86-64
(in the browser) for you regardless.

One of the main points we are trying to make here is that the
C++ you write is portable and can be compiled for any CPU, but the compiled
version of the code (assembly), is specific to a given CPU.

```
   WILL transfer to any CPU               will NOT transfer - x86-64 only
   ─────────────────────────              ────────────────────────────────
   a variable is an address in memory      the instruction is called "mov"
   a function call means: remember         the registers are called
   where you were, then jump in            eax, edi, rbp, rsp
   returning means jumping back            a multiply is spelled "imul"
   a loop is a jump backwards
```

**Code for this lecture**: `8.3CompilerExplorer/main.cpp` has `square`
ready to paste into Compiler Explorer, buildable and runnable on its
own too.

---

## 8.4 The stack before main

**There are things that happen before `main` runs**: your program
does not start itself, and `main` is not the very first code that runs.
The operating system loads the compiled program into memory and jumps
to a fixed entry point - conventionally named **`_start`** - which is
not part of your code at all, but a small amount of startup code the
compiler links in automatically (part of the C runtime, "CRT"). `_start`
sets a few things up and only then calls `main`. By the time that happens,
the stack already exists and is already partway in use, handed to your program
already set up.

```
   the bottom end of the full layout diagram from 8.2, zoomed in: low
   addresses at the TOP, high addresses at the BOTTOM, and the stack
   growing UP the page (toward lower addresses) - same orientation,
   same direction, just a closer look.

   address 0x6FE0:  ┌───────────────────────────────┐   ▲ toward the big
                    │                               │   │ gap from the full
                    │    (free - not yet claimed;   │     layout above:
                    │     part of the same large    │     room this stack
                    │     gap shown in the full     │     has not needed
                    │     layout diagram above -    │     yet, but COULD
                    │     room for the stack to     │     grow UP into
                    │     grow up into, if deeper   │
                    │     calls need it)            │
   address 0x7000:  ├───────────────────────────────┤ ◄── rsp = 0x7000
                    │                               │      (the boundary
                    │     (already claimed - in     │       IS 0x7000:
                    │     use by the code that      │       free above,
                    │     runs before main)         │       claimed
                    │                               │      below)
   address 0x7020:  └───────────────────────────────┘
```

The stack's real size limit (about 1 MiB by default on MSVC) is
far above the top of this picture. The addresses here are kept small
so they are easy to read; real ones are much larger (see the full
layout diagram in 8.2).

```
   every byte has its own address - counting from the top edge of
   this picture down to rsp, in hex:

   0x6FE0   ← top edge of the picture
   0x6FE1
   0x6FE2
   0x6FE3
   0x6FE4
   0x6FE5
   0x6FE6
   0x6FE7
   0x6FE8
   0x6FE9   (next comes 0x6FEA, not 0x6FF0 - hex digits run 0-9, then A-F)
     ...
   0x6FF7
   0x6FF8   ← the next diagram's return address starts here
   0x6FF9
   0x6FFA
   0x6FFB
   0x6FFC
   0x6FFD
   0x6FFE
   0x6FFF   ← last byte before rsp - one more rolls every F over:
   0x7000   ← rsp: the boundary

   0x7000 - 0x6FE0 = 0x20 = 32 bytes of free space in this picture
```

There is a register called **`rsp`**, and it holds an actual address -
`0x7000` in this diagram - marking the boundary between "stack space
already claimed" (below it in this drawing, at the higher addresses)
and "stack space not yet claimed" (above it, at the lower addresses).

**`rsp`** stands for "stack pointer." Its one job is to always
**hold the address** of the current top of the stack.

Here is the program we are about to trace - the smallest `main`
possible - with its C++ source on the left and the assembly gcc turns
it into at `-O0` on the right:

```
   C++ source                 gcc -O0 assembly
   ────────────────           ─────────────────────────────
   int main() {        ──►    main:
                                      push    rbp
                                      mov     rbp, rsp
       return 0;       ──►            mov     eax, 0
   }                   ──►            pop     rbp
                                      ret
```

Before any of these five lines runs, `_start` has already called
`main`. The next two diagrams show that call, and then these first two
lines.

Now watch what happens the instant the OS calls `main`, with the
addresses tracked at every step. A return address on this CPU is
**8 bytes**, so pushing one onto the stack always subtracts exactly 8
from `rsp` - moving it 8 bytes UP the page:

```
   the OS calls main()

   BEFORE the call - same as the diagram just above, rsp still at 0x7000:

   address 0x6FE0:  ┌───────────────────────────────┐   ▲ toward the
                    │                               │   │ big gap
                    │             (free)            │
                    │                               │
   address 0x7000:  ├───────────────────────────────┤ ◄── rsp = 0x7000
                    │        the C runtime's        │      (the boundary
                    │    startup frame ("_start")   │       IS 0x7000)
                    │                               │   ← "_start" - the C
                    │                               │     runtime's own
   address 0x7020:  └───────────────────────────────┘     startup code,
                                                          NOT the OS and
                                                          NOT main - the
                                                          thing that
                                                          actually calls
                                                          main.

   THE INSTANT main starts running -  the system claimed the 8 bytes just
   above the 0x7000 boundary, wrote into them, and moved rsp UP the page
   to a NEW boundary:

   address 0x6FE0:  ┌───────────────────────────────┐
                    │             (free)            │
   address 0x6FF8:  ├───────────────────────────────┤ ◄── rsp = 0x6FF8
                    │  return address: "come back   │      (moved UP by 8:
                    │   here when main ends"        │       0x7000 - 8)
   address 0x7000:  ├───────────────────────────────┤
                    │        the C runtime's        │
                    │    startup frame ("_start")   │
   address 0x7020:  └───────────────────────────────┘
```

Calling a function does not just "jump" to it - it first **writes**
that 8-byte return address into the 8 bytes just above `rsp` on the
page (`0x6FF8` up to `0x7000`), and moves `rsp` to that new boundary -
subtracting 8, from `0x7000` to `0x6FF8` - so `rsp` again marks
wherever the *new* top of the stack is. That written-down address is
how `main` - or any function - eventually finds its way back to
whoever called it. (The instruction that does this writing-down is
`call`, covered properly once you have a second function to call, in
8.7. For now, the point is only: by the time `main`'s own first
instruction runs, an address has already been written to memory at
`0x6FF8`, and `rsp` has already moved up the page by 8, from `0x7000`
to `0x6FF8`, to reflect it.)

`main` is about to want a private workspace of its own - somewhere to
keep its own bookkeeping, separate from `_start`'s.

That is what the statements

```
push rbp
mov rbp, rsp
```

do. **`rbp`** is the **base pointer**, and the easiest way to picture
it is as a pin stuck into the stack at the spot where a function's
workspace begins.

`rsp` can't do that job, because it moves every time something is
pushed or popped. If a function tried to find its own variables by
counting from `rsp`, the count would keep changing as the function
ran - "my variable is 4 bytes from `rsp`" would be true one moment and
wrong the next. So each function plants `rbp` once, right at its
start, and leaves it there. From then on every local variable has a
permanent, easy address: "4 bytes from the pin", "8 bytes from the
pin", no matter how much `rsp` moves around in the meantime.

In short: **`rsp` marks where the stack ends right now; `rbp` marks
where *this function's* part of the stack begins.** Each function needs
a base pointer to work with, including the starter code that calls our
main function. so before we give control to our own main function, we
push the base pointers of the caller of main to the stack, and after that,
we store the current stack pointer as the base pointer of our main function.

The diagram below shows the state after the two statements, reproduced
below for convenience, run:

```
push rbp          ; save rbp's current value on the stack
mov rbp, rsp      ; copy rsp INTO rbp   (rbp ◄── rsp)
```

**`mov` copies from right to left.** The first name after `mov` is the
**destination** - where the value ends up - and the second is the
**source** - where it comes from. So `mov rbp, rsp` means "copy the
value in `rsp` into `rbp`"; `rsp` itself is left unchanged. It reads
exactly like assignment in C++: `rbp = rsp;` - the thing on the left
receives, the thing on the right is read. Every `mov` in this chapter
follows that same rule - `mov eax, 0` in the listing above, for
example, puts `0` into `eax`.

```
   right after main's first two instructions run - "push rbp" wrote
   another 8 bytes just above the 0x6FF8 boundary, and moved rsp UP
   to a new boundary, 0x6FF0, which rbp then copies for itself:

   address 0x6FE0:  ┌─────────────────────────────────┐
                    │              (free)             │
   address 0x6FF0:  ├─────────────────────────────────┤ ◄── rsp = 0x6FF0
                    │     main's saved copy of the    │ ◄── rbp = 0x6FF0
                    │         CALLER's old rbp        │      (both agree,
   address 0x6FF8:  ├─────────────────────────────────┤       for now)
                    │    return address (unchanged,   │
                    │    written earlier by "call")   │
   address 0x7000:  ├─────────────────────────────────┤
                    │         the C runtime's         │
                    │     startup frame ("_start")    │
   address 0x7020:  └─────────────────────────────────┘
```

`rsp` moved AGAIN here - up the page from `0x6FF8` to `0x6FF0` - because
`push rbp` just wrote another 8 bytes (the value `rbp` held a moment
ago) onto the stack, at the new top. `rbp` then **copies** that same
address, `0x6FF0`, via `mov rbp, rsp` - so `rsp` and `rbp` now briefly
agree, both holding `0x6FF0`.

From here on, though, they behave differently: `rsp` will keep moving to
lower addresses (further up the page) as `main` uses more stack space,
but `rbp` will **not** change again for the rest of `main`'s run. `rbp`
becomes a fixed anchor: the moment `main` declares a local variable,
its address will be described as "so many bytes lower than `rbp`" -
e.g. `0x6FF0 - 4 = 0x6FEC`, and that arithmetic stays correct all the way
through `main`, precisely because `rbp` itself never changes.

Again, that fixed anchor is worth having, but setting it up spends `rbp` -
overwrites whatever it held before, which belonged to `_start`'s own
code, not main's. Throwing that away would be a problem the instant
`main` finishes and control needs to go back to code that still expects
to find its own `rbp` value intact. So the very first thing any
function does, before repointing `rbp` at itself, is **save the old
value of `rbp` on the stack** - and the very last thing it does, right
before returning, is **put that old value back**:

```
   push    rbp        first: save whatever rbp held before (the
                      CALLER's anchor point), so it is not lost
   mov     rbp, rsp    now: repoint rbp here - THIS function's own anchor

   ...the function's own body runs here, measured from rbp...

   pop     rbp         restore the CALLER's rbp value, exactly as found
   ret                 jump back to the address "call" saved
```

This four-line shape - **push rbp, mov rbp/rsp, ..., pop rbp** - opens
and closes essentially every function you are about to look at. It has
two names: the opening two lines are a function's **prologue** (the
setup), the closing two are its **epilogue** (the teardown). You now
know exactly what both are protecting and why.

Two more instructions, met just now and worth naming plainly before
moving on:

```
   push   <register>   claim the next 8 free bytes just above rsp and
                        write that register's value into them (rsp
                        DECREASES by 8 - the stack grows UP the page)

   pop    <register>   the exact reverse: read the value at the top of
                        the stack into that register, then hand those
                        8 bytes back as free space (rsp INCREASES by 8 -
                        the stack shrinks back DOWN the page)
```

### Reading it end to end: the smallest possible program

```cpp
int main() {
    return 0;
}
```

You already have everything needed to read this one. Here is what gcc,
at `-O0`, turns it into:

```
main:
        push    rbp
        mov     rbp, rsp
        mov     eax, 0
        pop     rbp
        ret
```

The first two lines and the last two are exactly the prologue and
epilogue you just walked through above - nothing new to figure out
there. That leaves exactly one line in the middle that is new, plus
`ret`:

```
   mov     eax, 0    copy the literal value 0 into a register called
                     eax. eax has a fixed, special job : it is always where a
                     function leaves its return value for whoever
                     called it to find. "return 0;" in your source
                     becomes, quite literally, "put 0 in eax."

   ret               "return." Jump back to wherever this function was
                     CALLED from - for main, that is the operating
                     system's own startup code from a moment ago.
```

So the whole five-line function reads, once you have both halves: save
the caller's `rbp`, claim this frame as your own, put the answer `0`
where callers look for it, give the caller's `rbp` back, jump back to
whoever called you. Every one of those five lines is either "move a
value" or "jump" - nothing more exotic happens anywhere in assembly.

**Code for this lecture**: `8.4StackBeforeMain/main.cpp` is exactly
this smallest `main`. Paste it into Compiler Explorer (gcc, `-O0`) and
confirm you see the same five lines.

---

## 8.5 A variable is an address in memory

```cpp
int rectangle_area() {
    int width{4};
    int height{3};
    int area{width * height};
    return area;
}
```

```
rectangle_area():
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 4     ← width
        mov     DWORD PTR [rbp-8], 3     ← height
        mov     eax, DWORD PTR [rbp-4]   ← read width into eax
        imul    eax, DWORD PTR [rbp-8]   ← eax = eax * height
        mov     DWORD PTR [rbp-12], eax  ← area
        mov     eax, DWORD PTR [rbp-12]  ← return value = area
        pop     rbp
        ret
```

The prologue and epilogue are the same two lines from 8.4 - skip past
those, you already know what they are doing. What is new is the body,
is this piece of new notation: **`DWORD PTR [rbp-4]`**. Read it in chunks:

```
   [rbp-4]        "the memory address that is 4 bytes lower than
                  wherever rbp is pointing" - an address, computed from
                  the frame's own anchor point.

   DWORD PTR      "treat whatever is at that address as a 4-byte value"
                  (DWORD = "double word" = 4 bytes, the size of an int
                  on this compiler). Without this, the CPU would not
                  know how many bytes at that address to read/write.
```

So `mov DWORD PTR [rbp-4], 4` reads as: "write the 4-byte value 4 into
memory, at the address 4 bytes lower than rbp." **That address is `width`.**
Not a name the CPU knows about - the name `width` existed only in your
source code, for you to read. To the compiled program, `width` simply
*is* a particular address, and every place your C++ used the name
`width`, the compiler substituted that same address.

Three variables, three addresses, spaced 4 bytes apart because each is
a 4-byte `int`:

```
   this function's stack frame:

   address rbp - 12:  ┌─────────────────────────┐
                      │  area    = 12           │
   address rbp - 8:   ├─────────────────────────┤
                      │  height  = 3            │
   address rbp - 4:   ├─────────────────────────┤
                      │  width   = 4            │
   address rbp:       ├─────────────────────────┤ ◄── rbp
                      │  caller's saved rbp     │
   address rbp + 8:   ├─────────────────────────┤
                      │  return address         │
   address rbp + 16:  └─────────────────────────┘
```

Each local sits at a *lower* address than the one declared before it,
so each new variable is drawn one row further UP the page.

And `int area{width * height};` itself is not one step to the CPU - it
is three: **load** `width` from its address into the register `eax`,
**multiply** `eax` by whatever is at `height`'s address, **store** the
result at `area`'s address. C++ lets you write the whole idea as one
line; the CPU only ever does one small thing at a time.

```
        mov     eax, DWORD PTR [rbp-4]   ← read width into eax
        imul    eax, DWORD PTR [rbp-8]   ← eax = eax * height
        mov     DWORD PTR [rbp-12], eax  ← area
```

**Code for this lecture**: `8.5VariablesAreAddresses/main.cpp` has this
exact function, ready to run normally and to paste into Compiler
Explorer. Try changing `int height{3};` to `int height{9};` there and
watch only the `3` in the assembly change to a `9` - nothing else about
the shape moves, because the *addresses* `width`, `height`, and `area`
live at did not change, only the number stored at one of them.

---

## 8.6 `if` and loops are jumps

### `if` is a comparison plus a jump

```cpp
int pass_or_fail(int score) {
    if (score >= 60) {
        return 1;
    } else {
        return 0;
    }
}
```

```
pass_or_fail(int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi
        cmp     DWORD PTR [rbp-4], 59
        jle     .L2
        mov     eax, 1
        jmp     .L3
.L2:
        mov     eax, 0
.L3:
        pop     rbp
        ret
```

In this code snippet, we introduce a new register: `edi`.
`score` is a **parameter** here, not a local variable the function
invented for itself - it is a value the *caller* has to hand over.
Registers are the fastest way to hand a value from one function to another,
so this ABI reserves `edi` as a fixed, agreed-on slot:
**"the first whole-number argument always arrives in `edi`."** Every
compiler targeting this platform honours that agreement.
`mov DWORD PTR [rbp-4], edi` is simply this function's very first move:
copy whatever the caller left in `edi` into `score`'s own stack slot, so
the rest of the function can treat `score` the same way 8.5 treated
`width` and `height` - a plain address, read and written by `mov`.

Two new *kinds* of instruction also show up here, both used for the
first time:

```
   cmp   DWORD PTR [rbp-4], 59    "compare score against 59" - this does
                                   not store a result anywhere visible;
                                   it just sets some internal CPU flags
                                   (e.g. "was the first value bigger,
                                   smaller, or equal") for the very next
                                   instruction to read.

   jle   .L2                      "jump if less-or-equal" - reads the
                                   flags cmp just set. If score <= 59,
                                   jump to the label .L2. Otherwise, do
                                   nothing and fall straight into the
                                   next line.
```

**A `.L2:` on its own line is a label** - not an instruction, just a
named marker in the code that a jump instruction can target. It exists
purely so `jle .L2` and `jmp .L3` have somewhere to point.

Trace it as a flowchart, which is really all this is:

```
                    cmp score, 59
                          │
                    is score <= 59 ?
                    ╱             ╲
                 yes               no
                  │                 │
                  ▼                 ▼
            jump to .L2       fall through:
            (the "else"        mov eax, 1   (the "if" branch)
             branch below)     jmp .L3  (skip over the else branch)
                  │                 │
           .L2:  mov eax, 0         │
                  │                 │
                  └────────┬────────┘
                           ▼
                      .L3: pop rbp ; ret
```

There is no dedicated "if" instruction anywhere on this CPU. `if`/`else`
in your source compiles down to exactly this: one `cmp`, one
conditional jump, two runs of plain instructions, and labels for the
jumps to land on. Every relational operator we have seen before in C++
(`<`, `<=`, `>`, `>=`, `==`, `!=`) has its own matching conditional
jump - `jl`, `jle`, `jg`, `jge`, `je`, `jne`.

One thing worth pointing out: the condition got **flipped**.
Your source says `score >= 60`; the assembly tests `score <= 59` and
jumps to the *else* branch on true. That is a compiler doing the exact
same job a different, equally correct way - "jump away from the if-branch
when the condition is false" reaches the same outcome as "jump into the
if-branch when the condition is true." Compilers choose whatever instructions
make the job easier. You don't have control over this. For example, depending
on the hardware configuration in CPU, that instruction may be more beneficial.

**Try it**: change `>= 60` to `> 60` and try to make sense of the generated assembly.

### A loop is a jump backwards

```cpp
int sum_below_five() {
    int total{0};
    for (int i{0}; i < 5; ++i) {
        total += i;
    }
    return total;
}
```

```
sum_below_five():
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 0    ← total = 0
        mov     DWORD PTR [rbp-8], 0    ← i = 0
        jmp     .L2
.L3:
        mov     eax, DWORD PTR [rbp-8]
        add     DWORD PTR [rbp-4], eax  ← total += i
        add     DWORD PTR [rbp-8], 1    ← ++i
.L2:
        cmp     DWORD PTR [rbp-8], 4    ← is i <= 4 ?  (same as i < 5)
        jle     .L3                     ← if true, jump BACK UP to .L3
        mov     eax, DWORD PTR [rbp-4]
        pop     rbp
        ret
```

Notice this uses **exactly** the same two instructions as the `if`
above - one `cmp`, one `jle` - nothing new. The only structural
difference from an `if` is *where the label being jumped to sits*:
`.L3` (the loop body) is written **above** `.L2` (the check), so
jumping to it means jumping **backward**, re-running instructions the
CPU already ran once.

```
   the loop, in the order its instructions sit in the listing
   (the numbers on the right are the order things HAPPEN):

          jmp  .L2  ────────────────┐   1. skip straight to the check
                                    │
   ┌───►  .L3:  total += i          │   3. run the body...
   │            ++i                 │      ...then fall down into the check
   │                                │
   │      .L2:  cmp  i, 4  ◄────────┘   2. is i <= 4 ?
   └──────────  jle  .L3                4. yes: jump BACK UP to .L3
                                           - THIS is the backward jump
                mov  eax, total         5. no: fall through, return total
```

Every loop shape you know - `while`, `for`, `do...while` - compiles
down to some arrangement of *label*, *body*, *check*, *jump backward*.
The one structural difference you can usually spot for `do...while` is
that it skips the initial `jmp` straight to the check.

**Code for this lecture**: `8.6IfAndLoopsAreJumps/main.cpp` has both
functions. Try it: change the `for` loop above to an equivalent `while`
loop and compare - the assembly should end up nearly identical, because
`for` and `while` are the same loop, just spelled differently in C++
source.

---

## 8.7 Calling a function: `call` and `ret`

We have a `add_numbers` function, called from `main`:

```cpp
int add_numbers(int first, int second) {
    int result{first + second};
    return result;
}

int main() {
    int sum{add_numbers(25, 7)};
    return 0;
}
```

```
add_numbers(int, int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi   ← first  = whatever main put in edi
        mov     DWORD PTR [rbp-8], esi   ← second = whatever main put in esi
        mov     eax, DWORD PTR [rbp-4]
        add     eax, DWORD PTR [rbp-8]   ← eax = first + second
        mov     DWORD PTR [rbp-12], eax  ← result = eax
        mov     eax, DWORD PTR [rbp-12]  ← return value = result
        pop     rbp
        ret

main:
        push    rbp
        mov     rbp, rsp
        mov     esi, 7                        ← 2nd argument
        mov     edi, 25                       ← 1st argument
        call    add_numbers(int, int)
        mov     DWORD PTR [rbp-4], eax        ← sum = whatever came back in eax
        mov     eax, 0
        pop     rbp
        ret
```

Two brand new instructions here, plus one new register.

The register first, since it is the smaller idea: `add_numbers` takes
*two* parameters, and 8.6 already covered where the first one, `edi`,
comes from. The second whole-number argument gets its own fixed slot
too, by that same convention - `esi`. Same idea as `edi`, just the
agreed-on spot for argument number two.

C++ lets a function take as many parameters as you like, but the CPU
only has a handful of registers, so the convention hands out registers
for the first few arguments and puts the **rest on the stack**:

```
   argument:    1st    2nd    3rd    4th    5th    6th    7th and beyond
   ────────     ────   ────   ────   ────   ────   ────   ──────────────
   gcc/clang    rdi    rsi    rdx    rcx    r8     r9     on the stack
   (Linux/Mac)

   MSVC         rcx    rdx    r8     r9     on the stack ─────────────►
   (Windows)
```

(These are the full 8-byte names; an `int` argument uses the 4-byte
`e` form, like the `edi`/`esi` above. `double`/`float` arguments use a
separate set of registers, `xmm0`, `xmm1`, ...) So the two platforms
agree on the idea but not on the register names.

Now the two instructions that actually make a function call happen:

```
   call    jump to another function's first instruction - but FIRST,
           push the address of the instruction right after this "call"
           onto the stack. That is the one and only way the CPU has of
           remembering where to come back to once the called function
           finishes.

   ret     pop that saved address back off the stack, and jump to it.
           This is how a function knows where to return TO, the address
           was written there by "call" itself, the moment this function was entered.
```

`ret` always jumps back to whatever `call` most recently pushed - which, for every
function *except* `main`, was written by another one of your own functions; for `main`,
by the operating system's own startup code.

Walk through the whole call as one sequence:

```
   main calls add_numbers(25, 7)

   ┌────────────────────────────────┐
   │  main:                         │
   │      mov  esi, 7               │  1. 2nd argument goes into esi
   │      mov  edi, 25              │  2. 1st argument goes into edi
   │      call add_numbers(int,int) │  3. remember here, jump in
   │  ┌─────────────────────────┐   │
   │  │ add_numbers(int, int):  │◄──┘
   │  │   reads edi, esi        │      4. new stack frame, its OWN
   │  │   ...computes...        │         first/second/result
   │  │   mov  eax, result      │      5. answer placed in eax
   │  │   ret                   │───┐  6. pop remembered address, jump back
   │  └─────────────────────────┘   │
   │      mov  [rbp-4], eax  ◄──────┘  7. main stores add_numbers's answer
   └────────────────────────────────┘
```

**Code for this lecture**: `8.7CallingAFunction/main.cpp` has both
functions. Paste them into Compiler Explorer together and make sense
of what is going on. Modify the C++ code by adding a third
parameter and make sense of the generated assembly. You can do it!

---

## 8.8 A reference is a hidden address

Let's see how references are actually handled by assembly.

```cpp
void add_one_by_value(int n) {
    n += 1;
}

void add_one_by_ref(int& n) {
    n += 1;
}
```

```
add_one_by_value(int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi   ← n = its OWN 4-byte copy
        add     DWORD PTR [rbp-4], 1     ← changes only that copy
        pop     rbp
        ret

add_one_by_ref(int&):
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi   ← n = an 8-byte ADDRESS
        mov     rax, QWORD PTR [rbp-8]   ← load that address into rax
        mov     eax, DWORD PTR [rax]     ← follow it - read the int it points to
        lea     edx, [rax+1]             ← edx = (that value) + 1
        mov     rax, QWORD PTR [rbp-8]   ← reload the address
        mov     DWORD PTR [rax], edx     ← write through it - the CALLER's int changes
        pop     rbp
        ret
```

Three things to notice, in order down that second listing.

First, `QWORD PTR` instead of `DWORD PTR` for `add_one_by_ref`'s `n`:
**QWORD** means 8 bytes (a "quad word"), because on this CPU a memory
address itself is 8 bytes long - `add_one_by_ref`'s `n` is not holding a
4-byte `int` at all, it is holding the *address of* one.

Second, `edi` became `rdi` (8 bytes) - the same register, just its full
64-bit width instead of its 4-byte one, because an address needs all 8 bytes
to store.

Third, one new register and one new instruction on the `lea` line:
`edx` is simply another general-purpose register, playing the same role
`eax` usually does - a scratch spot to hold a value briefly. `lea` -
"load effective address" - normally computes an address without reading
memory at all, but here it is being used as a shortcut for plain
addition: `lea edx, [rax+1]` means "put `rax + 1` into `edx`," done this
way because this particular addition happened to line up with an
address-arithmetic instruction the compiler already had available. It
is worth being able to recognise, not worth dwelling on.

```
   by value:   n IS the int itself                    4-byte value in edi
               add_one_by_value never touches
               the caller's own variable at all

   by ref:     n IS the ADDRESS of the caller's int    8-byte address in rdi
               every use of "n" in the source costs
               an extra step: follow the address
               ([rax]) to reach the real int
```

`n += 1` in `add_one_by_ref` is not one instruction, the way it was for
`add_one_by_value` - it is **load the address**, **follow it to read
the value**, **add one**, **follow the address again to write the
result back**. This is the entire mechanism behind 6.8's "an alias for
the caller's variable": a C++ reference is, underneath, an address. The
difference from a plain address is entirely at the C++ level - the
language will only let you use `n` as if it were the `int` itself, and
never lets you ask for the address it is secretly built from.

**Code for this lecture**: `8.8ReferencesAreAddresses/main.cpp` has
both functions. Paste them in together and count the instructions in
each body - `add_one_by_ref` needs noticeably more, purely to keep
following that address.

---

## 8.9 `inline` and `constexpr`: watching code disappear

### `inline`: watching the call disappear

```cpp
inline int cube(int num) {
    return num * num * num;
}

int main() {
    int result{cube(3)};
    return result;
}
```

At `-O0`, `inline` usually changes **nothing** you can see - `call
cube(int)` is still sitting right there in `main`'s assembly. That is
because `-O0` deliberately does the least amount of clever rewriting
possible, and `inline` (6.2) is only ever a *suggestion* to the
compiler, never a command it is obliged to follow.

Switch Compiler Explorer's optimisation flag from `-O0` to **`-O2`**
and look again:

```
   -O0  (optimisations off)          -O2  (optimisations on)
   ───────────────────────           ───────────────────────
   main:                             main:
       mov   edi, 3                      mov   eax, 27      ← no call at all
       call  cube(int)                   ret
       ...
   cube(int):                       cube(int) does not even
       ... multiply, multiply ...   appear in the output
       ret
```

At `-O2`, gcc does two things at once: it pastes `cube`'s body straight
into `main` instead of calling it (exactly what "inline" describes in
plain words), and then - since `cube(3)`'s argument never changes - it
goes ahead and does the multiplication itself, at compile time, leaving
only the finished number `27` behind. Nothing is computed while the
program runs; the entire function call has vanished. Clang and MSVC
reach the same outcome at their own equivalent "optimise for speed"
levels (`-O2`/`-O3` for clang, `/O2` for MSVC); the exact size or call
count at which a given compiler decides a function is worth inlining
can differ between them, but "a small, frequently-called function tends
to disappear into its caller once optimisation is turned on" holds
across all three.

**Try it**: flip the compiler options box between `-O0` and `-O2` on
this exact example and watch `cube(int)` appear and disappear.

### `constexpr`: computed before the program even runs

```cpp
constexpr int square_ce(int num) {
    return num * num;
}

constexpr int nine{square_ce(3)};
```

```
   square(6) at runtime            square_ce(3) as a constexpr call
   ───────────────────             ─────────────────────────────────
   argument only known             argument is a literal, known
   while the program runs          while the compiler is still running
        │                                    │
        ▼                                    ▼
   mov edi, 6 ; call square         mov [rbp-8], 9    ← just the answer, no work
```

A `constexpr` function *can* run at compile time - but only when every
value it is called with is itself known at compile time (6.10 has the
full rule). Call it with a literal, like `square_ce(3)` here, and the
compiler does not emit a multiply instruction at all: it works out
`3 * 3` itself, while compiling, and the assembly shows only the
finished number `9` being stored. Call the exact same function with a
value the program will not know until it runs (something typed in by
the user, say), and the assembly falls back to an ordinary `call` - a
`constexpr` function never *forces* compile-time evaluation, it only
*allows* it when the inputs make that possible.

One detail worth being precise about: this needs no `-O2`. Unlike
`inline` just above, folding away a genuinely compile-time-computable
`constexpr` call is not an optimisation being applied to generated
code - there was never any runtime code generated for it to begin with,
even at `-O0`.

**Code for this lecture**: `8.9InlineAndConstexpr/main.cpp` has both
functions. Try it: call `square_ce` once with a literal (like
`square_ce(3)`) and once with a variable whose value the compiler
cannot know ahead of time - compare the two call sites' assembly.

---

## 8.10 Recursion: a function calling itself, literally

6.15's `sum_to`, in its own assembly.

```cpp
long sum_to(int n) {
    if (n <= 0) { return 0; }
    return n + sum_to(n - 1);
}
```

Two small new pieces show up here, worth naming before the full listing:
`rbx` is just another general-purpose register, being borrowed here as
extra scratch space; and `leave` is a one-instruction shorthand for the
`mov rsp, rbp` / `pop rbp` pair you have already seen close out every
other function in this chapter - same epilogue, spelled more briefly.

```
sum_to(int):
        push    rbp
        mov     rbp, rsp
        push    rbx                       ← save rbx, this call is about to use it
        sub     rsp, 24
        mov     DWORD PTR [rbp-20], edi   ← THIS call's own n
        cmp     DWORD PTR [rbp-20], 0
        jg      .L2                       ← n > 0 ? skip the base case
        mov     eax, 0                    ← base case: return 0
        jmp     .L3
.L2:
        mov     eax, DWORD PTR [rbp-20]
        movsxd  rbx, eax                  ← copy n into rbx, widened to 8 bytes -
                                           ←   parked there so the call below cannot
                                           ←   disturb it (eax is about to be overwritten)
        mov     eax, DWORD PTR [rbp-20]
        sub     eax, 1                    ← compute n - 1
        mov     edi, eax                  ← argument for the next call
        call    sum_to(int)               ← sum_to calling sum_to
        add     rax, rbx                  ← n + (whatever the recursive call returned)
.L3:
        pop     rbx                       ← restore rbx to what it was before this call
        leave                             ← shorthand for: mov rsp, rbp ; pop rbp
        ret
```

There is no separate "recursive call" instruction - `call sum_to(int)`
is the **exact same `call`** you saw in 8.7, it just happens to
target the very function that is currently running. What makes
recursion work is something you already know from 8.4: every `call`
gets **its own fresh stack frame**, stacked on top of whichever frame
made the call. `[rbp-20]` in the outer call and `[rbp-20]` in the
nested call are two genuinely different addresses in memory, because
`rbp` itself points somewhere different in each frame - so each call's
`n` is kept completely separate, automatically, purely because each
call pushed its own new frame onto the stack. This is precisely 6.15's
"each pending call is a stack frame" diagram, now with the actual
instruction (`call`) responsible for building each one.

**Code for this lecture**: `8.10Recursion/main.cpp` has `sum_to`. Paste
it in and find the line that reads `call sum_to(int)` - a function's
assembly containing a call to its own name is the tell-tale sign of
recursion, visible before you have even worked out what the function
computes.

### What to take away

```
   variable             →  a named address in memory, read/written by mov
   if / loop             →  cmp + a conditional jump (jle, jg, je, ...) + labels
   function call           →  call / ret; arguments in fixed registers, answer in eax
   reference parameter      →  an address passed in a register, followed on every use
   inline (-O2)              →  the call disappears, body pasted into the caller
   constexpr (literal)        →  the whole computation disappears, only the answer remains
   recursion                   →  call targeting the same function, a fresh frame each time
```

You will not be asked to write assembly, and most day-to-day C++ never
needs it. What this gives you, even glanced at occasionally, is a way
to settle "wait, what does this actually do?" with certainty instead of
a guess - and a first, concrete look at what "the compiler optimised it
away" means in practice, a phrase you will hear constantly from here
on.

---

## 8.11 Going further: assembly on your own machine

Compiler Explorer has been the right tool for this entire chapter, and
for day-to-day "what does this actually compile to" questions it stays
the right tool - it is free, needs no setup, and lets you flip compilers
and flags in seconds. This closing lecture is purely optional "going
further" material: two different ways to leave the website behind, one
for *reading* assembly your own compiler produces, one for *writing* a
little of your own by hand.

### Seeing assembly locally, without a website

Every compiler that can produce assembly for Compiler Explorer can
produce the exact same assembly for you, on your own machine, as a
plain text file.

**gcc / clang** (Linux, macOS, or Windows via MinGW/WSL) - the `-S`
flag means "stop after producing assembly, don't link an executable":

```
g++ -S -O0 -masm=intel main.cpp -o main.s
```

That writes `main.s` right next to `main.cpp` - open it in any text
editor. `-masm=intel` asks for the same `mov dest, src` ordering this
whole chapter has been reading; leave it off and gcc defaults to
AT&T syntax instead (`mov src, dest` - everything reversed, with `%`
in front of register names). Either is correct, just pick one and stay
consistent.

**MSVC** - the equivalent flag is `/FAs` (capital or lowercase both
work), which asks the compiler to emit an "assembly with source code"
listing file (`.asm`) alongside the normal `.obj`:

```
cl /FAs /Od /c main.cpp
```

In the Visual Studio IDE itself, the same switch lives under
*Project Properties → C/C++ → Output Files → Assembler Output*, set to
"Assembly With Source Code".

**Disassembling something already built** - if you only have a
compiled binary or object file, not the source, you can go the other
direction with `objdump` (Linux/macOS, also ships with MinGW on
Windows) or MSVC's own `dumpbin`:

```
objdump -d -M intel main.o      # Linux / macOS / MinGW
dumpbin /disasm main.obj        # MSVC
```

**Try it**: build `main.cpp` in this folder normally first, confirm it
prints `square(7) = 49`, then run the `g++ -S` command above (or the
MSVC equivalent) on it and open the resulting `.s`/`.asm` file - you
should recognise `square`'s body immediately, it is exactly the
8.3 listing.

### Writing your own assembly by hand, cross-platform

If you want to go one step further than *reading* assembly and
actually *write* a little yourself, the most genuinely cross-platform
way to do that is **NASM** (the Netwide Assembler, free, at
`nasm.us`) - the same tool, with the same syntax, installs on Windows,
Linux, and macOS alike.

The important caveat: "cross-platform tool" does not mean "write one
file, run it unchanged everywhere." The *syntax* NASM accepts is
identical on all three platforms, but what an assembly program
actually has to *do* to exit, print something, or ask the operating
system for anything at all is **not** - each OS has its own entry-point
convention and its own way of making that request (Linux: a raw
`syscall` instruction with a syscall number in `rax`, as below; Windows:
a call into `kernel32.dll`; macOS: Apple's own syscall convention,
layered under extra restrictions on recent versions). So a hand-written
`.asm` file is portable in *tooling*, not in *content* - the file
itself is still written for one specific OS.

`exit_code.asm`, alongside this file, is a complete, working example
for Linux (the platform this course's own containers, from chapter 2,
actually run) - three instructions, no linked libraries, that exit with
status code 42:

```
nasm -f elf64 exit_code.asm -o exit_code.o
ld exit_code.o -o exit_code
./exit_code ; echo $?        # prints 42
```

**Try it**: run those three commands, confirm you see `42`, then open
`exit_code.asm` and change `mov rdi, 42` to a different number - no
reassembling theory required, just re-run the same two build commands
and watch the new number come back.

If you are on Windows or macOS and want to take this further on your
own machine rather than through this course's Linux containers, search
for "NASM Windows x64 hello world" or "NASM macOS hello world" - the
instruction-by-instruction ideas from this chapter (registers, `mov`,
jumps, `call`/`ret`) carry over completely unchanged; only the handful
of lines that talk to the operating system need to be swapped out.

**Code for this lecture**: `8.11WritingAssemblyYourself/main.cpp` (a
normal, buildable C++ file to try the local `-S`/`/FAs` commands on)
and `8.11WritingAssemblyYourself/exit_code.asm` (the standalone NASM
example above).
