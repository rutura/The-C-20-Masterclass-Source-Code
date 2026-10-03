#include <print>

// A variable is a slot in memory. Paste just the body into Compiler
// Explorer and watch three "mov"s appear - one per variable. NOTES.md
// walks through the exact addresses the compiler picks, measured from
// rbp, and why they are spaced 4 bytes apart.
int rectangle_area() {
    int width{4};
    int height{3};
    int area{width * height};
    return area;
}

int main() {
    std::println("rectangle_area() = {}", rectangle_area());
    return 0;
}

// Try it: change "int height{3};" to "int height{9};" and watch only
// the 3 in the assembly change to a 9 - nothing else about the shape
// moves, because the ADDRESSES width, height, and area live at did not
// change, only the number stored at one of them.
