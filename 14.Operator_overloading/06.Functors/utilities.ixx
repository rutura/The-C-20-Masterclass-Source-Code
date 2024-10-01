module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module utilities;

class Print
{
public:
  void operator()(const std::string &name) const { fmt::println("The name is: {} ", name); }

  std::string operator()(const std::string &last_name, const std::string &first_name) const
  {
    return (last_name + " " + first_name);
  }
};

void do_something(const Print &printer) { printer("Snow"); }


export void functors(){
	Print print;
	print("Mahoro");
	do_something(print);
	fmt::println("{}", print("Daniel", "Gray"));
}