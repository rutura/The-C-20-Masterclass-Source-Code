#include <bitset>
#include <fmt/format.h>

/**
* fmt output formatting and alignment - dynamic width
* - Reference: https://fmt.dev/latest/syntax.html
  Dynamic width:

      fmt::format("{:<{}}", "left aligned", 30);
      // Result: "left aligned
*/
int main()
{

  const int COLUMN_WIDTH{ 20 };

  fmt::println("Compound bitwise assignment operators");

  unsigned char sandbox_var{ 0b00110100 };// 8 bits : positive numbers only

  // Print out initial value
  fmt::println("Initial value :  ");
  fmt::println(
    "{:>{}} sandbox_var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(sandbox_var).to_string(), COLUMN_WIDTH);

  // Compound left shift
  fmt::println("Shift left 2 bit positions in place :  ");
  sandbox_var <<= 2;
  fmt::println(
    "{:>{}} sandbox_var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(sandbox_var).to_string(), COLUMN_WIDTH);

  // Compound right shift
  fmt::println("Shift right 4 bit positions in place :  ");
  sandbox_var >>= 4;
  fmt::println(
    "{:>{}} sandbox_var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(sandbox_var).to_string(), COLUMN_WIDTH);

  // Compound OR with 0000 0010 to have all lower 4 bits turned on
  fmt::println("Compound OR with 0000 0010 :  ");
  sandbox_var |= 0b00001111;
  fmt::println(
    "{:>{}} sandbox_var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(sandbox_var).to_string(), COLUMN_WIDTH);


  // Compound AND with 0000 1100 to turn off the 2 lowest bits
  fmt::println("Compound AND with 0000 1100 :  ");
  sandbox_var &= 0b000000000;
  fmt::println(
    "{:>{}} sandbox_var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(sandbox_var).to_string(), COLUMN_WIDTH);


  // XOR with 00000011 to turn on the 4 lowest bits again
  fmt::println("Compound XOR with 0000 0011 :  ");
  sandbox_var ^= 0b00000011;
  fmt::println(
    "{:>{}} sandbox_var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(sandbox_var).to_string(), COLUMN_WIDTH);

  return 0;
}