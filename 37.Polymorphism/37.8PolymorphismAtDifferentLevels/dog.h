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

    virtual void breathe()const override{
        fmt::println( "Dog::breathe called for : {}", m_description );
    }

    virtual void run() const override{
        fmt::println( "Dog {} is running" , m_description);
    }

};

#endif // DOG_H
