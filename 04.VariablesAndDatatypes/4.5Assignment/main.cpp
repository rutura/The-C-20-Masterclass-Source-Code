#include <iostream>
#include <iomanip>
#include <print>
#include <string>

using namespace std::string_literals;

/*
    Chapter 4 assignment
*/

// Exercise 4: a function goes here, above main, so main can call it.
// See the "Exercise 4" comment below for what to write.


// Function for exercise 4

/*
    [return type] [name of function] [parameter list] {

    }
*/

double unit_price(double total_cost, int quantity) {
    /*
        double price = total_cost / quantity;
        return price;
    */

    return total_cost / quantity;
}

int main() {

    /*
        Exercise 1 - Personal profile card

        Declare variables for a name, age, height (in meters, as a
        double), and whether the person is a student (bool). Print all
        four in a single formatted sentence using std::println
        or std::cout (if you don't have access to std::println).
    */
    std::println("--- Exercise 1: Personal profile card ---");
    // TODO: declare name/age/height/is_student and print them here.

    std::string name{ "Ada" };
    int age{ 28 };
    double height{ 1.65 }; 
    bool is_student{ false };

    // Modern way
    std::println("{} is {} years old, {}m tall and the value of is_student is {}",
        name, age, height, is_student);

    // Classic way
    std::cout << name << " is " << age << " years old, " << height
        << "m tall, and the value of is_student is " << is_student << "\n";


    /*
        Exercise 2 - Receipt printer

        Declare six variables as literals in code, exactly as follows:
            coffee_price  (double)  4.50      coffee_qty  (int)  2
            muffin_price  (double)  3.25      muffin_qty  (int)  1
            juice_price   (double)  2.75      juice_qty   (int)  3

        Compute a line total for each item (price * quantity) and a
        grand total (the sum of all three line totals).

        Print exactly four lines, in this order, with a $ before each
        amount and amounts printed to 2 decimal places (use
        std::format's {:.2f} spec, e.g. std::println("{:.2f}", 9.0)
        prints "9.00"):
            Coffee 2x : $9.00
            Muffin 1x : $3.25
            Juice  3x : $8.25
            Grand total  : $20.50
        The label column (everything before the " : ") must line up
        exactly as shown above - pad "Juice " with one trailing space so
        it's the same width as "Coffee" and "Muffin".
    */
    std::println("\n--- Exercise 2: Receipt printer ---");
    // TODO: declare the six variables above, compute the four totals,
    // and print the four-line receipt exactly as specified above.

    double coffe_price{ 4.5 };
    int coffee_qty{ 2 };
    double muffin_qty{ 3.25 };
    int muffin_price{ 1 };
    double juice_price{ 2.75 };
    int juice_qty{ 3 };

    double coffee_total{ coffe_price * coffee_qty };
    double muffin_total{ muffin_price * muffin_qty };
    double juice_total{ juice_price * juice_qty };
    double grand_total{ coffee_total + muffin_total + juice_total };


    // Modern way: {:.2f} forces 2 decimal places for just that one value,
    // no stream state to set beforehand or reset afterward.
    std::println("Coffee {}x : ${:.2f}", coffee_qty, coffee_total);
    std::println("Muffin {}x : ${:.2f}", muffin_qty, muffin_total);
    std::println("Juice  {}x : ${:.2f}", juice_qty, juice_total);
    std::println("Grand total  : ${:.2f}", grand_total);


    // Classic way: std::fixed + std::setprecision(2) force 2 decimal
    // places for every double printed afterward via std::cout.
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Coffee " << coffee_qty << "x : $" << coffee_total << "\n";
    std::cout << "Muffin " << muffin_qty << "x : $" << muffin_total << "\n";
    std::cout << "Juice  " << juice_qty << "x : $" << juice_total << "\n";
    std::cout << "Grand total  : $" << grand_total << "\n";

    // Reset std::cout back to its default formatting so it doesn't leak
    // into the exercises below.
    std::cout << std::defaultfloat << std::setprecision(6);

    /*
        Exercise 3 - Base converter tool

        Prompt the user (std::cin) for a decimal integer, then print it
        back out in octal, hex, and binary using std::println's format
        spec - the same {:#o}/{:#x}/{:#b} syntax from the lecture on NumberSystems,
        but on a value read from input instead of a hardcoded literal.
    */
    std::println("\n--- Exercise 3: Base converter tool ---");
    // TODO: read an int from std::cin and print it in octal/hex/binary.
    /*
    std::println("Type a whone number");
    int reading { };
    std::cin >> reading;

    // Modern way: one format string covers all three bases, binary included.
    std::println("{} in octal is {:#o}, hex {:#x}, binary {:#b}",
        reading, reading, reading, reading);

    // Classic way: std::oct/std::hex switch the base for everything
    // printed afterward, and there's no std::cout manipulator for binary
    // at all - it would need to be built by hand with bit shifting.
    std::cout << reading << " in octal is " << std::oct << reading
        << ", hex " << std::hex << reading << std::dec << "\n";
    */

    /*
        Exercise 4 - Unit price calculator (function)

        Write a function double unit_price(double total_cost, int quantity)
        above main that returns cost-per-item. Define it near the top of
        this file (see the placeholder above main), then call it here
        with at least two different sets of literal inputs and print the
        results.
    */
    std::println("\n--- Exercise 4: Unit price calculator ---");
    // TODO: call your unit_price(...) function with a couple of
    // different inputs and print the results here.

    double price1{ unit_price(12.00, 4) };
    double price2{ unit_price(7.50, 3) };

    // Modern way
    std::println("$12 for 4 items -> ${} each", price1);
    std::println("$7.50 for 3 items -> ${} each", price2);


    // Classic way:
    std::cout << "$12.00 for 4 items -> $" << price1 << " each\n";
    std::cout << "$7.50 for 3 items -> $" << price2 << " each\n";
    /*
        Exercise 5 - auto detective

        Before compiling, predict the deduced type for each auto
        declaration below (an int literal, a literal with a u/ll/f
        suffix, a bare string literal, an "s"-suffixed string literal,
        and an expression mixing int and double). Then use sizeof and
        std::println to check your predictions - a bare string literal
        deduces to const char*, not std::string, unless you use the "s"
        suffix. 
    */
    std::println("\n--- Exercise 5: auto detective ---");
    // TODO: Predict the types deduced by the declarations below and
    // print their sizeof() to check your predictions.

    auto whole_number{ 7 };         //   int      
    auto unsigned_number{ 7u };     //   unsigned int  
    auto big_number{ 7ll };         //   long long int 
    auto small_decimal{ 7.0f };     //   float 
    auto c_style_text{ "hello" };   //   const char * (c-string)  
    auto cpp_text{ "hello"s };      //   std::string literal 
    auto mixed_math{ 7 + 2.5 };     // double - int promoted to double

    return 0;
}