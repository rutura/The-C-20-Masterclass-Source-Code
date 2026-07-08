#include "person.h"

Person::~Person()
{
	delete age; // Make sure that you are not leaking memory
}
Person::Person(const std::string& last_name)
	: Person(last_name,"")
{
}
Person::Person(const std::string& last_name_param, const std::string& first_name_param)
	: Person(last_name_param,first_name_param,0)
{
}
Person::Person(const std::string& last_name_param, const std::string& first_name_param, int age_param)
	: 	last_name(last_name_param),
		first_name(first_name_param),
		age(new int(age_param))
{
}

//Delegate from the copy constructor
Person::Person(const Person& source_p) 
    : Person(source_p.get_last_name(),source_p.get_first_name(),*(source_p.get_age()))
{
    std::cout << "Copy constructor called for " << last_name <<  std::endl;

}

