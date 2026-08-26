#include <iostream>
#include <print>
#include <string>

int main(){
	// Ask information from the user
	std::println("Please type in your full name and age:");

	std::string full_name;
	std::getline(std::cin, full_name);

	int age{};
	std::cin >> age;

	std::println("Hello {}, you are {} years old!", full_name, age);
	std::cout << "Hello " << full_name << ", you are " << age << " years old!\n";

	return 0;
}