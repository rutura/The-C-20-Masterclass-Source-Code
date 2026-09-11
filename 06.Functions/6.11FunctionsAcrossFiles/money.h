#pragma once

// The money helpers - declarations here, bodies in money.cpp.

double add_tax(double amount, double rate);          // rate as a fraction, e.g. 0.2
double apply_discount(double amount, double percent_off);  // percent_off, e.g. 15
