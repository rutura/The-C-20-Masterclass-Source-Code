/*
            .#5: The class is a template, friend functions and classes are templates, but
              but we want a few instances of the friends to have access to the private members of the class. 
            . Only int instances of the friends have access to the private members 
                of Point.
            . Others can't. They will trigger a compiler error.
*/
module;

#include <fmt/format.h>

export module templates_5;

namespace templates_5{

    template <typename T>
    class Canvas;

    export template <typename T>
    class Point {
        //Only int instances or specializations of the friends have access to private members.
        friend class Canvas<int>;
        friend void print_point<int>(const Point<int>& p);
    public:
        Point (T x, T y) : x(x), y(y) {}
    private: 
        T x;
        T y;
    };

    export template <typename T>
    void print_point(const Point<T>& p) {
        fmt::print("Point: ({}, {})\n", p.x, p.y); // Instances other than int will cause an error
    }

    template <>
    void print_point<int>(const Point<int>& p) {
        fmt::print("Point - function specialization : ({}, {})\n", p.x, p.y);
    }

    export template <typename T>
    class Canvas {
    public:
        void draw(const Point<T>& p) {
            fmt::print("Drawing point: ({}, {})\n", p.x, p.y); // Error: Instances othe than int will cause an error.
        }
    };

    template <>
    class Canvas<int> {
    public:
        void draw(const Point<int>& p) {
            fmt::print("Drawing point - specialization: ({}, {})\n", p.x, p.y);
        }
    };


}   // namespace templates_5