#include <print>
#include <string>

int main() {

    // Our expense tracker sorts spending into categories, and a single
    // letter is a handy, compact code for one - each letter stored as its
    // own char: F(ood), T(ransport), E(ntertainment).
    char foodCode{'F'};
    char transportCode{'T'};
    char entertainmentCode{'E'};

    std::println("Category codes: {} {} {}", foodCode, transportCode, entertainmentCode);

    // A char is just one byte in memory: 2^8 = 256 possible values (0-255),
    // each one mapped to a character by the ASCII table.
    std::println("sizeof(char): {}", sizeof(char));

    // Because a char *is* a small integer under the hood, we can store its
    // numeric code directly and cast it back to see the number.
    char fromCode{70}; // ASCII code 70 is 'F'
    std::println("");
    std::println("fromCode          : {}", fromCode);
    std::println("fromCode (as int) : {}", static_cast<int>(fromCode));

    // Char arithmetic works too, since chars behave like small integers -
    // handy for stepping through category codes when adding a new one.
    char nextCategoryCode = static_cast<char>(entertainmentCode + 1);
    std::println("nextCategoryCode  : {}", nextCategoryCode); // 'F' - next letter after 'E'

    // A single char can only ever hold one letter. For a full expense
    // description we reach for std::string instead - the type we've already
    // used for full names since chapter 3.
    std::string expenseDescription{"Coffee with client"};
    std::println("");
    std::println("expenseDescription: {}", expenseDescription);

    return 0;
}
