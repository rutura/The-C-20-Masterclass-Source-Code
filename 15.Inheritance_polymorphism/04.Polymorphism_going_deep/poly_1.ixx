/*
    . Exploring overloading, overriding and member hiding.

        . Overriding: The draw() function in the Oval and Circle classes 
            overrides the base class's draw() function. This is indicated 
            by the override keyword, which helps catch errors at compile time 
            if the function does not actually override a base class function.

        . Member Hiding: In the Oval class, the overloaded draw(int color_depth, 
            std::string_view color) function hides the Shape::draw(int) function. 

            . The moment you set up the two param draw function in the Oval class, 
                the one param draw function in the Shape class is hidden. 
                If you don't explicitly override the one param draw function in the
                Oval class, you lose the ability to call draw() on an Oval object.

        . Overloading: The draw() function is overloaded in both the Shape and 
            Oval classes. The Shape class has a version that takes no parameters 
            and one that takes an int, while the Oval class adds an additional 
            draw() function that takes both an int and a std::string_view.



        . I decided to keep the two draw functions in the Oval class to show the 
            concept of member hiding, and overloading. Notice that the two param 
            draw function is introduced at the Oval level, and Shape has no knowledge
            of it. To call, it we need to cast from Shape* to Oval*. We do this because
            we know that the second element in the vector is an Oval.
*/
module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module poly_1;

namespace poly_1{

    // Shape class
    export class Shape {
    public:
        // Default constructor
        Shape() = default;
        
        // Parameterized constructor
        explicit Shape(std::string_view description) : m_description(description) {}
        
        // Virtual destructor for proper cleanup in derived classes
        virtual ~Shape() = default;

        // Virtual function to draw the shape (overridden in derived classes)
        virtual void draw() const {
            fmt::println("Shape::draw() called. Drawing {}", m_description);
        }

        // Overloaded draw function to handle color depth
        virtual void draw(int color_depth) const {
            fmt::println("Shape::Drawing with color depth: {}", color_depth);
        }

    protected:
        std::string m_description{ "" };  // Shape description
    };

    // Oval class inheriting from Shape
    export class Oval : public Shape {
    public:
        // Default constructor
        Oval() = default;

        // Parameterized constructor
        Oval(double x_radius, double y_radius, std::string_view description)
            : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}

        // Override the draw function to provide specific behavior for Oval
        // DO: COmment the draw() method out and try to all it on a raw Oval object. Error.
        virtual void draw() const override {
            fmt::println(
                "Oval::draw() called. Drawing {} with x_radius: {} and y_radius: {}",
                m_description, m_x_radius, m_y_radius);
        }

        // Overloaded draw function with additional parameters
        virtual void draw(int color_depth, std::string_view color) const {
            fmt::println("Oval::Drawing with color depth: {} and color: {}", color_depth, color);
        }

        // Getters for radii
        double get_x_rad() const { return m_x_radius; }
        double get_y_rad() const { return m_y_radius; }

    private:
        double m_x_radius{ 0.0 };  // X radius of the oval
        double m_y_radius{ 0.0 };  // Y radius of the oval
    };

    // Circle class inheriting from Oval
    export class Circle : public Oval {
    public:
        // Default constructor
        Circle() = default;

        // Parameterized constructor
        explicit Circle(double radius, std::string_view description)
            : Oval(radius, radius, description) {}

        // Override the draw function to provide specific behavior for Circle
        virtual void draw() const override {
            fmt::println("Circle::draw() called. Drawing {} with radius: {}", m_description, get_x_rad());
        }
    };
    
} // namespace poly_1