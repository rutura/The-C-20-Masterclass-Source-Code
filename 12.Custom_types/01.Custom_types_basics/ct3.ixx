/*
    . Separating declarations from definitions in the same file.
*/
module;

#include <cstdint>
#include <fmt/format.h>

export module ct3;

namespace ct3{

    //Only put in the declarations in the Pixel class
    export class Pixel {
        public: 
            Pixel();
            Pixel(uint32_t color, unsigned int x, unsigned int y);
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

    //The definitions
    Pixel::Pixel(){
        fmt::print("Pixel created\n");
    }

    Pixel::Pixel(uint32_t color, unsigned int x, unsigned int y){
        m_color = color;
        m_pos_x = x;
        m_pos_y = y;
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
    
} // namespace ct3