#include <iostream>

//Declare an enum type
//The default type associated with enum classes with C++ is int
//unsigned char : 0 ~ 255
enum class Month :  char {
    Jan = -1, January = Jan, Feb, Mar, 
    Apr, May, Jun,
    Jul, Aug, Sep,
    Oct = 100, Nov, Dec
};


int main(){

    Month month {Month::Jan};
    std::cout << "month : " << static_cast<int>(month) << std::endl;
    std::cout << "sizeof(month) : " << sizeof(month) << std::endl;

    return 0;
}