/*
    . Showcasing cases where one has to go through constructor initializer lists.
        . When data members are const:
            . If we add a const member to the Pixel class, 
                it must be initialized through the constructor initializer 
                list since const members cannot be modified after the object is created.
        . When data members are references:

            . References must also be initialized through the constructor
                initializer list because a reference must always be bound
                to a valid object upon initialization.
        . When data members are objects of a class without a default constructor:

            . If a member is an object of a class that doesn’t have a default
                 constructor, we must initialize it in the constructor initializer list,
                     as it cannot be default-constructed.
                     
    . Key Points In the code: 
        . Const member (m_const_color):
            This member is const, so it must be initialized using the initializer list in the constructor. In this example, m_const_color is initialized in all constructors.

        . Reference member (m_ref_color):
            A reference must be initialized when it is declared. In the example, m_ref_color is initialized to a reference of color in the constructor's initializer list.

        . Object without default constructor (m_position):
            The Position struct does not have a default constructor, so we must initialize m_position using the initializer list with the given x and y values.

*/
module;

#include <cstdint>
#include <fmt/format.h>

export module ct7;

namespace ct7{

    export struct Position {
        unsigned int x;
        unsigned int y;

        Position(unsigned int px, unsigned int py) : x{px}, y{py} {}  // No default constructor
    };

    export class Pixel {
    public:
        Pixel();  // Default constructor
        Pixel(uint32_t color, unsigned int x, unsigned int y);
        Pixel(uint32_t color, const Position& pos, const uint32_t& ref_color);  // Custom constructor
        ~Pixel();

        uint32_t get_color() const;
        void set_color(uint32_t color);

        unsigned int get_x() const;
        void set_x(unsigned int x);

        unsigned int get_y() const;
        void set_y(unsigned int y);

    private:
        const uint32_t m_const_color;        // 1. Const member
        const uint32_t& m_ref_color;         // 2. Reference member
        Position m_position;                 // 3. Object without default constructor
        uint32_t m_color{0xFF000000};
        unsigned int m_pos_x{0};
        unsigned int m_pos_y{0};
    };

    // Implementations

    Pixel::Pixel()
        :   m_const_color{0}, 
            m_ref_color{m_color}, 
            m_position{0, 0} 
    {
        //m_const_color = 0;  // Error: assignment of read-only member 'ct7::Pixel::m_const_color'
        //m_ref_color = m_color;  
        //m_position = Position(0, 0);  
        fmt::print("Default Pixel created\n");
    }

    Pixel::Pixel(uint32_t color, unsigned int x, unsigned int y) 
        :   m_const_color{color}, 
            m_ref_color{color}, 
            m_position{x, y}, 
            m_color{color}, 
            m_pos_x{x}, 
            m_pos_y{y} {
        fmt::print("Pixel created with color: 0x{:08X} at ({}, {})\n", color, x, y);
    }

    // Constructor demonstrating const, reference, and non-default constructor initialization
    Pixel::Pixel(uint32_t color, const Position& pos, const uint32_t& ref_color) 
        : m_const_color{color}, m_ref_color{ref_color}, m_position{pos.x, pos.y}, m_color{color} {
        fmt::print("Pixel created with color: 0x{:08X} at Position({}, {}) using a reference to 0x{:08X}\n", 
                    color, pos.x, pos.y, ref_color);
    }

    Pixel::~Pixel() {
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

    
} // namespace ct7