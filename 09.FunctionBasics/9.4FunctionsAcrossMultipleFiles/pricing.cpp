#include "pricing.h"

double applyDiscount(double amount, double discountRate) {
    return amount * (1.0 - discountRate);
}

double applyTax(double amount, double taxRate) {
    return amount * (1.0 + taxRate);
}
