#ifndef DOG_H
#define DOG_H

#include <string>
#include <iostream>

class Dog
{
public:
	Dog() = default;
	Dog(const std::string& name);
	~Dog();
	
	void print_info() const{
		std::cout << "Dog [ name : " << name << "]" << std::endl;
	}
private : 
	std::string name{};
};

#endif // DOG_H
