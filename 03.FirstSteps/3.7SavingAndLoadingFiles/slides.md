---
marp: true
theme: masterclass
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# 3.7 Saving and Loading Files

## Making data outlive the program

---

*3.7 / The problem*

## Everything so far disappears

Everything we've built lives only in the program's **memory** - it
disappears the moment the program ends.

<div class="callout"><strong>File I/O</strong> is how a program remembers something between separate runs.</div>

---

*3.7 / Writing*

## Writing a file

`std::ofstream` ("output file stream") opens a file for writing.

```cpp
#include <fstream>

std::ofstream outputFile("friends.txt");

for (const std::string& friendName : friends) {
    outputFile << friendName << "\n";
}

outputFile.close();
```

Write to it with `<<`, just like `std::cout`.

---

*3.7 / Reading*

## Reading a file back

`std::ifstream` ("input file stream") opens a file for reading.

```cpp
std::ifstream inputFile("friends.txt");
std::vector<std::string> friendsFromDisk;

std::string line;
while (std::getline(inputFile, line)) {
    friendsFromDisk.push_back(line);
}

inputFile.close();
```

Same `std::getline` already used for keyboard input.

---

*3.7 / The key idea*

## It's all just a stream

A file and the keyboard are both just a **stream of text** as far as
C++ is concerned.

| Direction | Tool |
|---|---|
| keyboard in | `std::cin` |
| console out | `std::cout` / `std::print` |
| file in | `std::ifstream` |
| file out | `std::ofstream` |

---

*3.7 / Proof*

## Proving it worked

```cpp
std::println("\nReloaded from {}:", fileName);
for (const std::string& friendName : friendsFromDisk) {
    std::println(" - {}", friendName);
}
```

Written this run, read back this same run - next lecture makes it
actually persist **across** runs.

<div class="shot" data-label="Screenshot: terminal — Saved N friend(s), then Reloaded from friends.txt listing"></div>

---

*3.7 / Debug a file write*

## Watch the file appear

Step over the `saveFriendsToFile`-equivalent write, then open
`friends.txt` in your IDE's file browser - it now exists, with the
friend names written to it.

<div class="shot" data-label="Screenshot: friends.txt open in editor immediately after stepping over the write"></div>

---

<!-- _class: lead -->

# Next: 3.8
## Remembering Things
