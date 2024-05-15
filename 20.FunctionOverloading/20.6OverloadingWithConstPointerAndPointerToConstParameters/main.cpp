#include <fmt/format.h>


int max(int *a, int *b)
{
  fmt::println("max with int* called");
  return (*a > *b) ? *a : *b;
}

int max(const int *a, const int *b)
{
  fmt::println("max with cont int* called");
  return (*a > *b) ? *a : *b;
}


/*
int min(const int* a, const int* b){
    return (*a < *b)? *a : *b;
}
*/


int min(const int *const a, const int *const b)
{
  fmt::println("&a : {}", fmt::ptr(&a));
  fmt::println("&b : {}", fmt::ptr(&b));
  return (*a < *b) ? *a : *b;
}


int main()
{

  /*
      int a{10};
          int b{12};

          const int c{30};
          const int d{15};

      auto result = max(&c,&c);
      */

  const int c{ 30 };
  const int d{ 15 };

  const int *p_c{ &c };
  const int *p_d{ &d };

  fmt::println("&p_c : {}", fmt::ptr(&p_c));
  fmt::println("&p_d : {}", fmt::ptr(&p_d));

  auto result = min(p_c, p_d);


  return 0;
}