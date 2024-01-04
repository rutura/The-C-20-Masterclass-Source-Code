/*
    Number Systems
          - Integers - OK
            - How they are represented in memory
            - The range of values they can hold
            - Signed and unsigned integers, how negative numbers are done
   through the 2's complement method, and how they can be mapped on a wheel. See
   borks zine on floats and ints. The zine is stored in ibitabo/zines
            - Play with signed and unsigned integers in code as shown below.
          - Floating points: IEEE 754
            - do a representation of float num = -343.53125f
            - you take the decimal part and represent it in binary. You can use
   a calculator to do this.
            - you then multiply the decimal part by 2 and take the integer part
   and repeat the process. You can watch https://youtu.be/MA5JB3-85jA for this.
            - for floats (32 bits) the bias is 127. Represent the number in
   memory.
            - This should show that floats are not precise.
            - Say that floats offer the precision of 7 digits while double
   offers 15 digits of precision
            - Floats allow us to store very large and very small numbers.
            - Use https://ciechanow.ski/exposing-floating-point/ as a reference
   in all this.
          - Numeric limits: How to show the ranges

*/

#include <fmt/format.h>
#include <bitset>

//Declare the function
void represent_float(float& num);

void print_type_ranges();

int main() {
  // Integers
  int number1 = 15;          // Decimal
  int number2 = 017;         // Octal
  int number3 = 0x0F;        // Hexadecimal
  int number4 = 0b00001111;  // Binary

  fmt::println("number1 : {}", number1);
  fmt::println("number2 : {}", number2);
  fmt::println("number3 : {}", number3);
  fmt::println("number4 : {}", number4);

  // Signed integers
  signed char number5 = 0b11111111;  // Binary
  fmt::println("number5 : {}", number5);

  // Floating point types
  // floats offer 7 digits of precision while double offers 15 digits of
  // precision The range of float is 1.17549e-38 to 3.40282e+38 The range of
  // double is 2.22507e-308 to 1.79769e+308 Using
  // https://ciechanow.ski/exposing-floating-point/ as a reference
  float num = -343.53125f;

  represent_float(num);

  print_type_ranges();

  return 0;
}

void print_type_ranges() {
  // Ranges
  fmt::println("The range for short is from {} to {}",
               std::numeric_limits<short>::min(),
               std::numeric_limits<short>::max());
  fmt::println("The range for unsigned short is from {} to {}",
               std::numeric_limits<unsigned short>::min(),
               std::numeric_limits<unsigned short>::max());
  fmt::println("The range for int is from {} to {}",
               std::numeric_limits<int>::min(),
               std::numeric_limits<int>::max());
  fmt::println("The range for unsigned int is from {} to {}",
               std::numeric_limits<unsigned int>::min(),
               std::numeric_limits<unsigned int>::max());
  fmt::println("The range for long is from {} to {}",
               std::numeric_limits<long>::min(),
               std::numeric_limits<long>::max());
  fmt::println("The range for float is from {} to {}",
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

void represent_float(float& num) {
  // Bit manipulation to get the binary representation
  uint32_t* numBits = reinterpret_cast<uint32_t*>(&num);

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