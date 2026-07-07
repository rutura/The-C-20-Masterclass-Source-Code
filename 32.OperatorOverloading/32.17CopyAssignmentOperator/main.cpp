#include <iostream>
#include "point.h"

int main(){

    
    Point p1(10,10,10);
    Point p2(20,20,20);
    Point p77(3,3,3);

    std::cout << "p1 : " << p1 << std::endl;
    std::cout << "p2 : " << p2 << std::endl;

    std::cout << "-----" << std::endl;

    //Assignment
    //p1 = p2 = p77;
    //p1.operator=(p2).operator=(p77);
    p1.operator=(p2.operator=(p77));

    std::cout << "p1 : " << p1 << std::endl;
    std::cout << "p2 : " << p2 << std::endl;

    //Change data
    p1.set_data(55);

    std::cout << "-----------" << std::endl;
    std::cout << "p1 : " << p1 << std::endl;
    std::cout << "p2 : " << p2 << std::endl;
   

   //
   /*
   Point p3(30,30,30);
   Point p4 = p3;

   std::cout << "p3 : " << p3 << std::endl;
   std::cout << "p4 : " << p4 << std::endl;

   p3.set_data(77);

   std::cout << "-----" << std::endl;
   std::cout << "p3 : " << p3 << std::endl;
   std::cout << "p4 : " << p4 << std::endl;


   std::cout << "Done!" << std::endl;
   */

    
    return 0;
}