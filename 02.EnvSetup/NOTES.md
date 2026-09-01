# Environment Setup

You need three things to work through this course:

- A **C++ compiler**. This is the program that turns your `.cpp` source
  text into an executable the machine can run. It also comes bundled with
  a debugger for stepping through code. Any of the mainstream ones works
  for this course; the videos lean on whichever is furthest ahead on the
  newest C++ features.
  - **MSVC** — Microsoft's compiler, Windows only, ships with Visual
    Studio.
  - **GCC** — the GNU compiler, standard on Linux, also available on
    Windows and Mac.
  - **Clang** — the LLVM compiler, the default on macOS and usable
    everywhere.
- A **build tool**. Real projects are more than one file, and calling the
  compiler by hand for each one does not scale. A build tool reads a
  project description and works out what to compile, in what order, with
  which flags. This course uses **CMake**, which is the de facto standard
  in the C++ world and what every lecture folder is set up for. CMake does
  not build directly; it generates files for an underlying build system:
  - **Ninja** — a fast, minimal build system, what the course uses inside
    the container.
  - **Make** — the long-standing Unix default.
  - A **Visual Studio** or **Xcode** project — when you build from inside
    those IDEs.
- An **editor or IDE** to tie them together. You could use a plain text
  editor plus a terminal, but an IDE bundles the editor, a button to
  invoke CMake and the compiler, and a graphical debugger in one place.
  The common choices:
  - **Visual Studio** — Windows.
  - **Qt Creator** — all three platforms.
    parts later in the course.
  - **Xcode** — macOS.
  - **VS Code** with C++ extensions — all platforms.

This file walks through getting that stack running on Windows, Linux, and
macOS, and then shows a Docker option for anyone who wants a modern
compiler without touching their system install.

Pick the section for your operating system. You do not need to read the
others.

A note on compiler versions: the course targets **C++23 and beyond**. The
newer your compiler, the more of the course you can follow line for line.
Older compilers still work for most of the material, and wherever a feature
needs a very recent toolchain the video will call it out so you are not
left guessing.

## 1. Windows

On Windows you have two good paths. Most students on Windows use **Visual
Studio**; **Qt Creator** is the second option.

### Option A: Visual Studio

Visual Studio ships its own compiler (MSVC), CMake, and debugger in one
installer, so this is the least fiddly way to get started on Windows.

1. Download **Visual Studio Community** from
   <https://visualstudio.microsoft.com/downloads/>. Community is free for
   individuals, students, and open source.
2. Run the installer. In the **Workloads** tab, check **Desktop
   development with C++**. That workload includes the MSVC compiler, the
   Windows SDK, CMake, and the debugger.
3. Finish the install and launch Visual Studio.
4. Open a lecture folder with **File > Open > Folder** and point it at a
   folder that contains a `CMakeLists.txt` (for example
   `03.FirstSteps/3.2FirstCppProgram`). Visual Studio detects the CMake
   project, configures it, and lets you build and run with **F5**.

MSVC on current Visual Studio (at the time of recording) is the toolchain used in the videos to
demonstrate the newest features, because it tends to be ahead on C++23
support.

### Option B: Qt Creator

Use this if you want a lighter IDE.

1. Download and install **Qt and Qt Creator** from the Qt website. The open 
   source version is sufficient for the course.

2. The installer will give you different kit options depending on the operating
    system you are using. Choose the appropriate one for your platform.

3. Launch Qt Creator, open **Edit > Preferences > Kits**, and confirm at
   least one kit shows a valid compiler and CMake. Qt Creator usually
   auto-detects them.

4. Open a lecture with **File > Open File or Project** and select its
   `CMakeLists.txt`. Choose a kit when prompted, then build and run with
   **Ctrl+R**.

## 2. Linux

On Linux you install the compiler and CMake from your distribution's
package manager, then use **Qt Creator** as the IDE.

### Compiler and build tools

On Debian or Ubuntu:

```
sudo apt update
sudo apt install build-essential cmake ninja-build gdb git
```

On Fedora:

```
sudo dnf install gcc-c++ cmake ninja-build gdb git
```

On Arch:

```
sudo pacman -S base-devel cmake ninja gdb git
```

`build-essential` (or `gcc-c++` / `base-devel`) pulls in GCC. Check what
you got with `g++ --version`. If your distribution's GCC is older than you
would like, either add a newer-toolchain repository for your distro 
(**do this if you know what you are doing**) or skip to the **Docker** 
section below for a current GCC or Clang without changing your system.

### Qt Creator

1. Download and install **Qt and Qt Creator** from the Qt website. The open 
   source version is sufficient for the course.
2. Install the kit that is appropriate for your platform.
3. Open a lecture with **File > Open File or Project**, select its
   `CMakeLists.txt`, pick the kit, and build and run with **Ctrl+R**.

## 3. Mac

On macOS you have two paths: Apple's **Xcode** with its bundled Clang, or
**Qt Creator** on top of the same command line tools.

### Command line tools

Both paths need Apple's command line tools. Install them with:

```
xcode-select --install
```

