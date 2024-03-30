#include <fmt/format.h>

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
    fmt::println( "volume : {}" , cylinder1.volume() );

    //Change the member variables
    cylinder1.base_radius = 10;
    cylinder1.height = 3;

    fmt::println( "volume : {}" , cylinder1.volume() );

    cylinder1.height =8;

    fmt::println( "volume : {}" , cylinder1.volume() );
   
    return 0;
}