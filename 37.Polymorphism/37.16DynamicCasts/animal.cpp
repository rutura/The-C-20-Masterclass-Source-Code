#include "animal.h"

Animal::Animal(std::string_view description)
    : m_description(description)
{
}

Animal::~Animal()
{
    fmt::println( "Animal destructor called");
}

