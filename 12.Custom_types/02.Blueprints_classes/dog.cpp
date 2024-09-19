#include "dog.h"

#include <fmt/core.h>

Dog::Dog(std::string_view name_param, std::string_view breed_param, int age_param)
{
  name = name_param;
  breed = breed_param;
  p_age = new int;
  *p_age = age_param;
  fmt::println("Dog constructor called for {}", name);
}

Dog::~Dog()
{
  delete p_age;
  fmt::println("Dog destructor called for : {}", name);
}