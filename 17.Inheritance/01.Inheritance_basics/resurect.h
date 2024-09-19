#pragma once

#include <string>
#include <iostream>
#include <string_view>

namespace resurect {
class Person
{
  friend std::ostream &operator<<(std::ostream &, const Person &person);

public:
  Person() = default;
  Person(std::string_view fullname,
    int age,
    const std::string address);
  ~Person();

  //Getters
  std::string get_full_name() const { return m_full_name; }

  int get_age() const { return m_age; }

  std::string get_address() const { return m_address; }


  int add(int a, int b) const { return a + b; }

  int add(int a, int b, int c) const { return a + b + c; }

  void do_something() const;

public:
  std::string m_full_name{ "None" };

protected:
  int m_age{ 0 };

private :
  std::string m_address{ "None" };
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
    //m_address = "897-78-723"; Compiler error
  }

public :
  using Person::add;

protected :
  using Person::get_full_name;
  using Person::get_age;
  using Person::get_address;
  //using Person::m_address; // Compiler error

  int get_contract_count() const { return contract_count; }

private :
  int contract_count{ 0 };
};

//CivilEngineer class
class CivilEngineer : public Engineer
{
  friend std::ostream &operator<<(std::ostream &, const CivilEngineer &operand);

public:
  CivilEngineer();
  ~CivilEngineer();

  void build_road()
  {
    //get_full_name(); // Compiler error
    ///m_full_name = "Daniel Gray"; //Compiler error
    //m_age = 45; // Compiler error

    add(10, 2);
    add(10, 2, 4);
  }

public :
  //using Person::do_something; // Compiler error

private :
  std::string m_speciality{ "None" };

};
}// namespace resurect