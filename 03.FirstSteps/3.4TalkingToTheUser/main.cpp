#include <iostream>
#include <string>

void greetPerson(std::string name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {

    std::string name;
    int age{};

    // std::cout sends text to the console. std::cin/std::getline read text from it.
    std::cout << "What is your name? ";
    std::getline(std::cin, name); // getline reads a full line, including spaces

    std::cout << "How old are you? ";
    std::cin >> age;

    greetPerson(name);
    std::cout << "You are " << age << " years old." << std::endl;

    return 0;
}
