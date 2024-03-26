#include <fmt/format.h>

int* max_return_pointer(int* a, int* b)
{
    if(*a > *b) {
        return a;
    } else {
        return b;
    }
}

int* max_input_by_value (int a, int b)
{
    if(a > b) {
        return &a; // Pointer to local variable returned
    } else {
        return &b; // Pointer to local variable returned
    }
}


int* sum( int* a, int* b){
    int result = *a + *b; 
    return &result;// Pointer to local variable returned
}


int main(){

    /*
    int x{56};
    int y{45};
    int* p_max = max_return_pointer(&x,&y);

    fmt::println( "x : {}" , x );
    fmt::println( "y : {}" , y );
    fmt::println( "*p_max : {}" , *p_max );


    ++(*p_max);

    fmt::println( "-----" );
    fmt::println( "x : {}" , x );
    fmt::println( "y : {}" , y );
    fmt::println( "*p_max : {}" , *p_max );
    */


   /*
    int x{56};
    int y{45};
    int* p_sum = sum(&x,&y);
    fmt::println( *p_sum );
    */


    int x{56};
    int y{45};
    int* p_sum = max_input_by_value(x,y);
    fmt::println( "{}", *p_sum );




    fmt::println( "Done!" );
   
    return 0;
}