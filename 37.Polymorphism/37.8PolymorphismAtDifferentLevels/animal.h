#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <string_view>
#include <fmt/format.h>

class Animal
{
public:
    Animal() = default;
    Animal(std::string_view description);
    virtual ~Animal();
    
    virtual void breathe()const{
        fmt::println( "Animal::breathe called for : {}" , m_description);
    }
    
protected: 
    std::string m_description;
};

#endif // ANIMAL_H
