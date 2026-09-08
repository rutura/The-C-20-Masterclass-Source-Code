#ifndef NON_POLYMORPHIC_H
#define NON_POLYMORPHIC_H

#include <iostream>

class StaticBase{
     void do_something(){
        std::cout << "StaticBase::do_something() called" << std::endl;
    }
};

class StaticDerived : public StaticBase{
     void do_something() {
        std::cout << "StaticDerived::do_something() called" << std::endl;
    }    
};


#endif // NON_POLYMORPHIC_H
