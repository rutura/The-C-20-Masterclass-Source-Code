/*
    . This file contains code that showcases how the defaulted equality operator
        works in C++20.
    . It does lexicographical member wise comparison for equality.
    . Once you have this operator, the compiler will also generate the != operator.
    . Implicit conversions are also taken care of.
    . For implicit conversions to work, the class has make the one param constructor
        non-explicit.
    . Rewrite rules: 
            | Expression     | Rewritten as     | Alternate Rewrite            |
            |----------------|------------------|------------------------------|
            | a > b          | (a <=> b) > 0    | (b <=> a) < 0                |
            | a < b          | (a <=> b) < 0    | (b <=> a) > 0                |
            | a >= b         | (a <=> b) >= 0   | (b <=> a) <= 0               |
            | a <= b         | (a <=> b) <= 0   | (b <=> a) >= 0               |
            | a == b         | b == a           |                              |
            | a != b         | !(a == b)        |  !(b == a)                   |
*/
module;

export module spaceship_ops_2;

namespace spaceship_ops_2{

    //Defaulted equality operator
    export class Item
    {
    public:
        Item(int i) : Item(i, i, i) {}
        Item(int a_param, int b_param, int c_param) : a(a_param), b(b_param), c(c_param) {}

        //#2: Defaulted equality operator
        // Equality, default : member wise comparison for equality
        bool operator==(const Item &right_operand) const = default;

        private:
        int a{ 1 };
        int b{ 2 };
        int c{ 3 };
    };
    
} // namespace spaceship_ops_2