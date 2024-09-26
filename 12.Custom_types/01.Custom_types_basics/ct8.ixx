/*
    . Exploring copy constructors
        . The compiler can generate one if you don't have one defined.
        . You can also default it, and it will do blind member wise copy.
        . We can set up our own copy constructor.
        . The next bit will show why copy constructors to do deep copies.
*/
module;

#include <cstdint>
#include <fmt/format.h>

export module ct8;

namespace ct8{

    export class Pixel {
         public: 
              Pixel() = default;
              Pixel(uint32_t color, unsigned int x, unsigned int y);
              //Set up a copy constructor
              //Pixel(const Pixel& other) = default;
              Pixel(const Pixel& other);
              ~Pixel();
    
              uint32_t get_color() const;
              void set_color(uint32_t color);
    
              unsigned int get_x() const;
              void set_x(unsigned int x);
    
              unsigned int get_y() const;
              void set_y(unsigned int y);
    
         private: 
              uint32_t m_color{0xFF000000};
              unsigned int m_pos_x{0};
              unsigned int m_pos_y{0};
    };

    Pixel::Pixel(uint32_t color, unsigned int x, unsigned int y)
        : m_color{color}, m_pos_x{x}, m_pos_y{y} {
    }

    //Copy constructor
    Pixel::Pixel(const Pixel& other)
        : m_color{other.m_color}, 
        m_pos_x{other.m_pos_x}, 
        m_pos_y{other.m_pos_y} 
    {
    }

    Pixel::~Pixel(){
        fmt::print("Pixel destroyed\n");
    }

    uint32_t Pixel::get_color() const {
        return m_color; 
    }

    void Pixel::set_color(uint32_t color) {
        m_color = color; 
    }

    unsigned int Pixel::get_x() const {
        return m_pos_x; 
    }

    void Pixel::set_x(unsigned int x) {
        m_pos_x = x; 
    }

    unsigned int Pixel::get_y() const {
        return m_pos_y; 
    }

    void Pixel::set_y(unsigned int y) {
        m_pos_y = y; 
    }

} // namespace ct8