module;

#include<fmt/format.h>

export module implicit_instantiations;

namespace implicit_instantiations{

    // Define a class template
    export template <typename T>
    class MyClass {
    public:
        // A function that has no error
        void safeFunction() {
            fmt::println("{}", "Safe function called");
        }

        // A function that has an error
        void errorFunction() {
            // Intentional error: assuming T is a class with a member function 'nonExistentFunction'
            T instance;
            instance.nonExistentFunction();  // This will cause an error if instantiated
        }
    };

}   // namespace implicit_instantiations 