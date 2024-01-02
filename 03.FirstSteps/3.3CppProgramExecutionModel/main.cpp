/*
    . Exploring the C++ program execution model
    . Reference the lecture on execution model in v 1.0 of the course.
    . Same content as v 1.0 in the course but updated to use the fmt library.

*/

#include <fmt/format.h>

int f_add(int a, int b){
    return a + b;
}

int main(){

    int a = 10;
    int b = 5;
    int c;

    fmt::println("Statement 1");
    fmt::println("Statement 2");
    c = f_add(a, b);
    fmt::println("c = {}", c);
    fmt::println("Statement 3");
    fmt::println("Statement 4");
 
  return 0;
}