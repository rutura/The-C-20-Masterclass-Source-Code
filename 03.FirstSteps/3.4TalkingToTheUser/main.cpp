#include <iostream>
#include <print>
#include <string>

void greetPerson(std::string name) {
    std::println("Hello, {}!", name);
}

int main() {

    std::string name;
    int age{};

    // std::print sends text to the console. std::cin/std::getline read text from it.
    std::print("What is your name? ");
    std::getline(std::cin, name); // getline reads a full line, including spaces

    std::print("How old are you? ");
    std::cin >> age;

    greetPerson(name);
    std::println("You are {} years old.", age);

    return 0;
}
