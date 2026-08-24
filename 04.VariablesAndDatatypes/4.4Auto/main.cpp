#include <print>
#include <string>

using namespace std::string_literals;

int main() {

    // auto deduces the type from the initializer - the compiler already
    // knows the type of 93.33, so writing "double" again is redundant.
    auto amount_spent{93.33};
    auto items_purchased{42};

    // A bare string literal deduces to const char*, not std::string - it's
    // the C-style string type C++ inherited from C. The "s" suffix (from
    // std::string_literals) makes it a std::string literal instead, so
    // auto deduces std::string the way you'd actually want here.
    auto store_id{"store-42"};
    auto customer_name{"Ada"s};

    std::println("amount spent: {} ({} bytes)", amount_spent, sizeof(amount_spent));
    std::println("items purchased: {} ({} bytes)", items_purchased, sizeof(items_purchased));
    std::println("store id: {} ({} bytes)", store_id, sizeof(store_id));
    std::println("customer: {} ({} bytes)", customer_name, sizeof(customer_name));

    // The deduced type sticks around for the variable's whole lifetime -
    // auto only affects how the type is written down, not how the
    // variable behaves afterward.
    auto loyalty_points{350u}; // the 'u' suffix deduces unsigned int

    // DANGER: assigning a negative value to an unsigned variable doesn't
    // error - it wraps around to a huge positive number instead. Because
    // auto deduced unsigned here, this mistake is easy to miss without
    // checking what auto actually chose.
    loyalty_points = -10;
    std::println("loyalty points after mistaken refund: {}", loyalty_points);

    return 0;
}
