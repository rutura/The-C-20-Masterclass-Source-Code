/*
    . This file contains code that showcases the case where you set up
        an explicitly defaulted spaceship operator.
    . When you do that, the compiler will generate the >, <, >=, <= operators
        and also the == operator.
    . This will do member wise comparison for ordering.
    . If this is what you want, this option is amazing.
*/
module;

#include <compare>

export module spaceship_ops_4;

namespace spaceship_ops_4{

    //Default ordering with the spaceship operator
    export class Item
    {
    public:
        Item() = default;
        Item(int i) : Item(i, i, i) {}
        Item(int a_param, int b_param, int c_param) : a(a_param), b(b_param), c(c_param) {}

        //Defaulted spaceship operator
        // Default ordering : compiler generates >, < , >=, <= and also puts in the == operator
        auto operator<=>(const Item &right_operand) const = default;

        private:
        int a{ 1 };
        int b{ 2 };
        int c{ 3 };
    };
    
} // namespace spaceship_ops_4