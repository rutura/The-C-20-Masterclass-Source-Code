#include <fmt/format.h>
#include "cylinder.h"

int main(){

    Cylinder cylinder1(10,10);

    cylinder1.volume();

    //Managing a stack object through pointers
    Cylinder* p_cylinder1 = &cylinder1;

//    fmt::println("volume : {}" , (*p_cylinder1).volume() );
    fmt::println( "volume : {}" , p_cylinder1->volume() );

    //Create a cylinder heap object through the new operator
    Cylinder* p_cylinder2 = new Cylinder(100,2); // Heap

    fmt::println( "volume(clylinder2) : {}" , p_cylinder2->volume() );
    fmt::println( "base_rad(cylinder2) : {}" , p_cylinder2->get_base_radius() );




    delete p_cylinder2;
   
    
    return 0;
}