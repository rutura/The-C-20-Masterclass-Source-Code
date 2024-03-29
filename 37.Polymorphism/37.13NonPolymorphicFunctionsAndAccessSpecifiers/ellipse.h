#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse();
    Ellipse(double x_radius, double y_radius,
                            std::string_view description);
    ~Ellipse();
private: 
     void draw( )const {
        fmt::println( "Ellipse::draw() called for : {}" , m_description );
    }
public: 
     void func() const  {
        fmt::println( "Ellipse::func() called for : {}" , m_description );
    }
private : 
    double m_x_radius;
    double m_y_radius;
};

#endif // ELLIPSE_H
