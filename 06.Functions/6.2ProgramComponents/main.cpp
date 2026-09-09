#include <print>

// A C++ program is built from FUNCTIONS. Some you write yourself; many
// come ready-made in the C++ Standard Library (std::println, std::sqrt,
// std::sort, ...). Either way you USE a function by CALLING it: name,
// then arguments in parentheses.
//
// The point of writing your own is reuse: define a piece of work once,
// then call it wherever you need it instead of copying the code.

// A function definition: name, parameter list, return type, body.
int rectangle_perimeter(int width, int height) {
    return 2 * (width + height);
}

int main() {

    // Call our own function for several rectangles - the formula lives
    // in one place, not copied three times.
    std::println("perimeter of  3 x  4 = {}", rectangle_perimeter(3, 4));
    std::println("perimeter of 10 x 10 = {}", rectangle_perimeter(10, 10));
    std::println("perimeter of  7 x  2 = {}", rectangle_perimeter(7, 2));

    return 0;
}
