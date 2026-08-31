# Welcome

## 1. What C++ actually is

C++ is a **general-purpose programming language** built for one job above
all others: getting the most out of the machine without giving up the
ability to build large, structured systems. It sits close enough to the
hardware that you can reason about memory and CPU cost, and high enough
that you can express real abstractions: types, classes, generic
algorithms, whole libraries.

```
        assembly            C++                Python / JS
     ────────────────────────────────────────────────────────
        raw control     control + structure     convenience
        no safety net   you choose the cost     runtime does it for you
```

It was created by Bjarne Stroustrup in the early 1980s as "C with
classes," and it has been evolving on a fixed schedule ever since. A new
standard lands every three years: C++11, C++14, C++17, C++20, C++23, with
C++26 already taking shape. This course targets the modern end of that
line, **C++23 and beyond**, not the C++ of twenty years ago.

## 2. Where C++ runs

You are almost certainly using software written in C++ right now, whether
you know it or not.

- **Browsers**: Chrome, Firefox, and Edge's engines.
- **Operating systems**: large parts of Windows, macOS, and Linux tooling.
- **Databases**: MySQL, MongoDB, PostgreSQL internals.
- **Games and engines**: Unreal Engine, most AAA titles, console SDKs.
- **Creative tools**: Photoshop, Premiere, Blender, most audio DAWs.
- **Finance**: high-frequency trading systems, risk engines.
- **Embedded and automotive**: car firmware, medical devices, robotics.
- **Aerospace**: flight software, simulation, ground systems.
- **Infrastructure**: compilers, virtual machines, parts of the JVM and
  .NET.

The common thread: when performance, control, or scale actually matters,
C++ is still the language people reach for.

## 3. Learning to think like an engineer

The reason to learn C++ is not only the job listings. C++ forces you to
understand what is actually happening.

When you write a variable, you decide how big it is and whether it is
signed. When you pass data around, you decide whether it is copied or
shared. When you allocate memory, you are responsible for it. Nothing is
hidden, and nothing is free.

That pressure is uncomfortable at first, and it is exactly what turns you
into an engineer. You stop asking only "does it run?" and start asking
"what does this cost, what can go wrong, and who owns this?" Those
questions carry over to every other language you will ever use.

## 4. What this course is

This is a **problem-solving course**, not a language-feature tour. Every
concept is introduced because a problem needs it, not because it exists.
The goals:

- Teach **modern C++23** idioms from the start, so you are not unlearning
  old habits later.
- Build the habit of **breaking a problem down** before writing code.
- Give you enough **live exercises** that the syntax becomes muscle
  memory, not something you look up every time.
- Walk through **real projects** end to end, not toy snippets.

### The practical topics we go through

- **Debugging**: reading a debugger, stepping through code, and finding
  the actual cause of a bug instead of guessing.
- **Third-party libraries**: pulling in and building against code you
  did not write, which is what real work looks like.
- **GUI development**: putting a real interface on a program instead of
  only printing to a console.
- **Packaging and distribution**: turning your build into something
  another person can install and run.
- **CI/CD**: automating builds and tests so regressions get caught
  before users do.
- **Gaming**: a project that ties the performance and structure lessons
  together.
- **Compiler Support**: Understanding what the compiler you have access to can and cannot do, and how to work with it. C++ 11, 14, 17, 20, and 23 are all supported by different compilers at different levels. We will cover what is available and how to use it.
- **CMake**: A build system that is widely used in the C++ world. We will cover how to use it to build your projects and manage dependencies.

## 5. How to get the most out of it

- **Type the code yourself.** Watching is not learning. The exercises are
  there for a reason.
- **Break things on purpose.** Change a type, remove an initializer, see
  what the compiler says. The error messages are part of the material.
- **Do not rush the early chapters.** Number systems, types, and memory
  feel slow, but everything later stands on them.
- **Ask questions.** If you are stuck, ask. If you are curious, ask. If
  you are confused, ask. The only bad question is the one you do not ask.


## 6. The Flow

- **Get the Starter Files**: Download the starter files from the course platform. These contain the course structure, initial code, and any assets you'll need. 
- **Open a Project and Work Through it folloing along with the video**: Do what we do in the course.
- **Make it your own**: After watching the video, try to modify the code, add features, or experiment with different approaches.

