#include <fmt/format.h>


class Point
{
public : 
    double x;
    double y;
};

void print_point(const Point p){
    fmt::println( "Point [ x : {}{}{}{}" , p.x , ", y : " , p.y , "]" );
}


int main(){

    Point point1;

    point1.x = 5;
    point1.y = 6;

    print_point(point1);

    auto [a,b] = point1;

    fmt::println( "a : {}" , a );
    fmt::println( "b : {}" , b );

    point1.x = 44.1;
    point1.y = 55.2;

    print_point(point1);

    fmt::println( "a : {}" , a );
    fmt::println( "b : {}" , b );

    auto func = [=](){
        fmt::println( "a (captured) : {}" , a );
        fmt::println( "b (captured) : {}" , b );
    };
    func();

    
    return 0;
}