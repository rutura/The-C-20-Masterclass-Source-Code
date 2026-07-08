module;
//Global module fragment : #include , preprocessor directives
export module my_math_module;
//Module preamble: imports
import <iostream>;

//Module purview
export void say_something() {
	std::cout << "Saying something..." << std::endl;
}