module;
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module my_math_module;

//Module purview
export void say_something() {
	// std::cout << "Saying something..." << std::endl;
	fmt::println( "Saying something...");
}