#include "utilities.h"

#include <fmt/format.h>
#include <string>

void print_msg(std::string_view msg) { fmt::print("{}\n", msg); }

void do_work()
{
  // 1. Basic Declaration and Initialization
  // Declaring a std::string and initializing it with a literal
  std::string str1 = "Hello, World!";
  fmt::println("str1: {}", str1);


  // 2. Using Constructors
  // Creating a std::string using various constructors
  std::string str2(str1);// Copy constructor
  std::string str3(str1, 7, 5);// Substring constructor: start at index 7, length 5
  std::string str4(10, 'A');// Fill constructor: 10 characters of 'A'
  fmt::println("str2: {}", str2);
  fmt::println("str3: {}", str3);
  fmt::println("str4: {}", str4);

  // 3. Accessing Characters
  // Accessing individual characters using the [] operator and at() method
  fmt::println("First character of str1: {}", str1[0]);
  fmt::println("Second character of str1 using at(): {}", str1.at(1));

  // 4. Modifying Strings
  // Modifying characters in the string
  str1[0] = 'h';
  str1.at(7) = 'w';
  fmt::println("Modified str1: {}", str1);

  // 5. Appending and Concatenation
  // Appending to a string using operator+= and append()
  str1 += " How are you?";
  str2.append(" Goodbye!");
  fmt::println("Appended str1: {}", str1);
  fmt::println("Appended str2: {}", str2);

  // Concatenating strings using operator+
  std::string str5 = str3 + " Everyone!";
  fmt::println("Concatenated str5: {}", str5);

  // 6. Substrings
  // Extracting a substring using substr()
  std::string subStr = str1.substr(7, 5);// Start at index 7, length 5
  fmt::println("Substring of str1: {}", subStr);

  // 7. Finding Substrings
  // Finding a substring within a string using find()
  size_t pos = str1.find("World");
  if (pos != std::string::npos) { fmt::println("'World' found at position: {}", pos); } else {
    fmt::println("'World' not found");
  }

  // 8. Comparison
  // Comparing strings using compare()
  if (str1.compare(str2) == 0) { fmt::println("str1 is equal to str2"); } else {
    fmt::println("str1 is not equal to str2");
  }

  // 9. Inserting and Erasing
  // Inserting a substring into a string
  str1.insert(5, ", Beautiful");
  fmt::println("After insertion: {}", str1);

  // Erasing a part of the string
  str1.erase(5, 11);// Erase 11 characters starting from index 5
  fmt::println("After erasing: {}", str1);

  // 10. Length and Capacity
  // Getting the length and capacity of a string
  fmt::println("Length of str1: {}", str1.length());
  fmt::println("Capacity of str1: {}", str1.capacity());

  // 12. Iterating over a string
  // Using range-based for loop to iterate over a string
  fmt::print("Characters in str1: ");
  for (const auto &ch : str1) { fmt::print("{} ", ch); }
  fmt::print("\n");

  // 13. Clearing a string
  // Clearing the contents of a string
  str1.clear();
  fmt::println("Cleared str1, new length: {}", str1.length());

}