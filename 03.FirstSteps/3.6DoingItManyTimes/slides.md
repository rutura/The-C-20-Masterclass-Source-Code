---
marp: true
theme: masterclass
paginate: true
footer: 'Chapter 3 · First Steps'
---

<!-- _class: lead -->

# 3.6 Doing It Many Times

## Loops and your first collection

---

*3.6 / while*

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

*3.6 / break*

## break

`break` exits a loop immediately, regardless of the loop's condition.

```cpp
if (friendName.empty()) {
    break;
}
```

Without it, `while (true)` would never stop on its own.

---

*3.6 / A collection, ready-made*

## You don't have to build one

C++ ships with ready-made collections - you don't have to build your
own growable list.

```cpp
std::vector<std::string> friends;
```

`std::vector<std::string>` is a list of strings that **grows** as you
add to it with `push_back`.

<div class="callout">Same idea as <code>std::string</code> being a ready-made collection of characters. You don't need to know how <code>std::vector</code> works inside to use one.</div>

---

*3.6 / Looping over it*

## Looping over the collection

```cpp
std::println("\nYou added {} friend(s):", friends.size());
for (const std::string& friendName : friends) {
    std::println(" - {}", friendName);
}
```

A range-based `for` visits every element, one at a time - no manual
indexing required.

---

*3.6 / See it run*

<div class="shot tall" data-label="Screenshot: terminal — adding three friend names, then the printed list"></div>

---

*3.6 / Debug the collection*

## Watch it grow, one push_back at a time

Step into the loop and open your IDE's variable/locals view - watching
`friends` gain an element on each iteration is the clearest way to see
a `std::vector` actually grow.

<div class="shot" data-label="Screenshot: Locals/Expressions panel showing friends vector expanding across steps"></div>

---

<!-- _class: lead -->

# Next: 3.7
## Saving and Loading Files
