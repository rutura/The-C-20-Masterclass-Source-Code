#ifndef CYLINDER_H
#define CYLINDER_H

namespace Geom{
    
    class Cylinder
    {
    public:
        Cylinder(double base_rad, double height);
        
        double volume() const{
            return PI * m_base_rad * m_base_rad * m_height;
        }
        
    private : 
        inline static const double PI {3.1415926535897932384626433832795};
        double m_base_rad{1};
        double m_height{1};
    };
    
}

#endif // CYLINDER_H


