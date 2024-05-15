#ifndef PIGEON_H
#define PIGEON_H
#include "bird.h"
class Pigeon : public Bird
{
public:
  Pigeon() = default;
  Pigeon(std::string_view wing_color, std::string_view description);
  ~Pigeon();

  virtual void coo() const { fmt::println("Pigeon::coo called for pigeon :{} ", m_description); }

  virtual void breathe() const { fmt::println("Pigeon::breathe called for :{} ", m_description); }

  virtual void fly() const override { fmt::println("Pigeon::fly() called for bird :{} ", m_description); }
};

#endif// PIGEON_H
