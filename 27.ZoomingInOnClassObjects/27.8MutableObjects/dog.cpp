#include "dog.h"

Dog::Dog(const std::string &name_param, const std::string &breed_param, unsigned int age_param)
{
  m_name = name_param;
  m_breed = breed_param;
  m_age = age_param;
}


// Utility functions
void Dog::print_info() const
{
  ++m_print_info_count;
  fmt::println("Dog ({}): [ name: {}, breed: {}, age: {}, print_count: {}]",
    fmt::ptr(this),
    this->m_name,
    this->m_breed,
    this->m_age,
    m_print_info_count);
}