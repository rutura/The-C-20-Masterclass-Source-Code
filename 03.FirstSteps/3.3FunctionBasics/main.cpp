#include <iostream>
#include <print>

int add_numbers(int first, int second) {
	int result = first + second;
	return result;
}

int main(){
		
	int first_number{ 13 };
	int second_number{ 7 };

	std::println("First number: {}", first_number);
	std::println("Second number: {}", second_number);

	std::cout << "First number: " << first_number << std::endl;
	std::cout << "Second number: " << second_number << std::endl;


	int sum{ first_number + second_number };
	std::println("Sum: {}", sum);
	std::cout << "Sum: " << sum << std::endl;


	sum = add_numbers(25, 7);
	std::println("Sum: {}", sum);
	std::cout << "Sum: " << sum << std::endl;

	// A function call can be used directly wherever a value is expected.
	std::println("Sum: {}", add_numbers(3, 42));
	std::cout << "Sum: " << add_numbers(3, 42) << std::endl;



}