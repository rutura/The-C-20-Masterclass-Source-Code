#pragma once

#include <fmt/format.h>
#include <iostream>
#include <string>
#include <string_view>


namespace protected_members {


//Person class
class Person
{
  friend std::ostream &operator<<(std::ostream &out, const Person &person);

public:
  Person();
  Person(std::string &first_name_param, std::string &last_name_param);
  ~Person();

  // Getters
  std::string get_first_name() const { return first_name; }

  std::string get_last_name() const { return last_name; }

  // Setters
  void set_first_name(std::string_view fn) { first_name = fn; }
  void set_last_name(std::string_view ln) { last_name = ln; }

protected:
  std::string first_name{ "Mysterious" };
  std::string last_name{ "Person" };
};


//Player class

class Player : public Person
{
  friend std::ostream &operator<<(std::ostream &out, const Player &player);

public:
  Player() = default;
  Player(std::string_view game_param, std::string_view first_name_param, std::string_view last_name_param);

private:
  std::string m_game{ "None" };
};

}// namespace protected_members