#include "shape.h"
#include "circle.h"

int main(){

    Shape * shape_ptr = new Circle(10,"Circle1");
    // shape_ptr->draw(45,"Red");
    shape_ptr->draw(45);

    delete shape_ptr;
    return 0;
}