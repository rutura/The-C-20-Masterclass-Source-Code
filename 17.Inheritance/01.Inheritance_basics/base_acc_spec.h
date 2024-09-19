#pragma once

#include <fmt/format.h>
#include <string>
#include <iostream>
#include <string_view>

namespace base_acc_spec {

//Person
class Person
{
  friend std::ostream &operator<<(std::ostream &, const Person &person);

public:
  Person() = default;
  Person(std::string_view fullname, int age, const std::string address);
  ~Person();

  // Getters
  std::string get_full_name() const { return m_full_name; }

  int get_age() const { return m_age; }

  std::string get_address() const { return m_address; }

public:
  std::string m_full_name{ "None" };

protected:
  int m_age{ 0 };

private:
  std::string m_address{ "None" };
};


//Player class
class Player : public Person
{
  friend std::ostream &operator<<(std::ostream &out, const Player &player);

public:
  Player();
  ~Player();

  // See the access we have to inherited members from Person
  void play()
  {

    m_full_name = "John Snow";// OK
    m_age = 55;// OK
    // m_address = "DSAKFD;ASKFJ;DKAS"; Compiler error
  }

private:
  int m_career_start_year{ 0 };
  double m_salary{ 0.0 };
  int health_factor{ 0 };// Let's say that it's 0~10
};


//Nurse class
class Nurse : protected Person
{
  friend std::ostream &operator<<(std::ostream &, const Nurse &operand);

public:
  Nurse();
  ~Nurse();

  void treat_unwell_person()
  {
    m_full_name = "John Snow";// OK
    m_age = 23;// OK
    // m_address = "897-78-723"; Compiler error
  }

private:
  int practice_certificate_id{ 0 };
};


//Engineer class
class Engineer : private Person
{
  friend std::ostream &operator<<(std::ostream &out, const Engineer &operand);

public:
  Engineer();

  ~Engineer();

  void build_something()
  {
    m_full_name = "John Snow";// OK
    m_age = 23;// OK
    // m_address = "897-78-723"; Compiler error
  }

private:
  int contract_count{ 0 };
};

}// namespace base_acc_spec