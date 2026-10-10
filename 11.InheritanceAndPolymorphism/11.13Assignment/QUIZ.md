# Chapter 11 Quiz - Inheritance and Polymorphism

20 multiple-choice questions covering **Chapter 11 (Inheritance and Polymorphism)**:
base and derived classes, `virtual` and `override`, polymorphic containers and
slicing, abstract classes, virtual destructors, how virtual calls work, access
control and composition, multiple inheritance, `dynamic_cast`, and
`std::variant`. Each question is followed immediately by its correct answer and a
short explanation.

---

### 1. In `class TemperatureSensor : public Sensor`, what does `: public Sensor` say?

A. A TemperatureSensor contains a Sensor as a private member
B. A TemperatureSensor IS A Sensor: it gets Sensor's public and protected members and can be used wherever a Sensor is expected
C. Sensor is allowed to see TemperatureSensor's private members
D. TemperatureSensor can only be created by Sensor

**Answer: B** - public inheritance models "is a". A derived object converts to a reference or pointer to its base without a cast.

### 2. A `TemperatureSensor` derives from `Sensor`. Which order do the constructors run in?

A. TemperatureSensor's, then Sensor's
B. Whichever is declared first in the file
C. Both at once
D. Sensor's first, then TemperatureSensor's

**Answer: D** - the base part must exist before the derived part can be built, so the derived constructor calls the base constructor first (in its initializer list). Destructors run in the opposite order.

### 3. A base class has a private data member `id_`. Can a derived class's member function use it directly?

A. Yes, derived classes inherit access to everything
B. Yes, but only through `this->`
C. No: it is private to the base. The derived class must use a public or protected member of the base
D. Only if the derived class is declared `friend`

**Answer: C** - private means "this class only". A `protected` member is the level that derived classes may also use.

### 4. What does `virtual` change about a member function?

A. The version to run is chosen when the program runs, from the real type of the object, instead of at compile time from the declared type
B. It makes the function run faster
C. It makes the function private
D. It stops derived classes from having the same function

**Answer: A** - through a base reference or pointer, a virtual call goes to the derived class's version. A non-virtual call goes to the version of the declared type.

### 5. Why should an overriding function be marked `override`?

A. Without it, the function is not virtual
B. The compiler checks that the base really has a virtual function with the same signature, and refuses otherwise, which catches typos and a missing `const`
C. It makes the function faster
D. It lets the function access private members of the base

**Answer: B** - without `override`, a mismatch (say, a forgotten `const`) silently creates a new, unrelated function that is never called through the base.

### 6. A derived class declares `std::string kind() const` with the same name and signature as a **non-virtual** `Sensor::kind()`. A function holding a `const Sensor&` calls `kind()`. Which one runs?

A. The derived one
B. Neither: it does not compile
C. Both
D. The base one: a non-virtual function is chosen by the declared type, and the derived function only hides it

**Answer: D** - only virtual functions follow the real type. Declaring another function with the same name in the derived class hides the base's, but does not override it.

### 7. What is slicing?

A. Dividing a vector into parts
B. Deleting part of an object
C. Copying a derived object into a base-class VALUE, which keeps only the base part, so its virtual functions run the base versions
D. Calling a virtual function without a pointer

**Answer: C** - `Sensor sliced{wind};` copies just the Sensor part of the WindSensor. To avoid it, hold polymorphic objects through references, pointers or smart pointers, never as base-class values.

### 8. Why is `std::vector<std::unique_ptr<Sensor>>` the usual type for a collection of different sensors?

A. Each slot holds a pointer to a Sensor, which can really be any derived object, so the elements keep their real types and nothing is sliced
B. `unique_ptr` is required for virtual calls
C. A vector of objects cannot hold a class that has a constructor
D. It uses less memory than a vector of Sensor

**Answer: A** - a `std::vector<Sensor>` would have room for a Sensor in each slot and slice whatever was pushed in. Pointers refer to the full objects.

### 9. What does `virtual double read() const = 0;` make a class?

A. Final: it cannot be derived from
B. A template
C. Static: it cannot have objects
D. Abstract: it cannot be instantiated, and every concrete derived class must override `read()`

**Answer: D** - `= 0` marks a pure virtual function. An abstract class is a contract: it says what a derived class must provide, without providing it.

### 10. A class has only pure virtual functions (and a virtual destructor) and no data. What is it usually called?

A. An interface
B. A namespace
C. A struct
D. An aggregate

**Answer: A** - it says what something can do and nothing about how. A class may inherit from several interfaces at once without trouble.

