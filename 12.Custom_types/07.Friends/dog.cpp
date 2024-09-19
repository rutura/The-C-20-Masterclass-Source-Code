#include "dog.h"
#include <fmt/format.h>

Dog::Dog(const std::string &name, int age)
  : m_name{ name }, m_age{ age } {}

/*void debug_dog_info(const ::Dog &d) { fmt::println("Dog [ name : {}, age: {} ] ", d.m_name, d.m_age); }

void debug_dog_info()
{
  Dog dog1("Milou", 3);
  dog1.m_name = "Fluffy";
  fmt::println("Dog [ name : {}, age: {} ] ", dog1.m_name, dog1.m_age);
}*/

void Cat::print_dog_info(const Dog &d) const { fmt::println("Dog [ name : {}, age: {}] ", d.m_name, d.m_age); }