#include <iostream>
#include <print>

int main(){

	const std::string name{ "Daniel" };

	//Print this name 10 times
	/*
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	std::println("Your name is {}", name);
	*/

	/*
	int condition{ 0 };

	while (condition < 10) {
		std::println("[{}]: Your name is {}", condition, name);
		condition++;
	}
	*/


	// --- Looping with while ---
	// A while loop repeats a block of code while a condition is true.

	/*
	int loop_count{ 0 };
	while (loop_count < 5) {
		std::println("loop_count: {}", loop_count);
		++loop_count;           // increment the counter so the loop ends
	}
	*/

	// --- Counter-controlled iteration: you know the count up front ---
	// Read exactly 5 scores and total them.
	/*
	int total{ 0 };
	int entered{ 0 };

	while (entered < 5) {
		std::print("Enter score {} of 5: ", entered + 1);
		int score{};
		std::cin >> score;

		total += score;
		++entered;
	}
	++score;

	const int average{ total / 5 };
	std::println("Total: {}, average: {}", total, average);
	*/


	// --- Sentinel-controlled iteration: loop until a marker value ---
	// The user types -1 when done, so the count isn't known in advance.
	std::println("\nNow enter any number of scores, -1 to stop.");

	int sentinel_total{ 0 };
	int count{ 0 };

	std::print("Score (-1 to stop): ");
	int score{};
	std::cin >> score;

	while (score != -1) {
		sentinel_total += score;
		++count;

		std::print("Score (-1 to stop): ");
		std::cin >> score;      // read the next one before re-testing
	}

	// Guard against dividing by zero when no real scores were entered.
	if (count != 0) {
		double real_average{ static_cast<double>(sentinel_total) / count };
		std::println("Entered {} scores, average {:.2f}", count, real_average);
	}
	else {
		std::println("No scores entered.");
	}

}