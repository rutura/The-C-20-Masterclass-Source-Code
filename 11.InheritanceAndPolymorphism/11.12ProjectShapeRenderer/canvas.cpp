#include "canvas.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <utility>

// Only the declarations of stb's functions are needed here. Their bodies are
// compiled once, in stb_impl.cpp (6.18).
#include "stb_image_write.h"

Canvas::Canvas(int width, int height, Color background)
    : width_{std::max(width, 0)},
      height_{std::max(height, 0)},
      pixels_(static_cast<std::size_t>(width_) * static_cast<std::size_t>(height_) * 3) {
    // Parentheses, on purpose: they ask for a vector of that SIZE (7.4). Braces
    // would build a vector holding the one number. It starts full of zeros;
    // now paint it.
    fill(background);
}

Canvas::Canvas(Canvas&& other) noexcept
    : width_{std::exchange(other.width_, 0)},
      height_{std::exchange(other.height_, 0)},
      pixels_{std::exchange(other.pixels_, {})} {}

Canvas& Canvas::operator=(Canvas&& other) noexcept {
    if (this != &other) {
        width_ = std::exchange(other.width_, 0);
        height_ = std::exchange(other.height_, 0);
        pixels_ = std::exchange(other.pixels_, {});
    }
    return *this;
}

bool Canvas::contains(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

std::size_t Canvas::offset(int x, int y) const {
    return (static_cast<std::size_t>(y) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(x)) * 3;
}

void Canvas::set_pixel(int x, int y, Color color) {
    if (!contains(x, y)) {
        return;
    }
    const std::size_t i{offset(x, y)};
    pixels_[i + 0] = color.r;
    pixels_[i + 1] = color.g;
    pixels_[i + 2] = color.b;
}

Color Canvas::pixel(int x, int y) const {
    if (!contains(x, y)) {
        return Color{};
    }
    const std::size_t i{offset(x, y)};
    return Color{pixels_[i + 0], pixels_[i + 1], pixels_[i + 2]};
}

void Canvas::fill(Color color) {
    for (int y{0}; y < height_; ++y) {
        for (int x{0}; x < width_; ++x) {
            set_pixel(x, y, color);
        }
    }
}

void Canvas::fill_rect(int x, int y, int width, int height, Color color) {
    for (int row{y}; row < y + height; ++row) {
        for (int column{x}; column < x + width; ++column) {
            set_pixel(column, row, color);        // set_pixel clips anything outside
        }
    }
}

void Canvas::draw_gradient(Color left, Color right) {
    for (int x{0}; x < width_; ++x) {
        // t goes 0.0 at the left edge to 1.0 at the right edge.
        const double t{width_ > 1 ? static_cast<double>(x) / (width_ - 1) : 0.0};
        const auto mix = [t](std::uint8_t a, std::uint8_t c) {
            return static_cast<std::uint8_t>(a + t * (c - a));
        };
        const Color blended{mix(left.r, right.r), mix(left.g, right.g), mix(left.b, right.b)};
        for (int y{0}; y < height_; ++y) {
            set_pixel(x, y, blended);
        }
    }
}

void Canvas::draw_border(int thickness, Color color) {
    for (int y{0}; y < height_; ++y) {
        for (int x{0}; x < width_; ++x) {
            const bool on_edge{x < thickness || x >= width_ - thickness ||
                               y < thickness || y >= height_ - thickness};
            if (on_edge) {
                set_pixel(x, y, color);
            }
        }
    }
}

bool Canvas::write_ppm(std::string_view filename) const {
    if (empty()) {
        return false;
    }
    std::ofstream out{std::string{filename}, std::ios::binary};
    if (!out) {
        return false;
    }
    // Header: "P6\n<width> <height>\n255\n", then width*height*3 raw bytes.
    out << "P6\n" << width_ << ' ' << height_ << "\n255\n";
    out.write(reinterpret_cast<const char*>(pixels_.data()),
              static_cast<std::streamsize>(pixels_.size()));
    return out.good();
}

bool Canvas::write_png(std::string_view filename) const {
    if (empty()) {
        return false;
    }
    // stb wants a C string, and the number of bytes in one row of pixels.
    const std::string path{filename};
    return stbi_write_png(path.c_str(), width_, height_, 3, pixels_.data(), width_ * 3) != 0;
}
