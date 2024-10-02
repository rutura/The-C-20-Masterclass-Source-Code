/*
    . This file contains code that showcases how to simplify the Number class, 
        which used to have dozens of logical operators, to allow implicit 
        conversions.
    . First, we use explicitly defaulted spaceship operator, this will 
        generate the >, <, >=, <= operators and also the == operator.
    . These operators will use the rewrite rules from teh compiler to 
        work when literals are either on the left or right side.
    . To prevent us from having to write a LOT Of operators with the literal 
        on the left side, on the right side, ..., we just
        allow implicit conversions on the one param constructor. This is a design 
        choice, you'll have to make.
*/
module;

#include <iostream>
#include <compare>

export module spaceship_ops_7;

namespace spaceship_ops_7{

    // Logical operators simplified.
    export class Number {
        friend std::ostream &operator<<(std::ostream &out, const Number &number);

    public:
        Number(int value); // We enable implicit conversions here.

        // getter
        int get_wrapped_int() const { return m_wrapped_int; }

        auto operator<=>(const Number &right) const = default;

    private:
        int m_wrapped_int{0};
    };

    // Implementations

    Number::Number(int value) : m_wrapped_int(value) {}

    std::ostream &operator<<(std::ostream &out, const Number &number) {
        out << "Number : [" << number.m_wrapped_int << "]";
        return out;
    }

} // namespace spaceship_ops_7
