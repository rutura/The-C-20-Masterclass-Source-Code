/*
    . Exploring the use of the explicit keyword to prevent implicit conversions from constructors.
    . We don't want the compiler to convert a uint32_t to a Pixel object.
    . You can do that : 
        . using the explicit keyword as shown below
            . explicit(true) Pixel(uint32_t color) : Pixel(color, 0, 0) {};
            . explicit Pixel(uint32_t color) : Pixel(color, 0, 0) {};
    . explicit(true) is the same as explicit
    . You can explicitly allow implicit conversions by using the explicit(false) keyword.
*/
module;

#include <cstdint>
#include <fmt/format.h>

export module ct11;

namespace ct11 {

    export class Pixel {
    public:
        // Default constructor
        Pixel() = default;

        // Constructor with color only, explicit to prevent implicit conversions
        explicit(true) Pixel(uint32_t color) : Pixel(color, 0, 0) {
            fmt::print("Body of the one param constructor\n");
        }

        // Constructor with all arguments
        Pixel(uint32_t color, unsigned int x, unsigned int y)
            : m_color{color}, m_pos_x{x}, m_pos_y{y} {
            fmt::print("Three-argument constructor\n");
        }

        // Copy constructor
        Pixel(const Pixel& other)
            : Pixel(other.m_color, other.m_pos_x, other.m_pos_y) {
            fmt::print("Body of the copy constructor\n");
        }

        ~Pixel() {
            fmt::print("Pixel destroyed\n");
        }

        uint32_t get_color() const { return m_color; }
        void set_color(uint32_t color) { m_color = color; }

        unsigned int get_x() const { return m_pos_x; }
        void set_x(unsigned int x) { m_pos_x = x; }

        unsigned int get_y() const { return m_pos_y; }
        void set_y(unsigned int y) { m_pos_y = y; }

    private:
        uint32_t m_color{0xFF000000};
        unsigned int m_pos_x{0};
        unsigned int m_pos_y{0};
    };

    // Function that takes a Pixel object
    export void print_pixel(const Pixel& p) {
        fmt::print("Pixel: color = 0x{:08X}, x = {}, y = {}\n", p.get_color(), p.get_x(), p.get_y());
    }

} // namespace ct11
