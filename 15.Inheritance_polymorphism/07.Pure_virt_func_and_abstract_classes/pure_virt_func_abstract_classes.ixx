module;

#include <string>

export module pure_virt_func_abstract_classes;

namespace pure_virt_func_abstract_classes{

    //Shape class
    export class Shape
    {
    protected:
    Shape() = default;
    Shape(std::string_view description);

    public:
    virtual ~Shape() = default;// If destructor is not public, you won't be
                                // able to delete base_ptrs. SHOW THIS TO STUDENTS
    // Pure virtual functions
    virtual double perimeter() const = 0;
    virtual double surface() const = 0;

    private:
    std::string m_description;
    };
    //Implementation
    Shape::Shape(std::string_view description) : m_description(description) {}





    //Rectangle class
    export class Rectangle : public Shape
    {
    public:
    Rectangle() = default;
    Rectangle(double width, double height, std::string_view description);
    virtual ~Rectangle() = default;

    public:
    virtual double perimeter() const override { return (2 * m_width + 2 * m_height); }


    virtual double surface() const override { return (m_width * m_height); }

    private:
    double m_width{ 0.0 };
    double m_height{ 0.0 };
    };
    //Implementation
    Rectangle::Rectangle(double width, double height, std::string_view description)
    : Shape(description), m_width(width), m_height(height)
    {}





    //Circle class
    export class Circle : public Shape
    {
    public:
    Circle() = default;
    Circle(double radius, std::string_view description);
    virtual ~Circle() = default;


    virtual double perimeter() const { return (2 * PI * m_radius); }

    virtual double surface() const { return PI * m_radius * m_radius; }


    private:
    double m_radius{ 0.0 };

    inline static double PI{ 3.14159265 };
    };
    //Implementation
    Circle::Circle(double radius, std::string_view description) : Shape(description), m_radius(radius) {}

}   // namespace pure_virt_func_abstract_classes