#include <fmt/format.h>

void increment(int &value);
void print_out(const int &value);

int main()
{

  /*
  int int_var{3};

  increment(int_var);
  print_out(int_var);
  */

  double double_var{ 3.6 };

  int data = double_var;

  increment(data);
  print_out(double_var);

  return 0;
}

void increment(int &value)
{
  value++;
  fmt::println("value incremented to : {}", value);
}

void print_out(const int &value) { fmt::println("value : {}", value); }