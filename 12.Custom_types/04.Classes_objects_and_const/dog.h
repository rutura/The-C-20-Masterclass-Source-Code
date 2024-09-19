#pragma once

#include <string>

//Non const member functions - a separate implementation of Dog. Comment out all others for this to work.
/*
class Dog
{
public:
  Dog() = default;
  Dog(std::string_view name_param, std::string_view breed_param, unsigned int age_param);

  // Getters
  std::string_view get_name();
  std::string_view get_breed();
  unsigned int get_age();

  // Setters
  void set_name(std::string_view name_param);
  void set_breed(std::string_view breed_param);
  void set_age(unsigned int age);

  // Utility functions
  void print_info();

private:
  std::string_view m_name;
  std::string_view m_breed;
  unsigned int m_age;
};

Dog::Dog(std::string_view name_param, std::string_view breed_param, unsigned int age_param)
{
  m_name = name_param;
  m_breed = breed_param;
  m_age = age_param;
}

// Getters
std::string_view Dog::get_name()
{
  // return m_name;
  return this->m_name;
}
std::string_view Dog::get_breed() { return m_breed; }
unsigned int Dog::get_age() { return m_age; }

// Setters
void Dog::set_name(std::string_view name_param)
{
  // m_name = name_param;
  this->m_name = name_param;
}
void Dog::set_breed(std::string_view breed_param) { m_breed = breed_param; }
void Dog::set_age(unsigned int age) { m_age = age; }

// Utility functions
void Dog::print_info()
{
  fmt::println("Dog ({}): [ name: {}, bread: {}, age: {}]", fmt::ptr(this), this->m_name, this->m_breed, this->m_age);
}
*/


//Const member functions - a separate implementation of Dog. Comment out all others for this to work.
/*
class Dog
{
public:
  Dog() = default;
  Dog(std::string_view name_param, std::string_view breed_param, unsigned int age_param);

  // Getters
  std::string_view get_name() const;
  std::string_view get_breed() const;
  unsigned int get_age() const;

  // Setters
  void set_name(std::string_view name_param);
  void set_breed(std::string_view breed_param);
  void set_age(unsigned int age);

  // Utility functions
  void print_info() const;

private:
  std::string_view m_name;
  std::string_view m_breed;
  unsigned int m_age;
};

Dog::Dog(std::string_view name_param, std::string_view breed_param, unsigned int age_param)
{
  m_name = name_param;
  m_breed = breed_param;
  m_age = age_param;
}

// Getters
std::string_view Dog::get_name() const
{
  // return m_name;
  return this->m_name;
}
std::string_view Dog::get_breed() const { return m_breed; }
unsigned int Dog::get_age() const { return m_age; }

// Setters
void Dog::set_name(std::string_view name_param)
{
  // m_name = name_param;
  this->m_name = name_param;
}
void Dog::set_breed(std::string_view breed_param) { m_breed = breed_param; }
void Dog::set_age(unsigned int age) { m_age = age; }

// Utility functions
void Dog::print_info() const
{
  fmt::println("Dog ({}): [ name: {}, bread: {}, age: {}]", fmt::ptr(this), this->m_name, this->m_breed, this->m_age);
}
*/


//Mutable objects - a separate implementation of Dog. Comment out all others for this to work
class Dog
{
public:
  Dog() = default;
  Dog(const std::string &name_param, const std::string &breed_param, unsigned int age_param);

  std::string &name() { return m_name; }
  const std::string &name() const { return m_name; }


  std::string &breed() { return m_breed; }
  const std::string &breed() const { return m_breed; }


  unsigned int &age() { return m_age; }
  const unsigned int &age() const { return m_age; }

  // Utility functions
  void print_info() const;

private:
  std::string m_name;
  std::string m_breed;
  unsigned int m_age;
  mutable size_t m_print_info_count{};
};
