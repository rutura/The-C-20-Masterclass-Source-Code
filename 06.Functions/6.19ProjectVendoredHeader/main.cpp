#include <print>

#include "image.h"

// PROJECT (version B): the same image, but the file is written by a
// real third-party library - stb_image_write - VENDORED into this
// project (the header sits in vendor/, committed alongside our code).
//
// Nothing is downloaded. The header is compiled from source with our
// own toolchain, so there is no prebuilt binary and no ABI mismatch.
// Our own code is unchanged from version A except that write_png()
// now calls stbi_write_png() instead of hand-writing a PPM.

int main() {

    const int width{400};
    const int height{300};

    auto pixels = make_canvas(width, height);

    draw_gradient(pixels, width, height,
                  20, 30, 90,
                  240, 140, 40);

    draw_border(pixels, width, height, 8, 255, 255, 255);

    if (write_png("image.png", width, height, pixels)) {
        std::println("wrote image.png ({} x {}) via stb_image_write", width, height);
    }
    else {
        std::println("could not write image.png");
        return 1;
    }

    return 0;
}
