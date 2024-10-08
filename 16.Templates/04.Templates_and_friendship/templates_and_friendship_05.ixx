module;

#include <fmt/format.h>

export module templates_and_friendship_05;

namespace templates_and_friendship_05{

    template <typename T>
    class Canvas;

    export template <typename T>
    class Point {
        friend class Canvas<int>;
        friend void print_point<int>(const Point<int>& p);

        T x;
        T y;
    public:
        Point (T x, T y) : x(x), y(y) {}
    };

    export template <typename T>
    void print_point(const Point<T>& p) {
        //fmt::print("Point: ({}, {})\n", p.x, p.y); // Error, can't access private members of Point
    }

    template <>
    void print_point<int>(const Point<int>& p) {
        fmt::print("Point - function specialization : ({}, {})\n", p.x, p.y);
    }

    export template <typename T>
    class Canvas {
    public:
        void draw(const Point<T>& p) {
            //fmt::print("Drawing point: ({}, {})\n", p.x, p.y); // Error: can't access private members of Point
        }
    };

    template <>
    class Canvas<int> {
    public:
        void draw(const Point<int>& p) {
            fmt::print("Drawing point - specialization: ({}, {})\n", p.x, p.y);
        }
    };


}   // namespace templates_and_friendship_05