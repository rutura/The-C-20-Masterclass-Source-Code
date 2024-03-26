#include <fmt/format.h>
#include "point.h"

int main(){

    Point p1(10,10);

    auto p2 = p1--;
    fmt::println( "p1 : {}" , fmt::ptr(&p2)); // (10,10);
    fmt::println( "p1 : {}" , fmt::ptr(&p1) ); // (11,11)
   
    return 0;
}