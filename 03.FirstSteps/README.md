# Chapter 3: First Steps

## The running example: a personal profile

Throughout this chapter we build up one small program: something that greets
you by name, asks a few questions about you, and - by the end of the chapter -
remembers your friends list between runs, growing it further each time you
run it. Nothing fancy, but it's a natural excuse to meet every foundational
building block of a C++ program, one lecture at a time, instead of learning
them in isolation.

## What does a program like this actually need to do?

| Need | Example | C++ building block |
|---|---|---|
| Say something to the screen | `"Hello there!"` | Output |
| Do a named, reusable action | greet a person by name | A function |
| Ask the user something and read the answer | "What is your name?" | Input |
| Compute something new from what was typed | the year you'll turn 100 | Arithmetic on variables |
| Follow a different path depending on the answer | adult vs. minor, comparing two ages | A decision (`if`/`else`) |
| Repeat an action until told to stop | collecting friend names | A loop (`while`) |
| Hold a growing list of things | the friends you added | `std::vector` - a ready-made collection |
| Remember data between separate runs of the program | friends saved to disk | File I/O (`<fstream>`) |
| Pick up where you left off, not just replay the last run | loading existing friends, then adding more | Combining file I/O with functions |

Every one of these is something almost any program needs to do, which is why
they come first - before we even talk about the different kinds of data a
variable can hold (that's chapter 4).

## Lecture by lecture

- **3.2 Your First Program** - printing text to the screen, and the
  difference between a one-line `//` comment and a `/* block */` comment.
- **3.3 Statements and Functions** - grouping repeatable behavior into a
  function (`greetPerson`), and the difference between a compile-time error
  (the program won't even build) and a runtime error (it builds, but breaks
  while running).
- **3.4 Talking to the User** - reading input with `std::cin`/`std::getline`
  and printing prompts without a trailing newline. The lecture doesn't stop
  at just echoing input back - it computes something new from it (the year
  you'll turn 100), because that's the moment a program starts being useful
  instead of just being a fancy printer.
- **3.5 Making Decisions** - branching program flow with `if`/`else`, first
  against a fixed value (adult vs. minor), then between two variables
  (comparing your age with a friend's) - the same comparison operators,
  applied where they're actually useful instead of listed in isolation.
- **3.6 Doing It Many Times** - looping with `while`, breaking out of a loop,
  and collecting values into a `std::vector`. You don't need to know how a
  `std::vector` works inside to use one - it's a ready-made, growable
  collection C++ gives you, the same way `std::string` is a ready-made
  collection of characters.
- **3.7 Saving and Loading Files** - `<fstream>` for the first time, written
  raw and inline in `main()` (no helper functions yet) so the stream
  mechanics are the whole focus: open an `std::ofstream`, write the friends
  list to it with `<<`, then open an `std::ifstream` and read it back line by
  line with the same `std::getline` already used for keyboard input - a file
  is just another stream of text as far as C++ is concerned.
- **3.8 Remembering Things** - the chapter's capstone. Takes the raw file I/O
  from 3.7 and wraps it in functions (`loadFriendsFromFile`,
  `saveFriendsToFile`), then uses them properly: load whatever friends are
  already saved *first*, show them, let you add more, and save the combined
  list back - so the friends list actually grows a little more every time you
  run the program, instead of starting over each time.

## How C++'s latest features help

- **`std::print` / `std::println`** (C++23) replace `std::cout <<` chains
  with a single, readable, `{}`-style format string from the very first
  lecture - no stream operators to explain before you can print anything.
  `std::cin`/`std::getline` are still used for input, since C++23 doesn't
  yet have a formatted-input equivalent.
- **Brace initialization (`{}`)**, e.g. `int age{}`, is used for every
  variable that needs a starting value - it's the same safe habit this
  course leans on again once chapter 4 explains *why* it matters
  (narrowing conversions).

## Building the code

Every lecture folder has its own `CMakeLists.txt`. If you don't have a C++23
compiler installed locally, use one of the ready-made Docker images in
[`../docker`](../docker) - see that folder's README for exact commands.

## Debugging these programs

Debugging isn't a topic reserved for once things get complicated - it's a
habit worth building from the very first lecture, the moment 3.2 or 3.3
declares its first variable. Long before there's input or a file to reason
about, a debugger already answers the most basic question you'll ever ask
about a running program: "what does this variable actually hold right now?"
Get comfortable pausing a program and looking at a value here, while the
programs are still small, and it stops being a special skill you reach for
only when stuck - it becomes how you read code, period. These notes assume
the project (a lecture folder's `CMakeLists.txt`) is already open in the IDE.

**The basic idea, regardless of IDE:** click in the gutter to the left of a
line number to set a breakpoint (a red dot appears), then start debugging
instead of just running. The program pauses right before that line executes,
and you can inspect variables, then step forward one line at a time.

Even in 3.2 (no variables yet) or 3.3 (`greetPerson`'s `name` parameter),
breakpointing a line and looking at what's in scope is worth doing just to
see the mechanics work. Once lectures start reading input (3.4 onward) and
reading/writing files (3.7/3.8), the same habit pays off even more - a good
breakpoint there is the line right *after* a prompt's
`std::cin`/`std::getline` call, so stepping onto that line proves what
actually got read into the variable.

### Visual Studio

1. Set a breakpoint (click the gutter next to, say, the `std::getline(std::cin, name);`
   line).
2. Press **F5** (or the green "Local Windows Debugger" button) instead of
   Ctrl+F5. This builds a Debug version and launches it under the debugger
   automatically.
3. The console window opens and the program runs up to your breakpoint.
4. **F10** steps over a line (use this for `std::cin`/`getline` calls - you
   don't want to step into stream internals). **F11** steps into a function
   you wrote, like `loadFriendsFromFile`, so you can watch it work line by
   line.
5. While paused, open **Debug -> Windows -> Locals** to see every local
   variable update live as you step - this is the clearest way to watch a
   `std::vector` (like `friends`) grow one `push_back` at a time in 3.6-3.8.
6. To only stop under a specific condition (e.g. only when `age` is under
   18), right-click a breakpoint -> **Conditions...** and enter something
   like `age < 18`.

### Qt Creator

1. Same idea: click the gutter to set a breakpoint, then press **F5** (or the
   Debug icon in the left sidebar) instead of plain Run.
2. **Important:** for a console program like these, open **Projects -> Run**
   and make sure **"Run in terminal"** is checked. Without it, prompts and
   output can end up somewhere you're not looking (or appear to not show up
   at all) once a debugger is attached - this trips up almost everyone the
   first time. If you toggle it, apply and start a fresh debug session for it
   to take effect.
3. Stepping uses the same **F10** (Step Over) / **F11** (Step Into) as Visual
   Studio.
4. The **Locals and Expressions** panel (bottom, appears automatically when
   you hit a breakpoint) is the equivalent of VS's Locals window.
5. Conditional breakpoints: right-click the breakpoint dot -> **Edit
   Breakpoint...** -> set a **Condition**.
6. If the embedded terminal's `cmd.exe` look bothers you, **Preferences ->
   Terminal** lets you point **Shell path** at PowerShell instead (e.g.
   `C:\WINDOWS\System32\WindowsPowerShell\v1.0\powershell.exe`).

### The one thing that trips people up in both tools

You can't step "into" `std::cin >> age` or `std::getline(...)` to watch
keystrokes arrive - reading input is atomic as far as the debugger is
concerned. The pattern that works is always: breakpoint on the line *after*
the read, step over the read itself, then inspect the variable that just got
filled in. The same idea applies to reading a line from `friends.txt` in
3.7/3.8 - it's just another stream, so it debugs the same way keyboard input
does.
