// import <iostream>;
#include <fmt/format.h>
import Line;

int main()
{
    Point p1{ 1, 2 };
    Point p2{ 3, 4 };

    Line line{ p1, p2 };

    fmt::println("p1 [{}, {}]" ,p1.x(),  p1.y());
    // std::cout << "p1 [" << p1.x() << "," << p1.y() << "]\n";
    fmt::println("p2 [{}, {}]",  p2.x() ,  p2.y());
    // std::cout << "p2 [" << p2.x() << "," << p2.y() << "]\n";
}