### 11. `Base* p{new Derived};  delete p;` where `Base` has a **non-virtual** destructor. What happens?

A. `~Derived` and `~Base` both run, in the right order
B. The program does not compile
C. Undefined behaviour: in practice `~Derived` is skipped, so what `Derived` owns is leaked
D. Only `~Derived` runs

**Answer: C** - the compiler decides which destructor to call from the pointer's type. AddressSanitizer reports it as `new-delete-type-mismatch`. The fix is `virtual ~Base() = default;`.

### 12. Which classes should have a virtual destructor?

A. Every class
B. Classes that are used through a base-class pointer, which means any class with virtual functions that is meant to be derived from
C. Only classes with a pointer member
D. Only abstract classes

**Answer: B** - a plain value type that is never deleted through a base pointer does not need one. Any class designed as a polymorphic base does.

### 13. On a 64-bit machine, `struct Plain { int value; };` is 4 bytes. Why is `struct WithVirtual { int value; virtual void work() const {} };` 16 bytes?

A. Virtual functions are stored inside every object
B. The compiler pads every class with virtual functions
C. A hidden pointer to the class's table of virtual functions (the vptr) is added to every object, and padding follows
D. The int becomes a long

**Answer: C** - 8 bytes for the vptr, 4 for the int and 4 of padding. The table itself (the vtable) exists once per class, not once per object.

### 14. What does a virtual call through a base reference compile to?

A. A direct call to the base class's function
B. A search for the function by name at run time
C. A new object being created
D. Loading the object's vptr, reading the function's address from the table, and calling through it: one indirect call

**Answer: D** - in the assembly it is a load of the pointer at the start of the object, then a `call` through a memory operand. That is the whole cost: one extra read per call, and the call usually cannot be inlined.

### 15. When is `private` inheritance (`class Stack : private std::vector<double>`) usually better replaced with a member?

A. Always: a member (`std::vector<double> items_;`) says "has a" more plainly, and exposes nothing you did not choose
B. Never: private inheritance is always better
C. Only for classes without constructors
D. Only when the base is abstract

**Answer: A** - private inheritance means "implemented in terms of", which is what composition already says, with fewer surprises. Prefer composition unless you specifically need access to protected members or to override virtual functions.

### 16. Which sentence best decides between inheritance and composition?

A. Use inheritance whenever two classes share code
B. If you can say "B is an A" and mean it for every use of A, inherit. If it is "B has an A", use a member
C. Always use composition
D. Always use inheritance

**Answer: B** - a Station is not a Logger, it has one. Reusing code alone is not a reason to inherit, because inheritance also gives every user of the derived class the base's whole public interface.

### 17. A `Station` inherits from `Radio` and `Meter`, and both inherit from `Device` (with data). How many `Device` parts does a `Station` contain, and how is that changed?

A. One, always
B. Two (the diamond problem). Making both inherit `virtual Device` shares a single copy
C. Two, and it cannot be changed
D. None: Device is abstract

**Answer: B** - plain inheritance gives each path its own copy, so `station.serial_number` is ambiguous. Virtual inheritance builds one shared Device, constructed by the most-derived class. Interfaces with no data avoid the problem altogether.

### 18. `dynamic_cast<WindSensor*>(sensor)` returns `nullptr`. What does that mean?

A. The cast crashed
B. `sensor` is null
C. The object `sensor` points at is not a `WindSensor` (nor derived from one)
D. `WindSensor` has no virtual functions

**Answer: C** - the check happens at run time using the object's type information. The reference form, `dynamic_cast<WindSensor&>`, throws `std::bad_cast` instead of returning null.

### 19. What is the design warning attached to `dynamic_cast`?

A. It is deprecated
B. It only works on `const` objects
C. It cannot be used with smart pointers
D. Needing it often means the base class lacks a virtual function the caller wanted: asking an object what it is, and then acting, is often better replaced by asking it to act

**Answer: D** - `if (is a WindSensor) print gust` is the sign. A `virtual void print_details()` on the base lets each class do its own thing, with no cast.

### 20. When is a `std::variant<Temperature, Humidity, Wind>` a better fit than a base class with three derived classes?

A. When the set of kinds is closed and known, so values can be stored inline with no pointers and no heap, and the compiler checks that every case is handled
B. When anyone may add new kinds later
C. When the objects are very large
D. Never: variant is slower in every case

**Answer: A** - with a variant, adding a new operation is one new visitor, but adding a new type means changing the list and every visitor. With inheritance it is the other way round, and the set of types stays open.
