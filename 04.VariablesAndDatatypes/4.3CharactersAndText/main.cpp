/*
        . Experiment with with raw characters
        . Experiment with collections of characters
            . First using std::vector and std::array
            . Taking a chance to introduce those collections
        . Introduce std::string as the more appropriate type to use for strings

*/

#include <array>
#include <fmt/format.h>
#include <string>
#include <vector>

int main()
{
  // Raw characters
  char character1{ 'a' };
  char character2{ 'r' };
  char character3{ 'r' };
  char character4{ 'o' };
  char character5{ 'w' };

  fmt::println("{}", character1);
  fmt::println("{}", character2);
  fmt::println("{}", character3);
  fmt::println("{}", character4);
  fmt::println("{}", character5);

  // One byte in memory: 2^8 = 256 different values (0 ~ 255)

  char value = 65;// ASCII character code for 'A'
  fmt::println("value : {}", value);// A
  fmt::println("value(int) : {}", static_cast<int>(value));

  // Collections of characters
  fmt::println("------Collections of characters------");
  // const std::vector<char> characters {'a', 'r', 'r', 'o', 'w'};
  const std::array<char, 5> characters{ 'a', 'r', 'r', 'o', 'w' };
  fmt::println("{}", characters[0]);
  fmt::println("{}", characters[1]);
  fmt::println("{}", characters[2]);
  fmt::println("{}", characters[3]);
  fmt::println("{}", characters[4]);

  // Print all characters in one go: compiler error.
  // fmt::println("{},characters");

  // Using std::string
  fmt::println("Printing the string");
  std::string message{ "arrow" };
  fmt::println("{}", message);


  // Doing more stuff with std::string
  std::string greeting{ "Hello" };
  greeting.append(" there");
  fmt::println("{}", greeting);
  return 0;
}