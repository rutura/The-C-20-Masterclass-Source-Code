#include <fmt/format.h>

int max(int a, int b);// Function declaration , prototype
                      // Signature doesn't include return type
int min(int a, int b);

int inc_mult(int a, int b);

int main()
{

  int x{ 5 };
  int y{ 12 };

  int result = min(x, y);
  fmt::println("min : {}", result);

  result = inc_mult(x, y);
  fmt::println("result : {}", result);

  return 0;
}

// Function definition. Shows up after main
int max(int a, int b)
{
  if (a > b)
    return a;
  else
    return b;
}


// Function definition. Shows up after main
int min(int a, int b)
{
  if (a < b)
    return a;
  else
    return b;
}

int inc_mult(int a, int b) { return ((++a) * (++b)); }