#include <iostream>
#include "point.h"
#include "line.h"
#include "cylinder.h"
#include "operations.h"


//using Geom::Point; // Just bringing in the name from the namespace
using namespace Geom;


double add(double a, double b){
    std::cout << "::add" << std::endl;
    return a + b + 0.555;
}


//using Math::add;
//using namespace Math;

int main(){

    Point p1(10,20);
    Point p2(3.4,6.1);
    p1.print_info();
    p2.print_info();

    std::cout << "---" << std::endl;

    Line l1(p1,p2);
    l1.print_info();

    std::cout << "---" << std::endl;

    Cylinder c1(1.4,10);
    std::cout << "c1.volume : " << c1.volume() << std::endl;

    std::cout << "---" << std::endl;

    Math_Weighted::add(10,20);

    std::cout << "---" << std::endl;

    //using std::cout;
    ///using std::endl;
    using namespace std; // NOT RECOMMENDED!


    cout << "Hello World" << std::endl;




    return 0;
}