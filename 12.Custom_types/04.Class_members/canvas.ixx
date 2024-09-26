/*
        . Exploring static functions.
        . Facts: 

            . Class-wide Applicability: Static member functions apply to the
                     class as a whole, not to individual objects.
            . Definition: They can be defined just like regular member functions
                 but use the static keyword. You don't have to repeat the static keyword
                 in the class definition, if the definition is inside a module implementation file.
            . Access to Static Members: Static member functions can access private
                 and protected static members of the class.
            . Limited Access to Non-static Members: They do not have a this pointer and
                 cannot directly access non-static members. However, they can access
                 non-static members of other objects of the same class by passing
                 the object as a parameter.
            . Calling Static Functions: Within the class, static member functions
                 can be called like regular member functions. Outside the class, 
                 they must be called using the class name and the scope resolution
                  operator (e.g., Canvas::get_count()).
            . No this Pointer: Since they are not associated with a specific object,
                 static member functions do not have a this pointer.

            . Show that the static variable can either be defined (initialized) inside 
                the class definition by using the inline keyword or outside the class definition.

            . Explore the use of the inline keyword.
                    . We use the Pixel class here.
                    . The class definition and the inline function definitions should be placed together to ensure the compiler has access to the function body when needed.
                    . Outside of C++ modules, if the definition of a member function
                          is placed directly in the class definition,
                         that member function implicitly is marked as inline, 
                         even without using the inline keyword.

            . You should use static constexpr (or constexpr static)
                    data members in place of global constants when the constants apply only to the class, also called class constants. 
                    
                    . static constexpr data members of integral types and enumerations
                          can be defined and initialized inside the class definition even without making them inline variables.
            . Explore the use of reference members
*/
module;

#include <cstddef>
#include <fmt/format.h>
#include <vector>

export module canvas;

export import pixel;

namespace raw{

    //Add a configration struct and set up a method to print the configuration.
    export struct Configuration{
        std::size_t width{0};
        std::size_t height{0};
        std::string title{""};
        bool full_screen{false};
    };


    export class Canvas {

    public:
        Canvas(std::size_t width , std::size_t height, const Configuration& config);
        Canvas(const Canvas& src);
        Canvas(Canvas&& other) noexcept;
        ~Canvas();

        Canvas& operator=(const Canvas& rhs);
        Canvas& operator=(Canvas&& other) noexcept;

        void set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel);
        Pixel& get_pixel_at(std::size_t x, std::size_t y);

        void swap(Canvas& other) noexcept;

        void print() const;

        // Static methods
        static Canvas create_default_canvas(const Configuration& config);
        static std::size_t get_total_canvas_count();

    private:
        void verify_coordinate(std::size_t x, std::size_t y) const;

        std::size_t m_width{ 0 };
        std::size_t m_height{ 0 };
        Pixel** m_pixels{ nullptr };

        //Static member variable
        //static std::size_t s_canvas_count;
        static inline std::size_t s_canvas_count {0};

        // Static constexpr variables: These are used in the create_default_canvas method.
        static constexpr std::size_t DEFAULT_WIDTH {10};
        static constexpr std::size_t DEFAULT_HEIGHT {20};

        // Reference member variable
        const Configuration& m_config;


    };

    export void swap(Canvas& first, Canvas& second) noexcept;
}   // namespace raw