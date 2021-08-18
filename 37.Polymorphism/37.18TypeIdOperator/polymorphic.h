#ifndef POLYMORPHIC_H
#define POLYMORPHIC_H

#include <iostream>

class DynamicBase{
public: 
    virtual void do_something(){
        std::cout << "DynamicBase::do_something() called" << std::endl;
    }
    virtual ~DynamicBase() = default;
};

class DynamicDerived : public DynamicBase{
public : 
    virtual void do_something() override{
        std::cout << "DynamicDerived::do_something() called" << std::endl;
    } 
    virtual ~DynamicDerived() = default;
};


#endif // POLYMORPHIC_H
