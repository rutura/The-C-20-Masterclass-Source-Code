#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void greetPerson(std::string name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

std::vector<std::string> collectFriendNames() {
    std::vector<std::string> friends;

    std::cout << "\nLet's add some friends. Type a name and press enter." << std::endl;
    std::cout << "Press enter on an empty line when you're done." << std::endl;

    while (true) {
        std::cout << "Friend's name: ";
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
        outputFile << friendName << std::endl;
    }
    std::cout << "Saved " << friends.size() << " friend(s) to " << fileName << std::endl;
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

    std::cout << "What is your name? ";
    std::getline(std::cin, name);

    std::cout << "How old are you? ";
    std::cin >> age;
    std::cin.ignore();

    greetPerson(name);

    if (age >= 18) {
        std::cout << "You are an adult." << std::endl;
    } else {
        std::cout << "You are a minor." << std::endl;
    }

    std::vector<std::string> friends = collectFriendNames();

    const std::string fileName = "friends.txt";
    saveFriendsToFile(friends, fileName);

    // Read the file back in, proving the data survives after the program ends and restarts.
    std::vector<std::string> friendsFromDisk = loadFriendsFromFile(fileName);

    std::cout << "\nReloaded from " << fileName << ":" << std::endl;
    for (const std::string& friendName : friendsFromDisk) {
        std::cout << " - " << friendName << std::endl;
    }

    return 0;
}
