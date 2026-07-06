#include <iostream>
#include <string>

// A function: a named, reusable block of statements.
// This one takes a name and prints a greeting for it.
void greetPerson(std::string name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {

    // Each of these lines is a "statement" - a single instruction for the computer.
    greetPerson("Ada");
    greetPerson("Grace");
    greetPerson("Alan");

    // --- Compile time errors ---
    // If you misspell a name the compiler knows about, the program won't even build.
    // Try it yourself: uncomment the line below and build the project.
    // greetPerson("Ada");   ->   greetPersonn("Ada");   // compiler error: no such function

    // --- Runtime errors ---
    // Some mistakes only show up while the program is running.
    // Dividing by zero is a classic example - it compiles fine, but crashes at runtime.
    // int numerator = 7;
    // int denominator = 0;
    // int trouble = numerator / denominator; // don't uncomment this, it will crash when run

    return 0;
}
