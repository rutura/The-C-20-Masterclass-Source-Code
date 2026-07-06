# Table of Contents — The C++23/26 Masterclass (New Order)

This is the student-facing course outline in the order lectures are actually watched (per `CPP_23_UPDATE.md` §2). Chapter numbers in parentheses are the original source-folder numbers, kept for traceability — they no longer indicate teaching order.

---

## Arc 1 — Ship Something on Day One

### Chapter 0 — Ship Something on Day One *(new)*
A fast, shallow first pass across several later chapters, compressed to the minimum needed to build one real program. Each topic returns for a full treatment later in Arc 2 — this chapter is deliberately not the deep version.

| # | Lecture | Covers |
|---|---|---|
| 0.1 | Print, Read, Compile | Compiling and running a program; `std::print`/`std::println` (C++23); reading input with `std::cin` and `std::getline`. |
| 0.2 | Storing Data | Declaring `int`, `bool`, `auto`, and `std::string`; assigning and re-assigning values. |
| 0.3 | Deciding and Repeating | `if`/`else if`; indexed `for` loops; range-based `for` loops over a list. |
| 0.4 | Holding a List | Constructing a `std::vector<std::string>`; `push_back`; printing it with a range-based `for` loop. |
| 0.5 | Packaging Into Functions | Splitting logic into `add_task`, `list_tasks`, `remove_task` functions — informally, no parameter-passing theory yet. |

**→ Milestone: Project 1, Task Tracker CLI, v0 — a working add/list/remove command-line task list, built and running by the end of Chapter 0.**

---

## Arc 2 — Depth Pass on the Fast-Path Topics

### Chapter 3 — First Steps *(was ch.03)*
| # | Lecture | Covers |
|---|---|---|
| 3.1 | Your First C++ Program | `#include`, `int main()`, `std::cout`, compiling and running. |
| 3.2 | Comments | `//` and `/* */` comments. |
| 3.3 | Errors and Warnings | Reading a compiler error and a runtime error. |
| 3.4 | Statements and Functions | A full function with parameters and a return value, seen before functions are formally taught. |
| 3.5 | Data Input and Output | `std::cin`, `std::getline`, `std::cerr`, `std::clog`. |

### Chapter 4 — Variables and Data Types *(was ch.04)*
| # | Lecture | Covers |
|---|---|---|
| 4.1 | Number Systems | Decimal, octal, hex, and binary integer literals. |
| 4.2 | Integer Types | Declaring `int` with brace-, functional-, and assignment-initialization; `sizeof`. |
| 4.3 | Integer Modifiers | `short`, `long`, `unsigned`, `signed`, and their combinations. |
| 4.4 | Fractional Numbers | `float`, `double`, `long double`; precision, scientific notation, `inf`/`NaN`. |
| 4.5 | Booleans | `bool`, using it in `if`, `std::boolalpha`. |
| 4.6 | Characters and Text | `char`, ASCII values, `static_cast<int>`. |
| 4.7 | Auto | Type deduction with `auto` across literal suffixes (`u`, `ul`, `ll`, `f`). |
| 4.8 | Assignments | Re-assigning a variable after declaration; the `auto` narrowing pitfall. |

### Chapter 5 — Operations on Data *(was ch.05, absorbs old ch.07)*
| # | Lecture | Covers |
|---|---|---|
| 5.1 | Basic Operations | Arithmetic operators on numbers. |
| 5.2 | Precedence and Associativity | Order of evaluation in compound expressions. |
| 5.3 | Increment and Decrement | Prefix vs. postfix `++`/`--`. |
| 5.4 | Compound Assignment Operators | `+=`, `-=`, `*=`, etc. |
| 5.5 | Relational Operators | `<`, `>`, `<=`, `>=`, `==`, `!=`. |
| 5.6 | Logical Operators | `&&`, `||`, `!`. |
| 5.7 | Output Formatting | Controlling how numbers print. |
| 5.8 | Numeric Limits | `std::numeric_limits`. |
| 5.9 | Math Functions | `<cmath>` functions. |
| 5.10 | Weird Integral Types | Edge cases in the integer type family. |
| 5.11 | Conversions, Overflow, and Underflow | Implicit narrowing conversions, explicit `static_cast`, and unsigned integer wraparound *(merged in from old ch.07 — Conversions/Overflow/Underflow)*. |

### Chapter 6 — Literals and Constants *(was ch.06)*
| # | Lecture | Covers |
|---|---|---|
| 6.1 | Literals | Integer, floating, character, and string literal forms. |
| 6.2 | Constants | `const`. |
| 6.3 | Constant Expressions | `constexpr`. |
| 6.4 | `constinit` | Compile-time-initialized, runtime-mutable variables. |

### Chapter 9 — Variable Lifetime and Scope *(was ch.09)*
| # | Lecture | Covers |
|---|---|---|
| 9.1 | Variable Scope | Block scope, shadowing, and lifetime. |

### Chapter 10 — Flow Control *(was ch.10)*
| # | Lecture | Covers |
|---|---|---|
| 10.1 | If Statements | `if`, `if`/`else`, nested conditions. |
| 10.2 | Else If | Multi-branch decision chains. |
| 10.3 | Switch | `switch`/`case`/`break`. |
| 10.4 | Short-Circuit Evaluation | How `&&`/`||` skip evaluating their right side. |
| 10.5 | Integral Logic Conditions | Treating integers as booleans in conditions. |
| 10.6 | Ternary Operator | The `?:` conditional expression. |
| 10.7 | `if constexpr` | Compile-time branching. |
| 10.8 | If with Initializer | The C++17 `if (init; condition)` form. |
| 10.9 | Switch with Initializer | The same pattern applied to `switch`. |
| 10.10 | Variable Scope Revisited | Scope rules inside `if`/`switch` blocks. |
| 10.11 | Switch Scope | Scoping pitfalls specific to `switch` statements. |

