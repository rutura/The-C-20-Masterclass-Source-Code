#include <iostream> // old
// #include <print>
#include <string>

int main() {

	//The old way
	std::cout << "The sky is blue\n";
	std::cout << "The water is not blue\n";


	//The new way
        /*
	std::println("Hello, C++");
	std::println("The water is not blue");
        */

	// Greet someone
	std::string name{ "Ada" };
	int age{ 28 };

	std::cout << name << " is " << age << " years old.\n";
        // std::println("{} is {} years old.", name, age);

	// Compiler error
	// std::printline("The sky blue");

	// Run time error
	//int total{ 7 / 0 };

}
