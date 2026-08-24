#include <iostream>
#include <print>
#include <string>

int main() {

    // C++23 has no formatted-input equivalent to std::print yet, so
    // reading input still goes through std::cin/std::getline.
    std::println("Please type in your full name and age:");

    std::string full_name;
    std::getline(std::cin, full_name);

    int age{};
    std::cin >> age;

    std::println("Hello {}, you are {} years old!", full_name, age);

    return 0;
}
