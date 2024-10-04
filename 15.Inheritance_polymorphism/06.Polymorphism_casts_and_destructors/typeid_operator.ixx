module;

#include <fmt/format.h>

export module typeid_operator;

namespace typeid_operator{

    //Polymorphic
    export class DynamicBase
    {
    public:
    virtual void do_something() { fmt::println("DynamicBase::do_something() called"); }
    virtual ~DynamicBase() = default;
    };

    export class DynamicDerived : public DynamicBase
    {
    public:
    virtual void do_something() override { fmt::println("DynamicDerived::do_something() called"); }
    virtual ~DynamicDerived() = default;
    };



    //Non polymorphic
    export class StaticBase
    {
    void do_something() { fmt::println("StaticBase::do_something() called"); }
    };

    export class StaticDerived : public StaticBase
    {
    void do_something() { fmt::println("StaticDerived::do_something() called"); }
    };

}   // namespace typeid_operator