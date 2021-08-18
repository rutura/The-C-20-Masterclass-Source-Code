#include <iostream>
#include "integer.h"

Integer::Integer(int value) : inner_int(value)
{
	std::cout << "Constructor for Integer " << inner_int << " called" << std::endl;
}

Integer::~Integer()
{
}

