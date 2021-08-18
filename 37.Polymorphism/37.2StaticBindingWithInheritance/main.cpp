#include <iostream>
#include "shape.h"
#include "oval.h"
#include "circle.h"

void draw_circle(const Circle& circle){
    circle.draw();
}

void draw_oval(const Oval& oval){
    oval.draw();
}
// More functions as you deal with more shape types. 30 ? 70? 100? It's messy.



int main(){

    Shape shape1("Shape1");
    //shape1.draw();

    Oval oval1(2.0,3.5,"Oval1");
    //oval1.draw();

    Circle circle1(3.3,"Circle1");
    //circle1.draw();

    //Base pointers
    Shape * shape_ptr = &shape1;
    //shape_ptr->draw();

    shape_ptr = &oval1;
    //shape_ptr->draw(); // Draw an oval

    shape_ptr = &circle1;
    //shape_ptr->draw();


    //Base references
    Shape& shape_ref = circle1;
    //shape_ref.draw();


    //Drawing shapes
    draw_circle(circle1);
    draw_oval(oval1);



    //Shapes stored in collections
     Circle circle_collection[]{circle1,Circle(10.0,"Circle2"),Circle(20.0,"Circle3")};
     Oval oval_collection[]{oval1,Oval(22.3,51.1,"Oval2")};
     //More arrays as you have more shape types, 100? Messy right?

    
   
    return 0;
}