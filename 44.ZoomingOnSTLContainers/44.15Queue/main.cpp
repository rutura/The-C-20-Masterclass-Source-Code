#include <deque>
#include <fmt/format.h>
#include <list>
#include <queue>


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

template<typename T, typename Container = std::deque<T>> void print_queue(std::queue<T, Container> queue)
{

  fmt::print(" queue of items : [");
  while (!queue.empty()) {
    T item = queue.front();
    fmt::print(" {}", item);
    queue.pop();
  }
  fmt::println("]");
}

template<typename T, typename Container = std::deque<T>> void clear_queue(std::queue<T, Container> &queue)
{
  fmt::println(" Clearing queue of size : {}", queue.size());

  while (!queue.empty()) { queue.pop(); }
}


int main()
{

  // Code1 : Creating  pushing and accessing
  fmt::print("Creating pushing and accessing : ");
  std::queue<int> numbers1;

  fmt::print(" numbers1 : ");
  print_queue(numbers1);

  numbers1.push(10);
  numbers1.push(20);
  numbers1.push(30);

  fmt::print(" numbers1 : ");
  print_queue(numbers1);

  numbers1.push(40);
  numbers1.push(50);

  fmt::print(" numbers1 : ");
  print_queue(numbers1);

  // Acess
  fmt::print(" numbers1.front() :  {}", numbers1.front());
  fmt::print(" numbers1.back() : {}", numbers1.back());

  // Code2 : Modify through top : this is because front and back return  a reference
  fmt::println("");
  fmt::print("modify top element through front and back :");

  fmt::print(" numbers1 (before modification) : ");
  print_queue(numbers1);

  numbers1.front() = 500;
  numbers1.back() = 600;

  fmt::print(" numbers1 (after modification) : ");
  print_queue(numbers1);

  // Code3 : poping
  fmt::println("");
  fmt::print("poping data : ");

  fmt::print(" numbers1 : ");
  print_queue(numbers1);

  numbers1.pop();

  fmt::print(" numbers1 : ");
  print_queue(numbers1);

  numbers1.pop();

  fmt::print(" numbers1 : ");
  print_queue(numbers1);


  // Code4 : Clearing a queue
  fmt::println("");

  fmt::print("clearing a queue : ");

  fmt::print(" queue initial size : {}", numbers1.size());

  fmt::print(" numbers1 (before) : ");
  print_queue(numbers1);

  clear_queue(numbers1);

  fmt::print(" queue final size : {}", numbers1.size());
  fmt::print(" numbers1(after) : ");
  print_queue(numbers1);


  // Code5 : Queue of user defined types
  fmt::println("");
  fmt::print("queue of user defined type :");

  std::queue<Book> books;

  books.push(Book(1921, "The Art of War"));
  books.push(Book(2000, "Social Media Marketing"));
  books.push(Book(2020, "How the Pandemic Changed the World"));

  fmt::print(" books : ");
  print_queue(books);
  fmt::print(" books size : {}", books.size());
  fmt::print(" front book : {}", books.front());
  fmt::print(" back book : {}", books.back());


  // Code6 Specify underlying container
  fmt::println("");
  fmt::print("custom underlying sequence container : ");

  std::queue<int, std::list<int>> numbers3;
  std::queue<int, std::deque<int>> numbers4;

  numbers3.push(3);
  numbers3.push(4);

  numbers4.push(5);
  numbers4.push(6);

  fmt::print(" numbers3 : ");
  print_queue(numbers3);

  fmt::print(" numbers4 : ");
  print_queue(numbers4);


  return 0;
}