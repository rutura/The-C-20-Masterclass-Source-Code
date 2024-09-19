#pragma once

#include <string>

// Declaration
class Person
{
public:
  // Declaration for the constructor
  Person(const std::string &names_param, int age_param);

  void print_info() const;

private:
  std::string full_name;
  int age;

public:
  // static variable declaration
  static int person_count;
};