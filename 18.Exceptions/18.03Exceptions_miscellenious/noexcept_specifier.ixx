module;

#include <fmt/format.h>

export module noexcept_specifier;

namespace noexcept_specifier{

    export class Item
    {
    public:
    Item() {}

    void do_something_in_class() const noexcept
    {
        fmt::println("Doing something from class");
        try {
        throw 1;
        } catch (int ex) {
        fmt::println("Handling exception in Item::do_something_in_class");
        // throw; // Rethrowing in noexcept function/method will terminate program
        }
    }

    private:
    int m_member_var;
    };

    export void some_function() noexcept
    {

    try {
        throw 1;
    } catch (int ex) {
        fmt::println("Handling int excpetion in free function some_function()");
        // throw;
    }
    }

}   // namespace noexcept_specifier