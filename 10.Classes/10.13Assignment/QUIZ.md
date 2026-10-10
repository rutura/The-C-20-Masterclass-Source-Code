# Chapter 10 Quiz - Classes

20 multiple-choice questions covering **Chapter 10 (Classes)**: private data and
invariants, constructors and initializer lists, splitting a class across a header
and a source file, `const` member functions, destructors and RAII, copying, moving,
the rules of zero and five, `static`, `this`, `friend`, and composition. Each
question is followed immediately by its correct answer and a short explanation.

---

### 1. What is the main reason to make a class's data members private?

A. It makes the program run faster
B. Outside code can only change the data through the class's own functions, so the class can enforce its rules
C. It saves memory
D. It lets the data be used without declaring it

**Answer: B** - private members cannot be touched from outside, so a rule such as "the offset stays between -5 and 5" is written once, in the member functions, and cannot be bypassed.

### 2. What is the only technical difference between `struct` and `class`?

A. The default access: members of a struct are public, members of a class are private
B. A struct cannot have member functions
C. A class can be copied and a struct cannot
D. A struct is stored on the stack, a class on the heap

**Answer: A** - everything else is the same. By habit, a struct is used for plain data with no rules, and a class for something that must stay valid.

### 3. Why is a member initializer list (`: id_{id}, name_{name}`) better than assigning inside the constructor body?

A. It is required for every class
B. It makes the constructor run only once
C. It builds each member directly with its value instead of default-constructing it first, and it is the only way to initialize `const` and reference members
D. It lets the constructor take no parameters

**Answer: C** - assignment in the body means the member was already built, with a default value, and then overwritten. For a `const` member, there is no assignment at all, so the list is the only possible place.

### 4. A class declares `Noisy first_;` and then `Noisy second_;`, but its constructor's initializer list names `second_` first. In what order are they initialized?

A. `second_`, then `first_`: the order of the list
B. Both at once
C. In alphabetical order
D. `first_`, then `second_`: the order of the declarations

**Answer: D** - members are always initialized in declaration order, whatever the list says. Compilers warn about a list that disagrees (`-Wreorder`), because it hides the real order.

### 5. What does marking a one-argument constructor `explicit` do?

A. It makes the constructor run faster
B. It stops the compiler from using it for silent conversions, such as turning a bare `int` into the class
C. It makes the constructor private
D. It makes the class impossible to copy

**Answer: B** - without `explicit`, `describe(15)` could quietly build an object from the number 15. With it, the conversion has to be written out.

### 6. What is a delegating constructor?

A. One that forwards to another constructor of the same class, so the setup logic is written once
B. One that constructs a base class
C. One that is run by the destructor
D. One that is inherited from a parent

**Answer: A** - `Sensor(int id, const std::string& name) : Sensor{id, name, 0.0} {}` hands the work to the full constructor.

### 7. What does the `const` at the end of `double offset() const` mean?

A. The function returns a constant
B. The function can only be called once
C. The function promises not to change the object, and can therefore be called on a `const` object
D. The offset can never change

**Answer: C** - the compiler checks the promise inside the function, and a `const Sensor&` parameter can only call such functions. Mark every member function that only looks.

### 8. What is `mutable` for?

A. It lets a member be changed from outside the class
B. It makes a member `static`
C. It makes the whole object writable
D. It exempts one member (a cache or a counter) from `const`, so a `const` member function can still update it

**Answer: D** - for bookkeeping that is not part of the object's real state, such as counting how often a `const` function was called. Use it sparingly.

### 9. In `sensor.cpp`, a definition starts with `double Sensor::offset() const`. What does `Sensor::` do?

A. It creates a new Sensor
B. It says the function belongs to the class `Sensor`, rather than being an unrelated free function
C. It makes the function static
D. It includes the header

**Answer: B** - `::` is the scope resolution operator. The header holds the declaration (what a Sensor is), the source file holds the definitions, and the linker joins them (7.12).

### 10. Three local objects `a`, `b` and `c` are created in that order in one scope. In what order are their destructors run when the scope ends?

A. `c`, `b`, `a`: the reverse of creation
B. `a`, `b`, `c`: the same order as creation
C. In an unspecified order
D. Only the first one's destructor runs

**Answer: A** - the last object built is the first destroyed. Members of a class follow the same rule, in reverse order of their declaration.

### 11. What does RAII mean in practice?

