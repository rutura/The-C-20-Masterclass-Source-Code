#include <fmt/format.h>
#include "point.h"

int main() {
    Point p1(10, 10);
    Point p2(20, 20);
    Point p3(5, 5);

    auto p1_plus_p2 = p1 + p2;
    auto p2_minus_p3 = p2 - p3;

    fmt::println("p1 + p2: {}", p1_plus_p2); // (30, 30)
    fmt::println("p2 - p3: {}", p2_minus_p3); // (15, 15)

    fmt::println("------");

    p1 += p2;
    p2 -= p3;

    fmt::println("point1: {}",  p1); // (30, 30)
    fmt::println("point2: {}",  p2); // (15, 15)

    return 0;
}
