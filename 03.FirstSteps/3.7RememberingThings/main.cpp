#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <fstream>

void greetPerson(std::string name) {
    std::println("Hello, {}!", name);
}

std::vector<std::string> collectFriendNames() {
    std::vector<std::string> friends;

    std::println("\nLet's add some friends. Type a name and press enter.");
    std::println("Press enter on an empty line when you're done.");

    while (true) {
        std::print("Friend's name: ");
        std::string friendName;
        std::getline(std::cin, friendName);

        if (friendName.empty()) {
            break;
        }

        friends.push_back(friendName);
    }

    return friends;
}

void saveFriendsToFile(const std::vector<std::string>& friends, const std::string& fileName) {
    std::ofstream outputFile(fileName);
    for (const std::string& friendName : friends) {
        outputFile << friendName << "\n";
    }
    std::println("Saved {} friend(s) to {}", friends.size(), fileName);
}

std::vector<std::string> loadFriendsFromFile(const std::string& fileName) {
    std::vector<std::string> friends;
    std::ifstream inputFile(fileName);

    std::string friendName;
    while (std::getline(inputFile, friendName)) {
        friends.push_back(friendName);
    }

    return friends;
}

int main() {

    std::string name;
    int age{};

    std::print("What is your name? ");
    std::getline(std::cin, name);

    std::print("How old are you? ");
    std::cin >> age;
    std::cin.ignore();

    greetPerson(name);

    if (age >= 18) {
        std::println("You are an adult.");
    } else {
        std::println("You are a minor.");
    }

    std::vector<std::string> friends = collectFriendNames();

    // A relative filename like this is created in whatever directory you
    // *ran the program from*, not necessarily next to main.cpp or inside
    // build/. Following this course's documented workflow (running
    // `./build/rooster` from this lecture folder) puts it right here, next
    // to main.cpp; cd-ing into build/ first and running `./rooster` from
    // there would put it inside build/ instead.
    const std::string fileName = "friends.txt";
    saveFriendsToFile(friends, fileName);

    // Read the file back in, proving the data survives after the program ends and restarts.
    std::vector<std::string> friendsFromDisk = loadFriendsFromFile(fileName);

    std::println("\nReloaded from {}:", fileName);
    for (const std::string& friendName : friendsFromDisk) {
        std::println(" - {}", friendName);
    }

    return 0;
}
