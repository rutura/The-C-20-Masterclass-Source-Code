/*#include <iostream>

const double PI {3.1415926535897932384626433832795};

class Cylinder {
    public : 
        //Functions (methods)
        double volume(){
            return PI * base_radius * base_radius * height;
        }

    public : 
        //Member variables
        double base_radius{1};
        double height{1};
};


int main(){

    Cylinder cylinder1; // Objects
    std::cout << "volume : " << cylinder1.volume() << std::endl;

    //Change the member variables
    cylinder1.base_radius = 10;
    cylinder1.height = 3;

    std::cout << "volume : " << cylinder1.volume() << std::endl;

    cylinder1.height =8;

    std::cout << "volume : " << cylinder1.volume() << std::endl;
   
    return 0;
}*/

#include <iostream>
#include <cmath>
 
class Point{
    public : 
    //methods
    Point() = default;
    Point(double x, double y){
        m_x = x; 
        m_y = y;
    }
    double distance_to( Point target){
        return sqrt(pow(target.m_x - m_x, 2) + pow(target.m_y - m_y, 2) * 1.0);
    }
    void print_info(){
        std::cout << "Point [ x : " << m_x << ", y: " << m_y << "]" << std::endl;
    }
    //member variables
    private : 
    double m_x{1};
    double m_y{1};
};
 
int main()
{
    Point p1;
    p1.print_info();
    return 0;
}