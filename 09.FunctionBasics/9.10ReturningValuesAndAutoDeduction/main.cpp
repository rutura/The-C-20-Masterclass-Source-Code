#include <print>
#include <string>

// Returning a value by value hands the caller a brand-new copy - the
// function's local variable and the caller's variable are separate objects
// with separate addresses, same idea as pass-by-value in reverse.
double computeTotal(double amount, double taxRate) {
    double total = amount * (1.0 + taxRate);
    return total;
}

std::string formatCategory(std::string_view category) {
    std::string label = "[" + std::string(category) + "]";
    return label;
}

// auto as a return type asks the compiler to work out the return type from
// what's actually returned, instead of spelling it out. Every return
// statement in the function must agree on what type that is.
auto classifyAmount(double amount) {
    if (amount > 100.0) {
        return std::string("large");
    } else {
        return std::string("small");
    }
}

int main() {

    double total = computeTotal(93.33, 0.08);
    std::string label = formatCategory("Food");

    std::println("total : {:.2f}", total);
    std::println("label : {}", label);
    std::println("classifyAmount(150.0) : {}", classifyAmount(150.0));
    std::println("classifyAmount(50.0)  : {}", classifyAmount(50.0));

    return 0;
}
