module;

#include <string>
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

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