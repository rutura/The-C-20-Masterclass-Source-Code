#include <fmt/format.h>
#include <string>

// Ambiguous calls
void say_my_name(const std::string &name) { fmt::println("Your name is (ref) : {}", name); }

void say_my_name(std::string name) { fmt::println("Your name is (non ref) : {}", name); }

// Implicit conversions with references

double max(double a, double b)
{
  fmt::println("double max called");
  return (a > b) ? a : b;
}


// int& max(int& a, int& b){
const int &max(const int &a, const int &b)
{
  fmt::println("int max called");
  return (a > b) ? a : b;
}

int main()
{

  char a{ 6 };
  char b{ 9 };


  auto result = max(a, b);


  return 0;
}