#pragma once

#include <fmt/format.h>
#include <string>
#include <string_view>
/*
                            Animal
                   Feline                Bird
                Dog    Cat           Crow    Pigeon
        Bulldog            Wildcat

*/

namespace final_keyword {

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

  // The run method in subclasses of dog can't be overrided
  // further, derived classes are forced to use the implmenetation in Dog
  void run() const override final { fmt::println("Dog::run called"); }
};

//Bulldog class
class BullDog : public Dog
{
public:
  BullDog();
  virtual ~BullDog();


  // Will throw a compiler error
  /*
  virtual void run() const override{
      fmt::println( "Bulldog::run() called" );
  }
  */
};

//Cat class
class Cat final : public Feline
{
public:
  Cat() = default;
  Cat(std::string_view fur_style, std::string_view description);
  virtual ~Cat();

  // Interesting fact #2
  // Useless virtual method. Cat is final, so no one will be deriving from
  // this class and have a chance to specialize it
  virtual void miaw() const { fmt::println("Cat::miaw() called for cat {}", m_description); }

  // This method is useful though
  void virtual run() const override
  {
    //
  }
};


//Wildcat class
class WildCat/* : public Cat */// Can not derive from final base class
{
public:
  WildCat();
  ~WildCat();
};

//Implementation
WildCat::WildCat() {}

WildCat::~WildCat() {}


//Bird class
class Bird : public Animal
{
public:
  Bird() = default;
  Bird(std::string_view wing_color, std::string_view description);

  virtual ~Bird();

  // This is contradictory : virtual and final have counter acting effects.
  // Final wins here
  virtual void fly() const final { fmt::println("Bird::fly() called for bird : {}", m_description); }

private:
  std::string m_wing_color;
};


//Crow class
class Crow : public Bird
{
public:
  Crow() = default;
  Crow(std::string_view wing_color, std::string_view description);
  virtual ~Crow();

  virtual void cow() const { fmt::println("Crow::cow called fro crow : {}", m_description); }

  // This will give a compiler error is fly is marked as final in Bird
  /*
  virtual void fly() const override{

  }
  */
};

//Pigeon class
class Pigeon : public Bird
{
public:
  Pigeon() = default;
  Pigeon(std::string_view wing_color, std::string_view description);
  virtual ~Pigeon();

  virtual void coo() const { fmt::println("Pigeon::coo called for pigeon : {}", m_description); }
};


}// namespace final_keyword