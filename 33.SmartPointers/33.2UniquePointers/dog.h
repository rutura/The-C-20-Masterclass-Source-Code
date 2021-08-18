#ifndef DOG_H
#define DOG_H


#include <string>
#include <iostream>
class Dog
{
public:
    explicit Dog(std::string name_param);
    Dog() = default;
    ~Dog();
    
    void print_dog() const{
        std::cout << "Printing dog : " << dog_name << std::endl;
    }
    
    std::string get_name() const{
        return dog_name;
    }
    
    void set_dog_name(const std::string & name){
        dog_name = name;
    }
    
private:
    std::string dog_name {"Puffy"};

};


#endif // DOG_H
