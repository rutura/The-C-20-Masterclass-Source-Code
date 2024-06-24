module;
#include <string_view>
#include <cstdlib>
#include <cstring>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void process_arguments(int argc,  char* argv[]) {
	fmt::println("We have {} parameters in our program", argc);
	for (size_t i{ 0 }; i < argc; ++i) {
		fmt::println("parameter [{}]: {}", i, argv[i]);
	}
}

export void calculator(int argc, char* argv[]){
	// Check the number of parameters
	if (argc != 4) {
		fmt::println("Program can only be called with 3 arguments like: ");
		fmt::println("rooster a + b");
		fmt::println("You called with : ");
		for (int i{ 0 }; i < argc; ++i) { fmt::print(" {}", argv[i]); }
		return;
	}

	// Grab the operands
	double first_number{ atof(argv[1]) };
	double second_number{ atof(argv[3]) };

	if ((first_number == 0.0) || (second_number == 0.0)) {
		fmt::println("Please use valid numbers ( different from zero) for first and second parameters)");
		return;
	}

	// Grab the operation
	const char *operation{ argv[2] };
	char c;

	if ((std::strlen(operation) == 1)
		&& ((operation[0] == '+') || (operation[0] == '-') || (operation[0] == 'x')
			||// x is for multiplication. * is interpreted
			// by the shell and disturbing things.
			(operation[0] == '/'))) {
		c = operation[0];
	} else {
		fmt::println("{} is not a valid operation.", operation);
		return;
	}

	// Do the operation
	switch (c) {
	case '+':
		fmt::println("{} + {} = {}", first_number, second_number, first_number + second_number);
		break;

	case '-':
		fmt::println("{} - {} = {}", first_number, second_number, first_number - second_number);
		break;

	case 'x':
		fmt::println("{} x {} = {}", first_number, second_number, first_number * second_number);

		break;

	case '/':
		fmt::println("{} / {} = {}", first_number, second_number, first_number / second_number);

		break;
	}
}