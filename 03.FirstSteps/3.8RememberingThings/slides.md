---
marp: true
theme: masterclass
paginate: true
---

<!-- _class: lead -->
# 3.8 Remembering Things

---

## The chapter's capstone

Takes the raw file I/O from 3.7 and wraps it in functions, then uses them
properly:

1. **Load** whatever friends are already saved
2. **Show** them
3. Let the user **add more**
4. **Save** the combined list back

The friends list grows a little more every time you run the program.

---

## Wrapping file I/O in functions

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

## Run it twice

**First run** - `friends.txt` doesn't exist yet:
```
You already have 0 friend(s) saved:
```

**Second run** - picks up right where you left off:
```
You already have 2 friend(s) saved:
 - Grace
 - Hopper
```

---

<!-- _class: lead -->
# End of Chapter 3
## First Steps
