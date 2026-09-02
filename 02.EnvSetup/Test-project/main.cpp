#include <iostream>
#include <print>

int main() {

    // Print data the classic way
    std::cout << "Hello, C++!\n";
    std::cout << "This is the classic way to print output.\n";

    // Print data the modern way
    std::println("Hello, C++!");
    std::println("This is the modern way to print output.");

    // Get some data into your program
    std::string name{"Ada"};
    int age{28};

    //Print the data out
    std::cout << name << " is " << age << " years old.\n";
    std::println("{} is {} years old.", name, age);

    return 0;
}
