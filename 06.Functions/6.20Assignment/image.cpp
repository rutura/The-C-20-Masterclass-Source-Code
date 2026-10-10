#include "image.h"

#include <string>

#include "stb_image_write.h"   // declarations only - the bodies are
                               // compiled in stb_impl.cpp

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

void draw_background(std::vector<std::uint8_t>& pixels, int width, int height,
                     std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    for (int y{0}; y < height; ++y) {
        for (int x{0}; x < width; ++x) {
            set_pixel(pixels, width, height, x, y, r, g, b);
        }
    }
}

void draw_rectangle(std::vector<std::uint8_t>& pixels, int width, int height,
                    int x, int y, int rect_width, int rect_height,
                    int thickness,
                    std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    for (int row{0}; row < rect_height; ++row) {
        for (int col{0}; col < rect_width; ++col) {
            // Same "on the outline band" test as draw_border, just measured
            // from the rectangle's own edges instead of the canvas's.
            const bool on_edge{col < thickness || col >= rect_width - thickness ||
                               row < thickness || row >= rect_height - thickness};
            if (on_edge) {
                set_pixel(pixels, width, height, x + col, y + row, r, g, b);
            }
        }
    }
}

bool write_png(std::string_view filename, int width, int height,
               const std::vector<std::uint8_t>& pixels) {
    // stbi_write_png(path, w, h, channels, data, stride_in_bytes)
    // channels = 3 (RGB); stride = one row = width * 3 bytes.
    // It returns non-zero on success.
    const int ok{stbi_write_png(std::string{filename}.c_str(),
                                width, height, 3,
                                pixels.data(), width * 3)};
    return ok != 0;
}
