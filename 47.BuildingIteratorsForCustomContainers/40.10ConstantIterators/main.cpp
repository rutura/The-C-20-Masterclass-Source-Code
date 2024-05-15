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

  fmt::print("data : ");
  for (auto it = copy.begin(); it != copy.end(); ++it) { fmt::print("{} ", (*it)); }
  fmt::println("");


  // print(copy);


  return 0;
}