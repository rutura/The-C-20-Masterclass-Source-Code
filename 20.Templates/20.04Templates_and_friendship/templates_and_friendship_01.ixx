module;

#include <fmt/format.h>

export module templates_and_friendship_01;

namespace templates_and_friendship_01 {

    export class Point {
        int x;
        int y;
    public:
        Point(int x, int y) : x(x), y(y) {}
        friend void print_point(const Point& p);
    };

    export void print_point(const Point& p) {
        fmt::print("Point: ({}, {})\n", p.x, p.y);
    }

}   // namespace templates_and_friendship_01