#include <iostream>
#include <print>
#include <string>

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

    // An "if/else" lets the program make a decision and follow different paths.
    if (age >= 18) {
        std::println("You are an adult.");
    } else {
        std::println("You are a minor.");
    }

    // Comparisons aren't just for one variable against a fixed number -
    // they work between two variables too. Let's compare ages with a friend.
    std::string friendName;
    int friendAge{};

    std::print("\nWhat is your friend's name? ");
    std::getline(std::cin, friendName);

    std::print("How old are they? ");
    std::cin >> friendAge;

    if (age == friendAge) {
        std::println("{} and {} are the same age.", name, friendName);
    } else if (age < friendAge) {
        std::println("{} is younger than {}.", name, friendName);
    } else {
        std::println("{} is older than {}.", name, friendName);
    }

    return 0;
}
