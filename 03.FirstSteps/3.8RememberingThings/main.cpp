#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <fstream>

void greetPerson(std::string name) {
    std::println("Hello, {}!", name);
}

// Same idea as the raw std::ifstream loop from the previous lecture, just
// wrapped in a function so main() can ask for "the friends on disk" without
// caring how that's done.
std::vector<std::string> loadFriendsFromFile(const std::string& fileName) {
    std::vector<std::string> friends;
    std::ifstream inputFile(fileName);

    std::string friendName;
    while (std::getline(inputFile, friendName)) {
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

std::vector<std::string> collectMoreFriendNames() {
    std::vector<std::string> newFriends;

    std::println("\nAdd more friends. Type a name and press enter.");
    std::println("Press enter on an empty line when you're done.");

    while (true) {
        std::print("Friend's name: ");
        std::string friendName;
        std::getline(std::cin, friendName);

        if (friendName.empty()) {
            break;
        }

        newFriends.push_back(friendName);
    }

    return newFriends;
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

    // A relative filename like this is created in whatever directory you
    // *ran the program from*, not necessarily next to main.cpp or inside
    // build/. Following this course's documented workflow (running
    // `./build/rooster` from this lecture folder) puts it right here, next
    // to main.cpp; cd-ing into build/ first and running `./rooster` from
    // there would put it inside build/ instead.
    const std::string fileName = "friends.txt";

    // This is the payoff of the previous lecture: instead of writing once and
    // immediately reading it back, we load whatever is already on disk from
    // a previous run - the very first run, this is just an empty list.
    std::vector<std::string> friends = loadFriendsFromFile(fileName);

    std::println("\nYou already have {} friend(s) saved:", friends.size());
    for (const std::string& friendName : friends) {
        std::println(" - {}", friendName);
    }

    std::vector<std::string> newFriends = collectMoreFriendNames();
    friends.insert(friends.end(), newFriends.begin(), newFriends.end());

    saveFriendsToFile(friends, fileName);

    std::println("\n{} now has {} friend(s) saved in total:", name, friends.size());
    for (const std::string& friendName : friends) {
        std::println(" - {}", friendName);
    }

    return 0;
}
