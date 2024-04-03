#ifndef CAT_H
#define CAT_H
#include "feline.h"
class Cat : public Feline
{
public:
  Cat() = default;
  Cat(std::string_view fur_style, std::string_view description);
  virtual ~Cat();

  virtual void miaw() const { fmt::println("Cat::miaw() called for cat {}", m_description); }

  virtual void breathe() const { fmt::println("Cat::breathe called for : {}", m_description); }

  virtual void run() const override { fmt::println("Cat {} is running", m_description); }
};

#endif// CAT_H
