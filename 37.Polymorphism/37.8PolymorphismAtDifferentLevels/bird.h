#ifndef BIRD_H
#define BIRD_H
#include "animal.h"
class Bird : public Animal
{
public:
  Bird() = default;
  Bird(std::string_view wing_color, std::string_view description);

  ~Bird();

  virtual void fly() const { fmt::println("Bird::fly() called for bird : {}", m_description); }

private:
  std::string m_wing_color;
};

#endif// BIRD_H
