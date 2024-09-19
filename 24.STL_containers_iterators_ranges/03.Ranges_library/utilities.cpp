#include "utilities.h"
#include"ranges_library_01.h"
#include "ranges_library_02.h"
#include "ranges_library_03.h"
#include "ranges_library_04.h"
#include "ranges_library_05.h"

#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ranges>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void ranges_library_01_demo()
{

  std::vector<int> numbers{ 11, 2, 6, 4, 8, 3, 17, 9 };
  ranges_library_01::print_collection(numbers);

  // std::ranges::all_of()
  fmt::println("");
  fmt::print("std::ranges::all_of(): ");

  auto odd = [](int n) { return n % 2 != 0; };

  auto result = std::ranges::all_of(numbers, odd);

  if (result) { fmt::print("All elements in numbers are odd"); } else {
    fmt::print("Not all elements in numbers are odd");
  }


  // For each
  fmt::println("");
  fmt::print("std::ranges::for_each(): ");
  ranges_library_01::print_collection(numbers);
  std::ranges::for_each(numbers, [](int &n) { n *= 2; });
  ranges_library_01::print_collection(numbers);


  // Sort
  fmt::println("");
  fmt::print("std::ranges::sort(): ");
  ranges_library_01::print_collection(numbers);
  std::ranges::sort(numbers);
  ranges_library_01::print_collection(numbers);


  // Find
  fmt::println("");
  fmt::print("std::ranges::find(): ");
  auto odd_n_position = std::ranges::find_if(numbers, odd);

  if (odd_n_position != std::end(numbers)) {
    fmt::print("numbers contains at least one odd number: {}", *odd_n_position);
  } else { fmt::print("numbers does not contain any odd number"); }


  // Important, copying into outputstream on the fly
  fmt::println("");
  fmt::print("numbers: ");
  fmt::print("{}\n", fmt::join(numbers | std::views::common, " "));
  // std::ranges::copy(numbers,std::ostream_iterator<int>(std::cout, " "));

}


void ranges_library_02_demo()
{

  std::vector<int> numbers{ 11, 2, 6, 4, 8, 3, 17, 9 };
  ranges_library_02::print_collection(numbers);

  // std::ranges::all_of()
  fmt::println("");
  fmt::println("std::ranges::all_of() : ");

  auto odd = [](int n) { return n % 2 != 0; };

  // Ranges, iterator pair
  auto result = std::ranges::all_of(numbers.begin(), numbers.end(), odd);

  if (result) { fmt::println("All elements in numbers are odd"); } else {
    fmt::println("Not all elements in numbers are odd");
  }


  // For each
  fmt::println("");
  fmt::println("std::ranges::for_each() : ");
  ranges_library_02::print_collection(numbers);
  std::ranges::for_each(numbers.begin(), numbers.end(), [](int &n) { n *= 2; });
  ranges_library_02::print_collection(numbers);


  // Sort
  fmt::println("");
  fmt::println("std::ranges::sort() : ");
  ranges_library_02::print_collection(numbers);
  std::ranges::sort(numbers.begin(), numbers.end());
  ranges_library_02::print_collection(numbers);

  // Find
  fmt::println("");
  fmt::println("std::ranges::find() : ");
  auto odd_n_position = std::ranges::find_if(numbers.begin(), numbers.end(), odd);

  if (odd_n_position != std::end(numbers)) {
    fmt::println("numbers contains at least one odd number : {}", *odd_n_position);
  } else { fmt::println("numbers does not contain any odd number"); }

  // Copy to the output stream
  fmt::println("");
  fmt::print("numbers : ");
  // std::ranges::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(std::cout, " "));
  fmt::print("{}\n", fmt::join(numbers | std::views::common, " "));


  // Why you should prefer std::ranges algorithms from now on
  fmt::println("");
  std::vector<int> numbers_list{ 11, 2, 6, 4, 8, 3, 17, 9 };
  fmt::print("numbers_list : ");
  ranges_library_02::print_collection(numbers_list);

  std::ranges::sort(numbers_list.begin(), numbers_list.end());

}

