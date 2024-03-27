#include <fmt/format.h>
#include "point.h"

int main(){

    Point point1(10.0,10.0);
	Point point2(20.0,20.0);
    fmt::println( "point1 : {}" , point1 );
    fmt::println( "point2 : {}" , point2 );
  

    auto result1 = (point1 > point2);
    fmt::println( "point1 > point2 : {}" , result1 );

    auto result2 = (point1 >= point2);
    fmt::println( "point1 >= point2 : {}" , result2 );

    auto result3 = (point1 == point2);
    fmt::println( "point1 == point2 : {}" , result3 );

    auto result4 = (point1 != point2);
    fmt::println( "point1 != point2 : {}" , result4 );

    auto result5 = (point1 < point2);
    fmt::println( "point1 < point2 : {}" , result5 );

    auto result6 = (point1 <= point2);
    fmt::println( "point1 <= point2 : {}" , result6 );


    //Implicit conversions
    fmt::println( "point1 > 20.1 : {}" , (point1 > 20.1) );
    //fmt::println( "20.1 > point1 : {}" , (20.1 > point1) );
    fmt::println( "20.1 > point1 : {}" , ((point1 <=> 20.1) < 0) );
    //((point1 <=> 20.1) < 0)

   
    return 0;
}