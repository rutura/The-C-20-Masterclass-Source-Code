module;

#include <fmt/format.h>

export module exceptions_5;

namespace exceptions_5{

    void exception_thrower() { throw 'z'; }

    export void some_function()
    {
        for (size_t i{}; i < 15; ++i) {
            fmt::println("Iteration : {}", i);

            try {// Outer try block
            // Exceptions thrown in this scope are
            // handled in outer catch blocks
            if (i == 2) {
                throw "exception for int 2 thrown";// Throws const char*
            }

            try {// Inner try block

                if (i == 5) {
                throw 'd';// Throw char,  Will be  handled by inner catch block
                }

                if (i == 7) {
                throw i;// Thrown as size_t Will be handled in outer block
                }

                if (i == 8) { exception_thrower(); }

                if (i == 9) {
                throw std::string("string thrown for int 9");// Inner and outer catch blocks
                                                            // can't handle it, may be handled by try block
                                                            // wrapping around the function
                }

            } catch (char ex) {// Inner catch
                fmt::println("Inner catch(char) block : cought thrown for : {}", ex);
            }

            } catch (const char *ex) {// Outer catch
            fmt::println("Outer catch(const char*) block , cought  :{}", ex);
            } catch (size_t ex) {// Outer catch
            fmt::println("Outer catch(size_t) block, cought {}", ex);
            }
        }
    }
    
} // namespace exceptions_5