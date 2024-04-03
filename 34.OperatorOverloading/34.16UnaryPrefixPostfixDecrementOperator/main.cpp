#include <fmt/format.h>
#include "point.h"

int main(){

    Point p1(10,10);

    auto p2 = p1--;
    fmt::println( "p1 : {}" , p1); // (10,10);
    fmt::println( "p2 : {}" , p2); // (9,9)
   
    return 0;
}