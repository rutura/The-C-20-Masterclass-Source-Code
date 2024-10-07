/*
    . Exploring pure virtual functions and abstract classes: 
        . Pure virtual functions are functions that are declared in a base class but have no implementation.
            . The syntax is to add an =0 at the end of the function declaration.
        . The abstract class defines an interface that derived classes must implement.
        . If a class has at least one pure virtual function, it becomes an abstract class
        . You can’t create objects of an abstract class, if you do that , 
            you’ll get  a hard compiler error
        . Derived classes from an abstract class must explicitly override all the 
            pure virtual functions from the abstract parent class, if they don’t 
            they themselves become abstract
        . Pure virtual functions don’t have an implementation in the abstract class. 
            They are meant to be implemented by deriving classes
        . You can’t call the pure virtual functions from the constructor 
            of the abstract class
        . The constructor of the abstract class is used by deriving class to 
            build up the base part of the object

*/
module;

#include <string>
#include <string_view>


export module inh_poly_1;

namespace inh_poly_1{

    // Shape class
    export class Shape {
    protected:
        Shape() = default;  // Default constructor
        explicit Shape(std::string_view description) : m_description(description) {}  // Constructor with description

    public:
        virtual ~Shape() = default;  // Virtual destructor for proper cleanup

        // Pure virtual functions
        virtual double perimeter() const = 0;  // Calculate perimeter
        virtual double surface() const = 0;     // Calculate surface area

    private:
        std::string m_description;  // Description of the shape
    };



    // Rectangle class
    export class Rectangle : public Shape {
    public:
        Rectangle() = default;  // Default constructor
        Rectangle(double width, double height, std::string_view description) 
            : Shape(description), m_width(width), m_height(height) {}  // Parameterized constructor

        virtual ~Rectangle() override = default;  // Virtual destructor

        double perimeter() const override { return 2 * (m_width + m_height); }  // Calculate perimeter
        double surface() const override { return m_width * m_height; }          // Calculate surface area

    private:
        double m_width{ 0.0 };  // Width of the rectangle
        double m_height{ 0.0 }; // Height of the rectangle
    };



    // Circle class
    export class Circle : public Shape {
    public:
        Circle() = default;  // Default constructor
        Circle(double radius, std::string_view description) 
            : Shape(description), m_radius(radius) {}  // Parameterized constructor

        virtual ~Circle() override = default;  // Virtual destructor

        double perimeter() const override { return 2 * PI * m_radius; }  // Calculate perimeter
        double surface() const override { return PI * m_radius * m_radius; }  // Calculate surface area

    private:
        double m_radius{ 0.0 };  // Radius of the circle
        static inline constexpr double PI{ 3.14159265 };  // Constant PI value
    };
    
} // namespace inh_poly_1
