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
        std::cout << "Ellipse::draw() called for : " << m_description << std::endl;
    }
public: 
     void func() const  {
        std::cout << "Ellipse::func() called for : " << m_description << std::endl;
    }
private : 
    double m_x_radius;
    double m_y_radius;
};

#endif // ELLIPSE_H
