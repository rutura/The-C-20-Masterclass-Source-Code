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

// Every call has a small cost: the CPU sets up a stack frame, jumps into
// the function, and tears the frame down on return. For a tiny function
// called in a tight loop that cost can matter. `inline` gives the
// compiler permission to paste the body at the call site and skip the
// jump. (Its formal job is a linker rule - see NOTES.md - but this is
// the effect worth knowing here.)
inline double cube(double side) {
    return side * side * side;
}

int main() {

    // Call our own function for several rectangles - the formula lives
    // in one place, not copied three times.
    std::println("perimeter of  3 x  4 = {}", rectangle_perimeter(3, 4));
    std::println("perimeter of 10 x 10 = {}", rectangle_perimeter(10, 10));
    std::println("perimeter of  7 x  2 = {}", rectangle_perimeter(7, 2));

    std::println("volume of a cube, side 5 = {}", cube(5.0));

    return 0;
}
