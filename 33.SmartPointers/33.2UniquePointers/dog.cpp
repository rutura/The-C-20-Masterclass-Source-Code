#include "dog.h"
#include <fmt/format.h>
Dog::Dog(std::string name_param) : dog_name(name_param)
{
    fmt::println( "Constructor for dog {} called " , dog_name  );
}

Dog::~Dog()
{
    fmt::println( "Destructor for dog {} called" , dog_name  );
}

