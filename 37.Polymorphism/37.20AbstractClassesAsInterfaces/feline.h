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
        std::cout << "Feline " << m_description << " is running" << std::endl;
    }
    
    //Stream insertable interface
     virtual void stream_insert(std::ostream& out)const override{
         out << "Feline [description : " << m_description << ", fur_style : " << 
                m_fur_style << "]";
     }
    std::string m_fur_style;
};

#endif // FELINE_H
