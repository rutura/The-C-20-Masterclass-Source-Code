/*
    . Exploring the ellipsis catch all block: 
        . It catches all exceptions.
        . The example code in utilities.ixx sets up a loop that 
            loops 5 times, but only the first two iterations will run
        . The second one will throw an exception that goes to be cought by 
            the ellipsis catch all block outside the loop.
*/
module;

#include <string>
#include <fmt/format.h>

export module exceptions_3;

namespace exceptions_3{

        // Base class for exceptions
    export class SomethingIsWrong {
    public:
        SomethingIsWrong(const std::string& s) : m_message(s) {}
        
        // Virtual destructor ensures proper cleanup for derived classes
        virtual ~SomethingIsWrong() = default;
        
        // Virtual function to allow overriding in derived classes
        virtual std::string what() const { return m_message; }

    protected:
        std::string m_message;
    };

    // Derived class representing a warning
    export class Warning : public SomethingIsWrong {
    public:
        Warning(const std::string& s) : SomethingIsWrong(s) {}

        // Override to provide specific message
        std::string what() const override { return m_message + " Yellow"; }
    };

    // Derived class representing a small error
    export class SmallError : public Warning {
    public:
        SmallError(const std::string& s) : Warning(s) {}

        // Override to provide specific message
        std::string what() const override { return m_message + " Orange"; }
    };

    // Derived class representing a critical error
    export class CriticalError : public SmallError {
    public:
        CriticalError(const std::string& s) : SmallError(s) {}

        // Override to provide specific message
        std::string what() const override { return m_message + " Red"; }
    };

    export void some_function(size_t i)
    {
        fmt::println("\nIteration: {}", i);
        if (i == 0) 
            throw 1;
        if (i == 2) 
            throw "const char*-Hello there";
        if (i == 3) 
            throw CriticalError("Something is wrong");
        if (i == 4) 
            throw std::string("std::string-Hello there");
    }
    
} // namespace exceptions_3