#include "dog.h"
#include <fmt/format.h>
#include <memory>


int main()
{

  // C++17 only : Recommended
  std::shared_ptr<int[]> shared_ptr_int_arr_1(new int[10]{ 1, 2, 3, 4, 5, 6, 7, 8 });
  std::shared_ptr<Dog[]> shared_ptr_dog_arr_1(new Dog[10]{ Dog("Dog1"), Dog("Dog2") });


  // Setting elements
  shared_ptr_int_arr_1[3] = 28;
  shared_ptr_dog_arr_1[1] = Dog("Fluzzy");

  // Read int array
  fmt::println("\n");
  fmt::println("Reading data from arrays");
  fmt::println("Reading shared_ptr_int_arr_1: ");
  for (size_t i{ 0 }; i < 10; ++i) { fmt::println("shared_ptr_int_arr_1[{}] : {}", i, shared_ptr_int_arr_1[i]); }

  fmt::println("\n");
  fmt::println("Reading shared_ptr_dog_arr_1: ");
  for (size_t i{ 0 }; i < 10; ++i) {
    fmt::println("shared_ptr_dog_arr_1[{}] : {}", i, shared_ptr_dog_arr_1[i].get_name());
  }

  return 0;
}