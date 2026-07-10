---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 2 · Environment Setup'
---

<!-- _class: lead -->

# Linux: Qt Creator

## Uses compiler that's already on your system

---

*Recommended*

## Qt Creator on Linux

Free, cross-platform, and reads the same `CMakeLists.txt` every lecture
in this course ships with. Install Qt and Qt Creator using the **Qt Online Installer**.

---

*The default kit*

## Qt Creator will pick your system compiler

Linux will almost always already have a C++ compiler installed system-wide.
If yours doesn't yet, install one with your distro's package manager. 
Qt Creator will detect it automatically and offer a **Kit** that uses it.

---

*The catch*

## That default compiler might be old

Your distro's system GCC is whatever version shipped when your OS was
released or last updated - not necessarily the latest one. This course is
written against **C++23**, which needs a fairly recent compiler.

<div class="callout">A system GCC that's a few years old may not build
every example in this course - that's not a mistake on your part, it's
just what "the default compiler" means.</div>

---

*Checking your version*

## Check before you assume

```sh
g++ --version
```

If your version is less than 14, you may need to install a newer compiler. 
**But don't panic** - in a later lecture I will show you how to use 
**Docker** to get a modern GCC or Clang without touching anything 
already installed on your system.

---

*Opening this lecture*

## Building this lecture's program

**File -> Open File or Project**, select a lecture's `CMakeLists.txt`,
confirm a Kit, then **Configure Project**. Build and run
`rooster` the same way you would any Qt Creator project.