/*
        . Introducing the copy and swap idiom for copy assigment operators.
            . The copy and swap idiom is a way to implement the copy assignment operator in terms of the copy constructor and swap function.
            . It avoids leaving the object in a bad state if an exception is thrown during the copy assignment.
            . Here is how it works: 
                . It creates a copy of the object to be assigned.
                . The hard work of memory allocation and deallocation is done in the copy constructor.
                . If something goes wrong during the copy, the original object is left unchanged.
                . Once the copy is successfully created, the swap function swaps the contents of the copy with the original object.
                . We return the original object, which now contains the copied data.
                . The old data is deleted when the copy goes out of scope.
            . We also set up a global swap function to swap the contents of two objects.
            . This global swap function helps the standard library algorithms like std::swap to work with our class.
        . Visualize the copy and swap idiom when you get to the slides.

        . If have a user defined copy assignment operator, or destructor, the compiler won't generate a copy constructor for you. If you still need the compiler to generate a copy constructor, you can explicitly default it.
            eg: Pixel(const Pixel& other) = default;

        . If you have a user defined copy constructor or destructor, the compiler won't generate a copy assignment operator for you. If you still need the compiler to generate a copy assignment operator, you can explicitly default it.
            eg: Pixel& operator=(const Pixel& other) = default;

        . Think twice before you add a destructor to your class. If you don't need one, don't add one. The compiler generated destructor is usually good enough.

        . You can also explicitly delete the copy constructor and copy assignment operator if you don't want them .
            eg: Pixel(const Pixel& other) = delete;
                Pixel& operator=(const Pixel& other) = delete;


*/
module;

#include <cstdint>
#include <memory>
#include <fmt/format.h>

export module ct14;

namespace ct14{

   export struct Position {
        unsigned int x{0};
        unsigned int y{0};
    };

    export class Pixel {
    public:
        Pixel() = default;
        Pixel(uint32_t color, unsigned int x, unsigned int y);
        
        // Copy constructor for deep copy
        Pixel(const Pixel& other);

        // Copy assignment operator using copy-and-swap idiom
        Pixel& operator=(const Pixel &other);

        ~Pixel();
        
        // Getters and setters for color
        uint32_t get_color() const;
        void set_color(uint32_t color);

        // Getters and setters for raw pointer (m_pos)
        unsigned int get_x() const;
        unsigned int get_y() const;
        void set_x(unsigned int x);
        void set_y(unsigned int y);

        // Getters and setters for smart pointer (m_smart_pos)
        unsigned int get_smart_x() const;
        unsigned int get_smart_y() const;
        void set_smart_x(unsigned int x);
        void set_smart_y(unsigned int y);

        // Member swap function
        void swap(Pixel& other){
            std::swap(m_color, other.m_color);
            std::swap(m_pos, other.m_pos);
            std::swap(m_smart_pos, other.m_smart_pos);
        }

    private:
        uint32_t m_color{0xFF000000};
        Position* m_pos{nullptr}; // Raw pointer for position
        std::unique_ptr<Position> m_smart_pos; // Smart pointer for position
    };

    // Constructor
    Pixel::Pixel(uint32_t color, unsigned int x, unsigned int y)
        : m_color{color}, 
          m_pos{new Position{x, y}}, 
          m_smart_pos{std::make_unique<Position>(Position{x, y})} 
    {
    }

    // Copy constructor for deep copy with raw pointer and smart pointer
    Pixel::Pixel(const Pixel& other)
        : m_color{other.m_color}, 
          m_pos{new Position{*other.m_pos}}, 
          m_smart_pos{std::make_unique<Position>(*other.m_smart_pos)} {
        fmt::print("Pixel deep copied (with both raw and smart pointers)\n");
    }

    // Copy assignment operator using copy-and-swap idiom
    Pixel& Pixel::operator=(const Pixel& other) {
        Pixel temp(other); // Create a temporary copy
        swap(temp); // Swap the contents with the temporary copy
        fmt::print("Pixel copy-assigned (with both raw and smart pointers)\n");
        return *this;
    }

    // Destructor to clean up raw pointer
    Pixel::~Pixel() {
        delete m_pos; // Clean up memory allocated by raw pointer
        fmt::print("Pixel destroyed\n");
    }

    // Get color
    uint32_t Pixel::get_color() const {
        return m_color;
    }

    // Set color
    void Pixel::set_color(uint32_t color) {
        m_color = color;
    }

    // Getters for raw pointer position (m_pos)
    unsigned int Pixel::get_x() const {
        return m_pos->x;
    }

    unsigned int Pixel::get_y() const {
        return m_pos->y;
    }

    // Setters for raw pointer position (m_pos)
    void Pixel::set_x(unsigned int x) {
        m_pos->x = x;
    }

    void Pixel::set_y(unsigned int y) {
        m_pos->y = y;
    }

    // Getters for smart pointer position (m_smart_pos)
    unsigned int Pixel::get_smart_x() const {
        return m_smart_pos->x;
    }

    unsigned int Pixel::get_smart_y() const {
        return m_smart_pos->y;
    }

    // Setters for smart pointer position (m_smart_pos)
    void Pixel::set_smart_x(unsigned int x) {
        m_smart_pos->x = x;
    }

    void Pixel::set_smart_y(unsigned int y) {
        m_smart_pos->y = y;
    }

    // Global swap function
    void swap(Pixel& first, Pixel& second) {
        first.swap(second);
    }
    
    
} // namespace ct14