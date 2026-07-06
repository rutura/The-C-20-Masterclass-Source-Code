#include <iostream>
#include <string>
#include <vector>

void greetPerson(std::string name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {

    std::string name;
    int age{};

    std::cout << "What is your name? ";
    std::getline(std::cin, name);

    std::cout << "How old are you? ";
    std::cin >> age;
    std::cin.ignore(); // discard the leftover newline left behind by std::cin >> age

    greetPerson(name);

    if (age >= 18) {
        std::cout << "You are an adult." << std::endl;
    } else {
        std::cout << "You are a minor." << std::endl;
    }

    // A vector is a growable list of values - here, a list of friend names.
    std::vector<std::string> friends;

    std::cout << "\nLet's add some friends. Type a name and press enter." << std::endl;
    std::cout << "Press enter on an empty line when you're done." << std::endl;

    // A loop repeats the same statements until we tell it to stop.
    while (true) {
        std::cout << "Friend's name: ";
        std::string friendName;
        std::getline(std::cin, friendName);

        if (friendName.empty()) {
            break; // empty line means we're done adding friends
        }

        friends.push_back(friendName);
    }

    std::cout << "\nYou added " << friends.size() << " friend(s):" << std::endl;
    for (const std::string& friendName : friends) {
        std::cout << " - " << friendName << std::endl;
    }

    return 0;
}
