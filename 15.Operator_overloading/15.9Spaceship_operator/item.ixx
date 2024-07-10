module;

export module item;

//#2: Defaulted equality operator
export class Item
{
public:
    Item() = default;
    Item(int i) : Item(i, i, i) {}
    Item(int a_param, int b_param, int c_param) : a(a_param), b(b_param), c(c_param) {}

    //#2: Defaulted equality operator
    // Equality, default : member wise comparison for equality
    /*
    bool operator==(const Item &right_operand) const = default;
    */

    //#:3 Defaulted spaceship operator
    // Default ordering : compiler generates >, < , >=, <= and also puts in the == operator
    auto operator<=>(const Item &right_operand) const = default;

    private:
    int a{ 1 };
    int b{ 2 };
    int c{ 3 };
};