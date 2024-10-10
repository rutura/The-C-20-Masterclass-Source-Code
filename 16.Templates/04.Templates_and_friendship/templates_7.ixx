/*
    .#7: Class is a template, friends are templates, and we only want friends 
        whose template parameter matches that  of the class to have access to 
        the private members of the class.
*/
module;

#include <fmt/format.h>

export module templates_7;

namespace templates_7{

    template <typename T>
    class Canvas;

    export template <typename T>
    class Point {
        //We only grant access to friends whose template paramters match that of the class.
        friend class Canvas<T>;
        friend void print_point<T>(const Point<T>& p);
    public:
        Point(T x, T y) : x(x), y(y) {}
    private: 
        T x;
        T y;
    };

    export template <typename T>
    void print_point(const Point<T>& p) {
        fmt::print("Point: ({}, {})\n", p.x, p.y);
    }

    export template <typename T>
    class Canvas {
    public:
        void draw(const Point<T>& p) {
            fmt::print("Drawing point: ({}, {})\n", p.x, p.y);
        }
    };

}   // namespace templates_7 