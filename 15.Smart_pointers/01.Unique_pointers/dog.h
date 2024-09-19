#pragma once

#include <string>

class Dog
{
public:
  explicit Dog(std::string name_param);
  Dog() = default;
  ~Dog();

  void print_info() const;

  std::string get_name() const;

  void set_dog_name(const std::string &name) { dog_name = name; }

private:
  std::string dog_name{ "Puffy" };
};