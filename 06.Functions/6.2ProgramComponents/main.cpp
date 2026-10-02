#include <iostream>
#include <print>

// A C++ program is built from FUNCTIONS. Some you write yourself; many
// come ready-made in the C++ Standard Library (std::println, std::sqrt,
// std::sort, ...). Either way you USE a function by CALLING it: name,
// then arguments in parentheses.
//
// The point of writing your own is reuse: define a piece of work once,
// then call it wherever you need it instead of copying the code.

// A function definition: name, parameter list, return type, body.
int rectangle_perimeter(int width, int height);

// Every call has a small cost: the CPU sets up a stack frame, jumps into
// the function, and tears the frame down on return. For a tiny function
// called in a tight loop that cost can matter. `inline` gives the
// compiler permission to paste the body at the call site and skip the
// jump. (Its formal job is a linker rule - see NOTES.md - but this is
// the effect worth knowing here.)
inline int sum(int a, int b) {
    return a + b;
}

int main(){

    int p1 = rectangle_perimeter(100, 20);
    int p2 = rectangle_perimeter(300, 10);
    std::println("Perimeter for p1: {}", p1);
    std::println("Perimeter for p2: {}", p2);

    int total{ sum(3, 4) };
    std::println("Total: {}", total);
}

int rectangle_perimeter(int width, int height) {
    return  2 * (width + height) ;
}

