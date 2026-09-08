#ifndef FARM_H
#define FARM_H

class Dog; // Forward declaration
//#include "dog.h"

class Farm
{
public:
	Farm();
	~Farm();
	
	void use_dog(const Dog& dog_param); // Doesn't require the definition

    // void do_something(const Dog& dog_param){
    //     dog_param.print_info();
    // }
private : 
    //Dog dog_member;

};

#endif // FARM_H
