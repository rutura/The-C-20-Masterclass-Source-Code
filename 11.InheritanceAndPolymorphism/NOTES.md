# Inheritance and Polymorphism

In chapter 10 you built classes that are good at **one thing each**. Real programs are made of classes that **relate** to one another. A thermometer and a barometer are both instruments. A circle and a triangle are both shapes. Whatever is true of "an instrument" should be written **once**, and code that works with instruments should not need to know which kind it is holding.

C++ has a tool for exactly that, and this chapter is about it:

```
   Sensor                     the BASE class: what every sensor has and does
     ▲
     │  "is a"
     ├── TemperatureSensor    DERIVED classes: a sensor, plus something of their own
     ├── WindSensor
     └── HumiditySensor
```

- **Inheritance** lets a class be built on top of another: the derived class gets everything the base has, and adds to it.
- **Polymorphism** ("many forms") lets you hold a **base-class** reference or pointer, call a function on it, and have the **real, derived** object answer. One loop over a list of sensors, and each sensor behaves as its own kind.

Used well, this is how large programs stay open to change: a new kind of sensor is a new class, and no existing code has to be edited. Used badly, it produces tangled hierarchies that nobody can change. A good half of this chapter is about **when not to use it**: slicing, the virtual destructor trap, the diamond, and the cases where composition (10.11) or a `std::variant` is the better answer.

The project at the end returns to the `Canvas` from chapter 10. You will draw a picture out of **shapes** that draw themselves, and a **group** of shapes that is itself a shape.

---

## 11.2 Inheritance basics

In this lecture we build one class on top of another, and watch what the derived class receives, what it cannot touch, and in what order the pieces are built.

### The base class

```cpp
class Sensor {
public:
    Sensor(int id, const std::string& name) : id_{id}, name_{name} { ... }
    ~Sensor() { ... }

    int id() const { return id_; }
    const std::string& name() const { return name_; }
    std::string describe() const { return std::format("#{} {}", id_, name_); }

protected:
    void log(const std::string& message) const { ... }

private:
    int id_;
    std::string name_;
};
```

Alongside `public` and `private` from chapter 10 there is a third access level: **`protected`**. A protected member is **invisible to the outside world**, but **visible to derived classes**. (`private` members are not.)

```
                 outside code     derived class     the class itself
   public            yes              yes                yes
   protected         no               yes                yes
   private           no               no                 yes
```

### The derived class

```cpp
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(int id, const std::string& name, double offset)
        : Sensor{id, name}, offset_{offset} { ... }

    double calibrated(double raw) const {
        log("calibrating a reading");              // a protected member of Sensor: allowed
        return raw + offset_;
    }

private:
    double offset_;
};
```

`: public Sensor` says "**a TemperatureSensor IS A Sensor**". The derived class has all the public and protected members of `Sensor` without writing them again, and adds its own (`calibrated`, `offset_`).

Two things to notice:

- The **base constructor is called in the initializer list**: `Sensor{id, name}`. The base part of the object has to be built **before** the derived part, so the derived constructor says how. If it did not, the compiler would look for a `Sensor()` constructor with no arguments, and fail to find one.
- The derived class **cannot** reach `id_`, because it is private to `Sensor`:

```cpp
// int broken() const { return id_; }      // error: 'id_' is private
std::string tag() const { return "T" + std::to_string(id()); }    // go through the public interface
```

### What the derived object can do

```cpp
TemperatureSensor north{1, "north", 1.5};

std::println("name() = {}, id() = {}, describe() = {}", north.name(), north.id(), north.describe());
std::println("calibrated(70.0) = {}", north.calibrated(70.0));
std::println("tag() = {}", north.tag());
```

```
building a TemperatureSensor:
  Sensor north constructed
  TemperatureSensor constructed (offset 1.5)

name() = north, id() = 1, describe() = #1 north
  [north] calibrating a reading
calibrated(70.0) = 71.5
tag() = T1
```

Look at the **construction order**: `Sensor` first, then `TemperatureSensor`. The object is built from the inside out, base first.

### A derived object IS a base object

Because of the "is a", a derived object converts to a reference or pointer to its base with **no cast**:

```cpp
const Sensor& as_sensor{north};
std::println("viewed as a Sensor: {}", as_sensor.describe());
```

```
viewed as a Sensor: #1 north
```

But the conversion only goes **one way**. Through `as_sensor`, the object looks like a plain `Sensor`, so the derived extras are out of reach:

```cpp
// as_sensor.calibrated(70.0);              // error: Sensor has no 'calibrated'
```

The derived object also **contains** the base object, which shows in its size:

```
sizeof(Sensor) = 40, sizeof(TemperatureSensor) = 48
```

The `Sensor` part is inside, and the extra `double` is added after it. (The exact numbers depend on the compiler.)

```
   TemperatureSensor object
   ┌──────────────────────────┐
   │  Sensor part             │   id_, name_       (built first)
   ├──────────────────────────┤
   │  TemperatureSensor part  │   offset_          (built second)
   └──────────────────────────┘
```

### Inheriting constructors

A derived class that adds no data would otherwise have to repeat every base constructor. A `using` declaration brings them in as they are:

```cpp
class HumiditySensor : public Sensor {
public:
    using Sensor::Sensor;
};

HumiditySensor humidity{2, "east"};          // uses Sensor's constructor
```

### Destruction in reverse

At the end of `main`, the objects are destroyed in reverse order of construction, and inside each object, **derived part first, then the base**:

```
end of main, destruction in reverse order:
  Sensor east destroyed
  TemperatureSensor destroyed
  Sensor north destroyed
```

`humidity` was built last, so it goes first (it is just a `Sensor`). Then `north`: `TemperatureSensor` destroyed, then the `Sensor` part inside it. The same last-in, first-out rule as everywhere in chapter 10.

(The destructor of `Sensor` here is not virtual. That is fine **only** because nothing in this program deletes a derived object through a `Sensor` pointer. 11.6 shows what goes wrong when something does.)

**Code for this lecture**: `11.2InheritanceBasics/main.cpp`.

---

## 11.3 Virtual functions and `override`

In this lecture we get to the point of inheritance: calling a function through a **base** reference and having the **derived** class answer.

### The problem

Suppose `Sensor` has a function that tells you its label, and `TemperatureSensor` has its own:

```cpp
void inspect(const Sensor& sensor) {
    std::println("{}", sensor.label());
}
```

