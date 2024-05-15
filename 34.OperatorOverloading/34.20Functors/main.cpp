#include <fmt/format.h>
#include <string>

class Print
{
public:
  void operator()(const std::string &name) const { fmt::println("The name is : ", name); }

  std::string operator()(const std::string &last_name, const std::string &first_name) const
  {
    return (last_name + " " + first_name);
  }
};

void do_something(const Print &printer) { printer("Snow"); }


int main()
{

  Print print;
  print("John");
  do_something(print);
  fmt::println("{}", print("Daniel", "Gray"));

  return 0;
}