#include <cstring>
#include <fmt/format.h>

//(3)Function template
template<typename T> T maximum(T a, T b)
{
  fmt::println("Template overload called(T) ");
  return (a > b) ? a : b;
}

//(1)A raw overload will take precedence over any template instance
// if const char* is passed to maximum
const char *maximum(const char *a, const char *b)
{
  fmt::println("Raw overload called");
  return (std::strcmp(a, b) > 0) ? a : b;
}


//(2)Overload through templates. Will take precedence over raw T
// if a pointer is passed to maximum

template<typename T> T *maximum(T *a, T *b)
{
  fmt::println("Template overload called (T*) ");
  return (*a > *b) ? a : b;
}


int main()
{


  /*
      const char* g{"wild"};
      const char* h{"animal"};

      const char* result = maximum(g,h);
  */

  int a{ 810 };
  int b{ 23 };

  auto result = maximum(&a, &b);
  fmt::println("result : {}", *result);

  return 0;
}