A. Every object must be allocated on the heap
B. Resources must be freed by a separate cleanup function
C. A resource (memory, a file, a lock) is acquired in an object's constructor and released in its destructor, so it is released on every path out of the scope
D. Objects must never be copied

**Answer: C** - the destructor runs on a normal exit, an early `return` and an exception alike, which is what a manual `delete` could not promise. `std::vector` and `std::unique_ptr` are RAII types.

### 12. A class owns a block of memory through a raw `int*` and writes a destructor that does `delete[]`, but nothing else. What goes wrong when an object is copied?

A. Nothing: the copy is a separate object
B. The program does not compile
C. The copy allocates its own block, which wastes memory
D. The compiler-written copy copies only the pointer, so two objects own one block, and the second destructor deletes it again

**Answer: D** - a shallow copy leads to a double delete. A class that owns a resource has to say what copying it means: a deep copy, or no copy at all.

### 13. Why does a copy assignment operator begin with `if (this == &other)`?

A. To make sure the object is not `const`
B. To make `a = a` safe: without it, the operator would delete the memory that it is about to copy from
C. To count how many assignments happened
D. To prevent copying from a temporary

**Answer: B** - self-assignment is legal and happens indirectly, such as `v[i] = v[j]` with `i == j`. Freeing the old block before reading the source would destroy the data.

### 14. After `ReadingLog moved{std::move(original)};`, what is the state of `original` in a well-written class?

A. Valid but empty: the block was stolen, and it can still be destroyed or assigned to safely
B. Unchanged, still holding all its data
C. Destroyed, and must not be named again
D. Undefined: any use is a crash

**Answer: A** - a moved-from object must remain safe to destroy and to assign to. Our move constructor leaves it with a null pointer and size zero, and `delete[] nullptr` is allowed.

### 15. What does `std::move(x)` do by itself?

A. It copies `x` more efficiently
B. It moves the data of `x` into a new variable
C. It only casts `x` to a type that allows moving, so the move constructor is chosen instead of the copy constructor
D. It deletes `x`

**Answer: C** - nothing moves until a move constructor or move assignment runs. After `std::move`, you should treat `x` as something you are finished with.

### 16. A `std::vector<T>` has to grow. Why does it matter whether `T`'s move constructor is `noexcept`?

A. `noexcept` makes the move faster
B. Without `noexcept`, the vector cannot grow
C. It does not matter
D. If the move might throw, the vector falls back to copying the elements, to keep its strong guarantee

**Answer: D** - a move that fails halfway cannot be undone, but a copy can be abandoned safely. So the vector only moves when it knows the move cannot throw. In the lecture, `Careless` was copied and `Quiet` never was.

### 17. What is the rule of zero?

A. A class should have no member functions
B. Design a class so that its members (a `std::vector`, a `std::unique_ptr`) manage themselves, and write no destructor, copy or move operations at all
C. Never write a constructor
D. Delete every special member function

**Answer: B** - if each member already knows how to destroy, copy and move itself, the compiler-written versions are correct. A class that wraps a vector is eight lines instead of thirty.

### 18. A class writes its own destructor to release a resource. According to the rule of five, what else should it consider writing or deleting?

A. The copy constructor, copy assignment, move constructor and move assignment
B. Nothing else
C. A second destructor
D. A static member

**Answer: A** - needing a custom destructor is a sign that the class owns something, and then the default copy and move are probably wrong. Either write them, or delete them with `= delete`.

### 19. What is true of a `static` data member such as `static inline int issued_{0};`?

A. Each object has its own copy
B. It can only be used inside a `static` function
C. There is exactly one, shared by every object of the class, and it exists even when no object does
D. It is destroyed every time an object is

**Answer: C** - it belongs to the class itself. A `static` member *function* has no `this` pointer, so it can only touch static members, and it is called with the class name: `Ticket::issued()`.

### 20. A `Station` class declares members `name_`, `where_`, `antenna_` and `battery_` in that order. When a `Station` goes out of scope, what is the order of events?

A. The members are destroyed first, then the destructor body runs
B. Only the destructor body runs: members are not destroyed
C. The members are destroyed in the order they were declared
D. The destructor body runs first, then the members are destroyed in reverse order of declaration: `battery_` before `antenna_`

**Answer: D** - construction is the mirror image: the members are built in declaration order before the constructor body runs. The same last-in, first-out rule applies to everything in this chapter.
