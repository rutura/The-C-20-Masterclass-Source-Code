#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <fmt/format.h>

namespace abstract_class_interfaces {

//StreamInsertable class
class StreamInsertable
{
  friend std::ostream &operator<<(std::ostream &out, const StreamInsertable &operand);

public :
  virtual void stream_insert(std::ostream &out) const =0;
};

//Animal
class Animal : public StreamInsertable
{
public:
  Animal() = default;
  Animal(const std::string &description);
  ~Animal();

  virtual void breathe() const { std::cout << "Animal::breathe called for : " << m_description << std::endl; }

  //Stream insertable interface
  virtual void stream_insert(std::ostream &out) const override
  {
    out << "Animal [description : " << m_description << "]";
  }

protected:
  std::string m_description;
};

//Feline
class Feline : public Animal
{
public:
  Feline() = default;
  Feline(const std::string &fur_style, const std::string &description);
  ~Feline();

  virtual void run() const { std::cout << "Feline " << m_description << " is running" << std::endl; }

  //Stream insertable interface
  virtual void stream_insert(std::ostream &out) const override
  {
    out << "Feline [description : " << m_description << ", fur_style : " <<
      m_fur_style << "]";
  }

  std::string m_fur_style;
};

//Dog
class Dog : public Feline
{
public:
  Dog() = default;
  Dog(const std::string &fur_style, const std::string &description);
  ~Dog();

  virtual void bark() const { std::cout << "Dog::bark called : Woof!" << std::endl; }

  virtual void stream_insert(std::ostream &out) const override
  {
    out << "Dog [description : " << m_description << ", fur_style : " <<
      m_fur_style << "]";
  }

};


//Cat
class Cat : public Feline
{
public:
  Cat() = default;
  Cat(const std::string &fur_style, const std::string &description);
  ~Cat();

  virtual void miaw() const { std::cout << "Cat::miaw() called for cat " << m_description << std::endl; }

  virtual void stream_insert(std::ostream &out) const override
  {
    out << "Cat [description : " << m_description << ", fur_style : " <<
      m_fur_style << "]";
  }


};

//Bird
class Bird : public Animal
{
public:
  Bird() = default;
  Bird(const std::string &wing_color, const std::string &description);

  ~Bird();

  virtual void fly() const { std::cout << "Bird::fly() called for bird : " << m_description << std::endl; }

  virtual void stream_insert(std::ostream &out) const override
  {
    out << "Bird [description : " << m_description << ", wing_color : " <<
      m_wing_color << "]";
  }

protected :
  std::string m_wing_color;
};

//Crow
class Crow : public Bird
{
public:
  Crow() = default;
  Crow(const std::string &wing_color, const std::string &description);
  ~Crow();

  virtual void cow() const { std::cout << "Crow::cow called fro crow : " << m_description << std::endl; }

  virtual void stream_insert(std::ostream &out) const override
  {
    out << "Crow [description : " << m_description << ", wing_color : " <<
      m_wing_color << "]";
  }

};

//Pigeon
class Pigeon : public Bird
{
public:
  Pigeon() = default;
  Pigeon(const std::string &wing_color, const std::string &description);
  ~Pigeon();

  virtual void coo() const { std::cout << "Pigeon::coo called for pigeon : " << m_description << std::endl; }

  virtual void stream_insert(std::ostream &out) const override
  {
    out << "Pigeon [description : " << m_description << ", wing_color : " <<
      m_wing_color << "]";
  }

};

//Point class
class Point : public StreamInsertable
{
public :
  Point() = default;

  Point(double x, double y)
    : m_x(x), m_y(y) {}

  virtual void stream_insert(std::ostream &out) const override { out << "Point [x: " << m_x << ",y: " << m_y << "]"; }

private :
  double m_x;
  double m_y;
};


}// namespace abstract_class_interfaces