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
        std::cout << "Dog::bark called : Woof!" << std::endl;
    }
    
    //The run method in subclasses of dog can't be overrided
    //further, derived classes are forced to use the implmenetation in Dog
    void run() const override final {
        std::cout << "Dog::run called" << std::endl;
    }

};

#endif // DOG_H
