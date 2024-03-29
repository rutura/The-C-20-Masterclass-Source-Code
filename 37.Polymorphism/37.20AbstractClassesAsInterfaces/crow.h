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
        fmt::println( "Crow::cow called fro crow : {}",  m_description);
    }
    
    virtual void stream_insert(std::ostream& out)const override{
         out << "Crow [description : " << m_description << ", wing_color : " << 
                m_wing_color << "]";
     }
    void stream_insert(fmt::basic_memory_buffer<char> &out) const override {
        fmt::format_to_n(std::back_inserter(out), out.capacity(), "Crow [description: {}, wing_color: {}]", m_description, m_wing_color);
    }
};

#endif // CROW_H
