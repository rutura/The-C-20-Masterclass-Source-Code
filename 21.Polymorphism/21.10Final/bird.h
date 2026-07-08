#ifndef BIRD_H
#define BIRD_H
#include "animal.h"
class Bird : public Animal
{
public:
    Bird() = default;
    Bird(std::string_view wing_color, std::string_view description);
    
    virtual ~Bird();
    
    //This is contradictory : virtual and final have counter acting effects.
	//Final wins here
    virtual void fly() const final{
        std::cout << "Bird::fly() called for bird : " << m_description << std::endl;
    }
    
private : 
    std::string m_wing_color;
};

#endif // BIRD_H
