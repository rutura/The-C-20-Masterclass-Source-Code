module;
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void number_systems(){
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

export void print_type_ranges()
{
  // Ranges
  fmt::println(
    "The range for short is from {} to {}", std::numeric_limits<short>::min(), std::numeric_limits<short>::max());
  fmt::println("The range for unsigned short is from {} to {}",
    std::numeric_limits<unsigned short>::min(),
    std::numeric_limits<unsigned short>::max());
  fmt::println("The range for int is from {} to {}", std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
  fmt::println("The range for unsigned int is from {} to {}",
    std::numeric_limits<unsigned int>::min(),
    std::numeric_limits<unsigned int>::max());
  fmt::println(
    "The range for long is from {} to {}", std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
  fmt::println(
    "The range for float is from {} to {}", std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
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

export void represent_float(float &num)
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