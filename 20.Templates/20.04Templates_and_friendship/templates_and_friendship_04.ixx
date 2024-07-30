module;

#include <fmt/format.h>

export module templates_and_friendship_04;

namespace templates_and_friendship_04 {

    export template <typename T>
    class Point {
        //The overload of print_point that takes a Point<int> as an argument can access the private members of any instance of Point.
        friend void print_point(const Point<int>& p);
        friend class Canvas;
        int x;
        int y;  
    public:
        Point(T x, T y) : x(x), y(y) {}
    };

    export void print_point(const Point<int>& p) {
        fmt::print("Point: ({}, {})\n", p.x, p.y);
    }

    //This overload can't access the private members of any instance of Point.
    //Error!
    /*
    export void print_point(const Point<double>& p) {
        fmt::print("Point: ({}, {})\n", p.x, p.y);
    }
    */

}   // namespace templates_and_friendship_04