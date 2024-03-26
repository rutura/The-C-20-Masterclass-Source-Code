#include <fmt/format.h>
#include <limits>


int main(){



  /*std::string m1{"Hello"};
  std::string m2{"World"}; // World comes after Hello in alphabetical order so it's
                           // considered to be greater.

  auto result = m1.compare(m2);
  if(result > 0){
    fmt::println( "m1 > m2" );
  }else if(result == 0){
    fmt::println( "m1 == m2" );
  }else{
    fmt::println( "m1 < m2" );
  }*/

  //Three way comparison operator : spaceship operator <=>
    /*int n1{5};
    int n2{5};
    //int n3{0};

    auto result = ( n1 <=> n2);

    fmt::println( "n1 > n2 : {}" , ((n1 <=> n2) > 0) ); // true
    fmt::println( "n1 >= n2 :{} ", ((n1 <=> n2) >= 0) );
    fmt::println( "n1 == n2 : {}" , ((n1 <=> n2) == 0) );
    fmt::println( "n1 < n2 : {}" , ((n1 <=> n2) < 0) );
    fmt::println( "n1 <= n2 : {}" , ((n1 <=> n2) <= 0) );*/


   //Strong ordering
    /*
    int n4{5};
    int n5{5};

    fmt::println( "n4 > n5 : {}" , (n4 > n5) ); // false
    fmt::println( "n4 == n5 : {}" , (n4 == n5) ); //true :  Absolute equality
    fmt::println( "n4 < n5 : {}" , (n4 < n5) ); // false
    */

   //Weak ordering
    /*std::string m1{"Hello"};
    std::string m2{"HELLO"};

    fmt::println( "m1 > m2 :{} " , (m1 > m2) ); //
    fmt::println( "m1 == m2 :{} " , (m1 == m2) ); // equivalence
    fmt::println( "m1 < m2 :{} " , (m1 < m2) ); //*/

    //Partial ordering
    double d1{33.9};
    double d2{std::numeric_limits<double>::quiet_NaN()};

    fmt::println( "d1 > d2 : {}" , (d1 > d2) ); // false
    fmt::println( "d1 == d2 : {}" , (d1 == d2) ); //false
    fmt::println( "d1 < d2 : {}" , (d1 < d2) ); //false

   



    return 0;
}