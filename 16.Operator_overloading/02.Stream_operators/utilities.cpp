#include "utilities.h"

#include "point.h"

#include <iostream>

void print_msg(std::string_view msg)
{
  //fmt::println("{}",msg);
}


//#1: Overloading the stream insertion operator 
void overload_stream_insertion_operator()
{
  Point p1(10, 20);
  Point p2(3, 4);

  std::cout << p1 << "\n";
  std::cout << p2 << "\n";

}

//#2: Overloading the stream extraction operator
void overload_stream_extraction_operator()
{
  Point p2;
  std::cin >> p2;//
  std::cout << p2 << "\n";
}