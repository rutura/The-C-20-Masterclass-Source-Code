#include "virtual_destructors.h"

namespace virtual_destructors {
//Implementation
Animal::Animal(std::string_view description)
  : m_description(description) {}

Animal::~Animal() { fmt::println("Animal destructor called"); }

//Implementation
Feline::Feline(std::string_view fur_style, std::string_view description)
  : Animal(description), m_fur_style(fur_style) {}

Feline::~Feline() { fmt::println("Feline destructor called"); }


//Implementation
Dog::Dog(std::string_view fur_style, std::string_view description)
  : Feline(fur_style, description) {}

Dog::~Dog() { fmt::println("Dog destructor called"); }


}