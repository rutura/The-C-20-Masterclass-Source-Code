#ifndef PERSON_H
#define PERSON_H

#include <iostream>

//Declaration and definition
class Person{
public : 
    //Declaration for the constructor
	Person(const std::string& names_param, int age_param);
	
	void print_info()const{
		std::cout << "name : " << full_name << " , age : " << age << std::endl;
	}
private : 
	std::string full_name;
	int age;
	
public : 
	//static variable declaration
	static int person_count;
};


#endif //PERSON_H