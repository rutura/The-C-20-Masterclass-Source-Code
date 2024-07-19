module;

#include <fmt/format.h>
#include <string>

export module poly_func_and_acc_spec;

namespace poly_func_and_acc_spec{

    //Shape class
    export class Shape
    {
    public:
    Shape();
    Shape(std::string_view description);
    ~Shape();

    public:
    virtual void draw() const { fmt::println("Shape::draw() called for : {}", m_description); }

    private:
    // Can be inherited even if it is private. Derived class will put
    // this in public scope
    virtual void func() const { fmt::println("Shape::func() called for : {}", m_description); }

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
    virtual void draw() const override { fmt::println("Ellipse::draw() called for : {}", m_description); }

    public:
    virtual void func() const override { fmt::println("Ellipse::func() called for : {}", m_description); }

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


}   //namespace poly_func_and_acc_spec