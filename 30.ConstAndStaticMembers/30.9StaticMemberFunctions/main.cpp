#include <fmt/format.h>
#include "point.h"


int main(){

   // fmt::println( "Point count : {}" , Point::get_point_count() );

    Point p1{6,7};

   // fmt::println( "Point count : {}" , p1.get_point_count() );
    p1.print_info(p1) ;

 
    return 0;
}