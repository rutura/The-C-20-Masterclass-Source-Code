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
macOS, then shows an online option for quick experiments with no install at
all, and finally a Docker option for anyone who wants a modern compiler
without touching their system install.

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

## 4. Online: Compiler Explorer (no install, single-file snippets only)

Before setting up anything locally, [Compiler Explorer](https://godbolt.org)
(also known as "Godbolt") is the fastest way to try a single-file snippet
against a specific, very recent compiler version, right from a browser. It
is not a substitute for the local setup above — the course's lecture
folders are multi-file CMake projects, and Compiler Explorer only compiles
one source pane — but it is the easiest way to check whether a particular
C++23/26 feature is supported by a given compiler before you decide whether
to chase a newer toolchain locally.

1. Go to <https://godbolt.org>.
2. In the compiler pane on the right, pick a compiler from the dropdown
   (see recommendations below).
3. Paste your code into the left pane. It compiles automatically as you
   type; errors and warnings show inline and in the output pane.
4. Set the language standard in the compiler's **options** box (the small
   text field above the output, next to the compiler dropdown) since the
   defaults are usually older standards:
   - **GCC or Clang**: `-std=c++23` (or `-std=c++2b` on older compiler
     builds that have not yet renamed the flag once C++23 was finalized).
   - **MSVC**: `/std:c++latest` (MSVC's own `/std:c++23` also exists, but
     `/std:c++latest` tracks whatever the newest draft/standard features
     that build of MSVC supports, which is what the videos rely on for
     bleeding-edge features).

Recommended compilers to pick from the dropdown, matching what the videos
use:

- **GCC** — the newest **GCC 16** entry (trunk/snapshot builds are labelled
  separately from numbered releases; prefer the highest-numbered stable
  release, e.g. `x86-64 gcc 16.1`, over a trunk build unless you specifically
  want bleeding-edge/unreleased features).
- **Clang** — the newest stable numbered release in the dropdown (e.g.
  `x86-64 clang 21.1.0`); avoid `clang (trunk)` unless a feature is missing
  from the latest stable.
- **MSVC** — the newest `x64 msvc v19.latest` entry. Compiler Explorer keeps
  this pointed at the newest MSVC it has, which is the closest match to
  what current Visual Studio ships.

Since this is single-file only, use it to sanity-check a language feature
or standard-library call in isolation, then bring the working code back
into the matching lecture folder for the full CMake build.

## 5. Docker (optional, for a modern compiler)

If your system compiler is too old and you do not want to upgrade it, or
you just want a clean throwaway environment, this repo ships two
Dockerfiles under `02.EnvSetup`:

- `02.EnvSetup/gcc/Dockerfile` builds an image with **GCC 16**.
- `02.EnvSetup/clang/Dockerfile` builds an image with **Clang 21**.

Both give you top notch C++23 support, plus CMake, Ninja, a debugger,
`clang-format`, `clang-tidy`, and `vcpkg` already set up. The default
workflow is console based: you edit files with your normal editor on your
host machine, and compile and run them inside the container. **5.5** shows
the alternative — attaching a VS Code window straight to the running
container so the editor, IntelliSense, and debugger all use the
container's toolchain.

