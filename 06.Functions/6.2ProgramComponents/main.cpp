#include <print>

// A C++ program is built from FUNCTIONS. Some you write yourself; many
// come ready-made in the C++ Standard Library (std::println, std::sqrt,
// std::sort, ...). Either way you USE a function by CALLING it: name,
// then arguments in parentheses.
//
// The point of writing your own is reuse: define a piece of work once,
// then call it wherever you need it instead of copying the code.

// A function definition: name, parameter list, return type, body.
double average_of_three(double a, double b, double c) {
    return (a + b + c) / 3.0;
}

int main() {

    // Call our own function three times with different data - the logic
    // lives in one place.
    std::println("avg(2, 4, 9)     = {}", average_of_three(2, 4, 9));
    std::println("avg(10, 10, 10)  = {}", average_of_three(10, 10, 10));
    std::println("avg(1.5, 2.5, 8) = {}", average_of_three(1.5, 2.5, 8));

    // std::println itself is a library function we have been calling
    // since chapter 3. Calling library functions works exactly the same
    // way as calling our own.

    return 0;
}
