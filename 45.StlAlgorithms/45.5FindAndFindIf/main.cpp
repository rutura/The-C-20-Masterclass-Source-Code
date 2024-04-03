#include <algorithm>
#include <fmt/format.h>
#include <vector>

int main()
{

  // int n = 23;
  int n = 24;

  std::vector<int> collection{ 14, 24, 72, 8, 98, 112 };

  auto result = std::find(std::begin(collection), std::end(collection), n);

  if (result != std::end(collection)) {
    fmt::println("collection contains: {}", n);
  } else {
    fmt::println("collection does not contain: {}", n);
  }

  fmt::println("------------");

  auto odd = [](int x) {
    if ((x % 2) != 0) return true;
    return false;
  };

  auto odd_n_position = std::find_if(std::begin(collection), std::end(collection), odd);

  if (odd_n_position != std::end(collection)) {
    fmt::println("collection contains at least one odd number : {}", *odd_n_position);
  } else {
    fmt::println("collection does not contain any odd number");
  }

  return 0;
}