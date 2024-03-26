#include <fmt/format.h>

int max(int& a, int&b){
    fmt::println( "max with int& called" );

    //Can change a and b through the reference 
    //a = 200;// This change will be visible outside the function
    
    return (a > b)? a : b;
}

int max(const int& a, const int& b){
    fmt::println( "max with const int& called" );
    
    //Can NOT change a and b through the reference 
    //a = 200; // Will give a compiler error.
    return (a > b)? a : b;
}


int main(){

	int a{45};
    int b{85};
    
    int max1 = max(a,b);
    fmt::println( "max1 : " , max1 );

    const int& ref_a = a;
    const int& ref_b = b;

    int max2 = max(ref_a,ref_b);
    fmt::println( "max2 : " , max2 );

   
    return 0;
}