`inspect` takes a **`const Sensor&`**. When it is called with a `TemperatureSensor`, which `label()` runs: the one in `Sensor`, or the one in `TemperatureSensor`? For an ordinary member function, the answer is **the one in `Sensor`**: the compiler picks the function from the **declared type of the variable** (`Sensor`), at compile time. It cannot know what the real object is.

### The fix: `virtual`

```cpp
class Sensor {
public:
    virtual double read() const { return 0.0; }
    virtual std::string label() const { return "generic sensor"; }

    std::string kind() const { return "sensor"; }            // NOT virtual

    virtual ~Sensor() = default;
};
```

Marking a function **`virtual`** changes **when** the choice is made. For a virtual function, the compiler leaves the choice to **run time**, and looks at the **real type of the object**. A derived class then **overrides** it:

```cpp
class TemperatureSensor : public Sensor {
public:
    double read() const override { return 21.5; }
    std::string label() const override { return "temperature sensor"; }
    std::string kind() const { return "temperature sensor"; }     // hides, does not override
};
```

The function `inspect` shows both behaviours side by side:

```cpp
void inspect(const Sensor& sensor) {
    std::println("  kind()  = {}   (non-virtual: follows the declared type, Sensor)", sensor.kind());
    std::println("  label() = {}   (virtual: follows the real type)", sensor.label());
    std::println("  read()  = {}   (virtual: follows the real type)", sensor.read());
}
```

```
a TemperatureSensor:
  kind()  = sensor   (non-virtual: follows the declared type, Sensor)
  label() = temperature sensor   (virtual: follows the real type)
  read()  = 21.5   (virtual: follows the real type)
a WindSensor:
  kind()  = sensor   (non-virtual: follows the declared type, Sensor)
  label() = wind sensor   (virtual: follows the real type)
  read()  = 12   (virtual: follows the real type)
a plain Sensor:
  kind()  = sensor   (non-virtual: follows the declared type, Sensor)
  label() = generic sensor   (virtual: follows the real type)
  read()  = 0   (virtual: follows the real type)
```

The same function, the same three lines, three different objects. `kind()` always says `sensor`, because it is not virtual. `label()` and `read()` follow the object. **This is polymorphism**: `inspect` was written once, knows only about `Sensor`, and still works for every kind of sensor, including kinds that do not exist yet.

Called **directly** on the derived object, the compiler knows the real type, so the derived `kind()` wins:

```
temperature.kind() called directly = temperature sensor
```

That is **hiding**: the derived `kind()` and the base `kind()` are two unrelated functions with the same name, and which one you get depends on the declared type of what you call it on. It is almost never what you want, and it is the reason to make a function virtual from the start, if it is going to be redefined.

### `override`

```cpp
double read() const override { return 21.5; }
```

The **`override`** keyword means "I intend to replace a virtual function of the base". The compiler then **checks** that the base has a virtual function with exactly this signature, and refuses to compile otherwise. That catches the classic mistakes, each of which would otherwise **silently create a new function that nothing ever calls**:

```cpp
// double read() override;              // error: missing const, so no such function in the base
// std::string Label() const override;  // error: a typo in the name
```

Without the keyword, both lines compile, and the program quietly uses the base version. **Always write `override`.** Some teams enforce it with a compiler warning (`-Wsuggest-override`).

### `final`

`final` closes a door. On a **class**, it forbids deriving from it. On a **virtual function**, it forbids overriding it any further:

```cpp
class FrozenSensor final : public Sensor {
public:
    std::string label() const override { return "frozen sensor"; }
};

// class SuperFrozen : public FrozenSensor {};     // error: FrozenSensor is final
```

Use it when you have designed a class to be the end of a line. Besides documenting the intention, it lets the compiler skip the run-time lookup when it knows the real type.

### What virtual costs

A virtual call is slightly slower than an ordinary call (11.7 shows why), and a class with virtual functions has a hidden pointer in every object. For the kinds of designs in this chapter the cost is negligible. It matters only in the innermost loop of a program doing millions of calls a second. Do not make everything virtual "just in case": make a function virtual when a derived class has a real reason to replace it.

**Code for this lecture**: `11.3VirtualFunctionsAndOverride/main.cpp`.

---

## 11.4 Polymorphic containers and slicing

In this lecture we use polymorphism for what it is best at: **one list, many kinds**. And we meet the trap that waits for everyone who forgets the rule about pointers.

### One container, one loop

```cpp
std::vector<std::unique_ptr<Sensor>> sensors;
sensors.push_back(std::make_unique<TemperatureSensor>("north"));
sensors.push_back(std::make_unique<WindSensor>("roof"));
sensors.push_back(std::make_unique<Sensor>("spare"));
sensors.push_back(std::make_unique<TemperatureSensor>("east"));

for (const auto& sensor : sensors) {
    std::println("  {:<6} {:<20} reads {}", sensor->name(), sensor->label(), sensor->read());
}
```

```
one loop, four sensors, three kinds:
  north  temperature sensor   reads 21.5
  roof   wind sensor          reads 12
  spare  generic sensor       reads 0
  east   temperature sensor   reads 21.5
```

The vector holds **`std::unique_ptr<Sensor>`**: each slot is a pointer to a `Sensor`, and the object it points at can really be **any** derived class. The loop calls `label()` and `read()` through the base pointer, and each element answers as its own type. If tomorrow someone adds a `PressureSensor`, **this loop does not change**.

Why pointers, and why a smart pointer? Each sensor is a different size, so they cannot sit side by side in the vector itself. They live on the heap, and the vector holds a pointer to each. A `unique_ptr` owns its sensor and deletes it when the vector dies (9.10), which needs the virtual destructor of 11.6.

### Slicing

Now the trap. What if you copy a derived object into a **base-class variable**, by value?

```cpp
WindSensor wind{"mast"};
Sensor sliced{wind};                 // builds a Sensor from the Sensor part of the WindSensor

std::println("original: {} reads {}", wind.label(), wind.read());
std::println("sliced:   {} reads {}   <- a plain Sensor, the wind part is gone", sliced.label(), sliced.read());
```

```
original: wind sensor reads 12
sliced:   generic sensor reads 0   <- a plain Sensor, the wind part is gone
```

A `Sensor` variable has room for a `Sensor`, and nothing more. Copying a `WindSensor` into it copies **only the `Sensor` part** and throws the rest away: this is **slicing**. What is left is a genuine, plain `Sensor`, and its virtual functions run the base versions, because that is what it now is.

