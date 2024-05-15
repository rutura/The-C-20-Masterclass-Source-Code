#include <fmt/format.h>
#include <functional>
#include <set>


class Book
{
  friend std::ostream &operator<<(std::ostream &out, const Book &operand);
  friend struct fmt::formatter<Book>;

public:
  Book(int year, std::string title) : m_year(year), m_title(title) {}
  bool operator<(const Book &right_operand) const { return this->m_year < right_operand.m_year; }

private:
  int m_year;
  std::string m_title;
};
std::ostream &operator<<(std::ostream &out, const Book &operand)
{
  out << "Book [" << operand.m_year << ", " << operand.m_title << "]";
  return out;
}

template<> struct fmt::formatter<Book>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Book &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Book [{},{}]", obj.m_year, obj.m_title);
  }
};

template<typename T> void print_collection(const T &collection)
{

  auto it = collection.begin();

  fmt::print(" Collection [");
  while (it != collection.end()) {
    fmt::print(" {}", *it);
    ++it;
  }
  fmt::println("]");
}


// Comparator functor
class IntComparator
{
public:
  bool operator()(int left, int right) const { return (left < right); }
};

// Comparator function pointer
bool compare_ints(int left, int right) { return (left < right); }


int main()
{

  // Code1 : Building sets
  std::set<int> numbers{ 11, 16, 2, 912, 15, 6, 15, 2 };// Data is ordered internally, no duplicates.
  fmt::println("");
  fmt::println("building sets (Need < operator for ordering) : ");
  print_collection(numbers);


  // Set of custom types : Need to implement operator<
  std::set<Book> books{
    Book(2000, "Cooking Food"), Book(1930, "Building Computers"), Book(1995, "Farming for Beginners")
  };

  print_collection(books);
  fmt::println("---------------------");


  // Code2 : Iterators : forward and back, and constant

  fmt::println("");
  fmt::println("iterators : ");

  auto it = numbers.begin();
  fmt::print(" set of numbers : [");
  while (it != numbers.end()) {
    fmt::print("{} ", *it);
    ++it;
  }
  fmt::println("]");

  auto it_back = numbers.rbegin();
  fmt::print(" set of numbers (reverse) : [");
  while (it_back != numbers.rend()) {
    fmt::print(" {}", *it_back);
    ++it_back;
  }
  fmt::println("]");

  auto it_back_books = books.rbegin();
  fmt::print(" set of books (reverse) : [");
  while (it_back_books != books.rend()) {
    fmt::print(" {}", *it_back_books);
    ++it_back_books;
  }
  fmt::println("]");


  // Code3 : Capacity :
  fmt::println("---------------------");

  fmt::println("");
  fmt::println("capacity : ");
  fmt::print(" numbers : ");
  print_collection(numbers);
  fmt::println(" set max_size : {}", numbers.max_size());
  fmt::println(" set is empty : {}", numbers.empty());
  fmt::println(" set size : {}", numbers.size());


  fmt::println("---------------------");
  // Modifiers

  // Clear
  fmt::println("");
  fmt::println("clear :");
  print_collection(numbers);

  numbers.clear();

  print_collection(numbers);
  fmt::println("numbers is empty : {}", numbers.empty());


  // Insert  : returns an std::pair object containing result about the insert operation.
  fmt::println("");
  fmt::println("Insert : ");
  numbers = { 11, 12, 13, 14, 15 };
  print_collection(numbers);

  // Insert 14 : won't insert because std::set doesn't allow duplicates.
  // Will just do nothing and won't give an error though.
  numbers.insert(14);

  fmt::print(" After insert 14 : ");
  print_collection(numbers);


  // Can capture the insert result through a returned std::pair object.

  fmt::println("-------");

  // auto result = numbers.insert(14);
  auto result = numbers.insert(20);

  fmt::println(" first : {}", *result.first);
  fmt::println(" second : {}", result.second);

  fmt::println("------");
  if (result.second) {
    fmt::println(" Insertion of {} successful", *result.first);
  } else {
    fmt::println(" Couldn't insert {} in the set. It's a duplicate!", *result.first);
  }
  print_collection(numbers);


  // Emplace
  fmt::println("");
  fmt::println("emplace : ");

  print_collection(numbers);

  // auto result_emplace = numbers.emplace(421); // Succeeds
  auto result_emplace = numbers.emplace(13);// Fails

  if (result_emplace.second) {
    fmt::println(" Emplace of {} successful", *result_emplace.first);
  } else {
    fmt::println(" Emplace of {} FAILED ", *result_emplace.first);
  }

  print_collection(numbers);


  // Erase
  fmt::println("");
  fmt::println("erase : ");

  print_collection(numbers);

  auto it_erase = std::find(numbers.begin(), numbers.end(), 13);

  if (it_erase != numbers.end()) {
    fmt::println("Found 13 !");
  } else {
    fmt::println("Couldn't find 13 !");
  }

  // Erase the 13
  if (it_erase != numbers.end()) numbers.erase(it_erase);

  print_collection(numbers);

  // swap
  fmt::println("");
  fmt::println("swap : ");

  std::set<int> other_numbers{ 200, 400, 600 };

  fmt::print(" numbers : ");
  print_collection(numbers);
  fmt::print(" other_numbers :");
  print_collection(other_numbers);


  numbers.swap(other_numbers);

  fmt::print(" numbers : ");
  print_collection(numbers);
  fmt::print(" other_numbers :");
  print_collection(other_numbers);


  // Change comparator
  fmt::println("");
  fmt::println("change comparator : ");

  // std::set<int> numbers1 {11,16,2,9,12,15,6,15,2};  // Use default functor (std::less)
  // std::set<int,std::less<int>> numbers1 {11,16,2,9,12,15,6,15,2};  // Built in functor
  // std::set<int,std::greater<int>> numbers1 {11,16,2,9,12,15,6,15,2}; // Built in functor
  // std::set<int,IntComparator> numbers1 {11,16,2,9,12,15,6,15,2}; // Use Custom functor

  // Function pointer
  /*
  std::set<int,bool(*)(int,int)> numbers1(compare_ints) ;
  numbers1.insert({11,16,2,9,12,15,6,15,2});
  */

  std::set<int, std::function<bool(int, int)>> numbers1([](int left, int right) { return left > right; });
  numbers1.insert({ 11, 16, 2, 9, 12, 15, 6, 15, 2 });// Lambda function


  fmt::print(" numbers1 :[ ");
  for (const auto &elt : numbers1) { fmt::print(" {}", elt); }
  fmt::println("]");


  return 0;
}