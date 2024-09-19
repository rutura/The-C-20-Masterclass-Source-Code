#include "person.h"

#include <iostream>
#include <string>

// Definition
int Person::person_count = 8;


Person::Person(const std::string &names_param, int age_param) : full_name{ names_param }, age{ age_param }
{
  ++person_count;
}

void Person::print_info() const {
  //fmt::println("name : {}, age: {}", full_name, age);
  std::cout << "name: " << full_name << ", age: " << age << "\n";
}

