#include <algorithm>
#include <fmt/format.h>
#include <set>
#include <vector>


struct Sum
{
  void operator()(int n) { sum += n; }
  int sum{ 0 };
};


int main()
{

  std::vector<int> nums{ 3, 4, 2, 8, 15, 267 };
  // int nums[]{3, 4, 2, 8, 15, 267};
  // std::set<int> nums{3, 4, 2, 8, 15, 267};

  auto print = [](const int &n) { fmt::print(" {}", n); };

  // Print each elt in the collection : lambda function predicate
  std::for_each(std::begin(nums), std::end(nums), print);
  fmt::println("");

  fmt::println("---------------------------------");

  // Predicate that modifies elements in place
  std::for_each(std::begin(nums), std::end(nums), [](int &n) { n++; });

  // Print
  std::for_each(std::begin(nums), std::end(nums), print);
  fmt::println("");


  fmt::println("---------------------------------");

  // Capturing result through stateful functor that's returned
  //  calls Sum::operator() for each number
  Sum s;
  s = std::for_each(std::begin(nums), std::end(nums), s);
  fmt::println("result : {}", s.sum);

  fmt::println("---------------------------------");

  // Using a lambda that captures a local variables by ref and modifies it.
  int our_result{ 0 };
  std::for_each(std::begin(nums), std::end(nums), [&our_result](int n) { our_result += n; });
  fmt::println("result : {}", our_result);

  return 0;
}