#include <iostream>
#include <print>
#include <string>
#include <vector>

void greetPerson(std::string name) {
    std::println("Hello, {}!", name);
}

int main() {

    std::string name;
    int age{};

    std::print("What is your name? ");
    std::getline(std::cin, name);

    std::print("How old are you? ");
    std::cin >> age;
    std::cin.ignore(); // discard the leftover newline left behind by std::cin >> age

    greetPerson(name);

    if (age >= 18) {
        std::println("You are an adult.");
    } else {
        std::println("You are a minor.");
    }

    // A vector is a growable list of values - here, a list of friend names.
    std::vector<std::string> friends;

    std::println("\nLet's add some friends. Type a name and press enter.");
    std::println("Press enter on an empty line when you're done.");

    // A loop repeats the same statements until we tell it to stop.
    while (true) {
        std::print("Friend's name: ");
        std::string friendName;
        std::getline(std::cin, friendName);

        if (friendName.empty()) {
            break; // empty line means we're done adding friends
        }

        friends.push_back(friendName);
    }

    std::println("\nYou added {} friend(s):", friends.size());
    for (const std::string& friendName : friends) {
        std::println(" - {}", friendName);
    }

    return 0;
}
