module;

#include <fmt/format.h>
#include <string>

export module dog;

// #1: Friend functions

/*
export class Dog
{
  friend void debug_dog_info(const Dog &d);
  friend void debug_dog_info();

public:
  Dog(const std::string &name, int age) : m_name{ name }, m_age{ age } {}

private:
  std::string m_name;
  int m_age;
};


export  void debug_dog_info(const Dog &d) { fmt::println("Dog [ name : {}, age: {} ] ", d.m_name, d.m_age); }

export void debug_dog_info()
{
	Dog dog1("Milou", 3);
	dog1.m_name = "Fluffy";
	fmt::println("Dog [ name : {}, age: {} ] ", dog1.m_name, dog1.m_age);
}
*/


// #2: Friend classes

export class Dog
{
  friend class Cat;

public:
  Dog(const std::string &name, int age) : m_name{ name }, m_age{ age } {}

private:
  std::string m_name;
  int m_age;
};

export class Cat
{
public:
  void print_dog_info(const Dog &d) const { fmt::println("Dog [ name : {}, age: {}] ", d.m_name, d.m_age); }
};