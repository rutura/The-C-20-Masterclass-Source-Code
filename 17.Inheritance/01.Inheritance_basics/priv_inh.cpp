#include "priv_inh.h"


namespace priv_inh {

//Implementations

Person::Person(std::string_view fullname, int age, const std::string address)
  : m_full_name{ fullname }, m_age{ age }, m_address{ address } {}

std::ostream &operator<<(std::ostream &out, const Person &person)
{
  out << "Person [Full name :" << person.get_full_name() << ", Age:" << person.get_age()
    << ", Address:" << person.get_address() << "]";
  return out;
}

Person::~Person() {}

//Implementations
Engineer::Engineer() {}

std::ostream &operator<<(std::ostream &out, const Engineer &operand)
{
  out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
    << ",address : " << operand.get_address() << ",contract_count : " << operand.contract_count << "]";
  return out;
}

Engineer::~Engineer() {}



//Implementations
CivilEngineer::CivilEngineer() {}

std::ostream &operator<<(std::ostream &out, const CivilEngineer &operand)
{
  /*
  out << "CivilEngineer [Full name : " << operand.get_full_name() <<
                  ",age : " << operand.get_age() <<
                  //",address : " << operand.get_address() <<
                  ",contract_count : " << operand.contract_count <<
                  ",speciality : " << operand.m_speciality << "]";
                  */


  return out;
}


CivilEngineer::~CivilEngineer() {}



}