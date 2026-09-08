#include <print>

// A parameter can have a default value. If the caller omits that
// argument, the default is used. Defaults go in the DECLARATION (the
// prototype), not the definition - and only trailing parameters can
// have them, so callers fill arguments left to right.

int box_volume(int length = 1, int width = 1, int height = 1);

int main() {

    std::println("box_volume()          = {}", box_volume());          // 1*1*1
    std::println("box_volume(10)        = {}", box_volume(10));         // 10*1*1
    std::println("box_volume(10, 5)     = {}", box_volume(10, 5));      // 10*5*1
    std::println("box_volume(10, 5, 2)  = {}", box_volume(10, 5, 2));   // 10*5*2

    // You cannot skip a middle argument: box_volume(10, , 2) is invalid.
    // If you need that flexibility, order parameters so the ones most
    // often defaulted come last.

    return 0;
}

// Note: the defaults are NOT repeated here - just in the declaration.
int box_volume(int length, int width, int height) {
    return length * width * height;
}
