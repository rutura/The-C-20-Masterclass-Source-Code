/*
    exploring the concept of friendship
*/
module;

#include <cstdint>
#include <fmt/format.h>

export module ct17;

namespace ct17{

    export class Pixel {

        // Declare Canvas and print_pixel as friends
        friend class Canvas;
        friend void print_pixel(const Pixel& p);
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


    private:
        uint32_t m_color{0xFF000000};
        unsigned int m_pos_x{0};
        unsigned int m_pos_y{0};
    };

    // Class Canvas is a friend of Pixel and can modify its private members
    export class Canvas {
    public:
        void modify_pixel(Pixel& p, uint32_t new_color, unsigned int new_x, unsigned int new_y) {
            // Directly accessing private members of Pixel
            p.m_color = new_color;
            p.m_pos_x = new_x;
            p.m_pos_y = new_y;
        }

        void display_pixel(const Pixel& p) const {
            fmt::print("Canvas displaying Pixel: color = 0x{:08X}, x = {}, y = {}\n",
                       p.m_color, p.m_pos_x, p.m_pos_y);
        }
    };

    // Friend function print_pixel that can access private members of Pixel
    export void print_pixel(const Pixel& p) {
        fmt::print("Pixel: color = 0x{:08X}, x = {}, y = {}\n", p.m_color, p.m_pos_x, p.m_pos_y);
    }
    
} // namespace ct17
