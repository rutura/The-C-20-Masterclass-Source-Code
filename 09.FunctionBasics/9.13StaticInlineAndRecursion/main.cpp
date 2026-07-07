#include <print>

// --- static local variables ---
// A regular local variable is created fresh and destroyed every time a
// function runs. A static local variable is created only once, the first
// time the function runs, and keeps its value across every later call -
// its scope is still just this function, but its lifetime lasts as long as
// the whole program does.
int nextTransactionId() {
    static int id{1000}; // initialized only once, ever
    return id++;
}

// --- inline functions ---
// inline is a hint to the compiler that it may replace a call to this
// function with the function's body directly at the call site, avoiding
// the (tiny) overhead of an actual function call - most useful for small,
// frequently-called functions. Modern compilers already make this decision
// on their own in most cases; inline is a suggestion, not a guarantee.
inline double higherOf(double a, double b) {
    return (a > b) ? a : b;
}

// --- recursion ---
// A recursive function calls itself with a smaller version of the same
// problem, until it reaches a "base case" simple enough to answer directly
// without recursing further.
long long sumExpensesUpTo(int count) {
    if (count <= 0) {
        return 0; // base case: nothing left to add
    }
    return count + sumExpensesUpTo(count - 1); // recursive case
}

int main() {

    std::println("nextTransactionId() : {}", nextTransactionId());
    std::println("nextTransactionId() : {}", nextTransactionId());
    std::println("nextTransactionId() : {}", nextTransactionId());

    std::println("");
    std::println("higherOf(45.6, 22.1) : {}", higherOf(45.6, 22.1));

    std::println("");
    std::println("sumExpensesUpTo(5) : {}", sumExpensesUpTo(5)); // 5+4+3+2+1

    return 0;
}
