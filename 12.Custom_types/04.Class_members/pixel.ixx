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
    inline uint32_t get_color() const { return m_color; }

    void set_position(Position position);
    inline Position get_position() const{ return m_position; }

private:
    uint32_t m_color{0xFFFFFF}; // Default to white color in hex
    Position m_position;
};

