#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

// Same pixel model as version A: one flat vector, 3 bytes (R, G, B) per
// pixel, laid out row by row.
//
//   index of pixel (x, y) = (y * width + x) * 3

std::vector<std::uint8_t> make_canvas(int width, int height);

void set_pixel(std::vector<std::uint8_t>& pixels, int width, int height,
               int x, int y,
               std::uint8_t r, std::uint8_t g, std::uint8_t b);

void draw_gradient(std::vector<std::uint8_t>& pixels, int width, int height,
                   std::uint8_t left_r,  std::uint8_t left_g,  std::uint8_t left_b,
                   std::uint8_t right_r, std::uint8_t right_g, std::uint8_t right_b);

void draw_border(std::vector<std::uint8_t>& pixels, int width, int height,
                 int thickness,
                 std::uint8_t r, std::uint8_t g, std::uint8_t b);

// The only difference from version A: instead of hand-writing a PPM, we
// hand the buffer to the vendored stb_image_write library and get a
// real PNG. Returns true on success.
bool write_png(std::string_view filename, int width, int height,
               const std::vector<std::uint8_t>& pixels);
