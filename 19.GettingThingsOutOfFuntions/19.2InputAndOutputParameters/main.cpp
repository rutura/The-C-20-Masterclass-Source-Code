#include <fmt/format.h>
#include <string>

void max_str(const std::string &input1, const std::string input2, std::string &output)
{
  if (input1 > input2) {
    output = input1;
  } else {
    output = input2;
  }
}

void max_int(int input1, int input2, int &output)
{
  if (input1 > input2) {
    output = input1;
  } else {
    output = input2;
  }
}

void max_double(double input1, double input2, double *output)
{
  if (input1 > input2) {
    *output = input1;
  } else {
    *output = input2;
  }
}


int main()
{

  /*
      std::string out_str;
      std::string string1("Cassablanca");
      std::string string2("Bellevue");

      max_str(string1,string2,out_str);
      fmt::println( "max_str : {}", out_str );
  */

  /*
   int out_int;
   int in1{45};
   int in2{723};
   max_int(in1,in2,out_int);
   fmt::println( "max_int : {}" , out_int );
   */

  double out_double;
  double in_double1{ 45.8 };
  double in_double2{ 76.9 };
  max_double(in_double1, in_double2, &out_double);
  fmt::println("max_double : {}", out_double);

  return 0;
}