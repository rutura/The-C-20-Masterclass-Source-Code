#include <iostream>
#include <print>
#include <string>

using namespace std::string_literals;

/*
    Chapter 4 assignment - solutions

    Solves every exercise from main.cpp. Where an exercise's output can be
    written either the classic std::cout way or the modern std::print way,
    both are shown side by side so you can compare them directly - from
    here on, the rest of the course sticks to std::print/std::println.
*/

// Exercise 4: unit_price is defined here, above main, so main can call it.
double unit_price(double total_cost, int quantity) {
    return total_cost / quantity;
}

// Exercise 6 (optional part): split a whole-cents amount into dollars
// and remaining cents, so the change-maker logic isn't repeated inline.
void split_cents(long long total_cents, long long& dollars, long long& cents) {
    dollars = total_cents / 100;
    cents = total_cents % 100;
}

int main() {

    // --- Exercise 1: Personal profile card ---
    std::println("--- Exercise 1: Personal profile card ---");

    std::string name{"Ada"};
    int age{28};
    double height_meters{1.65};
    bool is_student{false};

    // Classic way:
    std::cout << name << " is " << age << " years old, " << height_meters
        << "m tall, and is " << (is_student ? "a student" : "not a student")
        << ".\n";

    // Modern way:
    std::println("{} is {} years old, {}m tall, and is {}.",
        name, age, height_meters, is_student ? "a student" : "not a student");


    // --- Exercise 2: Receipt printer ---
    std::println("\n--- Exercise 2: Receipt printer ---");

    double coffee_price{4.50};
    int coffee_qty{2};
    double muffin_price{3.25};
    int muffin_qty{1};
    double juice_price{2.75};
    int juice_qty{3};

    double coffee_total{coffee_price * coffee_qty};
    double muffin_total{muffin_price * muffin_qty};
    double juice_total{juice_price * juice_qty};
    double grand_total{coffee_total + muffin_total + juice_total};

    // Classic way:
    std::cout << "Coffee " << coffee_qty << "x : $" << coffee_total << "\n";
    std::cout << "Muffin " << muffin_qty << "x : $" << muffin_total << "\n";
    std::cout << "Juice  " << juice_qty << "x : $" << juice_total << "\n";
    std::cout << "Grand total  : $" << grand_total << "\n";

    // Modern way:
    std::println("Coffee {}x : ${}", coffee_qty, coffee_total);
    std::println("Muffin {}x : ${}", muffin_qty, muffin_total);
    std::println("Juice  {}x : ${}", juice_qty, juice_total);
    std::println("Grand total  : ${}", grand_total);


    // --- Exercise 3: Base converter tool ---
    std::println("\n--- Exercise 3: Base converter tool ---");

    std::println("Type a whole number:");
    int reading{};
    std::cin >> reading;

    // Classic way: std::oct/std::hex switch the base for everything
    // printed afterward, and there's no std::cout manipulator for binary
    // at all - it would need to be built by hand with bit shifting.
    std::cout << reading << " in octal is " << std::oct << reading
        << ", hex " << std::hex << reading << std::dec << "\n";

    // Modern way: one format string covers all three bases, binary included.
    std::println("{} in octal is {:#o}, hex {:#x}, binary {:#b}",
        reading, reading, reading, reading);


    // --- Exercise 4: Unit price calculator ---
    std::println("\n--- Exercise 4: Unit price calculator ---");

    double price1{unit_price(12.00, 4)};
    double price2{unit_price(7.50, 3)};

    // Classic way:
    std::cout << "$12.00 for 4 items -> $" << price1 << " each\n";
    std::cout << "$7.50 for 3 items -> $" << price2 << " each\n";

    // Modern way:
    std::println("$12.00 for 4 items -> ${} each", price1);
    std::println("$7.50 for 3 items -> ${} each", price2);


    // --- Exercise 5: auto detective ---
    std::println("\n--- Exercise 5: auto detective ---");

    auto whole_number{7};            // int
    auto unsigned_number{7u};        // unsigned int
    auto big_number{7ll};            // long long
    auto small_decimal{7.0f};        // float
    auto c_style_text{"hello"};      // const char* - not std::string!
    auto cpp_text{"hello"s};         // std::string (needs the "s" suffix)
    auto mixed_math{7 + 2.5};        // double - int promotes to double

    std::println("whole_number     : {} bytes", sizeof(whole_number));
    std::println("unsigned_number  : {} bytes", sizeof(unsigned_number));
    std::println("big_number       : {} bytes", sizeof(big_number));
    std::println("small_decimal    : {} bytes", sizeof(small_decimal));
    std::println("c_style_text     : {} bytes (a pointer, not the text)", sizeof(c_style_text));
    std::println("cpp_text         : {} bytes (a real std::string object)", sizeof(cpp_text));
    std::println("mixed_math       : {} ({} bytes)", mixed_math, sizeof(mixed_math));


    // --- Exercise 6: Change-maker ---
    std::println("\n--- Exercise 6: Change-maker ---");

    std::println("Enter the bill total and amount paid:");
    double bill_total{};
    double amount_paid{};
    std::cin >> bill_total >> amount_paid;

    // Money math is done in whole cents (a long long), not floating
    // point, to avoid the rounding errors doubles can introduce.
    long long change_cents{
        static_cast<long long>((amount_paid - bill_total) * 100 + 0.5)};

    long long dollars{};
    long long cents{};
    split_cents(change_cents, dollars, cents);

    // Classic way:
    std::cout << "You get $" << dollars << " and " << cents << " cents back.\n";

    // Modern way:
    std::println("You get ${} and {} cents back.", dollars, cents);

    return 0;
}