```
   WindSensor wind                         Sensor sliced
   ┌──────────────┐                        ┌──────────────┐
   │ Sensor part  │ ── copied ──────────►  │ Sensor part  │
   ├──────────────┤                        └──────────────┘
   │ WindSensor   │ ── cut off, lost
   │ part         │
   └──────────────┘
```

The same happens in a `std::vector<Sensor>`, which holds `Sensor` **values**:

```cpp
std::vector<Sensor> by_value;
by_value.push_back(wind);
by_value.push_back(TemperatureSensor{"copy"});
```

```
vector<Sensor> of the same two:
  mast   generic sensor
  copy   generic sensor
```

Both were pushed in as sensors with a wind or a temperature personality, and both came out as generic. There is no compiler error and no warning, only an object that is not what you stored.

### The rule

**Never copy a polymorphic object into a base-class value.** Hold polymorphic objects through a **reference**, a **pointer**, or a **smart pointer**: all three refer to the real object, and keep its real type.

```cpp
const Sensor& by_reference{wind};
std::println("through a reference: {} reads {}", by_reference.label(), by_reference.read());    // wind sensor reads 12
```

This also explains two choices you saw in 11.3: `inspect` took a **`const Sensor&`**, not a `Sensor`, and the container held **pointers**. A `Sensor` parameter would have sliced every argument. (The project makes the rule enforceable: its `Shape` base class makes the copy operations `protected`, so nobody outside can slice one by accident.)

### The other direction

A base pointer can only call what the **base** declares. `gust()` exists only in `WindSensor`:

```cpp
// sensors[1]->gust();                    // error: Sensor has no member 'gust'
```

To get at it you would need to ask "is this one really a `WindSensor`?". 11.10 shows how, and also why you should usually design so that you do not have to.

**Code for this lecture**: `11.4PolymorphicContainersAndSlicing/main.cpp`.

---

## 11.5 Abstract classes and interfaces

In this lecture we meet a base class that is **not meant to have objects of its own**: it exists only to say what its derived classes must be able to do.

### Pure virtual functions

A virtual function can be declared with **`= 0`**:

```cpp
class Instrument : public Reportable {
public:
    virtual double read() const = 0;              // pure virtual
    virtual std::string unit() const = 0;         // pure virtual
    // ...
};
```

`= 0` means "**there is no implementation here, every concrete derived class must provide one**". A class with at least one pure virtual function is **abstract**, and you **cannot create an object of it**:

```cpp
// Instrument instrument{"x"};              // error: Instrument is abstract
```

You can create objects only of classes that have **filled in every** pure virtual function. A derived class that forgets one is abstract too:

```cpp
class Unfinished : public Instrument {
public:
    using Instrument::Instrument;
    double read() const override { return 0.0; }
    // unit() is missing
};

// Unfinished unfinished{"x"};              // error: unit() is still pure in Unfinished
```

An abstract class is a **contract**. It names what any instrument must be able to do (`read` and `unit`), and leaves the "how" to the derived classes.

### Concrete classes

```cpp
class Thermometer : public Instrument {
public:
    using Instrument::Instrument;
    double read() const override { return 21.5; }
    std::string unit() const override { return "C"; }
};

class Barometer : public Instrument {
public:
    using Instrument::Instrument;
    double read() const override { return 1013.2; }
    std::string unit() const override { return "hPa"; }
};
```

### A template for the derived classes

An abstract class can still contain **ordinary** members, including ones that **use** the pure virtual ones:

```cpp
std::string report() const override {
    return std::format("{}: {:.1f} {}", name_, read(), unit());
}
```

`report()` is written once, in `Instrument`, and works for every instrument. It calls `read()` and `unit()`, and **those** are answered by the real class. The base class supplies the **steps**, the derived classes supply the **details**.

### Interfaces

A class with **nothing but pure virtual functions** (and a virtual destructor) is an **interface**: it says what something can do, and nothing about how.

```cpp
class Reportable {
public:
    virtual ~Reportable() = default;
    virtual std::string report() const = 0;
};
```

A function written against an interface works with **anything** that implements it, even things that have nothing else in common:

```cpp
void print_report(const Reportable& item) {
    std::println("  {}", item.report());
}

class DailySummary : public Reportable {
public:
    std::string report() const override { return "summary: all instruments nominal"; }
};
```

```
through the Reportable interface:
  thermometer: 21.5 C
  barometer: 1013.2 hPa
  summary: all instruments nominal
```

A thermometer, a barometer and a daily summary are three unrelated things, and one function handles them all. And an abstract base is exactly the right element type for a container of different things that share a job:

```
through a container of Instrument pointers:
  north: 21.5 C
  roof: 1013.2 hPa
```

### The design idea

Code that **uses** instruments depends only on `Instrument`. Adding an anemometer means writing **one new class** and changing **no existing code**. That is the real payoff of this chapter, and the project makes it concrete. (Chapter 16 will show the same idea done at compile time, with templates and concepts.)

**Code for this lecture**: `11.5AbstractClassesAndInterfaces/main.cpp`.

---

## 11.6 Virtual destructors

In this lecture we deal with the most important rule of this chapter, the one that every `virtual` function you write quietly depends on.

### The problem

In 11.4 the vector held `std::unique_ptr<Sensor>`. When the vector dies, each `unique_ptr` deletes its object **through a `Sensor` pointer**, even though the object is really a `WindSensor` or a `TemperatureSensor`. Which destructor runs? For a normal function the compiler picks from the **pointer's type**, so it would run the **base** destructor and nothing else. The derived part, and everything it owns, would never be cleaned up.

Here is the bug in its smallest form. `Derived` owns a buffer, and `Base` has an ordinary destructor:

```cpp
class Base {
public:
    ~Base() { std::println("  ~Base"); }                 // NOT virtual
    virtual void work() const {}
};

class Derived : public Base {
public:
    Derived() : buffer_{new int[100]} {}
    ~Derived() {
        std::println("  ~Derived: freeing the buffer");
        delete[] buffer_;
    }
    void work() const override {}

private:
    int* buffer_;
};

Base* bad{new Derived{}};
delete bad;                    // undefined behaviour
```

The program only runs this when you give it the argument `broken`. In a plain build on MSVC:

```
NON-virtual destructor, deleting through a base pointer:
  ~Base
(~Derived was never called: its buffer was leaked)
```

`~Derived` never ran. No crash, no message, exit code 0: just a buffer that is never freed. In the language's terms this is **undefined behaviour**, so another compiler is free to do something else, and a sanitizer (9.12) notices at once. On Linux, AddressSanitizer says:

