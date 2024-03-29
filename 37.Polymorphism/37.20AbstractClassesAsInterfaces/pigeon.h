#ifndef PIGEON_H
#define PIGEON_H
#include "bird.h"
class Pigeon : public Bird
{
public:
    Pigeon() = default;
    Pigeon(const std::string& wing_color, const std::string& description);
    ~Pigeon();
    
    virtual void coo() const{
        fmt::println( "Pigeon::coo called for pigeon : {}", m_description);
    }
    
    void stream_insert(std::ostream& out)const override{
         out << "Pigeon [description : " << m_description << ", wing_color : " << 
                m_wing_color << "]";
     }
    void stream_insert(fmt::basic_memory_buffer<char> &out) const override {
        format_to_n(std::back_inserter(out), out.capacity(), "Pigeon [description : {}, wing_color : {}]", m_description, m_wing_color);
    }

};

#endif // PIGEON_H
