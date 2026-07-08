#include <iostream>
#include "point.h"


int main(){

    Point p1(10,20);

    //std::cout << "p1.x : " << p1[0] << std::endl; // x coordinate : 10
    std::cout << "p1.x : " << p1.operator[](0) << std::endl; // x coordinate : 10
    std::cout << "p1.y : " << p1[1] << std::endl; // y coordinate : 20
    return 0;
}