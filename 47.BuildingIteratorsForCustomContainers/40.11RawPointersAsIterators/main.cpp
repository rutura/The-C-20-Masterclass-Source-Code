#include "boxcontainer.h"
#include <algorithm>
#include <ranges>
#include <vector>


template<typename T> void print(const BoxContainer<T> &c)
{
  for (auto i : c) {// Computation happens here.
    fmt::print("{} ", i);
  }
  fmt::println("");
}

int main()
{

  BoxContainer<int> vi;
  vi.add(5);
  vi.add(1);
  vi.add(7);
  vi.add(2);
  vi.add(5);
  vi.add(3);
  vi.add(7);
  vi.add(9);
  vi.add(6);

  const BoxContainer<int> copy(vi);

  // Printing a const container
  fmt::print("data : ");
  for (auto it = copy.begin(); it != copy.end(); ++it) { fmt::print("{} ", (*it)); }
  fmt::println("");

  // Printing throgh a function
  fmt::print("copy : ");
  print(copy);


  // Attempt to sort copy
  // std::ranges::sort(copy); // Compiler error. Can't sort a const collection
  std::ranges::sort(vi);

  fmt::print("vi : ");
  print(vi);


  fmt::print("view taking only 3 : ");
  for (auto i : std::views::take(vi, 3)) { fmt::print("{} ", i); }
  fmt::println("");

  fmt::print("End!");


  return 0;
}