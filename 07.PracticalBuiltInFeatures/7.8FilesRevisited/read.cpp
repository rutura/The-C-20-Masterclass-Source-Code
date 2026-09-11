#include <fstream>
#include <print>
#include <string>

// Part 2: read the account records back and print them as a table.
//
// >> reads one whitespace-delimited field at a time, same as std::cin -
// three reads per record instead of getline's one-line-at-a-time.

int main() {

    std::ifstream in{"accounts.txt"};

    if (!in) {
        std::println("Could not open accounts.txt. Run rooster_write first.");
        return 1;
    }

    std::println("{:<10}{:<10}{:>8}", "Account", "Name", "Balance");

    int number{};
    std::string name;
    double balance{};

    // Same shape as chapter 5's `while (std::getline(in, name))` - the
    // stream itself becomes false once there is nothing left to read, so
    // this loop runs once per complete record in the file.
    while (in >> number >> name >> balance) {
        std::println("{:<10}{:<10}{:>8.2f}", number, name, balance);
    }

    return 0;
}
