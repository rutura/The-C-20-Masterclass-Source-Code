module;

#include <fmt/format.h>

export module virt_func_default_arg;

namespace virt_func_default_arg{

    //Base class
    export class Base
    {
    public:
    Base();
    ~Base();

    virtual double add(double a = 5, double b = 5) const
    {
        fmt::println("Base::add() called");
        return (a + b + 1);
    }
    };
    //Implementation
    Base::Base() {}

    Base::~Base() {}





    //Derived class
    export class Derived : public Base
    {
    public:
    Derived();
    ~Derived();

    virtual double add(double a = 10, double b = 10) const override
    {
        fmt::println("Derived::add() called");
        return (a + b + 2);
    }
    };
    //Implementation
    Derived::Derived() {}
    Derived::~Derived() {}


}   // namespace virt_func_default_arg