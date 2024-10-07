/*
    . Exploring the usage of the typeid operator with polymorphic types: 
        . It is used to obtain type information at runtime.
        . For fundamental types, it returns the static type.
            . eg: typeid(int).name() returns int
        . For polymorphic references and pointers, it returns the dynamic type.
            . eg: typeid(*b_ptr).name() returns DynamicDerived
        . For non polymorphic references and pointers, it returns the static type.
            . eg: typeid(*b_ptr_s).name() returns StaticBase
    . It's meant to be used with polymorphic types.
        . It fetches and uses the dynamic type information stored in the vtable.  
*/
module;

#include <fmt/format.h>

export module inh_poly_2;

namespace inh_poly_2{

    // Polymorphic
    export class DynamicBase {
    public:
        virtual void do_something() { fmt::println("DynamicBase::do_something() called"); }
        virtual ~DynamicBase() = default;
    };

    export class DynamicDerived : public DynamicBase {
    public:
        virtual void do_something() override { fmt::println("DynamicDerived::do_something() called"); }
        virtual ~DynamicDerived() override = default;
    };

    // Non polymorphic
    export class StaticBase {
    public:
        void do_something() { fmt::println("StaticBase::do_something() called"); }
    };

    export class StaticDerived : public StaticBase {
    public:
        void do_something() { fmt::println("StaticDerived::do_something() called"); }
    };
    
} // namespace inh_poly_2