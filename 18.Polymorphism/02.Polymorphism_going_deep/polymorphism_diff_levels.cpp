#include "polymorphism_diff_levels.h"

namespace polymorphism_diff_levels {
//Implementation
Animal::Animal(std::string_view description)
  : m_description(description) {}

Animal::~Animal() {}


//Implementation
Feline::Feline(std::string_view fur_style, std::string_view description)
  : Animal(description), m_fur_style(fur_style) {}

Feline::~Feline() {}

//Implementation
Dog::Dog(std::string_view fur_style, std::string_view description)
  : Feline(fur_style, description) {}

Dog::~Dog() {}

//Implementation
Cat::Cat(std::string_view fur_style, std::string_view description)
  : Feline(fur_style, description) {}

Cat::~Cat() {}


//Implementation
Bird::Bird(std::string_view wing_color, std::string_view description)
  : Animal(description), m_wing_color(wing_color) {}

Bird::~Bird() {}

//Implementation
Crow::Crow(std::string_view wing_color, std::string_view description)
  : Bird(wing_color, description) {}

Crow::~Crow() {}


//Implementation
Pigeon::Pigeon(std::string_view wing_color, std::string_view description)
  : Bird(wing_color, description) {}

Pigeon::~Pigeon() {}


}