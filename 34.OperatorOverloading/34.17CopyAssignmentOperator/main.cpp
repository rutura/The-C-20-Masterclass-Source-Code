#include "point.h"
#include <fmt/format.h>

int main()
{


  Point p1(10, 10, 10);
  Point p2(20, 20, 20);
  Point p77(3, 3, 3);

  fmt::println("p1 : {}", p1);
  fmt::println("p2 : {}", p2);

  fmt::println("-----");

  // Assignment
  // p1 = p2 = p77;
  // p1.operator=(p2).operator=(p77);
  p1.operator=(p2.operator=(p77));

  fmt::println("p1 : {}", p1);
  fmt::println("p2 : {}", p2);

  // Change data
  p1.set_data(55);

  fmt::println("-----------");
  fmt::println("p1 : {}", p1);
  fmt::println("p2 : {}", p2);


  //
  /*
  Point p3(30,30,30);
  Point p4 = p3;

  fmt::println( "p3 : {}" , p3 );
  fmt::println( "p4 : {}" , p4 );

  p3.set_data(77);

  fmt::println( "-----" );
  fmt::println( "p3 : {}" , p3 );
  fmt::println( "p4 : {}" , p4 );


  fmt::println( "Done!" );
  */


  return 0;
}