You need **Docker** installed first: Docker Desktop on Windows and macOS
(<https://www.docker.com/products/docker-desktop/>), or the Docker Engine
package on Linux.

### 5.1 Build an image

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

### 5.2 Create the container once

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

### 5.3 Start the container every time after that

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

If you forget whether the container still exists, `docker container ls` on
its own will **not** show it — that command only lists currently running
containers. A stopped container (the normal state between sessions) only
shows up with `docker container ls -a`, alongside its name and `Exited`
status. Find it there, then `docker start -ai <name>` brings it back with
the same mount.

You only redo the `docker run --name` step from 5.2 if you delete the
container (`docker rm cpp-masterclass`) or rebuild the image.

### 5.4 Build and run a lecture inside the container

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

### 5.5 Editing in VS Code attached to the container

The steps above are terminal only. If you would rather have an editor, a
graphical debugger, and IntelliSense that all run against the container's
compiler, VS Code can attach a window directly to the running container.
Only the VS Code UI runs on your host; your files, the compiler, and the
editor extensions all live inside the container.

This is optional — the console workflow in 5.4 is enough to follow the
course.

**Both images are set up the same way. The only thing that differs is the
container name from 5.2:** `cpp-masterclass` for the GCC container,
`cpp-masterclass-clang` for the Clang container. Use yours wherever a step
says *your container*. Everything else is identical because IntelliSense
reads the compiler and the flags straight out of the `compile_commands.json`
your build produces, so it follows whichever image you built with no
per-compiler tweaks.

#### On the host

- **VS Code** with the **Dev Containers** extension
  (`ms-vscode-remote.remote-containers`).
- Docker running, with your container from 5.2 started: `docker start
  <your container>`. You do not need `-ai` or a terminal in it — VS Code
  only needs the container to be running.

#### Attach and open a lecture

1. Command Palette (`F1` or `Ctrl+Shift+P`) > **Dev Containers: Attach to
   Running Container** > pick your container. A new window opens with a
   coloured *Container <your container>* badge in the bottom-left corner.
2. **File > Open Folder** and pick the lecture you are working on, for
   example `/workspace/03.FirstSteps/3.2FirstCppProgram`. Open one lecture
   folder, not the repo root (see the note at the end).

#### Two extensions, once per container

When attached, the Extensions view splits into a **LOCAL** group and a
**CONTAINER** group. Install both of these into the **CONTAINER** group:

- **C/C++** (`ms-vscode.cpptools`) — the IntelliSense engine: completion,
  go-to-definition, error checking, and the debugger UI.
- **CMake Tools** (`ms-vscode.cmake-tools`) — configure/build/run buttons
  in the status bar, and it writes the `compile_commands.json` that the
  C/C++ extension reads.

They install into `~/.vscode-server/extensions` inside the container and
survive `docker stop` / `docker start`, like anything you `apt install`.
Delete the container (`docker rm`) and they go with it — recreate it (5.2)
and reinstall. Do not add a second IntelliSense engine (such as clangd)
alongside C/C++; they fight over the same squiggles.

#### One setting, once per container

This is the entire configuration, and it goes in the container's own
settings so it never touches your host VS Code:

1. Command Palette > **Preferences: Open Remote Settings (JSON)**. The
   editor title must read *Remote Settings*, not *User Settings* — the
   Remote file lives inside the container at
   `~/.vscode-server/data/Machine/settings.json` and only applies while a
   window is attached to it.
2. Add:

   ```json
   {
     "cmake.configureOnOpen": true,
     "C_Cpp.default.compileCommands": "${workspaceFolder}/build/compile_commands.json"
   }
   ```

3. Save.

What the two lines do:

- `cmake.configureOnOpen` — the moment you open a lecture, CMake Tools
  configures it. The first time, it asks you to pick a kit; choose the
  Clang or GCC entry it found, or **[Unspecified]** to let CMake decide.
  It remembers the choice. Configuring writes `build/compile_commands.json`
  with the exact compiler and `-std=gnu++23` for that lecture.
- `C_Cpp.default.compileCommands` — points the C/C++ extension at that
  file. From then on IntelliSense uses the real compiler and the real
  standard, so `std::println`, `<print>`, and the rest of C++23 resolve
  with nothing further to do.

The same block works on both images: the compiler path inside
`compile_commands.json` is written by CMake when it configures, so the
C/C++ extension follows GCC or Clang on its own — no compiler path or
standard to set by hand.

#### Day to day

Open a lecture, wait a second for CMake Tools to configure it, and the
squiggles clear. Build and run from the CMake Tools buttons in the status
bar, or keep using the terminal exactly as in 5.4 — the `build/` folder is
the same one.

#### Notes

- **Open one lecture folder at a time, not the repo root.**
  `${workspaceFolder}` has to resolve to the lecture so
  `build/compile_commands.json` is found. Opening `/workspace` points it
  at a single build folder the lectures do not share.
- **A lecture needs configuring once before IntelliSense is correct.**
  That is what `cmake.configureOnOpen` handles; if a folder still shows
  C++23 names as unknown, run **CMake: Configure** from the palette. Until
  a `build/compile_commands.json` exists, the C/C++ extension falls back to
  an older standard.
- **Extensions and the Remote setting live with the container.** Rebuild
  the image (5.1) or recreate the container (5.2) and you redo the two
  extension installs and re-add the setting.
- **File ownership on Linux hosts.** The container runs as root, so
  `build/` folders it writes through the mount are root-owned on your
  host. `sudo chown -R "$USER" .` from the repo root clears it if it gets
  in your way.