That gives you `clang` (Apple's build), `git`, and `make`. You still need
CMake separately. The easiest way is **Homebrew** (<https://brew.sh>):

```
brew install cmake ninja
```

### Option A: Xcode

1. Install **Xcode** from the Mac App Store, then launch it once so it
   finishes setting up components.
2. From a lecture folder, generate an Xcode project with CMake:

   ```
   cd 03.FirstSteps/3.2FirstCppProgram
   cmake -S . -B build -G Xcode
   open build/rooster.xcodeproj
   ```

3. In Xcode, pick the `rooster` scheme and press **Cmd+R** to build and
   run.

Apple's Clang lags the upstream LLVM release on the very newest C++23
features. If a lecture uses something Apple Clang does not have yet, use
the **Docker** option below for an up to date Clang.

### Option B: Qt Creator

1. Install Qt Creator from the **Qt Online Installer** at
   <https://www.qt.io/download-qt-installer> (a free account is required),
   or with `brew install --cask qt-creator`.
2. Launch Qt Creator and open **Qt Creator > Preferences > Kits**. The
   Clang from the command line tools and the CMake from Homebrew should be
   picked up as a working kit.
3. Open a lecture's `CMakeLists.txt` with **File > Open File or Project**,
   choose the kit, and build and run with **Cmd+R**.

## 4. Docker (optional, for a modern compiler)

If your system compiler is too old and you do not want to upgrade it, or
you just want a clean throwaway environment, this repo ships two
Dockerfiles under `02.EnvSetup`:

- `02.EnvSetup/gcc/Dockerfile` builds an image with **GCC 16**.
- `02.EnvSetup/clang/Dockerfile` builds an image with **Clang 21**.

Both give you top notch C++23 support, plus CMake, Ninja, a debugger,
`clang-format`, `clang-tidy`, and `vcpkg` already set up. This is a
console workflow: you edit files with your normal editor on your host
machine, and compile and run them inside the container.

You need **Docker** installed first: Docker Desktop on Windows and macOS
(<https://www.docker.com/products/docker-desktop/>), or the Docker Engine
package on Linux.

### 4.1 Build an image

Run these from the repo root. Each command names two paths:

- The path after `-f` is the **Dockerfile**, the recipe `docker` reads.
- The trailing path is the **build context**, the folder `docker` sends to
  the engine as the build's root. This only matters at build time; it has
  nothing to do with which of your files are visible inside the container
  later. Pointing it at the small `gcc` / `clang` folder (rather than
  letting it default to the whole repo) just keeps the build fast.

The image you get out of this contains the compiler, CMake, and Ninja, and
nothing of the course. Your course files are mounted in at run time, in
the next step.

GCC:

```
docker build -t cpp-masterclass-gcc -f 02.EnvSetup/gcc/Dockerfile 02.EnvSetup/gcc
```

Clang:

```
docker build -t cpp-masterclass-clang -f 02.EnvSetup/clang/Dockerfile 02.EnvSetup/clang
```

`-t` names the image. You only need to do this once (or again after the
Dockerfile changes). Check it landed with `docker images`.

### 4.2 Create the container once

You create a **named** container one time, telling it then which host
folder to mount. After that you never repeat this command: the name, the
image, and the mount are all recorded in the container, and you just start
and stop it.

Run this from the repo root so `PWD` is the repo.

On **Linux or macOS**:

```
docker run -it --name cpp-masterclass -v "$(pwd)":/workspace cpp-masterclass-gcc
```

On **Windows PowerShell**:

```
docker run -it --name cpp-masterclass -v "${PWD}:/workspace" cpp-masterclass-gcc
```

What the flags do:

- `-it` gives you an interactive terminal.
- `--name cpp-masterclass` gives the container a fixed name so you can
  refer back to it. Note there is **no** `--rm` here: we want the
  container to stick around after you exit.
- `-v host:/workspace` mounts the repo root into the container at
  `/workspace`, which is the working directory. Edits on the host show up
  inside immediately, and build output created inside shows up on the
  host. This mapping is remembered for the life of the container.

For the Clang image, use `cpp-masterclass-clang` as the image and give the
container a different name, for example `--name cpp-masterclass-clang`, so
the two do not collide.

### 4.3 Start the container every time after that

Once the container exists, you do not need to be in the repo folder and
you do not repeat the `-v` mapping. From anywhere:

```
docker start -ai cpp-masterclass
```

`-ai` attaches your terminal and reconnects stdin, so you land back at the
`bash` prompt in `/workspace` with the same mount as before. Typing `exit`
stops the container; `docker start -ai cpp-masterclass` brings it back
exactly as it was, including anything extra you installed inside it with
`apt`.

You only redo the `docker run --name` step from 4.2 if you delete the
container (`docker rm cpp-masterclass`) or rebuild the image.

### 4.4 Build and run a lecture inside the container

Once you are at the container's `bash` prompt, you are sitting in
`/workspace`, which is the repo. Change into any chapter and lecture and
build it the standard CMake way:

```
cd 03.FirstSteps/3.2FirstCppProgram
cmake -S . -B build -G Ninja
cmake --build build
./build/rooster
```

Every lecture builds the same way because they all define the same
`rooster` executable target. The `build/` folder is written back out to
the host through the mount, so you can delete it from your editor like any
other file. When you are done, type `exit` to stop the container.
