#include "person.h"
#include <iostream>

Person::Person(std::string name) : m_name{name}
{
    std::cout << "Constructor for person  " << m_name << " called." << std::endl;
}

Person::~Person()
{
    std::cout << "Destructor for person  " << m_name << " called." << std::endl;
}

