#include <iostream>
#include "point.h"

int main(){
    
    Point p1(std::move(Point(4.6,5.2)));
    return 0;
}