#include <fmt/format.h>
#include "integer.h"

Integer::Integer(int value) : inner_int(value)
{
	fmt::println( "Constructor for Integer {} called" , inner_int );
}

Integer::~Integer()
{
}

