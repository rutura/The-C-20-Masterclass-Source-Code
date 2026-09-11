#include <fstream>
#include <print>
#include <string>

// Part 1: write account records to a text file.
//
// Chapter 5's file lecture wrote one plain line of text per name. A file
// can just as easily hold several fields per line - here an account
// number, a name, and a balance - the same way std::cout would print them,
// just aimed at std::ofstream instead.

struct Account {
    int number;
    std::string name;
    double balance;
};

int main() {

    std::ofstream out{"accounts.txt"};

    if (!out) {
        std::println("Could not open accounts.txt for writing.");
        return 1;
    }

    // << separates fields with a space by default reading them back with
    // >>, which is exactly what read.cpp relies on.
    for (const Account& account :
         {Account{100, "Jones", 24.98}, Account{200, "Doe", 345.67},
          Account{300, "White", 0.0}, Account{400, "Stone", -42.16},
          Account{500, "Rich", 224.62}}) {
        out << account.number << ' ' << account.name << ' '
            << account.balance << '\n';
    }

    std::println("Wrote 5 account records to accounts.txt");

    return 0;
}
