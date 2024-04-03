#include <fmt/format.h>

class Dog
{
  friend class Cat;

public:
  Dog(const std::string &name, int age) : m_name{ name }, m_age{ age } {}

private:
  std::string m_name;
  int m_age;
};

class Cat
{
public:
  void print_dog_info(const Dog &d) const { fmt::println("Dog [ name : {}, age: {}] ", d.m_name, d.m_age); }
};

int main()
{

  Cat cat1;

  Dog dog1("Fluffly", 2);

  cat1.print_dog_info(dog1);

  return 0;
}