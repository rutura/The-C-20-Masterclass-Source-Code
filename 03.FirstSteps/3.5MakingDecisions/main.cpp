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

    greetPerson(name);

    // An "if/else" lets the program make a decision and follow different paths.
    if (age >= 18) {
        std::println("You are an adult.");
    } else {
        std::println("You are a minor.");
    }

    return 0;
}
