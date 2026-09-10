#include <print>

#include "image.h"

// PROJECT (version A): write an image with NO third-party library at all.
//
// The whole program is functions from this chapter: a header/source
// split (6.10), plain functions taking scalars and a std::vector by
// reference (6.8), a lambda inside draw_gradient (6.13). The output
// format, PPM, is simple enough to write by hand.

int main() {

    const int width{400};
    const int height{300};

    auto pixels = make_canvas(width, height);

    // Deep blue on the left, warm orange on the right.
    draw_gradient(pixels, width, height,
                  20, 30, 90,       // left  colour
                  240, 140, 40);    // right colour

    draw_border(pixels, width, height, 8, 255, 255, 255);   // white frame

    if (write_ppm("image.ppm", width, height, pixels)) {
        std::println("wrote image.ppm ({} x {})", width, height);
        std::println("open it with an image viewer, or convert: "
                     "magick image.ppm image.png");
    }
    else {
        std::println("could not write image.ppm");
        return 1;
    }

    return 0;
}
