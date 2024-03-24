#include <fmt/format.h>

int global_var1{23}; // global variable


void some_function(){
    int local_var{10};
    fmt::println( "Inside function global_var : {}" , global_var1 );
    fmt::println( "Inside functoin local_var : {}" , local_var );
}

void some_other_function(){
    //local_var = 5;
}



int main(){
 fmt::println( "Inside main function global_var : {}" , global_var1 );
 //local_var = 5;
   
    return 0;
}