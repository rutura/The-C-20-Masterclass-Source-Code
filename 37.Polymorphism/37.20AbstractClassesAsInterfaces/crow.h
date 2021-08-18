#ifndef CROW_H
#define CROW_H
#include "bird.h"

class Crow : public Bird
{
public:
    Crow() = default;
    Crow(const std::string& wing_color, const std::string& description);
    ~Crow();
    
    virtual void cow() const{
        std::cout << "Crow::cow called fro crow : " << m_description << std::endl;
    }
    
    virtual void stream_insert(std::ostream& out)const override{
         out << "Crow [description : " << m_description << ", wing_color : " << 
                m_wing_color << "]";
     }

};

#endif // CROW_H
