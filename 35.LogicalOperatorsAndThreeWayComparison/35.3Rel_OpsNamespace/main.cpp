//#include <utility>
#include "point.h"


int main(){
   // using namespace std::rel_ops;
    Point point1(10.0,10.0);
	Point point2(20.0,20.0);
  
    fmt::println( "point1 : {}" , point1 );
	fmt::println( "point2 : {}" , point2 );
	
   
    fmt::println( "point1 > point2 : {}",(point1 > point2) );
    fmt::println( "point1 < point2 : {}", (point1 < point2) );
    fmt::println( "point1 >= point2 : {}" , (point1 >= point2) );
    fmt::println( "point1 <= point2 : {}" , (point1 <= point2) );
    fmt::println( "point1 == point2 : {}" , (point1 ==point2) );
    fmt::println( "point1 != point2 : {}" , (point1 != point2) );
 
    
    return 0;
}