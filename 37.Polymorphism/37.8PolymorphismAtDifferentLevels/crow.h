#ifndef CROW_H
#define CROW_H
#include "bird.h"

class Crow : public Bird
{
public:
    Crow() = default;
    Crow(std::string_view wing_color, std::string_view description);
    ~Crow();
    
    virtual void cow() const{
        fmt::println( "Crow::cow called fro crow : {}" , m_description );
    }

    virtual void breathe()const{
        fmt::println( "Crow::breathe called for : {}" , m_description );
    }

    virtual void fly() const override{
        fmt::println( "Crow::fly() called for bird : {}" , m_description );
    }

};

#endif // CROW_H
