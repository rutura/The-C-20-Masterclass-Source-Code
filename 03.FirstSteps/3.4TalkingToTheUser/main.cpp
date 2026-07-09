#include <iostream>
#include <print>
#include <string>

void greetPerson(std::string name) {
    std::println("Hello, {}!", name);
}

int main() {

    std::string name;
    int age{};
    int birthYear{};

    // std::print sends text to the console. std::cin/std::getline read text from it.
    std::print("What is your name? ");
    std::getline(std::cin, name); // getline reads a full line, including spaces

    std::print("How old are you? ");
    std::cin >> age;

    std::print("What year were you born? ");
    std::cin >> birthYear;

    greetPerson(name);
    std::println("You are {} years old.", age);

    // Reading input isn't very useful on its own - the moment it gets
    // interesting is when the program computes something new from it.
    int turns100In = birthYear + 100;
    std::println("You'll turn 100 in the year {}.", turns100In);

    return 0;
}
