module;

#include <fmt/format.h>
#include <string>

export module person;

// #5: Copy constructors

export class Person
{
private:
  std::string last_name{};
  std::string first_name{};
  int *age{};

public:
  // Constructors
  Person() = default;
  Person(const std::string &last_name_param, const std::string &first_name_param, int age_param);
  Person(const std::string &last_name_parm, const std::string &first_name_param);
  Person(const std::string &last_name);

  // Copy Constructor
  // Person(const Person source_p); // BAD : Potential for an endles chain of copy constructor calls

  // Memberwise copy
  // Person(const Person& source_p);

  // Don't blindly copy the pointer
  Person(const Person &source_p);
  ~Person();

  // Setters
  void set_first_name(const std::string &first_name) { this->first_name = first_name; }
  void set_last_name(const std::string &last_name) { this->last_name = last_name; }
  void set_age(int age) { *(this->age) = age; }// Remember to dereference

  // Getters
  const std::string &get_first_name() const { return first_name; }
  const std::string &get_last_name() const { return last_name; }
  int *get_age() const { return age; };

  // Utilities
  void print_info()
  {
    fmt::println("Person object at : {} [ Last_name: {}, First_name: {}, age: {}, age address: {}]",
      fmt::ptr(this),
      last_name,
      first_name,
      *age,
      fmt::ptr(age));
  }
};

//Implementations
Person::~Person()
{
  delete age;// Make sure that you are not leaking memory
}
Person::Person(const std::string &last_name) : Person(last_name, "") {}
Person::Person(const std::string &last_name_param, const std::string &first_name_param)
  : Person(last_name_param, first_name_param, 0)
{}
Person::Person(const std::string &last_name_param, const std::string &first_name_param, int age_param)
  : last_name(last_name_param), first_name(first_name_param), age(new int(age_param))
{}

/*
Person::Person(const Person source_p)  // BAAAAD!
    : last_name(source_p.get_last_name()),
        first_name(source_p.get_last_name()),
        age(source_p.get_age())

{

}
*/


// Memberwise copy : BAD
/*
Person::Person(const Person& source_p)
    : last_name(source_p.get_last_name()),
        first_name(source_p.get_first_name()),
        age(source_p.get_age())

{
    fmt::println( "Copy constructor called" );

}
*/

// Don't blindly copy pointer member variables
/*
Person::Person(const Person& source_p)
    : last_name(source_p.get_last_name()),
        first_name(source_p.get_first_name()),
        age(new int(*(source_p.get_age())))

{
    fmt::println( "Copy constructor called" );

}
*/

// Delegate from the copy constructor
Person::Person(const Person &source_p)
  : Person(source_p.get_last_name(), source_p.get_first_name(), *(source_p.get_age()))
{
  fmt::println("Copy constructor called");
}
