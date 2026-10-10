# Pointers and Arrays

In chapter 8 you saw that every variable lives at an **address**, and that a function call, a reference and a loop are all built out of addresses. C++ lets you hold an address in a variable of your own. That variable is a **pointer**.

```
   a variable                          a pointer
   ──────────                          ─────────
   int reading{72};                    int* where{&reading};

   ┌──────────┐                        ┌──────────────┐        ┌──────────┐
   │    72    │  address 1000          │     1000     │ ─────► │    72    │  address 1000
   └──────────┘                        └──────────────┘        └──────────┘
   holds a value                       holds an ADDRESS, which leads to a value
```

Pointers are how C++ talks about memory directly, and that makes them both powerful and dangerous: a pointer can point at something that is gone, at something that was never there, or at the wrong thing, and the compiler will let you try. This chapter teaches you what pointers are and how to read them, because you will meet them in older code, in libraries and in the machine-level view of every program. It also teaches you what modern C++ offers so that **you rarely have to use them raw**: spans for arrays, `std::vector` for growable data, and smart pointers that clean up after themselves.

The chapter ends with a detective project: a program with seven planted memory bugs, and the tools that catch them.

---

## 9.2 Pointers and addresses

In this lecture we meet the pointer itself, using the weather station's readings: a pointer that leads to a reading, reading through it, writing through it, and the value that means "points at nothing".

### Declaring a pointer, and taking an address

```cpp
int reading{72};
int* where{&reading};
```

Read the type `int*` as "**pointer to int**": a variable that holds the address of a place that holds an `int`. The **`&`** operator, placed in front of a variable, means "**the address of**". So `&reading` is the address where `reading` lives, and it is what `where` is initialised with.

To print an address, `std::println` needs it as a `void*` (an address with no type attached):

```cpp
std::println("reading lives at   {}", static_cast<const void*>(&reading));
std::println("where holds        {}", static_cast<const void*>(where));
std::println("where itself is at {}", static_cast<const void*>(&where));
```

```
reading lives at   0xb848aff9d0
where holds        0xb848aff9d0
where itself is at 0xb848aff9d8
```

(Your numbers will differ, and change between runs, as in 8.2.) Two things to see in that output. The first two lines are the **same address**: `where` holds exactly the address of `reading`. And the third line is a **different** address: `where` is itself a variable with a place to live. Here it sits 8 bytes after `reading`, because it is an 8-byte value (an address on a 64-bit machine).

```
   address 0xb848aff9d0   ┌──────────────────┐
                          │  reading = 72    │ ◄──────────┐
   address 0xb848aff9d8   ├──────────────────┤            │
                          │  where = 0xb848aff9d0 ────────┘
                          └──────────────────┘
```

### Following a pointer: `*`

In an expression, the **`*`** operator means "**follow the address**": the object the pointer points at. It works for reading and for writing.

```cpp
std::println("reading = {}, *where = {}", reading, *where);   // 72 and 72

*where = 75;                                                  // write through the pointer
std::println("after *where = 75: reading = {}", reading);     // 75
```

`*where` is not a copy. It **is** `reading`, reached by another route. That is the whole use of a pointer: a way to reach a variable that is not in your hands.

> **The star means two things.** In a declaration, `int*` is part of the **type** ("pointer to int"). In an expression, `*where` is an **operation** ("follow it"). The same symbol, two jobs, and you tell them apart by where they appear.

### A pointer can be pointed somewhere else

The pointer is its own variable. Assign a new address, and it leads somewhere new. The old target is not affected.

```cpp
int other{60};
where = &other;     // where now holds a different address
std::println("after where = &other: *where = {}, reading = {}", *where, reading);
```

```
after where = &other: *where = 60, reading = 75
```

### Every pointer has the same size, the type tells you what it leads to

```cpp
double temperature{21.5};
double* temperature_where{&temperature};
std::println("sizeof(int*) = {}, sizeof(double*) = {}", sizeof(where), sizeof(temperature_where));
std::println("sizeof(*where) = {}, sizeof(*temperature_where) = {}", sizeof(*where), sizeof(*temperature_where));
```

```
sizeof(int*) = 8, sizeof(double*) = 8
sizeof(*where) = 4, sizeof(*temperature_where) = 8
```

An address is the same size whatever it leads to. What differs is the **type** `int*` versus `double*`, which tells the compiler **how many bytes to read** at that address and **how to interpret them**. That is also why you cannot assign a `double*` to an `int*`: the compiler would be guessing how to read the memory.

### `nullptr`: pointing at nothing

A pointer you have no object for yet should hold the special value **`nullptr`**, never a random leftover address.

```cpp
int* nothing{nullptr};

if (nothing == nullptr) {
    std::println("nothing points nowhere");
}

if (nothing) {                    // a pointer converts to bool: false for nullptr
    std::println("this never prints: *nothing = {}", *nothing);
}
else {
    std::println("not dereferencing it: there is nothing to read");
}
```

Comparing a pointer with `nullptr`, or using it as a condition, is always safe. **Following** a null pointer with `*nothing` is **undefined behaviour**: usually an immediate crash, but the language promises nothing. The pattern to remember: **check before you follow, whenever a pointer might be empty.**

> **Never leave a pointer uninitialised.** In this course every variable is brace-initialised, and for pointers that means `nullptr` or a real address. An uninitialised pointer holds whatever bits were left in that memory, which is an address pointing at nobody knows what.

### Gotcha: the star belongs to the name

```cpp
int* first{&reading}, second{5};
std::println("sizeof(first) = {}, sizeof(second) = {}", sizeof(first), sizeof(second));
```

```
sizeof(first) = 8, sizeof(second) = 4
```

Only `first` is a pointer. `second` is a plain `int`, even though it looks like it shares the `int*`. The `*` attaches to the **name** next to it, not to the type. The simple cure is one variable per declaration.

### Pointers can outlive what they point at

A pointer holds an address and nothing else, so it knows nothing about the lifetime of the object there:

```cpp
int* dangling{nullptr};
{
    int short_lived{1};
    dangling = &short_lived;
}   // short_lived is destroyed here. dangling still holds its old address.
```

Reading through `dangling` after the closing brace is **undefined behaviour**: a **dangling pointer**. This is the main danger of raw pointers, and most of this chapter is about avoiding it.

**Code for this lecture**: `9.2PointersAndAddresses/main.cpp`.

---

## 9.3 `const` and pointers

In this lecture we answer a question the previous one raised: a pointer involves **two** things, the pointer itself and the data it points at. Either can be `const`, separately.

```
   const int*  p   ──►  the DATA is protected    "I may look, I may not write"
   int* const  p        the POINTER is fixed     "I always lead to the same place"
```

### Read it from the name, outwards

The reliable way to read a pointer declaration is to start at the name and read **right to left**:

```
   const int* p         p is a pointer to an int that is const
   int* const p         p is a const pointer to an int
   const int* const p   p is a const pointer to a const int
```

The four combinations, with what each allows:

