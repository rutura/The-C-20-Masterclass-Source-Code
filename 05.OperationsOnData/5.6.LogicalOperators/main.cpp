#include <print>

int main() {

    bool hasReceipt{true};
    bool isOverBudget{false};
    bool isRecurring{true};

    std::println("hasReceipt   : {}", hasReceipt);
    std::println("isOverBudget : {}", isOverBudget);
    std::println("isRecurring  : {}", isRecurring);

    // AND (&&): true only when every operand is true - e.g. flagging an
    // expense for review requires it to be both over budget AND missing a
    // receipt. A single false operand drags the whole expression to false.
    std::println("");
    std::println("AND (&&)");

    std::println("hasReceipt && isOverBudget             : {}", hasReceipt && isOverBudget);
    std::println("hasReceipt && isRecurring               : {}", hasReceipt && isRecurring);
    std::println("hasReceipt && isOverBudget && isRecurring: {}", hasReceipt && isOverBudget && isRecurring);

    // OR (||): true when at least one operand is true - e.g. an expense is
    // worth double-checking if it's over budget OR recurring (either reason
    // is enough on its own).
    std::println("");
    std::println("OR (||)");
    std::println("hasReceipt || isOverBudget              : {}", hasReceipt || isOverBudget);
    std::println("hasReceipt || isRecurring                : {}", hasReceipt || isRecurring);
    std::println("hasReceipt || isOverBudget || isRecurring: {}", hasReceipt || isOverBudget || isRecurring);

    // NOT (!): flips true to false and false to true.
    std::println("");
    std::println("NOT (!)");
    std::println("!hasReceipt   : {}", !hasReceipt);
    std::println("!isOverBudget : {}", !isOverBudget);
    std::println("!isRecurring  : {}", !isRecurring);

    // These combine, and parentheses make the intent explicit: flag this
    // expense unless it has both a receipt and isn't over budget.
    std::println("");
    std::println("Combining logical operators");
    std::println("!(hasReceipt && !isOverBudget) : {}", !(hasReceipt && !isOverBudget));

    // Logical operators read naturally alongside relational ones, which is
    // exactly how a real budget check ends up being written.
    int todaySpend{45};
    int dailyBudget{20};
    int lowSpendThreshold{11};

    std::println("");
    std::println("Combining relational and logical operators");
    std::println("todaySpend  : {}", todaySpend);
    std::println("dailyBudget : {}", dailyBudget);
    std::println("lowSpendThreshold : {}", lowSpendThreshold);
    std::println("");

    std::println("(todaySpend > dailyBudget) && (todaySpend > lowSpendThreshold) : {}",
                  (todaySpend > dailyBudget) && (todaySpend > lowSpendThreshold));
    std::println("(todaySpend == dailyBudget) || (dailyBudget <= lowSpendThreshold) : {}",
                  (todaySpend == dailyBudget) || (dailyBudget <= lowSpendThreshold));
    std::println("!hasReceipt && (todaySpend == dailyBudget) : {}",
                  !hasReceipt && (todaySpend == dailyBudget));

    return 0;
}
