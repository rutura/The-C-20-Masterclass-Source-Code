#ifndef BIRD_H
#define BIRD_H
#include "animal.h"
class Bird : public Animal
{
public:
    Bird() = default;
    Bird(const std::string& wing_color, const std::string& description);
    
    ~Bird();
    
    virtual void fly() const{
        fmt::println("Bird::fly() called for bird : {}", m_description);
    }
    
    virtual void stream_insert(std::ostream& out)const override{
         out << "Bird [description : " << m_description << ", wing_color : " << 
                m_wing_color << "]";
     }
    void stream_insert(fmt::basic_memory_buffer<char> &out) const override {
        format_to_n(std::back_inserter(out), out.capacity(), "Bird [description: {}, wing_color: {}]", m_description, m_wing_color);
    }
    
protected : 
    std::string m_wing_color;
};

#endif // BIRD_H
