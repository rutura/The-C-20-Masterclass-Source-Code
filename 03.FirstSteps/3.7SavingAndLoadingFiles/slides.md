---
marp: true
theme: masterclass
paginate: true
---

<!-- _class: lead -->
# 3.7 Saving and Loading Files

---

## The problem

Everything we've built so far only lives in the program's memory - it
disappears the moment the program ends.

**File I/O** is how a program remembers something between separate runs.

---

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

## The key idea

A file and the keyboard are both just a **stream of text** as far as
C++ is concerned.

- keyboard in -> `std::cin`
- console out -> `std::cout` / `std::print`
- file in -> `std::ifstream`
- file out -> `std::ofstream`

---

## Proving it worked

```cpp
std::println("\nReloaded from {}:", fileName);
for (const std::string& friendName : friendsFromDisk) {
    std::println(" - {}", friendName);
}
```

Written this run, read back this same run - next lecture makes it
actually persist *across* runs.

---

<!-- _class: lead -->
# Next: 3.8
## Remembering Things