void ranges_library_03_demo()
{
  //Projections : usually the sorting is done based on operator<
  //but you get one chance to write operator <
  //sometimes you want to sort things based on another scheme or
  //member variable other than the one used by operator<
  //You can do that with projections. For example, sorting based on y
  // for Point can be achieved with a y projection as shown in this example

  std::cout << "\n";
  std::cout << "Sorting points (default : based on length) : " << "\n";
  std::vector<ranges_library_03::Point> points{ { 10, 90 }, { 30, 70 }, { 20, 80 } };

  ranges_library_03::print_collection(points);

  //Sorting with the default comparator
  std::ranges::sort(points, std::less<>{});// Default sort based on distance
  ranges_library_03::print_collection(points);


  //Sorting with a projection : The data is passed into the projection before
  //it's passed into the comparator. std::less<> is going to compare two doubles
  //instead of comparing two Points.
  std::cout << "\n";
  std::cout << "projection on Point::m_x : " << "\n";
  ranges_library_03::print_collection(points);
  std::ranges::sort(points, std::less<>{}, [](auto const &p) { return p.m_x; });
  ranges_library_03::print_collection(points);


  //Projecting with direct member variable
  std::cout << "\n";
  std::cout << "projection on Point::m_y with direct member variables : " << "\n";
  ranges_library_03::print_collection(points);
  std::ranges::sort(points, std::less<>{}, &ranges_library_03::Point::m_y);
  ranges_library_03::print_collection(points);


  //Projections with for_each
  std::cout << "\n";
  std::cout << "Projections with for_each : " << "\n";

  auto print = [](const auto &n) { std::cout << " " << n; };
  using pair = std::pair<int, std::string>;
  std::vector<pair> pairs{ { 1, "one" }, { 2, "two" }, { 3, "tree" } };

  std::cout << "project the pair::first: ";
  std::ranges::for_each(pairs, print, [](const pair &p) { return p.first; });
  std::cout << "\n";

  std::cout << "project the pair::first: ";
  std::ranges::for_each(pairs, print, &pair::first);
  std::cout << "\n";

  std::cout << "project the pair::second: " << "\n";
  std::ranges::for_each(pairs, print, [](const pair &p) { return p.second; });
  std::cout << "\n";

}

