#include "circle.h"

Circle::Circle(double radius , std::string_view  description)
    : Shape(description) , 
        m_radius(radius)
{
}

