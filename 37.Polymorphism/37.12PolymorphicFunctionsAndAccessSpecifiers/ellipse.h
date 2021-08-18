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
    virtual void draw( )const override{
        std::cout << "Ellipse::draw() called for : " << m_description << std::endl;
    }
public: 
    virtual void func() const override {
        std::cout << "Ellipse::func() called for : " << m_description << std::endl;
    }
private : 
    double m_x_radius;
    double m_y_radius;
};

#endif // ELLIPSE_H
