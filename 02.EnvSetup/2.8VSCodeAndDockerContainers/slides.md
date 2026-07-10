---
marp: true
theme: contrast
paginate: true
footer: 'Chapter 2 · Environment Setup'
---

<!-- _class: lead -->

# VS Code and Docker

## A full editor, wired into the container that builds your code

---

*Why this lecture*

## The gap left by the last lecture

You can already run a container and build inside it - but so far that
means an interactive shell and typing `build/rooster` by hand.
No syntax highlighting, no autocomplete, no clicking a line to set a
breakpoint. This lecture connects **Visual Studio Code**, running on your
machine, to that same container - so you get a real editor experience
while every build still happens inside Linux, on GCC 16 or Clang 21.

---

*The pieces*

## What you'll install

- **Visual Studio Code** - the editor itself (separate from Visual
  Studio, despite the name).
- **Dev Containers** extension. It lets VS Code talk to a container instead of your local filesystem.
- **C/C++** extension - IntelliSense and debugging.
- **CMake Tools** extension - Configure/Build/ Debug buttons for a `CMakeLists.txt` project.

All three install the same way: **Extensions** view (Ctrl+Shift+X), search the name, **Install**.

---

*Where Docker Desktop fits*

## Still the same Docker as the last lecture

Dev Containers doesn't replace Docker Desktop - it drives it. Docker
Desktop must already be installed and running on your Windows, Linux or Mac machine. 
If `docker run` already worked for you in the last lecture, you have all you need.

---

*The plan for this lecture*

## One of the ways to connect

- **Attach to a container you started yourself** - we'll keep it 
  running in a terminal, then connect VS Code to it.
---

*Step 1*

## Start a container, same as last lecture

Nothing new here - this is the exact command from the last lecture, run from the repo
root:

```powershell
# Windows (PowerShell)
docker run --rm -it -v "${PWD}:/workspace" masterclass-gcc:16
```

```sh
# Linux / macOS
docker run --rm -it -v "$(pwd):/workspace" masterclass-gcc:16
```

Leave this terminal open - the container is now running, with this
lecture's folder mounted at `/workspace` inside it.

---

*Step 2*

## Find it from VS Code

Open VS Code, then either:

- Command Palette (Ctrl+Shift+P) -> **"Dev Containers: Attach to Running
  Container..."**, then pick the container from the list, **or**
- click the **Remote Explorer** icon in the Activity Bar, expand
  **Containers**, and use the inline **Attach to Container** action next
  to the running container.

VS Code opens a **new window** connected to that container.

---

*Step 3*

## Point it at your code

That new window starts at the container's filesystem root, not your
code. Use **File -> Open Folder...** inside that window and open
`/workspace` - the exact folder you mounted with `-v` in step 1.

---

*Step 4*

## Install extensions - inside the container

Extensions run **on your machine** and **inside containers** separately.
Install **C/C++** and **CMake Tools** again from the Extensions view -
notice the button now says something like **"Install in Container"**.
Your local VS Code extensions don't automatically carry over.

---

*Step 5*

## Let CMake Tools find the compiler

Command Palette -> **"CMake: Select a Kit"**. CMake Tools scans the
container's `PATH` for compilers. Pick the one you want (GCC 16.1.0 in this lecture).  
file to write by hand.

---

*Step 6*

## Configure and build

Two commands, but now buttons instead of typing:

- **CMake: Configure** (Command Palette, or the status bar) - same as
  `cmake -B build -G Ninja .`
- **CMake: Build** - same as `cmake --build build`

Since this lecture's `CMakeLists.txt` only defines one target
(`rooster`), there's nothing else to pick.

---

*Step 7*

## Run it

Click the **Run** button in the CMake Tools status bar, or Command
Palette -> **"CMake: Run Without Debugging"**. Output appears in VS
Code's integrated terminal - still the container's terminal.
the editor now instead of the separate window from step 1.

---

*Step 8*

## Set a breakpoint and debug

Click in the gutter next to a line in `main.cpp` to set a breakpoint,
then **CMake: Debug** (or **Shift+F5**). No `launch.json` needed for this
basic case - CMake Tools uses `gdb`, already installed in this image, to
drive the debug session.

---

*If debugging refuses to start*

## A specific error to recognize

Some Docker setups block the `ptrace` syscall gdb needs to attach to a
process, surfacing as `ptrace: Operation not permitted`. If you see it,
re-run step 1's `docker run` with two extra flags:

```sh
docker run --rm -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
  -v "$(pwd):/workspace" masterclass-gcc:16
```

<div class="callout">These flags loosen container isolation - fine for a
local course sandbox, not something to reach for on a production
container.</div>

---

*Cleaning up*

## Ending the session

Closing the VS Code window just disconnects the editor - the container
(and the terminal from step 1) is still running. Since you started it
with `--rm`, typing `exit` in that original terminal stops **and**
removes the container in one step. Nothing to clean up by hand.

---

*Basic Docker commands worth knowing*

## You don't strictly need these today, but you will eventually

| Command | What it does |
|---|---|
| `docker images` | List images you've built or pulled (e.g. confirm `masterclass-gcc:16` exists) |
| `docker ps` (add `-a` for stopped ones too) | List containers |
| `docker exec -it <container> bash` | Open another shell into an already-running container |
| `docker logs <container>` | See a container's output history |
| `docker stop <container>` | Stop a running container |
| `docker rm <container>` / `docker rmi <image>` | Remove a container / an image |

---

*Image vs. container, one more time*

## The distinction that makes all of this make sense

An **image** (`masterclass-gcc:16`) is a fixed template - it never
changes just by using it. A **container** is one running (or stopped)
instance made *from* an image. You can start as many containers from the
same image as you like; each gets its own throwaway filesystem layer on
top, which is exactly why `--rm` is safe to use by default.

---

*The optional upgrade*

## devcontainer.json - letting VS Code manage the container

Instead of running `docker run` yourself, a `.devcontainer/devcontainer.json`
file next to a lecture's `CMakeLists.txt` lets **VS Code** create,
mount, and tear down the container for you:

```json
{
  "name": "C++ Masterclass (GCC 16)",
  "image": "masterclass-gcc:16",
  "workspaceFolder": "/workspace",
  "customizations": {
    "vscode": {
      "extensions": ["ms-vscode.cpptools", "ms-vscode.cmake-tools"]
    }
  }
}
```
---
*The optional upgrade*

## devcontainer.json - letting VS Code manage the container(contd)

With the `.devcontainer/devcontainer.json` in place, you can open 
the lecture folder locally, then **"Dev Containers: Reopen in
Container"** - no manual `docker run` at all. Extensions from
`customizations.vscode.extensions` install automatically every time.

I won't be exploring this further, because Visual Studio Code frequently
changes the devcontainer.json schema and the extension's behavior. The
interested student can explore this further on their own.