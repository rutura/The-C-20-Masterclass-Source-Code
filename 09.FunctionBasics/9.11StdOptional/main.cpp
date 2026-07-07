#include <print>
#include <optional>
#include <string_view>

// std::optional<T> represents a value that might not be there - useful for
// a function whose result is legitimately "nothing" sometimes, without
// resorting to a sentinel value like -1 or an empty string that the caller
// has to remember to check for.
std::optional<double> findCategoryBudget(std::string_view category) {
    if (category == "Food") {
        return 400.0;
    }
    if (category == "Transport") {
        return 150.0;
    }
    return std::nullopt; // no budget configured for this category
}

int main() {

    std::optional<double> foodBudget = findCategoryBudget("Food");
    std::optional<double> travelBudget = findCategoryBudget("Travel");

    // has_value() (or a direct bool check) tells you whether there's
    // something to read before you try to read it.
    if (foodBudget.has_value()) {
        std::println("Food budget       : {}", foodBudget.value());
    }

    if (!travelBudget.has_value()) {
        std::println("Travel budget     : not configured");
    }

    // value_or(...) reads the value if present, or falls back to a default
    // in one step, without an explicit if/else.
    double travelBudgetOrDefault = travelBudget.value_or(0.0);
    std::println("Travel budget (or default) : {}", travelBudgetOrDefault);

    // Reading .value() on an optional with nothing in it throws an
    // exception and crashes the program - always check has_value() (or use
    // value_or) first.
    // std::println("{}", travelBudget.value()); // would throw

    return 0;
}
