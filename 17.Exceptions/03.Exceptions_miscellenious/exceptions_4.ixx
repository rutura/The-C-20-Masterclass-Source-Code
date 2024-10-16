/*
    . Exploring the noexcept specifier.
        . It instructs the compiler not to allow exceptions to be thrown from a function.
        . To be specific, exceptions can be thrown, but they can't propagate out of the 
            function. The naming is a bit misleading.
        . As long as all thrown exceptions that are thrown in the function are handled in the function, 
            the program will not terminate.
*/
module;

#include <fmt/format.h>

export module exceptions_4;

namespace exceptions_4{

    export class Item {
    public:
        Item() {}

        void do_something_in_class() const noexcept {
            fmt::println("Doing something from class");
            try {
                throw 1;
            } catch (int ex) {
                fmt::println("Handling exception in Item::do_something_in_class");
                //throw; // Rethrowing in noexcept function/method will terminate program
            }
        }

    private:
        int m_member_var;
    };

    export void some_function() noexcept {
        try {
            throw 1;
        } catch (int ex) {
            fmt::println("Handling int exception in free function some_function()");
            //throw;
        }
    }
    
} // namespace exceptions_4
