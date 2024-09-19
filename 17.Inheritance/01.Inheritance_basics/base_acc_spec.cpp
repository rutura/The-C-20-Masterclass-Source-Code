#include "base_acc_spec.h"


namespace base_acc_spec {
//Implementation

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
Player::Player() {}

std::ostream &operator<<(std::ostream &out, const Player &player)
{
  out << "Player[Full name : " << player.get_full_name() << ",age : " << player.get_age()
    << ",address : " << player.get_address() << "]";
  return out;
}

Player::~Player() {}


//Implementation
Nurse::Nurse() {}

std::ostream &operator<<(std::ostream &out, const Nurse &operand)
{
  out << "Nurse [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
    << ",address : " << operand.get_address() << ",practice certificate id : " << operand.practice_certificate_id
    << "]";
  return out;
}

Nurse::~Nurse() {}


//Implementation
Engineer::Engineer() {}

std::ostream &operator<<(std::ostream &out, const Engineer &operand)
{
  out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
    << ",address : " << operand.get_address() << ",contract_count : " << operand.contract_count << "]";
  return out;
}

Engineer::~Engineer() {}


}