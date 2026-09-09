#include <print>

// How an argument reaches a function - the two ways.
//
//   PASS BY VALUE      the parameter is a COPY of the argument.
//                      Changing the parameter does not affect the caller.
//
//   PASS BY REFERENCE  the parameter (written T&) is an ALIAS for the
//                      caller's variable. Changing the parameter changes
//                      the caller's variable.

// By value: `balance` is a copy of the caller's account balance. The
// deduction happens on the copy; the caller's balance is untouched and
// only sees the result if it uses the return value.
double charged_copy(double balance, double fee) {
    balance -= fee;
    return balance;
}

// By reference: `balance` refers to the caller's variable itself, so the
// deduction lands on the real account.
void charge(double& balance, double fee) {
    balance -= fee;
}

int main() {

    double checking{100.0};
    std::println("checking = {} before charged_copy", checking);
    std::println("charged_copy(checking, 15) returns {}", charged_copy(checking, 15.0));
    std::println("checking = {} after charged_copy  (unchanged)\n", checking);

    double savings{100.0};
    std::println("savings = {} before charge", savings);
    charge(savings, 15.0);
    std::println("savings = {} after charge  (charged)", savings);

    return 0;
}
