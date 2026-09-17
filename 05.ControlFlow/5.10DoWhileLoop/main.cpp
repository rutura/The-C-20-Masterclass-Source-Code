#include <iostream>
#include <print>

int main(){

	/*
	const std::string name{ "Daniel" };
	int iter{};

	while (iter < 10) {
		std::println("[{}]: name is {}", iter, name);
		++iter;
	}
	*/

	//do while version
	/*
	iter = 0;

	do {
		std::println("[{}]: name is {}", iter, name);
		++iter;
	} while (iter < 10);
	*/


	// --- Prompt: ask at least once, repeat until the guess is valid ---
	int guess{};

	do {

		std::print("Guess the die roll (1-6): ");
		std::cin >> guess;

		if (guess < 1 || guess > 6) {
			std::println("  A die only shows 1-6, try again.");
		}

	} while (guess < 1 || guess > 6);

	std::println("You guessed: {}", guess);

}