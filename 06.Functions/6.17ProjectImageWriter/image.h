#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

// A picture is just a row-by-row list of pixels, each pixel three bytes:
// red, green, blue. We keep them in one flat vector, 3 bytes per pixel,
// width*height pixels.
//
//   index of pixel (x, y) in the vector = (y * width + x) * 3
//                                          └── the byte offset of its red

// Make a black canvas: width*height pixels, all bytes 0.
std::vector<std::uint8_t> make_canvas(int width, int height);

// Set one pixel. Out-of-range (x, y) is ignored so callers need not
// bounds-check every time.
void set_pixel(std::vector<std::uint8_t>& pixels, int width, int height,
               int x, int y,
               std::uint8_t r, std::uint8_t g, std::uint8_t b);

// Fill the whole canvas with a left-to-right gradient: colour `left` at
// x = 0 blending to `right` at x = width - 1.
void draw_gradient(std::vector<std::uint8_t>& pixels, int width, int height,
                   std::uint8_t left_r,  std::uint8_t left_g,  std::uint8_t left_b,
                   std::uint8_t right_r, std::uint8_t right_g, std::uint8_t right_b);

// Draw a solid frame `thickness` pixels wide around the edge.
void draw_border(std::vector<std::uint8_t>& pixels, int width, int height,
                 int thickness,
                 std::uint8_t r, std::uint8_t g, std::uint8_t b);

// Write the pixels to a binary PPM (.ppm) file. PPM is the simplest
// image format there is - a short text header, then the raw RGB bytes.
// Returns true on success.
bool write_ppm(std::string_view filename, int width, int height,
               const std::vector<std::uint8_t>& pixels);
