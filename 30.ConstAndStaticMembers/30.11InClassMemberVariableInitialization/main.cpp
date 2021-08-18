#include <iostream>
#include "integer.h"

class Point{
public : 
    Point() {

    }
    Point(double x , double y) : m_x{x} , m_y{y}{
    };

 private :
    /*
    //No initialization at all 
    double m_x;
    double m_y;
    */

    //Explicit assignment
    /* 
    double m_x = 0.1;
    double m_y = 0.1;
    */

   //Braced initializers
   double m_x{0.1};
   double m_y{0.1};

   //
   Integer i{}; // Default constructo the object

};



int main(){

    Point p1;
   
    return 0;
}