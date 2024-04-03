#include <fmt/format.h>

int &max_return_reference(int &a, int &b)
{
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int &sum(int &a, int &b)
{
  int result = a + b;
  return result;// Reference to local variable returned
}


int &max_input_by_value(int a, int b)
{
  if (a > b) {
    return a;// Reference to local variable returned
  } else {
    return b;// Reference to local variable returned
  }
}


int main()
{

  /*
  int x{14};
  int y{9};
  int& ref_max = max_return_reference(x,y); // Reference
  int val = max_return_reference(x,y); // Copy

  fmt::println( "ref_max : {}" , ref_max );
  fmt::println( "val : {}" , val );
  fmt::println( "x : {}" , x );
  fmt::println( "y : {}" , y );

  ref_max++;

  fmt::println( "----- " );
  fmt::println( "ref_max : {}" , ref_max ); // 15
  fmt::println( "val : {}" , val ); // 14
  fmt::println( "x : {}" , x ); // 15
  fmt::println( "y : {}" , y ); // 9

  */


  /*
   int x{14};
   int y{9};
   int& result = sum(x,y); // Reference
   fmt::println( "result : {}" , result );
   */


  int x{ 14 };
  int y{ 9 };
  int &result = max_input_by_value(x, y);// Reference
  fmt::println("result : {}", result);


  fmt::println("Done!");

  return 0;
}