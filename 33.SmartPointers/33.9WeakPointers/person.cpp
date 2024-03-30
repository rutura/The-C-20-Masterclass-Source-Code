#include "person.h"
#include <fmt/format.h>

Person::Person(std::string name) : m_name{name}
{
    fmt::println( "Constructor for person  {}{}" , m_name , " called." );
}

Person::~Person()
{
    fmt::println( "Destructor for person  {}{}" , m_name , " called." );
}

