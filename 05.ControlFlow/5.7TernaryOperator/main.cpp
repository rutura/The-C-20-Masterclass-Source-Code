#include <iostream>
#include <print>
#include <string>

int main() {

    std::print("Enter your age in years: ");
    int age{};
    std::cin >> age;

    // The conditional operator: condition ? value_if_true : value_if_false
    // Unlike an if statement, this whole thing IS a value - so it can go
    // straight into an initializer or a print.
    std::string category{age >= 18 ? "adult" : "child"};
    std::println("Category: {}", category);

    // Written the long way, that's:
    std::string category_long{};
    if (age >= 18) {
        category_long = "adult";
    }
    else {
        category_long = "child";
    }
    std::println("Category (if/else version): {}", category_long);

    // Handy inline inside a larger message. Keep it to simple either/or
    // choices - chained ?: nested inside ?: gets unreadable fast, and an
    // else-if ladder is clearer there.
    std::println("You pay the {} rate.", age >= 18 ? "adult" : "child");

    // Both branches must produce the same type. Here both are ints.
    int ticket_price{age >= 18 ? 12 : 7};
    std::println("Ticket price: {}", ticket_price);

    return 0;
}
