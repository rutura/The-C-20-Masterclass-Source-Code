#include <fmt/format.h>
#include "shape.h"
#include "oval.h"
#include "circle.h"

int main(){

     //Comparing object sizes
     fmt::println( "sizeof(Shape) : {}" , sizeof(Shape) ); // dynamic : 40
     fmt::println( "sizeof(Oval) : {}" , sizeof(Oval) ); // dynamic : 56
     fmt::println( "sizeof(Circle) : {}" , sizeof(Circle) ); // dynamic : 56


     //Slicing
    Circle circle1(3.3,"Circle1");
    Shape shape = circle1;
    shape.draw(); //Shape::draw

    return 0;
}