```
ERROR: AddressSanitizer: new-delete-type-mismatch on 0x7b8ecc7e0050 in thread T0:
  object passed to delete has wrong type:
  size of the allocated type:   16 bytes;
  size of the deallocated type: 8 bytes.
    #1 0x000000406089 in main 11.6VirtualDestructors/main.cpp:78
```

An object of 16 bytes (a `Derived`) was deleted as if it were an 8-byte `Base`. GCC and Clang also warn when they compile that line, with `-Wdelete-non-virtual-dtor` and `-Wdelete-non-abstract-non-virtual-dtor`: **listen to that warning**.

### The fix: a virtual destructor

```cpp
class GoodBase {
public:
    virtual ~GoodBase() { std::println("  ~GoodBase"); }
    virtual void work() const {}
};

class GoodDerived : public GoodBase {
public:
    GoodDerived() : buffer_{new int[100]} {}
    ~GoodDerived() override {
        std::println("  ~GoodDerived: freeing the buffer");
        delete[] buffer_;
    }
    // ...
};
```

A **virtual destructor** makes the choice happen at run time, like any other virtual function, so `delete` through a base pointer finds the **real** type and runs the **derived destructor first**, then the base destructor, in the usual order:

```
virtual destructor, deleting through a base pointer:
  ~GoodDerived: freeing the buffer
  ~GoodBase

the same through a unique_ptr to the base:
  ~GoodDerived: freeing the buffer
  ~GoodBase
```

The second block is the one that matters in modern code: a `std::unique_ptr<GoodBase>` holding a `GoodDerived` does exactly the right thing, because its destructor ends in a `delete` through a `GoodBase` pointer. **The virtual destructor is what makes `std::vector<std::unique_ptr<Sensor>>` safe.**

### The rule

> **A class that is meant to be used through a base-class pointer gets a virtual destructor.**

In practice: **any class with virtual functions that is meant to be derived from.** If you do not need to run any code in it, say so with the shortest form:

```cpp
virtual ~Sensor() = default;
```

That is what every base class in the project and in this chapter's later lectures does. Two notes:

- In a **derived** class, the destructor is virtual automatically once the base's is. You can write `~GoodDerived() override`, as above, and the compiler will check it.
- A class that is **never** used that way (a plain value type such as `Color` or `Location`) does **not** need one. A virtual destructor adds a hidden pointer to every object (11.7), and a class that is not a polymorphic base should not pay for it.

(In 11.2 the `Sensor` destructor was not virtual, and that was acceptable only because no program there deleted a `TemperatureSensor` through a `Sensor` pointer. The moment you do, the rule applies.)

**Code for this lecture**: `11.6VirtualDestructors/main.cpp`. Run it with `broken` as the first argument, and try it under a sanitizer.

---

## 11.7 How virtual functions work

In this lecture we open the hood. You do not need this to **use** polymorphism, but a rough picture of the machinery answers every "why" in the previous lectures, and connects to the assembly of chapter 8.

### The hidden pointer

Compare two small types, the second with one virtual function:

```cpp
struct Plain {
    int value{0};
    void work() const {}
};

struct WithVirtual {
    int value{0};
    virtual void work() const {}
    virtual ~WithVirtual() = default;
};
```

```
sizeof(Plain)       = 4  (just the int)
sizeof(WithVirtual) = 16  (the int, padding, and the hidden pointer)
sizeof(void*)       = 8
```

`WithVirtual` is four times bigger. The compiler added a hidden pointer to **every object** of a class that has virtual functions: the **vptr**. It occupies the first 8 bytes, the `int` follows it, and 4 bytes of padding round the size up to a multiple of 8.

### The table

The vptr points at a table that exists **once per class**, not once per object: the **vtable**. It holds the addresses of that class's virtual functions.

```
   a WithVirtual object              the vtable for WithVirtual (one for the whole class)
   ┌──────────────────┐              ┌───────────────────────────────┐
   │ vptr  ───────────┼────────────► │ address of WithVirtual::work  │
   ├──────────────────┤              │ address of ~WithVirtual       │
   │ value            │              └───────────────────────────────┘
   └──────────────────┘
   a Derived object                   the vtable for Derived
   ┌──────────────────┐              ┌───────────────────────────────┐
   │ vptr  ───────────┼────────────► │ address of Derived::work      │  ← the override
   ├──────────────────┤              │ address of ~Derived           │
   │ value            │              └───────────────────────────────┘
   └──────────────────┘
```

(The picture is simplified: a real table also holds type information, which 11.10 uses, and usually two entries for the destructor.) Two objects of the same class share the same vtable, and a derived class has its own, with **its** overrides in the slots. You can see that on a real machine. The program reads the first 8 bytes of three objects (this is how MSVC, GCC and Clang happen to lay things out on a 64-bit machine, not something the language promises, so it is for learning only):

```
hidden pointer of first:  0x7ff7be328ba0
hidden pointer of second: 0x7ff7be328ba0   same class, same table: true
hidden pointer of third:  0x7ff7be328bb8   Derived has its own table: true
```

### What a virtual call does

```cpp
void call_work(const WithVirtual& object) {
    object.work();
}
```

`call_work` does not know the real type of `object`, so the compiler cannot write a call to a fixed address. Instead it does three things at run time:

1. read the object's **vptr** (the first 8 bytes);
2. read the address of `work` from the **table** it points at;
3. **call** that address.

Here is the assembly for such a call, from GCC and from Clang at `-O0`, using the `-S -masm=intel` command of 8.11:

```
GCC:                                           Clang:
    mov  QWORD PTR [rbp-8], rdi                    mov  qword ptr [rbp - 8], rdi
    mov  rax, QWORD PTR [rbp-8]                    mov  rdi, qword ptr [rbp - 8]
    mov  rax, QWORD PTR [rax]    ← the vptr        mov  rax, qword ptr [rdi]    ← the vptr
    mov  rdx, QWORD PTR [rax]    ← table entry     call qword ptr [rax]         ← call through the table
    mov  rax, QWORD PTR [rbp-8]
    mov  rdi, rax                ← "this" in rdi
    call rdx
```

Read it with what you learned in 8.7. The object's address arrives in `rdi`, the first argument. Then comes **a load of the pointer stored at the start of the object**, and then a **`call` through a register or a memory operand** instead of through a fixed name. That indirect call **is** the virtual call. (Notice that `this` goes into `rdi` as a hidden first argument: in assembly, a member function is just a function whose first parameter is the object.)

### What it costs

```
   space   one pointer per OBJECT (8 bytes here), and one table per class
   time    one extra memory read per virtual call, and the call can rarely be inlined (8.9)
```

