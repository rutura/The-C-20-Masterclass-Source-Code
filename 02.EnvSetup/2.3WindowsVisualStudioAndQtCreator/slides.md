---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 2 · Environment Setup'
---

<!-- _class: lead -->

# Windows: Visual Studio and Qt Creator

## Two mainstream options, one compiler in common

---

*Two IDEs, one theme*

## Your choice on Windows

- **Visual Studio** - free Community edition, ships its own compiler
  (MSVC).
- **Qt Creator** - a lighter, cross-platform IDE. On Windows it doesn't
  ship a compiler of its own - it needs you to pick a **Kit**.

Both read the same `CMakeLists.txt` from this course. Pick whichever one
you're more comfortable with.

---

*Visual Studio*

## Installing Visual Studio

<div class="shot" data-label="Visual Studio Installer - Desktop development with C++ workload"></div>

1. Download the Visual Studio Installer, choose **Community** (free).
2. Under **Workloads**, check **Desktop development with C++**.
3. That workload includes MSVC, the Windows SDK, and CMake support - you
   don't install those separately.

---

*Opening a lecture folder*

## Open any lecture folder directly

Visual Studio can open a folder containing a `CMakeLists.txt` without a
`.sln` file at all: **File -> Open -> CMake...** and pick this lecture's
folder.

<div class="shot" data-label="Visual Studio - Open Folder / CMake project view"></div>

Visual Studio detects `CMakeLists.txt`, configures the project, and shows
`rooster` as the run/debug target.

---

*MSVC*

## MSVC - the compiler that comes with it

Visual Studio's C++ compiler is called **MSVC**. Its C++23 support is
controlled by a compiler flag, not a version number you pick yourself:

```text
/std:c++latest
```

CMake's `set(CMAKE_CXX_STANDARD 23)` (already in this course's
`CMakeLists.txt`) asks CMake to add the right flag for you automatically.

---

*Qt Creator*

## Installing Qt Creator

<div class="shot" data-label="Qt Online Installer - component selection"></div>

The Qt Online Installer lets you select **Qt Creator** as a standalone
component - you don't need to install the full Qt framework or any Qt
libraries just to use it as a C++ IDE.

---

*Kits*

## Kits - a bundle Qt Creator needs to build anything

A **Kit** = a compiler + a debugger + (optionally) a Qt version, bundled
together under one name. Qt Creator can't build a project until at least
one Kit is configured.

On Windows, the installer usually detects one automatically if Visual
Studio is already installed (an **MSVC kit**). You can also add:

- a **MinGW** kit (a GCC build for Windows)
- an **LLVM/Clang** kit, if you've installed one separately

---

*Picking a Kit*

## Opening this lecture in Qt Creator

<div class="shot" data-label="Qt Creator - Configure Project screen, choosing a Kit"></div>

**File -> Open File or Project**, choose this folder's `CMakeLists.txt`.
Qt Creator shows a **Configure Project** screen listing every Kit it
knows about - check the one you want to build with, then **Configure
Project**.

---

*Different kits, different support*

## Not all kits support C++23 equally

MSVC, MinGW, and LLVM/Clang kits are three genuinely different
compilers - each with its own pace of adding new C++ features. A kit
that's a version or two behind may not support everything this course
uses yet.

Lecture 2.5 shows how to check, for whichever kit you end up using.
