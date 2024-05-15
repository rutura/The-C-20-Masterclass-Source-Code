#include "boxcontainer.h"


class Point
{
  friend std::ostream &operator<<(std::ostream &out, const Point &operand);
  friend struct fmt::formatter<Point>;

public:
  Point(double x, double y) : m_x(x), m_y(y) {}
  // The default constructor must be there for bags of Points to be able
  // initializable with the new T[] statement in the BoxContainer<T> constructor.
  Point() : m_x(0.0), m_y(0.0) {}

private:
  double m_x{};
  double m_y{};
};

std::ostream &operator<<(std::ostream &out, const Point &operand)
{
  out << "Point [ x : " << operand.m_x << ",y : " << operand.m_y << "]";
  return out;
}

template<> struct fmt::formatter<Point>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Point &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Point [x: {}, y: {}]", obj.m_x, obj.m_y);
  }
};


int main()
{

  // int
  fmt::println("BoxContainer of int : ");
  BoxContainer<int> int_box;
  int_box.add(33);
  int_box.add(44);
  fmt::println("int_box : {}", int_box);

  // double
  fmt::println("BoxContainer of double : ");
  BoxContainer<double> double_box;
  double_box.add(100.11);
  double_box.add(200.22);
  fmt::println("double_box : {}", double_box);

  // Point
  fmt::println("BoxContainer of Point : ");
  BoxContainer<Point> point_box;
  point_box.add(Point(20.1, 20.2));
  point_box.add(Point(200.22, 300.33));
  fmt::println("point_box : {}", point_box);

  // std::string
  fmt::println("BoxContainer of std::string");
  BoxContainer<std::string> string_box;
  string_box.add("Hello");
  string_box.add("World");
  fmt::println("string_box : {}", string_box);

  // char
  fmt::println("BoxContainer of char");
  BoxContainer<char> char_box;
  char_box.add('H');
  char_box.add('e');
  char_box.add('l');
  char_box.add('l');
  char_box.add('o');
  char_box.add('o');
  fmt::println("char_box : {}", char_box);

  //------------------------------------------------------

  fmt::println("Trying out all the methods: ");

  BoxContainer<int> int_box1;
  int_box1.add(10);
  int_box1.add(21);
  int_box1.add(44);

  fmt::println("int_box1 : {}", int_box1);

  int_box1.add(10);
  int_box1.add(55);
  int_box1.add(10);
  fmt::println("int_box1 : {}", int_box1);

  int_box1.remove_item(55);
  fmt::println("int_box1 : {}", int_box1);

  size_t removed = int_box1.remove_all(10);
  fmt::println("{} items removed", removed);
  fmt::println("int_box1 : {}", int_box1);

  // Copy construct
  fmt::println("Copy construction");
  BoxContainer<int> int_box2(int_box);
  fmt::println("int_box : {}", int_box);
  fmt::println("int_box2 : {}", int_box2);

  // Copy assign
  fmt::println("Copy assignment");
  int_box2 = int_box1;
  fmt::println("int_box1 : {}", int_box1);
  fmt::println("int_box2 : {}", int_box2);

  fmt::println("operator+= : ");
  int_box2 += int_box;
  fmt::println("int_box : {}", int_box);
  fmt::println("int_box2 : {}", int_box2);


  fmt::println("operator+");
  BoxContainer<int> int_box3;
  int_box3.add(100);
  int_box3.add(200);

  BoxContainer<int> int_box4;
  int_box4 = int_box2 + int_box3;
  fmt::println("int_box4 : {}", int_box4);

  fmt::println("END.");


  return 0;
}