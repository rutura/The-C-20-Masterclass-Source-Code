module;

#include <concepts>
#include <iostream>

export module class_templates_concepts_02;

namespace class_templates_concepts_02{

    export template <typename T>
    requires std::is_arithmetic_v<T>
    class Point{
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
        std::weak_ordering operator<=>(const Point& other) const = default;
    private : 
        T m_x;
        T m_y;
    };

    export struct  Dog
    {
        ~Dog() = delete;
    };

    export struct  Cat
    {
    };

}   // namespace class_templates_concepts_02