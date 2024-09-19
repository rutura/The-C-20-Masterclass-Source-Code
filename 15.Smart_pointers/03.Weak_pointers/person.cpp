#include "person.h"


//Implementations
Person::Person(std::string name) : m_name{ name }
{
  fmt::println("Constructor for person  {} called ", m_name, " called.");
}

Person::~Person() { fmt::println("Destructor for person  {} called ", m_name, " called."); }