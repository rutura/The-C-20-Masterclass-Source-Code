// Chapter 5 continues the expense tracker from chapter 4 - now that we know
// how to store amounts and categories, this chapter is about actually
// computing with them.

#include <print>

int main() {

    int lunchCost{12};
    int coffeeCost{7};

    // Addition: combining two expenses into a subtotal.
    int subtotal = lunchCost + coffeeCost;
    std::println("subtotal (lunch + coffee): {}", subtotal);

    // Subtraction: applying a discount, or finding the difference in price
    // between two purchases.
    int discount = coffeeCost - 2;
    std::println("discounted coffee (coffeeCost - 2): {}", discount);

    int priceDifference = lunchCost - coffeeCost;
    std::println("priceDifference (lunchCost - coffeeCost): {}", priceDifference);

    // Multiplication: the cost of buying several of the same thing.
    int coffeesForTheTeam = coffeeCost * 4;
    std::println("coffeesForTheTeam (coffeeCost * 4): {}", coffeesForTheTeam);

    // Division: splitting a bill evenly between people.
    int totalBill{47};
    int peopleSplitting{4};
    int perPersonShare = totalBill / peopleSplitting;
    std::println("perPersonShare (totalBill / peopleSplitting): {}", perPersonShare);
    // Integer division truncates - 47 / 4 is really 11.75, but int can only
    // hold 11. Chapter 5.9 comes back to why, and chapter 4's float/double
    // types are the fix when the fractional part actually matters.

    // Modulus (%): the remainder left over after dividing - here, the leftover
    // cents that don't divide evenly among the group.
    int leftoverCents = totalBill % peopleSplitting;
    std::println("leftoverCents (totalBill % peopleSplitting): {}", leftoverCents);

    return 0;
}
