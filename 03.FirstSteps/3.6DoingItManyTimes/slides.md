---
marp: true
theme: masterclass
paginate: true
---

<!-- _class: lead -->
# 3.6 Doing It Many Times

---

## while - repeat until told to stop

```cpp
while (true) {
    std::print("Friend's name: ");
    std::string friendName;
    std::getline(std::cin, friendName);

    if (friendName.empty()) {
        break; // empty line means we're done
    }

    friends.push_back(friendName);
}
```

---

## A collection, ready-made

C++ ships with ready-made collections - you don't have to build your own
growable list.

```cpp
std::vector<std::string> friends;
```

`std::vector<std::string>` is a list of strings that **grows** as you add
to it with `push_back`.

Same idea as `std::string` being a ready-made collection of characters.

---

## Looping over the collection

```cpp
std::println("\nYou added {} friend(s):", friends.size());
for (const std::string& friendName : friends) {
    std::println(" - {}", friendName);
}
```

A range-based `for` visits every element, one at a time.

---

## break

`break` exits a loop immediately, regardless of the loop's condition.

```cpp
if (friendName.empty()) {
    break;
}
```

Without it, `while (true)` would never stop on its own.

---

<!-- _class: lead -->
# Next: 3.7
## Saving and Loading Files
