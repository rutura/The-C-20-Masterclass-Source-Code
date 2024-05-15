#include <fmt/format.h>
#include <vector>

/*
template <typename T>
concept OutputStreamable = requires(std::ostream& o , T d){
        o << d;
};


template <OutputStreamable T>
std::ostream & operator << (std::ostream& out, const std::vector<T> & vec){
        out << " [ ";
        for(auto i : vec){
        out << i  << " ";
         }
        out << "]";
        return out;
}
*/


struct Point
{
  double mx;
  double my;

  friend std::ostream &operator<<(std::ostream &o, const Point p)
  {
    o << "Point [ x : " << p.mx << ", y : " << p.my << "]";
    return o;
  }
  friend struct fmt::formatter<Point>;
};

template<> struct fmt::formatter<Point>
{
  constexpr auto parse(fmt::format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Point &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Point [ x: {}, y: {}]", obj.mx, obj.my);
  }
};

std::string format_point(const Point &p) { return fmt::format("{}", p); }

template<typename Container> concept PointContainer = requires(Container c)
{
  typename Container::value_type;// Container must have a value_type member
  {
    *std::begin(c)
    } -> std::same_as<Point &>;// Dereferencing must yield a Point&
  { std::begin(c) != std::end(c) };// Container must be iterable
};

template<PointContainer Container> std::string join_points(const Container &cont, const std::string &separator)
{
  std::string result;
  for (const auto &point : cont) {
    if (!result.empty()) { result += separator; }
    result += format_point(point);
  }
  return result;
}
int main()
{

  std::vector<int> numbers{ 1, 2, 3, 4, 5 };
  // fmt::println( "numbers : {}" , numbers );
  fmt::println("numbers : {}", fmt::join(numbers, ", "));

  std::vector<Point> points{ { 10, 20 }, { 59, 45 } };
  // fmt::println( "points : {}" , points );
  fmt::print("points: [{}]\n", join_points(points, ", "));

  return 0;
}