### Chapter 11 — Loops *(was ch.11, drops `FixCalculator`)*
| # | Lecture | Covers |
|---|---|---|
| 11.1 | For Loop | The classic indexed `for` loop. |
| 11.2 | For Loop, Multiple Declarations | Declaring more than one loop variable. |
| 11.3 | Comma Operator | Using `,` to sequence expressions. |
| 11.4 | Range-Based For Loop | Iterating a collection without manual indexing. |
| 11.5 | While Loop | The `while` loop. |
| 11.6 | Huge Loops with Output | Performance/output considerations in large loops. |
| 11.7 | Do-While Loop | The `do`/`while` loop. |
| 11.8 | Infinite Loops | Writing and recognizing infinite loops. |
| 11.9 | Infinite Loop Practice | Applied practice with intentional infinite loops. |
| 11.10 | Decrementing Loops | Loops that count down. |
| 11.11 | Nested Loops | Loops inside loops. |
| 11.12 | Break and Continue | Early exit and skip-iteration control flow. |
| 11.13 | For Loop with Init-Condition | Combining initialization and condition idioms. |

### Chapter 12 — Arrays *(was ch.12, adds `std::array`, drops both Fortune Teller lectures)*
| # | Lecture | Covers |
|---|---|---|
| 12.1 | Declaring and Using Arrays | Fixed-size C-style array basics. |
| 12.2 | Size of an Array | `sizeof` on arrays. |
| 12.3 | Arrays of Characters | Character arrays as primitive strings. |
| 12.4 | Array Bounds | Out-of-bounds access and why it's dangerous. |
| 12.5 | Generating Random Numbers | `<random>` basics, used to drive array examples. |
| 12.6 | Multi-Dimensional Arrays | 2D arrays. |
| 12.7 | Multi-Dimensional Arrays of Characters | 2D character arrays / grids of text. |
| 12.8 | `std::array` *(new)* | The safe, fixed-size alternative to a raw array. |

**→ Milestone: Project 1 gains a fixed-size lookup table (e.g. priority-level names) via `std::array`.**

### Chapter 15 — Character Manipulation and Strings *(was ch.15)*
| # | Lecture | Covers |
|---|---|---|
| 15.1 | Character Manipulation | Working with individual `char` values. |
| 15.2 | C-String Manipulation | Null-terminated `char*` strings. |
| 15.3 | C-String Concatenation and Copy | `strcat`, `strcpy`, and their pitfalls. |
| 15.4 | Declaring and Using `std::string` | Constructing, assigning, and printing `std::string`. |
| 15.5 | Concatenating `std::string`s | `+`, `+=`, `.append()`, `std::to_string`. |
| 15.6 | Accessing Characters in `std::string` | Indexing, `.at()`, `.front()`/`.back()`. |
| 15.7 | Size and Capacity | `.size()`, `.capacity()`, `.empty()`. |
| 15.8 | Modifying `std::string`s | In-place mutation methods. |
| 15.9 | Comparing `std::string`s | `==`, `.compare()`. |
| 15.10 | `std::string` Compare, Deep Dive | The full return-value semantics of `.compare()`. |
| 15.11 | Replacing, Copying, Resizing, Swapping | `.replace()`, `.copy()`, `.resize()`, `.swap()`. |
| 15.12 | Searching `std::string` | `.find()` and friends. |
| 15.13 | Transforming `std::string` To/From Numbers | `std::stoi`/`std::stod`/`std::to_string` round-trips. |
| 15.14 | Escape Sequences | `\n`, `\t`, `\\`, etc. |
| 15.15 | Raw String Literals | `R"(...)"`. |
| 15.16 | Copied Strings | Value semantics of `std::string` copies. |
| 15.17 | `string_view` | Non-owning string references. |

**→ Milestone: Project 1's text handling deepens — trimming and searching task descriptions properly.**

### Chapter 16 — Functions *(was ch.16, pass-by-X consolidated)*
| # | Lecture | Covers |
|---|---|---|
| 16.1 | Your First Functions | Void/value-returning functions, with and without parameters — informal first pass. |
| 16.2 | Function Declarations and Definitions | Prototypes vs. definitions; declaring before `main`. |
| 16.3 | Multiple Files: The Compilation Model Revisited | Splitting function declarations/definitions across files. |
| 16.4 | Passing Parameters, Compared *(merged — was 6 lectures)* | Pass-by-value, const-value, pointer, pointer-to-const, const-pointer-to-const, reference, and const-reference, shown side by side in one comparison: which variants allow mutation, which avoid a copy. |
| 16.5 | Array Function Parameters | Passing raw arrays to functions. |
| 16.6 | Sized Array Function Parameters | Passing array size alongside the array. |
| 16.7 | Sized Arrays by Reference | Passing a fixed-size array by reference (size baked into the type). |
| 16.8 | Multi-Dimensional Array Function Parameters | Passing 2D arrays. |
| 16.9 | Default Function Parameters | Parameters with default values. |
| 16.10 | Implicit Conversions | How arguments convert to match a parameter's type — by value, by reference, and by pointer. |
| 16.11 | `string_view` Parameters | Preferring `string_view` for read-only string parameters; implicit conversion from `string_view` to `string`. |
| 16.12 | `constexpr` and `consteval` Functions | Compile-time-evaluable functions. |

**→ Milestone: Project 1's functions get properly typed parameter passing, replacing the ad hoc versions from Chapter 0.**

### Chapter 17 — Enums and Type Aliases *(was ch.17)*
| # | Lecture | Covers |
|---|---|---|
| 17.1 | Enum Classes | Scoped enums. |
| 17.2 | `using enum` | Bringing enumerators into scope. |
| 17.3 | Old-Style Enums | Unscoped enums and why scoped ones are preferred. |
| 17.4 | Type Aliases | `using` for type aliases. |

### Chapter 18 — Arguments to the Main Function *(was ch.18, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 18.1 | Grab and Use the Arguments | `argc`/`argv`. |
| 18.2 | Calculator V1 | An interactive `std::cin`-driven REPL calculator. |
| 18.3 | Calculator V2 | A command-line-argument-driven calculator using `argv`/`atof`. |

**→ Milestone: Project 1 gains CLI flags (`--add`, `--list`).**

