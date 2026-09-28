#include <print>
#include "image.h"

int main(){
    const int width{ 400 };
    const int height{ 300 };

    auto pixels = make_canvas(width, height);

    // Deep blue on the left, warm orange on the right.
    draw_gradient(pixels, width, height,
        20, 30, 90,       // left  colour
        255, 255, 255);    // right colour

    draw_border(pixels, width, height, 2, 255, 0, 0);   // white frame


    if (write_ppm("image.ppm", width, height, pixels)) {
        std::println("wrote image.ppm ({} x {})", width, height);
    }else {
        std::println("could not write image.ppm");
        return 1;
    }

    return 0;
}