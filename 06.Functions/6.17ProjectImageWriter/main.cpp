#include <print>
#include "image.h"

int main(){
    const int width{ 400 };
    const int height{ 300 };

    auto pixels = make_canvas(width, height);


    // Deep blue on the left, warm orange on the right.
    draw_gradient(pixels, width, height,
        191, 69, 142, // left colour
        55, 74, 107);  // right color

    // 142, 191, 69

    draw_border(pixels, width, height, 28, 142, 191, 69);   // white frame


    if (write_ppm("image.ppm", width, height, pixels)) {
        std::println("wrote image.ppm ({} x {})", width, height);
    }
    else {
        std::println("could not write image.ppm");
        return 1;
    }
    return 0;
}