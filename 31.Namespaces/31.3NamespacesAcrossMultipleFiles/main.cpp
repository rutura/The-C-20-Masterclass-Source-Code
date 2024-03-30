#include <fmt/format.h>
#include "point.h"
#include "line.h"
#include "cylinder.h"


int main(){

    Geom::Point p1(10,20);
    Geom::Point p2(3.4,6.1);
    p1.print_info();
    p2.print_info();

    fmt::println( "---" );

    Geom::Line l1(p1,p2);
    l1.print_info();

    fmt::println( "---" );

    Geom::Cylinder c1(1.4,10);
    fmt::println( "c1.volume : {}" , c1.volume() );


    return 0;
}