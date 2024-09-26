/*
    . Introducting C++23 explicit object parameters.
        . Compiler support: 
            . Visual C++: Nope
            . Clang: Yes
            . GCC: May be. Haven't checked.

    . Facts: 
        . The first parameter of the set_color is the explicit object parameter.
        . It is named self, but we can use any name. We're trying to make it look like Python.
        . The explicit object parameter must be the first parameter.
        . Once you use an explicit object parameter, you can't use the this pointer. It's taken out by the compiler.
        . In the body of the set_color function, we can't use this->m_color. We have to use self.m_color.
        . Calling a function that uses explicit object parameters is the same as calling a normal function.

    . Benefits:
        . What we have now seems to add no apparent value, but explicit object parameters allow us to do a few useful things: 
            . Setting up recursive lambdas.
                . Example shown in the ct5_demo function.
            . Making it much clear to write ref-qualified member functions. (more on this later)
            . Making it easier to write generic code. (Out of scope for this course)
*/
module;

#include <cstdint>
#include <fmt/format.h>

export module ct5;

namespace ct5{
    export class Pixel {

        public: 
            Pixel(){

            } 
            Pixel(uint32_t color, unsigned int x, unsigned int y){
                m_color = color;
                m_pos_x = x;
                m_pos_y = y;
            }
            ~Pixel(){
                fmt::print("Pixel destroyed\n");
            }

            uint32_t get_color() const {
                return m_color; 
            }

            //void set_color(this Pixel& self, uint32_t color) {
            void set_color(uint32_t color) {
                m_color = color; 
                //this->m_color = color;
                //self.m_color = color;
            }

            unsigned int get_x() const {
                return m_pos_x; 
            }
            void set_x(unsigned int x) {
                m_pos_x = x; 
            }

            unsigned int get_y() const {
                return m_pos_y; 
            }
            void set_y(unsigned int y) {
                m_pos_y = y; 
            }

        private: 
            uint32_t m_color{0xFF000000};
            unsigned int m_pos_x{0};
            unsigned int m_pos_y{0};
    };
    
} // namespace ct5