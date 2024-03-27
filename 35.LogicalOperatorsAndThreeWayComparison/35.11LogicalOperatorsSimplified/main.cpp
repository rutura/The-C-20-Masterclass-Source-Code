#include "number.h"

int main(){
    Number n1(10);
    Number n2(20);
    

    fmt::println( "n1 > n2 : {}" , (n1 > n2) );
    fmt::println( "15 > n2 : {}" , (15 > n2) );
    fmt::println( "n1 > 25 : {}" , (n1 > 25) );

    fmt::println( "n1 >= n2 : {}" , (n1 >= n2) );
    fmt::println( "15 >= n2 : {}" , (15 >= n2) );
    fmt::println( "n1 >= 25 : {}" , (n1 >= 25) );

    fmt::println( "n1 == n2 : {}" , (n1 == n2) );
    fmt::println( "15 == n2 : {}" , (15 == n2) );
    fmt::println( "n1 == 25 : {}" , (n1 == 25) );

    fmt::println( "n1 < n2 : {}" , (n1 < n2) );
    fmt::println( "15 < n2 : {}" , (15 < n2) );
    fmt::println( "n1 < 25 : {}" , (n1 < 25) );

    fmt::println( "n1 <= n2 : {}" , (n1 <= n2) );
    fmt::println( "15 <= n2 : {}" , (15 <= n2) );
    fmt::println( "n1 <= 25 : {}" , (n1 <= 25) );
   
    return 0;
}