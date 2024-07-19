module;

#include <fmt/format.h>
#include <string>

export module polymorphism_with_static_members;

namespace polymorphism_with_static_members{

    //Shape class
    export class Shape
    {
    public:
    Shape();
    Shape(std::string_view description);
    virtual ~Shape();
    void draw() const { fmt::println("Shape::draw() called for : {}", m_description); }

    virtual int get_count() const { return m_count; }

    static int m_count;

    protected:
    std::string m_description;
    };
    //Implementation
    int Shape::m_count{ 0 };

    Shape::Shape(std::string_view description) : m_description(description) { ++m_count; }

    Shape::Shape() : Shape("NoDescription") {}

    Shape::~Shape() { --m_count; }




    //Ellipse class
    export class Ellipse : public Shape
    {
    public:
    Ellipse();
    Ellipse(double x_radius, double y_radius, std::string_view description);
    ~Ellipse();

    virtual int get_count() const override { return m_count; }

    static int m_count;

    private:
    double m_x_radius;
    double m_y_radius;
    };
    //Implementation
    int Ellipse::m_count{ 0 };

    Ellipse::Ellipse(double x_radius, double y_radius, std::string_view description)
    : Shape(description), m_x_radius(x_radius), m_y_radius(y_radius)
    {
    ++m_count;
    }

    Ellipse::Ellipse() : Ellipse(0.0, 0.0, "NoDescription") {}

    Ellipse::~Ellipse() { --m_count; }


}   // namespace polymorphism_with_static_members