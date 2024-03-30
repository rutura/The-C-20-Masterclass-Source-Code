#include <fmt/format.h>

namespace Hello{
    unsigned int age{23};
    
    namespace World{
        int local_var{44};
        
        void say_something(){
            fmt::println( "Hello there " );
            fmt::println( "The age is : {}" , age );
        }
    }
    
    void do_something(){
        //Here we don't have direct access to local_var, we have to go 
        //through the namespace.
        fmt::println( "Using local_var : {}" , World::local_var );
    }
}



int main(){
    //Hello::World::say_something();
    Hello::do_something();

    return 0;
}