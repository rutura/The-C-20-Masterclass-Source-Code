---
marp: true
theme: editorial
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# Remembering Things

## Functions to Save and Load Files

---

*The plan*

## What this lecture does

Takes the raw file I/O from the last lecture and wraps it in functions, then uses them properly:

1. **Load** whatever friends are already saved
2. **Show** them
3. Let the user **add more**
4. **Save** the combined list back

The friends list grows a little more every time you run the program.

---

*Loading*

## Wrapping file I/O in a function

```cpp
std::vector<std::string> loadFriendsFromFile(const std::string& fileName) {
    std::vector<std::string> friends;
    std::ifstream inputFile(fileName);

    std::string friendName;
    while (std::getline(inputFile, friendName)) {
        friends.push_back(friendName);
    }

    return friends;
}
```

---

*Saving*

## The other half

```cpp
void saveFriendsToFile(const std::vector<std::string>& friends,
                        const std::string& fileName) {
    std::ofstream outputFile(fileName);
    for (const std::string& friendName : friends) {
        outputFile << friendName << "\n";
    }
    std::println("Saved {} friend(s) to {}", friends.size(), fileName);
}
```

---

*Load first*

## Load first, THEN collect more

```cpp
std::vector<std::string> friends = loadFriendsFromFile(fileName);

std::println("\nYou already have {} friend(s) saved:", friends.size());
for (const std::string& friendName : friends) {
    std::println(" - {}", friendName);
}

std::vector<std::string> newFriends = collectMoreFriendNames();
friends.insert(friends.end(), newFriends.begin(), newFriends.end());

saveFriendsToFile(friends, fileName);
```

---

*Chapter Wrap-up*

## What this program actually needed

| Need | C++ building block |
|---|---|
| Say something to the screen | Output |
| Do a named, reusable action | A function |
| Ask the user something | Input |
| Compute something new | Arithmetic |
| Follow a different path | `if` / `else` |
| Repeat until told to stop | A loop |
| Hold a growing list | `std::vector` |
| Remember across runs | File I/O |

---

*In Your Toolbox*

- **`std::print` / `std::println`** - a single `{}`-style format string
  instead of chained `std::cout <<` - readable from lecture one
- **Brace initialization (`{}`)** - `int age{};` It makes your code safer
- **`std::vector`** - a ready-made collection that grows as you add to it
- **File I/O** - `std::ifstream` and `std::ofstream` for reading and writing files
- **Functions** - named, reusable actions that can take input and return output
- **Decisions and Loops** - `if` / `else` and `while` let your program follow different paths and repeat actions