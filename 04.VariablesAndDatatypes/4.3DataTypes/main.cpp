#include <print>
#include <string>

int main() {

    // --- Integers: whole numbers ---
    int items_purchased{42};
    std::println("items purchased: {}", items_purchased);

    // A regular int can't hold a number this large without overflowing.
    // long long buys a much bigger range for values like a yearly total.
    long long yearly_total_cents{1'284'950'000};
    std::println("yearly total (cents): {}", yearly_total_cents);

    // A quantity can never go negative, so unsigned communicates that
    // intent - though it's easy to misuse (more on that in the next
    // lecture on auto), so reach for it deliberately, not by default.
    unsigned int loyalty_points{350};
    std::println("loyalty points: {}", loyalty_points);

    // sizeof shows how many bytes a type actually occupies - useful when
    // you care about memory, or about how large a number the type can hold.
    std::println("sizeof(int): {}, sizeof(long long): {}", sizeof(int), sizeof(long long));

    // --- Floating point: fractional numbers ---
    // float trades precision for size; double is the practical default
    // for money and measurements unless you have a specific reason not to.
    double amount_spent{93.33};
    float discount_rate{0.15f};
    std::println("amount spent: {}, discount rate: {}", amount_spent, discount_rate);

    // Scientific notation reads the same as decimal notation to the
    // compiler - useful once numbers get very large or very small.
    double national_debt{3.4e13};
    std::println("national debt (approx): {}", national_debt);

    // --- Booleans: true/false ---
    bool over_budget{amount_spent > 100.0};
    std::println("over budget: {}", over_budget);

    // --- Characters and text ---
    char currency_symbol{'$'};
    std::string customer_name{"Ada"};
    std::println("{}{} spent by {}", currency_symbol, amount_spent, customer_name);

    return 0;
}
