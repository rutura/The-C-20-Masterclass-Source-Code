---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 2 · Environment Setup'
---

<!-- _class: lead -->

# Linux and Mac: Qt Creator

## Same IDE, a compiler that's already on your system

---

*Recommended*

## Qt Creator on Linux and Mac

Same reasoning as Windows: it's free, cross-platform, and reads the same
`CMakeLists.txt` every lecture in this course ships with. Install it via
the Qt Online Installer, selecting just the **Qt Creator** component.

---

*The default kit*

## Qt Creator will pick your system compiler

Unlike Windows, Linux and Mac almost always already have a C++ compiler
installed system-wide:

- **Linux** - usually **GCC**, already on the system or one
  `apt`/`dnf`/`pacman` install away.
- **Mac** - **Apple Clang**, installed as part of the Xcode Command Line
  Tools (`xcode-select --install`).

Qt Creator detects it automatically and creates a Kit for you - in most
cases, **you won't need to configure a Kit by hand at all**.

---

*The catch*

## That default compiler might be old

Your distro's or macOS's system compiler is whatever version shipped
when your OS was released or last updated - not necessarily the latest
GCC or Clang. This course is written against **C++23**, which needs a
fairly recent compiler.

<div class="callout">A system GCC/Clang that's a few years old may not
build every example in this course - that's not a mistake on your part,
it's just what "the default compiler" means.</div>

---

*Checking your version*

## Check before you assume

```sh
g++ --version
clang++ --version
```

Compare what you get against
[cppreference's compiler support table](https://en.cppreference.com/w/cpp/compiler_support)
(lecture 2.5 covers this in depth).

---

*Opening this lecture*

## Building this lecture's program

<div class="shot" data-label="Qt Creator - Configure Project screen on Linux/Mac"></div>

**File -> Open File or Project**, select this folder's `CMakeLists.txt`,
confirm the detected Kit, then **Configure Project**. Build and run
`rooster` the same way you would any Qt Creator project.

---

*If it's too old*

## If your compiler turns out to be too old

You don't need to upgrade your whole system compiler just for this
course. Lecture 2.6 covers **Docker** - a way to get a modern GCC or
Clang without touching anything already installed.
