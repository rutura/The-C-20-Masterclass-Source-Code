/*
    #2: Class is not template, friend function and friend class are templates.
        . Any template instantiations of print_point, regardless of the 
            template argument, can access the private members of the Point class.
        . Notice the syntax used to declare it as a friend of the 
            Point class: it uses the template syntax. 
        . The same applies to the class template Canvas. It's declared as a friend
             of the Point class and any template instantiation, regardless of the 
             template argument, can access its private members.
*/
module;

#include <fmt/format.h>

export module templates_2;

namespace templates_2 {

    //The class is not a template, but the friend function and class are templates.
    export class Point {
        template<typename T>
        friend class Canvas;

        template <typename T>
        friend void print_point(const Point& p);

        int x;
        int y;

    public:
        Point(int x, int y) : x(x), y(y) {}
    };

    export template<typename T>
    class Canvas {
    public:
        void draw(const Point& p) {
            if constexpr (std::is_same_v<T, int>) {
                fmt::print("Drawing integer point: ({}, {})\n", p.x, p.y);
            } else if constexpr (std::is_same_v<T, float>) {
                fmt::print("Drawing float point: ({:.2f}, {:.2f})\n"
                        , static_cast<float>(p.x)
                        , static_cast<float>(p.y));
            } else {
                fmt::print("Drawing generic point: ({}, {})\n", p.x, p.y);
            }
        }
    };

    export template <typename T>
    void print_point(const Point& p) {
        if constexpr (std::is_same_v<T, int>) {
            fmt::print("Point with int format: ({}, {})\n", p.x, p.y);
        } else if constexpr (std::is_same_v<T, float>) {
            fmt::print("Point with float format: ({:.2f}, {:.2f})\n"
                    , static_cast<float>(p.x)
                    , static_cast<float>(p.y));
        } else {
            fmt::print("Generic point: ({}, {})\n", p.x, p.y);
        }
    }

}   // namespace templates_2