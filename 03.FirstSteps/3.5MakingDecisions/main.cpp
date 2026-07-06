#include <iostream>
#include <string>

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

    greetPerson(name);

    // An "if/else" lets the program make a decision and follow different paths.
    if (age >= 18) {
        std::cout << "You are an adult." << std::endl;
    } else {
        std::cout << "You are a minor." << std::endl;
    }

    return 0;
}
