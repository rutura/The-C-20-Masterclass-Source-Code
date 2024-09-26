module;

#include <cstdint>
#include <fmt/format.h>

module ct4;

namespace ct4{

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
    
} // namespace ct4

