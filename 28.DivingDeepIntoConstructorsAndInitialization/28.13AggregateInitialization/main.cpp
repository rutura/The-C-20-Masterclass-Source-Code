#include <fmt/format.h>

struct Point
{
    double x;
    double y;
};

void print_point(const Point& p){
    fmt::println( "Point [ x: {}, y: {}]" , p.x  , p.y );
}


int main(){

    Point p1{10,20};
    print_point(p1);

    int scores[] {44,62,67,82,98,43,2,5,67};
   
    return 0;
}