/*
    . Object sizes and slicing

        . A virtual table is a mechanism used in C++ to support dynamic 
            (runtime) polymorphism. It is essentially an array of 
            pointers to virtual functions.
        . Each class with virtual functions has its own vtable. When a 
            class is instantiated, a pointer to its vtable is included 
            in the object. This pointer enables the program to call the 
            correct function implementation based on the actual object 
            type at runtime.
        . The base class with virtual functions has a vtable containing 
            pointers to its virtual functions. This means that each 
            object of the base class will include a pointer to its vtable.

        . Derived Classes:
            . When you derive a new class from a base class with virtual 
                functions, the derived class has its own vtable. If the 
                derived class does not add any new virtual functions, its 
                vtable will be the same as the base class's.
            . If the derived class adds new virtual functions, its vtable 
                will grow larger to include pointers to these new functions.

        . Take away: classes with virtual functions have objects bigger than 
            their data members due to the inclusion of the vtable pointer. They 
            are then larger than classes without virtual functions.

        . Slicing:
            . Slicing occurs when you assign a derived class object to a base 
                class object. The derived class object is sliced down to the 
                base class object, losing any additional data members or 
                functionality.
            . This can happen when you pass a derived class object by value 
                to a function that takes a base class object, or when you 
                store derived class objects in a container of base class objects.

            . Slicing doesn't occur when you pass objects by reference or 
                pointer, as the actual object type is preserved.

            . In the example, the Circle object is sliced down to a Shape 
                object when assigned to a Shape variable. This results in 
                the Shape version of the draw() function being called, 
                even though the object is( or was) actually a Circle.

*/
module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module poly_4;

namespace poly_4{

    namespace early_binding{

        // Shape class
        export class Shape {
        public:
            explicit Shape(std::string_view description) : m_description(description) {}

            void draw() const {
                fmt::print("Shape::draw() called. Drawing {}\n", m_description);
            }

        protected:
            std::string m_description;
        };

        // Oval class
        export class Oval : public Shape {
        public:
            Oval(double x_radius, double y_radius, std::string_view description)
                : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}

            void draw() const {
                fmt::print("Oval::draw() called. Drawing {} with m_x_radius: {} and m_y_radius: {}\n",
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
                fmt::print("Circle::draw() called. Drawing {} with radius: {}\n",
                        m_description, get_x_rad());
            }

            double get_x_rad() const { return m_x_radius; } // Accessor to retrieve x_radius
        };

    }   // namespace early_binding   

    namespace late_binding{

        // Shape class
        export class Shape {
        public:
            explicit Shape(std::string_view description) : m_description(description) {}

            virtual void draw() const {
                fmt::print("Shape::draw() called. Drawing {}\n", m_description);
            }

        protected:
            std::string m_description;
        };

        // Oval class
        export class Oval : public Shape {
        public:
            Oval(double x_radius, double y_radius, std::string_view description)
                : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}

            void draw() const override {
                fmt::print("Oval::draw() called. Drawing {} with m_x_radius: {} and m_y_radius: {}\n",
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

            void draw() const override {
                fmt::print("Circle::draw() called. Drawing {} with radius: {}\n",
                        m_description, get_x_rad());
            }

            double get_x_rad() const { return m_x_radius; } // Accessor to retrieve x_radius
        };

    }   // namespace late_binding   
   
    
} // namespace poly_4