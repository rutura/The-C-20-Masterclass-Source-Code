module;

#include <concepts>
#include <iostream>

export module class_templates_concepts_01;

namespace class_templates_concepts_01{
        
    export template <typename T>
    requires std::is_arithmetic_v<T>
    class Point{
        /*
            static_assert(std::is_arithmetic_v<T>,
            "Coordinates of Point can only be numbers.");
            */
    public : 
        Point() = default;
        Point(T x, T y)  
        : m_x(x), m_y(y)
        {
        }
        friend std::ostream& operator<< ( std::ostream& out, const Point<T> operand){
            out << "Point [ x : " << operand.m_x
                        << ", y : " << operand.m_y << "]";
            return out;
        }
    private : 
        T m_x;
        T m_y;
    };

}   // namespace class_templates_concepts_01