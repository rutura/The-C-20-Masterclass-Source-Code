#include <fmt/format.h>

int main()
{

  for (size_t i{ 0 }, x{ 5 }, y{ 22 }; y > 15; ++i, x += 5, y -= 1) { fmt::println("i: {}, x :{}, y :{}", i, x, y); }

  return 0;
}