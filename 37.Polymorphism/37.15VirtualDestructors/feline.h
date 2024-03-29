#ifndef FELINE_H
#define FELINE_H
#include "animal.h"
class Feline : public Animal
{
public:
    Feline() = default;
    Feline(std::string_view fur_style, std::string_view description);
     virtual ~Feline();
    
    virtual void run() const{
        fmt::println( "Feline {} is running", m_description);
    }
    std::string m_fur_style;
};

#endif // FELINE_H