```cpp
int reading{72};
int other{60};

int* free_pointer{&reading};              // 1. pointer and data both free
*free_pointer = 73;                       //    change the data
free_pointer = &other;                    //    change where it points

const int* read_only_view{&reading};      // 2. pointer to const data
read_only_view = &other;                  //    fine: the pointer can move
// *read_only_view = 0;                   //    error: cannot write through it

int* const fixed_pointer{&reading};       // 3. const pointer
*fixed_pointer = 74;                      //    fine: the data can change
// fixed_pointer = &other;                //    error: cannot repoint it

const int* const locked{&reading};        // 4. both const
// *locked = 0;                           //    error
// locked = &other;                       //    error
```

```
                         can I write through it?     can I repoint it?
   int* p                         yes                      yes
   const int* p                   no                       yes
   int* const p                   yes                      no
   const int* const p             no                       no
```

Try the lines that are commented out. Each one is a compile error, and reading the message once is worth more than any explanation.

### The case you will use every day: `const T*` parameters

A function that only **reads** through a pointer should say so with `const`:

```cpp
void print_reading(const int* reading) {
    std::println("reading is {}", *reading);     // *reading = 0; would not compile
}
```

This is the pointer version of the `const T&` parameters from 7.3: a promise to the caller that their data is safe, checked by the compiler. And it accepts **both** kinds of data:

```cpp
print_reading(&reading);          // a plain int

const int freezing{32};
print_reading(&freezing);         // a const int: also fine
```

### Why the other direction is refused

```cpp
// int* sneaky{&freezing};        // error: cannot convert 'const int*' to 'int*'
```

If that line were allowed, you could write through `sneaky` and change something that was declared `const`. The compiler refuses to **lose** a `const`. You can always go from "may write" to "may only read", and never back without an explicit cast. A cast (`const_cast`) will force it, but writing to an object that really was `const` is undefined behaviour. Do not.

### `const` restricts the view, not the data

```cpp
const int* view_of_reading{&reading};
reading = 80;
std::println("reading was changed directly, view_of_reading now sees {}", *view_of_reading);
```

```
reading was changed directly, view_of_reading now sees 80
```

`reading` itself is not `const`, so it can change, and every view of it sees the change. A `const int*` means "**I** will not change it through **this** pointer", not "nobody will".

**Code for this lecture**: `9.3PointersAndConst/main.cpp`.

---

## 9.4 Pointers and references as parameters

In this lecture we put pointers to work as function parameters, and see when a pointer is the better tool than the reference from 6.8.

### Two ways to swap

Both functions below swap the caller's two values.

```cpp
void swap_with_pointers(int* a, int* b) {
    int saved{*a};
    *a = *b;
    *b = saved;
}

void swap_with_references(int& a, int& b) {
    int saved{a};
    a = b;
    b = saved;
}
```

The call sites show the difference:

```cpp
swap_with_pointers(&morning, &evening);      // the caller writes & : the change is visible here
swap_with_references(morning, evening);      // looks like any other call
```

```
after swap_with_pointers:   morning = 75, evening = 68
after swap_with_references: morning = 68, evening = 75
```

With a pointer, the caller must hand over an address, which makes it obvious at the call that the function may change something. A reference hides that. This is one reason const references are the default and plain `&` is used sparingly (6.8).

### The real reason to use a pointer: "no answer" is possible

A reference must always refer to something. A pointer can say **"nothing"**, with `nullptr`. So a function that might not find what it is looking for can return a pointer to the element, or `nullptr`:

```cpp
const int* find_first_above(const std::vector<int>& readings, int limit) {
    for (const int& reading : readings) {
        if (reading > limit) {
            return &reading;        // points INTO the caller's vector
        }
    }
    return nullptr;
}
```

```cpp
const int* hot{find_first_above(readings, 70)};
if (hot != nullptr) {
    std::println("first reading above 70 is {}, at index {}", *hot, hot - readings.data());
}

const int* scorching{find_first_above(readings, 100)};
if (scorching == nullptr) {
    std::println("no reading above 100");
}
```

```
first reading above 70 is 71, at index 1
no reading above 100
```

The caller **must** check the result before following it. That is the cost, and also the honesty, of the design: the type says "this might be empty". (Later in the course you will meet `std::optional` and `std::expected`, which express "might be empty" with a type that is harder to misuse.)

### An optional output

A pointer parameter can also be **optional**: pass `nullptr` for any result you do not want.

```cpp
void summarize(const std::vector<int>& readings, int* lowest, int* highest);
```

```cpp
int lowest{0};
int highest{0};
summarize(readings, &lowest, &highest);          // both results
summarize(readings, nullptr, &just_highest);     // only the highest
```

Inside, `if (lowest != nullptr) { *lowest = low; }` skips the output nobody asked for. A reference parameter cannot be left out.

### Which one to use

```
   Must refer to something, always valid          →  reference
   May be absent (nullptr means "none")           →  pointer
   Needs to be pointed somewhere else later       →  pointer
   Only reads, large or not                       →  const reference (or const pointer)
```

### Never return the address of a local

```cpp
// const int* broken() {
//     int local{72};
//     return &local;        // dangling the moment the function returns
// }
```

`local` is destroyed when the function ends, so the caller receives the address of an object that no longer exists. It is the dangling pointer from 9.2 in its most common form, and it often appears to work, because the old bytes are still there for a while.

**Code for this lecture**: `9.4PointersAndReferencesAsParameters/main.cpp`.

---

## 9.5 Built-in arrays and decay

In this lecture we meet the array that C++ inherited from C, and the single most surprising thing about it: it cannot be passed to a function.

### A built-in array

```cpp
int readings[5]{68, 71, 69, 72, 70};
```

Five ints, side by side in memory. Unlike the `std::array` from 7.2, this one has no member functions, no bounds checking and no idea of its own size at run time. Still, in the scope where it is **declared**, the compiler knows everything about it:

```cpp
std::println("sizeof(readings)    = {}", sizeof(readings));                 // 20
std::println("sizeof(readings[0]) = {}", sizeof(readings[0]));              // 4
std::println("element count (old idiom) = {}", sizeof(readings) / sizeof(readings[0]));   // 5
std::println("element count (std::size) = {}", std::size(readings));                      // 5
```

`sizeof(array) / sizeof(element)` was the traditional way to count, and `std::size` is the modern one. A range-based `for` also works, because the compiler knows the size here:

```cpp
for (int reading : readings) { std::print("{} ", reading); }
```

### Decay

Now the trap. In almost every expression, **the name of an array turns into a pointer to its first element**. This is called **decay**, and it throws away the size.

```cpp
int* first{readings};                                    // no & needed: the array decayed
std::println("readings == &readings[0]: {}", readings == &readings[0]);    // true
```

```
   readings[5]                       first
   ┌────┬────┬────┬────┬────┐        ┌───────────┐
   │ 68 │ 71 │ 69 │ 72 │ 70 │ ◄──────│  address  │     a pointer to the first element,
   └────┴────┴────┴────┴────┘        └───────────┘     and nothing about the other four
```

### Why you cannot pass an array to a function

```cpp
void inside_the_function(int values[5]) {
    std::println("inside:  sizeof(values) = {}  (the size of a pointer, not of 5 ints)", sizeof(values));
}
```

