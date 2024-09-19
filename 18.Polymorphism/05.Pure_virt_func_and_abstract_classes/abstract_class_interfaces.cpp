#include "abstract_class_interfaces.h"


namespace abstract_class_interfaces {
//Implementation
std::ostream &operator<<(std::ostream &out, const StreamInsertable &operand)
{
  operand.stream_insert(out);
  return out;
}

//Implementation
Animal::Animal(const std::string &description)
  : m_description(description) {}

Animal::~Animal() {}


//Implementation
Feline::Feline(const std::string &fur_style, const std::string &description)
  : Animal(description), m_fur_style(fur_style) {}

Feline::~Feline() {}


//Implementation
Dog::Dog(const std::string &fur_style, const std::string &description)
  : Feline(fur_style, description) {}

Dog::~Dog() {}

//Implementation
Cat::Cat(const std::string &fur_style, const std::string &description)
  : Feline(fur_style, description) {}

Cat::~Cat() {}

//Implementation
Bird::Bird(const std::string &wing_color, const std::string &description)
  : Animal(description), m_wing_color(wing_color) {}

Bird::~Bird() {}

//Implementation
Crow::Crow(const std::string &wing_color, const std::string &description)
  : Bird(wing_color, description) {}

Crow::~Crow() {}

//Implementation
Pigeon::Pigeon(const std::string &wing_color, const std::string &description)
  : Bird(wing_color, description) {}

Pigeon::~Pigeon() {}


}