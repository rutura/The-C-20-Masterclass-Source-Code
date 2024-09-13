module;

#include <fmt/format.h>

export module templates_and_friendship_07;

namespace templates_and_friendship_07{

    template <typename T>
    class Canvas;

    export template <typename T>
    class Point {

        //We only grant access to friends whose template paramters match that of the class.
        friend class Canvas<T>;
        friend void print_point<T>(const Point<T>& p);

        T x;
        T y;
    public:
        Point(T x, T y) : x(x), y(y) {}
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

}   // namespace templates_and_friendship_07 