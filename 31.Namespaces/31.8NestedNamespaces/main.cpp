#include <iostream>

namespace Hello{
    unsigned int age{23};
    
    namespace World{
        int local_var{44};
        
        void say_something(){
            std::cout << "Hello there " << std::endl;
            std::cout << "The age is : " << age << std::endl;
        }
    }
    
    void do_something(){
        //Here we don't have direct access to local_var, we have to go 
        //through the namespace.
        std::cout << "Using local_var : " << World::local_var << std::endl;
    }
}



int main(){
    //Hello::World::say_something();
    Hello::do_something();

    return 0;
}