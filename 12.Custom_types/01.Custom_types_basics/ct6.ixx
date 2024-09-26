/*
    . Constructor initializer lists allow us to provide initial values for data members
        as they are created.
    . This is more efficient than assigning values in the constructor body.
    . Advice: 
        . Use constructor initializer lists whenever possible.
    . Keep in mind: 
        . The order of the data members in the initializer list must 
            match the order of the data members in the class definition.
        . The compiler initializes the data members in the order they are 
            declared in the class, not the order they are listed in the initializer list.
        . If the order of the data members in the initializer list 
            doesn't match the order of the data members in the class definition,
            sometimes the compiler will issue a warning.
    . There are cases when it is mandatory to use ctor initializer lists:
        . When the data members are const.
        . When the data members are references.
        . When the data members are objects of a class that doesn't have a default constructor.
    
*/
module;

#include <cstdint>
#include <fmt/format.h>

export module ct6;

namespace ct6{

    export class Pixel {
        public: 
            Pixel();
            //Pixel(uint32_t color, unsigned int x, unsigned int y);
            Pixel(uint32_t color, unsigned int x, unsigned int y)
                : m_color{color}, 
                m_pos_x{x}, 
                m_pos_y{y} 
            {
                fmt::print("Pixel created\n");
            }
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

    // Implementations
    Pixel::Pixel() {    //No need to ctor initializer list here. The in-class initializers are used.
        fmt::print("Pixel created\n");
    }

    /*
    Pixel::Pixel(uint32_t color, unsigned int x, unsigned int y) : 
        m_color{color}, 
        m_pos_x{x}, 
        m_pos_y{y} {
        fmt::print("Pixel created\n");
    }
    */

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

} // namespace ct6