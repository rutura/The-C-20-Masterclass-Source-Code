#ifndef PERSON_H
#define PERSON_H

#include <memory>
#include <string>

class Dog;
class Person
{
public:
  Person(std::string name);
  ~Person();

  void adopt_dog(std::unique_ptr<Dog> dog);

private:
  int m_age;
  std::string m_name;
};

#endif// PERSON_H
