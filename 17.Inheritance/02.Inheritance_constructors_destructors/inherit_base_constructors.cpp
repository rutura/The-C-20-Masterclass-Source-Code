#include "inherit_base_constructors.h"

namespace inherit_base_constructors{
//Implementation
Person::Person() { std::cout << "Default constructor for Person called..." << std::endl; }

Person::Person(std::string_view fullname, int age, std::string_view address)
: m_full_name{ fullname }, m_age{ age }, m_address{ address }
{
  std::cout << "Custom constructor for Person called..." << std::endl;
}

Person::Person(const Person &source) : m_full_name(source.m_full_name), m_age(source.m_age), m_address(source.m_address)
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

Person::~Person() {}


//Implementation
/*
Engineer::Engineer()
{
    std::cout << "Default constructor for Engineer called..." << std::endl;
}

Engineer::Engineer(const Engineer& source)
    : Person(source)
        , contract_count(source.contract_count)
{
    std::cout << "Custom copy constructor for Engineer called..." << std::endl;
}
*/
Engineer::Engineer(std::string_view fullname, int age, std::string_view address, int contract_count_param)
: Person(fullname, age, address), contract_count(contract_count_param)
{
  std::cout << "Custom constructor for Engineer called..." << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Engineer &operand)
{
  out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
      << ",address : " << operand.get_address() << ",contract_count : " << operand.contract_count << "]";
  return out;
}

Engineer::~Engineer() {}

}