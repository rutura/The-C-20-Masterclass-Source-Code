#include <iostream>
#include <print>

int main() {

    std::print("Enter two monthly salaries to compare: ");
    int salary1{};
    int salary2{};
    std::cin >> salary1 >> salary2;

    // Every one of these operators produces a bool: true or false.
    // std::println prints a bool as "true" / "false".
    std::println("salary1 == salary2 : {}", salary1 == salary2);   // equal pay
    std::println("salary1 != salary2 : {}", salary1 != salary2);   // not equal
    std::println("salary1 <  salary2 : {}", salary1 < salary2);
    std::println("salary1 >  salary2 : {}", salary1 > salary2);
    std::println("salary1 <= salary2 : {}", salary1 <= salary2);
    std::println("salary1 >= salary2 : {}", salary1 >= salary2);

    // The result is an ordinary value - you can name it and reuse it.
    bool first_earns_more{salary1 > salary2};
    std::println("first person earns more: {}", first_earns_more);

    return 0;
}
