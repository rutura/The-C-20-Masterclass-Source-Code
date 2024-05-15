#include <fmt/format.h>
#include <map>//multimap
#include <set>// multiset


class Book
{
  friend std::ostream &operator<<(std::ostream &out, const Book &operand);
  friend struct fmt::formatter<Book>;

public:
  Book() = default;
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

template<typename T> void print_multiset(const std::multiset<T> &m_set)
{

  auto it = m_set.begin();

  fmt::print("multiset of elements : [");
  while (it != m_set.end()) {

    fmt::print(" {}", *it);
    ++it;
  }
  fmt::println("]");
}


template<typename T, typename K> void print_multimap(const std::multimap<T, K> &m_map)
{

  auto it = m_map.begin();

  fmt::print("multimap of elements : [");
  while (it != m_map.end()) {

    fmt::println(" [{},{}]", it->first, it->second);
    ++it;
  }
  fmt::println("]");
}

int main()
{

  std::multiset<int> numbers = { 1, 2, 1, 6, 2, 8, 3, 9, 4, 24, 6, 2 };

  std::multiset<Book> books = {
    Book(1734, "Cooking Food"), Book(1930, "Building Computers"), Book(1734, "Farming for Beginners")
  };


  fmt::print("numbers : ");
  print_multiset(numbers);

  fmt::print("books : ");
  print_multiset(books);

  fmt::println("");
  fmt::println("multimap : ");


  std::multimap<int, std::string> office_numbers = {
    std::make_pair(101, "Daniel Gray"),
    std::make_pair(102, "John Snow"),
    std::make_pair(103, "Jamie Lanister"),
    std::make_pair(102, "Van Gomir"),
    std::make_pair(101, "Kay Moris"),
    std::make_pair(102, "Zuba Loy"),
  };

  fmt::print("office_numbers : ");
  print_multimap(office_numbers);


  std::multimap<int, Book> other_books = { std::make_pair(0, Book(1734, "Cooking Food")),
    std::make_pair(1, Book(1930, "Building Computers")),
    std::make_pair(1, Book(1995, "Farming for Beginners")) };

  fmt::print("other_books : ");
  print_multimap(other_books);


  // The rest of the cool stuff you can do with this can be browsed through
  // the documentation.Many methods are similar to the std::set and std::map
  // counterparts.

  return 0;
}