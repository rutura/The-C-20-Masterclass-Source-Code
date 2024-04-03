#include <fmt/format.h>
#include "point.h"
#include "car.h"

int main(){

    
    Point p1(10,10,10);
    Car c1("red",200.0);

    p1 = c1;

    fmt::println( "p1 : {}" , p1);
    

    return 0;
}