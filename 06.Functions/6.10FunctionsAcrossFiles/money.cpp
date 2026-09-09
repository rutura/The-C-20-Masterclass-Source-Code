#include "money.h"

double add_tax(double amount, double rate) {
    return amount + amount * rate;
}

double apply_discount(double amount, double percent_off) {
    return amount - amount * (percent_off / 100.0);
}
