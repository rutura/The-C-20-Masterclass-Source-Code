#include "utilities.h"
#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void is_al_num()
{
  // Check if character is alphanumeric
  fmt::println("");
  fmt::println("std::isalnum : ");

  fmt::println("C is alphanumeric : {}", std::isalnum('C'));
  fmt::println("^ is alphanumeric : {}", std::isalnum('^'));

  //Can use this as a test condition
  char input_char{ '*' };
  if (std::isalnum(input_char)) { fmt::println("{} is alhpanumeric.", input_char); } else {
    fmt::println("{} is not alphanumeric.", input_char);
  }
}

void is_alphabetic()
{
  // Check if character is alphabetic
  fmt::println("");
  fmt::println("std::isalpha : ");
  fmt::println("C is alphabetic : {}", std::isalpha('e'));// 1
  fmt::println("^ is alphabetic : {}", std::isalpha('^'));// 0
  fmt::println("7 is alphabetic : {}", std::isalpha('7'));// 0

  if (std::isalpha('e')) { fmt::println("e is alphabetic"); } else { fmt::println("e is NOT alphabetic"); }
}

void is_blank()
{
  // Check if a character is blank
  fmt::println("std::isblank: ");
  char message[]{ "Hello there. How are you doing? The sun is shining." };
  fmt::println("message : {}", message);

  //Find and print blank index
  size_t blank_count{};
  for (size_t i{ 0 }; i < std::size(message); ++i) {
    //fmt::println( "Value : " << message[i] );
    if (std::isblank(message[i])) {
      fmt::println("Found a blank character at index : [{}]", i);
      ++blank_count;
    }
  }
  fmt::println("In total, we found {} blank characters.", blank_count);
}

void is_upercase()
{
  // Check if character is lowercase or uppercase
  fmt::println("std::islower and std::isupper : ");
  fmt::println("");
  char thought[]{ "The C++ programming language is one of the most used on the planet." };
  size_t lowercase_count{};
  size_t upppercase_count{};

  //Print original string for ease of comparison on the terminal
  fmt::println("Original string  : {}", thought);

  for (auto character : thought) {
    if (std::islower(character)) {
      fmt::print("{} ", character);
      ++lowercase_count;
    }
    if (std::isupper(character)) { ++upppercase_count; }
  }
  fmt::println("");
  fmt::println("Found {} lowercase characters and {} uppercase characters.", lowercase_count, upppercase_count);
}

void is_digit()
{
  // Check if a character is a digit
  fmt::println("");
  fmt::println("std::isdigit : ");

  char statement[]{ "Mr Hamilton owns 221 cows. That's a lot of cows! The kid exclamed." };
  fmt::println("statement : {}", statement);

  size_t digit_count{};

  for (auto character : statement) {
    if (std::isdigit(character)) {
      fmt::println("Found digit : {}", character);
      ++digit_count;
    }
  }
  fmt::println("Found {} digits in the statement string", digit_count);
}

void change_to_lowercase()
{
  // Turning a character to lowercase using the std::tolower() function
  fmt::println("");
  fmt::println("std::tolwer and std::toupper: ");
  char original_str[]{ "Home. The feeling of belonging" };
  char dest_str[std::size(original_str)];

  // Turn this to uppercase. Change the array in place
  for (size_t i{}; i < std::size(original_str); ++i) { dest_str[i] = std::toupper(original_str[i]); }

  fmt::println("Original string: {}", original_str);
  fmt::println("Uppercase string: {}", dest_str);

  // Turn this to lowercase. Change the array in place
  for (size_t i{}; i < std::size(original_str); ++i) { dest_str[i] = std::tolower(original_str[i]); }
  fmt::println("Lowercase string: {}", dest_str);
}