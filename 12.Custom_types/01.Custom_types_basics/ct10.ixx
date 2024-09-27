/*
    . Exploring constructor delegation
        . Delegated constructors are put in the constructor initializer list.
        . They should be the only member initializer in the list.
            . a member can't be both initialized by a delegated constructor
                 and have an initializer in the member initializer list.
            . Variables not initialized by a delegated constructor, can't be added to the initializer list too.
        . The one parameter constructor delegates to the three parameter constructor.
        . The copy constructor delegates to the three parameter constructor.
        . This approach keeps your code DRY (Don't Repeat Yourself) and makes it easier to maintain.
*/
module;

#include <cstdint>
#include <fmt/format.h>

export module ct10;

namespace ct10{

    export class Pixel {
    public:
        // Default constructor
        Pixel() = default;

        // Constructor with color only, delegates to the three-argument constructor
        Pixel(uint32_t color) : Pixel(color, 0, 0) {
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
    
} // namespace ct10
