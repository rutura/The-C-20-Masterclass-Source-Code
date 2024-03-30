#include <fmt/format.h>
#include "point.h"

int main(){

    //Print the point count in our program
    //fmt::println( "Point count : " , Point::m_point_count ); //0

    Point p1(10.0,20.1);

    fmt::println( "Point count : {}" , p1.get_point_count() ); //1

    Point points[] {Point(1,1),Point(),Point(4)};

    fmt::println( "Point count : {}" , p1.get_point_count() ); //4
   
    return 0;
}