#include <print>
#include <bitset>

int main() {

    // Bitwise operators work on the individual bits of an integer, not the
    // number as a whole. std::bitset<N> is only used here to *display* those
    // bits readably (there's no std::formatter for bitset itself, so we go
    // through .to_string() first) - the operators themselves work on plain
    // unsigned char.
    unsigned char value{0b0000'1111};
    std::println("value        : {}", std::bitset<8>(value).to_string());

    // Shift left: every bit moves left by the given count, zeros fill in
    // from the right. Each left shift by 1 doubles the value (until bits
    // start falling off the top).
    unsigned char shiftedLeft = static_cast<unsigned char>(value << 2);
    std::println("value << 2   : {}", std::bitset<8>(shiftedLeft).to_string());

    // Shift right: every bit moves right, zeros fill in from the left.
    // Each right shift by 1 halves the value (rounding down).
    unsigned char shiftedRight = static_cast<unsigned char>(value >> 2);
    std::println("value >> 2   : {}", std::bitset<8>(shiftedRight).to_string());

    // AND, OR, XOR, NOT: the same logical operators from chapter 5, but
    // applied bit-by-bit instead of to the value as a whole.
    unsigned char a{0b0000'0011};
    unsigned char b{0b0000'0101};

    std::println("");
    std::println("a           : {}", std::bitset<8>(a).to_string());
    std::println("b           : {}", std::bitset<8>(b).to_string());
    std::println("a & b (AND) : {}", std::bitset<8>(a & b).to_string()); // 1 only where both are 1
    std::println("a | b (OR)  : {}", std::bitset<8>(a | b).to_string()); // 1 where either is 1
    std::println("a ^ b (XOR) : {}", std::bitset<8>(a ^ b).to_string()); // 1 where exactly one is 1
    std::println("~a    (NOT) : {}", std::bitset<8>(static_cast<unsigned char>(~a)).to_string()); // flips every bit

    return 0;
}
