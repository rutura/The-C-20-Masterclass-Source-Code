# 🚀 The C++20 Masterclass — Source Code

Welcome to the source code repository for **The C++20 Masterclass**.

This repository contains the code examples, experiments, and practice material used throughout the course. It starts with the fundamentals of C++ and gradually moves into modern C++ features and programming techniques introduced with **C++20**.

If you're learning C++, revisiting the language, or trying to understand what modern C++ looks like beyond the basics, this repository is a great place to follow along and experiment with the examples yourself. 💻

---

## 📚 What You'll Learn

The repository follows a progressive learning path, so the best way to use it is to work through the folders in order.

You'll find examples covering:

### 🟢 C++ Fundamentals

* First steps with C++
* Variables and data types
* Operations on data
* Literals and constants
* Type conversions
* Overflow and underflow
* Bitwise operators
* Variable lifetime and scope
* Flow control
* Loops
* Arrays
* Pointers
* References
* Character manipulation and strings

### 🔵 Functions & Language Features

* Functions
* Function arguments
* Return values
* Function overloading
* Lambda functions
* Function templates
* Function-like entities
* Enums and type aliases
* Debugging and the function call stack

### 🟣 Object-Oriented Programming

* Classes and objects
* Constructors and initialization
* `const` and `static` members
* Friend functions and classes
* Namespaces
* Multiple-file programs
* Operator overloading
* Three-way comparison (`<=>`)
* Inheritance
* Polymorphism
* Exceptions

### 🧠 Modern C++

* Smart pointers
* Move semantics
* Class templates
* Concepts
* STL containers
* STL iterators
* STL algorithms
* Ranges
* Custom iterators

### ⚡ C++20 Features

The repository also gets into some of the most interesting additions to modern C++:

* Concepts
* Ranges
* Coroutines
* Modules
* Three-way comparison
* Modern template techniques

---

## 🗂️ Repository Structure

The folders are numbered according to the progression of the course.

```text
The-C-20-Masterclass-Source-Code/
│
├── 03.FirstSteps/
├── 04.VariablesAndDatatypes/
├── 05.OperationsOnData/
├── 06.LiteralsAndConstants/
├── 07.ConversionsOverflowAndUnderflow/
├── 08.BitwiseOperators/
├── 09.VariableLifetimeAndScope/
├── 10.FlowControl/
├── 11.Loops/
├── 12.Arrays/
├── 13.Pointers/
├── 14.References/
├── 15.CharacterManipulationAndStrings/
├── 16.Functions/
├── 17.EnumsAndTypeAliases/
├── 18.ArgumentsToTheMainFunction/
├── 19.GettingThingsOutOfFuntions/
├── 20.FunctionOverloading/
├── 21.LambdaFunctions/
├── 22.FunctionsTheMisfits/
├── 23.FunctionCallStackD_ebugging/
├── 24.FunctionTemplates/
├── 25.Concepts/
├── 26.Classes/
├── 27.ZoomingInOnClassObjects/
├── 28.DivingDeepIntoConstructorsAndInitialization/
├── 29.Friends/
├── 30.ConstAndStaticMembers/
├── 31.Namespaces/
├── 32.ProgramsWithMultipleFiles/
├── 33.SmartPointers/
├── 34.OperatorOverloading/
├── 35.LogicalOperatorsAndThreeWayComparison/
├── 36.Inheritance/
├── 37.Polymorphism/
├── 38.Exceptions/
├── 39.Practice-BoxContainerType/
├── 40.ClassTemplates/
├── 41.MoveSemantics/
├── 42.FunctionLikeEntities/
├── 43.StlContainersAndIterators/
├── 44.ZoomingOnSTLContainers/
├── 45.StlAlgorithms/
├── 46.RangesLibraryInCpp20/
├── 47.BuildingIteratorsForCustomContainers/
├── 48.Coroutines/
└── 49.Modules/
```

Each section focuses on a particular topic and contains small, focused examples that make it easier to understand the concept without dealing with a huge application.

