#include <fmt/format.h>


void print_age_1();
void print_age_2();

void print_distance_1();
void print_distance_2();



int main(){

    print_age_1();
    print_age_2();

    fmt::println( "----" );

    print_distance_1();
    print_distance_2();
   
    return 0;
}