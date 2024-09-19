#include "utilities.h"

#include "create_namespace.h"
#include "cylinder.h"
#include "default_global_namespace.h"
#include "namespace_aliases.h"
#include "point.h"
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void create_namespace()
{
  auto result = Adjust::div(12, 3);
  fmt::println("result: {}", result);
}

void ns_x_multiple_files()
{
  Geom::Point p1(10, 20);
  Geom::Point p2(3.4, 6.1);
  p1.print_info();
  p2.print_info();

  fmt::println("---");

  Geom::Cylinder c1(1.4, 10);
  fmt::println("c1.volume : {}", c1.volume());
}

void default_global_namespace()
{
  //auto result = add(10,20);
  //auto result = My_Thing::add(10, 20);
  //fmt::println("The value is {}", result);
  My_Thing::do_something();
}

void built_in_namespaces()
{
  fmt::println("Hello World");
  std::string message{ "Hello World" };
  fmt::println("{}", message);
}

void using_declarations()
{
  using namespace Geom;
  Point p1(10, 20);
  Point p2(3.4, 6.1);
  p1.print_info();
  p2.print_info();

  fmt::println("---");

  Cylinder c1(1.4, 10);
  fmt::println("c1.volume : {}", c1.volume());

  fmt::println("---");

  // using std::cout;
  // using std::endl;
  //using namespace std;// NOT RECOMMENDED!
  //string msg("Hello World!");
  //fmt::println("Gretting: {}",msg);
}

void anonymous_namespace()
{
  /*
  auto result ::subtract(10,3); /// Compiler error: subtract is constrained to a single
                                                                  // TU because it's in an anonymous namespace.
  fmt::println("result: {}", result);
  */
}

void nested_namespaces()
{
  //ATTENTION: GCC 14 doesn't like it if we set up nested namespaces. It reports
  // 				an internal compiler error. Try this with MSVC/Clang and decide
  //				on the next course of action.
  //Hello::World::say_something();
  //Hello::do_something();
}

void namespace_aliases()
{
  // Namespace aliases
  namespace Data = Level1::Level2::Level3;
  fmt::println("weight : {}", Data::weight);
}