#include <fmt/format.h>

class Dog{
    friend void debug_dog_info(const Dog& d);
    friend void debug_dog_info();
public : 
    Dog(const std::string& name, int age) 
        : m_name{name},m_age{age}
    {

    }

private : 
    std::string m_name;
    int m_age;
};

void debug_dog_info(const Dog& d){
    fmt::println( "Dog [ name : {}{}{}{}" , d.m_name , ", age : " , d.m_age , "]" );
}

void debug_dog_info(){
    Dog dog1("Milou",3);
    dog1.m_name = "Fluffy";
    fmt::println( "Dog [ name : {}{}{}{}" , dog1.m_name , ", age : " , dog1.m_age , "]" );

}


int main(){
    Dog dog1("Fluffy",4);
    //debug_dog_info(dog1);

    debug_dog_info();
   
    return 0;
}