#ifndef POINT_H
#define POINT_H

#include <fmt/format.h>

namespace Geom{
    
    class Point
    {
    public:
        Point();
        Point( double x, double y);
        void print_info()const{
            fmt::println( "Point [ x : {}{}{}{}" , m_x , ", y : " , m_y , "]" );
        }
        ~Point();
    private : 
        double m_x;
        double m_y;
    };
    
}



#endif // POINT_H
