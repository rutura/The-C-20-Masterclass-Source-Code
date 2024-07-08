module;

#include <memory>
#include <string>
#include <fmt/format.h>

export module person;
/*

import dog;

export class Person
{
public:
  Person(std::string name);
  ~Person();

  void adopt_dog(std::unique_ptr<Dog> dog);

private:
  int m_age;
  std::string m_name;
};

//Implemenations
Person::Person(std::string name) : m_name{ name } {}

void Person::adopt_dog(std::unique_ptr<Dog> dog)
{
  fmt::println("{} just adopted the dog {}", m_name, dog->get_name());
}


Person::~Person() {}
*/