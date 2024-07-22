module;

#include <exception>
#include <string>
#include <fmt/format.h>

export module deriving_from_std_exceptions;

namespace deriving_from_std_exceptions{

    export class DivideByZeroException : public std::exception
    {
    public:
    DivideByZeroException(int a, int b) noexcept : std::exception(), m_a(a), m_b(b) {}

    virtual const char *what() const noexcept override
    {
        //Some compilers will give a warning that we're returning the address of a local string
        //link : https://www.udemy.com/instructor/communication/qa/17488954/detail/?course=2987082
        return (std::string("Divide by zero detected , dividing ") +
        std::to_string(m_a) + std::string(" by ") +
            std::to_string(m_b)).c_str();
        //return "divide by zero detected, dividing ";
    }

    int get_a() const { return m_a; }

    int get_b() const { return m_b; }

    private:
    int m_a{};
    int m_b{};
    };

    export int divide(int a, int b)
    {

    if (b == 0) throw DivideByZeroException(a, b);

    return a / b;
    }

}   // namespace deriving_from_std_exceptions