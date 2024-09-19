#pragma once

#include <fmt/format.h>
#include <string>
#include <string_view>


namespace virtual_destructors {

//Animal class
class Animal
{
public:
  Animal() = default;
  Animal(std::string_view description);
  virtual ~Animal();

  virtual void breathe() const { fmt::println("Animal::breathe called for : {}", m_description); }

protected:
  std::string m_description;
};

//Feline class
class Feline : public Animal
{
public:
  Feline() = default;
  Feline(std::string_view fur_style, std::string_view description);
  virtual ~Feline();

  virtual void run() const { fmt::println("Feline {} is running", m_description); }
  std::string m_fur_style;
};

//Dog class
class Dog : public Feline
{
public:
  Dog() = default;
  Dog(std::string_view fur_style, std::string_view description);
  virtual ~Dog();

  virtual void bark() const { fmt::println("Dog::bark called : Woof!"); }
};

}// namespace virtual_destructors