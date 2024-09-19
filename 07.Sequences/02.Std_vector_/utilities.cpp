#include "utilities.h"

#include <fmt/format.h>
#include <vector>

void print_msg(std::string_view msg) { fmt::print("{}\n", msg); }

void do_work()
{
  //1.Declaration and initialization
  std::vector<int> vec = { 1, 2, 3, 4, 5 };

  // Accessing elements using []
  for (size_t i = 0; i < vec.size(); ++i) { fmt::println("vec[{}] = {}", i, vec[i]); }

  //2. Accessing elements using at()
  // std::vector<int> vec = { 1, 2, 3, 4, 5 };

  // Accessing elements using at() method
  for (size_t i = 0; i < vec.size(); ++i) { fmt::println("vec.at({}) = {}", i, vec.at(i)); }

  //3. Modifying elements in the vector
  // std::vector<int> vec = { 1, 2, 3, 4, 5 };
  vec[0] = 10;
  vec.at(1) = 20;

  // Printing modified vector
  for (size_t i = 0; i < vec.size(); ++i) { fmt::println("vec[{}] = {}", i, vec[i]); }

  //4. Using range based for loop
  /*
  std::vector<int> vec = {1, 2, 3, 4, 5};

  for (const auto& element : vec) {
      fmt::print("{} ", element);
  }
  fmt::print("\n");
  */


  //5.Filling a vector with a value
  /*
  // std::vector doesn't have a fill() method. We can use std::fill() algorithm to fill a vector with a value.
  std::vector<int> vec(5); // Vector initialized with default values

  // Filling vector with a single value
  std::fill(vec.begin(), vec.end(), 7);

  for (const auto& element : vec) {
      fmt::print("{} ", element);
  }
  fmt::print("\n");
  */

  //6. Accessing the first and last elements
  /*
  std::vector<int> vec = {1, 2, 3, 4, 5};

  fmt::println("First element: {}", vec.front());
  fmt::println("Last element: {}", vec.back());
  */

  //7. Multi-dimensional: 2D vector (3x2)
  /*
  std::vector<std::vector<int>> vec = {{1, 2}, {3, 4}, {5, 6}};

  for (const auto& row : vec) {
      for (const auto& element : row) {
          fmt::print("{} ", element);
      }
      fmt::print("\n");
  }
  */

  //8. Comparing vectors
  /*
  std::vector<int> vec1 = {1, 2, 3};
  std::vector<int> vec2 = {1, 2, 3};
  std::vector<int> vec3 = {1, 2, 4};
  std::vector<int> vec4 = {0, 2, 3};

  // Comparing vectors for equality
  if (vec1 == vec2) {
      fmt::println("vec1 is equal to vec2");
  } else {
      fmt::println("vec1 is not equal to vec2");
  }

  // Comparing vectors for inequality
  if (vec1 != vec3) {
      fmt::println("vec1 is not equal to vec3");
  } else {
      fmt::println("vec1 is equal to vec3");
  }
  // Lexicographical comparison
  if (vec1 < vec3) {
      fmt::println("vec1 is less than vec3");
  } else {
      fmt::println("vec1 is not less than vec3");
  }

  if (vec1 <= vec2) {
      fmt::println("vec1 is less than or equal to vec2");
  } else {
      fmt::println("vec1 is not less than or equal to vec2");
  }

  if (vec3 > vec4) {
      fmt::println("vec3 is greater than vec4");
  } else {
      fmt::println("vec3 is not greater than vec4");
  }

  if (vec3 >= vec1) {
      fmt::println("vec3 is greater than or equal to vec1");
  } else {
      fmt::println("vec3 is not greater than or equal to vec1");
  }
  */

  //9. Assigning one vector to another
  /*
  std::vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {6, 7, 8, 9, 10};

  // Printing original vectors
  fmt::println("Original vec1: ");
  for (const auto& element : vec1) {
      fmt::print("{} ", element);
  }
  fmt::print("\n");

  fmt::println("Original vec2: ");
  for (const auto& element : vec2) {
      fmt::print("{} ", element);
  }
  fmt::print("\n");

  // Assigning vec2 to vec1
  vec1 = vec2;

  // Printing vectors after assignment
  fmt::println("vec1 after assignment: ");
  for (const auto& element : vec1) {
      fmt::print("{} ", element);
  }
  fmt::print("\n");

  fmt::println("vec2 after assignment: ");
  for (const auto& element : vec2) {
      fmt::print("{} ", element);
  }
  fmt::print("\n");
  */

}