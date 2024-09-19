#include "dog.h"

#include <string>
#include <fmt/format.h>

Dog::Dog(std::string name_param)
 : dog_name(name_param) { 
    fmt::println("Constructor for dog {} called ", dog_name); 
}

Dog::~Dog() {
     fmt::println("Destructor for dog {} called", dog_name); 
}

void Dog::print_info() const { fmt::println("Printing dog: {}", dog_name); }

std::string Dog::get_name() const  { return dog_name; }