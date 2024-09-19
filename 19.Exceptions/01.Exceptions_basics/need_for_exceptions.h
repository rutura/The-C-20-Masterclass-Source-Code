#pragma once
#include <fmt/format.h>


namespace need_for_exceptions {

class Animal
{
public:
  Animal() = default;
  virtual void breathe() const {};

private:
  std::string m_description;
};


class Dog : public Animal
{
public:
  Dog() = default;
  virtual void breathe() const override {};
  void run() { fmt::println("Dog running..."); }

private:
  std::string m_fur_color;
};

void process_parameters(int par_a, int par_b);
}// namespace need_for_exceptions