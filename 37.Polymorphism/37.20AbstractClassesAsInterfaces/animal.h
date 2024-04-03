#ifndef ANIMAL_H
#define ANIMAL_H

#include "stream_insertable.h"
#include <fmt/format.h>
#include <string>

class Animal : public StreamInsertable
{
public:
  Animal() = default;
  Animal(const std::string &description);
  ~Animal();

  virtual void breathe() const { fmt::println("Animal::breathe called for : {}", m_description); }

  // Stream insertable interface
  virtual void stream_insert(std::ostream &out) const override
  {
    out << "Animal [description : " << m_description << "]";
  }
  void stream_insert(fmt::basic_memory_buffer<char> &out) const override
  {
    fmt::format_to_n(std::back_inserter(out), out.capacity(), "Animal [description: {}]", m_description);
  }

protected:
  std::string m_description;
};

#endif// ANIMAL_H
