#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <fstream>

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
    std::cin.ignore();

    greetPerson(name);

    if (age >= 18) {
        std::println("You are an adult.");
    } else {
        std::println("You are a minor.");
    }

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

    // Everything above only lives in the program's memory - it disappears
    // the moment the program ends. Writing to a file is how a program
    // remembers something between separate runs.
    //
    // std::ofstream ("output file stream") opens a file for writing. Once
    // it's open, you write to it with << just like you would with std::cout -
    // the only difference is where the text ends up.
    const std::string fileName = "friends.txt";
    std::ofstream outputFile(fileName);

    for (const std::string& friendName : friends) {
        outputFile << friendName << "\n";
    }

    outputFile.close(); // done writing - close the file so the data is flushed to disk

    std::println("\nSaved {} friend(s) to {}", friends.size(), fileName);

    // std::ifstream ("input file stream") opens a file for reading. Reading
    // it back line by line uses the same std::getline you've already used
    // to read from the keyboard - a file and the keyboard are both just a
    // stream of text as far as C++ is concerned.
    std::ifstream inputFile(fileName);
    std::vector<std::string> friendsFromDisk;

    std::string line;
    while (std::getline(inputFile, line)) {
        friendsFromDisk.push_back(line);
    }

    inputFile.close();

    std::println("\nReloaded from {}:", fileName);
    for (const std::string& friendName : friendsFromDisk) {
        std::println(" - {}", friendName);
    }

    return 0;
}
