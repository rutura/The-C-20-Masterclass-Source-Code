#include <fmt/format.h>

class Dog{
    public : 
     Dog() = default;
     void prin_info(){

     }
     void do_something(){

     }

     private :
      size_t leg_count; //8
      size_t arm_count; //8
      int * p_age; // 8
};


int main(){

    Dog dog1;
    fmt::println( "sizeof(size_t) : {}" , sizeof(size_t) );
    fmt::println( "sizeof(int*) : {}" , sizeof(int*) );
    fmt::println( "sizeof(Dog) : {}" , sizeof(dog1) );

    std::string name{"I am the king of the universe!"};

    fmt::println( "sizeof(name) : {}" , sizeof(name) );
   
    return 0;
}