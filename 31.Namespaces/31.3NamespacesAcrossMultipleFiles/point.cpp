#include "point.h"

namespace Geom{
    
    Point::Point(double x, double y) : m_x{x}, m_y{y}{

    }
        
    Point::Point() : Point(0.0,0.0)
    {
    }

    Point::~Point()
    {
    }
    
}