void ranges_library_04_demo()
{

  std::vector<int> vi{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  // std::ranges::filter_view
  fmt::println("");
  fmt::println("std::ranges::filter_view : ");
  auto evens = [](int i) { return (i % 2) == 0; };
  fmt::print("vi : ");
  ranges_library_04::print(vi);
  std::ranges::filter_view v_evens = std::ranges::filter_view(vi, evens);// No computation
  fmt::print("vi evens : ");
  ranges_library_04::print(v_evens);// Computation happens in the print function
  // Print evens on the fly
  fmt::print("vi evens : ");
  ranges_library_04::print(std::ranges::filter_view(vi, evens));
  // Print odds on the fly
  fmt::print("vi odds : ");
  ranges_library_04::print(std::ranges::filter_view(vi, [](int i) { return (i % 2) != 0; }));

  fmt::print("vi : ");
  ranges_library_04::print(vi);


  // std::ranges::transform_view
  fmt::println("");
  fmt::println("std::ranges::transform_view : ");
  std::ranges::transform_view v_transformed = std::ranges::transform_view(vi, [](int i) { return i * 10; });
  fmt::print("vi : ");
  ranges_library_04::print(vi);
  fmt::println("vi transformed : ");
  ranges_library_04::print(v_transformed);
  fmt::print("vi : ");
  ranges_library_04::print(vi);


  // std::ranges::take_view
  fmt::println("");
  fmt::println("std::ranges::take_view : ");
  std::ranges::take_view v_taken = std::ranges::take_view(vi, 5);
  fmt::print("vi : ");
  ranges_library_04::print(vi);
  fmt::println("vi taken : ");
  ranges_library_04::print(v_taken);


  // is met
  fmt::println("");
  fmt::println("std::views::take_while : ");
  vi = { 1, 11, 23, 131, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::ranges::take_while_view v_taken_while = std::ranges::take_while_view(vi, [](int i) { return (i % 2) != 0; });
  fmt::print("vi : ");
  ranges_library_04::print(vi);
  fmt::println("vi taken_while : ");
  ranges_library_04::print(v_taken_while);


  // std::ranges::drop_view : drop n first elements
  fmt::println("");
  fmt::println("std::ranges::drop_view : ");
  vi = { 1, 11, 23, 131, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::ranges::drop_view v_drop = std::ranges::drop_view(vi, 5);
  fmt::print("vi : ");
  ranges_library_04::print(vi);
  fmt::println("vi_drop : ");
  ranges_library_04::print(v_drop);


  // std::views::drop_while_view : drops elements as long as the predicate is met
  fmt::println("");
  fmt::println("std::ranges::drop_while_view : ");
  vi = { 1, 11, 23, 4, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::ranges::drop_while_view v_drop_while = std::ranges::drop_while_view(vi, [](int i) { return (i % 2) != 0; });
  fmt::print("vi : ");
  ranges_library_04::print(vi);
  fmt::println("v_drop_while : ");
  ranges_library_04::print(v_drop_while);


  // std::ranges::keys_view and std::ranges_value_view
  // Compiler error which I don't understand the reason for yet.

  fmt::println("");
  using pair = std::pair<int, std::string>;
  std::vector<pair> numbers{ { 1, "one" }, { 2, "two" }, { 3, "tree" } };

  // Compiler error when you build views explicitly. Don't understand why yet
  // auto k_view = std::ranges::keys_view(numbers);
  // auto v_view = std::ranges::values_view(numbers);

  auto k_view = std::views::keys(numbers);
  auto v_view = std::views::values(numbers);
  ranges_library_04::print(k_view);
  ranges_library_04::print(v_view);


  vi = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  // std::views::filter()
  fmt::println("");
  fmt::println("std::views::filter : ");
  auto evens1 = [](int i) { return (i % 2) == 0; };
  fmt::print("vi : ");
  ranges_library_04::print(vi);
  std::ranges::filter_view v_evens1 = std::views::filter(vi, evens1);// No computation
  fmt::print("vi evens : ");
  ranges_library_04::print(v_evens1);// Computation happens in the print function
  // Print evens on the fly
  fmt::print("vi evens : ");
  ranges_library_04::print(std::views::filter(vi, evens1));
  // Print odds on the fly
  fmt::print("vi odds : ");
  ranges_library_04::print(std::views::filter(vi, [](int i) { return (i % 2) != 0; }));


  // Students example
  fmt::println("");
  fmt::println("students example : ");

  std::vector<ranges_library_04::Student> class_room{ { "Mike", 12 }, { "John", 17 }, { "Drake", 14 }, { "Mary", 16 } };

  fmt::println("");
  fmt::println("classroom : ");
  for (auto &s : class_room) { std::cout << s << " "; }

  std::ranges::sort(class_room, std::less<>{}, &ranges_library_04::Student::m_age);

  fmt::println("");
  fmt::println("classroom (after sort) : ");
  for (auto &s : class_room) { std::cout << s << " "; }

  fmt::println("students under 15 : ");
  ranges_library_04::print(std::views::take_while(class_room,
    [](const ranges_library_04::Student &s) { return (s.m_age < 15); }));

}


void ranges_library_05_demo()
{

  std::vector<int> vi{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  // Filter out evens and square them out.
  fmt::print("vi : ");
  ranges_library_05::print(vi);
  // V1 : Raw function composition
  auto even = [](int n) { return n % 2 == 0; };
  auto my_view = std::views::transform(std::views::filter(vi, even), [](auto n) { return n *= n; });
  fmt::print("vi transformed : ");
  ranges_library_05::print(my_view);

  fmt::println("");
  fmt::println("Pipe operator : ");
  auto my_view1 = vi | std::views::filter(even) | std::views::transform([](auto n) { return n *= n; });
  fmt::print("vi transformed : ");
  ranges_library_05::print(my_view1);


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

  //Some other views from C++23
  //std::views::zip (C++23)
  std::vector<int> v1 = { 1, 2, 3 };
  std::vector<std::string> v2 = { "one", "two", "three" };

  auto zipped = std::views::zip(v1, v2);

  fmt::print("std::views::zip:\n");
  for (const auto &[i, s] : zipped) { fmt::print("({}, {}) ", i, s); }
  fmt::print("\n\n");

  //std::views::adjacent (C++23)
  auto adjacent = std::views::adjacent<2>(v1);

  fmt::print("std::views::adjacent:\n");
  for (const auto &[a, b] : adjacent) { fmt::print("({}, {}) ", a, b); }
  fmt::print("\n\n");

  // std::views::chunk (C++23)
  auto chunked = std::views::chunk(v1, 2);
  fmt::print("std::views::chunk:\n");
  for (const auto &chunk : chunked) { fmt::print("{{{}}} ", fmt::join(chunk, ", ")); }
  fmt::print("\n\n");

  // std::views::stride (C++23)
  auto strided = std::views::stride(v1, 2);

  fmt::print("std::views::stride:\n");
  fmt::print("{}\n\n", fmt::join(strided, ", "));

  // std::views::cartesian_product (C++23)
  std::vector<char> v3 = { 'a', 'b', 'c' };
  auto cartesian_product = std::views::cartesian_product(v1, v3);

  fmt::print("std::views::cartesian_product:\n");
  for (const auto &[i, c] : cartesian_product) { fmt::print("({}, {}) ", i, c); }
  fmt::print("\n");
}

void ranges_library_06_demo()
{
  //Range factories
  // Generate an infinite sequence of numbers
  // auto infinite_view = std::views::iota(1) | std::views::take(20); // Stores the compuation
  // auto data_view = std::views::take( std::views::iota(1) , 20);

  // Numbers are generated lazily, on the fly, as we need them in each iteration
  for (auto i : std::views::iota(1) | std::views::take(20)) { fmt::println("{}", i); }
}