```
outside: sizeof(readings) = 20
inside:  sizeof(values) = 8  (the size of a pointer, not of 5 ints)
```

Look at the declaration. It says `int values[5]`, but the compiler treats it as `int* values`: **the 5 is ignored**, and so is any other number. What the function receives is only the address of the first element. The array was never copied and its length was left behind. GCC and Clang warn about this very line:

```
warning: 'sizeof' on array function parameter 'values' will return size of 'int*' [-Wsizeof-array-argument]
```

### The honest signature

Since the size cannot travel with the array, C code passes it separately, as a pointer and a count:

```cpp
void print_all(const int* values, std::size_t count) {
    for (std::size_t i{0}; i < count; ++i) {
        std::print("{} ", values[i]);
    }
    std::println("");
}

print_all(readings, std::size(readings));
```

It works, but **nothing checks that `count` is right**. Pass a count that is too big and the function reads past the end of the array without a complaint. In 9.8 you will meet a type that welds the two values together.

### What a built-in array cannot do

```cpp
// int copy[5]{};  copy = readings;     does not compile: arrays cannot be assigned
// readings[5] = 0;                      compiles, undefined behaviour: one past the end
// readings[-1]                          compiles, undefined behaviour: before the start
```

The compiler will not warn about the last two, and the program may appear to work. That is what makes them dangerous, and why the project at the end of the chapter exists.

### Prefer `std::array`

The `std::array` from 7.2 has none of these problems. It copies, it knows its size, `at()` checks the index, and `std::to_array` converts a built-in array into one:

```cpp
auto modern{std::to_array(readings)};
auto copy{modern};
copy[0] = 0;
std::println("modern.size() = {}, modern[0] = {}, copy[0] = {}", modern.size(), modern[0], copy[0]);
```

```
modern.size() = 5, modern[0] = 68, copy[0] = 0
```

You will still meet built-in arrays: in older code, in string literals (9.7), and in `main(int argc, char* argv[])`. In your own new code, reach for `std::array` and `std::vector`.

**Code for this lecture**: `9.5CArraysAndDecay/main.cpp`.

---

## 9.6 Pointer arithmetic

In this lecture we do arithmetic on addresses, and discover that it is how the array indexing you already use really works.

### Adding 1 moves one element

```cpp
int readings[5]{68, 71, 69, 72, 70};
const int* first{readings};
const int* second{first + 1};
```

How far apart are `first` and `second` in memory? The program can measure it, using the `uintptr_t` trick from 8.2:

```cpp
auto first_address{reinterpret_cast<std::uintptr_t>(first)};
auto second_address{reinterpret_cast<std::uintptr_t>(second)};
std::println("first + 1 is {} bytes after first (sizeof(int) = {})", second_address - first_address, sizeof(int));
```

```
first + 1 is 4 bytes after first (sizeof(int) = 4)
```

Adding 1 to a pointer moves it by **one element**, not by one byte. The compiler multiplies by `sizeof(int)` for you, so `first + 3` is 12 bytes further on. Remember `[rdi + rcx*4]` from the assembly lab (8.12): that is this very calculation, written the way the CPU spells it.

```
   address:    1000   1004   1008   1012   1016
              ┌──────┬──────┬──────┬──────┬──────┐
   readings:  │  68  │  71  │  69  │  72  │  70  │
              └──────┴──────┴──────┴──────┴──────┘
                 ▲      ▲                   ▲
               first  first + 1           first + 4
```

### `[]` is pointer arithmetic with a nicer face

```cpp
std::println("*(first + 3) = {}, first[3] = {}", *(first + 3), first[3]);
```

```
*(first + 3) = 72, first[3] = 72
```

`first[3]` is defined to mean exactly `*(first + 3)`: step 3 elements, then follow. Every time you wrote `readings[i]` in this course, this is what happened.

### The one-past-the-end pointer

To describe a run of elements, a common idea is **two pointers**: where it starts, and where it stops. The stop is the address **just after the last element**:

```cpp
const int* const last{readings + 5};      // one PAST the final element
```

```
   first                                       last
     ▼                                           ▼
   ┌────┬────┬────┬────┬────┐
   │ 68 │ 71 │ 69 │ 72 │ 70 │                  (nothing here, we must not read it)
   └────┴────┴────┴────┴────┘
```

Forming that pointer is allowed. **Reading through it is not.** It exists so that "am I still inside?" is the simple test `p != last`, which also works for an **empty** run, where `first == last` from the start.

```cpp
for (const int* p{first}; p != last; ++p) {
    std::print("{} ", *p);
}
```

Walking backwards works too. Step first, then read, because `last` itself must not be read:

```cpp
for (const int* p{last}; p != first;) {
    --p;
    std::print("{} ", *p);
}
```

```
walking forward:  68 71 69 72 70
walking backward: 70 72 69 71 68
```

### Subtraction and comparison

Subtracting two pointers into the same array gives the number of **elements** between them, as a signed `std::ptrdiff_t`:

```cpp
std::ptrdiff_t count{last - first};
std::println("last - first = {} elements", count);       // 5
std::println("first < last: {}", first < last);          // true
```

### A function that takes a range

```cpp
int sum(const int* first, const int* last) {
    int total{0};
    for (const int* p{first}; p != last; ++p) {
        total += *p;
    }
    return total;
}
```

```
sum(first, last)        = 350
sum of the middle three = 212          // sum(first + 1, first + 4)
```

Any sub-range works, because a range is just two pointers. **Remember this shape.** In chapters 14 and 15 it comes back as the **iterator pair** that every standard algorithm takes: `std::sort(v.begin(), v.end())` is "from here, up to but not including there", exactly like this. An iterator is, in effect, a pointer with manners.

### The rules, and what breaks them

All of these are undefined behaviour, **even if you never read the result**:

```
   first + 6                     more than one past the end
   first - 1                     before the start
   &other_array[0] - first       subtracting pointers into two different arrays
```

The compiler will not stop you, and the program may run on happily. A sanitizer will (see the project).

**Code for this lecture**: `9.6PointerArithmetic/main.cpp`.

---

## 9.7 C strings

In this lecture we meet the text type that C++ inherited from C: not a type at all, but a **convention**, a run of characters ending in a zero. You will see it constantly in older code and in operating system interfaces.

### A string literal is an array with a zero at the end

```cpp
const char* label{"sensor-12"};
std::println("sizeof(\"sensor-12\") = {}", sizeof("sensor-12"));
std::println("std::strlen(label)  = {}", std::strlen(label));
```

```
sizeof("sensor-12") = 10
std::strlen(label)  = 9
```

`"sensor-12"` has nine visible characters, but the array has **ten** elements: the last is the **terminator**, the character with the numeric value 0, written `'\0'`. A C string has no stored length. The terminator **is** the length information, and `std::strlen` finds it by walking until it meets the zero:

```cpp
std::size_t my_strlen(const char* text) {
    const char* p{text};
    while (*p != '\0') {
        ++p;
    }
    return static_cast<std::size_t>(p - text);
}
```

That is pointer arithmetic from 9.6 again. You can see the terminator for yourself:

