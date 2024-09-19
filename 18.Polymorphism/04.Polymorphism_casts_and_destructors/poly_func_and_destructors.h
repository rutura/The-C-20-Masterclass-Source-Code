#pragma once

#include <fmt/format.h>


namespace poly_func_and_destructors{
    class Base
    {
    public:
    Base() { fmt::println("Base constructor called"); }
    virtual ~Base() { fmt::println("Base destructor called"); }
    virtual void setup()
    {
        fmt::println("Base::setup() called");
        m_value = 10;
    }
    virtual void clean_up() { fmt::println("Base::clean_up() called"); }
    int get_value() { return m_value; }

    protected:
    int m_value;
    };

    class Derived : public Base
    {
    public:
    Derived() : Base() { fmt::println("Derived constructor called"); }
    virtual ~Derived() { fmt::println("Derived destructor called"); }

    virtual void setup() override
    {
        fmt::println("Derived::setup() called");
        m_value = 100;
    }
    virtual void clean_up() override { fmt::println("Derived::clean_up() called"); }
    };

}   // namespace poly_func_and_destructors{