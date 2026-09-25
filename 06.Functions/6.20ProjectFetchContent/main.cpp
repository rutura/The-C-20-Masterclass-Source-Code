#include <print>

#include "image.h"

// PROJECT (version C): the same image again, but stb is not committed
// here. Instead CMake fetches it FROM SOURCE at configure time
// (FetchContent) and drops it into the build tree. It is still compiled
// with our toolchain - nothing prebuilt, nothing to link - but now the
// dependency is declared in CMakeLists.txt and pinned to an exact
// commit, the way real projects pull in libraries.
//
// image.h / image.cpp / stb_impl.cpp are identical to version B. The
// only change is in CMakeLists.txt.

int main() {

    const int width{400};
    const int height{300};

    auto pixels = make_canvas(width, height);

    draw_gradient(pixels, width, height,
                  20, 30, 90,
                  240, 140, 40);

    draw_border(pixels, width, height, 8, 255, 255, 255);

    if (write_png("image.png", width, height, pixels)) {
        std::println("wrote image.png ({} x {}) - stb fetched by CMake", width, height);
    }
    else {
        std::println("could not write image.png");
        return 1;
    }

    return 0;
}
