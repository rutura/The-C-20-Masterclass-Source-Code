#include "feline.h"

Feline::Feline(const std::string& fur_style, const std::string& description)
    : Animal(description) , m_fur_style(fur_style)
{
}

Feline::~Feline()
{
}

