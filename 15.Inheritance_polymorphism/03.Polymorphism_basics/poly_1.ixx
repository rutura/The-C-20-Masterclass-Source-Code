/*
    . Showing static binding in action in preparation for polymorphism.
    . We would want to manage derived objects through base class pointers and references.
    . But when we call the draw() function, we want the derived class's draw() to be called.
    . This is not the default behavior in C++.
    . We will see how to achieve this with polymorphism, in a later lecture.
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
        Shape() = default;
        Shape(std::string_view description) : m_description(description) {}

        void draw() const { 
            fmt::println("Shape::draw() called. Drawing {}", m_description); 
        }

    protected:
        std::string m_description{ "" };
    };

    // Oval class
    export class Oval : public Shape {
    public:
        Oval(double x_radius, double y_radius, std::string_view description)
            : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}

        void draw() const {
            fmt::println("Oval::draw() called. Drawing {} with m_x_radius: {} and m_y_radius: {}",
                        m_description, m_x_radius, m_y_radius);
        }

    protected:
        double m_x_radius{ 0.0 };
        double m_y_radius{ 0.0 };
    };

    // Circle class
    export class Circle : public Oval {
    public:
        Circle(double radius, std::string_view description)
            : Oval(radius, radius, description) {}

        void draw() const { 
            fmt::println("Circle::draw() called. Drawing {} with radius: {}", m_description, m_x_radius); 
        }
    };

    //Helper functions for drawing.
    export void draw_shape(Shape* shape){
        shape->draw();
    }
    export void draw_shape(Shape& shape){
        shape.draw();
    }
    
} // namespace poly_1