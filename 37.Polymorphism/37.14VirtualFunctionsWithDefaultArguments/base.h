#ifndef BASE_H
#define BASE_H
#include <fmt/format.h>
class Base
{
public:
    Base();
    ~Base();
    
    virtual double add(double a = 5 , double b = 5) const{
        fmt::println( "Base::add() called" );
        return (a + b + 1);
    }
};

#endif // BASE_H
