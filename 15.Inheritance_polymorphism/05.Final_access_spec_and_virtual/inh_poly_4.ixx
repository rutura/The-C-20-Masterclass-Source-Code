/*
    . When default arguments are used on virtual functions, they are resolved at compile time
    . The actual virtual function to call is decided at compile time though.
    . This can be confusing.
    . The hierarchy: 
                    +----------------+
                    |     Base       | 
                    +----------------+
                    | + add(a=5, b=5)|  <-- Default arguments resolved at compile time
                    +----------------+
                            ^
                            |   (inherits from)
                            |
                    +----------------+
                    |    Derived     |
                    +----------------+
                    | + add(a=10, b=10)|  <-- Default arguments resolved at compile time
                    +----------------+
    . If we use a base pointer to manage a derived object and call the add function, the default 
        arguments of the base class will be used. This is probably what you don't want.
    
    . How I handle this: 
        . Use the same default arguments in the derived class as in the base class.
            . probably even store them in a static constexpr variable in the base class, so that I manage it from one place.
        . Not using default arguments in virtual functions at all.
*/
module;

#include <fmt/format.h>

export module inh_poly_4;

namespace inh_poly_4{

    // Base class
    export class Base
    {
    public:
        Base() {}
        virtual ~Base() {}

        // Virtual function with default arguments
        virtual double add(double a = 5, double b = 5) const
        {
            fmt::println("Base::add() called with: {} and {}", a, b); // Runtime: Function call resolution
            return (a + b + 1); // Runtime: Addition
        }
    };

    // Derived class
    export class Derived : public Base
    {
    public:
        Derived() {}
        virtual ~Derived() override {}

        // Override virtual function with different default arguments
        virtual double add(double a = 10, double b = 10) const override
        {
            fmt::println("Derived::add() called with: {} and {}", a, b); // Runtime: Function call resolution
            return (a + b + 2); // Runtime: Addition
        }
    };
    
} // namespace inh_poly_4