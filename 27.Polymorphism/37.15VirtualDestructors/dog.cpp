#include "dog.h"

Dog::Dog(std::string_view fur_style, std::string_view description)
    : Feline(fur_style,description)
{
}

Dog::~Dog()
{
    std::cout << "Dog destructor called" << std::endl;
}

