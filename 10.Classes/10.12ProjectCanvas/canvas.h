#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

#include "color.h"

// A Canvas owns a picture: width x height pixels, three bytes each.
//
// In chapter 6 the picture was a bare std::vector passed around next to its
// width and height, and every function had to be handed all three and trust
// that they agreed. Here the three live together inside one class, and the
// class keeps one promise (its INVARIANT):
//
//     pixels_.size() == width_ * height_ * 3, and width_, height_ >= 0
//
// Every member function may rely on it, and every member function must leave it
// true. Because the data is private, no outside code can break it.
class Canvas {
public:
    // A canvas of the given size, every pixel set to `background` (black by
    // default). A negative size is treated as zero.
    Canvas(int width, int height, Color background = {});

    // Copying a canvas copies the pixels: the two pictures are then
    // independent. The vector member knows how, so the compiler-written
    // versions are exactly right, and "= default" says so.
    Canvas(const Canvas&) = default;
    Canvas& operator=(const Canvas&) = default;
    ~Canvas() = default;

    // Moving needs real code. A compiler-written move would move the vector
    // and leave width_ and height_ unchanged, so the moved-from canvas would
    // claim to be 400 x 300 with no pixels at all, breaking the invariant. Our
    // versions leave it an empty 0 x 0 canvas instead.
    Canvas(Canvas&& other) noexcept;
    Canvas& operator=(Canvas&& other) noexcept;

    int width() const { return width_; }
    int height() const { return height_; }
    bool empty() const { return width_ == 0 || height_ == 0; }

    bool contains(int x, int y) const;

    // Out-of-range coordinates are ignored by set_pixel, and read as black by
    // pixel(), so callers never have to bounds-check.
    void set_pixel(int x, int y, Color color);
    Color pixel(int x, int y) const;

    void fill(Color color);
    void fill_rect(int x, int y, int width, int height, Color color);

    // Left-to-right gradient: `left` at x = 0 blending to `right` at the last column.
    void draw_gradient(Color left, Color right);

    // A solid frame `thickness` pixels wide around the edge.
    void draw_border(int thickness, Color color);

    // Both return true on success. An empty canvas cannot be written.
    bool write_ppm(std::string_view filename) const;
    bool write_png(std::string_view filename) const;

private:
    // The byte offset of the red channel of pixel (x, y) (6.17).
    std::size_t offset(int x, int y) const;

    int width_;
    int height_;
    std::vector<std::uint8_t> pixels_;
};
