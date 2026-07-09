---
marp: true
theme: editorial
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# Saving and Loading Files

## Making data outlive the program

---

*The problem*

## Everything so far disappears

Everything we've built lives only in the program's **memory** - it disappears the moment the program ends.

<div class="callout"><strong>File I/O</strong> is how a program remembers something between separate runs.</div>

---

*Writing*

## Writing a file

`std::ofstream` ("output file stream") opens a file for writing.

```cpp
#include <fstream>

// The file is created in the working directory.
// Where the program is run from.
std::ofstream outputFile("friends.txt");

for (const std::string& friendName : friends) {
    outputFile << friendName << "\n";
}

outputFile.close();
```

Write to it with `<<`, just like `std::cout`.

---

*Reading*

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

*The key idea*

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

*Debug a file write*

## Watch the file appear

Step over the `saveFriendsToFile`-equivalent write, then open
`friends.txt` in your IDE's file browser - it now exists, with the
friend names written to it.