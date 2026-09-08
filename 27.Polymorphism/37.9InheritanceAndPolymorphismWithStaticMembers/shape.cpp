#include "shape.h"

int Shape::m_count{0};

Shape::Shape(std::string_view description)
    : m_description(description)
{
    ++m_count;
}

Shape::Shape()
    : Shape("NoDescription")
{
}

Shape::~Shape()
{
    --m_count;
}