A non-virtual function costs nothing extra: it is an ordinary direct call, which the optimiser can inline. In nearly all programs the virtual call is negligible next to the work the function does. It only matters in the innermost loop of a program that makes millions of calls. When the compiler can tell the real type (a local object, or a `final` class), it often removes the lookup entirely, which is one more reason to mark classes `final` when they are the end of a hierarchy.

### What this explains

- **Why slicing loses the behaviour** (11.4): a sliced `Sensor` is a genuine `Sensor`, with the `Sensor` vptr. It never had the `WindSensor` table.
- **Why a virtual destructor is needed** (11.6): the destructor is a slot in the table too, and `delete` through a base pointer must go through the table to find the right one.
- **Why `dynamic_cast` works** (11.10): the table also carries type information, so the program can ask the object what it really is.

**Code for this lecture**: `11.7HowVirtualWorks/main.cpp`.

---

## 11.8 Access control and composition

In this lecture we meet the rest of the inheritance toolbox (`protected` and the other kinds of inheritance), and then the question that decides when to use any of it: **inheritance or composition?**

### Three kinds of inheritance

In `class Derived : public Base`, the word before `Base` controls what outside code sees of the inheritance itself:

```
   inheritance      meaning                        Base's public becomes    conversion to Base
   ───────────      ───────                        ────────────────────     ──────────────────
   public           "is a"                         public                   allowed
   protected        rare                           protected                inside the class and its derived classes
   private          "implemented in terms of"      private                  only inside the class
```

```cpp
class PublicDerived : public Base {
public:
    int use_shared() const { return shared; }      // a protected member of Base: allowed
    // int use_secret() const { return secret; }   // error: private to Base
};

class PrivateDerived : private Base {
public:
    int peek() const { return open; }              // fine inside the class
};
```

From **outside**, none of these compile:

```cpp
// derived.shared;                       // error: protected
// derived.secret;                       // error: private
// PrivateDerived hidden; hidden.open;   // error: private inheritance made it private
// Base& base{hidden};                   // error: no conversion with private inheritance
```

**Use `public` inheritance**, for a real "is a", in about 95% of the cases. With `private` inheritance, nothing outside the class can tell that a `PrivateDerived` was built on a `Base`. And that is exactly what **composition** already says, more plainly.

### Inheritance or composition?

Here is a stack of readings, built both ways:

```cpp
class StackByInheritance : private std::vector<double> {      // implemented in terms of a vector
public:
    using std::vector<double>::size;                           // choose what to expose
    void push(double value) { push_back(value); }
};

class StackByComposition {                                     // HAS a vector
public:
    std::size_t size() const { return items_.size(); }
    void push(double value) { items_.push_back(value); }

private:
    std::vector<double> items_;
};
```

```
two stacks, same behaviour: 1 and 1
```

They behave the same. The second is easier to read, exposes only what it chooses, and does not depend on `std::vector` being a class you can derive from (it was not designed to be a base class: no virtual destructor). **Prefer composition.**

### The test: "is a" for every use

Inheritance is a strong promise: **everywhere a `Base` is expected, a `Derived` must work**. A good test is to say the sentence and mean it for every use:

- "A `TemperatureSensor` **is a** `Sensor`": yes, for everything a sensor does.
- "A `Station` **is a** `Logger`": no. A station **has** a logger.

The second one is easy to get wrong because it **works**:

```cpp
class StationWrong : public Logger {            // claims "is a Logger"
public:
    void start() const { log("starting"); }
};

class StationRight {                            // has a logger, shows nothing of it
public:
    void start() const { logger_.log("starting"); }
private:
    Logger logger_;
};
```

```
the wrong and the right way to share a logger:
  log: starting
  log: starting
  log: anyone can call this on a StationWrong
```

Both start the same. But `StationWrong` has **leaked** `log()` to the whole world: anyone can call `wrong.log(...)` on a station, and any function that takes a `Logger&` accepts a station. The line `right.log("...")` does not compile, as it should. The wrong design gave away its internals to save one member variable.

### The rule of thumb

```
   inherit        when you need an is-a that you will use POLYMORPHICALLY (11.3 to 11.5)
   compose        for everything else, including code reuse on its own
```

A smell to watch for: a class that inherits from a standard container, or from a class "to get its functions". That is reuse, not an is-a, and a member does it better.

**Code for this lecture**: `11.8AccessControlAndComposition/main.cpp`.

---

## 11.9 Multiple inheritance

In this lecture we look at a class that has **more than one** base class: where it is safe and useful, and where it goes wrong.

### The safe use: several interfaces

C++ allows `class X : public A, public B`. The common and harmless use is to combine **interfaces** (11.5), which carry no data, so a class can say it is several things at once:

```cpp
class Reportable {
public:
    virtual ~Reportable() = default;
    virtual std::string report() const = 0;
};

class Rechargeable {
public:
    virtual ~Rechargeable() = default;
    virtual int battery_percent() const = 0;
};

class SolarSensor : public Reportable, public Rechargeable {
public:
    std::string report() const override { return "solar sensor: ok"; }
    int battery_percent() const override { return 87; }
};
```

```
one class implementing two interfaces:
  solar sensor: ok
  battery 87%
```

A `SolarSensor` can be passed to a function that wants a `Reportable&` and to another that wants a `Rechargeable&`. Each sees only its own side. This is the form of multiple inheritance found in well-run code bases, and there is nothing to fear in it.

### The trouble: the diamond

Things change when the bases have **data**, and **share a base of their own**:

```
              Device
             /      |
        Radio        Meter
             |      /
             Station
```

```cpp
struct Device {
    explicit Device(int serial) : serial_number{serial} { ++devices_built; }
    int serial_number;
};

struct Radio : Device { Radio() : Device{1} {} };
struct Meter : Device { Meter() : Device{2} {} };

struct Station : Radio, Meter {};
```

A `Station` is a `Radio` **and** a `Meter`, and each of those contains a `Device`. So a `Station` contains **two** `Device` parts:

```
the diamond, plain inheritance:
  Device parts built: 2
  sizeof(Station) = 8
  Radio's serial: 1, Meter's serial: 2
```

Two serial numbers in one object, and the question "what is this station's serial number?" has no answer. The compiler refuses to guess:

```cpp
// station.serial_number;                // error: ambiguous, Radio's or Meter's?
```

You would have to name the path: `station.Radio::serial_number`.

### The fix: virtual inheritance

If `Radio` and `Meter` inherit **`virtual`**ly from `Device`, the two paths **share one** `Device`:

