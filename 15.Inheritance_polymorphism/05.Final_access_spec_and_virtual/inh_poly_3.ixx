/*
    . Exploring the case where when the same function is public in the base class and private in the derived class, and vice versa.

    . The situation: 
        . draw is public in shape and private id ellipse
        . func is private in shape and public in ellipse
    . The question: if we go through a base class pointer, which classes's function will be called 
        both for draw and func?
        . When polymorphism is used, the function in the derived class is called.
        . When static binding is used, the function in the base class is called.

    . The hierarchy:
                  +---------------------+
                  |      Shape          |    <--- Base Class
                  +---------------------+
                  | + Shape()           |   
                  | + ~Shape()          |   
                  | + draw() const      |    <--- Public Method
                  | - func() const      |    <--- Private Method
                  |                     |
                  +---------------------+
                            ▲
                            |
                            |
                  +---------------------+
                  |      Ellipse        |    <--- Derived Class
                  +---------------------+
                  | + Ellipse()         |   
                  | + ~Ellipse()        |   
                  | + func() const      |    <--- Public Override of Base Method
                  | - draw() const      |    <--- Private Override of Base Method
                  |                     |
                  +---------------------+

    . Dynamic binding: 
        . When you call the virtual function through a base class pointer, the access specifier 
            in the base class determines whether the function is accessible, regardless of the 
            access specifier in the derived class

        . Another way to look at this : 
            . In general , when the function call is done through dynamic binding, the access 
                specifier of the base class applies, if the call is done through static binding,  
                the access specifier of the derived class applies.

        . My personal rule of thumb: 
            . When polymorphism is used, except for the base class, I mark all my other derived 
                overrides as private, unless the problem at hand requires otherwise.

    . Static binding:
        . When virtual functions are not used in a inheritance hierarchy, no dynamic binding 
            will take place, and static binding will occur, regardless of whether methods are 
            called through base class pointers, references or even raw derived objects.


*/
module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module inh_poly_3;

namespace inh_poly_3{

    namespace dyn_bind{
        // Shape class
        export class Shape {
        public:
            Shape() : m_description("NoDescription") {}
            Shape(std::string_view description) : m_description(description) {}
            virtual ~Shape() = default;  // Virtual destructor for proper cleanup

        public:
            virtual void draw() const {
                fmt::println("Shape::draw() called for: {}", m_description);
            }

        private:
            virtual void func() const {
                fmt::println("Shape::func() called for: {}", m_description);
            }

        protected:
            std::string m_description;

        };

        // Ellipse class
        export class Ellipse : public Shape {
        public:
            Ellipse() : Ellipse(0.0, 0.0, "NoDescription") {}
            Ellipse(double x_radius, double y_radius, std::string_view description)
                : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}
            ~Ellipse() = default;
        
        private: 
            virtual void draw() const override {
                fmt::println("Ellipse::draw() called for: {}", m_description);
            }

        public:
            virtual void func() const override {
                fmt::println("Ellipse::func() called for: {}", m_description);
            }

        private:
            double m_x_radius;
            double m_y_radius;
        };
        
    } // namespace dyn_bind


    namespace stat_bind{

        // Shape class
        export class Shape {
        public:
            Shape() : m_description("NoDescription") {}
            Shape(std::string_view description) : m_description(description) {}
            virtual ~Shape() = default;  // Virtual destructor for proper cleanup

        public:
            void draw() const {
                fmt::println("Shape::draw() called for: {}", m_description);
            }

        private:
            void func() const {
                fmt::println("Shape::func() called for: {}", m_description);
            }

        protected:
            std::string m_description;

        };

        // Ellipse class
        export class Ellipse : public Shape {
        public:
            Ellipse() : Ellipse(0.0, 0.0, "NoDescription") {}
            Ellipse(double x_radius, double y_radius, std::string_view description)
                : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius) {}
            ~Ellipse() = default;
        
        private: 
            void draw() const {
                fmt::println("Ellipse::draw() called for: {}", m_description);
            }

        public:
            void func() const {
                fmt::println("Ellipse::func() called for: {}", m_description);
            }

        private:
            double m_x_radius;
            double m_y_radius;
        };
        
    } // namespace stat_bind
    

    

    
} // namespace inh_poly_3