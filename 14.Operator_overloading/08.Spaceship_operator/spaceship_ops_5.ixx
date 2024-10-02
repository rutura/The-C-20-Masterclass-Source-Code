/*
    . This file contains code that showcases the case where you have members
        that don't have the spaceship operator.
    . In this case, Integer doesn't have the spaceship operator.
    . But BigItem has a member of type Integer.
    . If Integer doesn't have operator== and operator< overloaded, the compiler
        will delete the spaceship operator for BigItem. This is because it has 
        no way to compare the Integer members.
    . But if we provide the operator== and operator< for Integer, we can default
        the spaceship operator for BigItem, and just tell the compiler what the
        return type should be (The ordering).
    . Just returning auto won't cut it here.
*/
module;

#include <compare>

export module spaceship_ops_5;

namespace spaceship_ops_5{

    export struct Integer
    {

    Integer() = default;
    Integer(int n) : m_wraped_int{ n } {}
    int get() const { return m_wraped_int; }

    bool operator==(const Integer &right) const { return (m_wraped_int == right.m_wraped_int); }
    bool operator<(const Integer &right) const { return (m_wraped_int < right.m_wraped_int); }

    private:
    int m_wraped_int{};
    };


    export class BigItem
    {                               
    public:
    BigItem() = default;
    BigItem(int n) : BigItem(n, n, n) {}
    BigItem(int a_param, int b_param, int c_param) : a(a_param), b(b_param), c(c_param) {}

    // Ordering : compiler generates >, < , >=, <= and also puts in the == operator
    //auto operator<=>(const BigItem & right_operand) const = default;
    std::strong_ordering operator<=>(const BigItem &right_operand) const = default;

    private:
    int a{ 1 };
    int b{ 2 };
    int c{ 3 };
    Integer d;
    };  
    
} // namespace spaceship_ops_5