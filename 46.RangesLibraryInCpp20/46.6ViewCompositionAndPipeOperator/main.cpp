#include <fmt/format.h>
#include <map>
#include <ranges>
#include <vector>

void print(auto view)
{
  for (auto i : view) {// Computation happens here.
    fmt::print("{} ", i);
  }
  fmt::println("");
}


int main()
{

  std::vector<int> vi{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  // Filter out evens and square them out.
  fmt::print("vi : ");
  print(vi);
  // V1 : Raw function composition
  auto even = [](int n) { return n % 2 == 0; };
  auto my_view = std::views::transform(std::views::filter(vi, even), [](auto n) { return n *= n; });
  fmt::print("vi transformed : ");
  print(my_view);

  fmt::println("");
  fmt::println("Pipe operator : ");
  auto my_view1 = vi | std::views::filter(even) | std::views::transform([](auto n) { return n *= n; });
  fmt::print("vi transformed : ");
  print(my_view1);


  // classroom done as map : Keys are sorted by default
  // std::unordered_map<std::string,unsigned int> classroom    {
  std::map<std::string, unsigned int> classroom{
    { "John", 11 }, { "Mary", 17 }, { "Steve", 15 }, { "Lucy", 14 }, { "Ariel", 12 }
  };

  // Print out the names
  // auto names_view = std::views::keys(classroom);
  auto names_view = classroom | std::views::keys;
  fmt::println("names : ");
  fmt::print("{}\n", fmt::join(names_view | std::views::common, " "));
  // std::ranges::copy(names_view, std::ostream_iterator<std::string>(std::cout, " "));


  // Print out the ages :
  fmt::println("");
  auto ages_view = std::views::values(classroom);
  fmt::print("ages : ");
  fmt::print("{}\n", fmt::join(ages_view | std::views::common, " "));
  // std::ranges::copy(ages_view,std::ostream_iterator<unsigned int>(std::cout," "));


  // Print names in reverse : this doesn't work if you store the data in an
  // unordered_map. The reason in the unoredered_map doesn't have reverse iterators,
  // that are needed to set up a reverse view.
  fmt::println("");
  fmt::print("names in reverse : ");
  fmt::print("{}\n", fmt::join(std::views::keys(classroom) | std::views::reverse, " "));
  /*std::ranges::copy(std::views::keys(classroom) | std::views::reverse ,
                              std::ostream_iterator<std::string>(std::cout, " "));*/

  // Pick names that come before the letter "M" in the alphabet
  fmt::println("");
  auto before_M = [](const std::string &name) {
    return (static_cast<unsigned char>(name[0]) < static_cast<unsigned char>('M'));
  };

  fmt::print("names before M : ");
  fmt::print("{}\n", fmt::join(classroom | std::views::keys | std::views::filter(before_M), " "));
  /*std::ranges::copy(classroom | std::views::keys | std::views::filter(before_M),
             std::ostream_iterator<std::string>(std::cout, " "));*/

  return 0;
}