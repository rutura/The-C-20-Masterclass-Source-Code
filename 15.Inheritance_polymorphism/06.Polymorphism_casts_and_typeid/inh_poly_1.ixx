/*
    . Exploring the use of dynamic_cast
        . Purpose: dynamic_cast is used for safely downcasting polymorphic types in 
            an inheritance hierarchy.
        . Type Safety: It performs a runtime check to ensure that the cast is valid; 
            if the cast fails, it returns nullptr for pointer types or throws a     
            std::bad_cast exception for reference types.

        . Requires Polymorphism: The class must have at least one virtual function 
            for dynamic_cast to work. This is necessary for the runtime type 
            information (RTTI) mechanism.

        . Usage: Commonly used to downcast a base class pointer/reference to a derived 
            class pointer/reference when you are unsure of the object's actual type.

        . Performance Overhead: Because it involves a runtime check, dynamic_cast can 
            incur a performance penalty compared to static_cast, which performs compile-time checks.

        . Upcasting: dynamic_cast can also be used for upcasting (from derived to base class), 
            but it is generally unnecessary since upcasting is always safe and can be done with static_cast.

        . Key takeaways:
            . Transforming from base class pointer or reference to derived class pointer or reference, at run time. 
            . Makes it possible to call non polymorphic methods on derived objects

*/
module;

#include <fmt/format.h>
#include <string>
#include <string_view>

export module inh_poly_1;

namespace inh_poly_1{

    // Animal class
    export class Animal {
    public:
        Animal() = default;
        Animal(std::string_view description) : m_description(description) {}
        virtual ~Animal() { fmt::print("Animal destructor called\n"); }

        virtual void breathe() const {
            fmt::print("Animal::breathe called for: {}\n", m_description);
        }

    protected:
        std::string m_description;
    };

    // Feline class
    export class Feline : public Animal {
    public:
        Feline() = default;
        Feline(std::string_view fur_style, std::string_view description) 
            : Animal(description), m_fur_style(fur_style) {}

        virtual ~Feline() { fmt::print("Feline destructor called\n"); }

        virtual void run() const {
            fmt::print("Feline {} is running\n", m_description);
        }

        void do_some_feline_thingy() const {
            fmt::print("Doing some feline thingy...\n");
        }

    private:
        std::string m_fur_style;
    };

    // Dog class
    export class Dog : public Feline {
    public:
        Dog() = default;
        Dog(std::string_view fur_style, std::string_view description) 
            : Feline(fur_style, description) {}

        virtual ~Dog() { fmt::print("Dog destructor called\n"); }

        virtual void bark() const {
            fmt::print("Dog::bark called: Woof!\n");
        }

        void do_some_dog_thingy() const {
            fmt::print("Doing some dog thingy..., speed: {}\n", m_speed);
        }

    private:
        double m_speed{};
    };


    // Helper functions
    // For use with dynamic casts
    export void do_something_with_animal_ptr(Animal *animal) {
        fmt::print("In function taking base pointer...\n");
        Feline *feline_ptr = dynamic_cast<Feline *>(animal);

        if (feline_ptr) {
            feline_ptr->do_some_feline_thingy();
        } else {
            fmt::print("Couldn't cast to Feline pointer, Sorry.\n");
        }
    }

    export void do_something_with_animal_ref(Animal &animal) {
        fmt::print("In function taking base reference...\n");
        Feline *feline_ptr_1{ dynamic_cast<Feline *>(&animal) };
        if (feline_ptr_1) {
            feline_ptr_1->do_some_feline_thingy();
        } else {
            fmt::print("Couldn't cast to Feline reference, Sorry.\n");
        }
    }
    
} // namespace inh_poly_1