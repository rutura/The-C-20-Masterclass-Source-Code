#ifndef CAT_H
#define CAT_H
#include "feline.h"
class Cat final : public Feline
{
public:
    Cat() = default;
    Cat(std::string_view fur_style, std::string_view description);
    virtual ~Cat();
    
    //Interesting fact #2
	//Useless virtual method. Cat is final, so no one will be deriving from
	//this class and have a chance to specialize it
    virtual void miaw() const{
        std::cout << "Cat::miaw() called for cat " << m_description << std::endl;
    }
	
	//This method is useful though
	void virtual run() const override{
		//
	}
};

#endif // CAT_H
