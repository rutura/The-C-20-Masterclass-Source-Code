#include <fmt/format.h>


// The right way : return type deduction
/*
auto process_number(int value){
    if(value < 10){
        return 22; // returning int literal
    }else{
        return 55; // returning int literal
    }
}
*/

auto process_number(int value)
{
  if (value < 10) {
    return static_cast<double>(22);// returning int literal
  } else {
    return 33.1;// returning double literal
  }
}


int main()
{

  auto result = process_number(17);
  fmt::println("result : {}", result);
  fmt::println("sizeof(result)  : {}", sizeof(result));
  fmt::println("sizeof(int) : {}", sizeof(int));
  fmt::println("sizeof(double) : {}", sizeof(double));

  return 0;
}