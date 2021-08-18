#ifndef LINE_H
#define LINE_H

#include "point.h"

namespace Geom{
    
    class Line
    {
    public:
        Line(const Point& start, const Point& end); 
        
        void print_info()const{
            std::cout << "Line from " << std::endl;
            m_start.print_info();
            std::cout << "to : " << std::endl;
            m_end.print_info();
        }
    private : 
        Point m_start;
        Point m_end;
    };
    
}



#endif // LINE_H
