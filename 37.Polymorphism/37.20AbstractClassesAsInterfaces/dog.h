#ifndef DOG_H
#define DOG_H
#include "feline.h"
class Dog : public Feline
{
public:
    Dog() = default;
    Dog(const std::string& fur_style, const std::string& description);
    ~Dog();
    
    virtual void bark() const{
        std::cout << "Dog::bark called : Woof!" << std::endl;
    }
    
    virtual void stream_insert(std::ostream& out)const override{
         out << "Dog [description : " << m_description << ", fur_style : " << 
                m_fur_style << "]";
     }

};

#endif // DOG_H
