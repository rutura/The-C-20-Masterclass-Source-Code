/*
    . Catching standard exceptions
*/
module;

#include <string>

export module exceptions_1;

namespace exceptions_1{

    export class Animal
    {
    public:
        Animal(const std::string& n) : m_name(n) {}
        Animal() = default;
        virtual ~Animal() {}
        virtual void breathe() const {}

    protected:
        std::string m_name;
    };

    export class Feline : public Animal
    {
    public:
        Feline(const std::string& n) : Animal(n) {}

    private:
        int speed;
    };
    
} // namespace exceptions_1
