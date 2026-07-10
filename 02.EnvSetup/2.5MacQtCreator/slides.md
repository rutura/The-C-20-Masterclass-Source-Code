---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 2 · Environment Setup'
---

<!-- _class: lead -->

# Mac: Xcode and Qt Creator

## A compiler you already have, and the IDE we recommend

---

*Two things, not one*

## Compiler vs. IDE, on a Mac

On a Mac, **Xcode** and **Apple Clang** are easy to conflate, but they're
two different things:

- **Apple Clang** - the compiler. Installed via the much smaller **Xcode
  Command Line Tools**, not the full Xcode app.
- **Xcode** - Apple's own IDE. You don't need it for this course - we
  recommend **Qt Creator** instead, same as Linux and Windows.

---

*Install them Both*

## You can use either

Install **XCode** from the App Store, and then get a compiler:

```sh
xcode-select --install
```

This installs the **Xcode Command Line Tools**, which includes Apple
Clang, `make`, and other command-line build essentials.
download required.

---

*Recommended IDE*

## Qt Creator on Mac

Free, cross-platform, and reads the same `CMakeLists.txt` every lecture
in this course ships with. Install Qt and Qt Creator using the **Qt Online Installer.** 
selecting just the **Qt Creator** component.

---

*The default kit*

## Qt Creator will pick up Apple Clang automatically

Once the Command Line Tools are installed, Qt Creator detects Apple
Clang and offers a **Kit** that uses it. 

---

*The catch*

## Apple Clang isn't quite the same as upstream Clang

Apple Clang tracks upstream LLVM/Clang, but on its own release cadence
tied to macOS versions - its version numbers don't line up 1:1 with the
`clang++ --version` you'd see on Linux. This course is written against
**C++23**, which needs a fairly recent one.

<div class="callout">An older macOS with an older Apple Clang may not
build every example in this course - that's not a mistake on your part,
it's just what "the default compiler" means.</div>

---

*Checking your version*

## Check before you assume

```sh
clang++ --version
```

If your version is less than 20, you may need to install a newer compiler. **But don't panic** - in a later lecture I will show you how to use **Docker** to get a modern GCC or Clang without touching anything already installed on your system.

---

*Opening this lecture*

## Building this lecture's program

**File -> Open File or Project**, select a lecture's `CMakeLists.txt`,
confirm a Kit, then **Configure Project**. Build and run
`rooster` the same way you would any Qt Creator project.