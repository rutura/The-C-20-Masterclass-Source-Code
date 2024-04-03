#ifndef DOG_H
#define DOG_H

#include <string>
#include <fmt/format.h>
class Dog
{
public:
    explicit Dog(std::string name_param);
    Dog() = default;
    ~Dog();
    
    std::string get_name() const{
        return dog_name;
    }
    
    void set_dog_name(const std::string & name){
        dog_name = name;
    }
	
	void print_info() const{
		fmt::println( "Dog [ name : {} ]" , dog_name  );
	}
    
private:
    std::string dog_name {"Puffy"};
};


#endif // DOG_H
