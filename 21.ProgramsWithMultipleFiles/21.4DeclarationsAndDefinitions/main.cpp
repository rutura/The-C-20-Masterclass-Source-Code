#include <iostream>
#include "person.h"


//Declaration and definition
double weight;

//Functions : Declaration and defintion
/*
double add(double a, double b){
    return a + b;
}
*/

//Declaration
double add(double a, double b);



//Declaration and definition
struct Point{
    double m_x;
    double m_y;
};







int main(){
    /*
   // weight = 5; // Assignment

    std::cout << weight << std::endl;

    double result = add(10,20.5);
    std::cout << "result : " << result << std::endl;
    */

   Person p1("John Snow",27);
   p1.print_info();
  
    return 0;
}

/*
//Definition
double add(double a, double b){
    return a + b;
}
*/