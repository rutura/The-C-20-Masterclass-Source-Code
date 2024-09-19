#include "utilities.h"


#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void number_systems()
{
  // Integers
  int number1 = 15;// Decimal
  int number2 = 017;// Octal
  int number3 = 0x0F;// Hexadecimal
  int number4 = 0b00001111;// Binary

  fmt::println("number1 : {}", number1);
  fmt::println("number2 : {}", number2);
  fmt::println("number3 : {}", number3);
  fmt::println("number4 : {}", number4);
}

void print_type_ranges()
{
  // Ranges
  fmt::println(
    "The range for short is from {} to {}",
    std::numeric_limits<short>::min(),
    std::numeric_limits<short>::max());
  fmt::println("The range for unsigned short is from {} to {}",
    std::numeric_limits<unsigned short>::min(),
    std::numeric_limits<unsigned short>::max());
  fmt::println("The range for int is from {} to {}", std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
  fmt::println("The range for unsigned int is from {} to {}",
    std::numeric_limits<unsigned int>::min(),
    std::numeric_limits<unsigned int>::max());
  fmt::println(
    "The range for long is from {} to {}",
    std::numeric_limits<long>::min(),
    std::numeric_limits<long>::max());
  fmt::println(
    "The range for float is from {} to {}",
    std::numeric_limits<float>::min(),
    std::numeric_limits<float>::max());
  fmt::println("The range(with lowest) for float is from {} to {}",
    std::numeric_limits<float>::lowest(),
    std::numeric_limits<float>::max());
  fmt::println("The range(with lowest) for double is from {} to {}",
    std::numeric_limits<double>::lowest(),
    std::numeric_limits<double>::max());
  fmt::println("The range(with lowest) for long double is from {} to {}",
    std::numeric_limits<long double>::lowest(),
    std::numeric_limits<long double>::max());
  fmt::println("int is signed: {}", std::numeric_limits<int>::is_signed);
  fmt::println("int digits: {}", std::numeric_limits<int>::digits);
}

/*
//Detailed explanations for later on when bit manipulation is covered:
The masks and bit shifts in your function are used to extract specific parts of the 32-bit binary representation of a floating-point number (IEEE 754 format). Let's break down how they work:
IEEE 754 Floating-Point Format (Single Precision)

A single-precision float (float) in C++ is stored as a 32-bit binary value, and it is divided into three components:

    Sign bit: 1 bit (the most significant bit).
    Exponent: 8 bits.
    Mantissa (fraction): 23 bits.

Here’s how the layout looks:

scss

| Sign (1 bit) | Exponent (8 bits) | Mantissa (23 bits) |
|--------------|-------------------|--------------------|
|    31st bit  |    30th to 23rd    |     22nd to 0th    |

The function you're using attempts to extract these parts.
1. Extracting the Sign Bit

cpp

int sign = (*numBits >> 31) & 1;

    Right shift (>> 31):
        Shifting *numBits by 31 places moves the most significant bit (bit 31) to the least significant position (bit 0).
        This isolates the sign bit, effectively shifting the 31st bit of *numBits to the rightmost position.
    Bitwise AND (& 1):
        The result is then masked with 1 (0b00000001), which leaves only the rightmost bit. This removes all other bits except the sign bit.

So, if the original number was negative, sign will be 1; otherwise, it will be 0.
2. Extracting the Exponent

cpp

int exponent = (*numBits >> 23) & 0xFF;

    Right shift (>> 23):
        Shifting by 23 bits moves the 8 exponent bits (bits 23–30) to the least significant positions (bits 0–7).
        For example, the binary representation of the exponent field is now located in the lower byte of the result.
    Bitwise AND (& 0xFF):
        The mask 0xFF (which is 0b11111111 or 255 in decimal) keeps only the 8 least significant bits and masks out everything else.
        This isolates the 8-bit exponent part.

Now, the variable exponent contains the value of the exponent field from the original float.
3. Extracting the Mantissa (Fraction)

cpp

int mantissa = *numBits & 0x7FFFFF;

    Bitwise AND (& 0x7FFFFF):
        The mask 0x7FFFFF is 0b011111111111111111111111 in binary (23 bits set to 1).
        Applying this mask retains only the 23 least significant bits (the mantissa) and discards the upper 9 bits (the sign and exponent).
        Since there is no shift, the operation directly extracts the bits 0–22, which represent the mantissa (fraction).

Thus, the mantissa variable will contain the 23-bit mantissa value from the original float.
Putting It All Together

The float representation looks like this in memory:

scss

| Sign (1 bit) | Exponent (8 bits) | Mantissa (23 bits) |

    Sign is extracted by shifting the most significant bit (31st bit) to the right and masking.
    Exponent is extracted by shifting bits 23–30 to the least significant byte (lower 8 bits) and masking out everything except those 8 bits.
    Mantissa is extracted by masking the lower 23 bits of the float without shifting.

Example

Suppose you have a float num = -5.75. Its binary representation in IEEE 754 single-precision would be:

makefile

Sign     = 1 (negative number)
Exponent = 10000001 (129 in decimal)
Mantissa = 01110000000000000000000 (which represents 1.75 in normalized form)

The function would:

    Extract the sign bit (1).
    Extract the exponent (129).
    Extract the mantissa (23 bits, representing the fractional part).

This process helps decompose the float into its constituent components (sign, exponent, and mantissa) using simple bit manipulations like shifts and masks.

*/

void represent_float(float &num)
{
  // Bit manipulation to get the binary representation
  uint32_t *numBits = reinterpret_cast<uint32_t *>(&num);

  // Extracting sign, exponent, and mantissa
  int sign = (*numBits >> 31) & 1;
  int exponent = (*numBits >> 23) & 0xFF;
  int mantissa = *numBits & 0x7FFFFF;

  // Output the components
  fmt::println("Original number: {}", num);
  fmt::println("Sign bit: {}", sign);
  fmt::println("Exponent: {:08b}", exponent);
  fmt::println("Mantissa: {:023b}", mantissa);
}