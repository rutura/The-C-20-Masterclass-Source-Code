#include <iostream>
#include "cylinder.h"


int main(){
   Cylinder c1(5);
   std::cout << "base_rad : " << c1.get_base_radius() << std::endl;
   std::cout << "height : " << c1.get_height() << std::endl;
   std::cout << "volume : " << c1.volume() << std::endl;
    return 0;
}