```cpp
for (std::size_t i{6}; i <= 9; ++i) { std::print("{} ", static_cast<int>(label[i])); }
```

```
45 49 50 0         // '-', '1', '2', and the terminator
```

### Text you can change

The characters of a string literal are **read-only** data, which is why the pointer type is `const char*`. To get text you can edit, copy it into a `char` array:

```cpp
char editable[16]{"sensor-12"};      // copies the 10 bytes, and zeroes the other 6
editable[7] = '4';
editable[8] = '2';
std::println("editable = {}", editable);       // sensor-42
```

The array must be large enough for the text **plus the terminator**. If the text does not fit, the program does not compile (for a literal like this). With C functions that copy text at run time, nobody checks.

### Gotcha: `==` compares addresses

```cpp
char twin[16]{"sensor-12"};
char other_twin[16]{"sensor-12"};
const char* twin_address{twin};
const char* other_twin_address{other_twin};

std::println("same text, same address?  {}", twin_address == other_twin_address);
std::println("strcmp(twin, other) == 0: {}", std::strcmp(twin, other_twin) == 0);
std::println("string_view comparison:     {}", std::string_view{twin} == std::string_view{other_twin});
```

```
same text, same address?  false
strcmp(twin, other) == 0: true
string_view comparison:     true
```

Two `const char*` hold the same letters at two different places, and `==` on pointers compares the **places**. To compare the **text**, use `std::strcmp` (zero means equal), or wrap both in a `std::string_view` (7.9), which stores a pointer **and** a length and compares the letters.

### C string functions trust you completely

```cpp
// std::strcpy(editable, "a-very-long-sensor-name");
```

That line compiles. It copies 24 bytes into a 16-byte array and overwrites whatever sits after it: a classic **buffer overflow**, the source of countless security holes. Never do it. `std::string` grows to fit, and it is what your own code should use:

```cpp
std::string name{label};
name += "-north";
std::println("std::string: {} (size {})", name, name.size());      // sensor-12-north (size 15)
```

Old C functions want a `const char*`. A `std::string` can hand you one:

```cpp
std::puts(name.c_str());
```

The pointer from `c_str()` is valid only while the string is alive and unchanged. Use it for the call, and do not keep it.

### Command-line arguments

The most common place a C string reaches a modern program is `main`:

```cpp
int main(int argc, char* argv[])
```

`argc` counts the arguments, and `argv` is an array of C strings. `argv[0]` is the program itself, so `argc` is at least 1.

```cpp
for (int i{0}; i < argc; ++i) {
    std::println("argv[{}] = {}", i, argv[i]);
}
```

Run the program as `9.7CStrings.exe alpha "two words"`:

```
argc = 3
argv[0] = D:\Sandbox\_build\scratch\w4\9.7CStrings.exe
argv[1] = alpha
argv[2] = two words
```

The quotes in the second argument made it one argument, not two: your shell, not your program, did that. In an IDE you set them in the run configuration of the program (look for "command line arguments" or "args" in its debug or run settings).

**Code for this lecture**: `9.7CStrings/main.cpp`.

---

## 9.8 `std::span`

In this lecture we meet the modern answer to the problem of 9.5: a type that carries the pointer **and** the length together.

### The idea

```
   const int*, std::size_t         one thing, std::span<const int>
   ───────────────────────         ────────────────────────────────
   print_all(readings, 5)          print_all(readings)
   two values that can disagree    a pointer and a count that cannot
```

A **`std::span`** (from `<span>`) is a view of a contiguous run of elements: a pointer and a count, packaged as one type. Like `std::string_view` from 7.9, it **owns nothing and copies nothing**. It looks at memory that belongs to somebody else.

```cpp
double average(std::span<const int> values) {
    if (values.empty()) {
        return 0.0;
    }

    int total{0};
    for (int value : values) {
        total += value;
    }
    return static_cast<double>(total) / static_cast<double>(values.size());
}
```

The `const` in `span<const int>` is the same promise as `const int*`: the function will only read.

### One function, every container

```cpp
int built_in[5]{68, 71, 69, 72, 70};
std::array<int, 5> fixed{68, 71, 69, 72, 70};
std::vector<int> growable{68, 71, 69, 72, 70};

std::println("built-in array: {:.1f}", average(built_in));
std::println("std::array:     {:.1f}", average(fixed));
std::println("std::vector:    {:.1f}", average(growable));
```

```
built-in array: 70.0
std::array:     70.0
std::vector:    70.0
```

A built-in array, a `std::array` and a `std::vector` all convert to a span on their own. This is the answer to "which parameter type do I give a function that reads a run of values?": **`std::span<const T>`**. It avoids the decay trap of 9.5 (the length is kept), and it avoids tying the function to one container.

### Slicing without copying

```cpp
std::span<const int> all{growable};
all.first(3)        // the first 3 elements:         68 71 69
all.last(2)         // the last 2:                   72 70
all.subspan(1, 3)   // 3 elements starting at index 1: 71 69 72
```

```
first(3)      = 3 elements, average 69.3
last(2)       = 2 elements, average 71.0
subspan(1, 3) = 3 elements, average 70.7
```

Each of these is a **new view over the same elements**. Nothing is copied. That is also how you apply a function to only part of a container.

### Writing through a span

A span without `const` lets the function change the caller's elements:

```cpp
void add_offset(std::span<int> values, int offset) {
    for (int& value : values) {
        value += offset;
    }
}

add_offset(growable, 10);                                // every element
add_offset(std::span<int>{growable}.first(3), -10);      // only the first three, back again
```

```
after add_offset(growable, 10): front = 78, back = 80
after adjusting only the first three: 68 71 69 82 80
```

### From the old pair

An existing `(pointer, count)` pair converts directly:

```cpp
const int* pointer{fixed.data()};
std::span<const int> from_pair{pointer, 4};        // the first 4 elements
```

`from_pair.size()` is 4, and `from_pair.size_bytes()` is 16.

### Gotcha: a span dangles like a pointer

```cpp
// std::span<const int> view{growable};
// growable.push_back(75);         // may reallocate: moves every element elsewhere
// view[0];                        // possibly reading freed memory
```

A span is a pointer and a count, so it has a pointer's weakness. If the vector has to grow, it allocates new storage, moves its elements and **frees the old storage**, and every span over the old storage now looks at freed memory. Treat a span as a short-lived way to **pass** data to a function, and do not keep one while the container changes size. (The project's `stale-pointer` case is exactly this bug.)

```
   what a span can be made from            what it is NOT
   ───────────────────────────             ─────────────────────────────
   built-in array, std::array,             a container (it cannot grow or shrink)
   std::vector, a pointer and a count      an owner (it frees nothing)
                                           safe to keep after the data moves
```

**Code for this lecture**: `9.8Span/main.cpp`.

---

## 9.9 Dynamic memory: `new` and `delete`

In this lecture we look at the other kind of memory, the kind you request yourself, and why this lecture is mostly a warning about it.

### Two kinds of memory

Every variable so far lived on the **stack** (8.4): created when its scope began, destroyed automatically when the scope ended. The other kind is the **heap**: memory you ask for explicitly, which stays until you explicitly give it back.

