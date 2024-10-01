module;

#include <fmt/format.h>
#include <string>

export module no_poly_and_acc_spec;

namespace no_poly_and_acc_spec{

    //Shape class
    export class Shape
    {
    public:
    Shape();
    Shape(std::string_view description);
    ~Shape();

    public:
    void draw() const { fmt::println("Shape::draw() called for : {}", m_description); }

    private:
    void func() const { fmt::println("Shape::func() called for : {}", m_description); }

    protected:
    std::string m_description;
    };
    //Implementation
    Shape::Shape(std::string_view description) : m_description(description) {}

    Shape::Shape() : Shape("NoDescription") {}

    Shape::~Shape() {}





    //Ellipse class
    export class Ellipse : public Shape
    {
    public:
    Ellipse();
    Ellipse(double x_radius, double y_radius, std::string_view description);
    ~Ellipse();

    private:
    void draw() const { fmt::println("Ellipse::draw() called for : {}", m_description); }

    public:
    void func() const { fmt::println("Ellipse::func() called for : {}", m_description); }

    private:
    double m_x_radius;
    double m_y_radius;
    };
    //Implementation
    Ellipse::Ellipse(double x_radius, double y_radius, std::string_view description)
    : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius)
    {}

    Ellipse::Ellipse() : Ellipse(0.0, 0.0, "NoDescription") {}

    Ellipse::~Ellipse() {}


}   // namespace no_poly_and_acc_spec