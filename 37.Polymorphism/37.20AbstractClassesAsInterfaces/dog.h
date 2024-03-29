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
        fmt::println( "Dog::bark called : Woof!");
    }
    
    virtual void stream_insert(std::ostream& out)const override{
         out << "Dog [description : " << m_description << ", fur_style : " << 
                m_fur_style << "]";
     }
    void stream_insert(fmt::basic_memory_buffer<char> &out) const override {
        fmt::format_to_n(std::back_inserter(out), out.capacity(), "Dog [description: {}, fur_style: {}]", m_description, m_fur_style);
    }

};

#endif // DOG_H
