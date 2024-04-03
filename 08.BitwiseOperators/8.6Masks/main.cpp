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

  // Highlight position for bit of interest with a 1
  // Mask other positions with 0

  const unsigned char mask_bit_0{ 0b00000001 };// Bit0
  const unsigned char mask_bit_1{ 0b00000010 };// Bit1
  const unsigned char mask_bit_2{ 0b00000100 };// Bit2
  const unsigned char mask_bit_3{ 0b00001000 };// Bit3
  const unsigned char mask_bit_4{ 0b00010000 };// Bit4
  const unsigned char mask_bit_5{ 0b00100000 };// Bit5
  const unsigned char mask_bit_6{ 0b01000000 };// Bit6
  const unsigned char mask_bit_7{ 0b10000000 };// Bit7

  // Sandbox variable
  unsigned char var{ 0b00000000 };// Starts off all bits off

  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);

  // Set a few bits : make them 1's regardless of what's in there

  // SETTING BITS
  // Setting : |= with mask of the bit

  // Set bit 1
  fmt::println("Setting bit in position 1");
  var |= mask_bit_1;
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);

  // Set bit 5
  fmt::println("Setting bit in position 5");
  var |= mask_bit_5;
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);

  // RESETTING BITS : set to 0
  // Resetting : &= (~mask)

  // Reset bit 1
  fmt::println("Resetting bit in position 1");
  var &= (~mask_bit_1);
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);

  // Reset bit 5
  fmt::println("Resetting bit in position 1");
  var &= (~mask_bit_5);
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);

  // Set all bits
  fmt::println("Setting all bits");
  var |= (mask_bit_0 | mask_bit_1 | mask_bit_2 | mask_bit_3 | mask_bit_4 | mask_bit_5 | mask_bit_6 | mask_bit_7);
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);


  // Reset bits at pos 0,2,4,6
  fmt::println("Reset bits at pos 0,2,4,6");
  var &= ~(mask_bit_0 | mask_bit_2 | mask_bit_4 | mask_bit_6);
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);


  // Check state of a bit
  fmt::println("Checking the state of each bit position (on/off)");
  fmt::println("bit0 is {}", ((var & mask_bit_0) >> 0));
  fmt::println("bit1 is {}", ((var & mask_bit_1) >> 1));
  fmt::println("bit2 is {}", ((var & mask_bit_2) >> 2));
  fmt::println("bit3 is {}", ((var & mask_bit_3) >> 3));
  fmt::println("bit4 is {}", ((var & mask_bit_4) >> 4));
  fmt::println("bit5 is {}", ((var & mask_bit_5) >> 5));
  fmt::println("bit6 is {}", ((var & mask_bit_6) >> 6));
  fmt::println("bit6 is {}", static_cast<bool>(var & mask_bit_6));

  fmt::println("bit7 is {}", ((var & mask_bit_7) >> 7));
  fmt::println("bit7 is {}", static_cast<bool>(var & mask_bit_7));


  // Toggle bits
  // Toggle : var ^ mask

  // Toggle bit 0
  fmt::println("Toggle bit 0");
  var ^= mask_bit_0;
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);


  // Toggle bit7
  fmt::println("Toggle bit 7");
  var ^= mask_bit_7;
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);


  // Toggle multiple bits in one go : the 4 higher bits
  fmt::println("Toggle multiple bits in one go : the 4 higher bits");
  var ^= (mask_bit_7 | mask_bit_6 | mask_bit_5 | mask_bit_4);
  fmt::println("{:>{}} var : {:>{}}", " ", COLUMN_WIDTH / 2, std::bitset<8>(var).to_string(), COLUMN_WIDTH);


  return 0;
}