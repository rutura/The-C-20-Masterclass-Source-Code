module;

#include <fmt/format.h>
#include <string>
#include <string_view>

export module static_binding;

namespace static_binding{

    //Shape class
    export class Shape
    {
    public:
    Shape() = default;
    Shape(std::string_view description);
    ~Shape();

    void draw() const { fmt::println("Shape::draw() called. Drawing {}", m_description); }

    protected:
    std::string m_description{ "" };
    };
    //Implementations
    Shape::Shape(std::string_view description) : m_description(description) {}

    Shape::~Shape() {}


    //Oval class
    export class Oval : public Shape
    {
    public:
    Oval() = default;
    Oval(double x_radius, double y_radius, std::string_view description);
    ~Oval();

    void draw() const
    {
        fmt::println("Oval::draw() called. Drawing {} with m_x_radius :  {} and m_y_radius : {}",
        m_description,
        m_x_radius,
        m_y_radius);
    }

    protected:
    double get_x_rad() const { return m_x_radius; }

    double get_y_rad() const { return m_y_radius; }

    private:
    double m_x_radius{ 0.0 };
    double m_y_radius{ 0.0 };
    };
    //Implementations
    Oval::Oval(double x_radius, double y_radius, std::string_view description)
    : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius)
    {}
    Oval::~Oval() {}




    //Circle class
    export class Circle : public Oval
    {
    public:
    Circle() = default;
    Circle(double radius, std::string_view description);
    ~Circle();

    void draw() const { fmt::println("Circle::draw() called. Drawing {} with radius: {}", m_description, get_x_rad()); }
    };
    //Implementations
    Circle::Circle(double radius, std::string_view description) : Oval(radius, radius, description) {}
    Circle::~Circle() {}

}   // namespace static_binding