```
   STACK                                     HEAP
   ─────                                     ────
   int a{72};                                new int{72}
   created at the declaration                created when you ask
   destroyed at the closing brace            destroyed ONLY when you say so
   size known when you write the code        size can be decided while running
   automatic                                 manual
```

The heap exists for the cases the stack cannot handle: data whose size is only known at run time, or data that must outlive the function that made it.

### `new` and `delete`

```cpp
int* one{new int{72}};
std::println("*one = {}", *one);

delete one;         // give the memory back. Exactly one delete per new.
one = nullptr;      // so a leftover use is an obvious crash, not silent garbage
```

`new int{72}` finds room for an `int` on the heap, stores 72 there and returns the **address**, so it goes in a pointer. `delete` gives the memory back. Setting the pointer to `nullptr` afterwards means a stray use later is a clear failure, instead of a read of memory that now belongs to somebody else.

### Arrays: `new[]` and `delete[]`

```cpp
std::size_t count{6};
int* readings{new int[count]{}};      // the {} sets every element to 0

for (std::size_t i{0}; i < count; ++i) {
    readings[i] = 60 + static_cast<int>(i) * 3;
}

delete[] readings;       // new[] pairs with delete[], never plain delete
readings = nullptr;
```

```
heap readings: 60 63 66 69 72 75
```

The size `count` could come from a file or the user, which is the reason to use the heap. And the rule to remember is the **pairing**: `new` goes with `delete`, `new[]` goes with `delete[]`. Mixing them is undefined behaviour.

### `delete` runs the destructor

For an object that has cleanup to do, `delete` runs that cleanup, and then frees the memory. To see it, we use a small type with a **destructor**, a function that runs automatically when an object dies. (You will write your own in chapter 10. Here it only prints a message.)

```cpp
struct Probe {
    std::string name;

    ~Probe() {
        std::println("  probe {} shut down", name);
    }
};

Probe* probe{new Probe{"north"}};
std::println("  using probe {}", probe->name);
delete probe;
std::println("after delete");
```

```
  using probe north
  probe north shut down
after delete
```

`probe->name` is shorthand for `(*probe).name`: follow the pointer, then pick the member. The message appears at the moment of `delete`, before "after delete". Remember this pattern: **cleanup runs when the object dies**, and here that moment is entirely up to you.

### Why we avoid it

Everything above works. The trouble is what you must do **correctly, every time, on every path**:

```
   leak             new without any delete: the memory is never returned
   double free      delete the same pointer twice
   use after free   read or write through a pointer after delete
   wrong delete     delete on an array, or delete[] on a single object
```

All four compile without a warning. Most of them look as if they work. And they all share one root: a raw pointer says **where** something is, and says nothing about **who must clean it up**.

It gets worse with early exits. If a `return` or an exception happens between the `new` and the `delete`, the `delete` is skipped and the memory leaks. In real code, with many paths, that is easy to get wrong and hard to find.

### The alternative you already know

```cpp
std::vector<int> safer(count);
for (std::size_t i{0}; i < count; ++i) {
    safer[i] = 60 + static_cast<int>(i) * 3;
}
```

Same job, no `new`, no `delete`. A `std::vector` does the `new[]` and `delete[]` itself, in its destructor, so the memory is freed whenever the vector dies, however the scope is left. That idea, **an object whose destructor does the cleanup**, is called **RAII**, and it is the foundation of modern C++ memory management. The next two lectures give you the same safety for a single heap object, with **smart pointers**.

> **Rule for your own code: do not write `new` and `delete`.** Use `std::vector` for collections, and the smart pointers below for single objects. Raw `new` and `delete` are for understanding old code, and for the rare case where you are building one of those tools yourself.

**Code for this lecture**: `9.9NewAndDelete/main.cpp`.

---

## 9.10 `std::unique_ptr`

In this lecture we meet the smart pointer that should be your default way to own a heap object: it deletes the object for you, and it makes the question "who owns this?" a matter of the type.

### An owner that cleans up

```cpp
#include <memory>

{
    auto probe{std::make_unique<Probe>("north")};
    std::println("using {}", probe->name);          // -> and * work like a raw pointer
}   // no delete anywhere: the destructor message appears right here
std::println("scope ended");
```

```
using north
  probe north shut down
scope ended
```

A **`std::unique_ptr<T>`** holds a pointer to a heap object and **deletes it when the `unique_ptr` itself is destroyed**. `std::make_unique<T>(arguments)` creates both the object and the owner in one step. There is no `new` and no `delete` in your code, and the cleanup happens at the closing brace on every path, including early returns and exceptions.

It costs nothing extra: a `unique_ptr` is the size of a raw pointer, and `->` and `*` work exactly as before.

### Exactly one owner

The word "unique" is the rule. At any moment, exactly one `unique_ptr` owns an object, so **copying one is not allowed**:

```cpp
// auto copy{probe};          // does not compile
```

What you can do is **move** ownership from one to another with `std::move`:

```cpp
auto first_owner{make_probe("east")};
auto second_owner{std::move(first_owner)};
std::println("first_owner is empty: {}", first_owner == nullptr);       // true
std::println("second_owner has: {}", second_owner->name);              // east
```

`std::move` is a way of saying "I am done with this one, hand it over". After the move, `first_owner` is empty (it holds `nullptr`) and `second_owner` owns the probe. Chapter 10 explains what a move really is. For now, it is the way ownership changes hands.

```
   before the move                    after the move
   first_owner  ──► Probe east        first_owner  = nullptr
   second_owner = nullptr             second_owner ──► Probe east
```

### Returning one from a function

A function that creates an object for its caller returns the `unique_ptr`. Nothing is copied: ownership simply goes to the caller.

```cpp
std::unique_ptr<Probe> make_probe(const std::string& name) {
    return std::make_unique<Probe>(name);
}
```

### Lending and giving away

Most functions do not need to own anything. They need to **look** at the object. For those, take a plain reference:

```cpp
void inspect(const Probe& probe) {            // lend: only looks
    std::println("  inspecting {}", probe.name);
}

void retire(std::unique_ptr<Probe> probe) {   // give away: takes ownership
    std::println("  retiring {}", probe->name);
}   // probe dies here, and takes the Probe with it
```

```cpp
inspect(*second_owner);                 // lend: we keep ownership
retire(std::move(second_owner));        // give away: the probe is destroyed inside retire
```

```
  inspecting east
  retiring east
  probe east shut down
back in main, second_owner is empty: true
```

The signature **tells the story**. A `const Probe&` parameter means "borrowed, will not outlive the call". A `std::unique_ptr<Probe>` parameter, taken by value, means "I take ownership". Use the first for almost everything, and the second only when the function really must own the object.

### Arrays

There is an array form, which calls `delete[]` for you:

```cpp
std::size_t count{5};
auto readings{std::make_unique<int[]>(count)};          // every element starts at 0
readings[4] = 72;
```

For a growable collection, prefer `std::vector`. The array form is for when you need a fixed block and a raw interface to it.

### `get()` and `reset()`

