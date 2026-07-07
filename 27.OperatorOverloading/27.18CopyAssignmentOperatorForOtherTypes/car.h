#ifndef CAR_H
#define CAR_H

#include <string>
class Car
{
public:
    Car() = default;
    Car(const std::string& color, int speed);
    ~Car();
    
    double get_speed()const{
        return m_speed;
    }
    std::string get_color() const{
        return m_color;
    }
private:
    std::string m_color;
    double m_speed;
};

#endif // CAR_H
