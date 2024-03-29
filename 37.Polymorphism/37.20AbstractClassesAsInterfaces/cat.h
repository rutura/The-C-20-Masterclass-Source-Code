#ifndef CAT_H
#define CAT_H
#include "feline.h"
class Cat : public Feline
{
public:
    Cat() = default;
    Cat(const std::string& fur_style, const std::string& description);
    ~Cat();
    
    virtual void miaw() const{
        fmt::println( "Cat::miaw() called for cat {}", m_description );
    }
    
    void stream_insert(std::ostream& out)const override{
         out << "Cat [description : " << m_description << ", fur_style : " << 
                m_fur_style << "]";
     }
    void stream_insert(fmt::basic_memory_buffer<char> &out) const override {
        format_to_n(std::back_inserter(out), out.capacity(), "Cat [description: {}, fur_style: {}]", m_description, m_fur_style);
    }

};

#endif // CAT_H