```cpp
int* raw{readings.get()};         // the raw pointer, for an old API that wants one
```

`get()` lends you the raw pointer. It is **still owned** by the `unique_ptr`: never `delete` it, and never keep it beyond the owner's life. And `reset()` destroys the current object right away:

```cpp
auto temporary{make_probe("south")};
temporary.reset();                // destructor runs now
std::println("temporary is empty: {}", temporary == nullptr);       // true
```

### The parameter and return cheat sheet

```
   I only look at it                  const T&
   I change it, caller keeps it       T&
   it may be absent                   a raw pointer: T* (borrowed, never deleted)
   I take ownership                   std::unique_ptr<T>, by value
   I create it for the caller         return std::unique_ptr<T>
```

**Code for this lecture**: `9.10UniquePtr/main.cpp`.

---

## 9.11 `std::shared_ptr` and `std::weak_ptr`

In this lecture we deal with the case `unique_ptr` cannot handle: an object that several parts of a program use, where nobody can say in advance which of them is the last.

### Owners that count

A **`std::shared_ptr<T>`** is a smart pointer that **may be copied**. Every copy is another owner, and the object keeps a **count** of its owners. The object is destroyed when the **last** owner goes away.

```cpp
auto probe{std::make_shared<Probe>("north")};
std::println("owners: {}", probe.use_count());           // 1
```

The scenario: two screens show the same probe. Neither is "the" owner, and the probe must live as long as the longest-lived screen.

```cpp
struct Dashboard {
    std::string title;
    std::shared_ptr<Probe> probe;
};

{
    Dashboard wall{"wall screen", probe};
    Dashboard phone{"phone", probe};
    std::println("owners with two dashboards: {}", probe.use_count());     // 3
}
std::println("owners after both dashboards are gone: {}", probe.use_count());    // 1
```

```
owners: 1
owners with two dashboards: 3
owners after both dashboards are gone: 1
```

```
   probe (main)  ──┐
   wall.probe    ──┼──►  Probe north        count = 3
   phone.probe   ──┘
```

Each `Dashboard` holds a copy of the `shared_ptr`, which raised the count. When the dashboards died, their copies died with them and the count dropped back to 1. Only when it reaches **0** is the `Probe` destroyed. `std::make_shared<T>` is the way to create one, as `make_unique` was.

### `weak_ptr`: watching without owning

Sometimes you want to **look at** a shared object **without keeping it alive**: a cache, an observer, a link back to a parent. That is a **`std::weak_ptr<T>`**. It points at the object but does **not** count as an owner.

```cpp
std::weak_ptr<Probe> watcher{probe};
std::println("owners (a watcher does not count): {}", probe.use_count());     // still 1

if (auto locked{watcher.lock()}) {
    std::println("watcher found the probe {}, owners now {}", locked->name, probe.use_count());   // 2
}
```

`lock()` is how you use it: it returns a **temporary `shared_ptr`** if the object is still alive, or an empty one if it is gone. Inside the `if` the object is guaranteed to stay, because the temporary owner is holding it. The count went up to 2 only while `locked` existed.

```cpp
probe.reset();                                           // the last owner lets go
std::println("watcher expired: {}", watcher.expired());  // true
```

```
releasing the last owner:
  probe north shut down
watcher expired: true
lock() gave an empty pointer, nothing to use
```

The `weak_ptr` is safe in exactly the way a raw pointer is not: it **knows** whether the object is still there.

### The cycle problem

Counting has one famous flaw. Suppose two nodes each hold a `shared_ptr` to the other:

```
   a ──► Node a ◄──────────┐
            │              │         a's count: 2 (the variable a, and b's partner)
            ▼              │         b's count: 2 (the variable b, and a's partner)
          Node b ──────────┘
```

When the variables `a` and `b` go out of scope, each count drops from 2 to **1**. Each node is still owned by the **other**, so neither count ever reaches 0, and neither node is ever destroyed. It is a **leak**, with no crash and no message. The program runs the two versions side by side:

```cpp
leaky_pair();     // partner is a shared_ptr
safe_pair();      // partner is a weak_ptr
```

```
leaky_pair():
  (no messages: both nodes leaked)

safe_pair():
  SafeNode b destroyed
  SafeNode a destroyed
```

The leaky version printed **nothing**: the destructors never ran. The fix is in the design. For a pair like this, one direction is "owns" and the other is "merely knows about", and the second should be a `weak_ptr`. A weak link does not hold a count, so the cycle cannot form.

### Which one to use

```
   Default                              std::unique_ptr (9.10): one owner, zero overhead
   Ownership truly shared               std::shared_ptr: a count, a little overhead
   Look without owning                  std::weak_ptr: a back reference, an observer, a cache
   Just need to look, call is short     a reference, or a raw pointer you do not delete
```

Reach for `shared_ptr` only when you can name the reason that more than one party must own the object. Using it "just in case" hides the design question of who owns what, and brings cycles with it.

**Code for this lecture**: `9.11SharedAndWeakPtr/main.cpp`.

---

## 9.12 Project: the memory detective

Every lecture in this chapter ended with some version of "the compiler will not stop you". An out-of-bounds write, a read of freed memory, a leak: all of them compile, most of them even **appear to work**. This project is about the tools that **do** catch them.

The program is a weather station with **seven planted memory bugs**, one per case. Each case has a buggy function and a fixed one, side by side in `9.12ProjectMemoryDetective/main.cpp`. You choose a case on the command line:

```
detective heap-overflow            the buggy version
detective heap-overflow fixed      the corrected version
```

Your job is a detective's: **read the buggy function and find the mistake yourself first**, then run it and see whether the tool agrees.

| Case | The bug |
|---|---|
| `heap-overflow` | fills an 8-element `new[]` array with `i <= capacity`, one slot too far |
| `stack-overflow` | sums a local array with `i <= 5`, reading a sixth element |
| `use-after-free` | reads through a pointer after `delete` |
| `double-free` | two pointers to one allocation, both deleted |
| `leak` | allocates in a loop and never frees |
| `stale-pointer` | keeps a pointer into a `std::vector`, then lets the vector grow |
| `signed-overflow` | adds readings in an `int` that is too small |

### First, without any tool

Build it plainly and run each buggy case. This is what you would see if you never used a sanitizer.

```
cl /nologo /std:c++latest /EHsc /MD main.cpp /Fe:plain.exe        (MSVC)
g++ -std=c++23 main.cpp -o detective_plain                         (GCC or Clang, Linux)
```

| Case | What the plain build does (Windows / Linux) |
|---|---|
| `heap-overflow` | prints `last slot holds 67` and exits normally, in both |
| `stack-overflow` | prints a **wrong total**: `33109` on Windows, and on Linux it happened to print the right one, `350` |
| `use-after-free` | prints `latest = 72`, then **garbage** (`-2040678880`, `64406`) |
| `double-free` | **crashes**: exit code `0xC0000374` on Windows, `free(): double free detected` on Linux |
| `leak` | prints three lines. Nothing visible happens at all |
| `stale-pointer` | prints `68` on Windows, which is **correct by luck**, and `179455` on Linux |
| `signed-overflow` | prints `total = -1794967296`, a negative sum of positive numbers |

