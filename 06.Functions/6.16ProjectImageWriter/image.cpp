#include "image.h"

#include <fstream>

std::vector<std::uint8_t> make_canvas(int width, int height) {
    return std::vector<std::uint8_t>(static_cast<std::size_t>(width) * height * 3, 0);
}

void set_pixel(std::vector<std::uint8_t>& pixels, int width, int height,
               int x, int y,
               std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    const std::size_t i{(static_cast<std::size_t>(y) * width + x) * 3};
    pixels[i + 0] = r;
    pixels[i + 1] = g;
    pixels[i + 2] = b;
}

void draw_gradient(std::vector<std::uint8_t>& pixels, int width, int height,
                   std::uint8_t left_r,  std::uint8_t left_g,  std::uint8_t left_b,
                   std::uint8_t right_r, std::uint8_t right_g, std::uint8_t right_b) {
    for (int x{0}; x < width; ++x) {
        // t goes 0.0 at the left edge to 1.0 at the right edge.
        const double t{width > 1 ? static_cast<double>(x) / (width - 1) : 0.0};
        const auto mix = [t](std::uint8_t a, std::uint8_t c) {
            return static_cast<std::uint8_t>(a + t * (c - a));
        };
        const std::uint8_t r{mix(left_r, right_r)};
        const std::uint8_t g{mix(left_g, right_g)};
        const std::uint8_t b{mix(left_b, right_b)};
        for (int y{0}; y < height; ++y) {
            set_pixel(pixels, width, height, x, y, r, g, b);
        }
    }
}

void draw_border(std::vector<std::uint8_t>& pixels, int width, int height,
                 int thickness,
                 std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    for (int y{0}; y < height; ++y) {
        for (int x{0}; x < width; ++x) {
            const bool on_edge{x < thickness || x >= width - thickness ||
                               y < thickness || y >= height - thickness};
            if (on_edge) {
                set_pixel(pixels, width, height, x, y, r, g, b);
            }
        }
    }
}

bool write_ppm(std::string_view filename, int width, int height,
               const std::vector<std::uint8_t>& pixels) {
    std::ofstream out{std::string{filename}, std::ios::binary};
    if (!out) {
        return false;
    }
    // Header: "P6\n<width> <height>\n255\n", then width*height*3 raw bytes.
    out << "P6\n" << width << ' ' << height << "\n255\n";
    out.write(reinterpret_cast<const char*>(pixels.data()),
              static_cast<std::streamsize>(pixels.size()));
    return out.good();
}
