#include "dog.h"
#include <fmt/format.h>

//Implementations
Dog::Dog(std::string name_param) : dog_name(name_param)
{
  fmt::println("Constructor for dog {} called ", dog_name, " called.");
}

Dog::~Dog() { fmt::println("Destructor for dog {} called", dog_name, " called"); }

void Dog::print_info() const { fmt::println("Dog [ name : {}]", dog_name); }
