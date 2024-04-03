#include <array>
#include <fmt/format.h>
#include <vector>

template<typename T> void print_collection(const T &collection)
{

  auto it = collection.begin();

  fmt::print(" [");
  while (it != collection.end()) {
    fmt::print(" {}", *it);
    ++it;
  }
  fmt::println("]");
}


int main()
{

  std::vector ints1{ 11, 22, 33, 44 };
  std::array ints2{ 100, 200, 300, 400 };

  auto it_begin = ints1.begin();
  auto it_end = ints1.end();

  fmt::println("first elt : {}", *it_begin);
  fmt::println("it == end_it : {}", (it_begin == it_end));

  ++it_begin;
  fmt::println("second elt : {}", *it_begin);
  fmt::println("it == end_it : {}", (it_begin == it_end));

  ++it_begin;
  fmt::println("third elt : {}", *it_begin);
  fmt::println("it == end_it : {}", (it_begin == it_end));

  ++it_begin;
  fmt::println("fourth elt : {}", *it_begin);
  fmt::println("it == end_it : {}", (it_begin == it_end));


  ++it_begin;
  fmt::println("junk elt : {}", *it_begin);
  fmt::println("it == end_it : {}", (it_begin == it_end));// true


  fmt::println("--------");
  fmt::print("ints1 : ");
  print_collection(ints1);

  fmt::print("ints2 :");
  print_collection(ints2);


  return 0;
}