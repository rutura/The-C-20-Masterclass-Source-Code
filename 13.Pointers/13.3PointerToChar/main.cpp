#include <fmt/format.h>

int main()
{

  const char *message{ "Hello World!" };
  fmt::println("message : {}", message);

  //*message = "B"; // Compiler error
  fmt::println("*message : {}", *message);

  // Allow users to modify the string
  char message1[]{ "Hello World!" };
  message1[0] = 'B';
  fmt::println("message1 : {}", message1);

  return 0;
}