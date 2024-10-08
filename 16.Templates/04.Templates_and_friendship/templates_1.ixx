/*
            .#1: Friendship without templates
            . Exploring the basics of friendship
            . This has been covered earlier in the course.
            . It's just a review.
*/
module;

#include <fmt/format.h>

export module templates_1;

namespace templates_1 {

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

}   // namespace templates_1