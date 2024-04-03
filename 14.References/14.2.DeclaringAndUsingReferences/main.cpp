#include <fmt/format.h>

int main()
{

  int int_data{ 33 };
  double double_data{ 55 };

  // References
  int &ref_int_data{ int_data };
  double &ref_double_data{ double_data };

  // Print stuff out
  fmt::println("int_data : {}", int_data);
  fmt::println("&int_data : {}", fmt::ptr(&int_data));
  fmt::println("double_data : {}", double_data);
  fmt::println("&double_data : {}", fmt::ptr(&double_data));

  fmt::println("=======================");

  fmt::println("ref_int_data : {}", ref_int_data);
  fmt::println("&ref_int_data : {}", fmt::ptr(&ref_int_data));
  fmt::println("ref_double_data : {}", ref_double_data);
  fmt::println("&ref_double_data : {}", fmt::ptr(&ref_double_data));

  int_data = 111;
  double_data = 67.2;


  // Print stuff out
  fmt::println("int_data : {}", int_data);
  fmt::println("&int_data : {}", fmt::ptr(&int_data));
  fmt::println("double_data : {}", double_data);
  fmt::println("&double_data : {}", fmt::ptr(&double_data));

  fmt::println("=======================");

  fmt::println("ref_int_data : {}", ref_int_data);
  fmt::println("&ref_int_data : {}", fmt::ptr(&ref_int_data));
  fmt::println("ref_double_data : {}", ref_double_data);
  fmt::println("&ref_double_data : {}", fmt::ptr(&ref_double_data));


  ref_int_data = 1012;
  ref_double_data = 1000.45;


  // Print stuff out
  fmt::println("int_data : {}", int_data);
  fmt::println("&int_data : {}", fmt::ptr(&int_data));
  fmt::println("double_data : {}", double_data);
  fmt::println("&double_data : {}", fmt::ptr(&double_data));

  fmt::println("=======================");

  fmt::println("ref_int_data : {}", ref_int_data);
  fmt::println("&ref_int_data : {}", fmt::ptr(&ref_int_data));
  fmt::println("ref_double_data : {}", ref_double_data);
  fmt::println("&ref_double_data : {}", fmt::ptr(&ref_double_data));

  return 0;
}