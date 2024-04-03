#include <fmt/format.h>

int main()
{

  int scores[10]{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

  // Array index notation
  //     int * pointer1 {&scores[0]};
  //     int * pointer2 {&scores[8]};

  // Pointer arithmetic notation
  int *pointer1{ scores + 0 };
  int *pointer2{ scores + 8 };

  fmt::println("pointer2 - pointer1 : {}", pointer2 - pointer1);// 8
  fmt::println("pointer1 - pointer2 : {}", pointer1 - pointer2);// -8


  std::ptrdiff_t pos_diff = pointer2 - pointer1;
  std::ptrdiff_t neg_diff = pointer1 - pointer2;
  fmt::println("pointer2 - pointer1 : {}", pos_diff);// 8
  fmt::println("pointer1 - pointer2 : {}", neg_diff);// -8
  fmt::println("sizeof(std::ptrdiff_t) : {}", sizeof(std::ptrdiff_t));

  return 0;
}