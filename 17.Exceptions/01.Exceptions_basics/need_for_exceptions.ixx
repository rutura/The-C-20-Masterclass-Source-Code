module;

#include <fmt/format.h>

export module need_for_exceptions;

namespace need_for_exceptions{

    export class Animal
    {
    public:
    Animal() = default;
    virtual void breathe() const {};

    private:
    std::string m_description;
    };


    export class Dog : public Animal
    {
    public:
    Dog() = default;
    virtual void breathe() const override{};
    void run() { fmt::println("Dog running..."); }

    private:
    std::string m_fur_color;
    };


    /*  Function throws const char* exception when par_b is zero  */
    export void process_parameters(int par_a, int par_b)
    {

    // Do some processing
    if (par_b == 0) throw "Potential division by 0 detected";

    int result = par_a / par_b;

    // Some other processing.
    }

}   // namespace need_for_exceptions