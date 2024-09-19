#include "inh_and_destructors.h"

#include <iostream>

namespace inh_and_destructors {
//Implementation
Person::Person() { std::cout << "Default constructor for Person called..." << std::endl; }

Person::Person(std::string_view fullname, int age, std::string_view address)
  : m_full_name{ fullname }, m_age{ age }, m_address{ address }
{
  std::cout << "Custom constructor for Person called..." << std::endl;
}

Person::Person(const Person &source)
  : m_full_name(source.m_full_name), m_age(source.m_age), m_address(source.m_address)
{
  std::cout << "Custom copy constructor for Person called..." << std::endl;
}

void Person::do_something() const { std::cout << "Hello" << std::endl; }

std::ostream &operator<<(std::ostream &out, const Person &person)
{
  out << "Person [Full name :" << person.get_full_name() << ", Age:" << person.get_age()
    << ", Address:" << person.get_address() << "]";
  return out;
}

Person::~Person() { std::cout << "Destructor for Person called .." << std::endl; }


//Implementation
Engineer::Engineer() { std::cout << "Default constructor for Engineer called..." << std::endl; }

Engineer::Engineer(std::string_view fullname, int age, std::string_view address, int contract_count_param)
  : Person(fullname, age, address), contract_count(contract_count_param)
{
  std::cout << "Custom constructor for Engineer called..." << std::endl;
}

Engineer::Engineer(const Engineer &source)
  : Person(source), contract_count(source.contract_count)
{
  std::cout << "Custom copy constructor for Engineer called..." << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Engineer &operand)
{
  out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
    << ",address : " << operand.get_address() << ",contract_count : " << operand.contract_count << "]";
  return out;
}

Engineer::~Engineer() { std::cout << "Destructor for Engineer called ..." << std::endl; }


//Implementation
CivilEngineer::CivilEngineer() { std::cout << "Default constructor called for CivilEngineer ... " << std::endl; }

CivilEngineer::CivilEngineer(std::string_view fullname,
  int age,
  std::string_view address,
  int contract_count,
  std::string_view speciality)
  : Engineer(fullname, age, address, contract_count), m_speciality(speciality)
{
  std::cout << "Custom constructor called for CivilEngineer ... " << std::endl;
}

CivilEngineer::CivilEngineer(const CivilEngineer &source)
  : Engineer(source), m_speciality(source.m_speciality)
{
  std::cout << "Custom copy constructor called for CivilEngineer ... " << std::endl;
}

std::ostream &operator<<(std::ostream &out, const CivilEngineer &operand)
{
  out << "CivilEngineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
    << ",address : " << operand.get_address() << ",contract_count : " << operand.get_contract_count()
    << ",speciality : " << operand.m_speciality << "]";

  return out;
}

CivilEngineer::~CivilEngineer() { std::cout << "Destructor called for CivilEngineer ..." << std::endl; }

}