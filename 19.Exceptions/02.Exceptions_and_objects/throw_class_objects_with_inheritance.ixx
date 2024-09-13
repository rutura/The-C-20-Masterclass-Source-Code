module;

#include <string>
#include <fmt/format.h>

export module throw_class_objects_with_inheritance;

namespace throw_class_objects_with_inheritance{

    export class SomethingIsWrong
    {
    public:
    SomethingIsWrong(const std::string &s) : m_message(s) {}
    ~SomethingIsWrong() {}
    std::string what() const { return m_message; }

    protected:
    std::string m_message;
    };

    export class Warning : public SomethingIsWrong
    {
    public:
    Warning(const std::string &s) : SomethingIsWrong(s) {}
    std::string what() const { return m_message + " Yellow"; }
    };

    export class SmallError : public Warning
    {
    public:
    SmallError(const std::string &s) : Warning(s) {}
    std::string what() const { return m_message + " Orange"; }
    };

    export class CriticalError : public SmallError
    {
    public:
    CriticalError(const std::string &s) : SmallError(s) {}
    std::string what() const { return m_message + " Red"; }
    };


    //The do_something function
    export void do_something(size_t i)
    {
    if (i == 2) { throw CriticalError("i is 2"); }

    if (i == 3) { throw SmallError("i is 3"); }

    if (i == 4) { throw Warning("i is 4"); }
    fmt::println("Doing something at iteration : {}", i);
    }

}   // namespace throw_class_objects_with_inheritance