### Chapter 19 — Getting Things Out of Functions *(was ch.19, absorbs old ch.22/23)*
| # | Lecture | Covers |
|---|---|---|
| 19.1 | Input and Output Parameters | Using parameters to return extra results. |
| 19.2 | Returning by Value | Standard return-by-value. |
| 19.3 | Returning by Reference | Returning a reference to existing data. |
| 19.4 | Returning by Pointer | Returning a pointer, and its pitfalls. |
| 19.5 | Returning an Array Element's Index by Pointer | A worked pointer-return example. |
| 19.6 | Return Type Deduction | Bare `auto` deduction; function return-type deduction; deduction with references. |
| 19.7 | Function Definitions with Return-Type Deduction | Deduction across declaration/definition splits. |
| 19.8 | Optional Output from Functions | Motivating the need for "no result" as a valid outcome. |
| 19.9 | `std::optional` | Introducing and using `std::optional<T>`. |
| 19.10 | `std::expected` and Monadic Error Handling *(new, C++23)* | `std::expected<T,E>`, `and_then`/`transform`/`or_here` chaining, as the modern alternative to out-param error codes. |
| 19.11 | Static Variables, Inline Functions, and Recursion *(merged from old ch.22)* | Function-local `static`, the `inline` keyword, and recursive functions. |
| 19.12 | Debugging Functions and the Call Stack *(merged from old ch.23)* | Stepping through function calls, arrays, loops, and pointers in the debugger. |

**→ Milestone: Project 1's error handling upgrades from ad hoc to `std::expected<Task, TaskError>`.**

### Chapter 20 — Function Overloading and Lambdas *(was ch.20+21, merged)*
| # | Lecture | Covers |
|---|---|---|
| 20.1 | Overloading with Different Parameters | Basic overload resolution. |
| 20.2 | Overloading with Pointer Parameters | Overloads distinguished by pointer parameters. |
| 20.3 | Overloading with Reference Parameters | Overloads distinguished by reference parameters. |
| 20.4 | Overloading with Const Parameters by Value | `const` value-parameter overloads. |
| 20.5 | Overloading with Const Pointer and Pointer-to-Const Parameters | The full const/pointer overload matrix. |
| 20.6 | Overloading with Const References | Const-reference overloads. |
| 20.7 | Overloads with Default Parameters | Interaction between defaults and overload resolution. |
| 20.8 | Declaring and Using Lambdas | Lambda expression basics. |
| 20.9 | Capture Lists | Explicit lambda captures. |
| 20.10 | Capture-All Lists | `[=]`/`[&]` blanket captures. |

### Chapter 21.5 — AI-Assisted C++ Development I: Tools of the Trade *(new)*
| # | Lecture | Covers |
|---|---|---|
| 21.5.1 | Setting Up Your AI Pair Programmer | Installing and configuring Copilot / Claude Code for a C++ project. |
| 21.5.2 | Prompting for Boilerplate | Getting useful STL-idiom suggestions and boilerplate from an assistant. |
| 21.5.3 | Giving the Assistant Repo Context | MCP-based context so the assistant understands your build/test setup. |
| 21.5.4 | What AI Gets Wrong in C++ | First look at where AI suggestions go wrong in a systems language (expanded later in Ch.49.5). |

---

## Arc 3 — Templates I, Object-Oriented Programming, and Templates II

