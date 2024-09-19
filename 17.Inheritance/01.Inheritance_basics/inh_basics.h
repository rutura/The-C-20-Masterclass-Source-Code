#pragma once

#include <string>
#include <iostream>
#include <string_view>

namespace inh_basics {

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

private:
  std::string first_name{ "Mysterious" };
  std::string last_name{ "Person" };
};

//Player

class Player : public Person
{
  friend std::ostream &operator<<(std::ostream &out, const Player &player);

public:
  Player() = default;
  Player(std::string_view game_param);

private:
  std::string m_game{ "None" };
};

}