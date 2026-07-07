#include <print>
#include <string>

int main() {

    // Classic arcade cabinets only had room to save three letters of a
    // player's name next to a high score - each letter stored as its own char.
    char initial1{'A'};
    char initial2{'C'};
    char initial3{'E'};

    std::println("Initials: {}{}{}", initial1, initial2, initial3);

    // A char is just one byte in memory: 2^8 = 256 possible values (0-255),
    // each one mapped to a character by the ASCII table.
    std::println("sizeof(char): {}", sizeof(char));

    // Because a char *is* a small integer under the hood, we can store its
    // numeric code directly and cast it back to see the number.
    char fromCode{65}; // ASCII code 65 is 'A'
    std::println("");
    std::println("fromCode          : {}", fromCode);
    std::println("fromCode (as int) : {}", static_cast<int>(fromCode));

    // Char arithmetic works too, since chars behave like small integers -
    // handy for stepping through the alphabet to cycle a letter of the initials.
    char nextInitial = static_cast<char>(initial3 + 1);
    std::println("nextInitial       : {}", nextInitial); // 'F'

    // A single char can only ever hold one letter. For a whole player name we
    // reach for std::string instead - the type we've already used for
    // full names since chapter 3.
    std::string playerName{"Ada"};
    std::println("");
    std::println("playerName: {}", playerName);

    return 0;
}
