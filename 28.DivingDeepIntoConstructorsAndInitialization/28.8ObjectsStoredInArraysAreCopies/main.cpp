#include <fmt/format.h>
#include "person.h"


int main(){

    Person p1("John","Snow",25);
    Person p2("Sam","Gray",45);
    Person p3("Johny","Drill",5);
    p1.print_info();
    p2.print_info();
    p3.print_info();

    fmt::println( "----" );

    Person students[] {p1,p2,p3};
    for(size_t i{}; i < std::size(students); ++i){
        students[i].print_info();
    }

    fmt::println( "----" );
    for(Person& p : students){
        p.print_info();
    }


   
    return 0;
}