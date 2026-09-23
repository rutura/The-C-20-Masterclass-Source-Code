#include <print>

// OVERLOADING: several functions can share one name as long as their
// PARAMETER LISTS differ - in number, type, or order. At each call the
// compiler examines the arguments and picks the matching version.
//
// It is for one idea carried out on different inputs. Here: "area of a
// shape", where the shape is implied by what you pass.

// area of a square, from its side
int area(int side);


// area of a circle, from its radius - different parameter TYPE
double area(double radius) {
	std::print("(circle) ");
	return 3.14159 * radius * radius;
}

// area of a rectangle - different parameter COUNT
int area(int width, int height) {
	std::print("(rectangle) ");
	return width * height;
}


void reset() {
	std::println("Reset with no parameter");
}

void reset(int param = 0) {
	std::println("Reset with a parameter: {}", param);
}


int main(){

	std::println("area(4)     = {}", area(4));       // one int   -> square
	std::println("area(2.5)   = {}", area(2.5));     // one double -> circle
	std::println("area(3, 6)  = {}", area(3, 6));    // two ints  -> rectangle
	reset(12);

}

/*
int area(int side) {
	std::print("(square) ");
	return side * side;
}
*/