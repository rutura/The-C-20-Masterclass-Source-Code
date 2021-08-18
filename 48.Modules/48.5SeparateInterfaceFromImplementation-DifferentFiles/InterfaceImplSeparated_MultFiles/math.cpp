module;
#include <cstring> // C function includes must show up here
module math_stuff;

//Preamble

//Implementations
double add(double a, double b) {
	return a + b;
}

void greet(const std::string& name) {
	std::string dest;
	dest = "Hello ";
	dest.append(name);
	std::cout << dest << std::endl;
}

void print_name_length(const char* c_str_name) {
	std::cout << "Length : " << std::strlen(c_str_name) << std::endl;
}

//Point constructor
Point::Point(double x, double y) : m_x(x), m_y(y) {};

