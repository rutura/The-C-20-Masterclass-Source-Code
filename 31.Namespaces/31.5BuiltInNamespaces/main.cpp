#include <fmt/format.h>
#include <string>

int main()
{

  fmt::println("Hello World");
  std::string message{ "Hello World" };
  fmt::println("{}", message);
  return 0;
}