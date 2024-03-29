#ifndef FELINE_H
#define FELINE_H
#include "animal.h"
class Feline : public Animal
{
public:
    Feline() = default;
    Feline(const std::string& fur_style, const std::string& description);
    ~Feline();
    
    virtual void run() const{
        fmt::println( "Feline {} is running ", m_description);
    }
    
    //Stream insertable interface
     virtual void stream_insert(std::ostream& out)const override{
         out << "Feline [description : " << m_description << ", fur_style : " << 
                m_fur_style << "]";
     }
    void stream_insert(fmt::basic_memory_buffer<char> &out) const override {
        format_to_n(std::back_inserter(out), out.capacity(), "Feline [description : {}, fur_style : {}]", m_description, m_fur_style);
    }
    std::string m_fur_style;
};

#endif // FELINE_H
