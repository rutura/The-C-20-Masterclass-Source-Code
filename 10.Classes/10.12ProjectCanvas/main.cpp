#include <print>
#include <utility>

#include "canvas.h"

// PROJECT: the image program from chapter 6, rebuilt around a class.
//
// Chapter 6 had make_canvas(), set_pixel(), draw_gradient() ... as free
// functions that all took the same (pixels, width, height) triple. Now that
// triple is one object, Canvas, and the functions are its member functions.
// The same picture comes out, and the new things to watch are copying and
// moving a Canvas.

// A factory that returns a Canvas by value. The returned temporary is built
// straight into the caller's variable (10.8): no copy, no move.
Canvas make_banner(int width, int height) {
    Canvas banner{width, height, Color{.r = 255, .g = 255, .b = 255}};
    banner.fill_rect(10, 10, width - 20, height - 20, Color{.r = 20, .g = 30, .b = 90});
    return banner;
}

int main() {

    // The chapter 6 picture: a blue-to-orange gradient with a white frame.
    Canvas canvas{400, 300};
    canvas.draw_gradient(Color{.r = 20, .g = 30, .b = 90}, Color{.r = 240, .g = 140, .b = 40});
    canvas.draw_border(8, Color{.r = 255, .g = 255, .b = 255});

    if (canvas.write_ppm("image.ppm") && canvas.write_png("image.png")) {
        std::println("wrote image.ppm and image.png ({} x {})", canvas.width(), canvas.height());
    }
    else {
        std::println("could not write the image files");
        return 1;
    }

    // COPY: a Canvas can be duplicated, and the duplicate is independent.
    Canvas annotated{canvas};
    annotated.fill_rect(150, 100, 100, 100, Color{.r = 255, .g = 255, .b = 255});
    annotated.write_png("image_copy.png");

    const Color before{canvas.pixel(200, 150)};
    const Color after{annotated.pixel(200, 150)};
    std::println("\nthe centre pixel of the original is ({}, {}, {})", before.r, before.g, before.b);
    std::println("the centre pixel of the copy     is ({}, {}, {})", after.r, after.g, after.b);

    // MOVE: hand a canvas to a new owner without copying its pixels.
    Canvas banner{make_banner(200, 50)};
    Canvas new_owner{std::move(banner)};
    std::println("\nnew_owner is {} x {}", new_owner.width(), new_owner.height());
    std::println("banner, after the move, is {} x {} (empty: {})",
                 banner.width(), banner.height(), banner.empty());

    // The moved-from canvas is valid and safe to use. Writing to it does
    // nothing, because every pixel is out of range, and saving it reports
    // failure instead of writing a broken file.
    banner.set_pixel(5, 5, Color{.r = 255});
    std::println("saving the moved-from canvas: {}", banner.write_png("never_written.png"));

    // And pixels outside the picture are ignored or read as black, so the
    // drawing code never has to check bounds itself.
    canvas.set_pixel(-1, -1, Color{.r = 255});
    std::println("pixel(9999, 9999) reads as ({}, {}, {})",
                 canvas.pixel(9999, 9999).r, canvas.pixel(9999, 9999).g, canvas.pixel(9999, 9999).b);

    return 0;
}