```cpp
struct VRadio : virtual Device { VRadio() : Device{1} {} };
struct VMeter : virtual Device { VMeter() : Device{2} {} };

struct VStation : VRadio, VMeter {
    VStation() : Device{99} {}               // the most-derived class builds the one Device
};
```

```
the diamond, virtual inheritance:
  Device parts built: 1
  sizeof(VStation) = 24
  the one serial number: 99
```

There is one `Device`, built once, and **the most-derived class** (`VStation`) is the one that supplies its constructor arguments: the `Device{1}` and `Device{2}` in the middle classes are ignored. The object grows (24 bytes instead of 8, here), because it now carries extra hidden pointers to find the shared part.

### When to use what

```
   several interfaces (no data)     safe, common, good
   diamond with data                a sign to rethink: virtual inheritance works, but is rarely worth its cost
   what to do instead               one base class plus interfaces, or composition (11.8)
```

If you meet a diamond in your own design, take the compiler's ambiguity error as a design hint before reaching for `virtual`.

**Code for this lecture**: `11.9MultipleInheritance/main.cpp`.

---

## 11.10 RTTI and casts

In this lecture we answer a question that polymorphism usually makes unnecessary, but sometimes cannot avoid: **"what is this object really?"**

### The situation

You hold a base pointer, and you need something only one derived class has. In 11.4 a `Sensor` pointer could not reach `WindSensor::gust()`. To get at it, you need to ask the object. C++ keeps type information with every object of a class that has virtual functions (the **RTTI**, run-time type information), and gives you two tools to read it.

### `dynamic_cast`: "are you really one of these?"

```cpp
for (const auto& sensor : sensors) {
    if (const auto* wind{dynamic_cast<const WindSensor*>(sensor.get())}) {
        std::println("  {} found, gust {}", wind->label(), wind->gust());
    }
    else {
        std::println("  {} is not a wind sensor", sensor->label());
    }
}
```

```
looking for wind sensors in the list:
  temperature sensor is not a wind sensor
  wind sensor found, gust 18.5
  sensor is not a wind sensor
  wind sensor found, gust 18.5
  arctic sensor is not a wind sensor
```

`dynamic_cast<const WindSensor*>(p)` checks **at run time** whether the object `p` points at is a `WindSensor` (or derived from one). If it is, you get a pointer of the **derived** type, through which `gust()` is reachable. If not, you get **`nullptr`**, and the `if` takes the other branch. The `if (const auto* wind{...})` form declares the pointer and tests it in one line.

Two details:

- It only works on **polymorphic** types, which is to say classes with at least one virtual function. That is why every base class in this chapter has a virtual destructor.
- A **reference** cast has no "null" to return, so `dynamic_cast<const WindSensor&>(x)` **throws** `std::bad_cast` on failure. (Chapter 13 covers exceptions. Use the pointer form until then.)

### `typeid`: "exactly what are you?"

`typeid(x)` gives the exact dynamic type of an object, and two of them can be compared:

```cpp
const Sensor& temperature{*sensors[0]};
const Sensor& arctic{*sensors[4]};

std::println("sensors[0] is exactly a TemperatureSensor: {}", typeid(temperature) == typeid(TemperatureSensor));
std::println("sensors[4] is exactly a TemperatureSensor: {}", typeid(arctic) == typeid(TemperatureSensor));
```

```
sensors[0] is exactly a TemperatureSensor: true
sensors[4] is exactly a TemperatureSensor: false
```

`sensors[4]` is an `ArcticSensor`, a class **derived from** `TemperatureSensor`, so it is not **exactly** one. `dynamic_cast` is the looser test, and in most code it is the one you want, because an `ArcticSensor` **is** a `TemperatureSensor`:

```cpp
const auto* as_temperature{dynamic_cast<const TemperatureSensor*>(sensors[4].get())};
std::println("sensors[4] converts to a TemperatureSensor*: {}", as_temperature != nullptr);
```

```
sensors[4] converts to a TemperatureSensor*: true
  and its calibration offset is 1.5
```

Use `typeid` only when you need the **exact** type, which is rare.

### `static_cast` to a derived type: a promise, not a check

```cpp
// auto* wrong{static_cast<WindSensor*>(sensors[0].get())};   // compiles, a lie
// wrong->gust();                                              // undefined behaviour
```

A `static_cast` from base to derived is checked **only at compile time**: the compiler sees that `WindSensor` derives from `Sensor` and allows it. It does not check the real object. If you are wrong, nothing stops you, and using the result is undefined behaviour. `dynamic_cast` costs a lookup and **tells you**. Use `static_cast` only when you are certain, and you rarely are.

### The design warning

**Every `dynamic_cast` is a small admission that the base class did not offer what the caller needed.** Compare:

```
   asking the object what it is, then acting          asking the object to act
   ─────────────────────────────────────────          ────────────────────────
   if (it is a WindSensor) print its gust              sensor->print_details()    ← a virtual function
```

The right-hand version has no cast, no list of known types to keep in step, and works for kinds that do not exist yet. A chain of `dynamic_cast`s over a list of types is usually a **missing virtual function**. Before you write one, ask: should this be a virtual function on the base?

Casts remain for the cases where that is impossible: code you cannot change, or a rare need to treat one type specially. (And C++ lets you compile with RTTI turned off, `-fno-rtti` or `/GR-`, to save space: `dynamic_cast` and `typeid` then stop working. A design without them is a design that works in either setting.)

**Code for this lecture**: `11.10RttiAndCasts/main.cpp`.

---

## 11.11 `std::variant` and `std::visit`

In this lecture we look at the other way to have "one of several kinds": when the kinds are **fixed and known**, you do not need a base class at all.

### Open or closed

Everything so far was **open**: anyone can add a new derived class later, and code written against the base keeps working. That flexibility costs a pointer per object, a heap allocation, and a virtual call.

Sometimes the set of kinds is **closed**: a reading is a temperature, a humidity or a wind, and that will not change. For that case there is a tool in `<variant>`: a **`std::variant`** is a **value** that holds **exactly one** of a list of types.

```cpp
struct Temperature { double celsius; std::string describe() const; };
struct Humidity    { double percent; std::string describe() const; };
struct Wind        { double speed; double heading; std::string describe() const; };

using Reading = std::variant<Temperature, Humidity, Wind>;
```

A `Reading` is a temperature **or** a humidity **or** a wind, right now. There is no base class, no pointer and no heap: the value is stored **inline**, in room for the largest alternative plus a small tag saying which one is active.

