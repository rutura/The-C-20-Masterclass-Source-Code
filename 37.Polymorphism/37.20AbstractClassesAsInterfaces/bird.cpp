#include "bird.h"

Bird::Bird(const std::string& wing_color, const std::string& description)
    : Animal(description) ,m_wing_color(wing_color)
{
}

Bird::~Bird()
{
}

