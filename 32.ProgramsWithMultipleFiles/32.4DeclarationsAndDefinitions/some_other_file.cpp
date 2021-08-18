#include "person.h"

//Declaration
int Person::person_count = 8;


Person::Person(const std::string& names_param, int age_param)
    : full_name{names_param}, age{age_param}
{
    ++person_count;
}




double add(double a, double b){
    return a + b;
}