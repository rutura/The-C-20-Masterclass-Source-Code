#include <iostream>
#include <string>

class Print{
    public : 
    void operator()(const std::string& name) const{
        std::cout << "The name is : " << name << std::endl;
    }

    std::string operator()(const std::string& last_name,
                            const std::string& first_name) const {
        return (last_name + " " + first_name);
    }
};

void do_something(const Print& printer){
    printer("Snow");
}


int main(){

    Print print;
    print("John");
    do_something(print);
    std::cout << print("Daniel","Gray") << std::endl;
   
    return 0;
}