module;

#include <iostream>
#include <string>
//#include <fmt/format.h>

export module person;

//Trigger ODR on the add function
//export double add(double a, double b);

// Declaration and definition
export class Person
{
public:
  // Declaration for the constructor
  Person(const std::string &names_param, int age_param);

  void print_info() const {
   //fmt::println("name : {}, age: {}", full_name, age); 
   std::cout << "name: " << full_name << ", age: " << age << "\n";
  }

private:
  std::string full_name;
  int age;

public:
  // static variable declaration
  static int person_count;
};