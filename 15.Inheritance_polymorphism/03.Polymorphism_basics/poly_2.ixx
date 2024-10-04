/*
    . Facts about polymorphism
        . Polymorphism relies on virtual functions.
        . A virtual function is a function in the base class that can be overridden 
                in derived classes.
        . Virtual functions enable runtime polymorphism by ensuring that the correct 
            function (based on the actual object type) is called, WHEN accessed 
            through a base class pointer or reference.
        . When a derived class provides its own implementation of a virtual function 
            from the base class, this is called function overriding.
        . Overriding allows derived classes to provide specific behavior while keeping 
            the same interface (method signature) as the base class.
        . The override keyword is used to indicate that a function is intended to 
            override a virtual function in the base class. It's optional,  
            but highly recommended.
        . Polymorphism at runtime occurs when the decision of which method to invoke 
            (from base or derived) is made during program execution, based on the 
            actual object type.
        . This enables flexibility, where the exact type of object doesn’t need to be 
            known at compile time, but the correct function is still invoked.

        . When a base class has virtual functions, it must also have a virtual 
            destructor to ensure proper cleanup of derived objects when deleted 
            through a base class pointer.
        . Prevents memory leaks or undefined behavior during destruction. For now, 
            always make the destructor virtual when you have virtual functions. We'll
            see an example of this in the next lecture.
        . The compiler uses a virtual table (vtable) to keep track of virtual 
            function addresses. Each object of a class with virtual functions 
            contains a pointer (called vptr) to the vtable of that class.
        . The vtable allows dynamic dispatch of functions at runtime, enabling polymorphism.
        . Implementation Detail: This process is automatic and managed by the compiler.

*/
module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module poly_2;

namespace poly_2{

    // Shape class
    export class Shape {
    public:
        Shape(std::string_view description = "") : m_description(description) {}

        virtual void draw() const {
            fmt::println("Shape::draw() called. Drawing {}", m_description);
        }

        virtual ~Shape() = default;  // Virtual destructor for proper cleanup

    protected:
        std::string m_description;
    };

    // Oval class
    export class Oval : public Shape {
    public:
        Oval(double x_radius, double y_radius, std::string_view description)
            : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}

        virtual void draw() const override {
            fmt::println("Oval::draw() called. Drawing {} with m_x_radius: {} and m_y_radius: {}", 
                        m_description, m_x_radius, m_y_radius);
        }

    protected:
        double m_x_radius{0.0};
        double m_y_radius{0.0};
    };

    // Circle class
    export class Circle : public Oval {
    public:
        Circle(double radius, std::string_view description)
            : Oval(radius, radius, description) {}

        virtual void draw() const override {
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
    
} // namespace poly_2