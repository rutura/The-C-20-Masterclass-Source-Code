#include <iostream>
#include <string>

class Point{
public:
    Point(double x, double y) : m_x{x},m_y{y}{
        std::cout << "Point constructor called" << std::endl;
    }
 private : 
    double m_x ;
    double m_y;
};

struct Person
{
    std::string m_name;
    unsigned int m_age ;
};



int main(){

    Point p1{10.9,39.3}; // Uniform initialization : () or {}

    //Struct
        // {}
   // Person person1 {"Daniel",35};

        //()
    Person p2("John",41.7);

    int students[] (1,2,3,4.7,5,6,7);
    
    return 0;
}