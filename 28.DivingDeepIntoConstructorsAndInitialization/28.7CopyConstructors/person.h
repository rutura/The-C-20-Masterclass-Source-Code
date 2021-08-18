#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person
{
private : 
	 std::string last_name{};
	 std::string first_name{};
	 int * age{};
public:
	//Constructors
    Person() = default;
    Person(const std::string& last_name_param, const std::string& first_name_param, int age_param);
    Person(const std::string& last_name_parm, const std::string& first_name_param);
    Person(const std::string& last_name);

    //Copy Constructor
   // Person(const Person source_p); // BAD : Potential for an endles chain of copy constructor calls

    //Memberwise copy
    //Person(const Person& source_p);

    //Don't blindly copy the pointer
    Person(const Person& source_p);
    ~Person();
	
	//Setters 
	void set_first_name(const std::string& first_name) {this->first_name = first_name;}
	void set_last_name(const std::string& last_name) {this->last_name = last_name;}
	void set_age(int age) {*(this->age) = age;} // Remember to dereference
	
	//Getters
	const std::string& get_first_name() const {return first_name;}
	const std::string& get_last_name() const {return last_name;}
	int* get_age() const{ return age;};

	//Utilities
	void print_info(){
		std::cout << "Person object at : " << this 
			<<" [ Last_name : " << last_name 
			<< ", First_name :  " << first_name 
			<< " ,age : " << *age 
			<< " , age address : " << age 
			<< " ]" << std::endl;
	}
};

#endif // PERSON_H
