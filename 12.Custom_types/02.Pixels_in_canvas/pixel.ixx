module;

#include <cstdint>

export module pixel;

export struct Position {
    unsigned int x{0};
    unsigned int y{0};
};

export class Pixel {
public:
    Pixel() = default;
    Pixel(uint32_t initial_color, Position initial_position);

    void set_color(uint32_t color);
    uint32_t get_color() const;

    void set_position(Position position);
    Position get_position() const;

private:
    uint32_t m_color{0xFFFFFF}; // Default to white color in hex
    Position m_position{0, 0}; // Default initialized anyway.
};

