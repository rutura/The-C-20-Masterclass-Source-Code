#include <print>

// A parameter can have a DEFAULT value, used when the caller omits that
// argument. Rules:
//   - defaults go in the PROTOTYPE (the declaration), written once
//   - only TRAILING parameters may have defaults
//   - callers fill arguments left to right; you cannot skip a middle one

int box_volume(int length = 1, int width = 1, int height = 1);   // defaults here

int main() {

    std::println("box_volume()         = {}", box_volume());         // 1 * 1 * 1
    std::println("box_volume(10)       = {}", box_volume(10));        // 10 * 1 * 1
    std::println("box_volume(10, 5)    = {}", box_volume(10, 5));     // 10 * 5 * 1
    std::println("box_volume(10, 5, 2) = {}", box_volume(10, 5, 2));  // 10 * 5 * 2

    return 0;
}

// The definition does NOT repeat the defaults.
int box_volume(int length, int width, int height) {
    return length * width * height;
}
