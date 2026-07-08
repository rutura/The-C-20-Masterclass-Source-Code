#ifndef BASE_H
#define BASE_H
#include <iostream>
class Base
{
public:
    Base();
    ~Base();
    
    virtual double add(double a = 5 , double b = 5) const{
        std::cout << "Base::add() called" << std::endl;
        return (a + b + 1);
    }
};

#endif // BASE_H
