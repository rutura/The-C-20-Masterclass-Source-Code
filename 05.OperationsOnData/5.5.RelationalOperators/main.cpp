#include <print>

int main() {

    int todaySpend{20};
    int dailyBudget{20};

    std::println("todaySpend  : {}", todaySpend);
    std::println("dailyBudget : {}", dailyBudget);

    // Relational operators compare two values and produce a bool - exactly
    // the kind of question a budget check needs to answer.
    std::println("");
    std::println("Comparing today's spend against the budget");

    std::println("todaySpend < dailyBudget  : {}", todaySpend < dailyBudget);
    std::println("todaySpend <= dailyBudget : {}", todaySpend <= dailyBudget);
    std::println("todaySpend > dailyBudget  : {}", todaySpend > dailyBudget);
    std::println("todaySpend >= dailyBudget : {}", todaySpend >= dailyBudget);
    std::println("todaySpend == dailyBudget : {}", todaySpend == dailyBudget);
    std::println("todaySpend != dailyBudget : {}", todaySpend != dailyBudget);

    // The result of a comparison is just a bool, so it can be stored in a
    // variable and used later - like a hasHitBudget flag from chapter 4.
    std::println("");
    std::println("Storing the comparison for later use");

    bool hasHitBudget = (todaySpend >= dailyBudget);
    std::println("{} >= {} : {}", todaySpend, dailyBudget, hasHitBudget);

    return 0;
}
