# Classes

Until now, a program was variables and functions kept side by side. A `std::vector` of readings in one place, a function that averages them in another, and nothing but your own discipline making sure that the function is called with the right vector. That works for small programs and falls apart in large ones.

A **class** is the tool for the next step: it **bundles data together with the functions that work on it**, and it lets you **hide** the data, so that only those functions can change it.

```
   free functions and loose data                a class
   ─────────────────────────────                ───────
   std::vector<double> readings;                class ReadingLog {
   double average(const std::vector<double>&);      public:   add(), average()      ← what you can do
   void add(std::vector<double>&, double);          private:  the data             ← how it is kept
                                                };
   anyone can change readings, in any way       only add() can change the data, and it keeps the rules
```

You have been using classes since chapter 3: `std::string`, `std::vector` and `std::unique_ptr` are all classes someone wrote. This chapter is about **writing your own**, and about the ideas that make them trustworthy: **invariants** (rules a class always keeps), **constructors and destructors** (a guaranteed start and a guaranteed end of an object's life), and **copying and moving** (what it means to duplicate or hand over an object).

Two classes carry the chapter. A `Sensor` shows the basics, and a `ReadingLog` is the class that **owns its memory** that 9.13 promised: it is where destructors, copies and moves become necessary. The project at the end brings back the image writer from chapter 6 and turns it into a `Canvas`.

---

## 10.2 From struct to class

In this lecture we see why a plain `struct` is not enough once data has rules, and what a class does about it.

### The problem: nothing stops nonsense

A weather station sensor has a **calibration offset**, a small correction in degrees that is added to every raw reading. A sensor with an offset of 400 degrees is useless. With a `struct`, nothing prevents it:

```cpp
struct PlainSensor {
    std::string name;
    double offset;          // meant to stay between -5 and +5
};

PlainSensor plain{"sensor-3", 0.0};
plain.offset = 400.0;       // accepted, silently
```

```
PlainSensor sensor-3 has offset 400 (and nobody complained)
```

Every line of code that ever touches `offset` would have to remember the rule. One forgetful line anywhere in the program, and the sensor is broken.

### The fix: hide the data, guard the door

A **class** declares the data **private** and offers **public** functions as the only way in:

```cpp
class Sensor {
public:
    void set_offset(double offset) {
        if (offset < -5.0 || offset > 5.0) {
            std::println("  rejected offset {}: it must be between -5 and 5", offset);
            return;                       // the object keeps its previous, valid value
        }
        offset_ = offset;
    }

    double offset() const { return offset_; }
    // ...

private:
    std::string name_{"unnamed"};
    double offset_{0.0};
};
```

```
Sensor sensor-12 has offset 1.5
  rejected offset 400: it must be between -5 and 5
after the bad call it still has offset 1.5
```

Now the rule lives in **one place**. There is no other way to change `offset_`, because from outside the class it does not exist:

```cpp
// sensor.offset_ = 400.0;      // error: 'offset_' is private
```

A rule that a class always keeps is called its **invariant**. Here it is "the offset is between -5 and 5". Every member function may rely on the invariant being true when it starts, and must leave it true when it ends. Hiding the data is what makes that promise possible, because no outside code can break it.

### The pieces

```
   class Sensor {
   public:                                  the interface: what outside code may use
       void set_offset(double offset);      a member function
       double offset() const;
   private:                                 the implementation: hidden from outside
       double offset_{0.0};                 a data member
   };
```

- **`public:`** and **`private:`** are **access specifiers**. Everything after one, up to the next, has that access.
- Functions inside a class are **member functions**. They can use the private members directly, by name.
- The **trailing underscore** (`offset_`, `name_`) is a common habit to tell a member from a parameter or a local variable at a glance, so `offset_ = offset;` is easy to read: member on the left, parameter on the right. Some styles use a `m_` prefix instead. Pick one and keep it.
- **Default member initializers** (`double offset_{0.0};`) give a fresh object a sensible state, even before any constructor does anything. 10.3 covers constructors.
- The **`const`** after `double offset() const` means "this function does not change the object". 10.5 explains it. For now, read it as "this one only looks".

### struct or class?

The only technical difference is the **default access**: members of a `struct` are public until you say otherwise, members of a `class` are private. Everything else is identical. The habit that goes with it:

```
   struct   plain data with no rules to protect        (a point, a colour, a pair of numbers)
   class    something that must stay valid             (a sensor, a log, an image)
```

**Code for this lecture**: `10.2FromStructToClass/main.cpp`.

---

## 10.3 Constructors and initializer lists

In this lecture we deal with how an object **starts its life**. In 10.2 a `Sensor` began with default values and was then changed by setters. A **constructor** makes sure it is **valid from the first moment**.

### The constructor

A constructor is a function with the **same name as the class** and **no return type**. It runs automatically when an object is created.

```cpp
class Sensor {
public:
    Sensor(int id, const std::string& name, double offset)
        : id_{id}, name_{name}, offset_{offset} {
        std::println("  Sensor {} ({}) created, offset {}", id_, name_, offset_);
    }
    // ...
private:
    const int id_{0};
    std::string name_{"unnamed"};
    double offset_{0.0};
};

Sensor north{12, "north", 1.5};
```

```
full constructor:
  Sensor 12 (north) created, offset 1.5
```

### The member initializer list

Everything between the **colon** and the **opening brace** is the **member initializer list**: it builds each member **directly** with the value you give it.

```
   Sensor(int id, const std::string& name, double offset)
       : id_{id}, name_{name}, offset_{offset}      ← the list: members are BUILT here
   {
       ...                                           ← the body: members already exist
   }
```

Without the list, each member is first built with its default value and then **assigned** in the body: two steps, one of them wasted. And for some members there is no choice at all:

- a **`const` member** (`id_` above) cannot be assigned, only initialized;
- a **reference member** cannot be re-pointed, only initialized;
- a member **without a default constructor** has to be given its arguments.

For those, the initializer list is the only way. Use it for every member, by habit.

### The order is the declaration order

Members are initialized in the order they are **declared in the class**, not in the order they appear in the list. To see it, the program has a helper that announces itself, and a class whose list disagrees with its declarations:

```cpp
class Pair {
public:
    Pair() : second_{"second_"}, first_{"first_"} {}     // the list says second_ first...
private:
    Noisy first_;                                        // ...but first_ is declared first
    Noisy second_;
};
```

```
member initialization order:
    initializing first_
    initializing second_
```

`first_` goes first, whatever the list says. That matters when one member's initial value depends on another. GCC and Clang warn about a list that disagrees with the declaration order (`-Wreorder`), and the warning is worth listening to: a list that is out of order only **looks** like it initializes in the order written.

### Several constructors, and delegating

A class can have several constructors, picked by the arguments, like overloaded functions (6.9). To avoid repeating the setup, one constructor can **delegate** to another:

```cpp
Sensor(int id, const std::string& name)
    : Sensor{id, name, 0.0} {}               // hands the work to the full constructor

explicit Sensor(int id)
    : Sensor{id, "unnamed"} {}               // and this one to the previous
```

```
delegating to the full one:
  Sensor 13 (east) created, offset 0

the one-argument constructor:
  Sensor 14 (unnamed) created, offset 0
```

The setup logic exists **once**, in the full constructor. The others only fill in defaults.

### The default constructor

A **default constructor** takes no arguments. `Sensor() = default;` asks the compiler to write it, using the default member initializers:

```cpp
Sensor blank;                  // uses the default constructor
```

```
default constructor (compiler-written, uses the member defaults):
  0 / unnamed / 0
```

If you write **any** constructor of your own and still want a default one, you have to ask for it, like this. The compiler only writes one by itself when you have written no constructors at all.

### `explicit`

```cpp
explicit Sensor(int id) ...
```

A one-argument constructor is also a **conversion**: given a number, it can build a Sensor. Without `explicit`, the compiler is free to use that conversion silently:

```cpp
// Sensor accidental = 15;          // error with explicit: cannot convert int to Sensor
// describe(15);                    // error, for the same reason
```

Without the keyword, both lines would compile and quietly create a Sensor from the number 15, which is almost never what anyone meant. Mark one-argument constructors `explicit` unless you want the conversion.

### Braces and narrowing

Brace initialization, which you have used all course, also **refuses narrowing**:

```cpp
// Sensor lossy{12.7, "x", 0.0};    // error: double to int would lose data
```

Parentheses would have accepted it and quietly turned 12.7 into 12. Another reason for the brace habit.

**Code for this lecture**: `10.3ConstructorsAndInitializerLists/main.cpp`.

---

## 10.4 Splitting a class across a header and a source file

In this lecture we put a class where real programs put it: **declaration in a header, definitions in a source file**, exactly as you did for functions in 6.11.

```
   sensor.h        the class DECLARATION: what a Sensor is and what you can do with it
   sensor.cpp      the DEFINITIONS: how each function works
   main.cpp        includes sensor.h and uses Sensor
```

### The header

```cpp
#pragma once

#include <string>

class Sensor {
public:
    Sensor(int id, const std::string& name, double offset = 0.0);

    int id() const { return id_; }                // defined right here, inside the class

    const std::string& name() const;              // only declared here
    double offset() const;
    void set_offset(double offset);
    double calibrated(double raw) const;
    std::string describe() const;

private:
    int id_;
    std::string name_;
    double offset_;
};
```

- **`#pragma once`** stops the header from being processed twice when it is included from several places. Every header gets it.
- A function **defined inside the class**, like `id()`, is implicitly **`inline`**: the compiler may paste it into the caller. That suits one-line accessors.
- Longer functions are **declared** in the class and **defined** in the `.cpp`.

### The source file

```cpp
#include "sensor.h"

#include <format>

Sensor::Sensor(int id, const std::string& name, double offset)
    : id_{id}, name_{name}, offset_{offset} {}

double Sensor::calibrated(double raw) const {
    return raw + offset_;
}

std::string Sensor::describe() const {
    return std::format("Sensor #{} '{}' (offset {:+.1f})", id_, name_, offset_);
}
```

Every definition begins with **`Sensor::`**, the **scope resolution operator**. It says "this function belongs to the class `Sensor`". Without it, you would be defining a free function that happens to have the same name, which cannot see the private members. The `const` goes **after the parameter list in the definition too**: it is part of the function's signature, and leaving it out is a compile error, because the definition no longer matches any declaration in the class.

### Using it

```cpp
#include "sensor.h"

Sensor north{12, "north", 1.5};
Sensor east{13, "east"};
std::println("{}", north.describe());
```

```
Sensor #12 'north' (offset +1.5)
Sensor #13 'east' (offset +0.0)
Sensor #13 'east' (offset -2.0)
```

`main.cpp` sees only the declaration. It is compiled **without ever looking at `sensor.cpp`**, and the linker joins the two afterwards (7.12). The `CMakeLists.txt` lists both source files:

```cmake
add_executable(rooster main.cpp sensor.cpp sensor.h)
```

### What this buys you

```
   change a function BODY in sensor.cpp     →  only sensor.cpp is recompiled
   change sensor.h                           →  every file that includes it is recompiled
```

That is why the header should hold only what callers need to know, and why the private data is the part of a class you can least afford to change: it is in the header, so changing it recompiles everybody. (Chapter 17, modules, goes after this problem.) The caller cannot tell, and does not need to, which functions were written inside the class and which in the `.cpp`.

**Code for this lecture**: `10.4HeaderAndSourceSplit/` (`sensor.h`, `sensor.cpp`, `main.cpp`).

---

## 10.5 `const` member functions

In this lecture we finish the sentence that 10.2 left open: what the `const` at the end of a member function means.

### A promise the compiler checks

```cpp
class Sensor {
public:
    void record(double reading) {            // changes the object: not const
        readings_.push_back(reading);
    }

    std::size_t count() const {              // only looks: const
        return readings_.size();
    }
    // ...
};
```

A `const` member function **promises not to change the object**, and the compiler enforces it: assigning to a member inside would not compile. In return, such a function can be called on a **`const` object**, or through a `const` reference:

```cpp
void report(const Sensor& sensor) {
    std::println("{}: {} readings, latest {}, average {:.1f}",
                 sensor.name(), sensor.count(), sensor.latest(), sensor.average());

    // sensor.record(1.0);      // error: 'record' is not const, but sensor is
}
```

```
north: 3 readings, latest 70, average 69.8
```

This is the class version of the `const T&` parameters from 7.3. If a member function that merely looks is **not** marked `const`, then nobody holding a `const Sensor&` can call it, and the whole program ends up unable to use const references. So mark **every member function that does not change the object** `const`, from the start.

```cpp
const Sensor archived{"archived"};
std::println("{} has {} readings", archived.name(), archived.count());     // fine
// archived.record(65.0);   // error: cannot call a non-const function on a const object
```

### `mutable`: the one exception

Sometimes a `const` function has a good reason to update something internal that is **not part of the object's real state**: a cache, or a counter of how often it was used. Marking that member **`mutable`** exempts it:

```cpp
double average() const {
    ++average_calls_;                        // allowed: it is mutable
    // ...
}

private:
    mutable std::size_t average_calls_{0};
```

```
north.average() has been called 3 times
```

(Three, not two: the call inside `report` counted as well.) `mutable` is not a way around `const`. It is for **bookkeeping that an outside observer could not tell apart** from the object being unchanged. If a `mutable` member holds anything that changes what the object **means**, the design is wrong.

### Two overloads, one `const` and one not

The `const`-ness of a member function is part of its signature, so the two can **coexist**:

```cpp
const std::vector<double>& readings() const { return readings_; }     // for const objects: read-only view
std::vector<double>& readings() { return readings_; }                   // for the rest: writable
```

```cpp
north.readings().push_back(72.0);                          // non-const north: the writable one
const std::vector<double>& view{archived.readings()};     // const archived: the read-only one
// archived.readings().push_back(1.0);                    // error: the returned vector is const
```

The compiler picks the overload by looking at the object. This is the pattern behind `std::vector`'s own `operator[]` and `at()`, which come in both flavours.

### The const-correct habit

```
   member function changes the object     →  no const
   member function only looks              →  const
   it returns a reference to a member       →  const reference, from a const function
   parameters you only read                  →  const T&
```

**Code for this lecture**: `10.5ConstMembers/main.cpp`.

---

## 10.6 Destructors and RAII

In this lecture we deal with how an object **ends its life**, and with the idea that makes C++ memory management work: the class that cleans up after itself.

### A class that owns memory

In 9.9 you saw that a raw `new` and `delete` pair is easy to get wrong. Now we write the class that makes it impossible to forget. A `ReadingLog` owns a block of memory for its readings. The `new[]` goes in the **constructor**, and the `delete[]` goes in the **destructor**:

```cpp
class ReadingLog {
public:
    explicit ReadingLog(std::size_t capacity)
        : data_{new double[capacity]{}}, capacity_{capacity} {
        std::println("  log of {} created", capacity_);
    }

    ~ReadingLog() {
        std::println("  log of {} destroyed ({} readings stored)", capacity_, size_);
        delete[] data_;
    }
    // ...
private:
    double* data_;
    std::size_t capacity_;
    std::size_t size_{0};
};
```

The **destructor** is a function named after the class with a **`~`** in front. It takes **no parameters** and returns nothing, and it runs **automatically, exactly once, when the object's life ends**, however that happens.

### When does the destructor run?

```cpp
std::println("a log in main:");
ReadingLog main_log{8};
```

```
a log in main:
  log of 8 created
```

**Local objects** are destroyed when their scope ends, in **reverse order of creation**:

```cpp
{
    ReadingLog outer{2};
    {
        ReadingLog inner{3};
        std::println("  leaving the inner scope");
    }
    std::println("  leaving the outer scope");
}
```

```
  log of 2 created
  log of 3 created
  leaving the inner scope
  log of 3 destroyed (0 readings stored)
  leaving the outer scope
  log of 2 destroyed (0 readings stored)
```

Last in, first out: `inner` was built after `outer`, so it dies first. That order is not an accident. A later object may depend on an earlier one, so the later one has to go first.

### It runs on every way out

Here is the thing a manual `new`/`delete` pair could not promise (9.9). This function leaves **early**:

```cpp
bool store_if_valid(double reading) {
    ReadingLog log{4};

    if (reading < -50.0 || reading > 60.0) {
        std::println("  reading {} is out of range, leaving early", reading);
        return false;                 // the destructor runs here
    }

    log.add(reading);
    return true;                      // and here
}
```

```
leaving a function early:
  log of 4 created
  stored 21
  log of 4 destroyed (1 readings stored)
  log of 4 created
  reading 99 is out of range, leaving early
  log of 4 destroyed (0 readings stored)
```

Both paths cleaned up, and nobody wrote a `delete` on either. With raw `new` and `delete`, the early `return` would have skipped the `delete` and leaked. (The same holds for exceptions, chapter 13: the destructor runs while the exception unwinds the stack.)

### Heap objects and temporaries

An object created with `new` is destroyed by `delete`, which runs the destructor:

```cpp
ReadingLog* heap_log{new ReadingLog{5}};
delete heap_log;
```

```
a log on the heap: new runs the constructor, delete the destructor
  log of 5 created
  using it, size 0
  log of 5 destroyed (0 readings stored)
```

A **temporary** (an object with no name) lives until the **end of the statement** that created it:

```cpp
std::println("  size of a temporary log: {}", ReadingLog{6}.size());
```

```
  log of 6 created
  size of a temporary log: 0
  log of 6 destroyed (0 readings stored)
  (the temporary is already gone)
```

### RAII

Put the pieces together:

```
   constructor   ACQUIRES the resource       new[], open a file, take a lock
   destructor    RELEASES the resource       delete[], close the file, release the lock
   so            the resource is released on EVERY way out of the scope
```

This is **RAII**, "resource acquisition is initialization". The name is awkward and the idea is simple: **tie the life of a resource to the life of an object**, and the language's own rules for objects (destroy at the end of the scope, in reverse order, on every path) do the cleanup for you.

You have been using RAII all along. `std::vector` does the `new[]` and `delete[]` in its destructor. `std::unique_ptr` deletes its object in its destructor. A `std::ofstream` closes its file. And the reason the smart pointers of 9.10 and 9.11 work is that they are small RAII classes. **Whenever you need to manage a resource, wrap it in a class** and let the destructor do the release.

### A warning, to be resolved next

```cpp
ReadingLog(const ReadingLog&) = delete;
ReadingLog& operator=(const ReadingLog&) = delete;
```

These two lines **forbid copying** a `ReadingLog`. Why? Suppose one were copied, with the compiler's own rules. We will see exactly what happens in 10.7, and it ends with two objects deleting the same block. `= delete` tells the compiler "no such function exists", and any attempt to copy is a compile error. For now, it is the safe default for a class that owns something.

**Code for this lecture**: `10.6DestructorsAndRAII/main.cpp`.

---

## 10.7 Copying objects

In this lecture we answer the question 10.6 left open: what does it mean to **copy** an object that owns a resource?

### What the compiler does by default

When you copy an object, the compiler writes a copy that copies **every member, one by one**. For an `int` or a `std::string`, that is exactly right. For a **raw pointer**, it copies the **address** and nothing else: both objects now point at the **same** block. That is called a **shallow copy**.

To see it safely, here is a struct with a raw pointer and no destructor (adding one would make the program delete the same block twice):

```cpp
struct ShallowLog {
    double* data;
    std::size_t size;
};

ShallowLog original{new double[3]{60.0, 61.0, 62.0}, 3};
ShallowLog copy{original};                    // copies the POINTER, not the data
copy.data[0] = 99.0;
std::println("  original.data[0] = {}  (we changed the COPY)", original.data[0]);
std::println("  same block: {}", original.data == copy.data);
```

```
the compiler's own copy of a struct with a pointer:
  original.data[0] = 99  (we changed the COPY)
  same block: true
```

Changing the copy changed the original, because there is only **one block**, with two names for it:

```
   original.data ──┐
                   ├──►  [ 60 | 61 | 62 ]
   copy.data ──────┘
```

And now give this class the destructor from 10.6. When the two objects die, **each one deletes the block**: a **double free**, which you met in the project of 9.12. A class that owns something has to decide what copying it means.

### The deep copy

A **deep copy** makes the copy its **own block** and copies the elements across. Two special member functions do it.

```cpp
// The copy CONSTRUCTOR: builds a new log from an existing one.
ReadingLog(const ReadingLog& other)
    : data_{new double[other.capacity_]}, capacity_{other.capacity_}, size_{other.size_} {
    std::copy_n(other.data_, other.size_, data_);
}
```

The parameter is a **`const` reference** to the object being copied (never by value, which would need a copy to make the copy). The new object gets a fresh block, and `std::copy_n` copies the elements.

```cpp
ReadingLog first{3};
first.add(60.0); first.add(61.0); first.add(62.0);

ReadingLog second{first};                     // copy constructor
second.set(0, 99.0);
std::println("  first.at(0) = {}, second.at(0) = {}", first.at(0), second.at(0));
std::println("  same block: {}", first.address() == second.address());
```

```
  copy constructed (a new block of 3)
  first.at(0) = 60, second.at(0) = 99
  same block: false
```

Now the two logs are independent.

### The copy assignment operator

Copying onto an object that **already exists** is a different operation, **assignment**, with its own function:

```cpp
ReadingLog& operator=(const ReadingLog& other) {
    if (this == &other) {
        return *this;                               // self-assignment: nothing to do
    }

    double* fresh{new double[other.capacity_]};     // allocate FIRST...
    std::copy_n(other.data_, other.size_, fresh);

    delete[] data_;                                 // ...and only now give the old block back
    data_ = fresh;
    capacity_ = other.capacity_;
    size_ = other.size_;
    return *this;
}
```

Three details, each there for a reason:

1. **The self-assignment check.** `a = a` is legal (and happens indirectly, as in `v[i] = v[j]` with `i == j`). Without the check, the function would delete its own block and then copy from it.
2. **Allocate before deleting.** If `new` throws (out of memory), the object is still intact. The order "build the new thing, then replace the old" is the safe one.
3. **`return *this`** lets assignments be chained (`a = b = c`). `this` is a pointer to the object the function was called on. 10.10 returns to it.

```cpp
ReadingLog third{1};
third = first;                                // copy assignment
third = third;                                // self-assignment is safe
```

```
  copy assigned
  third now has 3 readings, third.at(2) = 62
  copy assigned
```

(Clang warns about the line `third = third;` itself, with `-Wself-assign-overloaded`. Here it is deliberate.)

### When copies happen without you asking

Copies happen in more places than the word "copy" suggests:

```
   ReadingLog b{a};                 initialization from another object
   b = a;                            assignment
   void f(ReadingLog log);  f(a);    passing by VALUE
   return a_local_log_by_value       (often avoided, 10.8)
```

```cpp
double first_of(ReadingLog log) { return log.at(0); }          // by value: a copy
double first_of_ref(const ReadingLog& log) { return log.at(0); }  // const reference: none
```

```
when copies happen, without you writing the word "copy":
  passing by value:
  copy constructed (a new block of 3)
  passing by const reference:
```

The by-value call copied the **whole block**. The const-reference call did not. This is why 7.3 taught `const T&` for read-only parameters: with a class that owns memory, passing by value is not just a style question, it is an allocation and a copy of everything on every call.

**Code for this lecture**: `10.7CopyingObjects/main.cpp`.

---

## 10.8 Move semantics

In this lecture we meet the other way to hand an object around: instead of **duplicating** it, **hand it over**.

### Copying is wasteful when the original is going away

Imagine a log with a million readings, returned from a function, or put into a `std::vector`. Copying it means allocating a million readings and copying each one, just so the **original, which is about to be destroyed anyway**, can throw its own away. A **move** skips all that. It takes the original's **block** (just the pointer), and leaves the original empty.

```
   COPY                                    MOVE
   original ──► [ ... a million ... ]      original ──► nothing
   copy     ──► [ ... a million ... ]      target   ──► [ ... the SAME block ... ]
   cost: allocate + copy everything        cost: three assignments, whatever the size
```

### The move constructor and move assignment

```cpp
ReadingLog(ReadingLog&& other) noexcept
    : data_{std::exchange(other.data_, nullptr)},
      capacity_{std::exchange(other.capacity_, 0)},
      size_{std::exchange(other.size_, 0)} {
    std::println("  [move] block stolen");
}
```

Three things to read here:

- **`ReadingLog&&`** is an **rvalue reference**. It binds to an object that is about to go away (a temporary, or something marked with `std::move`), and tells the function that it may take what it likes.
- **`std::exchange(x, y)`** (from `<utility>`) returns the old value of `x` and puts `y` in its place. So each line means "take the member, and leave a harmless value in the source". After it, the original holds **a null pointer and zero sizes**.
- **`noexcept`** promises that the function cannot throw, which is true: nothing here can fail. The promise matters, as the last section shows.

The move assignment operator does the same after releasing what the target already held:

```cpp
ReadingLog& operator=(ReadingLog&& other) noexcept {
    if (this != &other) {
        delete[] data_;                              // give up what we had
        data_ = std::exchange(other.data_, nullptr);
        capacity_ = std::exchange(other.capacity_, 0);
        size_ = std::exchange(other.size_, 0);
    }
    return *this;
}
```

### `std::move`

```cpp
ReadingLog copy{original};                   // a copy: original keeps its data
ReadingLog moved{std::move(original)};       // a move: original is emptied
```

```
a copy, then a move:
  [copy] 2 elements duplicated
  [move] block stolen
  copy has 2 readings, moved has 2
  original now has 0 readings (it was moved from)
```

**`std::move` does not move anything.** It is only a **cast**: it says "treat this object as something I am finished with", so that the **move** constructor is chosen instead of the copy constructor. The move happens inside the constructor.

After a move, the original is **moved-from**: still a valid object, safe to destroy and to assign to, but its contents are **no longer yours to rely on**. In our class it is deliberately empty, and the destructor's `delete[] nullptr` is allowed and does nothing. The pattern to remember: **after `std::move(x)`, do not read `x` again, except to give it a new value**.

```cpp
ReadingLog target{5};
target = std::move(moved);                   // move assignment
```

```
move assignment:
  [move assign] block stolen
  target has 2 readings
```

### Returning by value is cheap

```cpp
ReadingLog make_log(std::size_t capacity) {
    return ReadingLog{capacity};
}

ReadingLog fresh{make_log(10)};
```

```
returning by value:
  made a log of size 0 with no copy or move line above
```

When a function returns a **temporary**, C++17 guarantees that it is built **directly in the caller's variable**: no copy and no move. (Returning a **named local** is usually optimized the same way, and when it is not, the compiler moves instead of copying.) So returning big objects by value is the normal, cheap thing to do. Do not "optimize" it with `std::move`: that can only get in the way.

### Why `noexcept` matters: `std::vector`

When a `std::vector` runs out of room, it allocates bigger storage and has to bring its elements across. It would like to **move** them, which is cheap. But if a move **throws** halfway, the vector is left with some elements in the old storage and some in the new, and cannot undo it. So it only moves if the move is **`noexcept`**, and otherwise **copies**, which can be abandoned safely. The program counts what happens to two small types:

```cpp
struct Quiet {
    Quiet(const Quiet&) { ++quiet_copies; }
    Quiet(Quiet&&) noexcept { ++quiet_moves; }          // promises not to throw
};

struct Careless {
    Careless(const Careless&) { ++careless_copies; }
    Careless(Careless&&) { ++careless_moves; }          // no promise
};
```

```
vector growth, 8 push_backs each:
  Quiet    (noexcept move): 0 copies, 24 moves
  Careless (plain move):    16 copies, 8 moves
```

`Careless` was **copied** every time the vector grew, and `Quiet` never was. (The exact numbers depend on the library: MSVC printed `0 and 24` and `16 and 8`, GCC and Clang printed `0 and 15` and `7 and 8`, because they grow their storage differently. The pattern is the same everywhere.) The rule that follows: **mark your move operations `noexcept`**, whenever they cannot throw. Usually they cannot.

**Code for this lecture**: `10.8MoveSemantics/main.cpp`.

---

## 10.9 The rules of zero, three and five

In this lecture we put 10.6 to 10.8 together into rules you can follow, and see that the best answer is usually to write **none** of this code.

### The five special member functions

Five functions are about the life and the duplication of an object. The compiler can write them for you:

```
   ~T()                          destructor
   T(const T&)                   copy constructor
   T& operator=(const T&)        copy assignment
   T(T&&) noexcept               move constructor
   T& operator=(T&&) noexcept    move assignment
```

When a class owns a raw resource, the compiler's versions are wrong (10.7), and you must write **all five**. That is the **rule of five**. (Before C++11 there were no moves, and the same idea was the "rule of three".) The reason they come as a set is that they all answer one question: **who owns the resource, and what happens when ownership is duplicated or handed over?**

`RawLog` in the program is that class: 30 lines, every one a chance for a bug.

### The rule of zero

The better rule: **design the class so that it needs none of the five.** Hold your resources in members that already manage themselves, and the compiler-written versions are correct:

```cpp
class VectorLog {
public:
    explicit VectorLog(std::size_t capacity) { readings_.reserve(capacity); }
    void add(double reading) { readings_.push_back(reading); }
    std::size_t size() const { return readings_.size(); }

private:
    std::vector<double> readings_;
};
```

No destructor, no copy, no move. The `std::vector` member already knows how to destroy, copy and move itself, so `VectorLog` is copyable, movable and leak-free, in eight lines. This is the **rule of zero**, and it is what you should aim for **every time**.

A `std::unique_ptr` member is the same idea for a block you must manage yourself, with one difference:

```cpp
class UniqueLog {
    // ...
private:
    std::unique_ptr<double[]> data_;
    std::size_t capacity_;
    std::size_t size_{0};
};
```

A `unique_ptr` cannot be copied, so neither can `UniqueLog`, and that is **exactly right** for something with a single owner. The compiler-written **move** works. Still zero lines of special member code.

### Asking for it, or forbidding it

`= default` says "the compiler's version is what I want", out loud. `= delete` says "this operation does not exist":

```cpp
class SerialPort {
public:
    SerialPort(const SerialPort&) = delete;                // two objects cannot share one port
    SerialPort& operator=(const SerialPort&) = delete;

    SerialPort(SerialPort&&) = default;                    // but a port can be handed over
    SerialPort& operator=(SerialPort&&) = default;
    ~SerialPort() = default;
};
```

A class for something that must exist **once** says so, and the compiler enforces it: any attempt to copy is an error message at compile time, not a bug at run time.

### Asking the compiler about each class

The program asks all four classes the same questions, using type traits (`<type_traits>`):

```
what each class can do:
  RawLog     copyable: true   movable: true   move can throw: false
  VectorLog  copyable: true   movable: true   move can throw: false
  UniqueLog  copyable: false  movable: true   move can throw: false
  SerialPort copyable: false  movable: true   move can throw: false
```

All four can be moved without throwing. For `VectorLog`, `UniqueLog` and `SerialPort` that comes without a word from us, because their members already promise it, and `RawLog` has it because we wrote `noexcept` ourselves. `UniqueLog` and `SerialPort` are movable but **not copyable**: a class with exactly one owner, in the type itself.

### The summary

```
   Rule of zero    own nothing directly: let std::vector, std::string, std::unique_ptr
                   do the owning. Write no special member functions.         ← the default
   Rule of five    you wrap a raw resource: write all five, or delete what makes no sense.
   Rule of three   the old name for the copy half, from before moves existed.
```

And one habit: **if you write one of the five, stop and consider the other four.** A class with a hand-written destructor and nothing else is almost always a bug.

**Code for this lecture**: `10.9RuleOfZeroThreeFive/main.cpp`.

---

## 10.10 `static`, `this` and `friend`

In this lecture we meet three smaller features that you will keep running into: data that belongs to the **class** instead of to each object, the pointer to the **current object**, and a function allowed to peek inside.

### `static` members: one per class

A normal data member exists **once per object**. A **`static`** data member exists **once per class**, shared by all objects, and it exists even if no object does.

```cpp
class Sensor {
public:
    static constexpr double max_offset{5.0};         // a shared constant

    explicit Sensor(const std::string& name) : name_{name} {
        ++active_;
        ++created_;
    }

    ~Sensor() {
        --active_;
    }

    static int active() { return active_; }
    static int created() { return created_; }

private:
    static inline int active_{0};                     // how many Sensors exist right now
    static inline int created_{0};                    // how many have ever existed
};
```

- **`static constexpr`** makes a shared compile-time constant: nothing stored per object.
- **`static inline`** (C++17) lets the shared variable be **defined right in the class**. Before C++17 it had to be defined again in one `.cpp`, which was easy to forget.
- A **static member function** belongs to the class and has **no `this`** (see below), so it can only touch static members. It is called with the **class name**, no object needed:

```cpp
std::println("max_offset = {} (no object needed)", Sensor::max_offset);
std::println("sensors alive at the start: {}", Sensor::active());
```

```
max_offset = 5 (no object needed)
sensors alive at the start: 0
after creating two: 2
```

### A gotcha: the compiler-written copy does not count

```cpp
{
    Sensor copy{north};
    std::println("inside a scope, with a copy: {} alive ({} ever created)",
                 Sensor::active(), Sensor::created());
}
```

```
inside a scope, with a copy: 3 alive (3 ever created)
after the scope: 2 alive (3 ever created)
```

This printed the correct 3 because the class has its **own copy constructor** that increments the counters. Without it, the compiler writes a copy constructor that copies the **members** (`name_`, `offset_`) and **nothing else**, and the count would say 2 while three sensors existed. The destructor would then decrement for a sensor the constructor never counted, and `active_` would drift below the real count. **Any class that does bookkeeping in its constructors and destructor needs its own copy constructor too.** (Comment the copy constructor out in the program and watch the numbers go wrong.) This is the rule of five from 10.9, met in its natural habitat.

### `this`: the current object

Inside a non-static member function, **`this`** is a **pointer to the object the function was called on**. You rarely write it, because member names already mean `this->name`, but it lets a function **return the object itself**:

```cpp
Sensor& rename(const std::string& name) {
    name_ = name;
    return *this;                        // *this is the object; the return type is a reference to it
}

Sensor& set_offset(double offset) {
    if (offset >= -max_offset && offset <= max_offset) {
        offset_ = offset;
    }
    return *this;
}
```

Returning `*this` by reference makes calls **chainable**:

```cpp
north.rename("north-2").set_offset(1.5).set_offset(99.0);     // the last one is rejected by the rule
print_debug(north);
```

```
chained setters, using *this:
  debug: name_='north-2' offset_=1.5
```

You have already seen this idea: `std::cout << a << b << c` chains because each `<<` returns the stream itself. The return type is a **reference** (`Sensor&`), not a `Sensor`, so each call works on the **same** object and not on a copy.

### `friend`

A **friend** is a function (or another class) that is **allowed to see the private members**, without being a member itself. The class grants the access:

```cpp
class Sensor {
    // ...
    friend void print_debug(const Sensor& sensor);       // granted here
private:
    std::string name_;
    double offset_{0.0};
};

void print_debug(const Sensor& sensor) {                  // defined outside, not a member
    std::println("  debug: name_='{}' offset_={}", sensor.name_, sensor.offset_);
}
```

`print_debug` reads `sensor.name_` and `sensor.offset_` directly, which no ordinary function could. Use `friend` **sparingly**: it punches a hole in the encapsulation you built, and every friend becomes a function that must change when the private data does. You will meet it in chapter 12, where operators such as `<<` are the classic case.

**Code for this lecture**: `10.10StaticThisAndFriend/main.cpp`.

---

## 10.11 Composition, aggregates and `enum class`

In this lecture we build a class **out of** other objects, and see which things should be a plain `struct` instead.

### Aggregates: plain data

A **struct** with no constructors, no private members and no rules is an **aggregate**. It is initialized by listing the values:

```cpp
struct Location {
    double latitude;
    double longitude;
};

Location seattle{47.6, -122.3};
```

C++20 adds **designated initializers**, which name the fields and so remove any doubt about which number is which:

```cpp
Location denver{.latitude = 39.7, .longitude = -105.0};
```

The names must appear **in declaration order**. A reader of `Location{47.6, -122.3}` has to remember which one is the latitude. A reader of the second form does not.

A **structured binding** (C++17) unpacks an aggregate into separate named variables, in declaration order:

```cpp
auto [lat, lon]{denver};
std::println("denver: latitude {}, longitude {}", lat, lon);
```

```
denver: latitude 39.7, longitude -105
```

`lat` is `denver.latitude` and `lon` is `denver.longitude`. It is a tidy way to take apart a small bundle of values, and you will use it with `std::pair` and with map entries later.

### Composition: has-a

Most real classes are built **out of** other objects. A weather `Station` **has a** name, **has a** location, **has a** status and **has some** sensors:

```cpp
enum class Status { online, offline, faulty };

class Station {
public:
    Station(std::string name, Location where)
        : name_{std::move(name)}, where_{where} { ... }
    // ...
private:
    std::string name_;
    Location where_;
    Status status_{Status::online};
    std::vector<std::string> sensors_;
    Part antenna_{"antenna"};
    Part battery_{"battery"};
};
```

This is **composition**: the Station contains its parts as members, and the parts live and die with it. `enum class` is the scoped enumeration from chapter 5, used here for the status.

### The order of construction and destruction

To see the order, the program has a small `Part` class that prints when it is built and when it dies:

```
building a station:
    antenna built
    battery built
    Station Rooftop constructor body runs
  --- constructed, now using it ---
  Rooftop at (47.6, -122.3), faulty, 2 sensor(s)
  --- leaving the scope ---
    Station Rooftop destructor body runs
    battery destroyed
    antenna destroyed
```

Read it top to bottom:

1. The **members** are built first, in the order they are **declared** (`name_`, `where_`, `status_`, `sensors_`, `antenna_`, `battery_`). The two parts announce themselves.
2. Only **then** does the **constructor body** run, when everything it might use already exists.
3. On the way out, the **destructor body** runs **first**.
4. Then the **members are destroyed in reverse order**: `battery_` before `antenna_`.

The same last-in, first-out rule as for local variables in 10.6, applied to the inside of an object. It also explains why a class whose members are all RAII types (a `std::vector`, a `std::string`, another class that follows the rule of zero) needs **no destructor of its own**: the members clean up after themselves, in the right order.

### Struct or class?

```
   Location    a struct:  any two numbers are a valid location. Nothing to protect.
   Station     a class:   it has rules (a status, a list of sensors, a lifetime for its parts).
```

If you find yourself writing getters and setters that do nothing but copy a value in and out, with no rule, you probably wanted a struct.

### Where this leads

A `Station` **has a** `Part`. The other relation between types, **is a**, is **inheritance**, and it is the subject of chapter 11. Remember the difference: if you can say "a Station has an antenna", use a member. If you can say "a SolarSensor is a Sensor", that is inheritance.

**Code for this lecture**: `10.11CompositionAndAggregates/main.cpp`.

---

## 10.12 Project: the Canvas

In chapter 6 you built an image writer out of free functions. Every one of them, `set_pixel`, `draw_gradient`, `draw_border` and `write_ppm`, took the same three arguments: the vector of pixels, the width and the height. Nothing stopped you from passing a width that did not match the vector. Now we give those three values a home, and a promise.

The result is a **`Canvas`** class, and the picture it draws is exactly the one from 6.17.

```
   chapter 6                                  chapter 10
   ─────────                                  ──────────
   std::vector<std::uint8_t> pixels;          Canvas canvas{400, 300};
   set_pixel(pixels, w, h, x, y, r, g, b);    canvas.set_pixel(x, y, Color{r, g, b});
   draw_gradient(pixels, w, h, ...);          canvas.draw_gradient(left, right);
   write_ppm("image.ppm", w, h, pixels);      canvas.write_ppm("image.ppm");
```

The code is in `10.12ProjectCanvas`: `color.h`, `canvas.h`, `canvas.cpp`, `main.cpp`, `stb_impl.cpp` and the vendored header from 6.18 in `vendor/`. Later chapters will draw shapes onto this `Canvas`, so this is a class worth getting right.

### The pieces

**`Color`** is plain data: any three bytes are a valid colour. So it is an **aggregate** (10.11), initialized by value or by name:

```cpp
struct Color {
    std::uint8_t r{0};
    std::uint8_t g{0};
    std::uint8_t b{0};
};

Color orange{240, 140, 40};
Color blue{.r = 20, .g = 30, .b = 90};
```

**`Canvas`** is a class, because it has a rule to keep. Its three members:

```cpp
private:
    int width_;
    int height_;
    std::vector<std::uint8_t> pixels_;
```

and its **invariant**, written at the top of `canvas.h`:

```
   pixels_.size() == width_ * height_ * 3,   and width_, height_ >= 0
```

Every member function may rely on it, and must leave it true. Because the data is private, no outside code can break it. The constructor makes sure it holds from the start (a negative size becomes zero), and the drawing functions, `set_pixel` and `pixel`, check coordinates against the size, so a wrong coordinate can never reach the vector:

```cpp
void Canvas::set_pixel(int x, int y, Color color) {
    if (!contains(x, y)) {
        return;                                  // ignored: nothing outside the picture can be touched
    }
    const std::size_t i{offset(x, y)};
    pixels_[i + 0] = color.r;
    pixels_[i + 1] = color.g;
    pixels_[i + 2] = color.b;
}
```

### What the class needs, by the rules of 10.9

**Destructor**: none to write. The vector frees its own storage. That is the **rule of zero**, and the reason `pixels_` is a `std::vector` and not a raw `new[]` block.

**Copy**: also none to write, and `= default` says so out loud:

```cpp
Canvas(const Canvas&) = default;
Canvas& operator=(const Canvas&) = default;
~Canvas() = default;
```

The vector copies its elements, and the two integers copy as integers, so a copy of a Canvas is a **complete, independent picture**.

**Move**: **this is the one that needs real code.** The rule of zero would hand us a compiler-written move, which moves the vector and leaves `width_` and `height_` as they were. The moved-from canvas would then claim to be 200 x 50 while holding no pixels at all: **the invariant is broken**. Using it, even to set one pixel, goes straight past the end of an empty vector. (We tried it: with the compiler's move, the first `set_pixel` on the moved-from canvas aborted GCC's checked library with a failed `vector::operator[]` assertion. Without that check it would be a silent out-of-bounds write.) So we write the move ourselves, and reset the sizes too:

```cpp
Canvas::Canvas(Canvas&& other) noexcept
    : width_{std::exchange(other.width_, 0)},
      height_{std::exchange(other.height_, 0)},
      pixels_{std::exchange(other.pixels_, {})} {}
```

The lesson: **the rule of zero holds when every member manages itself independently.** Here two integers and a vector have to agree, so the class has to say what "moved-from" means: an empty 0 x 0 canvas, which keeps the invariant. `noexcept` is there because nothing in it can throw.

### The program

```cpp
Canvas canvas{400, 300};
canvas.draw_gradient(Color{.r = 20, .g = 30, .b = 90}, Color{.r = 240, .g = 140, .b = 40});
canvas.draw_border(8, Color{.r = 255, .g = 255, .b = 255});
canvas.write_ppm("image.ppm");
canvas.write_png("image.png");
```

The picture is the same blue-to-orange gradient with a white frame as in 6.17. Then the program tries the three things this chapter was about:

**A copy is independent.** It duplicates the canvas, draws a white square on the **copy**, and compares the centre pixel of both:

```cpp
Canvas annotated{canvas};
annotated.fill_rect(150, 100, 100, 100, Color{.r = 255, .g = 255, .b = 255});
```

```
wrote image.ppm and image.png (400 x 300)

the centre pixel of the original is (130, 85, 64)
the centre pixel of the copy     is (255, 255, 255)
```

`image_copy.png` shows the white square, and `image.png` is untouched.

**A move hands the picture over.** A factory function returns a canvas by value (guaranteed to be built in place, 10.8), and the program moves it to a new owner:

```cpp
Canvas banner{make_banner(200, 50)};
Canvas new_owner{std::move(banner)};
```

```
new_owner is 200 x 50
banner, after the move, is 0 x 0 (empty: true)
```

**A moved-from canvas is safe.** Setting a pixel on it does nothing, and saving it reports failure instead of writing a broken file:

```
saving the moved-from canvas: false
pixel(9999, 9999) reads as (0, 0, 0)
```

The last line shows the other half of the design: pixels outside the picture are **ignored when written and read as black**, so the drawing code never needs to check the bounds.

### Using the vendored header

PNG output uses `stb_image_write.h`, **vendored** into `vendor/` exactly as in 6.18: a single header, whose function bodies are compiled once in `stb_impl.cpp` (the file with `#define STB_IMAGE_WRITE_IMPLEMENTATION`). `canvas.cpp` includes the header for the declarations only. `write_png` is a few lines around one `stbi_write_png` call.

### Check it with the tools from chapter 9

A class that owns memory, a move that leaves things empty: this is exactly where the sanitizers of 9.12 earn their keep. We ran the finished project under AddressSanitizer and UndefinedBehaviorSanitizer with both GCC and Clang in the containers:

```sh
g++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer \
    -isystem vendor main.cpp canvas.cpp stb_impl.cpp -o canvas
./canvas
```

No warnings, and no reports. That is what you want to see before trusting a class. **Try it**: change the move constructor to `= default`, rebuild, and run it again. What you see depends on the compiler and its checks (an assertion failure, a crash, or nothing at all), which is exactly why this is a bug to design out and not one to hope you notice.

### What to take away

```
   invariant        a rule the class always keeps, protected by private data
   rule of zero     a vector member gives destructor, copy and move for free
   rule of five     when members must AGREE (width, height, pixels), write the move yourself
   moved-from       must still be a valid object: here, an empty 0 x 0 canvas
```

The Canvas comes back in chapter 11, where **shapes** draw themselves onto it.

**Code for this project**: `10.12ProjectCanvas/` (`color.h`, `canvas.h`, `canvas.cpp`, `main.cpp`, `stb_impl.cpp`, `vendor/`, `CMakeLists.txt`).

---

## 10.13 Assignment

Eight small classes for the weather station, one per exercise: a class that protects its data, constructors, `const` and `mutable`, RAII, the rule of five, the rule of zero, `static` and `this`, and composition with aggregates. `main.cpp` has the eight exercises, each with its statement and a sample run in a comment. You write each class above `main()` and the lines that use it in `main()` under its heading. `main_solution.cpp` solves all eight. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `Thermometer` | a private member, a validating setter that returns `bool`, `const` getters, a computed property |
| 2 | `Alarm` | a `const` member set in an initializer list, three constructors with two **delegating**, `std::format` |
| 3 | `Lookup` | a `const` member function that still counts its calls through a `mutable` member, a `const Lookup&` parameter |
| 4 | `ScopeLabel` | RAII: constructor and destructor messages, nested scopes, an early `return` |
| 5 | `Buffer` | the **rule of five**: `new[]`/`delete[]`, a deep copy constructor and assignment, `std::exchange` in the move operations |
| 6 | `SafeBuffer` | the **rule of zero**: the same interface over a `std::vector`, with no special members, checked with `std::is_copy_constructible_v` |
| 7 | `Ticket` | a `static inline` counter, a `static` function, `*this` chaining, `= delete` on the copy operations |
| 8 | `Gauge` | an aggregate `Range` with designated initializers, `enum class`, composition, a structured binding |

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole chapter.

After this chapter the student can design a class around an invariant, write constructors and destructors that give an object a guaranteed start and end, decide what copying and moving should mean, and prefer the rule of zero. The next chapter builds on it: classes that **inherit** from one another, and the Canvas gets **shapes** that draw themselves.
