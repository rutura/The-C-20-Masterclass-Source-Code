#pragma once

#include <string>

// #1: Friend functions

/*
class Dog
{
  friend void debug_dog_info(const Dog &d);
  friend void debug_dog_info();

public:
  Dog(const std::string &name, int age);

private:
  std::string m_name;
  int m_age;
};


 void debug_dog_info(const Dog &d);

void debug_dog_info();
*/


// #2: Friend classes

class Dog
{
  friend class Cat;

public:
  Dog(const std::string &name, int age);

private:
  std::string m_name;
  int m_age;
};

class Cat
{
public:
  void print_dog_info(const Dog &d) const;
};