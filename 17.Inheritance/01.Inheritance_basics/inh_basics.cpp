#include "inh_basics.h"


namespace inh_basics {

//Implementations
Person::Person() {}

Person::Person(std::string &first_name_param, std::string &last_name_param)
  : first_name(first_name_param), last_name(last_name_param) {}

std::ostream &operator<<(std::ostream &out, const Person &person)
{
  out << "Person [" << person.first_name << " " << person.last_name << "]";
  return out;
}

Person::~Person() {}

//Implementations

Player::Player(std::string_view game_param)
  : m_game(game_param)
{
  // first_name = "John"; Compiler errors
  // last_name = "Snow";
}

std::ostream &operator<<(std::ostream &out, const Player &player)
{

  out << "Player : [ game : " << player.m_game << " names : " << player.get_first_name() << " "
    << player.get_last_name() << "]";
  return out;
}


}