module;

#include <string>
#include <fmt/format.h>

export module ellipsis_catch_all;

namespace ellipsis_catch_all{

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

    export void some_function(size_t i)
    {
    if (i == 0) throw 1;
    if (i == 2) throw "const char*-Hello there";
    if (i == 3) throw CriticalError("Something is wrong");
    if (i == 4) throw std::string("std::string-Hello there");
    }

}   // namespace ellipsis_catch_all   