---

## 🛠️ Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/rutura/The-C-20-Masterclass-Source-Code.git
```

Then move into the project:

```bash
cd The-C-20-Masterclass-Source-Code
```

### 2. Pick a topic

Start with the earliest numbered folder if you're new to C++.

For example:

```text
03.FirstSteps
```

If you're already comfortable with the basics, jump directly to a topic you're interested in.

### 3. Compile and experiment

Most examples are small standalone C++ programs, so you can compile them with a C++ compiler that supports the required language features.

For example:

```bash
g++ -std=c++20 main.cpp -o main
./main
```

Depending on the example, you may need a sufficiently recent version of GCC, Clang, or MSVC.

> 💡 **Tip:** Don't just read the examples. Change them. Break them. Fix them. That's where most of the learning happens.

---

## 🎯 Recommended Learning Path

If you're completely new to C++, don't jump straight into coroutines or concepts. 😄

A good progression is:

```text
C++ Basics
    ↓
Functions
    ↓
Pointers & References
    ↓
Classes & OOP
    ↓
Templates
    ↓
Smart Pointers
    ↓
Move Semantics
    ↓
STL
    ↓
Algorithms & Iterators
    ↓
Ranges
    ↓
Concepts
    ↓
Coroutines
    ↓
Modules
```

This order gives you the fundamentals needed to understand the more advanced C++20 features.

---

## 🧪 Use This Repository as a Playground

One of the best ways to use this repository is to treat every example as a starting point.

Try things like:

* ✏️ Modify an existing example
* 🔍 Predict the output before running it
* 🐛 Introduce a bug and debug it
* 🧩 Rewrite an example using a different C++ feature
* ⚡ Compare old-style C++ with modern C++
* 🧠 Explain the code to someone else
* 🚀 Build a small project using what you've learned

The goal isn't just to make the examples compile.

The goal is to **understand why the code works**.

---

## 💡 Why C++20?

C++ has evolved considerably from the C++98/C++03 days.

Modern C++ gives developers powerful abstractions while still providing the low-level control and performance that make C++ useful for systems programming, game development, embedded software, high-performance applications, and many other domains.

C++20 is an especially important release because it introduced major language and library features such as:

* 🧠 **Concepts** — cleaner constraints for templates
* 🔄 **Ranges** — more expressive work with collections
* 🧵 **Coroutines** — a foundation for asynchronous and cooperative programming
* 📦 **Modules** — a modern alternative to traditional header-based organization
* ⚖️ **Three-way comparison** — simplified comparison operators
* 🛠️ Numerous improvements across the standard library

---

## 🎓 About the Course

This repository is the companion source code for the **C++20 Masterclass** course on Udemy.

The source code is organized around the lessons and topics covered in the course, making it easy to follow along while watching the lectures.

👉 **Course:** The Modern C++ 20 Masterclass on Udemy

---

## 🤝 Contributing

This repository primarily exists as course material, but if you spot an obvious issue, typo, broken example, or something that can be improved, feel free to open an issue or submit a pull request.

When contributing:

1. Keep examples simple and focused.
2. Follow modern C++ practices where appropriate.
3. Avoid adding unnecessary dependencies.
4. Clearly explain what you've changed.
5. Make sure examples compile before submitting a PR.

---

## ⭐ Found This Useful?

If this repository helped you learn something new, consider giving it a ⭐ on GitHub.

It helps others discover the project and is always appreciated!

---

## 🧑‍💻 Happy Coding!

C++ can feel intimidating at first. There are pointers, references, templates, memory management, undefined behavior... and then C++20 shows up with concepts, ranges, coroutines, and modules. 😅

Take it one concept at a time.

**Read → Code → Experiment → Break Things → Debug → Understand → Repeat.**

That's how you get better at C++. 💪

---

### 📌 Repository

**The-C-20-Masterclass-Source-Code**

A practical collection of C++ examples covering the journey from the fundamentals to modern C++20.

**Keep learning. Keep experimenting. Keep writing C++. 🚀**