Look at that list. Only one case failed loudly, and two of them gave a plausible answer. A different compiler, a different day, or a different optimisation level will change **all** of this, because every one of these is **undefined behaviour**: the language does not say what happens, so anything can. A bug that "works on my machine" is the worst kind.

### What a sanitizer is

A **sanitizer** is a checker that the compiler builds into your program. You add one flag, and the compiler:

- inserts a **check around every memory access**: "is this address inside a live object?";
- replaces `new` and `delete` with versions that put **forbidden zones** (red zones) around every allocation, and **keep freed memory off-limits** instead of reusing it at once.

When your program touches memory it should not, the check fires, and the sanitizer **stops the program and prints a report** with the exact line. The price is a program that runs a couple of times slower and uses more memory, so a sanitizer build is for **testing**, never for shipping.

The two you will use:

- **AddressSanitizer (ASan)**: out-of-bounds accesses, use after free, double free (and, on Linux, leaks).
- **UndefinedBehaviorSanitizer (UBSan)**: signed overflow, out-of-range array indexes, and more. Available with GCC and Clang, not with MSVC.

### Build with a sanitizer

#### MSVC (Windows)

```powershell
cl /nologo /std:c++latest /EHsc /MD /W4 /Zi /fsanitize=address main.cpp /Fe:detective.exe
```

- **`/fsanitize=address`** turns AddressSanitizer on.
- **`/Zi`** keeps the information that lets the report name files and line numbers. Without it, you get addresses and no lines.
- Run it from the **Developer PowerShell for VS**, which also puts the sanitizer's runtime DLL where the program can find it. If `cl` says it does not support `/fsanitize=address`, open the Visual Studio Installer, choose *Modify*, and tick the **C++ AddressSanitizer** component.

#### Linux, GCC or Clang (in the containers)

```sh
g++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer main.cpp -o detective
clang++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer main.cpp -o detective
```

- **`-fsanitize=address,undefined`** turns on both sanitizers.
- **`-g`** keeps line numbers for the report, like `/Zi`.
- **`-fno-omit-frame-pointer`** keeps the stack traces complete.

> **The MinGW compilers have no sanitizers.** The GCC and Clang in `C:\mingw64\bin` do not include the sanitizer runtime: asking for `-fsanitize=address` ends in a linker error such as `cannot find -lasan`. For this project use MSVC on Windows, or the Linux containers.

#### With CMake

The project's `CMakeLists.txt` has a switch, on by default:

```sh
cmake -S . -B build -G Ninja                           # sanitizers on
cmake -S . -B build -G Ninja -DDETECTIVE_SANITIZE=OFF  # a plain build
```

On MSVC it also removes `/RTC1` (the run-time checks that Debug builds add), because they cannot be combined with `/fsanitize=address`, and turns off the incremental linker, which the sanitizer does not support. Read those lines: they are what you add to a project of your own.

### How to read a report

Run the first case:

```powershell
.\detective.exe heap-overflow
```

```
=================================================================
==27120==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x118ad58a0030 at pc 0x7ff735d3114b
WRITE of size 4 at 0x118ad58a0030 thread T0
    #0 0x7ff735d3114a in heap_overflow_buggy(void) ...\main.cpp:35
    #1 0x7ff735d3433a in main ...\main.cpp:219
    #2 0x7ff735dd5ebe in invoke_main ...\exe_common.inl:78
    ...

0x118ad58a0030 is located 0 bytes after 32-byte region [0x118ad58a0010,0x118ad58a0030)
allocated by thread T0 here:
    #0 0x7ff735dd4d7e in operator new[](unsigned __int64) ...
    #1 0x7ff735d31091 in heap_overflow_buggy(void) ...\main.cpp:32
```

Every report has the same parts:

1. **The first line is the verdict**: `heap-buffer-overflow`. It names the **kind** of bug.
2. **`WRITE of size 4`**: what the faulty access was (a read or a write, and how many bytes).
3. **The stack of the faulty access**: `#0` is where it happened. Read down until you reach the **first line in your own file**. Here it is `main.cpp:35`, the `log[i] = ...` line, called from `main.cpp:219`.
4. **"located 0 bytes after 32-byte region"**: where the bad address is, relative to the block it fell off. 32 bytes is 8 ints, and the access is exactly **0 bytes after** the block: one element past the end. A classic off-by-one.
5. **"allocated by"**: the stack of the `new[]` that made that block (`main.cpp:32`). For use-after-free reports there is a "freed by" part too, so you see all three moments: the allocation, the free, and the bad use.

On the GCC and Clang side the same report looks nearly identical, with the same words. The tool gives you **the line, the kind and the history** that an hour of staring at the code might not.

### The cases

Run each buggy case, read the report, find the line, check against the fixed function, then run it again with `fixed`.

#### 1. `heap-overflow` (`main.cpp:35`)

`for (i = 0; i <= capacity; ++i)` writes `log[8]` in an array of 8. The report is the one above: **`heap-buffer-overflow`, WRITE, 0 bytes after a 32-byte region.** The fix is `<` instead of `<=`. Every `<=` against a size is worth a second look.

#### 2. `stack-overflow` (`main.cpp:62`)

The same mistake on a local array: `stack-buffer-overflow`, a **READ** of size 4. The stack is checked too, not only the heap. On GCC and Clang, UndefinedBehaviorSanitizer speaks first:

```
main.cpp:62:28: runtime error: index 5 out of bounds for type 'int [5]'
```

The fix removes the index altogether: `for (int reading : readings)` cannot go past the end.

#### 3. `use-after-free` (`main.cpp:88`)

```
ERROR: AddressSanitizer: heap-use-after-free on address ...
READ of size 4 at ...
    #0 ... in use_after_free_buggy() ...main.cpp:88
```

The memory was given back by `delete latest;` and then read. The report shows where it was **freed** and where it was **allocated** below. The fixed version sets the pointer to `nullptr` after `delete` and checks it. Better still, 9.10 gives a way to never have the stale pointer at all.

#### 4. `double-free` (`main.cpp:115`)

```
ERROR: AddressSanitizer: attempting double-free on 0x120f611a0030 in thread T0:
    #1 ... in double_free_buggy() ...main.cpp:115
```

`backup` was a second **name** for the same memory, not a second reading, and both were deleted. The fixed version has exactly one **owner** (`std::unique_ptr`) and gives out a borrowed raw pointer that is never deleted. That is the ownership idea of 9.10, doing its job.

#### 5. `leak` (`main.cpp:132`)

This one needs a different tool on each platform, and **AddressSanitizer on Windows does not report leaks**: the plain-ASan MSVC build just prints its three lines. On **Linux** the same sanitizer includes **LeakSanitizer**, which reports when the program exits:

```
ERROR: LeakSanitizer: detected memory leaks

Direct leak of 12 byte(s) in 3 object(s) allocated from:
    #1 0x0000004074d0 in leak_buggy() /tmp/.../main.cpp:132
    #2 0x0000004094fc in main /tmp/.../main.cpp:233
```

