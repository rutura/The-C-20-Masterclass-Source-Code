/*
    . Exploring exceptions when inheritance and polymorhism are involved: 
    . The chart: 
                    SomethingIsWrong
                    |
                    |-- Warning
                        |
                        |-- SmallError
                                |
                                |-- CriticalError

    . Catching by reference allows polymorphism to kick in.

*/
module;

#include <string>
#include <fmt/format.h>

export module exceptions_2;

namespace exceptions_2{

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

    // Function that throws different exceptions based on input
    export void do_something(size_t i) {
        try {
            if (i == 2) {
                throw CriticalError("CriticalError: i is 2");
            }
            if (i == 3) {
                throw SmallError("SmallError: i is 3");
            }
            if (i == 4) {
                throw Warning("Warning: i is 4");
            }

            fmt::println("Doing something at iteration: {}", i);
        } catch (const SomethingIsWrong& e) {
            fmt::println("Caught exception: {}", e.what());
        }
    }
    
} // namespace exceptions_2
