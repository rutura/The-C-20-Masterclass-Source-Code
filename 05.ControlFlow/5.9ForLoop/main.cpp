#include <print>

int main() {

    // A for loop packs the three pieces of a counter-controlled loop
    // into one header: initialization ; continuation condition ; update.
    //   for (int i{1}; i <= 10; ++i) { ... }
    //        \_______/  \______/   \_/
    //          once    before each  after each
    //                   iteration   iteration

    // --- Count 1 through 10 ---
    for (int i{1}; i <= 10; ++i) {
        std::print("{} ", i);
    }
    std::println("");

    // --- Sum the even integers from 2 through 20 ---
    // The update step can be any expression - here it's += 2.
    int total{0};
    for (int number{2}; number <= 20; number += 2) {
        total += number;
    }
    std::println("Sum of evens 2..20: {}", total);

    // --- Count down ---
    for (int countdown{5}; countdown >= 1; --countdown) {
        std::print("{}... ", countdown);
    }
    std::println("liftoff");

    // --- Compound-interest style table: one row per year ---
    double principal{1000.00};
    double rate{0.05};
    for (int year{1}; year <= 5; ++year) {
        double amount{principal};
        for (int k{0}; k < year; ++k) {   // multiply by (1 + rate), year times
            amount *= 1.0 + rate;
        }
        std::println("Year {}: {:.2f}", year, amount);
    }

    // The loop variable's scope is the loop body: `i`, `number`,
    // `countdown`, `year`, `k` are each gone once their loop ends.

    return 0;
}
