/*
        #5: Capturing the this pointers
            . You need to capture the this pointer to access member variables and member functions.
            . You can also capture all by value and you'll get the this pointer as part of the package.
*/
module;

#include <fmt/format.h>

export module lambdas_05;

namespace lambdas_05{

    export class Item {
    public:
        Item(int a, int b) : m_var1{a}, m_var2{b} {}

        void some_member_func() {
            auto func = [this]() { fmt::println("member vars : {} , {}", m_var1, m_var2); };
            func();
        }

    private:
        int m_var1;
        int m_var2;
    };

}   // namespace lambdas_05