#ifndef DOG_H
#define DOG_H

#include <string>
#include <fmt/format.h>

class Dog
{
public:
	Dog() = default;
	Dog(const std::string& name);
	~Dog();
	
	void print_info() const{
		fmt::println( "Dog [ name : {}]" , name );
	}
private : 
	std::string name{};
};

#endif // DOG_H
