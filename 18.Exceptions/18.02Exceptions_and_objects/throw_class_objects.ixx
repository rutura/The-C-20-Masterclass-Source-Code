module;

#include <fmt/format.h>

export module throw_class_objects;

namespace throw_class_objects{

    export class SomethingIsWrong
    {
    public:
    SomethingIsWrong(const std::string &s) : m_message(s) {}

    // Copy Constructor
    SomethingIsWrong(const SomethingIsWrong &source)
    {
        fmt::println("Copy constructor for SomethingIsWrong called");
        m_message = source.m_message;
    }

    // Destructor
    ~SomethingIsWrong() { fmt::println("SomethingIsWrong destructor called"); }
    const std::string &what() const { return m_message; }

    private:
    std::string m_message;
    };


    export void do_something(size_t i)
    {
    if (i == 2) { throw SomethingIsWrong("i is 2"); }
    fmt::println("Doing something at iteration : {}", i);
    }

}   // namespace throw_class_objects