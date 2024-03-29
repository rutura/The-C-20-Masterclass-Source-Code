#include <fmt/format.h>
#include "circle.h"
#include "rectangle.h"

int main(){
   
   //Shape * shape_ptr = new Shape; // Compiler error

    const Shape * shape_rect = new Rectangle(10,10,"rect1");
    double surface = shape_rect->surface();
    fmt::println( "dynamic type of shape_rect : {}" , typeid(*shape_rect).name() );
    fmt::println( "The surface of shape rect is : {}" , surface );


    fmt::println( "--------------" );

    const Shape * shape_circle = new Circle(10,"circle1");
    surface = shape_circle->surface();
    fmt::println( "dynamic type of shape_circle : {}" , typeid(*shape_circle).name() );
    fmt::println( "The surface of the circle is : {}" , surface );
    return 0;
}