module;

#include <stdexcept>
#include <fmt/format.h>

module pixel;
Pixel::Pixel(uint32_t initial_color, Position initial_position)
    : m_color(initial_color), m_position(initial_position) {}


void Pixel::set_color(uint32_t color) {
    if (color > 0xFFFFFF) {
        throw std::out_of_range("Invalid color value. Must be a 24-bit hex value.");
    }
    m_color = color;
}

uint32_t Pixel::get_color() const {
    return m_color;
}

void Pixel::set_position(Position pos) {
    m_position = pos;
}

Position Pixel::get_position() const {
    return m_position;
}
