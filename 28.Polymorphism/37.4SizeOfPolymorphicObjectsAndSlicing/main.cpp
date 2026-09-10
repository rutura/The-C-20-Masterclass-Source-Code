#include <iostream>
#include "shape.h"
#include "oval.h"
#include "circle.h"

int main(){

     //Comparing object sizes
     std::cout << "sizeof(Shape) : " << sizeof(Shape) << std::endl; // dynamic : 40
     std::cout << "sizeof(Oval) : " << sizeof(Oval) << std::endl; // dynamic : 56
     std::cout << "sizeof(Circle) : " << sizeof(Circle) << std::endl; // dynamic : 56


     //Slicing
    Circle circle1(3.3,"Circle1");
    Shape shape = circle1;
    shape.draw(); //Shape::draw

    return 0;
}