12 bytes in 3 objects: three `int`s that nobody freed, allocated at line 132. On **Windows** you use a different mechanism, the Debug runtime. Build the **Debug** way (`/MDd` and `_DEBUG`, which the project's code is ready for):

```powershell
cl /nologo /std:c++latest /EHsc /MDd /W4 /Zi /D_DEBUG main.cpp /Fe:detective_debug.exe
.\detective_debug.exe leak
```

```
Detected memory leaks!
Dumping objects ->
main.cpp(132) : {224} normal block at 0x0000017014B6DA90, 4 bytes long.
 Data: <>   > 3E 00 00 00
main.cpp(132) : {223} normal block at 0x0000017014B6D490, 4 bytes long.
 ...
Object dump complete.
```

Three blocks of 4 bytes, each with the **file and line** that allocated it, and the bytes that were in it (`3E`, `3D` and `3C` are 62, 61 and 60: the three samples). That output comes from the few lines at the top of `main.cpp` that include `<crtdbg.h>` and from the `_CrtSetDbgFlag` call in `main`. And a third option on Linux, with no special build at all, is **valgrind** (`apt-get install valgrind` in the container): `valgrind --leak-check=full ./detective_plain leak` reports `definitely lost: 12 bytes in 3 blocks`.

The fix is `std::make_unique`, which frees at the end of each pass.

#### 6. `stale-pointer` (`main.cpp:153`)

```
ERROR: AddressSanitizer: heap-use-after-free on address ...
READ of size 4 at ...
    #0 ... in stale_pointer_buggy() ...main.cpp:153
```

This is the **span lesson of 9.8**, caught red-handed. `first` pointed into the vector's storage. `push_back` found the vector full, allocated bigger storage, moved the elements and **freed the old block**, and `first` kept looking at it. On Windows the plain build printed `68`, which is exactly what the freed block still contained: a bug that gave the **right answer** by luck. The fix takes the address **after** the vector has grown, or just uses an index.

#### 7. `signed-overflow` (`main.cpp:174`)

```
main.cpp:174:11: runtime error: signed integer overflow: 2000000000 + 500000000 cannot be represented in type 'int'
```

This is **undefined behaviour sanitizer** territory, which exists on GCC and Clang. MSVC has no such sanitizer: the AddressSanitizer build runs the case without a word and prints `total = -1794967296`. The fix is a wider type, `std::int64_t`, which holds `2'500'000'000` without trouble.

### The fixed versions run clean

```powershell
.\detective.exe heap-overflow fixed         # exit code 0, no report
```

Run all seven with `fixed` under the sanitizer: all seven finish with exit code 0 and print nothing from the tools. That is what "the sanitizer is happy" looks like.

### What catches what

| Bug | MSVC `/fsanitize=address` | MSVC Debug runtime | GCC / Clang `-fsanitize=address,undefined` | valgrind (Linux) |
|---|---|---|---|---|
| heap overflow | yes | at `delete`, maybe | yes | yes |
| stack overflow | yes | no | yes | no |
| use after free | yes | no | yes | yes |
| double free | yes | yes | yes | yes |
| leak | **no** | **yes** | yes (LeakSanitizer) | yes |
| signed overflow | no | no | yes (UBSan) | no |

Take the table as a map, not a guarantee: the right habit is to run your tests under **both** a sanitizer build and, where you can, a second tool.

### Gotchas

- **A sanitizer stops at the first problem.** Fix it, run again, and read the next report. That is how the assignment's exercise 8 works.
- **No `-g` or `/Zi`, no line numbers.** The report is still correct but much harder to read.
- **Do not mix them:** ASan and valgrind cannot run together, so valgrind needs a plain build. And on MSVC, ASan and the Debug-runtime leak report are two separate builds.
- **Not for release builds.** The program is slower and bigger. Use sanitizers in tests and in continuous integration.
- **A plain Visual Studio Debug build can also notice some of these.** For example, the debug heap checks the guard bytes around a block when it is freed, and may stop the program with a "Debug Error" dialog about heap corruption. (When we ran a sanitizer-free Debug build of `heap-overflow` from a script, it never finished, most likely waiting on a dialog box that nobody could click.) That is helpful in the IDE, but it only checks at certain moments, and it does not name the faulty line the way a sanitizer does.

### What to take away

```
   compiler        finds mistakes in how you WROTE the code
   sanitizer       finds mistakes in what the program DOES
   plain run       finds nothing, and may even give the right answer
```

You now have the answer to every "the compiler will not stop you" in this chapter: a build flag that does. Make it a habit. **Whenever a program uses pointers, raw arrays or manual memory, run it under a sanitizer before you trust it.** And the best bug is the one you cannot write: after this project, notice how many of the seven fixes were "use a `std::vector`", "use a `std::unique_ptr`", or "use a range-based `for`".

**Code for this project**: `9.12ProjectMemoryDetective/main.cpp` (the seven cases), `CMakeLists.txt` (the sanitizer switch), and one script per environment (`build-msvc.ps1`, `build-linux-gcc.sh`, `build-linux-clang.sh`) that runs every case, so you can compare with what you typed.

---

## 9.13 Assignment

Eight small jobs for the weather station, in one program: swapping with pointers and references, searching and reversing with pointer arithmetic, one function for every container with `std::span`, C strings, owning pointers, shared ownership, and finally a bug hunt using the sanitizers from the project. `main.cpp` has the eight stubbed exercises, each with its problem statement and a sample run in a comment; `main_solution.cpp` solves all eight. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `swap_with_pointers()` / `swap_with_references()` | `T*` and `T&` parameters, `&` at the call site, `*` inside |
| 2 | `find_max()` | `const int*` range `[first, last)`, pointer `++`, `nullptr` as "no answer", pointer subtraction for the index |
| 3 | `reverse_in_place()` | two pointers moving toward each other, one-past-the-end, `std::swap` |
| 4 | `average()` / `clamp_all()` | `std::span<const int>` and `std::span<int>`, one function for a built-in array, `std::array` and `std::vector`, `first(n)` |
| 5 | `count_char()` / `shout()` | C strings, the `'\0'` terminator, walking with a pointer, `std::toupper` and the `unsigned char` cast, why a literal is `const` |
| 6 | `make_log()` / `make_probe()` / `retire()` | `std::make_unique<int[]>`, `std::unique_ptr<T>`, returning one, `std::move`, watching the destructor run |
| 7 | shared dashboards | `std::make_shared`, `use_count()`, `std::weak_ptr`, `expired()`, `reset()` |
| 8 | hunt the bugs | build with a sanitizer, read two reports (an out-of-bounds read, then a leak), then rewrite the function to return `std::unique_ptr<int[]>` |

The rule of the assignment: **no `new` and no `delete` in your answers.** Everything that needs memory goes through the smart pointers.

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole chapter, including what the sanitizers in the project can and cannot see.

After this chapter the student can read and write code that uses pointers, raw arrays and C strings, knows why most of it should be a reference, a span, a vector or a smart pointer instead, and has a way to prove that a program's memory handling is sound. The next chapter builds on all of it: a **class** that owns its memory.
