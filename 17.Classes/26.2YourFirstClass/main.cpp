#include <iostream>

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
}