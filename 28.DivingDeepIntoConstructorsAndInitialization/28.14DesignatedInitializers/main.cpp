#include <fmt/format.h>

struct Component
{
  double x;
  double y;
  double z;
};

void print_point(const Point &p) { fmt::println("Point [ x: {}, y: {}]", p.x, p.y); }


int main()
{

  Component c1{ .x = 5.7, .y = 8.2, .z = 5.2 };
  Component c2{ .x = 6.2, .z = 8.4 };
  Component c3{ .y = 6.2, .z = 5.9 };
  // Component c4 {.z =5.9 , .x=10.4 , .y =6.89}; // Compiler error

  print_component(c1);
  print_component(c2);
  print_component(c3);

  return 0;
}