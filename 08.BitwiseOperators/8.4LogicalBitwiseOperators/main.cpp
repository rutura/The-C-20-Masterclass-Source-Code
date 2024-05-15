#include <bitset>
#include <fmt/format.h>

/**
* fmt output formatting and alignment
* - Reference: https://fmt.dev/latest/syntax.html
  Aligning the text and specifying a width:

      fmt::format("{:<30}", "left aligned");
      // Result: "left aligned                  "
      fmt::format("{:>30}", "right aligned");
      // Result: "                 right aligned"
      fmt::format("{:^30}", "centered");
      // Result: "           centered           "
      fmt::format("{:*^30}", "centered");  // use '*' as a fill char
      // Result: "***********centered***********"
  Dynamic width:

      fmt::format("{:<{}}", "left aligned", 30);
      // Result: "left aligned
*/
int main()
{

  int COLUMN_WIDTH{ 20 };
  unsigned char value1{ 0x3 };// 0000 0011
  unsigned char value2{ 0x5 };// 0000 0101


  fmt::println("{:>{}} value1 : {:>{}} ", " ", COLUMN_WIDTH / 2, std::bitset<8>(value1).to_string(), COLUMN_WIDTH);
  fmt::println("{:>{}} value1 : {:>{}} ", " ", COLUMN_WIDTH / 2, std::bitset<8>(value2).to_string(), COLUMN_WIDTH);

  // AND
  fmt::println("Bitwise AND :  ");
  fmt::println(" {:>{}} value1 & value2 : {:>{}}",
    " ",
    COLUMN_WIDTH / 2,
    std::bitset<8>(value1 & value2).to_string(),
    COLUMN_WIDTH);

  // OR
  fmt::println("Bitwise OR :  ");
  fmt::println("{:>{}} value1 | value2 : {:>{}} ",
    " ",
    COLUMN_WIDTH / 2,
    std::bitset<8>(value1 | value2).to_string(),
    COLUMN_WIDTH);

  // NOT
  fmt::println("Bitwise NOT ");

  fmt::println("{:>{}} ~value1 : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(~value1).to_string(), COLUMN_WIDTH);

  fmt::println("{:>{}} ~value2 : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(~value2).to_string(), COLUMN_WIDTH);

  fmt::println("{:>{}} ~01011001 : {:>{}}",
    " ",
    COLUMN_WIDTH / 2,
    std::bitset<8>(~0b01011001).to_string(),
    COLUMN_WIDTH);// Using bin literal

  fmt::println("{:>{}} ~01011001 : {:>{}}",
    " ",
    COLUMN_WIDTH / 2,
    std::bitset<8>(~0x59).to_string(),
    COLUMN_WIDTH);// Using hex literal

  // XOR
  fmt::println("Bitwise XOR :");
  fmt::println("{:>{}} value1 ^ value2 : {:>{}}",
    " ",
    COLUMN_WIDTH / 2,
    std::bitset<8>(value1 ^ value2).to_string(),
    COLUMN_WIDTH);


  return 0;
}