### Chapter 24 — Templates I: Functions and Concepts *(was ch.24+25, merged)*
**Part A — Function Templates** *(was ch.24, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 24.1 | Trying Out Function Templates | Basic function template + type deduction. |
| 24.2 | Template Type Deduction and Explicit Arguments | Overriding deduction with explicit template arguments. |
| 24.3 | Template Type Parameters by Reference | Avoiding copies via reference template parameters. |
| 24.4 | Template Specialization | Providing a specialized implementation for one type. |
| 24.5 | Function Templates with Overloading | How templates and ordinary overloads interact. |
| 24.6 | Function Templates with Multiple Parameters | Multi-parameter templates and argument-order pitfalls. |
| 24.7 | Template Return-Type Deduction with `auto` | `auto` as a return type. |
| 24.8 | `decltype` and Trailing Return Types | Trailing-return-type syntax. |
| 24.9 | `decltype(auto)` | Precise return-type deduction. |
| 24.10 | Default Template Arguments | Giving templates default type parameters. |
| 24.11 | Non-Type Template Parameters | Template parameters that are values, not types. |
| 24.12 | Abbreviated Function Templates | `auto`-parameter shorthand for templates. |
| 24.13 | Named Template Parameters for Lambdas | Generic lambdas with explicit template parameter names. |
| 24.14 | Type Traits | `std::is_integral_v` and `static_assert`. |
| 24.15 | `if constexpr` | Compile-time branching inside a template. |

**Part B — Concepts** *(was ch.25, internally compressed from 5 lectures to 2)*
| # | Lecture | Covers |
|---|---|---|
| 24.16 | Constraining Templates with Concepts | The four syntactic forms for applying a `requires` constraint (`requires std::integral<T>`, trailing `requires`, constrained template parameter, `std::integral auto`); compound requirements via `ZoomingInOnRequiresClause`. |
| 24.17 | Building and Combining Your Own Concepts | Writing custom concepts (e.g. `Multipliable`, `Incrementable`) and combining multiple constraints on one template. |

### Chapter 26 — Classes *(was ch.26)*
| # | Lecture | Covers |
|---|---|---|
| 26.1 | Your First Class | Declaring a class with member variables and functions. |
| 26.2 | Constructors | Writing a constructor. |
| 26.3 | Defaulted Constructors | `= default`. |
| 26.4 | Setters and Getters | Basic accessor/mutator methods. |
| 26.5 | A Class Across Multiple Files | Splitting a class declaration/definition across header and source files. |
| 26.6 | Destructors | Writing a destructor. |
| 26.7 | Order of Constructor/Destructor Calls | Construction/destruction order in composed objects. |
| 26.8 | Managing Class Objects Through Pointers | Heap-allocated objects and pointer-based management. |
| 26.9 | The `this` Pointer | What `this` is and how it's used. |
| 26.10 | Struct | `struct` vs. `class`. |
| 26.11 | Size of Class Objects | `sizeof` on class instances, padding/alignment intuition. |

**→ Milestone: Project 2, GenericBox — a first, non-generic value-holder class (holds one `int` or one `std::string`) introduced here.**

### Chapter 27 — Classes II: Objects, Construction, and Initialization *(was ch.27+28, merged; adds deducing `this`)*
| # | Lecture | Covers |
|---|---|---|
| 27.1 | Const Objects | `const` instances. |
| 27.2 | Const Objects as Function Parameters | Passing const objects around. |
| 27.3 | Const Member Functions | `const`-qualified methods. |
| 27.4 | Getters That Double as Setters | Overloaded const/non-const accessor pairs. |
| 27.5 | Dangling Pointers and References | Object lifetime hazards. |
| 27.6 | Mutable Objects | The `mutable` keyword. |
| 27.7 | Structured Bindings | Destructuring objects/pairs into named variables. |
| 27.8 | Default Parameters for Constructors | Constructor parameter defaults. |
| 27.9 | Initializer Lists for Constructors | Member-initializer-list syntax. |
| 27.10 | Explicit Constructors | Preventing unwanted implicit conversions with `explicit`. |
| 27.11 | Constructor Delegation | One constructor calling another. |
| 27.12 | Copy Constructors | Writing a copy constructor. |
| 27.13 | Objects Stored in Arrays Are Copies | The copy-semantics implication of array storage. |
| 27.14 | Move Constructors | Writing a move constructor (first exposure; deepened in Ch.41). |
| 27.15 | Deleted Constructors | `= delete`. |
| 27.16 | Initializer-List Constructors | Constructors taking `std::initializer_list<T>`. |
| 27.17 | Aggregate Initialization | Brace-initializing aggregates. |
| 27.18 | Designated Initializers | `.field = value` initialization syntax. |
| 27.19 | Uniform Initialization for Aggregates | Consistent `{}` initialization across aggregate types. |
| 27.20 | Deducing `this` *(new, C++23)* | Explicit object parameters — simplifying const/non-const accessor duplication and enabling recursive lambdas. |

**→ Milestone: GenericBox gets full constructor/init-list treatment plus a deducing-`this` `getValue()` accessor.**

### Chapter 29 — Const, Static Members, and Friends *(was ch.29+30, merged)*
| # | Lecture | Covers |
|---|---|---|
| 29.1 | Friend Functions | Granting a free function access to private members. |
| 29.2 | Friend Classes | Granting an entire class access. |
| 29.3 | Static Member Variables | Class-wide shared state. |
| 29.4 | Inline Static Member Variables | In-class initialization of static members. |
| 29.5 | Static Constants | Class-wide constants. |
| 29.6 | Static Constants Pre-C++17 | The older workaround pattern, for context. |
| 29.7 | Member Variables of Type Self | Self-referential members (via pointer/reference). |
| 29.8 | Member Variables of Other Class Types | Composition. |
| 29.9 | Static Member Functions | Functions callable without an instance. |
| 29.10 | Nested Classes | Classes declared inside another class. |
| 29.11 | In-Class Member Variable Initialization | Default member initializers. |

**→ Milestone: GenericBox gains const-correct accessors, a static "boxes created" counter, and a friend `swap`.**

### Chapter 31 — Namespaces and Multi-File Programs *(was ch.31+32, merged)*
| # | Lecture | Covers |
|---|---|---|
| 31.1 | Creating Namespaces | Basic namespace declaration. |
| 31.2 | Namespaces Across Multiple Files | Splitting a namespace's contents across files. |
| 31.3 | The Default Global Namespace | What lives outside any named namespace. |
| 31.4 | Built-In Namespaces | Standard-library namespaces. |
| 31.5 | Using-Declarations | `using std::cout;`-style declarations. |
| 31.6 | Anonymous Namespaces | Internal linkage via unnamed namespaces. |
| 31.7 | Nested Namespaces | Namespaces inside namespaces. |
| 31.8 | Namespace Aliases | Shortening long namespace names. |
| 31.9 | Compiling and Linking: The Model | How translation units become an executable. |
| 31.10 | Declarations and Definitions | The distinction, revisited at program scale. |
| 31.11 | The One-Definition Rule | ODR and its consequences. |
| 31.12 | Linkage | Internal vs. external linkage. |
| 31.13 | Flipping Linkage | Changing a symbol's linkage and observing the effect. |
| 31.14 | Inline Variables and Functions | `inline` at namespace scope. |
| 31.15 | Forward Declarations | Declaring before defining across files. |

### Chapter 34 — Operator Overloading *(was ch.34, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 34.1 | Addition Operator as a Member | `operator+` as a member function. |
| 34.2 | Addition Operator as a Non-Member | `operator+` as a free function. |
| 34.3 | Subscript Operator, Reading | `operator[]` for read access. |
| 34.4 | Subscript Operator, Reading and Writing | `operator[]` with a non-const overload. |
| 34.5 | Subscript Operator for Collection Types | Applying `[]` to a container-like class. |
| 34.6 | Stream Insertion Operator | `operator<<`. |
| 34.7 | Stream Extraction Operator | `operator>>`. |
| 34.8 | Other Arithmetic Operators | `-`, `*`, `/`, etc. |
| 34.9 | Compound Operators, Reusing Operators | Implementing `+=` in terms of `+`. |
| 34.10 | Custom Type Conversions | User-defined conversion operators. |
| 34.11 | Implicit Conversions with Overloaded Binary Operators | How conversions interact with operator overloads. |
| 34.12 | Unary Prefix Increment, as Member | `++obj` as a member. |
| 34.13 | Unary Prefix Increment, as Non-Member | `++obj` as a free function. |
| 34.14 | Unary Postfix Increment | `obj++` and the dummy-`int` trick. |
| 34.15 | Unary Prefix/Postfix Decrement | `--obj` and `obj--`. |
| 34.16 | Copy Assignment Operator | `operator=`. |
| 34.17 | Copy Assignment Operator for Other Types | Assignment across related types. |
| 34.18 | Type Conversions Recap | Consolidating the conversion rules covered so far. |
| 34.19 | Functors | Function-call operator `operator()`. |

**→ Milestone: GenericBox gets comparison and stream-insertion operators.**

### Chapter 35 — Logical Operators and Three-Way Comparison *(was ch.35, `35.2`/`35.3` merged)*
| # | Lecture | Covers |
|---|---|---|
| 35.1 | All Logical Operators, and the Legacy `rel_ops` Namespace *(merged — was 2 lectures)* | Hand-written `>`/`<`/`>=`/`<=`/`==`/`!=`, then the deprecated `std::rel_ops` alternative, framed as "here's the modern way, here's the legacy one you shouldn't use." |
| 35.2 | Logical Operators with Implicit Conversions | Interaction between conversions and comparisons. |
| 35.3 | Three-Way Comparison Operator | `<=>`, the spaceship operator. |
| 35.4 | Defaulted Equality Operator | `= default` for `==`. |
| 35.5 | Custom Equality Operator | Hand-writing `==`. |
| 35.6 | Default Ordering with Spaceship | `= default` for `<=>`. |
| 35.7 | Members Without a Spaceship Operator | Ordering when not every member is comparable. |
| 35.8 | Custom Spaceship Operator for Ordering | Hand-writing `<=>`. |
| 35.9 | Spaceship as Non-Member | Free-function `<=>`. |
| 35.10 | Zooming In on Weak Ordering (Two Examples) | Worked `std::weak_ordering` examples. |
| 35.11 | Zooming In on Partial Ordering | A worked `std::partial_ordering` example. |

**→ Milestone: Project 1 gets `operator<=>` to sort tasks by priority/due-date.**

### Chapter 36 — Inheritance *(was ch.36, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 36.1 | First Try on Inheritance | Basic base/derived class relationship. |
| 36.2 | Protected Members | The `protected` access specifier. |
| 36.3 | Base Class Access Specifiers, a Demo | `public`/`protected`/`private` inheritance compared. |
| 36.4 | Closing in on Private Inheritance | Private inheritance specifically. |
| 36.5 | Resurrecting Members Back Into Context | Using-declarations to re-expose inherited members. |
| 36.6 | Default-Argument Constructors with Inheritance | Defaults interacting with base-class construction. |
| 36.7 | Constructors with Inheritance | Calling base constructors from derived ones. |
| 36.8 | Copy Constructors with Inheritance | Copy semantics across a hierarchy. |
| 36.9 | Inheriting Base Constructors | `using Base::Base;`. |
| 36.10 | Inheritance and Destructors | Destructor call order in a hierarchy. |
| 36.11 | Reused Symbols in Inheritance | Name hiding/shadowing across base and derived classes. |

**→ Milestone: Project 3, MiniGrep — a `Matcher` base class with `LiteralMatcher`/`RegexMatcher`/`WildcardMatcher` derived types, introduced here.**

### Chapter 37 — Polymorphism *(was ch.37, `37.5`/`37.6` merged)*
| # | Lecture | Covers |
|---|---|---|
| 37.1 | Static Binding with Inheritance | Calling a non-virtual function through a base pointer. |
| 37.2 | Polymorphism with Virtual Functions | Making a function `virtual` and observing dynamic dispatch. |
| 37.3 | Size of Polymorphic Objects, and Slicing | `sizeof` on polymorphic types; object slicing. |
| 37.4 | Storing and Iterating Polymorphic Objects *(merged — was 2 lectures)* | Storing objects in collections of base pointers/`shared_ptr`, then iterating a raw-pointer array — shown as one continuous example. |
| 37.5 | Overloading, Overriding, and Hiding | Distinguishing the three, with a differently-signatured derived function. |
| 37.6 | Polymorphism at Different Levels | Virtual dispatch through multiple inheritance levels. |
| 37.7 | Inheritance and Polymorphism with Static Members | How `static` members behave in a polymorphic hierarchy. |
| 37.8 | `Final` | The `final` specifier. |
| 37.9 | `Final` and `Override` Are Not Keywords | Their status as identifiers-with-special-meaning, not reserved keywords. |
| 37.10 | Polymorphic Functions and Access Specifiers | Access-specifier interactions with virtual dispatch. |
| 37.11 | Non-Polymorphic Functions and Access Specifiers | The contrast case. |
| 37.12 | Virtual Functions with Default Arguments | A common gotcha: defaults are static, not virtual. |
| 37.13 | Virtual Destructors | Why base classes need a virtual destructor. |
| 37.14 | Dynamic Casts | `dynamic_cast`. |
| 37.15 | Polymorphic Functions and Destructors | Interaction between virtual functions and destruction order. |
| 37.16 | The `typeid` Operator | Runtime type identification. |
| 37.17 | Pure Virtual Functions and Abstract Classes | `= 0`, abstract base classes. |
| 37.18 | Abstract Classes as Interfaces | Using pure-virtual classes as interfaces. |

**→ Milestone: MiniGrep's matcher dispatch made virtual; matchers stored in a polymorphic collection.**

### Chapter 38 — Exceptions *(was ch.38, reframed against `std::expected`)*
| # | Lecture | Covers |
|---|---|---|
| 38.1 | The Need for Exceptions | Motivating example for exception-based error handling. |
| 38.2 | Try/Catch Blocks | Basic `try`/`catch`. |
| 38.3 | Handling Exceptions at Different Levels | Where to catch relative to where you throw. |
| 38.4 | Multiple Handlers for Exceptions | Multiple `catch` clauses. |
| 38.5 | Nested Try Blocks | `try` inside `try`. |
| 38.6 | Throwing Class Objects | Throwing custom exception types. |
| 38.7 | Exceptions as Class Objects with Inheritance Hierarchies | Exception class hierarchies. |
| 38.8 | Polymorphic Exceptions | Catching by base reference. |
| 38.9 | Rethrown Exceptions | `throw;` to rethrow. |
| 38.10 | Program Custom Termination | Customizing `std::terminate` behavior. |
| 38.11 | Ellipsis Catch-All Block | `catch (...)`. |
| 38.12 | The `noexcept` Specifier | Declaring a function won't throw. |
| 38.13 | Exceptions in Destructors | Why destructors shouldn't throw. |
| 38.14 | Catching Standard Exceptions | `std::exception` and its hierarchy. |
| 38.15 | Throwing `std` Exceptions | Using standard exception types. |
| 38.16 | Deriving from Standard Exceptions | Extending `std::exception`. |
| 38.17 | Exceptions vs. `std::expected`: Choosing Your Error Strategy *(new)* | The same failure (e.g. file-not-found) modeled first with exceptions, then refactored to `std::expected` from Ch.19 — a direct, side-by-side trade-off comparison. |

**→ Milestone: MiniGrep's file-not-found / invalid-pattern handling modeled both ways.**

### Chapter 38.5 — Project Capstone: The Box Container Type *(was ch.39)*
| # | Lecture | Covers |
|---|---|---|
| 38.5.1 | Constructing and Destroying | Building GenericBox's constructor/destructor pair for real, from Project 2's foundation. |
| 38.5.2 | Adding Items | Growable storage inside the container. |
| 38.5.3 | Removing Items | Safe removal and the bookkeeping it requires. |
| 38.5.4 | Other Operators | Rounding out the container's operator set. |
| 38.5.5 | Storing Different Types | Hitting the code-duplication pain point head-on — separate `IntContainer`/`DoubleContainer`/`CharContainer` classes — as the direct setup for "Templates II" solving it next chapter. |

### Chapter 40 — Templates II: Class Templates and Constraining Them *(was ch.40, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 40.1 | Your First Class Template | Collapsing `IntContainer`/`DoubleContainer`/`CharContainer` from Ch.38.5 into one `BoxContainer<T>` — the direct payoff of last chapter's setup. |
| 40.2 | Non-Type Template Parameters | `BoxContainer<T, size_t maximum>`. |
| 40.3 | Default Values for Template Parameters | Defaulting both type and non-type parameters. |
| 40.4 | Template Specializations | Fully specializing a class template for one type. |
| 40.5 | Template Specialization with Select Member Functions | Specializing a single member function, not the whole class. |
| 40.6 | Friend Functions for Class Templates | `friend` inside a template. |
| 40.7 | Stream Insertion Operator for Class Templates | `operator<<` for a templated type. |
| 40.8 | Class Templates with Type Traits and Static Asserts | Constraining a class template the pre-concepts way. |
| 40.9 | Class Templates with Concepts | Constraining `BoxContainer<T>` and its member functions with `requires` clauses. |
| 40.10 | Built-In Concepts | Using standard concepts like `std::copyable`, alongside a defaulted `<=>` from Ch.35. |
| 40.11 | Concepts Example: `OutputStreamable` | Constraining `operator<<` for a `std::vector<T>`. |
| 40.12 | Concepts Example: `Number` | Combining `std::integral`/`std::floating_point` into one concept. |

**→ Milestone: Project 4, MiniJSON — a templated `Value` variant-like type, introduced here.**
**→ Milestone: GenericBox becomes fully generic, plus a non-type template parameter for a fixed-capacity variant.**

---

## Arc 4 — Systems Layer: How It Really Works

### Chapter 13 — Pointers *(was ch.13, deliberately deferred here)*
| # | Lecture | Covers |
|---|---|---|
| 13.1 | Declaring and Using Pointers | Pointer basics. |
| 13.2 | Pointer to Char | Pointing at character data. |
| 13.3 | Array of Pointer to Char | Arrays of C-strings. |
| 13.4 | Const Pointer and Pointer to Const | The four const/pointer combinations. |
| 13.5 | Array of Const Pointer to Const Char | Combining the two. |
| 13.6 | Pointers and Arrays | The pointer/array duality. |
| 13.7 | Swapping Array Data, a Demo | A worked pointer-swap example. |
| 13.8 | Pointer Arithmetic: Navigation | Moving a pointer through memory. |
| 13.9 | Pointer Arithmetic: Distance Between Elements | Pointer subtraction. |
| 13.10 | Pointer Arithmetic: Comparing Pointers | Relational comparisons between pointers. |
| 13.11 | Swapping Array Data with Pointer Arithmetic | Combining arithmetic with the swap demo. |
| 13.12 | Dynamic Memory Allocation | `new`/`delete`. |
| 13.13 | Dangling Pointers | What they are and why they're dangerous. |
| 13.14 | When `new` Fails | Handling allocation failure. |
| 13.15 | Null Pointer Safety | Defensive null checks. |
| 13.16 | Memory Leaks | Recognizing and avoiding them. |
| 13.17 | Dynamically Allocated Arrays | `new[]`/`delete[]`. |

**→ Milestone: MiniGrep gets an intentionally-added raw-pointer buffer for reading file chunks, demonstrating dangling pointers/leaks in context, then fixed.**

### Chapter 14 — References *(was ch.14, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 14.1 | Declaring and Using References | Reference basics. |
| 14.2 | Comparing Pointers and References | When to reach for each. |
| 14.3 | References and `const` | Const references. |
| 14.4 | References with Range-Based For Loops | Avoiding copies while iterating. |

### Chapter 33 — Smart Pointers *(was ch.33, only `33.4`/`33.7` merged)*
| # | Lecture | Covers |
|---|---|---|
| 33.1 | Unique Pointers | `std::unique_ptr` basics. |
| 33.2 | Unique Pointers as Function Parameters and Return Types | Move-only semantics in function signatures. |
| 33.3 | Smart Pointers and Arrays *(merged — was 2 lectures)* | `unique_ptr<Dog[]>` and `shared_ptr<Dog[]>` construction, compared side by side. |
| 33.4 | Shared Pointers | `std::shared_ptr`, `use_count()`, multiple owners, `reset()` propagation across copies. |
| 33.5 | Shared Pointers from Unique Pointers | Ownership transfer between the two. |
| 33.6 | Shared Pointers as Function Parameters and Return Types | Refcounting effects of pass-by-value vs. pass-by-reference. |
| 33.7 | Weak Pointers | `std::weak_ptr` and breaking reference cycles. |

**→ Milestone: GenericBox's internal storage swaps to `unique_ptr<T[]>`.**

### Chapter 8 — Bitwise Operators *(was ch.08, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 8.1 | Printing Integers in Binary | Visualizing bit patterns. |
| 8.2 | Shift Operators | `<<`/`>>` at the bit level. |
| 8.3 | Logical Bitwise Operators | `&`, `|`, `^`, `~`. |
| 8.4 | Compound Bitwise Operators | `&=`, `|=`, `^=`. |
| 8.5 | Masks | Using bitmasks to test/set/clear bits. |
| 8.6 | Masks Example | A worked masking example. |
| 8.7 | Packing Color Information | Packing RGB(A) into a single integer. |

### Chapter 41 — Move Semantics *(was ch.41, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 41.1 | Lvalues and Rvalues | The core value-category distinction. |
| 41.2 | Rvalue References | `T&&`. |
| 41.3 | Moving Temporaries Around | How temporaries bind to rvalue references. |
| 41.4 | Move Constructors and Move Assignment Operators | Full move-semantics implementation. |
| 41.5 | Moving Lvalues with `std::move` | Explicitly opting an lvalue into a move. |
| 41.6 | Invalidating Pointers After `std::move` | The state of a moved-from object. |
| 41.7 | Move-Only Types | Types that forbid copying entirely. |
| 41.8 | Passing by Rvalue Reference | Function parameters that bind only to rvalues. |

**→ Milestone: GenericBox gets a move constructor/assignment operator.**

### Chapter 42 — Function-Like Entities *(was ch.42, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 42.1 | Function Pointers | Pointers to functions. |
| 42.2 | Callback Functions | Passing a function pointer as a callback. |
| 42.3 | Function Pointer Type Aliases | `using` for function-pointer types. |
| 42.4 | Function Pointer Type Aliases with Templates | Generic function-pointer aliases. |
| 42.5 | Functors | Classes with `operator()`. |
| 42.6 | Standard Functors | `<functional>`'s built-in functors. |
| 42.7 | Functors with Parameters | Stateful functors. |
| 42.8 | Functors and Lambda Functions | How lambdas relate to functors under the hood. |
| 42.9 | Lambda Functions as Callbacks | Using lambdas where callbacks are expected. |
| 42.10 | Capturing by Value, Under the Hood | What a value-capturing lambda compiles to. |
| 42.11 | Capturing by Reference, Under the Hood | The reference-capture equivalent. |
| 42.12 | Mixed Capturing | Combining by-value and by-reference captures. |
| 42.13 | Capturing the `this` Pointer | Lambdas inside member functions. |
| 42.14 | `std::function` | Type-erased callable wrapper. |

**→ Milestone: MiniGrep's matchers become configurable via `std::function<bool(std::string_view)>` predicates, compared directly against the virtual-dispatch version from Ch.37.**

---

## Arc 5 — STL Depth, Tooling, and Course Close

### Chapter 43 — STL Containers and Iterators *(was ch.43, `43.2`/`43.3` cut)*
| # | Lecture | Covers |
|---|---|---|
| 43.1 | Iterators | What an iterator is and the category hierarchy. |
| 43.2 | Traversing Container Subsets with Iterators | Iterating a portion of a container. |
| 43.3 | Reverse Iterators | `rbegin()`/`rend()`. |
| 43.4 | Const Iterators | Read-only iteration. |
| 43.5 | `std::begin`/`std::end` | Free-function iterator access, including for raw arrays. |

### Chapter 44 — Zooming on STL Containers *(was ch.44, adds `flat_map`/`flat_set`)*
| # | Lecture | Covers |
|---|---|---|
| 44.1 | Vector, In Depth | Capacity management (`reserve`, `shrink_to_fit`), the full modifier set (`insert`, `emplace`, `erase`, `emplace_back`, `resize`, `swap`) — the deep pass on the container first used informally back in Chapter 0. |
| 44.2 | Array, In Depth | `std::array`'s fuller method set — `fill`, `swap`, assignment, custom-object arrays. |
| 44.3 | Deque | `std::deque`. |
| 44.4 | Forward List | `std::forward_list`. |
| 44.5 | List | `std::list`. |
| 44.6 | Pair | `std::pair`. |
| 44.7 | Set | `std::set`. |
| 44.8 | Map | `std::map`. |
| 44.9 | Multiset and Multimap | `std::multiset`/`std::multimap`. |
| 44.10 | Unordered Set and Unordered Map | The hash-table-backed variants. |
| 44.11 | `std::flat_map` and `std::flat_set` *(new, C++23)* | Cache-friendly sorted-vector-backed associative containers, and when to prefer them over `map`/`set`. |
| 44.12 | Stack | `std::stack`. |
| 44.13 | Queue | `std::queue`. |
| 44.14 | Priority Queue | `std::priority_queue`. |

**→ Milestone: Project 1's storage upgrades from `std::vector` to `std::flat_map<int, Task>` keyed by task ID.**
**→ Milestone: MiniJSON's object members backed by `std::flat_map<std::string, Value>`.**

### Chapter 45 — STL Algorithms *(was ch.45, consolidated)*
| # | Lecture | Covers |
|---|---|---|
| 45.1 | Querying Algorithms | `all_of`, `find`/`find_if`, `for_each`, `max_element`/`min_element` — taught together rather than one-per-lecture. |
| 45.2 | Transforming Algorithms | `sort`, `copy`, `transform`. |

### Chapter 46 — Ranges and C++23 Views *(was ch.46, adds C++23 views + mdspan)*
| # | Lecture | Covers |
|---|---|---|
| 46.1 | Range Algorithms | `std::ranges::sort`/`all_of`/`for_each`/`find_if`/`copy` — the same algorithms from Ch.45, now without manual iterator pairs. |
| 46.2 | Range-Library Iterator-Pair Algorithms | Ranges algorithms that still take an iterator pair. |
| 46.3 | Projections | Transforming elements before an algorithm compares them. |
| 46.4 | Views and Range Adaptors | `views::filter`, `views::transform`, etc. |
| 46.5 | View Composition and the Pipe Operator | Chaining adaptors with `|`. |
| 46.6 | Range Factories | Generating ranges without a backing container. |
| 46.7 | New C++23 Views: `zip`, `chunk`, `slide`, `enumerate` *(new)* | The views that close real usability gaps left by C++20 ranges. |
| 46.8 | `std::mdspan` and the Multidimensional Subscript Operator *(new, C++23)* | Viewing contiguous memory as a multidimensional array. |

**→ Milestone: Project 1 filters/sorts tasks via `views::filter`/`views::zip`.**
**→ Milestone: MiniJSON's matrix-shaped values viewed through `std::mdspan`.**

### Chapter 47 — Building Iterators for Custom Containers *(was ch.47, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 47.1 | Iterator Powers | What an iterator needs to support to satisfy each category. |
| 47.2 | Custom Input Iterator | Implementing an input iterator. |
| 47.3 | Custom Output Iterator | Implementing an output iterator. |
| 47.4 | Custom Forward Iterator | Implementing a forward iterator. |
| 47.5 | Custom Bidirectional Iterator | Implementing a bidirectional iterator. |
| 47.6 | Custom Random-Access Iterator | Implementing a random-access iterator. |
| 47.7 | Custom Iterators with Views | Making a custom iterator work with `<ranges>` views. |
| 47.8 | Constant Iterators | Read-only custom iterators. |
| 47.9 | Raw Pointers as Iterators | Why a raw pointer already satisfies the iterator concept. |
| 47.10 | Wrapping Iterators from Other Containers | Adapting an existing container's iterator. |

**→ Milestone: GenericBox gets a real `begin()`/`end()` iterator.**

### Chapter 48 — Coroutines *(was ch.48, adds `std::generator`)*
| # | Lecture | Covers |
|---|---|---|
| 48.1 | `co_await` | Suspending and resuming a coroutine. |
| 48.2 | `co_yield` | Producing a sequence of values lazily. |
| 48.3 | `co_return` | Returning from a coroutine. |
| 48.4 | Custom Generator | Hand-building a generator type — and why it's fiddly in C++20. |
| 48.5 | `std::generator` *(new, C++23)* | The standard-library generator that replaces the old "you need a 3rd-party library" workaround. |

**→ Milestone: GenericBox gets a coroutine-based generator view over its contents.**
**→ Milestone: MiniJSON gets a `std::generator`-based lazy-parsing/streaming token generator.**

### Chapter 49 — Modules *(was ch.49, unchanged)*
| # | Lecture | Covers |
|---|---|---|
| 49.1 | Introduction | Why modules, and what problem they solve vs. headers. |
| 49.2 | Your First Module | A minimal module. |
| 49.3 | Block Export | `export { ... }` blocks. |
| 49.4 | Separating Interface from Implementation, Same File | Splitting within one file. |
| 49.5 | Separating Interface from Implementation, Different Files | Splitting across files. |
| 49.6 | Multiple Implementation Files | One interface, several implementation units. |
| 49.7 | Multiple Interface Files | Module partitions across several interface files. |
| 49.8 | Export/Import | The full export/import mechanics. |
| 49.9 | Submodules | Structuring a module into submodules. |
| 49.10 | Module Interface Partitions | Partitioning an interface. |
| 49.11 | GenericBox as a Module | Modularizing the running Project 2 example. |
| 49.12 | Modules with Namespaces | Combining the two. |
| 49.13 | Visibility and Reachability | The module-specific visibility rules. |
| 49.14 | The Private Module Fragment | `module :private;`. |
| 49.15 | Dos and Don'ts | Practical guidance for real module use. |

### Chapter 49.5 — AI-Assisted C++ Development II: Review, Safety, and Sanitizers *(new)*
| # | Lecture | Covers |
|---|---|---|
| 49.5.1 | Reviewing AI-Generated C++ Like a Junior's PR | A review checklist specific to C++'s failure modes. |
| 49.5.2 | The Mandatory Sanitizer Pass | Running ASan/UBSan on AI-generated code before trusting it. |
| 49.5.3 | Live Demo: Catching an AI-Introduced Memory Bug | Walking through a real example, sanitizer output and all. |
| 49.5.4 | Why This Matters | The CVE and vulnerability-rate data behind the review discipline. |

### Chapter 49.6 — Final Capstone Build *(new)*
| # | Lecture | Covers |
|---|---|---|
| 49.6.1 | Planning the Integration | Combining Project 1 (Task Tracker) and Project 4 (MiniJSON) into one application — a task tracker that saves/loads via MiniJSON. |
| 49.6.2 | Building with AI Assistance | Using an AI assistant for part of the implementation. |
| 49.6.3 | Applying the Review Checklist | Running the Ch.49.5 checklist and sanitizers against the AI-assisted code. |
| 49.6.4 | Wrap-Up and Next Steps | Where to go from here. |

### Chapter 50 — C++26 Hacking Preview *(new)*
| # | Lecture | Covers |
|---|---|---|
| 50.1 | Getting Trunk GCC Running | Compiler Explorer / GCC 16.1 setup, feature-test macros. |
| 50.2 | Static Reflection, Part 1 | The `^^` operator and `std::meta::info` basics (P2996). |
| 50.3 | Static Reflection, Part 2 | Reflectively generating a `to_string`/field-enumeration for GenericBox or `MiniJSON::Value`. |
| 50.4 | Contracts, Part 1 | `[[pre:]]`/`[[post:]]` on functions. |
| 50.5 | Contracts, Part 2 | `contract_assert`, contrasted against the `std::expected`/exceptions strategies from Ch.19/38. |
| 50.6 | The Placeholder Variable `_` | Ignoring values in structured bindings and beyond. |
| 50.7 | `std::execution` and Senders/Receivers | A conceptual walkthrough via NVIDIA's stdexec reference implementation — architecture preview, no standard library ships this yet. |
| 50.8 | What's Still Coming | Mention-only wrap-up: `std::linalg`, pattern matching/`inspect` — not reliably runnable yet, no graded exercises. |

---

**Total: ~355-370 lectures across 5 arcs**, down from ~460 lecture-equivalent folders in the original course. Full rationale, source-code evidence, and the old→new chapter mapping live in `CPP_23_UPDATE.md`.
