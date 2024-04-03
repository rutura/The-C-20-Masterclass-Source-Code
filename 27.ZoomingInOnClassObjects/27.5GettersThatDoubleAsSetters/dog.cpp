#include "dog.h"

Dog::Dog(const std::string &name_param, const std::string &breed_param, unsigned int age_param)
{
  m_name = name_param;
  m_breed = breed_param;
  m_age = age_param;
}

/*
 //Getters
 std::string Dog::get_name() const{
     //return m_name;
     return this->m_name;
 }
 std::string Dog::get_breed() const {
     return m_breed;
 }
 unsigned int Dog::get_age() const{
     return m_age;
 }

 //Setters
 void Dog::set_name(std::string name_param){
    // m_name = name_param;
    this->m_name = name_param;
 }
 void Dog::set_breed(std::string breed_param){
     m_breed = breed_param;
 }
 void Dog::set_age(unsigned int age){
     m_age = age;
 }
 */

// Utility functions
void Dog::print_info()
{
  fmt::println("Dog ({}): [ name: {}, bread: {}, age: {}]", fmt::ptr(this), this->m_name, this->m_breed, this->m_age);
}