```cpp
std::vector<Reading> readings;
readings.push_back(Temperature{21.5});
readings.push_back(Humidity{63.0});
readings.push_back(Wind{12.0, 270.0});
readings.push_back(Temperature{19.0});
```

### `std::visit`

To do something with a variant, you **visit** it: `std::visit` looks at which alternative is active and calls a function for that one. When every alternative has the same member function, **one generic lambda** will do:

```cpp
for (const Reading& reading : readings) {
    std::println("  {}", std::visit([](const auto& value) { return value.describe(); }, reading));
}
```

```
describe(), through a generic lambda:
  21.5 C
  63 % humidity
  12 km/h at 270 degrees
  19.0 C
```

The `auto` in the lambda's parameter means the compiler writes one version of the lambda for each alternative. When each alternative needs **different** code, use a **visitor**: a struct with one `operator()` per type. (`operator()` is the subject of chapter 12.)

```cpp
struct Summarize {
    std::string operator()(const Temperature& t) const { return std::format("it is {:.1f} degrees", t.celsius); }
    std::string operator()(const Humidity& h) const { return std::format("the air is {:.0f} % wet", h.percent); }
    std::string operator()(const Wind& w) const { return std::format("wind of {} km/h", w.speed); }
};

std::println("  {}", std::visit(Summarize{}, reading));
```

```
Summarize, one case per type:
  it is 21.5 degrees
  the air is 63 % wet
  wind of 12 km/h
  it is 19.0 degrees
```

The valuable part: **leave an alternative out, and the program does not compile.** The compiler checks that **every case is handled**. With a chain of `dynamic_cast`s (11.10), a forgotten case is a silent bug.

### Asking directly

```cpp
std::holds_alternative<Temperature>(first)        // true / false
first.index()                                      // 0 for Temperature, 1 Humidity, 2 Wind

if (const auto* wind{std::get_if<Wind>(&readings[2])}) {
    std::println("readings[2] is a Wind: speed {}", wind->speed);
}
```

```
first holds a Temperature: true
first holds a Wind:        false
index of the active type:  0
readings[2] is a Wind: speed 12
readings[0] is not a Wind
```

`std::get_if<T>` has the same shape as `dynamic_cast`: a pointer to the value if `T` is the active type, `nullptr` if not, but checked against a closed list, with no virtual function and no heap. (`std::get<T>` returns the value itself, and **throws** `std::bad_variant_access` if `T` is not active: prefer `get_if` or `visit`.)

```
sizeof(Reading) = 24  (room for the largest alternative, plus a tag)
```

### Which one to choose

```
                       inheritance                          variant
   kinds               OPEN: anyone can add one             CLOSED: fixed list, in one place
   storage             pointer + heap, virtual call         inline, no heap
   add a new KIND      one new class, nothing else changes  change the list and every visitor
   add a new OPERATION edit the base and every class        one new visitor
   objects             can be large, hold their own state   best for small values
```

Neither is better in general. They are **opposite trade-offs**. Inheritance makes adding **types** easy and adding **operations** hard. A variant makes adding **operations** easy and adding **types** hard. Pick according to what is likely to change. A weather program whose readings come from a fixed list of sensor kinds suits a variant. A drawing program where users add shapes suits inheritance, which is why the next lecture's project uses it.

**Code for this lecture**: `11.11VariantAndVisit/main.cpp`.

---

## 11.12 Project: the shape renderer

In chapter 10 you built a `Canvas` that can paint pixels, rectangles, gradients and borders. Now we draw a picture out of **shapes** that know how to draw **themselves**.

```
   main.cpp builds a scene:            Canvas
                                          ▲
   Group "scene"                          │ draw(canvas)
     ├── Rectangle   (grass)              │
     ├── Circle      (sun)           each shape paints itself,
     ├── Group "station"             a Group asks its children to paint themselves,
     │     ├── Rectangle (wall)      and a child that is a Group does the same again
     │     ├── Triangle  (roof)
     │     ├── Rectangle (door)
     │     ├── Line      (mast)
     │     └── Circle    (sensor)
     └── Group "station"   ← a clone, moved to the right
```

The code is in `11.12ProjectShapeRenderer`. The files `canvas.h`, `canvas.cpp`, `color.h`, `stb_impl.cpp` and `vendor/` are **copied from the chapter 10 project**: this folder is self-contained, as every project is. What is new is `shape.h`, `shapes.h`, `shapes.cpp` and `main.cpp`.

### The interface: `Shape`

```cpp
class Shape {
public:
    virtual ~Shape() = default;

    virtual void draw(Canvas& canvas) const = 0;
    virtual void translate(int dx, int dy) = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual std::string name() const = 0;

    virtual int count() const { return 1; }

protected:
    Shape() = default;
    Shape(const Shape&) = default;
    Shape& operator=(const Shape&) = default;
};
```

`Shape` is **abstract** (11.5): four pure virtual functions say what any shape must do, and no `Shape` object can exist on its own. It has a **virtual destructor** (11.6), because shapes will be held and deleted through `Shape` pointers. And it has a `count()` with a default, which only the group will override.

### The concrete shapes

`Rectangle`, `Circle`, `Line` and `Triangle` each derive from `Shape`, store their own numbers and colour, and implement the four functions. For example, the circle:

```cpp
void Circle::draw(Canvas& canvas) const {
    for (int dy{-radius_}; dy <= radius_; ++dy) {
        for (int dx{-radius_}; dx <= radius_; ++dx) {
            if (dx * dx + dy * dy <= radius_ * radius_) {
                canvas.set_pixel(center_x_ + dx, center_y_ + dy, color_);
            }
        }
    }
}
```

A pixel is inside a circle when its distance from the centre is at most the radius: `dx*dx + dy*dy <= r*r`. The loop tests every pixel of the bounding square. And `set_pixel` from chapter 10 **ignores** anything outside the canvas, so a shape half off the edge needs no special code. The line uses Bresenham's algorithm (integers only, one pixel per step), and the triangle tests, for each pixel of its bounding box, whether it lies on the same side of all three edges. You do not need the maths to follow the chapter: the point is that `main.cpp` never has to know it.

### `clone()`: copying through a base pointer

You cannot copy a `Shape` through a `Shape` pointer with a copy constructor: it would **slice** (11.4), and for an abstract class it would not even compile. The fix is a **virtual function that each class implements for itself**:

```cpp
std::unique_ptr<Shape> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}
```

