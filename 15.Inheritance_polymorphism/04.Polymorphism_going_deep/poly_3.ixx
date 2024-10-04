/*
    . Exploring static variables in the context of inheritance and polymorphism: 

        . In C++, static variables belong to the class itself rather than 
          to any individual instance of the class. This means :

            . Single Instance: There is only one instance of the static variable 
                shared across all instances of that class.
            . Independent in Each Class: If a derived class also declares a static 
                variable with the same name, it creates a separate static variable 
                independent of the base class's static variable.

    . Our example:
        . In the Shape class, m_count keeps track of the number of 
            Shape instances.
        . In the Ellipse class, m_count keeps track of the number of 
            Ellipse instances. This is not the same as the Shape::m_count. 
            Each class maintains its own static variable.

    . Inheritance:
        . When you create an instance of Ellipse, the constructor of Shape is 
            called, which increments Shape::m_count.
        . Simultaneously, the Ellipse constructor increments Ellipse::m_count.
        . If you create an Ellipse, Shape::m_count is incremented, but if you 
            create a Shape, only Shape::m_count is affected.
        . The destructors are called in the reverse order of construction, 
            decrementing the counts accordingly.

    . Accessing Static Variables:
        . You can access the static members using Shape::get_static_count() 
            and Ellipse::get_static_count().
        . This ensures that you can query the number of instances for each 
            class independently.
            
*/
module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module poly_3;

namespace poly_3{

    export class Shape {
    public:
        Shape(std::string_view description = "NoDescription") 
            : m_description(description) { ++m_count; }
        
        virtual ~Shape() { --m_count; }

        virtual void draw() const { 
            fmt::println("Shape::draw() called for: {}", m_description); 
        }
        
        virtual unsigned int get_count() const { return m_count; }

        static unsigned int get_static_count() { return m_count; }

    protected:
        std::string m_description;

    private:
        inline static unsigned int m_count{ 0 };  // Static variable for Shape
    };

    export class Ellipse : public Shape {
    public:
        Ellipse(double x_radius = 0.0, double y_radius = 0.0, 
                std::string_view description = "NoDescription") 
            : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {
            ++m_count; // Increment Ellipse count
        }

        ~Ellipse() { --m_count; }

        void draw() const override { 
            fmt::println("Ellipse::draw() called for: {} with radii ({}, {})", 
                        m_description, m_x_radius, m_y_radius); 
        }

        unsigned int get_count() const override { return m_count; }

        static unsigned int get_static_count() { return m_count; }

    private:
        inline static unsigned int m_count{ 0 };  // Static variable for Ellipse
        double m_x_radius;
        double m_y_radius;
    };
    
} // namespace poly_3