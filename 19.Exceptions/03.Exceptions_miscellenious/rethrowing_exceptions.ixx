module;

#include <string>
#include <fmt/format.h>

export module rethrowing_exceptions;

namespace rethrowing_exceptions{

    export class SomethingIsWrong
    {
    public:
    SomethingIsWrong(const std::string &s) : m_message(s) {}
    virtual ~SomethingIsWrong() {}
    virtual std::string what() const { return m_message; }

    protected:
    std::string m_message;
    };

    export class Warning : public SomethingIsWrong
    {
    public:
    Warning(const std::string &s) : SomethingIsWrong(s) {}
    virtual std::string what() const override { return m_message + " Yellow"; }
    };

    export class SmallError : public Warning
    {
    public:
    SmallError(const std::string &s) : Warning(s) {}
    virtual std::string what() const override { return m_message + " Orange"; }
    };

    export class CriticalError : public SmallError
    {
    public:
    CriticalError(const std::string &s) : SmallError(s) {}
    virtual std::string what() const override { return m_message + " Red"; }
    };


    export void do_something(size_t i)
    {
    if (i == 2) { throw CriticalError("i is 2"); }

    if (i == 3) { throw SmallError("i is 3"); }

    if (i == 4) { throw Warning("i is 4"); }
        fmt::println("Doing something at iteration : {}", i);
    }



}   // namespace rethrowing_exceptions