In `Rectangle::clone`, `*this` has the real type `Rectangle`, so `make_unique<Rectangle>(*this)` runs the `Rectangle` copy constructor and makes a complete copy. The caller receives it as a `unique_ptr<Shape>` and does not need to know what it is. This is called the **virtual constructor** idiom, and every polymorphic class that must be copied has one.

The protected copy operations in `Shape` fit this exactly: the derived classes **can** be copied (so `clone()` works), but code **outside** the hierarchy cannot copy a `Shape` by value and slice it by accident.

### `Group`: a shape made of shapes

```cpp
class Group : public Shape {
public:
    explicit Group(std::string label);
    Group& add(std::unique_ptr<Shape> shape);

    void draw(Canvas& canvas) const override;
    // ...
private:
    std::string label_;
    std::vector<std::unique_ptr<Shape>> children_;
};

void Group::draw(Canvas& canvas) const {
    for (const auto& child : children_) {
        child->draw(canvas);
    }
}
```

`Group` is a `Shape` **and** it has shapes (10.11's composition, together with this chapter's inheritance). Its `draw` is one loop: **every child draws itself as its own type**. Because a `Group` is itself a `Shape`, a child can be another group, and the loop just recurses. `translate` moves every child. `count()` adds up the children's counts. And `clone()` makes a **deep copy**: it clones every child, so the copy shares nothing with the original:

```cpp
std::unique_ptr<Shape> Group::clone() const {
    auto copy{std::make_unique<Group>(label_)};
    for (const auto& child : children_) {
        copy->add(child->clone());
    }
    return copy;
}
```

### The scene

`main.cpp` builds one station and puts it in a scene twice:

```cpp
Group station{"station"};
station.add(std::make_unique<Rectangle>(60, 160, 90, 60, wall))
       .add(std::make_unique<Triangle>(Point{50, 160}, Point{105, 110}, Point{160, 160}, roof_red))
       .add(std::make_unique<Rectangle>(95, 185, 20, 35, door_brown))
       .add(std::make_unique<Line>(Point{180, 220}, Point{180, 120}, mast_grey, 4))
       .add(std::make_unique<Circle>(180, 112, 9, sensor_red));

Group scene{"scene"};
scene.add(std::make_unique<Rectangle>(0, 220, 400, 80, grass))
     .add(std::make_unique<Circle>(340, 55, 32, sun_yellow))
     .add(station.clone());

auto second_station{station.clone()};
second_station->translate(175, 12);
scene.add(std::move(second_station));
```

The chain of `.add(...)` calls works because `add` returns `*this` (10.10). The second station is a **clone** of the first, moved 175 pixels right and 12 down. Then:

```cpp
Canvas canvas{400, 300, sky};
scene.draw(canvas);
canvas.write_png("scene.png");
```

```
Group 'scene' (12 shapes)
  Rectangle 400x80
  Circle r=32
  Group 'station' (5 shapes)
  Group 'station' (5 shapes)

wrote scene.png (400 x 300)
```

Each line of the listing is a virtual call to `name()`. The 12 is the sum of the shapes in the whole tree, found with one virtual call to `count()`: the two loose shapes and 5 in each station. The picture is two little weather stations with a mast, a red sensor on top, a sun and a lawn.

### The payoff

Look at what `main.cpp` does **not** contain: any mention of how a circle or a triangle is drawn, any `if` on the kind of shape, any cast. `scene.draw(canvas)` is one call. And now do this:

> **Try it**: add a class `Ellipse`, derived from `Shape`, in its own header and source file, implement the four functions, and add one to the scene.

Not one line of `Canvas`, `Group`, `Shape` or the existing shapes needs to change. That is what "open for extension" means, and it is the reason for everything in this chapter.

### Check it with the tools from chapter 9

A tree of owning pointers that is cloned and deleted through base pointers is exactly where a missing virtual destructor or a shallow copy would hide. We ran the project under AddressSanitizer and UndefinedBehaviorSanitizer with both GCC and Clang, with `-Wall -Wextra`:

```sh
g++ -std=c++23 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer \
    -isystem vendor main.cpp shapes.cpp canvas.cpp stb_impl.cpp -o shapes
./shapes
```

No warnings and no reports. **Try it**: remove the `virtual` from `~Shape()` and build again. The compiler now warns that `delete` is called on a class with virtual functions and a non-virtual destructor, and the sanitizer stops the program with a `new-delete-type-mismatch`: a 32-byte `Rectangle` was deleted as if it were an 8-byte `Shape`.

**Code for this project**: `11.12ProjectShapeRenderer/` (`shape.h`, `shapes.h`, `shapes.cpp`, `main.cpp`, the Canvas files, `CMakeLists.txt`).

---

## 11.13 Assignment

Eight small jobs for the weather station's instruments: construction order, `virtual` and `override`, a polymorphic container, an abstract class, the virtual destructor, slicing, `dynamic_cast`, and `std::variant`. `main.cpp` has the eight exercises, each with its statement and a sample run in a comment; a small `Sensor` hierarchy is provided for exercise 7. You write each class above `main()` and the lines that use it in `main()` under its heading. `main_solution.cpp` solves all eight. Built as two executables (`rooster`, `rooster_solution`).

| # | Exercise | Tools |
|---|----------|-------|
| 1 | `Instrument` and `Barometer` | a derived class, the base constructor in the initializer list, the order of construction and destruction |
| 2 | `Gauge`, `Thermometer2`, `Barometer2` | `virtual`, `override`, a function that takes a `const Gauge&` and still prints each object's own values |
| 3 | a vector of gauges | `std::vector<std::unique_ptr<Gauge>>`, `std::make_unique`, one loop for every kind |
| 4 | `Alarm`, `HighAlarm`, `LowAlarm` | an abstract class with a pure virtual function, a non-virtual member, a vector of owning base pointers |
| 5 | `Base` and `Derived` | a virtual destructor, and what happens without it |
| 6 | slicing | copying a derived object into a base value, and a reference that keeps the real type |
| 7 | counting anemometers | `dynamic_cast` on a raw pointer from a `unique_ptr`, a running maximum |
| 8 | `Value` | `std::variant<int, double, std::string>`, `std::visit` with a visitor struct |

The quiz (`QUIZ.md`) is 20 multiple-choice questions across the whole chapter.

After this chapter the student can build and use a class hierarchy: design an abstract interface, override virtual functions, hold polymorphic objects safely through smart pointers, give a base class a virtual destructor, and judge when a cast, composition or a `std::variant` is the better answer. The next chapter looks at **operators**: how your own classes can be added, compared and printed like the built-in types.
