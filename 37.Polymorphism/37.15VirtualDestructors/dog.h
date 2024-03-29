#ifndef DOG_H
#define DOG_H
#include "feline.h"
class Dog : public Feline
{
public:
    Dog() = default;
    Dog(std::string_view fur_style, std::string_view description);
     virtual ~Dog();
    
    virtual void bark() const{
        fmt::println( "Dog::bark called : Woof!" );
    }

};

#endif // DOG_H
