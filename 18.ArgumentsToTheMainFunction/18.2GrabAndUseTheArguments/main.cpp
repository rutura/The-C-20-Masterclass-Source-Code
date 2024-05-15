#include <fmt/format.h>


int main(int argc, char *argv[])
{

  fmt::println("We have {} parameters in our program", argc);

  for (size_t i{ 0 }; i < argc; ++i) { fmt::println("parameter [{}] :{}", i, argv[i]); }

  return 0;
}